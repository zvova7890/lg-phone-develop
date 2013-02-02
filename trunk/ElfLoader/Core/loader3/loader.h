
/*
 * Этот файл является частью программы ElfLoader
 * Copyright (C) 2011 by Z.Vova, Ganster
 * Licence: GPLv3
 */


#ifndef __LOADER_H__
#define __LOADER_H__


#include <string.h>
#include <stdio.h>
#include "../swihook.h"
#include "../fwlib.h"
#include "../corelib.h"


#ifdef _test_linux
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

#define A_ReadOnly O_RDONLY
#define A_BIN 0
#define A_TXT O_TXT

#define mfree free

#define fopen open
#define fread read
#define fwrite write
#define fclose close

#define FILE_SEEK_SET SEEK_SET
#define FILE_SEEK_END SEEK_END
#define P_READ 0

#define zeromem_a(d, s) memset(d, 0, s)
#define zeromem(d, s) memset(d, 0, s)

#define l_msg(x, y) printf("MESSAGE: %s\n", (char*)y);
#define __e_div(a, b) (b % a)

#else

//typedef unsigned int size_t;

void *malloc(size_t size);
void free(void *ptr);
void *realloc(void *ptr, size_t size);
void *calloc(size_t n, size_t s);

#endif

#include "elf.h"
#include "mode.h"

static const unsigned char elf_magic_header[] =
{
  0x7f, 0x45, 0x4c, 0x46,  /* 0x7f, 'E', 'L', 'F' */
  0x01,                    /* Only 32-bit objects. */
  0x01,                    /* Only LSB data. */
  0x01,                    /* Only ELF version 1. */
};

#ifndef _test_linux
  //#define printf __core_lprintf
  #define printf(...)
#ifdef __thumb_mode 
  #define __arch __thumb
#else
  #define __arch __arm
#endif /*__thumb_mode*/
#else
  #define __arch 
#endif /* _test_linux */

#define NO_FILEORDIR	"no such file or directory"
#define BADFILE		"bad file type"
#define OUTOFMEM	"out of memory"

enum ERROR{

    E_NO_ERROR = 0x0,
    E_RELOCATION,
    E_READ,
    E_SHARED,
    E_HEADER,
    E_SECTION,
    E_RAM,
    E_EMPTY,
    E_FILE,
    E_MACHINE,
    E_ALIGN,
    E_UNDEF,
    E_SYMTAB,
    E_STRTAB,
    E_PHDR,
    E_HASTAB
};

typedef struct
{
  void *lib;
  void *next;
  void *prev;
} Global_Queue;

typedef struct
{
  void *lib;
  void *next;
} Libs_Queue;

typedef enum elf32_type
{
  EXEC_NONE,
  EXEC_ELF,
  EXEC_LIB,
} Elf32_Type;

typedef struct
{
  char* body;
  unsigned int bin_size;
  Elf32_Ehdr ehdr;
  unsigned int v_addr;
  Elf32_Type type;
  Elf32_Word dyn[DT_FLAGS+1];
  Elf32_Sym* symtab;
  Elf32_Rel* jmprel;
  Elf32_Word* hashtab;
  char* strtab;
  Libs_Queue* libs;
  int fp;
  char complete, __is_ex_imported;
  
  struct {
    Libs_Queue *ex;	//Elf32_Exec
  }parents;
  
  int *switab;
  const char *fname;	// не постоянная переменная, после загрузки эльфа она обнулится
  char *temp_env;	// временное переменное окружение для эльфа
} Elf32_Exec;

typedef struct
{
  char soname[64];
  Elf32_Exec* ex;
  int users_cnt;
  void *glob_queue;
} Elf32_Lib;


typedef struct {
  int realtime_libclean;
  int loader_warnings;
  char LD_LIBRARY_PATH_env[512];
}ep_config_t;

extern ep_config_t ep_config;



typedef int ELF_ENTRY(const char *, void *);
typedef int LIB_FUNC();

extern unsigned int ferr;

#ifndef _test_linux
 #ifdef ARM
 #define zeromem_a(a,b) zeromem(a,b)
 #define l_msg(a,b) ShowMSG(a,b)
 #else
 void zeromem_a(void *d, int l);
 void l_msg(int a, int b);
 #endif
#endif
 
extern char tmp[258];
void ep_log(Elf32_Exec *ex, const char *data, int size);

#define lprintf(...) { int __dsz = snprintf(tmp, 256, __VA_ARGS__);\
      ep_log(ex, tmp, __dsz); }
      

int CheckElf(Elf32_Ehdr *ehdr);
unsigned int calc_binary_size(Elf32_Exec *ex, Elf32_Phdr* phdrs);
int LoadSections(Elf32_Exec* ex);
int DoRelocation(Elf32_Exec* ex, Elf32_Dyn* dyn_sect, Elf32_Phdr* phdr);
__arch unsigned long name_hash(const char* name);
Elf32_Word findExport(Elf32_Exec* ex, const char* name, unsigned long hash);
Elf32_Word FindFunction(Elf32_Lib* lib, const char* name, unsigned long hash);

/* shared support */
Elf32_Lib* OpenLib(const char *name, Elf32_Exec *ex);
int CloseLib(Elf32_Lib* lib, int immediate);
int dlopen(const char *name);
int dlclose(int handle);
Elf32_Word dlsym(int handle, const char *name);
__arch const char *dlerror();
__arch int dlcache_clean();
__arch void *SHARED_TOP();


/* executable support */
Elf32_Exec* elfopen(const char* filenam);
int elfclose(Elf32_Exec* ex);
void *elf_entry(Elf32_Exec *);
__arch void sub_clients(Elf32_Lib* lib);

/* init/fini arrays support */
void executeInitializersArray(Elf32_Exec *ex);
void executeFinishesArray(Elf32_Exec *ex);

void __elf_init();
int __elf_load(const char *elfname, int argc, char *argv[], unsigned int *start, unsigned int *ret);
void __elf_unload(void *base);

#endif
