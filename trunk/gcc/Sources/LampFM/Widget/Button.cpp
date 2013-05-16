
#include <gl.h>
#include "Button.h"
#include <Core/compatible.h>


Button::Button(const Rect &rc, Widget *parent, const std::string &text) :
    Widget(rc, parent),
    m_text(text),
    m_isActive(true),
    m_textVisible(true),
    m_icon(0)
{
    setDefaultTextRender();
}



Button* Button::setTextRender(std::function<void (Button *)> f)
{
    m_textRender = f;
    return this;
}


void Button::setDefaultTextRender()
{
    m_textRender = defaultTextRender;
}


int Button::roundRect(int w)
{
    return w * 12 / 100;
}


void Button::defaultTextRender(Button *b)
{
    int off_x = 0, off_y = 0;
    if(b->isTouched()) {
        glSetPen( b->style().pressedTextColor() );
        off_x = b->style().pressedTextOffset().x();
        off_y = b->style().pressedTextOffset().y();

    } else {
        glSetPen( b->style().textColor() );
    }

    glDrawString(b->m_text.c_str(), b->realRect().x()+off_x, b->realRect().y()+off_y, b->realRect().x2(), b->realRect().y2(),
                 b->style().fontSize(), b->style().fontFlags(), 0, 128);
}


void Button::paintEvent()
{
    int round = style().roundedRect()? roundRect(realRect().w()) : 0;

    //printf("round: %d\n", round);

    auto p = [this, round]() {
        if(isTouched())
            style().pressedBorder().paint((realRect() - Point(1, 1)) + Rect(0, 0, 1, 1), round, round);
        else
            style().border().paint((realRect() - Point(1, 1)) + Rect(0, 0, 1, 1), round, round);
    };

    if(!style().shadowAfterBackground())
        p();

    if(isTouched())
        style().pressedBackground().paint(realRect(), round, round);
    else
        style().background().paint(realRect(), round, round);


    if(style().shadowAfterBackground())
        p();


    if(m_icon) {
        int px, py;

        px = rect().w()/2 - m_icon->width()/2;
        py = rect().h()/2 - m_icon->height()/2;

        drawImage(realRect().x() + px, realRect().y() + py, m_icon);
    }

    if(m_textVisible)
        m_textRender(this);

    if(!isActive()) {
        //glSetPen(0x7F000000);
        //glDrawFilledRectange(realRect().x(), realRect().y(), realRect().x2(), realRect().y2());
        style().inactiveFill().paint(realRect());
    }
}


void Button::touchEvent(int action, int x, int y)
{
    switch(action)
    {
        case TOUCH_ACTION_PRESS:
            m_pressed.trigger(this);
            break;

        case TOUCH_ACTION_RELEASE:
            m_released.trigger(this);
            break;

        case TOUCH_ACTION_MOVE:
            m_moved.trigger(this);
            break;
    }

    m_touchAction.trigger(this, action);

    Widget::touchEvent(action, x, y);
    parent()->eventManager()->updateAfterEvent();
}


void Button::resizeEvent()
{

}
