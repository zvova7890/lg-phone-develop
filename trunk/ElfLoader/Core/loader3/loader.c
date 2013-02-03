/*
 * Этот файл является частью программы ElfLoader
 * Copyright (C) 2011 by Z.Vova, Ganster
 * Licence: GPLv3
 */

#include <string.h>
#include <stdio.h>
#include "loader.h"
#include "../core.h"


/* for testing on pc */
#ifdef _test_linux
#include <fcntl.h>
#include <unistd.h>
#include "fix.h"
int loader_warnings = 1;
int realtime_libclean = 1;
int AddrLibrary() {return 1;}

void ep_log(Elf32_Exec *ex, const char *l, int sz) {
    printf("AAA: %s\n", l);
}
#endif

void zeromem_a(void *mem, int size) {
  memset(mem, 0, size);
}

void l_msg(int a, int b) {
  __core_lprintf("Loader: %s\n", b);
}


/* wraper for thumb-mode calling */
#ifdef __thumb_mode
extern __arm void l_msg(int a, int b);

__arm void *memcpy_a(void *dest, const void *src, size_t size) {
    return memcpy(dest, src, size);
}

__arm int memcmp_a (const void *m1, const void *m2, size_t n) {
    return memcmp(m1, m2, n);
}
#else

#define l_msg ShowMSG
#define memcpy_a memcpy
#define memcmp_a memcmp
#endif


unsigned int ferr;



// Проверка валидности эльфа
__arch int CheckElf(Elf32_Ehdr *ehdr)
{
    if(memcmp_a(ehdr, elf_magic_header, sizeof(elf_magic_header))) return E_HEADER;
    if(ehdr->e_machine != EM_ARM) return E_MACHINE;

    return E_NO_ERROR;
}


// Получение нужного размера в раме
__arch unsigned int calc_binary_size(Elf32_Exec *ex, Elf32_Phdr* phdrs)
{
    unsigned int i = 0;
    unsigned long maxadr=0;
    unsigned int end_adr;

    while (i < ex->ehdr.e_phnum)
    {
        Elf32_Phdr phdr = phdrs[i];

        if (phdr.p_type == PT_LOAD)
        {
            if (ex->v_addr > phdr.p_vaddr) ex->v_addr = phdr.p_vaddr;
            end_adr = phdr.p_vaddr + phdr.p_memsz;
            if (maxadr < end_adr) maxadr = end_adr;
        }
        ++i;
    }
    return maxadr - ex->v_addr;
}



__arch char* LoadData(Elf32_Exec* ex, int offset, int size)
{
#ifdef _test_linux
    if(size > 0 && lseek(ex->fp, offset, FILE_SEEK_SET) > -1)
#else
    if(size > 0 && fs_seek(ex->fp, FILE_SEEK_SET, offset) > -1)
#endif
    {
        char* data = malloc(size+1);
	if(!data) {
	    lprintf("LoadData: No memory available\n");
	    return 0;
	}
#ifdef _test_linux
        if(fread(ex->fp, data, size) == size)
#else
        if(fs_read(ex->fp, data, size) == size)
#endif
        {
            data[size] = 0;
            return data;
        }
        else free(data);
    }

    return 0;
}


__arch int SLoadData(Elf32_Exec* ex, char *adr, int offset, int size)
{
#ifdef _test_linux
    if(size && lseek(ex->fp, offset, FILE_SEEK_SET) > -1)
#else
    if(size && fs_seek(ex->fp, FILE_SEEK_SET, offset) > -1)
#endif
    {
#ifdef _test_linux
        if(fs_read(ex->fp, adr, size) == size)
#else
        if(fs_read(ex->fp, adr, size) == size)
#endif
        {
            adr[size] = 0;
            return size;
        }
    }

    return 0;
}


/* Вспомогательная функция */
__arch static inline unsigned int _look_sym(Elf32_Exec *ex, const char *name, unsigned long hash)
{
    Libs_Queue *lib = ex->libs;
    unsigned int func = 0;
    while(lib && !func)
    {
        func = (unsigned int)FindFunction(lib->lib, name, hash);
        lib = lib->next;
    }
    return func;
}


