
#include <string.h>
#include <stdlib.h>


#include <Api/ApiLinkLib/ApiLink.h>

#include <pxeapi.h>
#include <loader.h>
#include <nucleus.h>
#include <taskapi.h>





int my_application = 0;
unsigned long clocks_per_second = -1, loops_per_second = -1;
double bogomips = 0.0f;
char is_calculating = 1;

NU_TASK task;
char stack[0x4000];
/*===================================================================*/
/*============================ GUI ==================================*/
/*===================================================================*/

#define WINDOW_ID_SCREEN 0x5001


__attribute__((naked))
static void delay_loop(unsigned long loops)
{
    asm volatile("CMP     R0, #0\n"
                 "MOVMI   PC, LR\n"
                 "loc_24: \n"
                 "SUBS    R0, R0, #1\n"
                 "BPL     loc_24\n"
                 "bx lr\n");
}

#undef CLOCKS_PER_SEC


volatile static unsigned long get_cur_secconds() {
    return *((volatile unsigned long *)0xF470001C);
}


volatile static unsigned long get_ticks() {
    return *((volatile unsigned long *)0xF4B00010);
}


static inline void __lock_itterupts()
{
    asm volatile("MRS R0, CPSR \n "
                 "ORR R0, R0, #0xC0\n "
                 "MSR CPSR_c, R0\n");
}


static inline void __unlock_itterupts()
{
    asm volatile("MRS R0, CPSR \n "
                 "BIC R0, R0, #0xC0\n "
                 "MSR CPSR_c, R0\n");
}


#define lock_itterrupts() __lock_itterupts()
#define unlock_itterrupts() __unlock_itterupts()


int calculate_bogomips(unsigned long *clock_per_second, unsigned long *_loops, double *_bogomips)
{
    char s[256];
    unsigned long CLOCKS_PER_SEC;

    unsigned long time = 0;

    lock_itterrupts();

    time = get_cur_secconds();
    while(time == get_cur_secconds());

    CLOCKS_PER_SEC = get_ticks();

    time ++;
    while(time == get_cur_secconds());

    CLOCKS_PER_SEC = get_ticks() - CLOCKS_PER_SEC;
    /*bogomips = CLOCKS_PER_SEC;
    unlock_itterrupts();
    return 0;*/

    unsigned long loops = 1;
    while ((loops <<= 1)) {
        unsigned long ticks;

        ticks = get_ticks();
        delay_loop(loops);
        ticks = get_ticks() - ticks;

        if (ticks >= CLOCKS_PER_SEC) {
            //return (1.0 * loops / ticks) * (CLOCKS_PER_SEC / 500000.0);
            *_bogomips = (1.0f * (float)loops / (float)ticks) * ((float)CLOCKS_PER_SEC / 500000.0f);
            if(clock_per_second) *clock_per_second = CLOCKS_PER_SEC;
            if(*_loops) *_loops = loops;
            unlock_itterrupts();
            return 0;
        }
    }

    if(clock_per_second) *clock_per_second = CLOCKS_PER_SEC;
    unlock_itterrupts();
    return -1;
}



void Draw()
{
    GrSys_FillRect(0, 0, GRSYS_WIDTH, GRSYS_HEIGHT, 0xFF000000);

    GrSys_SetBkMode(1);
    GrSys_SetTextColor(0xFF00FF00);

    wchar_t d[128];

    if(is_calculating == 1) {
        UniLib_Sprintf(d, L"Идёт расчёт...");
    } else if(is_calculating == -1) {
        UniLib_Sprintf(d, L"Ошибка при расчёте");
    } else {
        UniLib_Sprintf(d, L"BogoMIPS: %f", bogomips);
    }

    GrSys_WriteStr(0, 100, d, 20);


    GrSys_Refresh();
}


void t_entry(unsigned long argc, void *argv)
{
    is_calculating = 1;
    Draw();

    is_calculating = calculate_bogomips(&clocks_per_second, &loops_per_second, &bogomips);
    Draw();
}


//Действие при создании окна
void Screen_OnInit()
{
    GrSys_SelectGDI(0);
    NU_Create_Task(&task, "lol", t_entry, 0, 0, stack, 0x4000, 0x80, 0x50, NU_PREEMPT, NU_START);

    //Draw();
}


//Действие при уничтожении окна
void Screen_OnExit()
{
    NU_Terminate_Task(&task);
    NU_Delete_Task(&task);
}


//Действие при зажатии настоящией кнопки или рабочей области тачскрина
void Screen_OnKeyDown(int key)
{
    switch (key)
    {
    case BNS_MENU_K:
        TaskMngr_Show();
        break;
    case BNS_END_K:
        TaskMngr_AppExit(0, 0, 0);
        break;
    }

    Draw();
}


//Действие при отпускании настоящией кнопки
void Screen_OnKeyUp(int key)
{
}


//Действие при отрисовке окна
void Screen_OnDraw()
{
    Draw();
}


//Действие при отрисовке статус-бара
void Screen_OnIndicatorDraw()
{
    //Draw();
}


//Действие при срабатывании таймеров
void Screen_OnTimer(int timer_id, int param)
{

}

//Действие при манипуляциях с тачскрином
void Screen_OnPointing(int action, int position)
{
    int x, y;

    x = PXE_LOWORD(position);
    y = PXE_HIWORD(position);

    Draw();
}


//Действие при активации
void Screen_OnAwake()
{
}

//Действие при сворачивании
void Screen_OnSleep()
{
}

//Главный обработчик окна WINDOW_ID_MAINMENU от приложения
int Window_EventHandler(int cmd, int subcmd, int status)
{
    switch (cmd)
    {
    case Window_OnInit:
        Screen_OnInit();
        break;
    case Window_OnExit:
        Screen_OnExit();
        break;
    case Window_OnAwake:
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
        break;
    }

    return 1;
}



int listener(int event_id, int wparam, int lparam)
{
    switch (event_id)
    {
    case PXE_RUN_CREATE_EVENT:
        TaskMngr_AppSetName(my_application, 0, 0, 0);

        Window_Create(WINDOW_ID_SCREEN, Window_EventHandler);
        Window_Init(WINDOW_ID_SCREEN);
        return 1;

    case PXE_RUN_DESTROY_EVENT:

        // Уничтожаем окно
        Window_DestroyAll();
        ElfDestroy();
        return 1;

        //Событие при активации приложения
    case PXE_RUN_RESUME_EVENT:
        Window_TransEvent(PXE_RUN_PAINT_EVENT, 0, 0);
        return 1;

    case PXE_RUN_SUSPEND_EVENT:
        return 1;

    default:
        Window_TransEvent(event_id, wparam, lparam);
        return 1;
    }
}



int main(int argc, char *argv[])
{
    static ELF_PARASITE_INFO parasite;
    my_application = RegisterApplicationEventListener(&parasite, listener, L"MyMegaApplication");
    return 0;
}


