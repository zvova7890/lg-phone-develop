
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "elf.h"

#pragma segment="ELF"
const char __elf_build[] = "ElfApp, builded "__TIME__" "__DATE__;
#define __elf_start_address (void *)__segment_begin("ELF")

ELF_PARASITE_INFO __elf_app_ei;
int               __elf_app_handle = 0;
const unsigned short __task_api_name_extern[]=TASKAPI_NAME;


char  __elf_logfile[256];
char  __elf_file[256];
char  __elf_folder[256];
void *__elf_base = 0;

char  __elf_logbuf[512]; 


void __elf_clear()
{
  fs_unlink(__elf_logfile);
}

void __elf_printf(const char *format, ...)
{
  if (!format) return;
  
  va_list arg_ptr;
  va_start(arg_ptr, format);
  vsprintf(__elf_logbuf, format, arg_ptr);
  va_end(arg_ptr);
  
  int l = fs_open(__elf_logfile, FILE_OPEN_CREATE | FILE_OPEN_WRITE | FILE_OPEN_APPEND);
  if (l > 0)
   {
    fs_write(l, __elf_logbuf, strlen(__elf_logbuf));
    fs_close(l); 
   }  
}

void __elf_init(const char *elf_fname)
{
 int lenf, leno;
 char __elf_log[]="%s.log";
 
 lenf = strlen(elf_fname);
 leno = strlen(strrchr(elf_fname, '/')+1);
 memcpy(__elf_folder, elf_fname, lenf-leno);
 __elf_folder[lenf-leno] = '\0';
 
 strcpy(__elf_file, elf_fname); 
 sprintf(__elf_logfile, __elf_log, __elf_file); 

 __elf_base = __elf_start_address;
 __elf_clear();
}

 

int __elf_start(const char *elf, int argc, char *argv[])
{
#ifndef ELF_APP_ONECOPY
 char __elf_08X[]="%08X.pxo";
#else
 char __elf_s[]="%s";
#endif
  
 //Первичная инициализация
 __elf_init(elf);

 //Заполняем информацию для PXE - донора
 extern int elf_run(int, int, int);
 __elf_app_ei.evt_handler = elf_run;
 __elf_app_ei.base = __elf_start_address;
   
 //Загружаем PXE донор
 int __elf_app_handle = TaskMngr_AppRun(PXO_DONOR_PATH, (int)&__elf_app_ei);
 //Подменям имя файла, чтобы обеспечить загрузку других приложений
 if (__elf_app_handle)
  {
   char app_addr[32];
   APP *app = (APP *)__elf_app_handle;
#ifndef ELF_APP_ONECOPY
   sprintf(app_addr, __elf_08X, app);
#else
   snprintf(app_addr, 32, __elf_s, strrchr(__elf_file, '/')+1);
#endif
   cp1251_2_utf16(app->fname, app_addr);
   
   //Регистрируем приложение в Диспетчере задач
   TaskMngr_AppRegister(__elf_app_handle);
 
   __elf_printf("Elf App Start \"%s\" - AppHandle = 0x%08X\r\n", elf, __elf_app_handle);
  } else __elf_printf("Elf App Start \"%s\" - error\r\n", elf);

 return 0;
}