/* функция пролетается рекурсивно по либам которые в зависимостях */
__arch unsigned int try_search_in_base(Elf32_Exec* ex, const char *name, unsigned long hash, int bind_type)
{
    printf("'%s' Searching in libs... \n", name);
    unsigned int address = 0;

    if(ex->type == EXEC_LIB && !ex->dyn[DT_SYMBOLIC])
        address = findExport(ex, name, hash);

    if(!address)
        address = (unsigned int)_look_sym(ex, name, hash);

    if( !address )
    {
	if(ex && ex->parents.ex)
        {
	    //Elf32_Exec *parent = ex->parents;
	    printf("parent: %X\nname: %s\n", ex, name);

	    for(Libs_Queue *libq = ex->parents.ex; libq; libq = libq->next)
	    {
		printf("libq: %X\n", libq->lib);
		Elf32_Exec *n = libq->lib;
		if(n)
		{
		    address = findExport(n, name, hash);
		
		    if(!address)
			address = (unsigned int)_look_sym(n, name, hash);
		
		    if(address)
			break;
		}
	    }
        }
    }
    
    if(!address)
	printf(" not found!\n");
    else 
	printf(" %X found\n", address);

    return address;
}


unsigned int objectAddress(Elf32_Exec *ex, Elf32_Sym *sym, const char *name, unsigned long hash, int reloc_type, int bind_type, int *ncheck)
{
    printf("Lookup '%s' %X rel: %d bind: %d\n", name, sym->st_value, reloc_type, bind_type);
    *ncheck = 0;
    unsigned int func = 0;
    
    printf("local: %d st_value: %X st_shndx: %X\n", bind_type == STB_LOCAL, sym->st_value, sym->st_shndx);
    
    switch(bind_type)
    {
    case STB_LOCAL:
    case STB_GLOBAL:
	printf("STB_GLOBAL\n");

        switch(sym->st_shndx)
        {
          case SHN_ABS:
            printf("Absolute st_value: %X\n", sym->st_value);
            func = sym->st_value;
            break;
            
          default:
            if(sym->st_value) {
		printf("Have st_value %d\n", sym->st_value);
		func = ((unsigned int)ex->body)+sym->st_value;
	    }
	    else
		func = try_search_in_base(ex, name, hash, bind_type);
            break;
        }
        
	break;

    case STB_WEAK:
	printf("STB_WEAK %x\n", ex->body+sym->st_value);
	if(sym->st_value)
	    func = ((unsigned int)ex->body)+sym->st_value;
	else
	    func = try_search_in_base(ex, name, hash, bind_type);

	*ncheck = 1;
	break;
	
    default:
	printf("STB_!UNK!\n");
	//func = try_search_in_base(ex, name, hash, bind_type);
	break;
    }
    
    return func;
}


