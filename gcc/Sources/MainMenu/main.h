

#ifndef __MAIN_H__
#define __MAIN_H__



#include <Widget/MainWindow.h>
#include <Widget/Button.h>
#include <Widget/ListMenu.h>

#include "actionhandler.h"
#include "bar.h"
#include "tab.h"


class RootWindow : public Widget
{
public:
    RootWindow(const Rect &r, EventManager *p);
    void *providesExtraExtension(const std::string &s);
};



class MyWindow : public Widget
{
public:


    MyWindow(const Rect &r, Widget *);
    virtual ~MyWindow();

    void paintEvent();
    void touchEvent(int action, int x, int y);


    Image *background;
    Bar bar;
    Button exit;
    ActionHandler ahandler;
    std::vector<Tab *> m_tabs;
    Tab *curentTab;
};







#endif
