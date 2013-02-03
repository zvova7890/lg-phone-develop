
/*
 * Этот файл является частью программы ElfLoader
 * Copyright (C) 2011 by Z.Vova, Ganster
 * Licence: GPLv3
 */


#ifndef __LOADER_H__
#define __LOADER_H__

#include "swihelper.h"
#include "elf.h"

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




#ifdef __cplusplus
extern "C" {
#endif

__inl
int execelf(const char *elfname, int argc, char *argv[], unsigned int *start, unsigned int *ret)
__def( 0x0B, int, elfname, argc, argv, start, ret)

void ElfDestroy();

__inl
Elf32_Exec *elfopen(const char *elf)
__def( 0x80 + 11, Elf32_Exec *, elf)

__inl
int elfclose(void *ex)
__def( 0x80 + 12, int, ex)


__inl
int loader_dlopen(const char *name)
__def( 0x80 + 0, int, name)

__inl
void *loader_dlsym(int handle, const char *name)
__def( 0x80 + 1, void *, handle, name)

__inl
int loader_dlclose(int handle)
__def( 0x80 + 2, int, handle)

__inl
const char *loader_dlerror()
__def( 0x80 + 3, const char *)

__inl
int dlcache_clean()
__def( 0x80 + 4, int)

__inl
void *SHARED_TOP()
__def( 0x80 + 5, void *)


__inl
char * loader_getenv(const char *var)
__def( 0x80 + 6, char *, var)

__inl
int loader_setenv(const char *name, const char *value, int replace)
__def( 0x80 + 7, int, name, value, replace)

__inl
int loader_unsetenv(const char *name)
__def( 0x80 + 8, int, name)

__inl
int loader_clearenv(void)
__def( 0x80 + 9, int)

__inl
char ** loader_environ()
__def( 0x80 + 10, char **)

#ifdef __cplusplus
}
#endif

#endif
