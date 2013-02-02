
/*
 * Этот файл является частью программы ElfLoader
 * Copyright (C) 2011 by Z.Vova, Ganster
 * Licence: GPLv3
 */

#include <string.h>
#include <stdio.h>
#include "../core.h"
#include "loader.h"
#include "env.h"



char tmp[258] = {0}, dlerr[128]={0};

#ifdef __thumb_mode
extern __arm void *memcpy_a (void *dest, const void *src, size_t size);
__arm char * strrchr_a (const char *s, int c){
  return strrchr(s, c);
}

#else
#define memcpy_a memcpy
#define AddrLibrary_a AddrLibrary
#define strrchr_a strrchr
#endif


Global_Queue* lib_top = 0;
Elf32_Lib** handles = 0;
int handles_cnt = 0;



void loadlib_init() 
{
    lib_top = 0;
    handles = 0;
    handles_cnt = 0;
}




int is_parent_exist(Elf32_Exec *ex, Elf32_Exec *parent)
{
    Libs_Queue * libs = ex->parents.ex, *i;
  
    for( i = libs; i; i = i->next )
    {
	if(i->lib == parent)
	    return 1;
    }
    
    return 0;
}


void __ex_push_parent(Elf32_Exec *ex, Elf32_Exec *parent)
{
    if(!ex || !parent) return;
    
    Libs_Queue * libs = ex->parents.ex, *newex = malloc(sizeof(Libs_Queue));
    
    if(is_parent_exist(ex, parent)) return;

    newex->next = 0;
    newex->lib = parent;
    
    if(libs) {
	libs->next = newex;
    
    } else {
	ex->parents.ex = newex;
    }
}



 /*
  * Существует ли файл
  */
__arch char __is_file_exist(const char *fl)
{
#ifdef _test_linux
    return access(fl, 0) != -1;
#else
    FS_INFO st;
    if( fs_getinfo(fl, &st) < 0 )
      return 0;
#endif
    return 1;
}




 /*
  * Возвращает хеш имени
  */
__arch unsigned long name_hash(const char* name)
{
    unsigned long hash = 0;
    unsigned long hi;
    /* два раза *name требует больше времени */
    register unsigned char c = *name++;
    
    while (c != '\0')
    {
        hash = (hash << 4) + c;
        hi = hash & 0xf0000000;
        /*if (hi != 0)
        {
            hash ^= hi >> 24;
            hash ^= hi;
        }*/
        /* оптимизация из uclibc */
        hash ^= hi;
	hash ^= hi >> 24;
        
        c = *name++;
    }
    return hash;
}



 /*
  * Находит в библиотеке требуемый експорт
  */
__arch Elf32_Word findExport (Elf32_Exec* ex, const char* name, unsigned long hash)
{
    if(!ex || !ex->hashtab) return 0;

    Elf32_Word nbucket = ex->hashtab[0];
    //Elf32_Word nchain = ex->hashtab[1];
    Elf32_Word* bucket = &ex->hashtab[2];
    Elf32_Word* chain = &ex->hashtab[2 + nbucket];
    Elf32_Word func = 0;
    int symidx;

    for (symidx = bucket[/*__e_div(nbucket, hash)*/ hash % nbucket ]; symidx != STN_UNDEF; symidx = chain[symidx])
    {
        Elf32_Sym sym = ex->symtab[symidx];

        if (sym.st_value == 0 || sym.st_shndx == SHN_UNDEF)
            continue;

        switch (ELF_ST_TYPE(sym.st_info))
        {
        case STT_NOTYPE:
        case STT_FUNC:
        case STT_OBJECT:
            break;
        default:
            /* Not a code/data definition. */
            continue;
        }

        if (strcmp (ex->strtab + sym.st_name, name))
            /* Not the symbol we are looking for. */
            continue;

        switch (ELF_ST_BIND(sym.st_info))
        {
            case STB_GLOBAL:
                /* Global definition.  Just what we need. */
                return (Elf32_Word)ex->body + sym.st_value;
            case STB_WEAK:
                /* Weak definition.  Use this value if we don't find another. */
                func = (Elf32_Word)ex->body + sym.st_value;
                break;
        default:
            /* Local symbols are ignored.  */
            break;
        }
    }

    return func;
}



