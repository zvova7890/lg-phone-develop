
#include <string.h>
#include <stdlib.h>

#include <Api/ApiLinkLib/ApiLink.h>
#include <fs.h>
#include <loader.h>
#include <mem.h>
#include <pxeapi_graphics.h>
#include <pxeapi.h>
#include <taskapi.h>
#include <wchar.h>
#include <nucleus.h>
#include "png.h"
#include "ui/ui.h"
#include <gl.h>
#include <math.h>
#include <fcntl.h>
#include <platform/lg/rom.h>
#include "bogomips.h"





char elfdir[256];
char rom_file_name[256] = "";
int my_application = 0;
NU_TASK task;
char task_stack[0x4000];

/* frame-rate controll */
static int frame_cnt = 0;
static int skeep_frames = 0;
static int max_skeep_frames = 8;
static int sleep_ticks = 10;

unsigned int fps = 0, frame_count;
unsigned int total_fps = 0, total_frame_count = 0, last_time;

unsigned long clocks_per_second = 0, loops_per_second = 0;
char restored_bogomips = 0;

#define multiply_fps 30
#define WINDOW_ID_SCREEN 10
/*===================================================================*/
/*============================ GUI ==================================*/
/*===================================================================*/


void *getFrameBuffer()
{
    return Graphics_GetScreenBuffer();
}

#define ENABLE_OSD
#define THREAD_RENDERING


void Draw()
{
    //Graphics_DrawFillRect(0, 0, GRSYS_WIDTH, GRSYS_HEIGHT, MakeRGBColor(0xFF, 0, 0));

#ifndef THREAD_RENDERING
    int skeep = 1;
    if(frame_cnt >= skeep_frames) {
        skeep = 0;
        frame_cnt = 0;
    }

    PicoDriveFrame(skeep);
    frame_cnt++;
#endif

    UIOnDraw();

#ifdef ENABLE_OSD
    char osd[128];
    sprintf(osd, "%d,%d,%d", sleep_ticks, skeep_frames, total_fps);
    //sprintf(osd, "%d, %d", sleep_ticks, fps*multiply_fps);
#endif

    /* To avoid tearing */
#ifdef THREAD_RENDERING
    NU_Suspend_Task(&task);
#endif

#ifdef ENABLE_OSD
    glSetPen(0xFF000000);
    glDrawFilledRectange(3, 30, 50, 45);
    glSetPen(0xFFFFFFFF);
    glDrawString(osd, 3, 45, 80, 90, 10, 0, 0, 128);
#endif

    if(!*rom_file_name) {
        glDrawString("CAN`T LOAD ROM", 0, 0, 400, 240, 25, FT_TEXT_H_CENTER | FT_TEXT_W_CENTER, 0, 128);
    }

    //GrSys_RefreshRect(0, 0, 320, 240);
    GrSys_Refresh();

#ifdef THREAD_RENDERING
    NU_Resume_Task(&task);
#endif
}




#define start_calculate() __last_ticks = get_ticks()
#define ticks() get_ticks() - __last_ticks

void t_entry(unsigned long argc, void *argv)
{
    const int max_frames = 60.0f/multiply_fps+1; // NTSC
    unsigned long __last_ticks;

    if(!restored_bogomips)
        calculate_bogomips(&clocks_per_second, &loops_per_second, 0);
    start_calculate();

    while(1) {
        int skeep = 1;

        if(frame_cnt >= skeep_frames) {
            skeep = 0;
            frame_cnt = 0;
        }

        PicoDriveFrame(skeep);
        frame_cnt++;


        ++frame_count;
        ++total_frame_count;
        if((ticks()) >= (clocks_per_second)/multiply_fps)
        {
            start_calculate();

            fps = frame_count;
            frame_count = 0;

            if(fps > max_frames) {
                if(skeep_frames > 0) {
                    sleep_ticks = 0;
                    if(fps > max_frames+(13/multiply_fps) && skeep_frames > 1)
                        skeep_frames -= 2;
                    else
                        skeep_frames --;
                } else {
                    skeep_frames = 0;
                    sleep_ticks += 1;

                    int delay = sleep_ticks*(loops_per_second/3000);
                    if(delay > 1)
                        delay_loop(delay);
                }

            }

            if(fps < max_frames) {

                if(sleep_ticks > 0) {
                    sleep_ticks -= 1;

                    if(sleep_ticks > 0) {
                        int delay = sleep_ticks*(loops_per_second/3000);
                        if(delay > 1)
                            delay_loop(delay);
                    }

                    if(sleep_ticks < 0)
                        sleep_ticks = 0;

                } else {
                    if(skeep_frames < max_skeep_frames) {
                        if(fps < max_frames-(13/multiply_fps))
                            skeep_frames += 2;
                        else
                            skeep_frames ++;
                    }
                }
            }
        }

        if(last_time != cur_seconds()) {
            total_fps = total_frame_count;
            total_frame_count = 0;
            last_time = cur_seconds();
        }

    }
}



/**
 * We needs a bogomips, because we want kwon, how many ticks we have per seccond
 * for more accurate frame-rate controll
 */

void save_bogomips()
{
    char file[256];

    sprintf(file, "%sconfig/", elfdir);
    mkdir(file, 0777);

    sprintf(file, "%sconfig/CLOCKS_PER_SEC", elfdir);
    FILE *fp = fopen(file, "w+");

    if(fp) {

        int r = fwrite(&clocks_per_second, 4, 1, fp);
        r += fwrite(&loops_per_second, 4, 1, fp);
        fclose(fp);
    }
}


