#include "ListMenu.h"
#include "main.h"


ListMenuItem::ListMenuItem(ListMenu *parent, int w, int h, const std::string &text) :
    ActiveListItem(parent, w, h),
    _text(text)
{

}


void ListMenuItem::paintEvent()
{
    int pressed = 0;

    if(isTouched() && !isMoved()) {
        pressed = 1;

        if(isHaveLongPress())
            pressed += 1;

        switch(pressed)
        {
        case 1:
            style().linePressed().paint(Rect(rect().x(), rect().y(), rect().w()-1, rect().h()));
            break;

        case 2:
            style().lineLongPressed().paint(Rect(rect().x(), rect().y(), rect().w()-1, rect().h()));
            break;
        }

    }


    //glSetPen(style().separator());
    //glDrawHLine(rect().x(), rect().x2()-1, rect().y());

    if(currentLineDisplayID() == (int)parent()->linesCount()) {
        if( parent()->style().isPaintLastLine()  )
            style().separator().paint(Rect(rect().x(), rect().y2()-1, rect().w()-1, 1));
    }
    else if(currentLineDisplayID() == 0) {
        if( parent()->style().isPaintFirstLine() )
            style().separator().paint(Rect(rect().x(), rect().y(), rect().w()-1, 1));
    }
    else {
        style().separator().paint(Rect(rect().x(), rect().y(), rect().w()-1, 1));
    }

    switch(pressed)
    {
    case 1:
        glSetPen(style().linePressedText());
        break;

    case 2:
        glSetPen(style().lineLongPressedText());
        break;

    default:
        glSetPen(style().lineText());
        break;
    }


    glDrawString(_text.c_str(), rect().x()+1, rect().y(), rect().x2()-1, rect().y2(), 24, FT_TEXT_H_CENTER, 0, 128);
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






ListMenu::ListMenu(UActiveArea *parent, const Rect &r, bool blockable) :
    ActiveList(parent, r, blockable)
{
    style().setSize(r);
    style().setListSize(r);
}


ListMenu::~ListMenu()
{

}


void ListMenu::paintEvent()
{
    glSaveClipRegion();

    style().background().paint(rect());

    style().shadow().paint(Rect(rect().x(), rect().y()-1, rect().w(), 1));
    style().shadow().paint(Rect(rect().x(), rect().y2(), rect().w(), 1));

    style().shadow().paint(Rect(rect().x2(), rect().y(), 1, rect().h()));
    style().shadow().paint(Rect(rect().x()-1, rect().y(), 1, rect().h()));


    glSetPen(style().headerText());

    const Rect & r = style().headerSize();
    glDrawString(_head_text.c_str(), rect().x()+r.x()+1, rect().y()+r.y(),
                 rect().x()+r.w()-1, rect().y()+r.h(), 19, FT_TEXT_H_CENTER, 0, 128);

    /* save old rect */
    Rect save_rect = rect();

    /* set new, for list */

    Rect list(style().listSize().x()+rect().x(), style().listSize().y()+rect().y(),
              style().listSize().w(), style().listSize().h());

    setSize(list);

    glSetClipRegion(rect().x(), rect().y(), rect().x2(), rect().y2());
    ActiveList::paintEvent();

    /* restore */
    setSize(save_rect);

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
    } else {
        /* save old rect */
        Rect save_rect = rect();

        /* set new, for list */
        setSize(style().listSize());

        ActiveList::touchEvent(action, x, y);

        /* restore */
        setSize(save_rect);
    }
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

