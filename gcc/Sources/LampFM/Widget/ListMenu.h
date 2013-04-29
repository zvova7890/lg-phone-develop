#ifndef LISTMENU_H
#define LISTMENU_H


#include <VScrollArea.h>
#include "ListMenuStyle.h"
#include <HTextScroller.h>
#include <Graph/Brush.h>
#include <signals/signal.h>
#include <string>
#include <png_ops.h>



class ListMenu;

class ListMenuItem : public Widget
{
public:
    ListMenuItem(ListMenu *parent, int w, int h, const std::string &text);
    virtual ~ListMenuItem();

    void paintEvent();
    void touchEvent(int action, int x, int y);


    typedef signal_slot::multi_signal<ListMenuItem*> signal;

    signal & onPressedSignal() {
        return _pressed;
    }

    signal & onReleasedSignal() {
        return _released;
    }

    void setText(const std::string &text) {
        m_text = text;
    }

    ListMenu *parent() {
        return (ListMenu*)Widget::parent();
    }

    ListMenuItemStyle & style() {
        return _style;
    }

    void setStyle(const ListMenuItemStyle & style) {
        _style = style;
    }


    bool isActive() const {
        return m_isActive;
    }

    void setActive(bool is = true) {
        m_isActive = is;
    }

protected:
    ListMenuItemStyle _style;
    signal _pressed, _released;
    std::string m_text;
    bool m_isActive;
};


class ListMenu : public Widget
{

public:
    friend class ListMenuItem;

    typedef signal_slot::multi_signal<ListMenu*> signal;

    ListMenu(Widget *parent, const Rect &r);
    ~ListMenu();

    void paintEvent();
    void touchEvent(int action, int x, int y);

    void show();
    void hide();
    void close();

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

    inline void setHeaderScrollable(bool is) {
        m_headerTextScrollable = is;
    }

    inline VScrollArea & scrollArea() {
        return m_scroll;
    }

    inline bool isModal() const {
        return m_isModal;
    }

    inline void setModal(bool is) {
        m_isModal = is;
    }

protected:
    signal _on_hide, _on_show, _on_offsreen_touch;

private:
    VScrollArea m_scroll;
    //Widget m_header;
    ListMenuStyle _style;
    std::string _head_text;
    HTextScroller m_scroller;

    bool m_headerTextScrollable;
    bool m_isModal;

public:
    GLColor _background, _iline, _ilinepressed, _ilinetext;

};


#endif // LISTMENU_H
