#ifndef UBUTTONSTYLE_H
#define UBUTTONSTYLE_H


#include <gl.h>
#include <Graph/Brush.h>

#define getset(type, visible1, name1, visible2, name2) \
    private:   type m_##name2; \
    visible2: type &name2() { return m_##name2; } \
    visible1: void set##name1(type &t) { m_##name2 = t; }



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

    /*ButtonStyle & setBackground(const Brush &b) {
        m_background = b;
        return *this;
    }

    const Brush & background() const {
        return m_background;
    }

    ButtonStyle & setPressedBackground(const Brush &b) {
        m_pressedBackground = b;
        return *this;
    }

    const Brush & pressedBackground() const {
        return m_pressedBackground;
    }

    ButtonStyle & setBorder(const Brush &b) {
        m_border = b;
        return *this;
    }

    const Brush & border() const {
        return m_border;
    }*/



private:
    friend class Button;
    GLColor m_textColor, m_pressedTextColor;
    //Brush m_background, m_pressedBackground,
     //     m_border, m_pressedBorder;



    getset(Brush, public, Background, public, background)
    getset(Brush, public, PressedBackground, public, pressedBackground)
    getset(Brush, public, Border, public, border)
    getset(Brush, public, PressedBorder, public, pressedBorder)
};

#endif // UBUTTONSTYLE_H
