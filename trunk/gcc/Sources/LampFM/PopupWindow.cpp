
#include <gl.h>
#include "PopupWindow.h"


PopupWindow::PopupWindow(Widget *parent) :
    Widget(Rect(), parent)
{
    setFullScreenBlock(true);
    sizesNPositions();

    timer.timerEventSignal().connect( [this](Timer *t) {
        t->stop();
        deleteLater();
    });

    //timer.start(1000);
}


PopupWindow::~PopupWindow()
{

}


void PopupWindow::paintEvent()
{
    /*glSetPen(0xF0000000);
    glDrawFilledRectange(realRect().x()+1, realRect().y()+1, realRect().x2()-1, realRect().y2()-1);
    glSetPen(0xFFFFFFFF);
    glDrawRectange(realRect().x(), realRect().y(), realRect().x2(), realRect().y2());

    glSetPen(0xFFFFFFFF);
    glDrawString(m_text.c_str(), realRect().x()+2, realRect().y()+4, realRect().x2()-4, realRect().y2()-60, 23,
                 FT_TEXT_W_CENTER | FT_TEXT_SENTENCEBREAK | FT_TEXT_H_CENTER, 0, 256);

*/
    Widget::paintEvent();
}


void PopupWindow::touchEvent(int action, int x, int y)
{
    Widget::touchEvent(action, x, y);
}



void PopupWindow::sizesNPositions()
{
    Rect r;

    int h = parent()->rect().h() *75 / 100;
    int y = (parent()->rect().h()-h)/2;

    int w = parent()->rect().w() *85 / 100;
    int x = (parent()->rect().w()-w)/2;

    r.setY(y);
    r.setH(h);

    r.setX(x);
    r.setW(w);
    setSize(r);
}


void PopupWindow::resizeEvent()
{
    Widget::resizeEvent();

    sizesNPositions();
}


