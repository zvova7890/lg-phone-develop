
#include <Core/compatible.h>
#include "ListMenu.h"




ListMenuItem::ListMenuItem(ListMenu *parent, int w, int h, const std::string &text) :
    Widget(Rect(0, 0, w, h), parent),
    m_text(text),
    m_isActive(true),
    m_icon(0)
{

}


ListMenuItem::~ListMenuItem()
{

}


void ListMenuItem::paintEvent()
{
    int pressed = 0;
    int xoffset = 0;


    if(isTouched() && !isMoved()) {
        pressed = 1;

        if(isHaveLongPress())
            pressed += 1;

        switch(pressed)
        {
        case 1:
            style().linePressed().paint(Rect(realRect().x(), realRect().y(), realRect().w()-1, realRect().h()));
            break;

        case 2:
            style().lineLongPressed().paint(Rect(realRect().x(), realRect().y(), realRect().w()-1, realRect().h()));
            break;
        }

    }


    //glSetPen(style().separator());
    //glDrawHLine(realRect().x(), realRect().x2()-1, realRect().y());

    if(Widget::id() == (int)parent()->m_scroll.count()) {
        if( parent()->style().isPaintLastLine()  )
            style().separator().paint(Rect(realRect().x(), realRect().y2()-1, realRect().w()-1, 1));
    }
    else if(Widget::id() == 0) {
        if( parent()->style().isPaintFirstLine() )
            style().separator().paint(Rect(realRect().x(), realRect().y(), realRect().w()-1, 1));
    }
    else {
        style().separator().paint(Rect(realRect().x(), realRect().y(), realRect().w()-1, 1));
    }

    switch(pressed)
    {
    case 1:
        if(m_isActive)
            glSetPen(style().linePressedText());
        else
            glSetPen(style().lineInactivePressedText());
        break;

    case 2:
        if(m_isActive)
            glSetPen(style().lineLongPressedText());
        else
            glSetPen(style().lineInactiveLongPressedText());
        break;

    default:
        if(m_isActive)
            glSetPen(style().lineText());
        else
            glSetPen(style().lineInactiveText());
        break;
    }



    if(m_icon && !m_icon->isEmpty()) {
        int yc = realRect().y() + (realRect().h()/2 - m_icon->height()/2);

        drawImage(1, yc, m_icon);
        xoffset = m_icon->width()+4;
    }

    glDrawString(m_text.c_str(), realRect().x()+ xoffset +1, realRect().y(), realRect().x2()-1, realRect().y2(),
                 style().fontSize(), FT_TEXT_H_CENTER, 0, 128);
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






ListMenu::ListMenu(const Rect &r, Widget *parent) :
    Widget(r, parent),
    m_scroll(Rect(0, 0, rect().w(), rect().h()), ScrollList::Vertical, this),
    m_scroller(eventManager()),
    m_headerTextScrollable(false),
    m_isModal(false)
{
    style().setSize(r);
    style().setListSize(r);

    m_scroller.onTextSmallerSignal().connect( [](HTextScroller *s) {
        s->stop();
    });



    m_scroll.handleResizeEvent().connect( [this](Widget *) {
        m_scroll.setSize( Rect(0, 0, rect().w(), rect().h()) );

        Rect r( m_scroll.rect() );

        r.setY(style().headerSize().h());
        r.setH( rect().h() - r.y() );

        style().setSize(m_scroll.rect());
        style().setListSize(r);
    });

    m_scroll.show();
}


ListMenu::~ListMenu()
{

}


void ListMenu::paintEvent()
{
    glSaveClipRegion();

    style().background().paint(realRect());

    style().shadow().paint(Rect(realRect().x(), realRect().y()-1, realRect().w(), 1));
    style().shadow().paint(Rect(realRect().x(), realRect().y2(), realRect().w(), 1));

    style().shadow().paint(Rect(realRect().x2(), realRect().y(), 1, realRect().h()));
    style().shadow().paint(Rect(realRect().x()-1, realRect().y(), 1, realRect().h()));

    const Rect & r = style().headerSize();
    Rect rc = realRect();

    style().header().paint(Rect(r.x() + rc.x(), r.y() + rc.y(), r.w(), r.h()));


    glSetPen(style().headerText());
    if(m_headerTextScrollable) {

        if( !scrollArea().isAutoScrollActive() ) {
            if( !m_scroller.isActive() ) {
                m_scroller.setTextAttrs(FT_TEXT_H_CENTER);
                m_scroller.setTextSize(19);
                m_scroller.setRect(Rect(realRect().x()+r.x()+1, realRect().y()+r.y(), r.w()-1, r.h()));

                m_scroller.start(100);
                m_scroller.setText(_head_text);
            }
        } else {
            m_scroller.stop();
        }

        m_scroller.paintEvent();

    } else {
        m_scroller.stop();
        glDrawString(_head_text.c_str(), realRect().x()+1, realRect().y(),
                     realRect().x()+r.w()-1, realRect().y()+r.h(), 19, FT_TEXT_H_CENTER, 0, 128);
    }


    // if we have changed sizes we recalculate it
    /*Rect rc = scrollArea().rect();

    rc.setY( r.h() );
    rc.setH( rect().h() - r.h() );*/

    scrollArea().setSize(style().listSize());


    glSetClipRegion(scrollArea().realRect().x(), scrollArea().realRect().y(),
                    scrollArea().realRect().x2(), scrollArea().realRect().y2());
    Widget::paintEvent();
    glRestoreClipRegion();
}


void ListMenu::touchEvent(int action, int x, int y)
{
    // Offscreen touch
    if(isOffRectTouch()) {

        if( action == TOUCH_ACTION_RELEASE &&
            !isMoved())
        {
            ListMenu::hide();
            return;
        }
    } else {

        Widget::touchEvent(action, x, y);
    }

}



bool ListMenu::close()
{
    m_scroller.stop();

    bool r = Widget::close();
    _on_hide.trigger(this);

    return r;
}


bool ListMenu::hide()
{
    m_scroller.stop();

    bool r = Widget::hide();
    _on_hide.trigger(this);

    return r;
}


bool ListMenu::show()
{
    m_scroller.reset();

    bool r = Widget::show();
    _on_show.trigger(this);

    return r;
}

