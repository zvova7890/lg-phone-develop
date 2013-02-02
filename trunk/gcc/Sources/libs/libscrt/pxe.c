
#include <fs.h>
#include <loader.h>
#include <pxeapi.h>
#include <mem.h>
#include <wchar.h>
#include <taskapi.h>


#define PXO_DONOR_PATH L"LGAPP/Pxo/donor.pxo"


__attribute__((naked))
int *swibase()
{
    asm(" stmfd sp!, {lr} \n"
        " swi   0 \n"
        " ldmfd sp!, {pc} \n");
}


void _init()
{
    /*int *switbl = swibase();

    for(int i=0; i<0x4000; ++i)
        ((int *)__switab)[i] = switbl[i];*/
}


static int wstrcpy(wchar_t *dest, wchar_t *src)
{
    wchar_t *d = dest;
    while((*dest++ = *src++));
    return dest-d;
}


int RegisterApplicationEventListener( ELF_PARASITE_INFO *pi, int (*handler)(int event_id, int wparam, int lparam),
                                      const wchar_t *name )
{
    //Заполняем информацию для PXE - донора
    pi->evt_handler = handler;
    pi->base = malloc(4);

    //Загружаем PXE донор
    int my_application = TaskMngr_AppRun(PXO_DONOR_PATH, (int)pi);

    //Подменям имя файла, чтобы обеспечить загрузку других приложений
    if (my_application)
    {
        PxoApplicationData *app = (PxoApplicationData *)my_application;
        wstrcpy(app->fname, L"MyMegaApplication");
        //Регистрируем приложение в Диспетчере задач
        TaskMngr_AppRegister(my_application);
    }

    return 0;
}