__arch Elf32_Word FindFunction(Elf32_Lib* lib, const char *name, unsigned long hash)
{
    if(!lib) return 0;
    return findExport(lib->ex, name, hash);
}



 /*
  * пропарсить содержимое переменной LD_LIBRARY_PATH
  * путь1;путь2;путь3;
  */
__arch char * envparse(const char *str, char *buf, int num)
{
  if( !str || !buf || num < 0) return 0;
  const char *start = str;
  const char *s = strchr(str, ';');
  
  while(num-- && start)
  {
    start = s? s+1:0;
    if(start)
      s = strchr(start, ';');
    else s = 0;
  }
  
  if(!s){
    switch( start ? 1:0 )
    {
      case 0:
	return 0;
      case 1:
	s = str + strlen(str);
    }
  }

  memcpy_a(buf, start, s-start);
  buf[s-start] = 0;
  return buf;
}



 /*
  * Поиск библиотек в папках переменной окружения
  */
__arch const char * findShared(const char *name)
{
#ifdef _test_linux
    const char *env = getenv("sie_test");
#else
    const char *env = getenv("LD_LIBRARY_PATH");
#endif
    if(!env || !*env) return 0;
    
    for(int i=0;; ++i)
    {
        if( !envparse(env, tmp, i) ) return 0;
        strcat(tmp, name);
        if( __is_file_exist(tmp) )
        {
            return tmp;
        }
    }
    
    /* этого никогда не будет */
    //return 0;
}



 /*
  * Открывает и парсит заданную библиотеку
  */
