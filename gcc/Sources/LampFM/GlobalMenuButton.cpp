#include "GlobalMenuButton.h"
#include "main.h"



GlobalMenuButton::GlobalMenuButton(const Rect &r, Widget *parent) :
    Widget(r, parent),
    m_borderImg(0)
{

}


void GlobalMenuButton::paintEvent()
{
    int x = rect().x(),
        y = rect().y();

    //if(m_borderImg)
        //drawImage(x, y, m_borderImg);
    //else
    {
        GLGradient g;
        glAllocateGradient(&g, 4);

        int part = realRect().h()/3;

        g.colors[0].color = 0xFF2c2c2c;
        g.colors[0].pixels = part;

        g.colors[1].color = 0xFF000000;
        g.colors[1].pixels = part;

        g.colors[2].color = 0xFF000000;
        g.colors[2].pixels = part;

        g.colors[3].color = 0xFF2c2c2c;

        glDrawGradient(realRect().x(), realRect().y(), realRect().w(), realRect().h(), 2, &g);
        glDestroyGradient(&g);
    }


    int center = realRect().w()/2;
    int vw = 4;
    int vh = 8;

    center -= vw/2;

    glSetPen(0xFFFFFFFF);
    glDrawHLine(center, center+vw, realRect().y2() - vh - 1);
    glDrawHLine(center, center+vw, realRect().y2() - vh - 1+3);


    glDrawVLine(realRect().y2() - vh - 1, realRect().y2() - 3 - 1, center);
    glDrawVLine(realRect().y2() - vh - 1, realRect().y2() - 3 - 1, center+vw);

    glDrawLine(center, realRect().y2() - 3 - 1, center+vw/2, realRect().y2() - 1);
    glDrawLine(center+vw, realRect().y2() - 3 - 1, center+vw/2, realRect().y2() - 1);



    char extra_info[256];

    glSetPen(0xFFFFFFFF);
    glDrawString(m_directory.c_str(), x+2, y+2, x+rect().w()-2, y+35-2, 15, FT_TEXT_H_UP, 0, 100500);

    sprintf(extra_info, "%d", m_workpace);
    glDrawString(extra_info, x+2, y+2, x+rect().w()-1, y+35-2, 15, FT_TEXT_H_UP | FT_TEXT_W_RIGHT, 0, 100500);

    sprintf(extra_info, "Files: %d Dirs: %d", m_filesCount, m_dirsCount);
    glDrawString(extra_info, x+2, y+2, x+rect().w()-2, y+35-2, 13, FT_TEXT_H_DOWN, 0, 100500);

    sprintf(extra_info, "%d/%d", m_line, m_entries);
    glDrawString(extra_info, x+2, y+2, x+rect().w()-2, y+35-2, 13, FT_TEXT_H_DOWN | FT_TEXT_W_RIGHT, 0, 100500);


    /*if(isTouched()) {
        glSetPen(0x4F000000);
        glDrawFilledRectange(rect().x(), rect().y(), rect().x2(), rect().y2());
    }*/
}


void GlobalMenuButton::touchEvent(int action, int x, int y)
{
    m_move.trigger(this, action, x, y);
}



