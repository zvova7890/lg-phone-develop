
#include <stdio.h>
#include <string.h>

#include "intrinsics.h"
#include "swihook.h"
#include "ejapi.h"
#include "loader3/loader.h"

#include "core.h"


const char ejapi_head[]      = EJAPI_HEAD;
const char ejapi_avail[]     = EJAPI_AVAIL;
const char ejapi_open[]      = EJAPI_OPEN;
const char ejapi_close[]     = EJAPI_CLOSE;
const char ejapi_run[]       = EJAPI_RUN;
const char ejapi_ver[]       = EJAPI_VER;

const char ejapi_true[]      = EJAPI_TRUE;
const char ejapi_percd[]     = EJAPI_PERCD;
const char ejapi_perss[]     = EJAPI_PERSS;

char __ejapi_build[] = "1.1";
char __ejapi_handle_string[256];
char __ejapi_folder[260];

EJAPI_ITEM ejapi_base[EJAPI_BASE_SIZE];


__arm char *__ejapi_handler(char *key)
{
 if (!memcmp(key, ejapi_head, EJAPI_PREFIX_LEN))
  {
   if (!strcmp(key, ejapi_avail))
    return (char *)ejapi_true;
   else
   if (!strcmp(key, ejapi_ver))
    return (char *)__ejapi_build;
   else
   if (!memcmp(key, ejapi_open, EJAPI_OPEN_LEN))
    {
     char *n = key + EJAPI_OPEN_LEN;
     int handle = 0;
     if ((handle = __ejapi_addapi(n)) != EJAPI_ERROR)
      {
       sprintf(__ejapi_handle_string, ejapi_percd, handle);
       return __ejapi_handle_string;
      } else return EJAPI_NULL;
    }
   else
   if (!memcmp(key, ejapi_close, EJAPI_CLOSE_LEN))
    {
     char *n = key + EJAPI_CLOSE_LEN;
     int handle = 0;
     sscanf(n, ejapi_percd, &handle);
     
     if (__ejapi_removeapi(handle) == EJAPI_SUCCESS)
       return (char *)ejapi_true;
     else return EJAPI_NULL;
    } else 
   if (!memcmp(key, ejapi_run, EJAPI_RUN_LEN))
    {
     char *n = key + EJAPI_RUN_LEN;
     char *k = key + EJAPI_RUN_LEN;
     int nn = 0;
     int handle = 0;
     while (n[nn] != '.')
      {
       if (n[nn] == '\0') 
         return EJAPI_NULL; 
       nn++;
      }
     n[nn] = '\0';
     k += (nn + 1);
     sscanf(n, ejapi_percd, &handle);
     
     if ((handle >= EJAPI_HANDLE) && (handle < (EJAPI_HANDLE + EJAPI_BASE_SIZE)))
      {
       if (ejapi_base[handle - EJAPI_HANDLE].handler)
         return ejapi_base[handle - EJAPI_HANDLE].handler(k);
       else return EJAPI_NULL;
      } else return EJAPI_NULL;
    } else return EJAPI_NULL;
  } else return EJAPI_NULL;
}

void __ejapi_init(char *ejapi_folder)
{
 void *ejapi_hook_address = (void *)EJAPI_HOOK_ADDRESS;
 
 for (int i = 0; i < EJAPI_BASE_SIZE; i++)
  {
   ejapi_base[i].handler = EJAPI_NULL;
   ejapi_base[i].base = EJAPI_NULL;
  }
 
 strcpy(__ejapi_folder, ejapi_folder);
 
 __disable_interrupt();
 int doms =  __MRC(15, 0, 3, 0, 0);
 __MCR(15, 0, 0xFFFFFFFF, 3, 0, 0);
   
 memcpy(ejapi_hook_address, (void *)((int)&__ejapi_patch - 1), EJAPI_HOOK_SIZE);
            
 __MCR(15, 0, doms, 3, 0, 0);
 
 __swihook_setfunc(SWINUM_EJAPIADD, (int)__ejapi_addapi);
 __swihook_setfunc(SWINUM_EJAPIREM, (int)__ejapi_removeapi);
 __swihook_setfunc(SWINUM_EJAPIGET, (int)__ejapi_getbase);
 __swihook_setfunc(SWINUM_EJAPIGSZ, (int)__ejapi_getbasesize);
 __enable_interrupt();
}

int __ejapi_addapi(char *path)
{  
 unsigned int ebase = 0;
 unsigned int ehandler = 0;
 char ejp[260];
 
 
 if (!path) return EJAPI_ERROR; 
  
 if (path[0] == '/')
   strcpy(ejp, path);
 else
   sprintf(ejp, ejapi_perss, __ejapi_folder, path);
 
 char *argv[2] = {ejp, 0};
 if (!__elf_load(ejp, 1, argv, &ebase, &ehandler))
  {
   if (!ebase) return EJAPI_ERROR; 
   if (!ehandler) return EJAPI_ERROR; 
  } else return EJAPI_ERROR; 
 
  for (int i = 0; i < EJAPI_BASE_SIZE; i++)
   {
    if (ejapi_base[i].handler == EJAPI_NULL)
     {
      ejapi_base[i].handler = (char *(*)(char *))ehandler;
      ejapi_base[i].base = (void *)ebase;
      __core_lprintf("*** EJAPI: handle = %d,  %s load\r\n", EJAPI_HANDLE + i, ejp);
      return EJAPI_HANDLE + i;
     }
   }
 
  return EJAPI_ERROR; 
}

int __ejapi_removeapi(int handle)
{
 if ((handle >= EJAPI_HANDLE) && (handle < (EJAPI_HANDLE + EJAPI_BASE_SIZE)))
 {
  ejapi_base[handle - EJAPI_HANDLE].handler = EJAPI_NULL;
  __elf_unload(ejapi_base[handle - EJAPI_HANDLE].base);
  ejapi_base[handle - EJAPI_HANDLE].base = EJAPI_NULL;
  __core_lprintf("*** EJAPI: handle = %d, unload\r\n", handle);
  return EJAPI_SUCCESS;
 }
 return EJAPI_NULL;
}


EJAPI_ITEM *__ejapi_getbase()
{
 return (EJAPI_ITEM *)&ejapi_base;
}

int __ejapi_getbasesize()
{
 return EJAPI_BASE_SIZE;
}

