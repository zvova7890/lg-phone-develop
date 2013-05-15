
#include <Core/Rect.h>
#include <Widget/Button.h>
#include "ButtonStyle.h"





ButtonStyle::ButtonStyle() :
    m_textColor(0xFFFFFFFF)
  , m_pressedTextColor(0xFFFFFFFF)
  , m_fontFlags( FT_TEXT_H_CENTER | FT_TEXT_W_CENTER )
  , m_background(0xFF000000)
  , m_pressedBackground(0xFF2f2f2f)
  , m_border(0xFFFFFFFF, false)
  , m_pressedBorder(0xFF000000, false)
  , m_pressedTextOffset(2, 2)
  , m_roundedRect(false)
  , m_shadowAfterBackground(false)
  , m_fontSize(15)
{

    /*m_background = Brush( [](Brush &, const Rect &r) {
        //
        GLGradient g;
        glAllocateGradient(&g, 2);

        g.colors[0].color = 0xFF2d2d2d;
        g.colors[0].pixels = r.h();

        g.colors[1].color = 0xFF1d1d1d;

        glDrawGradient(r.x(), r.y(), r.w(), r.h(), 2, &g);
    });


    m_pressedBackground = Brush( [](Brush &, const Rect &r) {
        //
        GLGradient g;
        glAllocateGradient(&g, 2);

        g.colors[0].color = 0xFF4d4d4d;
        g.colors[0].pixels = r.h();

        g.colors[1].color = 0xFF2d2d2d;

        glDrawGradient(r.x(), r.y(), r.w(), r.h(), 2, &g);
    });*/

}
