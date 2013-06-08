
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
#include <prochandler.h>



ProcHandlerStruct *proc_hook = 0;
H_PROCESS my_application = 0;
/*===================================================================*/
/*============================ GUI ==================================*/
/*===================================================================*/
#define WINDOW_ID_SCREEN 10

char msg_pool[512];
#define msg(m, ...) { sprintf(msg_pool, m, ##__VA_ARGS__); Screen_OnDraw(); }



void Screen_OnDraw()
{
    GrSys_FillRect(0, 0, GRSYS_WIDTH, GRSYS_HEIGHT, glRgb16(56, 0, 0));
    Indicator_Draw(0);
    GrSys_Refresh();
}



//Действие при создании окна
void Screen_OnInit()
{
    Indicator_SetShowStyle( INDICATORSTY_SHOW );

    glActivateContext( glCreateContext(GRSYS_WIDTH, GRSYS_HEIGHT, 16, GrSys_GetGrBuf()) );
    glEnable( GL_ALPHA_TEST );

    Screen_OnDraw();
}


//Действие при уничтожении окна
void Screen_OnExit()
{
    glDestroyContext( glActiveContext() );
    printf("Screen_OnExit()!!!\n");
}



//Действие при активации
void Screen_OnAwake()
{
    Indicator_SetShowStyle( INDICATORSTY_SHOW );
    Screen_OnDraw();
}

//Действие при сворачивании
void Screen_OnSleep()
{
}



//Действие при зажатии настоящией кнопки или рабочей области тачскрина
void Screen_OnKeyDown(int key)
{
    switch (key)
    {
        case KEY_CAMERA:
        {

            break;
        }

        case KEY_MULTI:
            App_RunEx(L"LGAPP/Pxo/TaskList.pxo", 0, FOREGROUND_PRIORITY, TRUE);
            //MsgHandler_SetActivePID(2);
            //proc_hook->old_listener(BNS_EVENT_KEYDOWN, key, 0);
            break;

        case KEY_END:
        {
            TaskMngr_AppExit(0, 0, 0);
            //App_Exit(my_application, 0);
            break;
        }

        case BNS_VOLUP_K:
            break;

        case BNS_VOLDOWN_K:
            break;

    }
}


//Действие при отпускании настоящией кнопки
void Screen_OnKeyUp(int key)
{
    (void) key;
}


//Действие при отрисовке статус-бара
void Screen_OnIndicatorDraw()
{
    Indicator_Draw(1);
}


//Действие при срабатывании таймеров
void Screen_OnTimer(int timer_id, int param)
{
    (void) timer_id;
    GL_UNUSED(param);

}


//Действие при манипуляциях с тачскрином
void Screen_OnPointing(int action, int position)
{
    static int last_action;
    int x, y;

    x = PXE_LOWORD(position);
    y = PXE_HIWORD(position);

    if( GrSys_GetGDIID() == 1) {
        /* retranslate coordinates */
        int t = x;

        x = y;
        y = 240-t;
    }

    Screen_OnDraw();
}


int Window_EventHandler(unsigned long cmd, unsigned long subcmd, unsigned long status)
{
    switch (cmd)
    {
    case Window_OnInit:
        Screen_OnInit();
        break;
    case Window_OnExit:
        Screen_OnExit();
        break;

    case MSG_AWAKE: case MSG_RESUME:
        Screen_OnAwake();
        break;

    case Window_OnSleep:
        Screen_OnSleep();
        break;
    case Window_OnKeyDown:
        Screen_OnKeyDown(subcmd);
        break;
    case Window_OnKeyUp:
        Screen_OnKeyUp(subcmd);
        break;
    case Window_OnDraw:
        Screen_OnDraw();
        break;
    case Window_OnTimer:
        Screen_OnTimer(subcmd, status);
        break;
    case Window_OnPointing:
        Screen_OnPointing(subcmd, status);
        break;
    case Window_OnIndicatorDraw:
        Screen_OnIndicatorDraw();
        break;
    default:
        //printf("Ololo event: %d\n", cmd);
        break;
    }

    return 1;
}


