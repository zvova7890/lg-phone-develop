#include "ListMenuStyle.h"




ListMenuStyle::ListMenuStyle() :
    _background(GLColor(0xFF000000)),
    _shadow(GLColor(0xF7FFFFFF)),
    _header_text(0xFF9FFFFF),
    _paint_first_line(false),
    _paint_last_line(false),

    _list_r(0, 0, 230, 300),
    _size(10, 60, 230, 300)
{


}


ListMenuStyle &ListMenuStyle::operator =(const ListMenuStyle &s)
{
    _background = s._background;
    _shadow = s._shadow;
    _header_text = s._header_text;
    _list_r = s._list_r;
    _header_r = s._header_r;
    _size = s._size;
    _paint_first_line = s._paint_first_line;
    _paint_last_line = s._paint_last_line;

    return *this;
}


ListMenuItemStyle::ListMenuItemStyle() :
    m_separator(0xFF332828),
    m_lineLongSelected(GLColor(0x4FFF00FF)),


    m_listText(0xFFFFFFFF),
    m_pressedText(0xFFFFFFFF),
    m_longPressedText(0xFFFFFFFF),

    m_inactiveText(0xffa3a3a3),
    m_inactivePressedText(0xffa3a3a3),
    m_inactiveLongPresedText(0xffa3a3a3),
    m_fontSize(24)
{
    m_lineSelected = Brush( [](Brush &, const Rect & rect) {

        unsigned short alpha = 0x30;
        for(int i=1; i<rect.h()/2; ++i, alpha += 4) {

            if(alpha >= 0xff) {
                alpha = 0xff;
            }

            GLColor c = ((unsigned char)alpha << 24) | 0x0000FF;
            glSetPen(c);
            glDrawHLine(rect.x(), rect.x2()-1, rect.y()+i);

        }

        for(int i=(const int)rect.h()/2; i<rect.h()-1; ++i, alpha -= 4) {
            if(alpha <= 0x20) {
                alpha = 0x20;
            }
            GLColor c =  ((unsigned char)alpha << 24) | 0x0000FF;
            glSetPen(c);
            glDrawHLine(rect.x(), rect.x2()-1, rect.y()+i);
        }
    });

    // Set the separator as gradient-line
    m_separator = Brush( [](Brush &, const Rect & rect) {
        /*const short alpha = 0xff;
        float colors = 255.0f;
        float r = rect.w() / 2;
        float sub_f = 255 / r + (r * 0.1f/100.0f);

        for(int i=r; i > 0; --i)
        {
            GLColor col = colors;
            GLColor c =  ((unsigned char)alpha << 24) | (col << 16) | (col << 8) | (col & 0xff);

            glActiveContext()->setColorPixel(glActiveContext(), rect.x()+i, rect.y(), c);

            colors -= sub_f;
            if(colors < 0)
                colors = 0;
        }


        colors = 0xff;
        for(int i=0; i < r; ++i)
        {
            GLColor col = colors;
            GLColor c =  ((unsigned char)alpha << 24) | (col << 16) | (col << 8) | (col & 0xff);

            glActiveContext()->setColorPixel(glActiveContext(), rect.x()+r+i, rect.y(), c);

            colors -= sub_f;
            if(colors < 0)
                colors = 0;
        }*/

            glSetPen(0x4FFFFFFF);
            glDrawHLine(rect.x()+4, rect.x2()-4, rect.y());

    });
}


ListMenuItemStyle &ListMenuItemStyle::operator =(const ListMenuItemStyle &s)
{
    m_separator = s.m_separator;
    m_lineSelected = s.m_lineSelected;
    m_lineLongSelected = s.m_lineLongSelected;
    m_listText = s.m_listText;
    m_pressedText = s.m_pressedText;
    m_longPressedText = s.m_longPressedText;
    m_line = s.m_line;
    return *this;
}
