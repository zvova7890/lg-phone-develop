#include <string.h>
#include <stdio.h>
#include <intrinsics.h>

#include "corelib.h"

#include "fwlib.h"
#include "core.h"

#include "swihook.h"
#include "pxeapi.h"
#include "mirfs.h"
#include "gc.h"
#include "loader3/loader.h"


char s_corestart[]="*** core.elf start\r\n";
char s_coreeend[]="*** core.elf error end\r\n";
char s_coresend[]="*** core.elf success end\r\n";

char s_rn[]="\r\n";
char s_ss[]="%s%s";
char s_s_s[]="%s/%s";

char folder_daemons[256];
char folder_patches[256];
char folder_mirfs[256];

char f_daemons[] = "daemons";
char f_patches[] = "patches";
char f_mirfs[]   = "mirfs";

#define PMB8877_KPD_MATRIX0 *( ( unsigned int *)( 0xF4D00018 ) )
#define PMB8877_KPD_MATRIX1 *( ( unsigned int *)( 0xF4D0001C ) )
#define PMB8877_KPD_MATRIX2 *( ( unsigned int *)( 0xF4D00020 ) )
#define SUCCESS_STAMP_FILE "/usr/Others/elfloader.donotdelete"



void stamp(const char *text)
{
    int h = fwlib->open(SUCCESS_STAMP_FILE, FILE_OPEN_CREATE | FILE_OPEN_TRUNCATE | FILE_OPEN_WRITE);
    if(h > 0)
    {
        fwlib->write(h, text, strlen(text));
        fwlib->close(h);
    }
}

int stamp_read(char *buf)
{
  *buf = 0;
  int h = fwlib->open(SUCCESS_STAMP_FILE, FILE_OPEN_READ);
  if(h > 0)
  {
    fwlib->read(h, buf, 10);
    fwlib->close(h);
    return 0;
  }
  
  return -1;
}


