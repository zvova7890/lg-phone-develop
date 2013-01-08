
#include <string.h>
#include <stdlib.h>

#include <loader.h>
#include <wchar.h>


#include <lgos_timers.h>
#include <ApiLinkLib/ApiLink.h>



#undef printf
__attribute__((swi(0xE)))
int printf(const char *format, ...);


#define glRgb16(r,g,b)  ((uint16_t)((r & 0xF8) << 8) | ((g & 0xFC) << 3) | ((b & 0xF8) >> 3))

//Хендл процесса
H_PROCESS h_proc;
TApiLink *g_pApiLink = (void *)0x400000;


int x_state = 0, x_seek = 0;
wchar_t text[] = L"OLOLO TROLOLO я водитель нло";
int text_pos = sizeof(text)/2-1;

/*===================================================================*/
/*============================ GUI ==================================*/
/*===================================================================*/

void ApplicationDrawEvent()
{
    GrSys_FillRect(0, 0, GrSys_GetWidth(), GrSys_GetHeight(), glRgb16(0, 0, 0));


    if(x_state >= GrFont_GetCharWidth(20, *(text+text_pos)))
    {
        x_state = 0;
        text_pos--;
    }

    if(text_pos < 0)
        text_pos = 0;

    GrText_Reset();
    GrText_SetRange(0+x_seek, 10, GrSys_GetWidth(), GrSys_GetHeight());
    GrText_SetSepXRange(10, 10);
    GrText_SetFont(20);
    GrText_SetColor(glRgb16(0xff, 0, 0));
    GrText_SetMultiLine(0);


    GrText_Draw(text);

    //GrText_SetSelection(text_pos, 0);
    GrText_SetRange(0 + x_seek - GrSys_CalcStrWidth(text + (text_pos), 20)-20,
                     10, GrSys_GetWidth(), GrSys_GetHeight());

    GrText_Draw(text + (text_pos));

    GrSys_ResetClipRect();

    x_state += 3;
    x_seek += 3;

    if(x_seek-20 >= (signed int)GrSys_CalcStrWidth(text, 20)) {
       x_seek = 0;
       x_state = 0;
       text_pos = sizeof(text)/2-1;
    }

    GrSys_RefreshRect(0, 10, 240, 30);
}



void ololo_calback
    //(T_HANDLE owner, H_TIMERCORE timer, int flags)
    (void *user)
{
    ApplicationDrawEvent();
}


LGOS_TIMER timer;


void ApplicationInitEvent()
{
    /*LGOS_Timer_Create(&timer, "Lol");
    LGOS_Timer_SetLoop(&timer, 1);
    LGOS_Timer_SetPeriod(&timer, 15, 15);
    LGOS_Timer_SetProc(&timer, ololo_calback, 0);
    LGOS_Timer_Start(&timer);*/

    Timer_SetTimer(2, 1, 1);

    printf("-> %s\n", __FUNCTION__);
}


void ApplicationFiniEvent()
{
    //LGOS_Timer_Stop(&timer);
    //LGOS_Timer_Delete(&timer);

    Timer_KillTimer(2);
    printf("-> %s\n", __FUNCTION__);
}


void ApplicationSleepEvent()
{
    LGOS_Timer_Stop(&timer);
    printf("-> %s\n", __FUNCTION__);
}


void ApplicationResumeEvent()
{
    LGOS_Timer_Start(&timer);
    printf("-> %s\n", __FUNCTION__);
}


void ApplicationTimerEvent(int id)
{
    if(id == 2) {
        ApplicationDrawEvent();
    }

    //printf("-> %s\n", __FUNCTION__);
}


void ApplicationKeyEvent(int type, int key)
{
    switch(type)
    {
    case MSG_KEYDOWN:

        switch(key)
        {
        case BNS_END_K:
            App_Exit(h_proc, 0);
            break;

        case BNS_MENU_K:
            //LGOS_Timer_Stop(&timer);
            //TaskMngr_Show();
            break;

        }

        break;
    }
}


/* Обработчик сообщений для приложения */
BOOL elf_main_processor(T_MSG msg, T_PARAM wParam, T_PARAM lParam)
{
    switch(msg)
    {
    case MSG_INIT:
        ApplicationInitEvent();
        return TRUE;

    case MSG_EXIT:
        ApplicationFiniEvent();
        return TRUE;

    case MSG_DRAW:
        ApplicationDrawEvent();
        return TRUE;

    case MSG_KEYDOWN:
        ApplicationKeyEvent(MSG_KEYDOWN, wParam);
        return TRUE;

    case MSG_TIMER:
        ApplicationTimerEvent(wParam);
        return TRUE;

    case MSG_SLEEP:
        ApplicationSleepEvent();
        return TRUE;

    case MSG_RESUME:
        ApplicationResumeEvent();
        return TRUE;

    default:
        return TRUE;
    }
}



/* Процедура инициализации */
void elf_init(int *api)
{
    if (api)
    {
        g_pApiLink = (TApiLink *)api[0];
    }
}



/* Обработчик событий для приложения */
int elf_run(T_EVENT EventType, T_PARAM wParam, T_PARAM lParam)
{
    BOOL error = 0;
    switch (EventType)
    {
    case BNS_EVENT_START:

        MsgHandler_RegisterProcessor(1, elf_main_processor);
        MsgHandler_SetActivePID(1);

        MsgHandler_Process();
        break;

    case BNS_EVENT_TERMINATE:
        MsgHandler_Terminate();
        MsgHandler_RemoveProcessor(elf_main_processor, 0, 0);

        /* Оповестим эльфпак, о окончании работы эльфа */
        ElfDestroy();
        break;

    default:
        MsgHandler_Translate(EventType, wParam, lParam);
        break;
    }

    return 0;
}


int main(int argc, char *argv[])
{
    /* Создание процесса */
    TProcessCI tproc;

    //Доступность процесса
    tproc.enAccessLevel = ACCESSLEVEL_SYSTEM;
    //Задаём адрес кода (чтобы при закрытии автоматически очистить)
    //У нас это весь эльф целиком
    tproc.CodeArea = (T_ADDR)0;
    //Задаём адрес данных (чтобы при закрытии автоматически очистить)
    //Зададим пустышку
    tproc.DataArea = (T_ADDR)0;
    //Зададим ф-ию для инициализации (обычно это инициализация API)
    tproc.PxeInitAddr = (T_ADDR)elf_init;
    //Зададим ф-ию для обработки событий процесса
    tproc.PxeRunAddr = (T_ADDR)elf_run;
    //Зададим имя процесса
    tproc.pszAppName = L"Process";
    //Остальные параметры
    tproc.hAppDrive = 0;
    tproc.hAppDir   = 0;

    //Создаём непосредственно процесс
    h_proc = ProcMngr_CreateProcess(&tproc, TRUE);

    /* Старт процесса */
    ProcMngr_StartProcess(h_proc, 0, FOREGROUND_PRIORITY);
    return 0;
}


