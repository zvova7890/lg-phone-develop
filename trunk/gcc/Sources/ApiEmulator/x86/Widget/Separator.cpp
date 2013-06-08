

#include "Separator.h"
#include <gl.h>



Separator::Separator(const Rect &r, Widget *parent, int type) :
    Widget(r, parent),
    m_type(type),
    m_size(r)
{
    m_paintHandler = [](Separator *) { };
}



void Separator::paintEvent()
{
    m_paintHandler(this);

    glSetPen(m_color);

    switch(m_type)
    {
        case Vertical:
            if(m_size.w() < 2)
                glDrawVLine(m_size.y(), m_size.y2(), m_size.x());

            break;

        case Horizontal:
            if(m_size.h() < 2)
                glDrawHLine(m_size.x(), m_size.x2(), m_size.y());

            break;
    }
}