void init()
{
    if (PMB8877_KPD_MATRIX0 == 0xDFFFFFFF) return;

    /* Гарантия запуска телефона, если в прошлый раз небыло штампа удачной загрузки,
       то прерываем загрузку и уведомляем пользователя */
    char verify[24];
    if(!stamp_read(verify))
    {
      if(strcmp(verify, "Done")) {
        __core_lprintf("  ATENTION: In last time loader looks like loaded not correctly.\n"
                       "    Please, fix the problem and unlink file '%s'.\n"
                       "    Last loader stamp is '%s'.\n", SUCCESS_STAMP_FILE, verify);
        return;
      }
    }
    
    /* Загрузчик начал работу */
    stamp("Loading");
    
    
    __core_lclear();
    __core_lprintf(s_corestart);

    __core_lprintf("Info:\r\n");

    __core_lprintf("version: %s\r\n",             __core_getversion());
    __core_lprintf("folder: %s\r\n",              __core_getfolder());
    __core_lprintf("elf: %s\r\n",               __core_getelffile());
    __core_lprintf("lib: %s\r\n",               __core_getlibfile());
    __core_lprintf("common folder: %s\r\n",     __core_getcomfolder());
    __core_lprintf("daemons folder: %s%s/\r\n", __core_getcomfolder(), f_daemons);
    __core_lprintf("patches folder: %s%s/\r\n", __core_getcomfolder(), f_patches);
    __core_lprintf("mirror fs folder: %s%s/\r\n",   __core_getcomfolder(), f_mirfs);
    
    
    
    sprintf(folder_daemons, s_ss,    __core_getcomfolder(), f_daemons);
    sprintf(folder_patches, s_ss,    __core_getcomfolder(), f_patches);
    sprintf(folder_mirfs,   s_ss,    __core_getcomfolder(), f_mirfs);

    __core_lprintf("base: 0x%08X\r\n", __core_getbase());

    __core_lprintf(s_rn);
    __core_lprintf("FWLIB:\r\n");

    __core_lprintf("open: 0x%08X\r\n",   fwlib->open);
    __core_lprintf("read: 0x%08X\r\n",   fwlib->read);
    __core_lprintf("write: 0x%08X\r\n",  fwlib->write);
    __core_lprintf("seek: 0x%08X\r\n",   fwlib->seek);
    __core_lprintf("close: 0x%08X\r\n",  fwlib->close);
    __core_lprintf("unlink: 0x%08X\r\n", fwlib->unlink);
    __core_lprintf("malloc: 0x%08X\r\n", fwlib->malloc);
    __core_lprintf("free: 0x%08X\r\n",   fwlib->free);

    __core_lprintf(s_rn);
    __core_lprintf("Init SWIHook ...\r\n");

    void *swilib = fwlib->malloc(SWILIB_SIZE);
    if (!swilib)
    {
        __core_lprintf("malloc swilib error!\r\n");
        __core_lprintf(s_coreeend);
        return;
    }

    memset(swilib, 0, SWILIB_SIZE);
    __core_lprintf("swilib: 0x%08X\r\n", swilib);

    int lib = fwlib->open(__core_getlibfile(), FILE_OPEN_READ);
    if (lib > 0)
    {
        if (fwlib->read(lib, swilib, SWILIB_SIZE) == SWILIB_SIZE)
        {
            int ctotal = 0;
            int *libr = (int *)swilib;
            for (int i = 0; i < SWILIB_LEN; i++)
                if (libr[i] != -1) ctotal++;

            __core_lprintf("core.lib: %d functions\r\n", ctotal);
            fwlib->close(lib);

            if (!ctotal)
            {
                fwlib->free(swilib);
                __core_lprintf("core.lib: zero functions count!\r\n");
                __core_lprintf(s_coreeend);
                return;
            }

        }
        else
        {
            fwlib->free(swilib);
            __core_lprintf("core.lib: read error!\r\n");
            __core_lprintf(s_coreeend);
            return;
        }
    }
    else
    {
        fwlib->free(swilib);
        __core_lprintf("core.lib: open error!\r\n");
        __core_lprintf(s_coreeend);
        return;
    }

    if (!__swihook_install(swilib))
    {
        fwlib->free(swilib);
        __core_lprintf("swihook install error!\r\n");
        __core_lprintf(s_coreeend);
        return;
    }
    else  __core_lprintf("swilib remaped to address: 0x%08X\r\n", swihook_getlib());

    __core_lprintf(s_rn);
    __core_lprintf("Init PXEAPI ...\r\n");
    if (!__pxeapi_init())
    {
        fwlib->free(swilib);
        __core_lprintf("pxeapi init error!\r\n");
        __core_lprintf(s_coreeend);
        return;
    }
    else  __core_lprintf("pxeapi remaped to address: 0x%08X\r\n", __pxeapi_getlib());

    __core_lprintf(s_rn);
    __core_lprintf("Init GC ...\r\n");

    if(__gc_init())
    {
        fwlib->free(swilib);
        __core_lprintf("Warning: gc init error! It`s may provide a memory leaks.\r\n");
        __core_lprintf(s_coreeend);
    }

    __core_lprintf(s_rn);
    __core_lprintf("Init ELF ...\r\n");
    __elf_init();

    __disable_interrupt();
    __swihook_setfunc(SWINUM_LCLEAR, (unsigned int)&__core_lclear);
    __swihook_setfunc(SWINUM_LPRINTF, (unsigned int)&__core_lprintf);
    __enable_interrupt();

    //__core_lprintf(s_rn);
    //__core_lprintf("Init Mirror FileSystem ...\r\n");
    //__mirfs_init(folder_mirfs);

    __core_lprintf(s_rn);
    __core_lprintf("Init Patches ...\r\n");

    FS_INFO patches_de;
    int patches_f = fs_opendir(folder_patches);
    if (patches_f > 0)
    {
        int tpatch = 0;
        while (!fs_readdir(patches_f, &patches_de))
        {
            if (!(patches_de.attr & FS_ATTR_FOLDER))
            {
                int len = strlen(patches_de.name);
                if (
                    len > 4                       &&
                    patches_de.name[len - 4] == '.' &&
                    patches_de.name[len - 3] == 'e' &&
                    patches_de.name[len - 2] == 'l' &&
                    patches_de.name[len - 1] == 'f'
                )
                {
                    int err = 0;
                    char d[256];
                    sprintf(d, s_s_s, folder_patches, patches_de.name);
                    char *argv[2] = {d, 0};
                    if(!(err = __elf_load(d, 1, argv, 0, 0)))
                    {
                        __core_lprintf("-> ok\r\n", err);
                        tpatch++;
                    }
                    else __core_lprintf("-> error (%d)\r\n", err);
                }
            }
        }
        fs_closedir(patches_f);
        __core_lprintf("patches elfs loaded: %d\r\n", tpatch);
    }
    else __core_lprintf("patches folder not found!\r\n");

    __core_lprintf(s_rn);
    __core_lprintf("Init Daemons ...\r\n");

    FS_INFO daem_de;
    int daem_f = fs_opendir(folder_daemons);
    if (daem_f > 0)
    {
        int tdaem = 0;
        while (!fs_readdir(daem_f, &daem_de))
        {
            if (!(daem_de.attr & FS_ATTR_FOLDER))
            {
                int len = strlen(daem_de.name);
                if (
                    len > 4                       &&
                    daem_de.name[len - 4] == '.' &&
                    daem_de.name[len - 3] == 'e' &&
                    daem_de.name[len - 2] == 'l' &&
                    daem_de.name[len - 1] == 'f'
                )
                {
                    int err = 0;
                    char d[256];
                    sprintf(d, s_s_s, folder_daemons, daem_de.name);

                    char *argv[2] = {d, 0};
                    if(!(err = __elf_load(d, 1, argv, 0, 0)))
                    {
                        __core_lprintf("-> ok\r\n", err);
                        tdaem++;
                    }
                    else __core_lprintf("-> error (%d)\r\n", err);
                }
            }
        }
        fs_closedir(daem_f);
        __core_lprintf("daemons elfs loaded: %d\r\n", tdaem);
    }
    else __core_lprintf("daemons folder not found.\r\n");
    __core_lprintf(s_coresend);
    
    
    /* Загрузчик успешно закончил работу, 
       в противно случаем после перезагрузки инициализация загрузчика будет прервана */
    stamp("Done");
}
