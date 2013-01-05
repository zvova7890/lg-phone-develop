
#include <string.h>
#include <stdlib.h>

#include <fs.h>
#include <loader.h>
#include <mem.h>
#include <pxeapi_graphics.h>
#include <pxeapi.h>
#include <taskapi.h>
#include <wchar.h>

#include "png.h"



int my_application = 0;

/*===================================================================*/
/*============================ GUI ==================================*/
/*===================================================================*/



#define WINDOW_ID_SCREEN 0x5001


typedef struct
{
    int id;
    int is_freable : 1;
    int x, y;
    int w, h;
    int state;
    wchar_t *text;
    void (*draw)(void *);
    void (*pressed)(void *);
    void (*released)(void *);
    void (*destroy)(void *);
}Button;


typedef struct
{
    void *next;
    void *prev;
    void *button;
}ButtonsQueue;


ButtonsQueue *bqueue_top = 0;
Button ExitButton = {.is_freable = 0 };


Button *create_button(Button *btn, int id, wchar_t *text, int x, int y, int w, int h,
                    void (*draw)(Button *), void (*pressed)(Button *), void (*released)(Button *), void (*destroy)(Button *))
{
    if(!btn) {
        btn = calloc(1, sizeof(*btn));
        btn->is_freable = 1;
    }

    ButtonsQueue *q = calloc(1, sizeof(ButtonsQueue));

    btn->draw = (void (*)(void*))draw;
    btn->pressed = (void (*)(void*))pressed;
    btn->released = (void (*)(void*))released;
    btn->destroy = (void (*)(void*))destroy;
    btn->x = x;
    btn->y = y;
    btn->w = w;
    btn->h = h;
    btn->id = id;
    btn->text = text;
    return btn;
}


ButtonsQueue *add_button_to_queue(ButtonsQueue *q, Button *btn)
{
    if(!q) {
        q = calloc(1, sizeof(*q));
        q->button = btn;
        return q;
    }

    ButtonsQueue *qq = calloc(1, sizeof(*qq));
    qq->button = btn;
    qq->prev = q;
    q->next = qq;

    return qq;
}



void ReleasedButton(Button *btn)
{
    switch(btn->id)
    {
        case 1:
            btn->state = 0;
            TaskMngr_AppExit(0, 0, 0);
            break;

        case 2:
        {
            btn->state = 0;
            image_t img;

            img.bitmap = Graphics_GetScreenBuffer();
            img.w = 240;
            img.h = 400;
            img.bit = 16;

            save_png_to_file (&img, "/usr/Zbin/tmp/shoot.png");
            break;
        }
    }
}


void PressedButton(Button *btn)
{
    switch(btn->id)
    {
        case 1:
            btn->state = 1;
            break;

        case 2:
        {
            btn->state = 1;
            break;
        }
    }
}



void DestroyButton(Button *btn)
{
    if(btn->is_freable)
        free(btn);
}


void DrawButton(Button *btn)
{
    Graphics_DrawRoundRect(btn->x, btn->y, btn->x+btn->w, btn->y+btn->h, 5, 5, Graphics_MakeRGBColor(0, 0xff, 0));


    int color = Graphics_MakeRGBColor(0xff, 0, 0);
    if(btn->state)
        color = Graphics_MakeRGBColor(0, 0, 0xff);

    Graphics_DrawStringSetOutLine(1);
    Graphics_DrawStringSetColor(color);
    Graphics_DrawString(btn->x+12, btn->y + (btn->h/2 - 16/2), btn->text, 16);
}


void Draw()
{
    Graphics_DrawFillRect(0, 0, DISPLAY_WITDH, DISPLAY_HEIGHT, 0xFF000000);

    Graphics_DrawStringSetOutLine(1);
    Graphics_DrawStringSetColor(0xFF00FF00);

    wchar_t d[128];

    swprintf(d, 128,  L"Привет мир! ram: %d kb", mem_freesize()/1024);

    Graphics_DrawString(2, 5, d, 16);

    ButtonsQueue *q = bqueue_top;
    while(q)
    {
        Button *btn = q->button;

        if(btn)
            btn->draw(btn);

        q = q->prev;
    }

    Graphics_Repaint();
}


//Действие при создании окна
void Screen_OnInit()
{
    Button *b = create_button(&ExitButton, 1, L"Exit", 128, 350, 80, 30, DrawButton, PressedButton, ReleasedButton, DestroyButton);
    bqueue_top = add_button_to_queue(bqueue_top, b);

    b = create_button(NULL, 2, L"Shoot", 30, 350, 80, 30, DrawButton, PressedButton, ReleasedButton, DestroyButton);
    bqueue_top = add_button_to_queue(bqueue_top, b);

    Draw();
}


//Действие при уничтожении окна
void Screen_OnExit()
{
    ButtonsQueue *q = bqueue_top;

    while(q)
    {
        ButtonsQueue *d = q;
        q = q->prev;

        Button *b = d->button;
        b->destroy(b);
        free(d);
    }
}


//Действие при зажатии настоящией кнопки или рабочей области тачскрина
void Screen_OnKeyDown(int key)
{
    switch (key)
    {
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

    switch (action)
    {
        case TOUCH_ACTION_PRESS: case TOUCH_ACTION_RELEASE:
        {
            ButtonsQueue *q = bqueue_top;
            while(q)
            {
                Button *btn = q->button;

                if( btn ) {
                    if( x >= btn->x && x <= btn->x+btn->w &&
                        y >= btn->y && y <= btn->y+btn->h )
                    {
                        if(action == TOUCH_ACTION_PRESS)
                            btn->pressed(btn);
                        else
                            btn->released(btn);
                    }
                }

                q = q->prev;
            }

            break;
        }
    }

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
    static int setup_h;

    switch (event_id)
    {
    case PXE_RUN_CREATE_EVENT:
        TaskMngr_AppSetName(my_application, 0, 0, 0);

        // Устанавливам чуствительность тачскрина
        setup_h = SetUP_GetHandle();
        SetUP_SetTouchpadSensitivity(setup_h, TOUCHPAD_SENSITIVITY_SET, 1);

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
        SetUP_SetTouchpadSensitivity(setup_h, TOUCHPAD_SENSITIVITY_SET, 1);
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
    static ELF_PARASITE_INFO parasite;
    my_application = RegisterApplicationEventListener(&parasite, listener, L"MyMegaApplication");
    return 0;
}


