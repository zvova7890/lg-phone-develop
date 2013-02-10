#include "ListMenu.h"
#include "main.h"


ListMenuItem::ListMenuItem(ListMenu *parent, int w, int h, const std::string &text) :
    ActiveListItem(parent, w, h),
    _text(text)
{

}


void ListMenuItem::paintEvent()
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


void ListMenuItem::touchEvent(int action, int x, int y)
{
    ((void)x);
    ((void)y);

    if(!isMoved())
    {
        if(action == TOUCH_ACTION_RELEASE) {
            _released.emit(this);
        } else if(action == TOUCH_ACTION_PRESS) {
            _pressed.emit(this);
        }
    }
}






ListMenu::ListMenu(UActiveArea *parent, const Rect &r, EventManager *e) :
    ActiveList(r, e),
    _parent(parent)
{

}


ListMenu::~ListMenu()
{

}


void ListMenu::paintEvent()
{
    glSaveClipRegion();
    glSetClipRegion(rect().x(), rect().y(), rect().x2(), rect().y2());

    glSetPen(_background);
    glDrawFilledRectange(rect().x(), rect().y(), rect().x2(), rect().y2());

    ActiveList::paintEvent();

    glRestoreClipRegion();
}


void ListMenu::touchEvent(int action, int x, int y)
{
    // Offscreen touch
    if(isOffRectTouch()) {

        if( action == TOUCH_ACTION_RELEASE &&
            !isMoved())
        {
            hide();
            return;
        }
    } else
        ActiveList::touchEvent(action, x, y);
}



void ListMenu::hide()
{
    _parent->pop(this);
    _on_hide.emit(this);
}



void ListMenu::setBackgroundColor(GLColor color)
{
    _background = color;
}


void ListMenu::setItemLineColor(GLColor color)
{
    _iline = color;
}


void ListMenu::setPressedLineColor(GLColor color)
{
    _ilinepressed = color;
}


void ListMenu::setItemTextColor(GLColor color)
{
    _ilinetext = color;
}

