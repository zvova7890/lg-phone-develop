#include "ProgressDialog.h"
#include "main.h"




ProgressDialog::ProgressDialog(UActiveArea *parent, const Rect &r, bool blockable) :
    UActiveAreaItem<ActiveAreaItem>(parent, r, blockable),
    m_fullProgress(0),
    m_progress(0),
    m_maxFullProgress(0),
    m_maxProgress(0)
{
    m_background = &resourceManager().image("progress");
}


void ProgressDialog::paintEvent()
{
    if(!m_background->isEmpty()) {
        drawImage(rect().x(), rect().y(), m_background);
    }

    glDrawString(m_progressName.c_str(), rect().x()+2, rect().y()+1, rect().x2()-2, rect().y()+20,
                 15, FT_TEXT_H_CENTER, 0, 128);


    char info[56];
    sprintf(info, "%d/%d", m_fullProgress, m_maxFullProgress);

    glDrawString(info, rect().x()+2, rect().y()+1, rect().x2()-2, rect().y()+20,
                 15, FT_TEXT_H_CENTER | FT_TEXT_W_RIGHT, 0, 128);

    glSetPen(0xFFFFFFFF);
    glDrawString(m_whatDoing.c_str(), rect().x()+2, rect().y()+23, rect().x2()-2, rect().y()+23+22,
                 15, FT_TEXT_W_CENTER | FT_TEXT_H_DOWN | FT_TEXT_CENTER_BY_XSTART, 0, 128);

    int y = rect().y()+60;

    int percent_full = m_fullProgress*100/m_maxFullProgress;
    int percent = m_progress*100/m_maxProgress;

    int max_w = rect().w()-10;
    int full_x = max_w*percent_full/100;
    int cur_x = max_w*percent/100;


    glSetPen(0xFFFF0000);
    glDrawRectange(rect().x()+4, y, rect().x2()-6, y+4);

    if(full_x < 1)
        full_x = 0;
    if(full_x > max_w)
        full_x = max_w;

    glSetPen(0xFFFFFFFF);
    glDrawFilledRectange(rect().x()+5, y+1, rect().x()+5+full_x, y+4);


    y += 10;

    glSetPen(0xFFFF0000);
    glDrawRectange(rect().x()+4, y, rect().x2()-6, y+4);

    if(cur_x < 1)
        cur_x = 0;
    if(cur_x > max_w)
        cur_x = max_w;

    glSetPen(0xFFFFFFFF);
    glDrawFilledRectange(rect().x()+5, y+1, rect().x()+5-1+cur_x, y+4);
}


void ProgressDialog::touchEvent(int action, int x, int y)
{

}


void ProgressDialog::show()
{
    _parent->pushFront(this);
}


void ProgressDialog::hide()
{
    _parent->pop(this);
}

