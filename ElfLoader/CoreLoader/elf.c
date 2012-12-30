#include <string.h>
#include "fwlib.h"
#include "elf.h"


__thumb long elfload(char *filename, void *param1, void *param2, void *param3)
{
  Elf32_Ehdr ehdr;			// Заголовок эльфа
  Elf32_Phdr phdrs[MAX_PHNUM];	        // Заголовки програм
  Elf32_Word dyn[DT_BIND_NOW+1];	// Тэги динамической секции
  
  char *reloc, *base;
  unsigned long minadr=(unsigned long)-1, maxadr=0;
  int n,m;
  
  memset(dyn, 0, sizeof(dyn));
    
  int fin;
  if ((fin=fw.open(filename, FILE_OPEN_MODE_READ))<0) return -1; // Не открывается эльф
  if (fw.read(fin, &ehdr, sizeof(Elf32_Ehdr))!=sizeof(Elf32_Ehdr))    // Не читается эльф
  {
    fw.close(fin); 
    return -2;
  }
  
  
  if (*((long *)ehdr.e_ident) != 0x464C457F) // Да и не эльф это вовсе /* \x7FELF */
  {                               
    fw.close(fin);
    return -3;
  }
  
  // Прочитаем все программные сегменты и вычислим необходимую область в RAM
  if (ehdr.e_phnum > MAX_PHNUM) return -9; // Слишком много програмных сегментов
  for(n = 0; n < ehdr.e_phnum; n++)
  {
    if (fw.seek(fin, FILE_SEEK_MODE_SET, ehdr.e_phoff+n*ehdr.e_phentsize))
     {
       fw.close(fin); 
       return -4;
     }	// Не найден программный заголовок
    if (fw.read(fin, &phdrs[n], sizeof(Elf32_Phdr))!=sizeof(Elf32_Phdr))
    {
      fw.close(fin); 
      return -5;
    }  // Не читается программный заголовок
    
    if (phdrs[n].p_type==PT_LOAD)
    {
      if (minadr > phdrs[n].p_vaddr) minadr=phdrs[n].p_vaddr;
      if (maxadr < (phdrs[n].p_vaddr+phdrs[n].p_memsz))
      {
	maxadr=phdrs[n].p_vaddr+phdrs[n].p_memsz;
      }
    }
  }
  
  // Выделим эту область и очистим ее
  if ((base=(char *)fw.malloc(maxadr-minadr))==0) // Не выделяется память под эльф (Нехватка свободной RAM)
  {
    fw.close(fin);
    return -13;
  }
  
  // Обнуление выделенной области
  memset(base, 0, maxadr-minadr);
  
  // Обход всех сегментов
  for(n=0; n < ehdr.e_phnum; n++)
  { 
    if (fw.seek(fin, FILE_SEEK_MODE_SET, phdrs[n].p_offset))
    {
      fw.close(fin);
      fw.free(base); 
      return -6;
    } // Не найден динамический сегмент

    switch (phdrs[n].p_type)
    {
     case PT_LOAD:
       
      // Загрузим программные сегменты с размером больше 0
      if (phdrs[n].p_filesz!=0) 
       {
	if (fw.read(fin, &base[phdrs[n].p_vaddr-minadr], phdrs[n].p_filesz)!= phdrs[n].p_filesz)
        {
          fw.close(fin); 
          fw.free(base); 
          return -10;
        } // Не читается программный сегмент
       }
        break;
     case PT_DYNAMIC:
       
      // Прочтем динамическую секцию
      if ((reloc=(char *)fw.malloc(phdrs[n].p_filesz))==0) // Не выделяется память под динамический сегмент
      {
	fw.close(fin);
	fw.free(base);
	return -7;
      }
      
      if (fw.read(fin, reloc, phdrs[n].p_filesz)!=phdrs[n].p_filesz)
      {
        fw.close(fin); 
        fw.free(reloc); 
        fw.free(base); 
        return -8;
      }	// Не читается динамический сегмент

      // Вытащим все тэги из динамической секции
      m=0;
      while (((Elf32_Dyn *)reloc)[m].d_tag!=DT_NULL)
       {
	if (((Elf32_Dyn *)reloc)[m].d_tag<=DT_BIND_NOW) 
        {
	  dyn[((Elf32_Dyn *)reloc)[m].d_tag]=((Elf32_Dyn *)reloc)[m].d_val;
	}
	m++;
       }
      m=0;
      
      // Выполним релокацию REL
      if (dyn[DT_RELSZ]!=0)
       {
	while (m*sizeof(Elf32_Rel)<dyn[DT_RELSZ])
         {

          Elf32_Word ri=ELF32_R_TYPE(((Elf32_Rel *)(reloc+dyn[DT_REL]-phdrs[n].p_vaddr))[m].r_info);
          if (ri!=R_ARM_RBASE)
          {
            if (ri==R_ARM_RABS32)
            {
              *((long*)(base+((Elf32_Rel *)(reloc+dyn[DT_REL]-phdrs[n].p_vaddr))[m].r_offset))+=(long)base-minadr;
            }
            else
              switch(ri)
               {
                case R_ARM_NONE: break; // Пустой релокейшен
                case R_ARM_ABS32:

                *((long*)(base+((Elf32_Rel *)(reloc+dyn[DT_REL]-phdrs[n].p_vaddr))[m].r_offset-minadr))+=(long)base;
                break;
                
                case R_ARM_RELATIVE: // Вообще говоря не minadr а начало сегмента содержащего символ
                  
                *((long*)(base+((Elf32_Rel *)(reloc+dyn[DT_REL]-phdrs[n].p_vaddr))[m].r_offset-minadr))+=(long)base-minadr;
                break;  // Игнорируем
                case R_ARM_RBASE: break;
                
                default: 	// Неизвестный тип релокации
                  fw.close(fin);
                  fw.free(base);
                  fw.free(reloc);
                  return -12;
               }
           }
	  m++;
	 }
       }

       fw.free(reloc);
       break;
      
      default:	// Неизвестный тип програмного сегмента
       fw.close(fin);
       fw.free(base);
       return -11;
    }
  }

  fw.close(fin);
  {
    //extern __arm void ExecuteIMB(void);
    //ExecuteIMB();	
  }
  ((TElfEntry *)(base+ehdr.e_entry-minadr))(filename,param1,param2,param3);
  return 0;
}
