
#include <pxeapi.h>
#include <Core/ResourceManager.h>
#include "bar.h"



Bar::Bar(const Rect &r, Widget *parent) :
    Widget(r, parent),
    m_selected(0)
{
    ResourceManager *res = (ResourceManager*)rootParent()->providesExtraExtension("resource");

    if(res) {
        m_bar = res? &res->image("bar") : 0;
        m_selectedIcon = res? &res->image("selected") : 0;
        m_animationYPos = -m_selectedIcon->width();

        const char *icons[] = {"bar_calls", "bar_media", "bar_tools", "bar_settings", "bar_apps"};
        for(int i=0; i<5; ++i) {
            m_icons.push_back(res->image(icons[i]));
        }
    }


    m_animation.timerEventSignal().connect(this, &Bar::animation, std::placeholders::_1);
}



void Bar::paintEvent()
{
    drawImage(realRect().x(), realRect().y(), m_bar);

    float height = realRect().h()/5;

    int cx, cy;

    for(int i = 0; i<m_icons.size(); ++i) {
        Image &img = m_icons.at(i);

        if(m_selected == i) {
            drawImage(realRect().x2()+m_animationYPos, realRect().y()+(height*i), m_selectedIcon);
        }

        cx = rect().w()/2 - img.width()/2;
        cy = height/2 - img.height()/2;

        drawImage(realRect().x()+cx, realRect().y()+ (height*i) + cy, &img);
    }

}


void Bar::touchEvent(int action, int x, int y)
{
    if(action == TOUCH_ACTION_RELEASE) {

        int yp = y-realRect().y();
        float height = realRect().h()/5;
        for(int i=0; i<5; ++i) {

            if(yp >= (height*i) && yp <= (height*(i+1))) {
                switchTab(i);
                break;
            }
        }
    }
}



void Bar::switchTab(int tab)
{
    if(m_selected == tab)
        return;

    m_selected = tab;
    m_animationYPos = 0;
    m_animation.start(1);

    m_changeBarAction.trigger(this, tab);
}


void Bar::animation(Timer *)
{
    m_animationYPos -= 8;
    if( (-m_animationYPos) >= m_selectedIcon->width() ) {
        m_animationYPos = -m_selectedIcon->width();
        m_animation.stop();
    }

    eventManager()->updateAfterEvent();
}

