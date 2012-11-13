#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>


#include "fwlib.h"
#include "core.h"


#pragma segment="CORESTART"
const char __core_build[] = "Core v1.4, builded "__TIME__" "__DATE__;
const char __core_ss[]="%s%s";

extern void init();


FWLIB *fwlib = 0;
char  __core_logfile[256];
char  __core_libfile[256];
char  __core_file[256];
char  __core_folder[256];
char  __core_comfolder[256];
char  __core_logbuf[512]; 
void *__core_base = 0;


const char *__core_getelffile()
{
 return __core_file;
}

const char *__core_getlibfile()
{
 return __core_libfile;
}


const char *__core_getfolder()
{
 return __core_folder;
}

const char *__core_getcomfolder()
{
 return __core_comfolder;
}

const char *__core_getversion()
{
 return __core_build;
}

const void *__core_getbase()
{
 return __core_base;
}


void __core_lclear()
{
 if (fwlib)
  if (fwlib->unlink)
   fwlib->unlink(__core_logfile);
}

void __core_lprintf(const char *format, ...)
{
  if (!format) return;
  if (!fwlib) return;
  
  va_list arg_ptr;
  va_start(arg_ptr, format);
  vsprintf(__core_logbuf, format, arg_ptr);
  va_end(arg_ptr);
  
  int l = fwlib->open(__core_logfile, FILE_OPEN_CREATE | FILE_OPEN_WRITE | FILE_OPEN_APPEND);
  if (l > 0)
   {
    fwlib->write(l, __core_logbuf, strlen(__core_logbuf));
    fwlib->close(l); 
   }  
}

void __core_start(char *core_fname, FWLIB *fw)
{
 int lenf, leno;
 
 lenf = strlen(core_fname);
 leno = strlen(strrchr(core_fname, '/')+1);
 memcpy(__core_folder, core_fname, lenf-leno);
 __core_folder[lenf-leno] = '\0';
 strcpy(__core_comfolder, __core_folder); 
 
 lenf = strlen(__core_comfolder) - 1;
 __core_comfolder[lenf] = '\0';
 
 lenf = strlen(__core_comfolder);
 leno = strlen(strrchr(__core_comfolder, '/')+1);
 __core_comfolder[lenf-leno] = '\0';
 
 strcpy(__core_file, core_fname); 
 sprintf(__core_logfile, __core_ss, __core_folder, CORE_LOG); 
 sprintf(__core_libfile, __core_ss, __core_folder, CORE_LIB); 
 
 fwlib = fw;
 __core_base = (void *)__segment_begin("CORESTART");
 
 init();
}

