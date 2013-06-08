#include "Layout.h"



Layout::Layout()
{

}



void Layout::addLayout(Widget *w, std::function<void(Widget *)> p)
{
    m_list.push_back(LayoutItem(w, p));
}


void Layout::layout()
{
    for(LayoutItem &li : m_list)
    {
        li.p(li.widget);
    }
}

