#ifndef UBUTTONSTYLE_H
#define UBUTTONSTYLE_H


#include <gl.h>
#include <Graph/Brush.h>

#define getset(type, visible1, name1, visible2, name2) \
    private:   type m_##name2; \
    visible2: type &name2() { return m_##name2; } \
    visible1: void set##name1(const type &t) { m_##name2 = t; }



class Button;

class ButtonStyle
{
public:
    ButtonStyle();


    ButtonStyle & setTextColor(GLColor color) {
        m_textColor = color;
        return *this;
    }

    GLColor textColor() const {
        return m_textColor;
    }

    ButtonStyle & setPressedTextColor(GLColor color) {
        m_pressedTextColor = color;
        return *this;
    }

    GLColor pressedTextColor() const {
        return m_pressedTextColor;
    }

    void setFontFlags(int flags) {
        m_fontFlags = flags;
    }

    int fontFlags() const {
        return m_fontFlags;
    }

private:
    friend class Button;
    GLColor m_textColor, m_pressedTextColor;
    int m_fontFlags;



    getset(Brush, public, Background, public, background)
    getset(Brush, public, PressedBackground, public, pressedBackground)
    getset(Brush, public, Border, public, border)
    getset(Brush, public, PressedBorder, public, pressedBorder)
    getset(Point, public, PressedTextOffset, public, pressedTextOffset)
    getset(bool, public, RoundedRect, public, roundedRect)
    getset(bool, public, ShadowAfterBackground, public, shadowAfterBackground)
    getset(int, public, FontSize, public, fontSize)
    getset(Brush, public, InactiveFill, public, inactiveFill)
    getset(int, public, AlighIcon, public, alighIcon)
    getset(Point, public, IconOffset, public, iconOffset)

};

#endif // UBUTTONSTYLE_H
