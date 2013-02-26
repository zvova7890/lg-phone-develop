

#include <gl.h>
#include <pxeapi.h>
#include "objectmap.h"
#include "button.h"


static void __button_paint(Button *btn)
{
    if(btn->paintEvent)
    {
        btn->paintEvent(btn);
        return;
    }

    if(btn->obj.have_touch)
        glSetPen(btn->tcolor);
    else
        glSetPen(btn->color);

    glDrawFilledRectange(btn->obj.x, btn->obj.y, btn->obj.x+btn->obj.w, btn->obj.y+btn->obj.h);

    if(btn->text && *btn->text)
    {
        glSetPen(0xFFFFFFFF);
        glDrawString(btn->text, btn->obj.x, btn->obj.y, btn->obj.x+btn->obj.w, btn->obj.y+btn->obj.h, btn->font, FT_TEXT_W_CENTER | FT_TEXT_H_CENTER, 0, 128);
    }
}


static void __button_touch(Button *btn, int action, int x, int y)
{
    if(btn->touchEvent)
        btn->touchEvent(btn, action, x, y);
}


void buttonCreate(Button *button, int x, int y, int w, int h, int no_mem_touch,
                  void (*paint)(Button *),
                  void (*touch)(Button *, int, int, int))
{
    memset(button, 0, sizeof(*button));
    button->obj.x = x;
    button->obj.y = y;
    button->obj.w = w;
    button->obj.h = h;
    button->obj.no_mem_touch = no_mem_touch;


    button->obj.paintEvent = (void (*)(void*))__button_paint;
    button->obj.touchEvent = (void (*)(void*,int,int,int))__button_touch;

    button->paintEvent = (void (*)(void*))paint;
    button->touchEvent = (void (*)(void*,int,int,int))touch;
}