__arch Elf32_Lib* OpenLib(const char *name, Elf32_Exec *_ex)
{
    if(!name || !*name) return 0;
    printf("Starting loading shared library '%s'...\n", name);
    int fp, _size = 0;
    Elf32_Ehdr ehdr;
    Elf32_Exec* ex;
    char __mem[256];

    // Поищем среди уже загруженых
    Global_Queue* ready_libs = lib_top;
    
    const char *cmp_share_name = strrchr_a(name, '/');
    if(!cmp_share_name) cmp_share_name = name;
    else cmp_share_name++;
    while(ready_libs)
    {
        Elf32_Lib* lib = ready_libs->lib;

        if(!strcmp (lib->soname, cmp_share_name))
        {
            printf(" '%s' is olready loaded\n", cmp_share_name);
            lib->users_cnt++;
            //PushParent(lib->ex, _ex);
            memset(dlerr, 0, 2);
            return lib;
        }
        ready_libs = ready_libs->prev;
    }

    
    const char *ld_path = 0;
    
    /* путь у нас реальный */
    if(name[0] == '/')
      ld_path = name;
    
    else
    {
      /* есть у нас временное окружение */
      if(_ex && _ex->temp_env)
      {
	/* попробуем из него достать переменную */
	ld_path = (const char*)__mem;
	sprintf((char *)ld_path, "%s%s", _ex->temp_env, name);
	
	/* нету её... */
	if(!__is_file_exist(ld_path))
	{
	  /* ну поищим по глобальным */
	  ld_path = findShared(name);
	}
      } else
	ld_path = findShared(name);
    }
    
    /* ничего не нашли */
    if(!ld_path) return 0;
    
    
try_again:

    /* Открываем */
    if((fp = fs_open(ld_path, FILE_OPEN_READ)) < 0) {
      strcpy(dlerr, NO_FILEORDIR);
      return 0;
    }
    /* Читаем хедер */
    if( (_size = fs_read(fp, &ehdr, sizeof(Elf32_Ehdr))) <= 0) {
      strcpy(dlerr, BADFILE);
      return 0;
    }
    
    /* Проверяем шо это вообще такое */
    if( _size < sizeof(Elf32_Ehdr) || CheckElf(&ehdr) ) // не эльф? о_О мб симлинк?!
    {
      int ns = fs_seek(fp, FILE_SEEK_END, 0); // если длина файл больше 256 байт то нахрен такой путь...
      if(ns < 256 && ns > 0)
      {
        fs_seek(fp, FILE_SEEK_SET, 0);
        if(fs_read(fp, tmp, ns) != ns){
          fs_close(fp);
          return 0;
        }
        tmp[ns] = 0;
        ld_path = tmp;
        fs_close(fp);
        goto try_again;
      }
      strcpy(dlerr, BADFILE);
      fs_close(fp);
      return 0;
    }
    
    /* Выделим память под структуру эльфа */
    if( !(ex = calloc(1, sizeof(Elf32_Exec))) ) {
      strcpy(dlerr, OUTOFMEM);
      return 0;
    }
    
    memcpy_a(&ex->ehdr, &ehdr, sizeof(Elf32_Ehdr));
    ex->v_addr = (unsigned int)-1;
    ex->fp = fp;
    ex->type = EXEC_LIB;
    __ex_push_parent(ex, _ex);
    
    ex->switab = /*FIXME*/ 0;
    ex->fname  = name;
    
    const char *p = strrchr_a(name, '/');
    if(p)
    {
      ++p;
      ex->temp_env = malloc(p - name + 2);
      memcpy_a(ex->temp_env, name, p - name);
      ex->temp_env[p - name] = 0;
    } else
	ex->temp_env = 0;

    /* Начинаем копать структуру либы */
    if( LoadSections(ex) ){
        strcpy(dlerr, BADFILE);
        fs_close(fp);
        elfclose(ex);
        return 0;
    }

    /* Он уже не нужен */
    fs_close(fp);

    /* Глобальная база либ */
    Elf32_Lib* lib;
    if( !(lib = malloc(sizeof(Elf32_Lib))) ){
        elfclose(ex);
        strcpy(dlerr, OUTOFMEM);
        return 0;
    }

    lib->ex = ex;
    lib->users_cnt = 1;
    
    const char *soname;
    
    
    if(!ex->dyn[DT_SONAME]) // пустой блок с именем либы о_О
    {
      if(name[1]==':') // путь относительный
      {
        soname = strrchr_a(name, '/'); // отчекрыжим путь, берём имя
        if(!soname) // шо за бляин путь такой?! 
        {
          soname = name; // лан, пох ...
        }else
          ++soname;
      }else // путь не относительный
      {
        soname = name;
      }
    }else // все норм, имя либы есть
    {
      soname = ex->strtab + ex->dyn[DT_SONAME];
    }
    
    strcpy(lib->soname, soname?soname : "Error Lib!");

    /*  Ведь капуста^W память всем нужна)) */
    Global_Queue* global_ptr = malloc(sizeof(Global_Queue));
    if(!global_ptr)    // ?????...?? ??? :'(
    {
        strcpy(dlerr, OUTOFMEM);
        CloseLib(lib, 0);
        return 0;
    }

    /* Ну тут заполняем */
    global_ptr->lib = lib;
    global_ptr->next = 0;
    lib->glob_queue = global_ptr;

    if(lib_top)
    {
        lib_top->next = global_ptr;
        global_ptr->prev = lib_top;
    }
    else global_ptr->prev = 0;
    
    lib_top = global_ptr;

    /* запустим контсрукторы */
    executeInitializersArray(ex);
    ex->complete = 1;

    /* запустим функциюю инициализации либы, если таковая имеется */
    if(ex->dyn[DT_INIT])
    {
        printf("init function found\n");
#ifndef _test_linux
        (( void (*)(const char*) )(ex->body + ex->dyn[DT_INIT] - ex->v_addr))(name);
#endif
    }

    printf(" '%s' Load complete\n", name);
    dlerr[0] = 0;
    dlerr[1] = 0;
    ex->fname = 0;
    return lib;
}


 /*
  * Вычесть общее количество клиентов либ
  */
__arch void sub_clients(Elf32_Lib* lib)
{
  lib->users_cnt--;
}



 /*
  * Закрывает бибилотеку и освобождает ресурсы
  */
