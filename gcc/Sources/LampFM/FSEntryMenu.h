#ifndef FSENTRYMENU_H
#define FSENTRYMENU_H

#include "ListMenu.h"
#include "FSEntryInfo.h"



class FSEntryMenuItem : public ListMenuItem
{
public:
    FSEntryMenuItem(ListMenu *parent, int w, int h, const std::string &text);

    void paintEvent();
};


class FSEntryMenu : public ListMenu
{
public:
    FSEntryMenu(UActiveArea *parent, const Rect &r, EventManager *e);

    void setHeadText(const std::string &text) {
        _head_text = text;
    }

    void paintEvent();
    void touchEvent(int action, int x, int y);
private:
    bool _loaded;
    image_t background;
    int _last_y, _last_h;
    std::string _head_text;
};

#endif // FSENTRYMENU_H
