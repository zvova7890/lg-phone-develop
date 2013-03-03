#ifndef LISTMENU_H
#define LISTMENU_H


#include "UActiveArea.h"
#include "ActiveList.h"
#include "ListMenuStyle.h"
#include <Graph/Brush.h>
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

    ListMenu *parent() {
        return (ListMenu*)ActiveListItem::parent();
    }

    ListMenuItemStyle & style() {
        return _style;
    }

    void setStyle(const ListMenuItemStyle & style) {
        _style = style;
    }

protected:
    ListMenuItemStyle _style;
    signal_slot::multi_signal<void(ListMenuItem*)> _pressed, _released;
    std::string _text;
};


class ListMenu : public ActiveList
{
public:
    typedef signal_slot::multi_signal<void(ListMenu*)> signal;

    ListMenu(UActiveArea *parent, const Rect &r, bool blockable = true);
    ~ListMenu();

    void paintEvent();
    void touchEvent(int action, int x, int y);

    void show(int after = 0);
    void hide();

    inline signal & onHideSignal() {
        return _on_hide;
    }

    inline signal & onShowSignal() {
        return _on_show;
    }

    inline signal & onOffScreenTouch() {
        return _on_offsreen_touch;
    }

    inline ListMenuStyle & style() {
        return _style;
    }

    inline void setHeadText(const std::string &h) {
        _head_text = h;
    }

protected:

    signal _on_hide, _on_show, _on_offsreen_touch;

private:
    ListMenuStyle _style;
    std::string _head_text;

public:
    GLColor _background, _iline, _ilinepressed, _ilinetext;

};


#endif // LISTMENU_H