int whoo = 0;
int listener(unsigned long event_id, unsigned long wparam, unsigned long lparam)
{
    switch (event_id)
    {
        case BNS_EVENT_START:
            //MsgHandler_RegisterProcessor(WINDOW_ID_SCREEN, Window_EventHandler);
            proc_hook->old_listener(event_id, wparam, lparam);


            break;

        case BNS_EVENT_TERMINATE:
        {
            proc_hook->old_listener(event_id, wparam, lparam);
            break;
        }

        case BNS_EVENT_RESUME:
            MsgHandler_SendMessage(WINDOW_ID_SCREEN, MSG_RESUME, 0, 0);
            proc_hook->old_listener(event_id, wparam, lparam);
            break;

        case 101200:
            // wparam == 0 - менюха
            // wparam == 6 - сообщения
            whoo = wparam;

            //if(wparam == 0)
            //    MsgHandler_SetActivePID(WINDOW_ID_SCREEN);
            //else
                proc_hook->old_listener(event_id, wparam, lparam);

            //if(wparam == 0)
                //MsgHandler_SetActivePID(WINDOW_ID_SCREEN);

            printf(" -> Event: %lu, %lu, %lu\n", event_id, wparam, lparam);
            break;

        /*case 329800:
        {
            char tmp[128];
            sprintf(tmp, "/usr/zbin/message_dump_%X.bin", lparam);

            FILE *fp = fopen(tmp, "w+");
            if(fp) {
                fwrite((void*)lparam, 128, 1, fp);
                fclose(fp);
            }

            proc_hook->old_listener(event_id, wparam, lparam);
            printf(" -> Event: %lu, %lu, %lu\n", event_id, wparam, lparam);
            break;
        }*/

        default:


            //printf("Event: %lu, %lu, %lu\n", event_id, wparam, lparam);
            proc_hook->old_listener(event_id, wparam, lparam);
            break;
    }

    return 1;
}



void init_elf(void *api)
{
    proc_hook->old_init(api);

    char tmp[128];
    sprintf(tmp, "/usr/zbin/code_%X.bin", proc_hook->tproc.CodeArea);

    FILE *fp = fopen(tmp, "w+");
    if(fp) {
        fwrite((void*)proc_hook->tproc.CodeArea, 256*1024, 1, fp);
        fclose(fp);
    }

    sprintf(tmp, "/usr/zbin/data_%X.bin", proc_hook->tproc.DataArea);
    fp = fopen(tmp, "w+");
    if(fp) {
        fwrite((void*)proc_hook->tproc.DataArea, 128*1024, 1, fp);
        fclose(fp);
    }

    printf("init: %X\n", (int)proc_hook->old_init);
    printf("list: %X\n", (int)proc_hook->old_listener);
}





H_PROCESS (*old_App_Run)(T_CSTR name, T_PARAM w);
H_PROCESS _App_Run(T_CSTR pcszFile, T_PARAM wParam)
{
    char lol[128];
    UniLib_UCS2ToUTF8(pcszFile, lol);

    printf("App_Run(%s, %d)\n", lol, (int)wParam);

    return old_App_Run(pcszFile, wParam);
}


H_PROCESS (*old_App_RunEx)(T_CSTR pcszFile, T_PARAM wParam, int nPriority, BOOL bIndividual);
H_PROCESS __App_RunEx(T_CSTR pcszFile, T_PARAM wParam, int nPriority, BOOL bIndividual, int _lr)
{
    char lol[128];
    UniLib_UCS2ToUTF8(pcszFile, lol);


    H_PROCESS p = old_App_RunEx(pcszFile, wParam, nPriority, bIndividual);
    printf("lr=%X  %X = App_RunEx(%s, %d, %d, %d)\n", _lr, (int)p, lol, (int)wParam, nPriority, bIndividual);


    if(!strcmp(lol, "/LGAPP/Pxo/Radio.pxo") || !strcmp(lol, "/LGAPP/Pxo/Radio.pxo")) {
        my_application = p;
    }
    return p;
}

__attribute__((naked))
H_PROCESS _App_RunEx(T_CSTR pcszFile, T_PARAM wParam, int nPriority, BOOL bIndividual)
{
    asm volatile( " stmfd sp!, {lr} \n"
                  " bl __App_RunEx \n"
                  " ldmfd sp!, {pc} \n"
                  );
}


BOOL (*old_MsgHandler_SetActivePID) (T_ID PID);
BOOL __MsgHandler_SetActivePID(T_ID PID, unsigned int lr, unsigned int last_lr)
{
    printf(" lr=%X last_lr=%X MsgHandler_SetActivePID(%d)\n", lr, last_lr,PID);
    return old_MsgHandler_SetActivePID(PID);
}


BOOL (*old_MsgHandler_InsertActivePID) (T_ID PID);
BOOL _MsgHandler_InsertActivePID(T_ID PID)
{
    printf("MsgHandler_InsertActivePID(%d)\n", PID);
    return old_MsgHandler_InsertActivePID(PID);
}


__attribute__((naked))
BOOL _MsgHandler_SetActivePID(T_ID PID)
{
    asm volatile( " mov r1, lr \n"
                  " ldr r2, [sp, #3*4] \n"
                  " b __MsgHandler_SetActivePID"
                  );
}


void (*old_App_Exit)(H_PROCESS p, int c);
void _App_Exit(H_PROCESS p, int c)
{
    printf("App_Exit(%X, %d)\n", (int)p, c);
    old_App_Exit(p, c);

    if(p == my_application)
        my_application = 0;
}


