
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


#include <Api/ApiLinkLib/ApiLink.h>

#include <nucleus.h>
#include <fs.h>
#include <loader.h>
#include <mem.h>
#include <pxeapi_graphics.h>
#include <pxeapi.h>
#include <taskapi.h>
#include <wchar.h>
#include <gl.h>

#include "access.h"


int my_application = 0;
int setup_h = 0;
/*===================================================================*/
/*============================ GUI ==================================*/
/*===================================================================*/


void unload_daemon();
int session_found = -1;



void myhook(int p, int t, int id)
{
    session_found = id;

    char val[24];

    sprintf(val, "%d", session_found);
    loader_setenv("EDGE_SESSION", val, 1);
}


__attribute__((noinline))
void hook()
{
    extern short hook_data[];
    extern unsigned int hook_helper_func[];
    extern void fhook();

    unlock_mem_access();

    hook_helper_func[0] = (unsigned int)fhook;
    memcpy(((char*)0x46536420)+2, hook_data, 10);

    lock_mem_access();
}



//Действие при создании окна
void onInit()
{
    char val[24];
    sprintf(val, "%X", unload_daemon);
    loader_setenv("EDGED_UNLOAD", val, 1);

    hook();
}


//Действие при уничтожении окна
void onExit()
{
    loader_unsetenv("EDGED_UNLOAD");
    glDestroyContext(glActiveContext());
}


void unload_daemon()
{
    onExit();
    ElfDestroy();
}



int main(int argc, char *argv[])
{
    onInit();
    return 0;
}


