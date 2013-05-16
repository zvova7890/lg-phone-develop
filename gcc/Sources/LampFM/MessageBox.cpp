
#include <gl.h>
#include <Core/Timer.h>
#include "MessageBox.h"



MessageBox::MessageBox(Widget *parent, const std::string &text) :
    PopupWindow(parent),
    m_text(text),
    m_okButton(Rect(), this, "ok")
{
    int w = rect().w()*60 / 100;

    m_okButton.setSize(Rect((rect().w()-w)/2, rect().h()-43, w, 40));
    m_okButton.show();

    m_okButton.releasedSignal().connect( [this](Button *b) {

        if(b->isTouched() && !b->isMoved())
            deleteLater();
    });


    timer.timerEventSignal().connect( [this](Timer *t) {
        t->stop();
        deleteLater();
    });

    //timer.start(1000);
}


MessageBox::~MessageBox()
{

}


void MessageBox::paintEvent()
{
    glSetPen(0xF0000000);
    glDrawFilledRectange(realRect().x()+1, realRect().y()+1, realRect().x2(), realRect().y2());
    glSetPen(0xFFFFFFFF);
    glDrawRectange(realRect().x(), realRect().y(), realRect().x2(), realRect().y2());

    glSetPen(0xFFFFFFFF);
    glDrawString(m_text.c_str(), realRect().x()+2, realRect().y()+4, realRect().x2()-4, realRect().y2()-60, 23,
                 FT_TEXT_W_CENTER | FT_TEXT_SENTENCEBREAK | FT_TEXT_H_CENTER, 0, 256);


    Widget::paintEvent();
}


void MessageBox::touchEvent(int action, int x, int y)
{
    Widget::touchEvent(action, x, y);
}


void MessageBox::resizeEvent()
{
    PopupWindow::resizeEvent();

    int w = rect().w()*60 / 100;
    m_okButton.setSize(Rect((rect().w()-w)/2, rect().h()-45, w, 40));
}


