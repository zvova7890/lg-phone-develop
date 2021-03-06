
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
#include "Pico/PicoInt.h"




#define WINDOW_ID_SCREEN 10
//#define ENABLE_OSD


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
int multiply_fps = 30;
int want_suspend = 0, resumed_state = 0;
NU_TASK *wait_for_resume_task = 0;



/*===================================================================*/
/*============================ GUI ==================================*/
/*===================================================================*/

#define LockThread() NU_Suspend_Task(&task);
#define UnLockThread() NU_Resume_Task(&task);



void *getFrameBuffer()
{
    return Graphics_GetScreenBuffer();
}


void Draw()
{
    if(!frame_count && *rom_file_name)
        return;

    /* To avoid tearing */
    NU_Suspend_Task(&task);

    UIOnDraw();

#ifdef ENABLE_OSD
    char osd[128];
    sprintf(osd, "%d,%d,%d", sleep_ticks, skeep_frames, total_fps);

    glSetPen(0xFF000000);
    glDrawFilledRectange(3, 30, 50, 45);
    glSetPen(0xFFFFFFFF);
    glDrawString(osd, 3, 45, 80, 90, 10, 0, 0, 128);
#endif

    if(!*rom_file_name) {
        glDrawString("CAN`T LOAD ROM", 0, 0, 400, 240, 25, FT_TEXT_H_CENTER | FT_TEXT_W_CENTER, 0, 128);
    }

    GrSys_Refresh();

    frame_count = 0;
    NU_Resume_Task(&task);
}



void PauseEmulator() {
    want_suspend = 1;
    frame_count = 0;

    wait_for_resume_task = NU_Current_Task_Pointer();
    NU_Suspend_Task(wait_for_resume_task);

    LockThread();
}

void ResumeEmulator() {
    want_suspend = 0;
    UnLockThread();
}


int SaveEmulatorState()
{
    PauseEmulator();

    char save_name[256];

    sprintf(save_name, "%s-save.bin", rom_file_name);
    int r = PicoSaveLoadGame(0, 0, save_name);

    ResumeEmulator();
    return r;
}


int LoadEmulatorState()
{

    PauseEmulator();

    char save_name[256];

    sprintf(save_name, "%s-save.bin", rom_file_name);
    int r = PicoSaveLoadGame(1, 0, save_name);

    ResumeEmulator();
    return r;
}


#define start_calculate() __last_ticks = get_ticks()
#define ticks() get_ticks() - __last_ticks


void t_entry(unsigned long argc, void *argv)
{
    unsigned int max_frames;
    unsigned long __last_ticks;
    unsigned long time_per_frame;

    if(Pico.m.pal) {
        multiply_fps = 1;
        max_frames = 50*2-2;
    }
    else {
        multiply_fps = 30;
        max_frames = 60*2-2;
    }

    /* restore or calculate bogomips info */
    if(!restored_bogomips)
        calculate_bogomips(&clocks_per_second, &loops_per_second, 0);


    time_per_frame = clocks_per_second/max_frames;
    start_calculate();

    while(1) {

        if(want_suspend) {
            resumed_state = 1;

            if(wait_for_resume_task) {
                NU_Resume_Task(wait_for_resume_task);
                wait_for_resume_task = 0;
            }
            NU_Sleep(50);
            continue;
        }

        int skeep = 1;
        unsigned long clocks = 0;

        clocks = ticks();
        start_calculate();
        resumed_state = 0;

        if(frame_cnt >= skeep_frames) {
            skeep = 0;
            frame_cnt = 0;
        }


        PicoDriveFrame(skeep);
        frame_cnt++;

        ++frame_count;
        ++total_frame_count;

        /* если фрейм рендернулся за время, большее чем нужно то меньше спим */
        if(clocks > time_per_frame) {
            sleep_ticks--;
            if(sleep_ticks < 0)
                sleep_ticks = 0;
        }

        if(clocks < time_per_frame) {
            sleep_ticks++;
        }


        if(sleep_ticks > 0) {
            skeep_frames = 0;
            // миллисекунда
            delay_loop(sleep_ticks*(loops_per_second/1000));
        }

        if(!sleep_ticks) {
            skeep_frames++;

            if(skeep_frames > 3)
                skeep_frames = 3;
        }


        if(last_time != cur_seconds()) {
            total_fps = total_frame_count;
            total_frame_count = 0;
            last_time = cur_seconds();
        }
    }
}



/**
 * We needs a bogomips, because we want know, how many ticks we have per seccond
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


    CreateTimerEvent(1, 50, TIMER_TYPE_LOOP);

    i = NU_Create_Task(&task, "Sega", t_entry, 0, 0, task_stack, sizeof(task_stack), 100, 0xC, NU_PREEMPT, NU_START);
    printf("Started task: %d\n", i);
}


//Действие при уничтожении окна
void Screen_OnExit()
{
    Graphics_ChangeGDI(0);

    if(!restored_bogomips)
        save_bogomips();

    if(*rom_file_name) {
        NU_Terminate_Task(&task);
        NU_Delete_Task(&task);
        KillTimerEvent(1);
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

    if(key == KEY_SIDE1) {
        LoadEmulatorState();
    }

    if(key == KEY_SIDE2) {
        SaveEmulatorState();
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
    if(timer_id == 1)
	Draw();
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


