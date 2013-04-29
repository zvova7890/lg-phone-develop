
#include <gl.h>
#include "Button.h"



Button::Button(const Rect &rc, Widget *parent, const std::string &text) :
    Widget(rc, parent),
    m_text(text),
    m_isActive(true)
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
        off_x = 2;
        off_y = 2;

    } else {
        glSetPen( b->style().textColor() );
    }

    glDrawString(b->m_text.c_str(), b->realRect().x()+off_x, b->realRect().y()+off_y, b->realRect().x2(), b->realRect().y2(),
                 15, FT_TEXT_H_CENTER | FT_TEXT_W_CENTER, 0, 128);
}


void Button::paintEvent()
{
    int round = roundRect(realRect().w());

    //printf("round: %d\n", round);

    if(isTouched())
        style().pressedBorder().paint((realRect() - Point(1, 1)) + Rect(0, 0, 1, 1), round, round);
    else
        style().border().paint((realRect() - Point(1, 1)) + Rect(0, 0, 1, 1), round, round);


    if(isActive()) {
        if(isTouched())
            style().pressedBackground().paint(realRect(), round, round);
        else
            style().background().paint(realRect(), round, round);

    } else {
        //style().pressedBackground().paint(realRect(), round, round);
    }


    m_textRender(this);
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
    }

    Widget::touchEvent(action, x, y);
    parent()->eventManager()->updateAfterEvent();
}


