#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>


#include "../inc/corelib.h"
#include "../inc/pxeapi.h"
#include "../inc/taskapi.h"



#pragma segment="ELF"
const char __elf_build[] = "ElfApp, builded "__TIME__" "__DATE__;
#define __elf_base (void *)__segment_begin("ELF")


unsigned char p[0x100000];

int main(int argc, char *argv[])
{
 p[555] = 0;
 
 lprintf("---------- Test ------------- \r\n");
 __exekiller_run(__elf_base);
 
 lprintf("---------- Test OK ------------- \r\n");
 
 //TaskMngr_ShowTaskList();
 
 return 1;
}


