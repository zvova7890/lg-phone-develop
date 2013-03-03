#include "GlobalMenuButton.h"
#include "main.h"



GlobalMenuButton::GlobalMenuButton(UActiveArea *parent, const Rect &r, bool blockable) :
    UButton(parent, r, blockable),
    m_borderImg(0)
{

}


void GlobalMenuButton::paintEvent()
{
    int x = rect().x(),
        y = rect().y();

    drawImage(x, y, m_borderImg);

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

