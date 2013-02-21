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
            _released.trigger(this);
        } else if(action == TOUCH_ACTION_PRESS) {
            _pressed.trigger(this);
        }
    }
}






ListMenu::ListMenu(UActiveArea *parent, const Rect &r, EventManager *e, bool blockable) :
    ActiveList(r, e, blockable),
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
            //_on_offsreen_touch.trigger(this);
            return;
        }
    } else
        ActiveList::touchEvent(action, x, y);
}



void ListMenu::hide()
{
    _parent->pop(this);
    _on_hide.trigger(this);
}


void ListMenu::show(int after)
{
    if(!after)
        _parent->pushFront(this);
    else
        _parent->insert(this, after);
    _on_show.trigger(this);
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

