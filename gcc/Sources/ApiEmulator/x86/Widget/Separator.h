#ifndef SEPARATOR_H
#define SEPARATOR_H


#include "Widget/Widget.h"



class Separator : public Widget
{
public:
    enum {
        Vertical = 1,
        Horizontal
    }Type;

public:
    Separator(const Rect &r, Widget *parent, int type = Horizontal);


    void paintEvent();

    void setColor(unsigned int color) {
        m_color = color;
    }

    void setSeparatorSize(const Rect &r) {
        m_size = r;
    }

private:
    std::function <void(Separator *)> m_paintHandler;
    int m_type;
    unsigned int m_color;
    Rect m_size;
};

#endif // SEPARATOR_H
