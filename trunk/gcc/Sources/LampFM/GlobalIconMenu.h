#ifndef GLOBALICONMENU_H
#define GLOBALICONMENU_H

#include <Widget/Widget.h>
#include <Widget/Button.h>
#include <Widget/ScrollArea.h>
#include <signals/signal.h>
#include <functional>


class GlobalIconMenu : public Widget
{
public:
    typedef signal_slot::multi_signal<GlobalIconMenu*> signal;

    GlobalIconMenu(const Rect &r, Widget *parent);
    ~GlobalIconMenu();

    Button *addIcon(int row, const std::string &n, Image *i, const std::function<void(Button*)> &f);

    void show();
    void hide();

    void paintEvent();
    void touchEvent(int action, int x, int y);
    void resizeEvent();

    signal & hideAction() {
        return m_hideAction;
    }


protected:
    void buttonTextRender(Button *b);

protected:
    signal_slot::multi_signal<GlobalIconMenu*> m_hideAction;
    ButtonStyle m_style;
    ScrollArea m_scroll1;

    int m_xpos;
};

#endif // GLOBALICONMENU_H