__arch int CloseLib(Elf32_Lib* lib, int immediate)
{
    if(!lib) return E_EMPTY;
    
    if(lib->users_cnt < 1) // нету больше юзеров либы :(
    {
        if(!ep_config.realtime_libclean && !immediate) goto end;
        
        Elf32_Exec* ex = lib->ex;
	executeFinishesArray(ex);
	
#ifndef _test_linux
	if(ex->dyn[DT_FINI]) ((LIB_FUNC*)(ex->body + ex->dyn[DT_FINI] - ex->v_addr))();
#endif
	
        if(lib->glob_queue)
        {
	    // Функция финализации
            Global_Queue* glob_queue = lib->glob_queue;
            //Global_Queue* tmp = glob_queue->next;
            
            Global_Queue* next = glob_queue->next;
            Global_Queue* prev = glob_queue->prev;
            
	    if(next) {
		next->prev = prev;
		if(prev)
		    prev->next = next;
	    } else {
		lib_top = prev;
		if(prev)
		    prev->next = 0;
	    }
	    
            
            /*if( glob_queue == lib_top && !lib_top->prev) lib_top = 0;
            else
            if( glob_queue == lib_top ) lib_top = glob_queue->prev;
              
            if(tmp) tmp->prev = glob_queue->prev;
            if(tmp = glob_queue->prev) tmp->next = glob_queue->next;*/
            
            free(glob_queue);
        }

        elfclose(ex);
        free(lib);
    }
end:
    return E_NO_ERROR;
}



 /*
  * POSIX-подобная dlopen
  */
__arch int dlopen(const char *name)
{
  int handle = -1;
  
  if(!name) return -1;
  
  // Первый клиент! :)
  if(!handles_cnt)
  {
    handles_cnt = 32;
    handles = malloc(sizeof(Elf32_Lib*) * handles_cnt);
    
    if(!handles) return -1;
    
    zeromem_a(handles, sizeof(Elf32_Lib*) * handles_cnt);
  }
  
  // Ищем свободный слот
  for(int i=0; i<handles_cnt; ++i)
  {
    if(handles[i] == 0)
    {
      handle = i;
      break;
    }
  }
  
  // Не нашли O_o
  if(handle == -1)
  {
    Elf32_Lib** new_handles = realloc(handles, sizeof(Elf32_Lib*) * (handles_cnt + 64));
    
    // Места нет, и рама кончилась :'(
    if(!new_handles) return -1;
    
    handle = handles_cnt;
    zeromem_a(&new_handles[handles_cnt], sizeof(Elf32_Lib*) * 64);
    handles_cnt += 64;
    handles = new_handles;
  }
  
  Elf32_Lib* lib = OpenLib(name, 0);
  if(!lib) return -1;
  
  handles[handle] = lib;
  return handle;
}



 /*
  * POSIX-подобная dlclose
  */
int dlclose(int handle)
{
  if(0 > handle > handles_cnt - 1 || !handles) return -1;
  
  if(handles[handle])
  {
    Elf32_Lib* lib = handles[handle];
    handles[handle] = 0;
    sub_clients(lib);
    return CloseLib(lib, 0);
  }
  
  return 0;
}



 /*
  * POSIX-подобная dlsym
  */
Elf32_Word dlsym(int handle, const char *name)
{
  if(0 > handle > handles_cnt - 1) return 0;
  
  if(handles && handles[handle]) return FindFunction(handles[handle], name, name_hash(name));
  
  return 0;
}



 /*
  * POSIX-подобная dlerror
  */
__arch const char *dlerror()
{
  return dlerr;
}



 /*
  * Шапка резинового массива^W^W связного списка либ
  */
__arch void *SHARED_TOP()
{
  return lib_top;
}



 /*
  * Очистка не используемых библиотек
  */
__arch int dlcache_clean()
{
  if(!lib_top) return -1;
  
  Elf32_Lib *bigger = 0;
  Global_Queue *tmp = lib_top, *prev = 0;
  int cleaned = 0;
  while(tmp)
  {
    // найдем либу которая юзает самое большое количество либ
    bigger = tmp->lib;
    prev = tmp->prev;
    
    if( bigger->users_cnt < 1 )
    {
      // закроем её, и она закроет весь хлам который сама юзает
      CloseLib(bigger, 1); // срочняком кроим их!
      ++cleaned;
      
      // если мы очистили либу, опять начинаем с топа, она могла закрыть dlopen-ом ещё одну либу
      tmp = lib_top;
      continue;
    }
    
    tmp = prev;
  }
  
  return cleaned;
}




