#include "GlobalMenuButton.h"
#include "main.h"



GlobalMenuButton::GlobalMenuButton(EventManager *e, const Rect &r) :
    UButton(e, r)
{
    background = resourceManager().image("global-menu");
}


void GlobalMenuButton::paintEvent()
{
    /*if(background.bitmap) {
        int cx, cy;
        cx = rect().x() + (rect().w()/2 - background.w/2);
        cy = rect().y() + (rect().h()/2 - background.h/2);

        drawImage(cx, cy, &background);
    }*/

    if(isTouched()) {
        glSetPen(0x4F000000);
        glDrawFilledRectange(rect().x(), rect().y(), rect().x2(), rect().y2());
    }

    //glSetPen(0x9FF01F00);
    //glDrawString(_name.c_str(), rect().x(), rect().y(), rect().x2(), rect().y2(), 20, FT_TEXT_H_CENTER | FT_TEXT_W_CENTER, 0, 128);
}


void GlobalMenuButton::touchEvent(int action, int x, int y)
{
    _move.emit(this, action, x, y);
}


void GlobalMenuButton::timerEvent()
{

}

