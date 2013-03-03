


#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <fcntl.h>
#include <unistd.h>
#include <loader.h>

#if 0
#include <fs.h>
#include <loader.h>
#include <mem.h>
#include <pxeapi_graphics.h>
#include <pxeapi.h>
#include <taskapi.h>
#include <wchar.h>
#include <gl.h>
#include "png_ops.h"



int my_application = 0;

/*===================================================================*/
/*============================ GUI ==================================*/
/*===================================================================*/

#define WINDOW_ID_SCREEN 0x5001

GLContext *gl_ctx = 0;


void Draw()
{
    //Graphics_DrawFillRect(0, 0, DISPLAY_WITDH, DISPLAY_HEIGHT, 0xFF000000);
    //Graphics_DrawBitmap(0, 0, image->sx, image->sy, 32, image->tpixels);


    glClear(gl_ctx, 0xFF000000);

    glSetPen(gl_ctx, 0xA000FF00);
    glDrawLine(gl_ctx, 0, 0, 128, 128);

    glSetPen(gl_ctx, 0xA0FF0000);
    glDrawLine(gl_ctx, 128, 0, 0, 128);

    glDrawVLine(gl_ctx, 0, 400, 0);
    glDrawHLine(gl_ctx, 0, 240, 399);

    glSetPen(gl_ctx, 0xAFFFFFFF);
    //glDrawFilledRectange(gl_ctx, 29, 29, 100, 100);

    //GLPoint rpts[8] = {{29, 29}, {100, 29}, {100, 29}, {100, 100}, {100, 100}, {29, 100}, {29, 100}, {29, 29}};
    GLPoint rpts[8] = {{29, 29}, {100, 39}, {100, 39}, {100, 110}, {100, 110}, {29, 100}, {29, 100}, {29, 29}};
    glDrawFilledPolygon(gl_ctx, rpts, 8);

    glSetPen(gl_ctx, 0xFF00FFFF);
    glDrawRectange(gl_ctx, 29, 29, 100, 100);

    glSetPen(gl_ctx, 0xFF00FFFF);
    glDrawFilledCircle(gl_ctx, 140, 200, 65);

    glSetPen(gl_ctx, 0xFFFF0000);
    glDrawCircle(gl_ctx, 140, 200, 66);

    glDrawFilledArc(gl_ctx, 100, 150, 70, 70, 0, 60, GL_EDGED);

    glSetPen(gl_ctx, 0xFFFFFFFF);
    glDrawFilledEllipse(gl_ctx, 140, 240, 14, 44);

    glSetPen(gl_ctx, 0xFFFF0000);
    glDrawEllipse(gl_ctx, 140, 240, 14, 44);

    glDrawFilledTriangle(gl_ctx, 43, 23, 20, 80, 70, 66);

    GLPoint pts[4] = {{43, 23}, {20, 80}, {70, 66}};
    glDrawFilledPolygon(gl_ctx, pts, 3);

    glSetPen(gl_ctx, 0xFFFFFFFF);
    glDrawString(gl_ctx, "Привет долбаный мир!", 10, 350, 300, 300, 20, 0, 0, 100);


    Graphics_Repaint();
}


//Действие при создании окна
void Screen_OnInit()
{
    //Graphics_ChangeGDI(1);
    gl_ctx = glCreateContext(240, 400, 16, GetScreenBuffer());

    glEnable(gl_ctx, GL_ALPHA_TEST);
    Draw();
}


//Действие при уничтожении окна
void Screen_OnExit()
{
    glDestroyContext(gl_ctx);
    Graphics_ChangeGDI(0);
}


//Действие при зажатии настоящией кнопки или рабочей области тачскрина
void Screen_OnKeyDown(int key)
{
    switch (key)
    {
    case KEY_SEND: {
        image_t img;

        img.bitmap = Graphics_GetScreenBuffer();
        img.w = 240;
        img.h = 400;
        img.bit = 16;

        save_png_to_file (&img, "/usr/Zbin/shoot.png");
        }break;

    case KEY_MULTI:
        TaskMngr_Show();
        break;
    case KEY_END:
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
    case PXE_RUN_SUSPEND_EVENT:
        return 1;
    default:
        Window_TransEvent(event_id, wparam, lparam);
        return 1;
    }
}



static int _log;
/*
int _printf(const char *dest, ...)
{
    char buf[512];
    va_list va;
    va_start(va, dest);

    int c = vsprintf(buf, dest, va);
    va_end(va);

    write(_log, buf, c);
    return c;
}*/


void __attribute__((constructor)) __init_env__()
{
    fs_unlink("/usr/zbin/apps/fm/log.txt");
    _log = open("/usr/zbin/apps/fm/log.txt", O_CREAT | O_WRONLY);

    write(_log, "LOL\n", 4);

    const char *env = getenv("FONTS");
    if(!env) {
        setenv("FONTS", "/usr/ZBin/fonts/", 1);
    }

    void initGlStringFont();
    initGlStringFont();
}



void __attribute__((destructor)) __destroy_so__()
{
    void finiGLStringFont();
    finiGLStringFont();

    void fte_cleanMap();
    fte_cleanMap();

    close(_log);
}



int main(int argc, char *argv[])
{
    static ELF_PARASITE_INFO parasite;
    my_application = RegisterApplicationEventListener(&parasite, listener, L"MyMegaApplication")
    return 0;
}

#endif

#include <string.h>
#include <stdio.h>


/*
void *__aeabi_memcpy(void *dest, const void *src, size_t sz)
{
    return memcpy(dest, src, sz);
}
*/

__attribute__((constructor))
void __init_env__()
{
    const char *env = loader_getenv("FONTS");
    if(!env) {
        loader_setenv("FONTS", "/usr/ZBin/fonts/", 1);
    }

    int init_freetype();
    init_freetype();

    void initFontBase();
    initFontBase();

    void initGLStringFont();
    initGLStringFont();
}


__attribute__((destructor))
void  __destroy_so__()
{
    //printf("libgl: __destroy_so__()\n");

    void finiGLStringFont();
    finiGLStringFont();

    void fte_cleanMap();
    fte_cleanMap();

    int fini_freetype();
    fini_freetype();
}



