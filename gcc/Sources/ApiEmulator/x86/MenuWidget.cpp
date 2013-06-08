
#include <Core/ResourceManager.h>
#include "MenuWidget.h"
#include "cmd.h"





MenuWidget::MenuWidget(const Rect &r, Widget *p) :
    Widget(r, p),
    m_list(Rect(1, 70, r.w()-2, r.h()-70), this),
    m_back(Rect(r.w()-30, 30, 35, 28), this, "<-")
{
    res_manager = (ResourceManager*)rootParent()->providesExtraExtension("resource");

    m_list.style().setHeaderSize(Rect());
    m_list.style().setListSize(Rect(Point(), m_list.rect().wh()));
    m_list.style().setSize(Rect(Point(), m_list.rect().wh()));
    m_list.style().setShadow(Brush());

    m_back.triggeredSignal().connect([this](Button *) {
        eventManager()->notifyAfterEvent( [&]() {
            close();
            m_closing.trigger(this);
            delete this;
        });
    });

    m_list.show();
    m_back.show();
}


MenuWidget::~MenuWidget() {
    auto its = m_list.scrollArea().items();
    for(auto w: its)
        delete w;
}



void MenuWidget::addItem(Image *icon, const std::string &name, std::function<void ()> f)
{
    ListMenuItem *it;
    m_list.scrollArea().addItem( it = new ListMenuItem(&m_list, m_list.rect().w(), 43, name) );
    it->style().setFontSize(17);
    it->setIcon(icon);
    it->onReleasedSignal().connect( [f](ListMenuItem *) {
        f();
    });

    m_list.scrollArea().setLinesCount(m_list.scrollArea().items().size());
}


void MenuWidget::paintEvent()
{
    glClear(0xFF000000);

    glSetPen(0xFFFFFFFF);
    glDrawString(m_name.c_str(), realRect().x(), realRect().y()+30, realRect().x2()-30, realRect().y()+65,
                 25, FT_TEXT_W_CENTER | FT_TEXT_H_CENTER, 0, 128);


    glSetPen(0xFF334452);
    glDrawHLine(realRect().x(), realRect().x2(), realRect().y()+60);

    Widget::paintEvent();
}