BOOL (*old_EvHandler_PostEvent)(T_HANDLE hDst, T_EVENT EventType, T_PARAM wParam, T_PARAM lParam);
BOOL __EvHandler_PostEvent(T_HANDLE hDst, T_EVENT EventType, T_PARAM wParam, T_PARAM lParam, int  _lr)
{

    if(hDst == my_application && EventType == 329800) {

        T_CMD_INFO * info = (T_CMD_INFO *)lParam;

        char tmp[128];
        sprintf(tmp, "/usr/zbin/message_dump_%X.bin", info->Param);

        FILE *fp = fopen(tmp, "w+");
        if(fp) {
            fwrite((void*)info->Param, 128, 1, fp);
            fclose(fp);
        }
    }

    printf("lr=%X  EvHandler_PostEvent(%X, %d, %d, %X)\n", _lr, hDst, EventType, wParam, lParam);
    return old_EvHandler_PostEvent(hDst, EventType, wParam, lParam);
}

__attribute__((naked))
BOOL _EvHandler_PostEvent(T_HANDLE hDst, T_EVENT EventType, T_PARAM wParam, T_PARAM lParam)
{
    asm volatile( " stmfd sp!, {lr} \n"
                  " bl __EvHandler_PostEvent \n"
                  " ldmfd sp!, {pc} \n"
                  );
}


BOOL (*old_EvHandler_SendEvent)(T_HANDLE hDst, T_EVENT EventType, T_PARAM wParam, T_PARAM lParam);
BOOL _EvHandler_SendEvent(T_HANDLE hDst, T_EVENT EventType, T_PARAM wParam, T_PARAM lParam)
{
    printf("EvHandler_SendEvent(%X, %d, %d, %d)\n", hDst, EventType, wParam, lParam);
    return old_EvHandler_SendEvent(hDst, EventType, wParam, lParam);
}



H_PROCESS (*old_ProcMngr_SearchApp)(T_CSTR rcszAppName);
H_PROCESS _ProcMngr_SearchApp(T_CSTR rcszAppName)
{
    char lol[128];
    UniLib_UCS2ToUTF8(rcszAppName, lol);

    H_PROCESS h = old_ProcMngr_SearchApp(rcszAppName);

    //if(!strcmp(lol, "MainMenu.pxo"))
        //printf("%X = ProcMngr_SearchApp(%s)\n", h, lol);
    return h;
}


T_CMD_INFO *(*old_T_CMD_ALLOC)(T_CSTR rcszAppName);
T_CMD_INFO *__T_CMD_ALLOC(int size, int _lr)
{
    T_CMD_INFO *h = old_T_CMD_ALLOC(size);

    printf("lr=%X  %X = T_CMD_ALLOC(%d)\n", _lr, h, size);
    return h;
}


__attribute__((naked))
T_CMD_INFO *_T_CMD_ALLOC(int size)
{
    asm volatile( " mov r1, lr \n"
                  " b __T_CMD_ALLOC \n"
                  );
}


void unlock_mem_access();
void lock_mem_access();

#define sniff_me(name, group) \
    old_##group##_##name = ((TApiGrp_##group*)g_pApiLink->p##group)->pfn##name; \
    ((TApiGrp_##group *)g_pApiLink->p##group)->pfn##name = _##group##_##name;

#define unsniff_me(name, group) \
    ((TApiGrp_##group *)g_pApiLink->p##group)->pfn##name = old_##group##_##name;



//#define __ERASE

void hook_erased(int id)
{
#ifndef __ERASE
    unlock_mem_access();
    unsniff_me(Run, App);
    unsniff_me(RunEx, App);
    unsniff_me(Exit, App);
    unsniff_me(SearchApp, ProcMngr);
    unsniff_me(SetActivePID, MsgHandler);
    unsniff_me(InsertActivePID, MsgHandler);
    unsniff_me(PostEvent, EvHandler);
    unsniff_me(SendEvent, EvHandler);
    unsniff_me(ALLOC, T_CMD);
    lock_mem_access();
#endif

    ElfDestroy();
    printf("Elf destroyed, because hook is replaced or removed\n");
}



int install_hook()
{
    int id = proc_handler_install_hook((unsigned short*)L"Radio.pxo", 1, init_elf, listener, hook_erased);
    if(id < 0) {
        ElfDestroy();
        printf("Can`t install hook\n");
        return;
    }


    proc_hook = proc_handler_hook(id);
    printf("Hook installed. Access granted %X\n", (int)proc_hook);

    return id;
}


int main(int argc, char *argv[])
{
    GL_UNUSED(argc);
    GL_UNUSED(argv);

    __clear_stdout();

    int id = install_hook();
#ifdef __ERASE
    proc_handler_erase_hook(id);
    return 0;
#endif

    unlock_mem_access();
    sniff_me(Run, App);
    sniff_me(RunEx, App);
    sniff_me(Exit, App);
    sniff_me(SearchApp, ProcMngr);
    sniff_me(SetActivePID, MsgHandler);
    sniff_me(InsertActivePID, MsgHandler);
    sniff_me(PostEvent, EvHandler);
    sniff_me(SendEvent, EvHandler);
    sniff_me(ALLOC, T_CMD);
    lock_mem_access();


    return 0;
}
