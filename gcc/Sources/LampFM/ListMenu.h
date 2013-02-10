#ifndef LISTMENU_H
#define LISTMENU_H


#include "UActiveArea.h"
#include "ActiveList.h"
#include <sigc++/sigc++.h>
#include <string>
#include <png_ops.h>



class ListMenu;

class ListMenuItem : public ActiveListItem
{
public:
    ListMenuItem(ListMenu *parent, int w, int h, const std::string &text);

    void paintEvent();
    void touchEvent(int action, int x, int y);


    template <class T>
    void connectPressedSignal(T t) {
        _pressed.connect(t);
    }

    template <class T>
    void connectReleasedSignal(T t) {
        _released.connect(t);
    }

protected:
    sigc::signal <void, ListMenuItem *> _pressed, _released;
    std::string _text;
};


class ListMenu : public ActiveList
{
public:
    ListMenu(UActiveArea *parent, const Rect &r, EventManager *e);
    ~ListMenu();

    void paintEvent();
    void touchEvent(int action, int x, int y);

    void hide();
    void setBackgroundColor(GLColor color);
    void setItemLineColor(GLColor color);
    void setPressedLineColor(GLColor color);
    void setItemTextColor(GLColor color);

    template <class T>
    auto connectOnHideSignal(T t) -> sigc::signal <void, ListMenu *>::iterator {
        return _on_hide.connect(t);
    }

protected:
    sigc::signal <void, ListMenu *> _on_hide;
    UActiveArea *_parent;

public:
    GLColor _background, _iline, _ilinepressed, _ilinetext;
};


#endif // LISTMENU_H
