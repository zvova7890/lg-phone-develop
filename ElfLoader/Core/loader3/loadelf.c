
/*
 * Этот файл является частью программы ElfLoader
 * Copyright (C) 2011 by Z.Vova, Ganster
 * Licence: GPLv3
 */

#include <string.h>
#include "loader.h"
#include "../gc.h"


#ifdef __thumb_mode
extern __arm void *memcpy_a (void *dest, const void *src, size_t size);
extern __arm char * strrchr_a (const char *s, int c);

#else
#define memcpy_a memcpy
#define strrchr_a strrchr
#endif



// Загрузка эльфа
__arch Elf32_Exec* elfopen(const char* filename)
{
  int fp;
  Elf32_Ehdr ehdr;
  Elf32_Exec* ex = 0;

  if( (fp = fs_open(filename, FILE_OPEN_READ) ) < 1)
    return 0;
  

  if( fs_read(fp, &ehdr, sizeof(Elf32_Ehdr)) == sizeof(Elf32_Ehdr) )
  {
    if( !CheckElf(&ehdr) )
    {
      ex = calloc(1, sizeof(Elf32_Exec));
      if(ex)
      {
        memcpy_a(&ex->ehdr, &ehdr, sizeof(Elf32_Ehdr));
        ex->v_addr = (unsigned int)-1;
        ex->fp = fp;
        ex->type = EXEC_ELF;

        // FIXME
        ex->switab = /*(int*)AddrLibrary_a()*/0;
	ex->fname = filename;
	
	const char *p = strrchr_a(filename, '/'); 
	if(p)
	{
          ++p;
	  ex->temp_env = malloc(p - filename + 2);
	  if(ex->temp_env) {
	      memcpy_a(ex->temp_env, filename, p - filename);
	      ex->temp_env[p - filename] = 0;
	  } else {
	      lprintf("temp_env: No memory available\n");
	  }
	  
	} else
	  ex->temp_env = 0;
	  
	
	
        if(!LoadSections(ex))
        {
          ex->complete = 1;
          fs_close(fp);
	  ex->fname = 0;
          return ex;
        }
        else 
          elfclose(ex);
      } else  {
	  lprintf("Elf32_Exec: No memory available\n");
      }
    }
  }

  fs_close(fp);
  return 0;
}


__arch void *elf_entry(Elf32_Exec *ex)
{
    if(!ex) return 0;
    return ( ex->body + ex->ehdr.e_entry - ex->v_addr );
}


__arch int elfclose(Elf32_Exec* ex)
{
  if(!ex) return E_EMPTY;

  /* CHECKME */
  /* Инициализаторы и финализаторы мы пускаем в эльфе */
  //if(ex->complete)
    //executeFinishesArray(ex);

  // Закрываем либы
  while(ex->libs)
  {
    Libs_Queue* lib = ex->libs;
    sub_clients(lib->lib);
    CloseLib(lib->lib, 0);
    ex->libs = lib->next;
    free(lib);
  }

  if(ex->hashtab) free(ex->hashtab);
  if(ex->temp_env) free(ex->temp_env);
  
  for(Libs_Queue *l = ex->parents.ex, *li; l; ) {
      li = l;
      l = l->next;
      free(li);
  }


  if(ex->body) __gc_cleanup(ex->body, 2);
  free(ex);  
  return E_NO_ERROR;
}

