
#include <gl.h>
#include "Keyboard.h"
#include <wchar.h>
#include <Widget/Button.h>
#include "KeyboardEN.h"




Keyboard::Keyboard(const Rect &r, Widget *parent, KeyboardHelper *kbd) :
    Widget(r, parent),
    m_kbdCleanup(false),
    m_animation_type(0)
{
    setBlockable(true);
    setFocuseable(false);

    if(!kbd) {
        kbd = new KeyboardEN(Rect(0, 0, r.w(), r.h()), this);
        m_kbdCleanup = true;
    }


    m_kbd = kbd;
    add(kbd);

    hide();

    m_timer.timerEventSignal().connect(this, &Keyboard::effectHandler, std::placeholders::_1);
    m_lastRect = rect();
}


Keyboard::~Keyboard()
{
    if(m_kbdCleanup) {
        delete m_kbd;
    }
}



void Keyboard::paintEvent()
{
    GLGradient *g = glAllocateGradient(NULL, 2);

    g->colors[0].pixels = 6;
    g->colors[0].color = 0xFF000000;

    g->colors[1].pixels = 0;
    g->colors[1].color = 0x50FFFFFF;


    glCtxDrawGradient(glActiveContext(), realRect().x(), realRect().y()-6, realRect().w(), 6, 3, g);

    glDestroyGradient(g);


    glSetPen(0xFF000000);
    glDrawFilledRectange(realRect().x(), realRect().y(), realRect().x2(), realRect().y2());

    /*glSetPen(0xFFFFFFFF);
    glDrawRectange(realRect().x(), realRect().y(), realRect().x2(), realRect().y2());*/

    Widget::paintEvent();
}


void Keyboard::touchEvent(int action, int x, int y)
{
    Widget::touchEvent(action, x, y);
}


void Keyboard::show()
{
    if(!isHidden())
        return;

    m_timer.start(10);
    m_animation_type = 1;

    move(parent()->rect().x(), parent()->rect().y2());
    Widget::show();

    m_showAction.trigger(this);
}


void Keyboard::hide()
{
    if(isHidden())
        return;

    m_timer.start(10);
    m_animation_type = 2;

    m_hideAction.trigger(this);
}



void Keyboard::effectHandler(Timer *)
{
    if(m_animation_type == 1) {
        move(parent()->rect().x(), rect().y()-18);

        if(m_lastRect.y() >= rect().y()) {
            m_timer.stop();
            m_animation_type = 0;
        }

    } else if(m_animation_type == 2) {
        move(parent()->rect().x(), rect().y()+18);

        if(m_lastRect.y2() <= rect().y()) {
            Widget::hide();
            m_timer.stop();
            m_animation_type = 0;
        }
    }

    eventManager()->updateAfterEvent();
}