/**
 * For faster start, we don`t calculate bogomips every time(e.g. 1-2 second for calculating)
 * just save variables on fs, and next time - restore it ;)
 */

void restore_bogomips()
{
    char file[256];

    sprintf(file, "%sconfig/CLOCKS_PER_SEC", elfdir);
    FILE *fp = fopen(file, "r");

    if(fp) {

        int r = fread(&clocks_per_second, 1, 4, fp);
        r += fread(&loops_per_second, 1, 4, fp);
        fclose(fp);

        if(r == 8)
            restored_bogomips = 1;
    }
}

//Действие при создании окна
void Screen_OnInit()
{
    Graphics_ChangeGDI(1);
    glActivateContext( glCreateContext(GRSYS_WIDTH, GRSYS_HEIGHT, 16, Graphics_GetScreenBuffer()) );
    glEnable(GL_ALPHA_TEST);

    Graphics_DrawFillRect(0, 0, GRSYS_WIDTH, GRSYS_HEIGHT, MakeRGBColor(0, 0, 0));

    UIOnInit();

    if(!*rom_file_name)
    {
        sprintf(rom_file_name, "%srom.gen", elfdir);

        if(access(rom_file_name, F_OK)) {
            sprintf(rom_file_name, "%srom.smd", elfdir);
            if(access(rom_file_name, F_OK)) {
                sprintf(rom_file_name, "%srom.bin", elfdir);
                if(access(rom_file_name, F_OK))
                    *rom_file_name = 0;
            }
        }
    }

    if(!*rom_file_name)
        return;


    restore_bogomips();
    int i = PicoDriveInit();

    if(!i)
        i += PicoDriveLoadRom(rom_file_name);
    else
        PicoDriveDeinit();

    if(i) {
        *rom_file_name = 0;
        return;
    }

#ifndef THREAD_RENDERING
    CreateTimerEvent(1, 1, TIMER_TYPE_LOOP);
    CreateTimerEvent(2, 1, TIMER_TYPE_LOOP);
    CreateTimerEvent(3, 1, TIMER_TYPE_LOOP);
#else
    CreateTimerEvent(1, 50, TIMER_TYPE_LOOP);

    i = NU_Create_Task(&task, "Sega", t_entry, 0, 0, task_stack, sizeof(task_stack), 100, 0, NU_PREEMPT, NU_START);
    printf("Started task: %d\n", i);
#endif

}


//Действие при уничтожении окна
void Screen_OnExit()
{
    Graphics_ChangeGDI(0);

    if(!restored_bogomips)
        save_bogomips();

    if(*rom_file_name) {
#ifdef THREAD_RENDERING
        NU_Terminate_Task(&task);
        NU_Delete_Task(&task);
        KillTimerEvent(1);
#else
        KillTimerEvent(1);
        KillTimerEvent(2);
        KillTimerEvent(3);
#endif
        PicoDriveDeinit();
    }

    UIOnDestroy();

    glDestroyContext( glActiveContext() );
}


//Действие при зажатии настоящией кнопки или рабочей области тачскрина
void Screen_OnKeyDown(int key)
{
    if(key == KEY_CAMERA) {
        TaskMngr_AppExit(0, 0, 0);
        return;
    }

    UIOnKey(1, key);
}


//Действие при отпускании настоящией кнопки
void Screen_OnKeyUp(int key)
{
    UIOnKey(2, key);
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
#ifdef THREAD_RENDERING
    if(timer_id == 1)
	Draw();
#else
    Draw();
#endif
}

//Действие при манипуляциях с тачскрином
void Screen_OnPointing(int action, unsigned int position)
{
    unsigned int x, y;

    x = PXE_LOWORD(position);
    y = PXE_HIWORD(position);

    UIOnTouch(action, x, y);
    //Draw();
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
    static int setup_h;

    switch (event_id)
    {
    case PXE_RUN_CREATE_EVENT:
        TaskMngr_AppSetName(my_application, 0, 0, 0);

        // Устанавливам чуствительность тачскрина
        setup_h = SetUP_GetHandle();
        SetUP_SetTouchpadSensitivity(setup_h, TOUCHPAD_SENSITIVITY_SET, 8);

        Window_Create(WINDOW_ID_SCREEN, Window_EventHandler);
        Window_Init(WINDOW_ID_SCREEN);
        return 1;

    case PXE_RUN_DESTROY_EVENT:

        SetUP_CloseHandle(setup_h);

        // Уничтожаем окно
        Window_DestroyAll();
        ElfDestroy();
        return 1;

        //Событие при активации приложения
    case PXE_RUN_RESUME_EVENT:
        Window_TransEvent(PXE_RUN_PAINT_EVENT, 0, 0);
        SetUP_SetTouchpadSensitivity(setup_h, TOUCHPAD_SENSITIVITY_SET, 8);
        return 1;

    case PXE_RUN_SUSPEND_EVENT:
        SetUP_SetTouchpadSensitivity(setup_h, TOUCHPAD_SENSITIVITY_DEFAULT, 0);
        return 1;

    default:
        Window_TransEvent(event_id, wparam, lparam);
        return 1;
    }
}



int main(int argc, char *argv[])
{
    if(argc > 1) {
        strcpy(rom_file_name, argv[1]);
        printf("Found rom file '%s'\n", rom_file_name);
    }

    strncpy(elfdir, argv[0], (strrchr(argv[0], '/')+1) - argv[0]);


    static ELF_PARASITE_INFO parasite;
    my_application = RegisterApplicationEventListener(&parasite, listener, L"PicoDrive");
    return 0;
}


