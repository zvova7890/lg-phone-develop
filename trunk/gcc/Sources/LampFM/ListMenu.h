#ifndef LISTMENU_H
#define LISTMENU_H


#include "UActiveArea.h"
#include "ActiveList.h"
#include <sigc++/sigc++.h>
#include <signals/signal.h>
#include <string>
#include <png_ops.h>



class ListMenu;

class ListMenuItem : public ActiveListItem
{
public:
    ListMenuItem(ListMenu *parent, int w, int h, const std::string &text);

    void paintEvent();
    void touchEvent(int action, int x, int y);


    signal_slot::multi_signal<void(ListMenuItem*)> & onPressedSignal() {
        return _pressed;
    }

    signal_slot::multi_signal<void(ListMenuItem*)> & onReleasedSignal() {
        return _released;
    }

    void setText(const std::string &text) {
        _text = text;
    }

protected:
    //sigc::signal <void, ListMenuItem *> _pressed, _released;
    signal_slot::multi_signal<void(ListMenuItem*)> _pressed, _released;
    std::string _text;
};


class ListMenu : public ActiveList
{
public:
    typedef signal_slot::multi_signal<void(ListMenu*)> signal;

    ListMenu(UActiveArea *parent, const Rect &r, EventManager *e, bool blockable = true);
    ~ListMenu();

    void paintEvent();
    void touchEvent(int action, int x, int y);

    void show(int after = 0);
    void hide();
    void setBackgroundColor(GLColor color);
    void setItemLineColor(GLColor color);
    void setPressedLineColor(GLColor color);
    void setItemTextColor(GLColor color);

    inline signal & onHideSignal() {
        return _on_hide;
    }

    inline signal & onShowSignal() {
        return _on_show;
    }

    inline signal & onOffScreenTouch() {
        return _on_offsreen_touch;
    }

protected:
    //sigc::signal <void, ListMenu *> _on_hide, _on_show;
    signal _on_hide, _on_show, _on_offsreen_touch;
    UActiveArea *_parent;

public:
    GLColor _background, _iline, _ilinepressed, _ilinetext;
};


#endif // LISTMENU_H
