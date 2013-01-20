
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
#include <gl.h>
#include "png_ops.h"




#define WINDOW_ID_SCREEN 0x5001

int curPos = 400/2;

image_t *background = 0;
int calibrate_mode = 0, calibrated_x = 24;
short sensor_x, sensor_y, sensor_z;

char tmp[256], elf_folder[128];
int my_application = 0;

unsigned int last_time, fps, fps_count;

/*===================================================================*/
/*============================ GUI ==================================*/
/*===================================================================*/

volatile static inline unsigned int cur_sec() {
    return *((volatile unsigned int *)( 0xF470001C ));
}

inline void redraw()
{
    void Screen_onDraw();
    Screen_onDraw();
}


inline void drawImage(int x, int y, image_t *image)
{
    if(image)
        glDrawBitmap(0, 0, image->w, image->h, image->bit, image->bitmap);
}


void Screen_onDraw()
{
    Graphics_DrawFillRect(0, 0, 240, 400, MakeRGBColor(0, 0, 0));
    drawImage(0, 0, background);

    glSetPen(0x9F0000FF);
    glDrawFilledRectange(0, curPos-3, 240, curPos+3);


    glSetPen(0xFF000000);

    if(calibrate_mode)
        sprintf(tmp, "Калибровка: x:%d y:%d z:%d, f: %d", sensor_x, sensor_y, sensor_z, fps);
    else
        sprintf(tmp, "cl:%d x:%d y:%d z:%d, f: %d", calibrated_x, sensor_x, sensor_y, sensor_z, fps);

    glDrawString(tmp, 1, 17, 240, 400, 15, 0, 0, 100);

    Graphics_Repaint();

    ++fps_count;
    if(last_time != cur_sec())
    {
        fps = fps_count;
        fps_count = 0;
        last_time = cur_sec();
    }
}



int getCalibratedValue()
{
    sprintf(tmp, "%sconfig.cfg", elf_folder);

    int val = 0, f = fs_open(tmp, FILE_OPEN_READ);
    if(f > -1)
    {
        fs_read(f, &val, 4);
        fs_close(f);
    }

    return val;
}


void saveCalibrateValue(int value)
{
    sprintf(tmp, "%sconfig.cfg", elf_folder);

    int f = fs_open(tmp, FILE_OPEN_CREATE | FILE_OPEN_WRITE);
    if(f > -1)
    {
        fs_write(f, &value, 4);
        fs_close(f);
    }
}


//Действие при создании окна
void Screen_onInit()
{
    calibrated_x = getCalibratedValue();

    AccelSensor_Enable();
    AccelSensor_EventsEnable(1);

    glActivateContext( glCreateContext(240, 400, 16, GetScreenBuffer()) );

    glEnable(GL_ALPHA_TEST);

    sprintf(tmp, "%sbackground.png", elf_folder);

    background = load_png(tmp, 0);

    CreateTimerEvent(2, 1, TIMER_TYPE_LOOP);
    CreateTimerEvent(1, 1, TIMER_TYPE_LOOP);
}


//Действие при уничтожении окна
void Screen_onExit()
{
    saveCalibrateValue(calibrated_x);

    AccelSensor_Disable();
    KillTimerEvent(2);
    KillTimerEvent(1);
    glDestroyContext( glActiveContext() );

    if(background) {
        if(background->bitmap)
            free(background->bitmap);

        free(background);
    }
}


//Действие при зажатии настоящией кнопки или рабочей области тачскрина
void Screen_onKeyDown(int key)
{
    switch (key)
    {

    case KEY_CAMERA: {
        image_t img;

        img.bitmap = Graphics_GetScreenBuffer();
        img.w = 240;
        img.h = 400;
        img.bit = 16;

        save_png_to_file (&img, "/usr/Zbin/shoot.png");
        break;
    }

    case KEY_SEND:

        if(calibrate_mode)
        {
            AccelSensor_GetPosition(&sensor_x, &sensor_y, &sensor_z);
            calibrated_x = sensor_x;
        }
        else
            calibrated_x = 0;

        calibrate_mode = !calibrate_mode;
        break;

    case KEY_MULTI:
        TaskMngr_Show();
        break;
    case KEY_END:
        TaskMngr_AppExit(0, 0, 0);
        break;
    }

    //redraw();
}


//Действие при отпускании настоящией кнопки
void Screen_onKeyUp(int key)
{
}



//Действие при отрисовке статус-бара
void Screen_onIndicatorDraw()
{
    //Draw();
}


//Действие при срабатывании таймеров
void Screen_onTimer(int timer_id, int param)
{
    //if(timer_id == 2)
    {
        AccelSensor_GetPosition(&sensor_x, &sensor_y, &sensor_z);

        curPos = 400/2 + sensor_x - calibrated_x;

        redraw();
    }
}


//Действие при манипуляциях с тачскрином
void Screen_onPointing(int action, int position)
{
    int x, y;

    x = PXE_LOWORD(position);
    y = PXE_HIWORD(position);

    redraw();
}


//Действие при активации
void Screen_onAwake()
{
}

//Действие при сворачивании
void Screen_onSleep()
{
}

//Главный обработчик окна WINDOW_ID_MAINMENU от приложения
int Window_EventHandler(int cmd, int subcmd, int status)
{
    switch (cmd)
    {
    case Window_OnInit:
        Screen_onInit();
        break;
    case Window_OnExit:
        Screen_onExit();
        break;
    case Window_OnAwake:
        Screen_onAwake();
        break;
    case Window_OnSleep:
        Screen_onSleep();
        break;
    case Window_OnKeyDown:
        Screen_onKeyDown(subcmd);
        break;
    case Window_OnKeyUp:
        Screen_onKeyUp(subcmd);
        break;
    case Window_OnDraw:
        redraw();
        break;
    case Window_OnTimer:
        Screen_onTimer(subcmd, status);
        break;
    case Window_OnPointing:
        Screen_onPointing(subcmd, status);
        break;
    case Window_OnIndicatorDraw:
        Screen_onIndicatorDraw();
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
    case PXE_RUN_SUSPEND_EVENT:
        return 1;
    default:
        Window_TransEvent(event_id, wparam, lparam);
        return 1;
    }
}



int main(int argc, char *argv[])
{
    char *end = strrchr(argv[0], '/');
    memcpy(elf_folder, argv[0], end-argv[0]+1);
    elf_folder[end-argv[0]+1] = 0;

    static ELF_PARASITE_INFO parasite;
    my_application = RegisterApplicationEventListener(&parasite, listener, L"MyMegaApplication");
    return 0;
}


