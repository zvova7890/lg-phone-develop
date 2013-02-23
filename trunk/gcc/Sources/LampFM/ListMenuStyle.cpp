#include "ListMenuStyle.h"




ListMenuStyle::ListMenuStyle() :
    _background(GLColor(0xF7000000)),
    _shadow(GLColor(0xF7FFFFFF)),
    //_line_selected(GLColor(0x4FFF0000)),
    _line_long_selected(GLColor(0x4FFF00FF)),

    _separator(0xFF332828),
    _list_text(0xFFFFFFFF),
    _pressed_text(0xFFFFFFFF),
    _long_pressed_text(0xFFFFFFFF),
    _header_text(0xFF9FFFFF),

    _list_r(0, 0, 230, 300),
    _size(10, 60, 230, 300)
{

    _line_selected = Brush( [](Brush &, const Rect & rect) {

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
            glDrawHLine(rect.x(), rect.x2(), rect.y()+i);
        }

    });

}


ListMenuStyle::~ListMenuStyle()
{

}
