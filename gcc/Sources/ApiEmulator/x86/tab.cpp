
#include <Widget/Button.h>
#include "tab.h"




Tab::Tab(const Rect &r, Widget *parent) :
    Widget(r, parent),
    buttons(0),
    m_rat(r)
{

    m_animation.timerEventSignal().connect( [this](Timer *) {
        int x = rect().x();
        moveX(x+39);

        if(rect().x() >= m_rat.x()) {
            setSize(m_rat);
            m_animation.stop();
        }

        eventManager()->updateAfterEvent();
    });
}


Tab::~Tab()
{
    auto ch = childs();
    for(Widget *w : ch)
        delete w;
}



void Tab::addButton(Image *icon, const std::string &text, std::function<void(Tab*, Button *)> f)
{
    float step_x = 4;
    float step_y = 15;
    float width = (rect().w() - step_x*3 )/2;
    float height = (rect().h() - step_y*5 - 15 )/4;


    auto calcCoords = [=](int at) {
        Point p;
        if(!((at+1) % 2)) {
            p.setX(width + step_x*2);
            p.setY(step_y + height * (at/2) + step_y*(at/2));
        } else {
            p.setX(step_x);
            p.setY(step_y + height * (at/2) + step_y*(at/2));
        }

        return p;
    };


    Button *b = new Button( Rect(calcCoords(buttons), Point(width, height)), this, text);
    b->style().setPressedBackground(Brush());
    b->style().setBackground(Brush());
    b->style().setPressedBorder(Brush());
    b->style().setBorder(Brush());
    b->style().setAlighIcon((1 << 1));
    b->style().setFontSize(10);
    b->style().setFontFlags(FT_TEXT_W_CENTER | FT_TEXT_H_DOWN);
    b->setIcon(icon);

    b->triggeredSignal().connect([this, f](Button *b) {
        f(this, b);
    });

    b->show();

    buttons++;
}


bool Tab::show()
{
    moveX( -m_rat.w() );

    m_animation.start(1);

    return Widget::show();
}
