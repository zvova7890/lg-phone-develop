#include "UButton.h"


UButton::UButton(UActiveArea *parent, const Rect &rc, const std::string &text, bool blockable) :
    UActiveAreaItem<ActiveAreaItem>(parent, rc, blockable),
    m_text(text)
{

}



void UButton::paintEvent()
{
    if(isTouched())
        glSetPen(0xFFFFFFFF);
    else
        glSetPen(0xFF370700);

    glFillRoundedRect(rect().x(), rect().y(), rect().w(), rect().h(), 15, 15);

    if(isTouched())
        glSetPen(0xFFF00000);
    else
        glSetPen(0xFF0000FF);

    glDrawRoundedRect(rect().x(), rect().y(), rect().w(), rect().h(), 15, 15);

    glDrawString(m_text.c_str(), rect().x(), rect().y(), rect().x2(), rect().y2(), 15, FT_TEXT_H_CENTER | FT_TEXT_W_CENTER, 0, 128);
}


void UButton::touchEvent(int action, int x, int y)
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

    parent()->eventManager()->updateAfterEvent();
}


