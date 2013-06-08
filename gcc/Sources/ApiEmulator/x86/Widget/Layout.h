#ifndef LAYOUT_H
#define LAYOUT_H


#include <Widget/Widget.h>
#include <functional>
#include <list>


class Layout
{
public:
    Layout();


    void addLayout(Widget *w, std::function<void(Widget*)> p);
    void layout();

private:

    class LayoutItem
    {
    public:

        LayoutItem(Widget *w, std::function <void(Widget*)> & pf) {
            widget = w;
            p = pf;
        }

        Widget *widget;
        std::function<void(Widget*)> p;
    };

    std::list <LayoutItem> m_list;
};

#endif // LAYOUT_H
