#include <gl.h>
#include "ProgressDialog.h"
#include "main.h"




ProgressDialog::ProgressDialog(Widget *parent, const Rect &r) :
    Widget(r, parent),
    m_cancelButton(Rect(rect().w()/2-95/2, 95, 100, 40), this, "Cancel"),
    m_fullProgress(0),
    m_progress(0),
    m_maxFullProgress(0),
    m_maxProgress(0)
{
    m_background = &resourceManager().image("progress");

    m_cancelButton.releasedSignal().connect( [this](Button *self) {

        if(self->isTouched() && !self->isMoved())
            m_onCancelPressed.trigger(self);
    });

    add(&m_cancelButton);
}


ProgressDialog::~ProgressDialog()
{

}


void ProgressDialog::paintEvent()
{
    if(!m_background->isEmpty()) {
        drawImage(realRect().x(), realRect().y(), m_background);
    }

    glDrawString(m_progressName.c_str(), realRect().x()+2, realRect().y()+1, realRect().x2()-2, realRect().y()+20,
                 15, FT_TEXT_H_CENTER, 0, 128);


    char info[56];
    sprintf(info, "%d/%d", m_fullProgress, m_maxFullProgress);

    glDrawString(info, realRect().x()+2, realRect().y()+1, realRect().x2()-2, realRect().y()+20,
                 15, FT_TEXT_H_CENTER | FT_TEXT_W_RIGHT, 0, 128);

    glSetPen(0xFFFFFFFF);
    glDrawString(m_whatDoing.c_str(), realRect().x()+2, realRect().y()+23, realRect().x2()-2, realRect().y()+23+22,
                 15, FT_TEXT_W_CENTER | FT_TEXT_H_DOWN | FT_TEXT_CENTER_BY_XSTART, 0, 128);

    int y = realRect().y()+60;

    int percent_full = m_fullProgress*100/m_maxFullProgress;
    int percent = m_progress? m_progress*100/m_maxProgress : 0;

    int max_w = realRect().w()-10;
    int full_x = max_w*percent_full/100;
    int cur_x = max_w*percent/100;


    glSetPen(0xFFFF0000);
    glDrawRectange(realRect().x()+4, y, realRect().x2()-6, y+4);

    if(full_x < 1)
        full_x = 0;
    if(full_x > max_w)
        full_x = max_w;

    glSetPen(0xFFFFFFFF);
    glDrawFilledRectange(realRect().x()+5, y+1, realRect().x()+5+full_x, y+4);


    y += 10;

    glSetPen(0xFFFF0000);
    glDrawRectange(realRect().x()+4, y, realRect().x2()-6, y+4);

    if(cur_x < 1)
        cur_x = 0;
    if(cur_x > max_w)
        cur_x = max_w;

    glSetPen(0xFFFFFFFF);
    glDrawFilledRectange(realRect().x()+5, y+1, realRect().x()+5-1+cur_x, y+4);

    Widget::paintEvent();
}


void ProgressDialog::touchEvent(int action, int x, int y)
{
    Widget::touchEvent(action, x, y);
}

