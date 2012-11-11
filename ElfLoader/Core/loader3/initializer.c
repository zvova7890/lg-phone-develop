
#include <stdio.h>
#include <stdarg.h>
#include <intrinsics.h>

#include "loader.h"
#include "env.h"
#include "../swihook.h"
#include "../fwlib.h"



#define SWINUM_ELFLOAD   0x0B
#define SWINUM_ELFUNLOAD 0x0C

ep_config_t ep_config;

__arm int setenv(const char *name, const char *value, int replace);


void *malloc(size_t size) {
  return mem_malloc(size);
}


void free(void *ptr) {
  mem_free(ptr);
}


void *realloc(void *ptr, size_t size) {
  return mem_realloc(ptr, size);
}


void *calloc(size_t n, size_t s){
  //return mem_calloc(n, s);
  void *adr = malloc(n*s);
  memset(adr, 0, n*s);
  return adr;
}


/*
int e_handle;
char data[128];

void echo(const char *fmt, ...)
{
  va_list va;
  
  va_start(va, fmt);
  int sz = vsprintf(data, fmt, va);
  va_end(va);
  
  fs_write(e_handle, data, sz);
}
*/


int __elf_load(char *filename, void *param1, void *param2, void *param3, unsigned int *start, unsigned int *ret)
{
  Elf32_Exec *ex = elfopen(filename);
  if(!ex){
    l_msg(1, (int)"Elf corrupt or missing");
    return -1;
  }
  
  int (*entry)(const char *, void *, void*, void*) = (int (*)(const char *, void *, void*, void*))elf_entry(ex);
  if(!entry){
   l_msg(1, (int)"Entry point not found");
   elfclose(ex);
   return -2;
  }
  
    
  if(!ex->__is_ex_imported && ex->libs)
  {
    l_msg(1, (int)"Incorrect elf");
    
    char dbg[256];
    int csz = sprintf(dbg, "Warning: If you wont to use the shared libraries, you must add to linker option '--defsym __ex=0' and use elfclose function!\n");
    ep_log(ex, dbg, csz);
  }
  
  extern __arm void ExecuteIMB(void);
  ExecuteIMB();

  int r = entry(filename, ex->body, param1, param2);
  if (start) *start = (unsigned int)ex->body;
  if (ret) *ret = (unsigned int)r;

  if(!ex->__is_ex_imported && !ex->libs)
  {
    ex->body = 0;
    elfclose(ex);
  }
  
  
  return 0;
}



void __elf_unload(void *base)
{
 if (base)
   fwlib->free(base);
}


void __elf_init()
{
  ep_config.loader_warnings = 1;
  ep_config.realtime_libclean = 0;
  
  __disable_interrupt();
  __swihook_setfunc(SWINUM_ELFLOAD, (int)__elf_load);
  __swihook_setfunc(SWINUM_ELFUNLOAD, (int)__elf_unload);
  
  //0x80
  __swihook_setfunc(0x80 + 0, (int)dlopen);
  __swihook_setfunc(0x80 + 1, (int)dlsym);
  __swihook_setfunc(0x80 + 2, (int)dlclose);
  __swihook_setfunc(0x80 + 3, (int)dlerror);
  __swihook_setfunc(0x80 + 4, (int)dlcache_clean);
  __swihook_setfunc(0x80 + 5, (int)SHARED_TOP);
  
  __swihook_setfunc(0x80 + 6, (int)setenv);
  __swihook_setfunc(0x80 + 7, (int)unsetenv);
  __swihook_setfunc(0x80 + 8, (int)clearenv);
  __swihook_setfunc(0x80 + 9, (int)environ);
  
  
  __swihook_setfunc(0x80 + 10, (int)elfopen);
  __swihook_setfunc(0x80 + 11, (int)elfclose);
  __swihook_setfunc(0x80 + 12, (int)calc_binary_size);
  __swihook_setfunc(0x80 + 13, (int)LoadSections);
  __swihook_setfunc(0x80 + 14, (int)DoRelocation);
  __enable_interrupt();
  
  
  //if(!*(ep_config.LD_LIBRARY_PATH_env)){
    strncpy(ep_config.LD_LIBRARY_PATH_env, "/usr/ZBin/lib/;/mmc/ZBin/lib/;", sizeof(ep_config.LD_LIBRARY_PATH_env));
  //}
  
  setenv("LD_LIBRARY_PATH", ep_config.LD_LIBRARY_PATH_env, 1);
}

