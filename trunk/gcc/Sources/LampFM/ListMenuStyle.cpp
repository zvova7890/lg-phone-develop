#include "ListMenuStyle.h"




ListMenuStyle::ListMenuStyle() :
    _background(GLColor(0xF7000000)),
    _shadow(GLColor(0xF7FFFFFF)),
    _line_selected(GLColor(0x4FFF0000)),
    _line_long_selected(GLColor(0x4FFF00FF)),

    _separator(0xFF332828),
    _list_text(0xFFFFFFFF),
    _pressed_text(0xFFFFFFFF),
    _long_pressed_text(0xFFFFFFFF),
    _header_text(0xFF9FFFFF),

    _list_r(10, 60, 230, 300),
    _size(10, 60, 230, 300)
{

}


ListMenuStyle::~ListMenuStyle()
{

}
