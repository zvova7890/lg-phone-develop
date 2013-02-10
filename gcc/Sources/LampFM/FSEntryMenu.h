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

    void setFSEntryInfo(const FSEntryInfo &i) {
        _fsinfo = i;
    }

    void paintEvent();
    void touchEvent(int action, int x, int y);

    FSEntryInfo & fsEntryInfo() {
        return _fsinfo;
    }

private:
    bool _loaded;
    image_t background;
    int _last_y, _last_h;
    FSEntryInfo _fsinfo;
};

#endif // FSENTRYMENU_H
