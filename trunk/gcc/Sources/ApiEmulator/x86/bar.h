#ifndef BAR_H
#define BAR_H

#include <Widget/Widget.h>
#include <Graph/Image.h>
#include <vector>
#include <Core/Timer.h>


class Bar : public Widget
{
public:
    typedef signal_slot::multi_signal<Bar*, int> signal;

    Bar(const Rect &r, Widget *parent);


    void paintEvent();
    void touchEvent(int action, int x, int y);


    signal &changeBarAction() {
        return m_changeBarAction;
    }

protected:
    void switchTab(int tab);
    void animation(Timer *);

private:
    signal m_changeBarAction;
    int m_animationYPos;
    int m_selected;
    Image *m_bar, *m_selectedIcon;
    std::vector<Image> m_icons;
    Timer m_animation;
};

#endif // BAR_H
