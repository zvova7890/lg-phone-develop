
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
void loadlib_init();
void env_init();


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


int __elf_load(const char *elfname, int argc, char *argv[], unsigned int *start, unsigned int *ret)
{
  /* открываем эльф */
  Elf32_Exec *ex = elfopen(elfname);
  int r;
  
  if(!ex) {
    l_msg(1, (int)"Elf corrupt or missing");
    return -1;
  }
  
  /* достаём ентрик */
  int (*entry)(int, char **) = (int (*)(int, char **))elf_entry(ex);
  if(!entry){
   l_msg(1, (int)"Entry point not found");
   elfclose(ex);
   return -2;
  }
  
  /* различие эльф с импортом __ex и обычным(на подобе иаровского, который не поддерживает импорты) */
  if(!ex->__is_ex_imported && ex->libs)
  {
    l_msg(1, (int)"Incorrect elf");
    
    char dbg[256];
    int csz = sprintf(dbg, "Warning: If you wont to use the shared libraries, you must add to linker option '--defsym __ex=0' and use elfclose function!\n");
    ep_log(ex, dbg, csz);
    elfclose(ex);
    return -1;
  }
  
  /* Требуха с кешем */
  extern __arm void ExecuteIMB(void);
  ExecuteIMB();

  /* проверим что нам подсунули в argv */
  if(!argv || argc < 1) {
    
    /* пустой, значит сделаем стандартный */
    char *_argv[2] = {(char *)elfname, 0};
    r = entry(1, _argv);
    
  } else {
    
    /* не пустой, но путь отсутствует, зделаем стандартный */
    if(!argv[0]) {
      argv[0] = (char *)elfname;
    }
    
    r = entry(argc, argv);
  }

  if (start) *start = (unsigned int)ex->body;
  if (ret) *ret = (unsigned int)r;

  /* эльф без импорта и либ, значит в услугах эльфпака он не нуждается, удалим его из базы... */
  if(!ex->__is_ex_imported && !ex->libs) {
    
    /* ... при этом запрещая удаление тела эльфа */
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
    env_init();
    loadlib_init();
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
    
    __swihook_setfunc(0x80 + 6, (int)getenv);
    __swihook_setfunc(0x80 + 7, (int)setenv);
    __swihook_setfunc(0x80 + 8, (int)unsetenv);
    __swihook_setfunc(0x80 + 9, (int)clearenv);
    __swihook_setfunc(0x80 + 10, (int)environ);
    
    
    __swihook_setfunc(0x80 + 11, (int)elfopen);
    __swihook_setfunc(0x80 + 12, (int)elfclose);
    __swihook_setfunc(0x80 + 13, (int)calc_binary_size);
    __swihook_setfunc(0x80 + 14, (int)LoadSections);
    __swihook_setfunc(0x80 + 15, (int)DoRelocation);
    __enable_interrupt();
    
    
    strncpy(ep_config.LD_LIBRARY_PATH_env, "/usr/ZBin/lib/;/mmc/ZBin/lib/;", sizeof(ep_config.LD_LIBRARY_PATH_env));
    setenv("LD_LIBRARY_PATH", ep_config.LD_LIBRARY_PATH_env, 1);
}

