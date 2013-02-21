#ifndef GLOBALMENU_H
#define GLOBALMENU_H

#include <EventManager.h>
#include "UActiveArea.h"
#include <ActiveList.h>
#include "png_ops.h"
#include <string>
#include <sigc++/sigc++.h>
#include <ListMenu.h>


class GlobalMenu;

class GlobalMenuItem : public ListMenuItem
{
public:
    GlobalMenuItem(GlobalMenu *parent, int w, int h, const std::string &text);

    void paintEvent();
    inline void setLighting(bool is) {
        _light = is;
    }

private:
    bool _light;
};


class GlobalMenu : public ListMenu
{
public:
    GlobalMenu(UActiveArea *parent, const Rect &r, EventManager *e, bool blockable = true);
    ~GlobalMenu();

    GlobalMenuItem *pushBack(GlobalMenuItem *m);
    void paintEvent();

    int offsetX() const {
        return _offset_x;
    }

    int offsetY() const {
        return _offset_y;
    }

private:
    bool last_light;
    int _offset_x, _offset_y;
};




#endif // GLOBALMENU_H
