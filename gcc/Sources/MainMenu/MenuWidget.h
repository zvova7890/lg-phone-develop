#ifndef MENUWIDGET_H
#define MENUWIDGET_H

#include <Widget/Widget.h>
#include <Widget/ListMenu.h>
#include <Widget/Button.h>
#include <signals/signal.h>

class ResourceManager;

class MenuWidget : public Widget
{
public:
    typedef signal_slot::multi_signal<MenuWidget*> signal;

    MenuWidget(const Rect &r, Widget *parent);
    ~MenuWidget();


    void setName(const std::string &n) {
        m_name = n;
    }

    void addItem(Image *icon, const std::string &name, std::function<void()> f = [](){});

    void paintEvent();

    signal &closingAction() {
        return m_closing;
    }

private:
    ResourceManager *res_manager;
    signal m_closing;
    ListMenu m_list;
    Button m_back;
    std::string m_name;
};

#endif // MENUWIDGET_H
