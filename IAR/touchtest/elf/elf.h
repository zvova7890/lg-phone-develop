#ifndef __ELF_H__
#define __ELF_H__

#define TASKAPI_EXTERN
#define PXO_DONOR_PATH L"LGAPP/Pxo/donor.pxo"

#include "../../inc/corelib.h"
#include "../../inc/pxeapi.h"
#include "../../inc/taskapi.h"

#include "unicode.h"

//Запрет на другие экземпляры приложения
//#define ELF_APP_ONECOPY
#define ELF_APP_LOG

#ifdef ELF_APP_LOG
#define printf __elf_printf
#define clear  __elf_clear
#else
#define printf(...)
#define clear(...)
#endif // ELF_APP_LOG

#define app_handle __elf_app_handle

extern int   __elf_app_handle;
extern char  __elf_logfile[];
extern char  __elf_file[];
extern char  __elf_folder[];
extern void *__elf_base;

void __elf_clear();
void __elf_printf(const char *format, ...);

void __elf_init(const char *elf_fname);
int  __elf_start(const char *elf, int argc, char *argv[]);

int elf_run(int event_id, int wparam, int lparam);

#endif // __ELF_H__

