
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include <fs.h>
#include <loader.h>
#include <mem.h>
#include <pxeapi_graphics.h>
#include <pxeapi.h>
#include <taskapi.h>
#include <wchar.h>
#include <nucleus.h>
#include <gl.h>

#include <Api/ApiLinkLib/ApiLink.h>

#include "logger.h"
#include <prochandler.h>


ProcHandlerStruct handlers[56];



__attribute__((constructor))
int _main()
{
    for(int i=0; i<56; ++i) {
        handlers[i].id = -1;
    }

    install_hook();
    return 0;
}



__attribute__((destructor))
int _destr()
{
    remove_hook();
    return 0;
}
