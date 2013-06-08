
#include <Button.h>
#include "GlobalIconMenu.h"
#include <functional>
#include "main.h"



GlobalIconMenu::GlobalIconMenu(const Rect &r, Widget *parent) :
    Widget(r, parent),
    m_scroll1(Rect(0, 3, r.w(), r.h()-3), ScrollList::Horizontal, this)
{
    m_style.setBorder(Brush());
    m_style.setPressedBorder(Brush());
    m_style.setPressedBackground(Brush());
    m_style.setBackground(Brush());
    m_style.setTextColor(0xFF00FF00);
    m_style.setFontSize(9);

    m_style.setFontFlags( FT_TEXT_W_CENTER | FT_TEXT_H_DOWN | FT_TEXT_NOCALC_HCENTER );

    m_scroll1.show();

    m_xpos = 5;
}



GlobalIconMenu::~GlobalIconMenu()
{
    for(Widget *i : m_scroll1.items()) {
        delete i;
    }
}


void GlobalIconMenu::buttonTextRender(Button *b)
{
    int off_x = 0, off_y = 0;
    if(b->isTouched()) {
        glSetPen( b->style().pressedTextColor() );
        off_x = b->style().pressedTextOffset().x();
        off_y = b->style().pressedTextOffset().y();

    } else {
        glSetPen( b->style().textColor() );
    }

    glDrawString(b->constText().c_str(), b->realRect().x()+off_x, b->realRect().y()+off_y,
                 b->realRect().x2(), b->realRect().y2()+b->style().fontSize(),
                 b->style().fontSize(), b->style().fontFlags(), 0, 128);

}


Button *GlobalIconMenu::addIcon(int row, const std::string &n, Image *i, const std::function<void(Button*)> &f)
{
    Button *b = new Button(Rect(0, 0, i->width()+8, i->height()), this, n);
    //b->setTextVisible(false);
    b->setTextRender( std::bind(&GlobalIconMenu::buttonTextRender, this, std::placeholders::_1) );

    b->setStyle(m_style);
    b->setIcon( i );
    b->releasedSignal().connect(f);


    ScrollList *scroll = 0;
    scroll = &m_scroll1;


    if(scroll) {
        scroll->addItem(b);
        scroll->setLinesCount( scroll->items().size() );
    }
    //m_xpos += i->width()+8;

    return b;
}


void GlobalIconMenu::paintEvent()
{
    glSetPen(0xFF000000);
    glDrawFilledRectange(realRect().x(), realRect().y(), realRect().x2(), realRect().y2());

    Widget::paintEvent();
}


void GlobalIconMenu::touchEvent(int action, int x, int y)
{
    Widget::touchEvent(action, x, y);
}


void GlobalIconMenu::resizeEvent()
{
    Widget::resizeEvent();

    m_scroll1.setSize(Rect(0, 3, rect().w(), rect().h()-3));

    m_scroll1.fixupViewPosition();
}


bool GlobalIconMenu::hide()
{
    m_hideAction.trigger(this);
    return Widget::hide();
}


bool GlobalIconMenu::show()
{
    return Widget::show();
}


