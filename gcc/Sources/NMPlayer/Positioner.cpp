
#include <pxeapi.h>
#include <gl.h>
#include "Positioner.h"



Positioner::Positioner(const Rect &r, Widget *parent) :
    Widget(r, parent)
{

}


void Positioner::paintEvent()
{
    char txt[128];
    int sec =  m_pos / 1000;
    sprintf(txt, "%02d.%02d", sec / 60, sec % 60);

    int w = glStringMetrics(13, txt, 0, 0, 12);

    int info_w = w + 8;
    int pwidth = realRect().w() - info_w*2;


    glSetPen(0xFFFFFFFF);

    glDrawString(txt, realRect().x(), realRect().y(), realRect().x2(), realRect().y2(), 13,
                 FT_TEXT_H_CENTER | FT_TEXT_NOCALC_HCENTER, 0, 128);


    if(m_lenght < m_pos)
        m_pos = m_lenght;



    sec =  m_lenght / 1000;
    sprintf(txt, "%02d.%02d", sec / 60, sec % 60);
    glDrawString(txt, realRect().x()+info_w+pwidth + (info_w-w), realRect().y(), realRect().x2(), realRect().y2(), 13,
                 FT_TEXT_H_CENTER | FT_TEXT_NOCALC_HCENTER, 0, 128);



    band = Rect(info_w, rect().y(), pwidth, rect().h());


    //glDrawRectange(realRect().x(), realRect().y(), realRect().x2(), realRect().y2());

    glDrawHLine(realRect().x()+info_w, realRect().x()+info_w+pwidth, realRect().y() + realRect().h()/2);


    float xpos;
    if(m_lenght > 0) {
        float perc = (float)m_pos * 100.0f / m_lenght;
        if(perc > 100.0f) {
            //printf("perc > 100 o_O\n");
            perc = 100.0f;
        }

        xpos = ((float)pwidth) * perc / 100.0f;
    } else
        xpos = 0;

    //glDrawVLine(rect().y(), rect().y2(), rect().x()+xpos);
    glDrawCircle(realRect().x() + info_w +xpos, realRect().y()+rect().h()/2, 7);
}


void Positioner::touchEvent(int action, int x, int y)
{
    if(action == TOUCH_ACTION_RELEASE)
    {
        int l = x-(realRect().x() + band.x());
        int percent = l*100 / band.w();

        m_positionSelected.trigger(percent);
    }
}


void Positioner::setPosition(int p)
{
    m_pos = p;
}


void Positioner::setLength(int l)
{
    m_lenght = l;
}
