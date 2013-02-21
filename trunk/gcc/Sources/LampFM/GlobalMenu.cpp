#include "GlobalMenu.h"
#include "main.h"


GlobalMenuItem::GlobalMenuItem(GlobalMenu *parent, int w, int h, const std::string &text) :
    ListMenuItem(parent, w, h, text),
    _light(false)
{

}


void GlobalMenuItem::paintEvent()
{

    /*if(!_light)
        glSetPen(0xFF000000);
    else
        glSetPen(0xFF2e2e2e);*/


    //glDrawFilledRectange(rect().x(), rect().y(), rect().x2()-1, rect().y2());
    glSetPen(0x4FAFAFFF);
    glDrawHLine(rect().x(), rect().x2()-1, rect().y());

    if(isTouched() && !isMoved()) {
        //glSetPen(0xAF0000FF);
        //glDrawFilledRectange(rect().x(), rect().y(), rect().x2()-1, rect().y2());

        unsigned short alpha = 0x20;
        for(int i=1; i<rect().h()/2; ++i, alpha += 4) {

            if(alpha >= 0xff) {
                alpha = 0xff;
            }

            GLColor c = ((unsigned char)alpha << 24) | 0x0000FF;
            glSetPen(c);
            glDrawHLine(rect().x(), rect().x2()-1, rect().y()+i);

        }

        //alpha = 0xFF;
        for(int i=(const int)rect().h()/2; i<rect().h()-1; ++i, alpha -= 4) {
            if(alpha <= 0x20) {
                alpha = 0x20;
            }
            GLColor c =  ((unsigned char)alpha << 24) | 0x0000FF;
            glSetPen(c);
            glDrawHLine(rect().x(), rect().x2(), rect().y()+i);

        }
    }

    if(currentDisplayID() == (int)parent()->itemList()->size()-1)
        glDrawHLine(rect().x(), rect().x2()-1, rect().y2());

    //glSetPen(0xFFd1d6d6);
    glSetPen(0xFFFFFFFF);
    glDrawString(_text.c_str(), rect().x()+5, rect().y(), rect().x2()-5, rect().y2(), 24, FT_TEXT_H_CENTER, 0, 128);
}

/*
void GlobalMenuItem::touchEvent(int action, int x, int y)
{
    if(!isMoved())
    {
        if(action == TOUCH_ACTION_RELEASE) {
            _released.emit(this);
        } else if(action == TOUCH_ACTION_PRESS) {
            _pressed.emit(this);
        }
    }
}
*/





GlobalMenu::GlobalMenu(UActiveArea *parent, const Rect &r, EventManager *e, bool blockable) :
    ListMenu(parent, r, e, blockable),
    last_light(true),
    _offset_x(0), //6
    _offset_y(3)
{

}


GlobalMenu::~GlobalMenu()
{

}


GlobalMenuItem * GlobalMenu::pushBack(GlobalMenuItem *m)
{
    ActiveList::pushBack(m);

    m->setLighting(last_light);
    last_light = !last_light;

    return m;
}


void GlobalMenu::paintEvent()
{
    /*if(background.bitmap)
        drawImage(rect().x()-_offset_x, rect().y()-_offset_y, &background);*/

    int x = rect().x()-_offset_x-1;
    int y = rect().y()-_offset_y-1;

    glSetPen(0xF0000000);
    glDrawFilledRectange(x+1, y+1, x+239, y+314);
    glSetPen(0xFFFFFFFF);
    glDrawRectange(x, y, x+239, y+314);

    glSaveClipRegion();
    glSetClipRegion(rect().x(), rect().y(), rect().x2(), rect().y2());

    //glSetPen(0xFFFFFFFF);
    //glDrawFilledRectange(rect().x(), rect().y(), rect().x2(), rect().y2());

    ActiveList::paintEvent();

    glRestoreClipRegion();
}

/*
void GlobalMenu::touchEvent(int action, int x, int y)
{
    // Offscreen touch
    if(isOffRectTouch()) {

        if( action == TOUCH_ACTION_RELEASE &&
            !isMoved())
        {
            _parent->pop(this);
            //_parent->setProntPaint(true);
            paint_mngr->updateAfterAction();
            return;
        }
    } else
        ActiveList::touchEvent(action, x, y);
}
*/
