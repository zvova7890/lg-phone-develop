
#include <Rect.h>
#include <Button.h>
#include "ButtonStyle.h"





ButtonStyle::ButtonStyle() :
    m_textColor(0xFFFFFFFF)
  , m_pressedTextColor(0xFFFFFFFF)
  , m_background(0xFF2f2f2f)
  , m_pressedBackground(0xFF2f2f2f)
  , m_border(0xFFFFFFFF, false)
  , m_pressedBorder(0xFF000000, false)
{

    m_border = Brush( [](Brush &, const Rect &r) {
        //
            glSetPen(0xFFa29f9f);

            int round = Button::roundRect(r.w());

            glDrawRoundedRect(r.x(), r.y(), r.w()-2, r.h()-2, round, round);
    });


    m_pressedBorder = Brush( [](Brush &, const Rect &r) {
        //
            glSetPen(0xFFa29f9f);

            int round = Button::roundRect(r.w());

            glDrawRoundedRect(r.x()+1, r.y()+1, r.w()-1, r.h()-1, round, round);
    });

}
