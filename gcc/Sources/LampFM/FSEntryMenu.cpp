#include "FSEntryMenu.h"
#include "main.h"
#include <nucleus.h>


FSEntryMenuItem::FSEntryMenuItem(ListMenu *parent, int w, int h, const std::string &text) :
    ListMenuItem(parent, w, h, text)
{

}


void FSEntryMenuItem::paintEvent()
{
    if(isTouched() && !isMoved()) {
        glSetPen( ((ListMenu*)parent())->_ilinepressed );
        glDrawFilledRectange(rect().x(), rect().y(), rect().x2()-1, rect().y2());
    }

    glSetPen(((ListMenu*)parent())->_iline);
    glDrawHLine(rect().x(), rect().x2()-1, rect().y());

    if(currentDisplayID() == (int)parent()->itemList()->size()-1)
        glDrawHLine(rect().x(), rect().x2()-1, rect().y2());

    glSetPen(((ListMenu*)parent())->_ilinetext);
    glDrawString(_text.c_str(), rect().x(), rect().y(), rect().x2()-1, rect().y2(), 24, FT_TEXT_H_CENTER, 0, 128);
}




FSEntryMenu::FSEntryMenu(UActiveArea *parent, const Rect &r, EventManager *e) :
    ListMenu(parent, r, e),
    _loaded(false),
    _last_y(r.y()),
    _last_h(r.h())
{

}



void FSEntryMenu::paintEvent()
{
    glSaveClipRegion();

    if(!_loaded) {
        background = resourceManager().image("fs-menu");
        _loaded = true;
    }

    drawImage(rect().x()-3, rect().y()-3, &background);

    glSetPen(0xFF9FFFFF);
    glDrawString(_fsinfo.name.c_str(), rect().x(), rect().y(), rect().x2(), rect().y()+30, 19, FT_TEXT_H_CENTER, 0, 128);


    moveY(_last_y + 30);
    setHeight(_last_h - 30);

    glSetClipRegion(rect().x(), rect().y(), rect().x2(), rect().y2());

    ActiveList::paintEvent();

    moveY(_last_y);
    setHeight(_last_h);

    glRestoreClipRegion();

}


void FSEntryMenu::touchEvent(int action, int x, int y)
{
    moveY(_last_y + 30);
    setHeight(_last_h - 30);
    ListMenu::touchEvent(action, x, y);
    moveY(_last_y);
    setHeight(_last_h);
}