#define Warn(ex, ...) \
  ep_log(ex, dbg, sprintf(dbg, ##__VA_ARGS__));

// Релокация
__arch int DoRelocation(Elf32_Exec* ex, Elf32_Dyn* dyn_sect, Elf32_Phdr* phdr)
{
    unsigned int i = 0;
    Elf32_Word libs_needed[64];
    unsigned int libs_cnt = 0;
    char dbg[128];
    char *prev_name = 0;
    unsigned long prev_hash = 0, prev_func = 0;
	
    /* чтобы не повторять поиск, найденого в пердидущий поиск адреса,
       мы запоминаем хеш и имя, проверяем перед поиском, если свопадают -
       то ничего не ищем, а сразу отдаём адрес
    */
    
    // SHN_ABS - is direct address, no need it to cache
#define check_prev_indexing(sym, phash, pname, set_v, jmp_l) \
	if(sym->st_shndx != SHN_ABS && prev_name && phash == prev_hash && !strcmp(pname, prev_name)) { \
	   set_v = prev_func; \
	   if(1) printf("Have indexed value: %s - %X\n", pname, prev_func); \
	   goto jmp_l; \
	} else { \
	    prev_hash = phash; \
	    prev_name = pname; \
	}
    

    // Вытаскиваем теги
    while (dyn_sect[i].d_tag != DT_NULL)
    {
        if (dyn_sect[i].d_tag <= DT_FLAGS)
        {
            switch(dyn_sect[i].d_tag)
            {
            case DT_SYMBOLIC:
                // Флаг SYMBOLIC-библиотек. В d_val 0, даже при наличии :(
                ex->dyn[dyn_sect[i].d_tag] = 1;
                break;
            case DT_NEEDED:
                // Получаем смещения в .symtab на имена либ
                libs_needed[libs_cnt++] = dyn_sect[i].d_un.d_val;
                break;
            default:
                ex->dyn[dyn_sect[i].d_tag] = dyn_sect[i].d_un.d_val;
            }
        }
        ++i;
    }

    // Таблички. Нужны только либам, и их юзающим)
    ex->symtab = ex->dyn[DT_SYMTAB]? (Elf32_Sym*)(ex->body + ex->dyn[DT_SYMTAB] - ex->v_addr) : 0;
    ex->jmprel = (Elf32_Rel*)(ex->body + ex->dyn[DT_JMPREL] - ex->v_addr);
    ex->strtab = ex->dyn[DT_STRTAB]? ex->body + ex->dyn[DT_STRTAB] - ex->v_addr : 0;
    
    printf("STRTAB: %X\n", ex->dyn[DT_STRTAB]);
    printf("SYMTAB: %X %X\n", ex->dyn[DT_SYMTAB], ex->symtab);

    if(ex->type == EXEC_LIB)
    {
        Elf32_Word* hash_hdr = (Elf32_Word*)LoadData(ex, ex->dyn[DT_HASH], 8);
        if(hash_hdr)
        {
            int hash_size = hash_hdr[0] * sizeof(Elf32_Word) + hash_hdr[1] * sizeof(Elf32_Word) + 8;
            ex->hashtab = (Elf32_Word*)LoadData(ex, ex->dyn[DT_HASH], hash_size);
            free(hash_hdr);
            if(!ex->hashtab) goto __hash_err;
        }
        else
        {
__hash_err:
            //ShowMSG(1, (int)"Error loading hashtab");
            ep_log(ex, "Hash tab is mising", 18);
            return E_HASTAB;
        }
    }

    // Загрузка библиотек
    for(i=0; i < libs_cnt; ++i)
    {
        char *lib_name = ex->strtab + libs_needed[i];
        Elf32_Lib* lib;
        if( (lib = OpenLib(lib_name, ex)) )
        {
            Libs_Queue* libq = malloc(sizeof(Libs_Queue));
            libq->lib = lib;

            if(ex->libs) libq->next = ex->libs;
            else libq->next = 0;

            ex->libs = libq;
        }
        else
        {
            int csz = sprintf(dbg, "Не могу загрузить %s!", lib_name);
            //l_msg(1, (int)dbg);
            // FIXME
            ep_log(ex, dbg, csz);
            return E_SHARED;
        }
    }

    // Релокация
    if (ex->dyn[DT_RELSZ])
    {
        i=0;
        unsigned int* addr;
        char* name;
        Elf32_Word r_type;
        unsigned int func = 0;
        int symtab_index = 0;
        int bind_type = 0;
        int reloc_type = 0;

        // Таблица релокаций
        //Elf32_Rel* reltab = (Elf32_Rel*)LoadData(ex, (phdr->p_offset - phdr->p_vaddr) + ex->dyn[DT_REL], ex->dyn[DT_RELSZ]);
        Elf32_Rel* reltab = (Elf32_Rel*)malloc(ex->dyn[DT_RELSZ]+1);

        if(!reltab)
        {
            int csz = sprintf(dbg, "Out of memory.\n");
            //l_msg(1, (int)dbg);
            ep_log(ex, dbg, csz);
            return E_RAM;
        }
        
        /*
          * У нас сегмент уже прочитан, а релокация находится в нём
          * Поэтому нет необходимости читать его ещё раз
        */

        unsigned int off_tbl = ex->dyn[DT_REL];
        unsigned int readed = 0;
        if(off_tbl >= phdr->p_offset && off_tbl < phdr->p_offset+phdr->p_memsz)
        {
          unsigned int reloff = (off_tbl - phdr->p_offset);
          unsigned int can_cpy = phdr->p_memsz - reloff;
          
          memcpy_a(reltab, dyn_sect+ reloff, can_cpy);
          readed += can_cpy;
        }
        
        /* на случай, если в секции мало данных */
        if(readed < ex->dyn[DT_RELSZ])
          readed += SLoadData(ex, ((char*)reltab)+readed, 
                    (phdr->p_offset - phdr->p_vaddr) + readed + ex->dyn[DT_REL], 
                    ex->dyn[DT_RELSZ] - readed);
        
        if(readed < ex->dyn[DT_RELSZ])
        {
            int csz = sprintf(dbg, "Invalid relocation table(not full).\n");
            //l_msg(1, (int)dbg);
            ep_log(ex, dbg, csz);
            free(reltab);
            return E_RELOCATION;
        }

        while(i * sizeof(Elf32_Rel) < ex->dyn[DT_RELSZ])
        {
            r_type = ELF32_R_TYPE(reltab[i].r_info);
            symtab_index = ELF32_R_SYM(reltab[i].r_info);
	   
	    Elf32_Sym *sym = ex->symtab? &ex->symtab[symtab_index] : 0;
            bind_type = sym ? ELF_ST_BIND(sym->st_info) : 0;
            reloc_type = sym ? ELF_ST_TYPE(sym->st_info) : 0;
            addr = (unsigned int*)(ex->body + reltab[i].r_offset - ex->v_addr);

            switch(r_type)
            {
            case R_ARM_NONE:
                break;
		
            case R_ARM_RABS32:
                printf("R_ARM_RABS32\n");
                *addr += (unsigned int)(ex->body - ex->v_addr);
                printf("*addr = %X\n", *addr);
                break;
            case R_ARM_ABS32:
                printf("R_ARM_ABS32\n");
                name = sym? ex->strtab + sym->st_name : 0;
                func = 0;

                if( !ex->symtab )
                {
		    int csz = sprintf(dbg, "warning: symtab not found, but relocation R_ARM_ABS32 is exist");
		    if(ep_config.loader_warnings)
		      ep_log(ex, dbg, csz);
		    *addr = (unsigned int)ex->body;
		    break;
                }

                if( !ex->strtab )
                {
		    int csz = sprintf(dbg, "warning: symtab not found, but relocation R_ARM_ABS32 is exist");
		    if(ep_config.loader_warnings)
		      ep_log(ex, dbg, csz);
		    
		    *addr = (unsigned int)ex->body;
		    break;
                }

                /* на всякий случай, вдруг сум пустой будет */
                if(sym)
                {
                    // Если нужен указатель на эльф
                    if( name[4] == 0   &&
                            name[0] == '_' &&
                            name[1] == '_' &&
                            name[2] == 'e' &&
                            name[3] == 'x'
                      )
                    {
                        ex->__is_ex_imported = 1;
                        *addr = (unsigned int)ex;
                        break;
                    }
                    
                    unsigned long hs = name_hash(name);

                    check_prev_indexing(sym, hs, name, func, skeep_err);
                    
                    int ncheck = 0;
                    func = objectAddress(ex, sym, name, hs, reloc_type, bind_type, &ncheck);
                    prev_func = func;
                    if(ncheck)
			goto skeep_err;

                }
                else {
                    func = 0;
                }

                /* ничего не нашли, жаль */
                if(!func && bind_type != STB_WEAK)
                {
                    int csz = sprintf(dbg, "[2] Undefined reference to `%s'\n", name?name : "");
                    ep_log(ex, dbg, csz);
                    return E_UNDEF;
                }

skeep_err:

                /* в ABS32 релоке в *addr всегда должен быть 0 */
                *addr += func;
                break;
		
            case R_ARM_RELATIVE:
                printf("R_ARM_RELATIVE\n");
                *addr += (unsigned int)(ex->body - ex->v_addr);
                break;

            case R_ARM_GLOB_DAT:
            case R_ARM_JUMP_SLOT:
                printf("R_ARM_GLOB_DAT\n");

                if( !ex->symtab )
                {
                    int csz = sprintf(dbg, "Relocation R_ARM_GLOB_DAT cannot run without symtab\n");
                    ep_log(ex, dbg, csz);
                    free(reltab);
                    return E_SYMTAB;
                }

                if( !ex->strtab )
                {
                    int csz = sprintf(dbg, "Relocation R_ARM_GLOB_DAT cannot run without strtab\n");
                    ep_log(ex, dbg, csz);
                    free(reltab);
                    return E_STRTAB;
                }
                
                name = sym? ex->strtab + sym->st_name : 0;

                printf(" strtab: '%s' \n", name);

                if( symtab_index && name )
                {
                    unsigned long hs = name_hash(name);
                    int ncheck = 0;
                    check_prev_indexing(sym, hs, name, func, skeep_err1);
                    
                    func = objectAddress(ex, sym, name, hs, reloc_type, bind_type, &ncheck);
                    prev_func = func;
                    if(ncheck)
			goto skeep_err1;


                    if(!func && bind_type != STB_WEAK)
                    {
                        int csz = sprintf(dbg, "[2] Undefined reference to `%s'\n", name?name : "");
                        //l_msg(1, (int)dbg);
                        ep_log(ex, dbg, csz);
                        free(reltab);
                        return E_UNDEF;
                    }

skeep_err1:

                    /* В доках написано что бинды типа STB_WEAK могут быть нулевыми */
                    *addr = func;

                    if(*addr)
                    {
                        printf("found at 0x%X\n", *addr);
                    }
                    else
                    {
                        printf("warning: address is zero\n");
                    }
                } else {
                    int csz = sprintf(dbg, "Symtab index or symbol name not found. Bad relocation\n");
                    //l_msg(1, (int)dbg);
                    ep_log(ex, dbg, csz);
                    free(reltab);
                    return E_RELOCATION;
                }

                break;

		
            case R_ARM_COPY:
                printf("R_ARM_COPY\n");
                
                if(!sym) {
                    int csz = sprintf(dbg, "R_ARM_COPY: Symtab not found. Bad relocation\n");
                    ep_log(ex, dbg, csz);
                    free(reltab);
                    return E_RELOCATION;
                }
                
                memcpy_a((void *) addr,
                         (void *)(ex->body + sym->st_value), sym->st_size);
                break;

		
	    /* хз чо за релок, ни в одном лоадере его не встречал, 
	     * хотя по описанию похож на R_ARM_REL32.
	     * Но, если выполнить релокацию по описанию - эльфятник падает.
	     * С пропуском - работает, так что хайтек.
	     */
            case R_ARM_THM_RPC22:
                printf("R_ARM_THM_RPC22 stub\n");
                break;

                // S + A - P
            case R_ARM_REL32:
                printf("R_ARM_REL32\n");
                
                if(!sym) {
                    int csz = sprintf(dbg, "R_ARM_REL32: Symtab not found. Bad relocation\n");
                    ep_log(ex, dbg, csz);
                    free(reltab);
                    return E_RELOCATION;
                }
                
                *addr += sym->st_value - (unsigned int)addr;
                break;

            default:
                printf("unknow relocation type '%d'\n", r_type);
                int csz = sprintf(dbg, "Fatal error! Unknown type relocation '%d'!\n", r_type);
                //l_msg(1, (int)dbg);
                ep_log(ex, dbg, csz);
                free(reltab);
                return E_RELOCATION;
            }
            ++i;
        }

        free(reltab);
    }

    // Биндим функции
    if(ex->dyn[DT_PLTRELSZ])
    {
        i=0;
        while(i * sizeof(Elf32_Rel) < ex->dyn[DT_PLTRELSZ])
        {
            int sym_idx = ELF32_R_SYM(ex->jmprel[i].r_info);
            char* name = ex->strtab + ex->symtab[sym_idx].st_name;
            Elf32_Sym *sym = &ex->symtab[sym_idx];
            Elf32_Word func = 0;
            int bind_type = sym? ELF_ST_BIND(sym->st_info) : 0;
	    int reloc_type = sym ? ELF_ST_TYPE(sym->st_info) : 0;
	    int ncheck = 0;
    
	    if(sym) {
              unsigned long hs = name_hash(name);
              check_prev_indexing(sym, hs, name, func, skeep_err2);

              func = objectAddress(ex, sym, name, hs, reloc_type, bind_type, &ncheck);
              prev_func = func;
            }
	    if(ncheck)
		goto skeep_err2;
	    
            if(!func && bind_type != STB_WEAK)
            {
                int csz = sprintf(dbg, "[3] Undefined reference to `%s'\n", name);
                //l_msg(1, (int)dbg);
                ep_log(ex, dbg, csz);
                return E_UNDEF;
            }

        skeep_err2:
            *((Elf32_Word*)(ex->body + (ex->jmprel[i].r_offset - ex->v_addr))) = func;
            ++i;
        }
    }

    return E_NO_ERROR;
}


// Чтение сегментов из файла
__arch int LoadSections(Elf32_Exec* ex)
{
    Elf32_Phdr* phdrs = malloc(sizeof(Elf32_Phdr) * ex->ehdr.e_phnum);
    if(!phdrs) return E_SECTION;

    unsigned int hdr_offset = ex->ehdr.e_phoff;
    int i = 0;

    unsigned long maxadr = 0;
    unsigned int end_adr;

    // Читаем заголовки
    while(i < ex->ehdr.e_phnum)
    {
#ifdef _test_linux
        if(lseek(ex->fp, hdr_offset, S_SET) == -1 ||
           fread(ex->fp, &phdrs[i], sizeof(Elf32_Phdr)) != sizeof(Elf32_Phdr))
#else
        if(fs_seek(ex->fp, FILE_SEEK_SET, hdr_offset) < 0 || 
           fs_read(ex->fp, &phdrs[i], sizeof(Elf32_Phdr)) != sizeof(Elf32_Phdr))
#endif
        {
            /* кривой заголовок, шлём нафиг этот эльф */
            free(ex->body);
            ex->body = 0;
            free(phdrs);
            return E_PHDR;
        }

        /* тут же и размер бинарника посчитаем */
        if (phdrs[i].p_type == PT_LOAD)
        {
            if (ex->v_addr > phdrs[i].p_vaddr) ex->v_addr = phdrs[i].p_vaddr;
            end_adr = phdrs[i].p_vaddr + phdrs[i].p_memsz;
            if (maxadr < end_adr) maxadr = end_adr;
        }

        hdr_offset += ex->ehdr.e_phentsize;
        ++i;
    }

    ex->bin_size = maxadr - ex->v_addr;

    if(i == ex->ehdr.e_phnum) // Если прочитались все заголовки
    {
        //ex->bin_size = GetBinSize(ex, phdrs);

        if(ex->body = calloc(1, ex->bin_size+1)) // Если хватило рамы
        {
            //zeromem_a(ex->body, ex->bin_size+1);
            zeromem_a(ex->dyn, sizeof(ex->dyn));

            for(i=0; i < ex->ehdr.e_phnum; ++i)
            {
                Elf32_Phdr phdr = phdrs[i];
                Elf32_Dyn* dyn_sect;

                switch (phdr.p_type)
                {
                case PT_LOAD:
                    printf("PT_LOAD: %X - %X\n", phdr.p_offset, phdr.p_filesz);
                    if(!phdr.p_filesz) break;
                    
#ifdef _test_linux
                    if(lseek(ex->fp, phdr.p_offset, S_SET) != -1)
#else
                    if(fs_seek(ex->fp, FILE_SEEK_SET, phdr.p_offset) > -1)
#endif
                    {
#ifdef _test_linux
                        if(fread(ex->fp, ex->body + phdr.p_vaddr - ex->v_addr, phdr.p_filesz) == phdr.p_filesz)
#else
			if(fs_read(ex->fp, ex->body + phdr.p_vaddr - ex->v_addr, phdr.p_filesz) == phdr.p_filesz)
#endif
                           break;
                    }

                    // Не прочитали сколько нужно
                    free(ex->body);
                    ex->body = 0;
                    free(phdrs);
                    return E_SECTION;

                case PT_DYNAMIC:
                    if(phdr.p_filesz == 0) break; // Пропускаем пустые сегменты

                    printf("Load data dynamic segment: %d - %d\n", phdr.p_offset, phdr.p_filesz);
                    if( (dyn_sect = (Elf32_Dyn*)LoadData(ex, phdr.p_offset, phdr.p_filesz)) )
                    {
                        if(!DoRelocation(ex, dyn_sect, &phdr))
                        {
                            free(dyn_sect);
                            break;
                        }
                    }

                    // Если что-то пошло не так...
                    if(dyn_sect)
                      free(dyn_sect);
                    
                    free(ex->body);
                    ex->body = 0;
                    free(phdrs);
                    return E_SECTION;
                }
            }

            free(phdrs);
            return E_NO_ERROR;
        }
    }

    free(ex->body);
    ex->body = 0;
    free(phdrs);
    return E_RAM;
}


/* constructors */
__arch void executeInitializersArray(Elf32_Exec *ex)
{
    if(!ex->dyn[DT_FINI_ARRAY]) return;
    size_t sz = ex->dyn[DT_INIT_ARRAYSZ] / sizeof (void*);
    void ** arr = (void**)(ex->body + ex->dyn[DT_INIT_ARRAY] - ex->v_addr);

    printf("init_array sz: %d\n", sz);

    for(int i=0; i < sz; ++i)
    {
        printf("init %d: 0x%X\n", i, arr[i]);
#ifndef _test_linux
        ( (void (*)())arr[i])();
#endif
    }
}


/* destructors */
__arch void executeFinishesArray(Elf32_Exec *ex)
{
    if(!ex->dyn[DT_FINI_ARRAY]) return;
    size_t sz = ex->dyn[DT_FINI_ARRAYSZ] / sizeof (void*);
    void ** arr = (void**)(ex->body + ex->dyn[DT_FINI_ARRAY] - ex->v_addr);

    printf("fini_array sz: %d\n", sz);

    for(int i=0; i < sz; ++i)
    {
        printf("fini %d: 0x%X\n", i, arr[i]);
#ifndef _test_linux
        ( (void (*)())arr[i])();
#endif
    }
}
