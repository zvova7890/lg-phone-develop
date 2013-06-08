#include "TabBox.h"




TabBox::TabBox(const Rect &r, Widget *parent, int type) :
    Widget(r, parent),
    m_type(type),
    m_lastTouchedButton(0)
{
    auto paintBackground = [](const Rect &r, GLColor begin, GLColor end) {
        GLGradient g;
        glAllocateGradient(&g, 2);

        g.colors[0].color  = begin; //0xFF2a0708;
        g.colors[0].pixels = r.h();

        g.colors[1].color  = end; //0xFF8f0f0f;

        glDrawGradient(r.x(), r.y(), r.w(), r.h(), 2, &g);
        glDestroyGradient(&g);
    };

    m_style.setBackground( Brush( [&paintBackground](Brush &, const Rect &r) {
        paintBackground(r, 0xFF878282, 0xFF000000);
    } ));


    m_style.setPressedBackground( Brush( [&paintBackground](Brush &, const Rect &r) {
        paintBackground(r, 0xFFcfcdcd, 0xFF000000);
    } ));


    m_style.setBorder(Brush());
    m_style.setPressedBorder(Brush());

    m_style.setFontFlags( m_style.fontFlags() | FT_TEXT_NOCALC_HCENTER );
    m_style.setPressedTextOffset(Point(0, 0));
}


TabBox::~TabBox()
{
    for(Button *b : m_tabsButton)
        delete b;

    m_tabsButton.clear();
}


void TabBox::buttonHandler(Button *b)
{
    setFocusTab(b->id(), false);
}


void TabBox::setFocusTab(int idx, bool no_trigger)
{
    if((unsigned int)idx >= m_tabsButton.size())
        return;

    int last_id = m_lastTouchedButton? m_lastTouchedButton->id() : -1;

    Button *b = m_tabsButton.at(idx);
    if((b->isTouched() && !b->isMoved() && b != m_lastTouchedButton) || !m_lastTouchedButton)
    {
        if(m_lastTouchedButton) {
            m_lastTouchedButton->style().setBackground( m_style.background() );
            m_lastTouchedButton->setSize(
                        m_lastTouchedButton->rect()
                        .setH(m_lastTouchedButton->rect().h()-3)
                        .setY(m_lastTouchedButton->rect().y()+3)
                        );
        }

        b->style().setBackground( b->style().pressedBackground() );
        m_lastTouchedButton = b;

        m_lastTouchedButton->setSize(
                    m_lastTouchedButton->rect()
                    .setH(m_lastTouchedButton->rect().h()+3)
                    .setY(m_lastTouchedButton->rect().y()-3)
                    );
    }

    if(b->isTouched() && !b->isMoved() && !no_trigger)
        m_tabChanged.trigger(this, last_id, b->id());
}


void TabBox::addTab(const std::string &text)
{
    Button *b = new Button(Rect(), this, text);
    b->setStyle(m_style);
    b->releasedSignal().connect( this, &TabBox::buttonHandler, std::placeholders::_1 );
    b->setId( m_tabsButton.size() );
    m_tabsButton.push_back(b);

    b->show();

    rebaseTabs();
}


int TabBox::tabsCount() const
{
    return m_tabsButton.size();
}


void TabBox::rebaseTabs()
{
    if(m_type == Horizontal)
    {
        int count = m_tabsButton.size();
        int width = (rect().w() - (count+1)) / (count);
        int pos = 1;

        for(int i=0; i<count; ++i)
        {
            Button *b = m_tabsButton.at(i);

            if(i == count-1) {
                if(pos + width+1 < rect().w()) {
                    width = width + (rect().w() - (pos + width+1));
                }
            }
            b->setSize(Rect(pos, 0, width, rect().h()));
            pos += width+1;
        }
    } else {

        int count = m_tabsButton.size();
        int height = (rect().h() - (count+1)) / (count);
        int pos = 1;

        for(int i=0; i<count; ++i)
        {
            Button *b = m_tabsButton.at(i);

            if(i == count-1) {
                if(pos + height+1 < rect().h()) {
                    height = height + (rect().h() - (pos + height+1));
                }
            }
            b->setSize(Rect(0, pos, rect().w(), height));
            pos += height+1;
        }

    }
}


void TabBox::paintEvent()
{
    if(m_type == Horizontal) {
        int h;
        for(Button *b : m_tabsButton)
        {
            int h = b->realRect().y();
            if(b == m_lastTouchedButton)
                h += 3;

            glSetPen(0xFFFFFFFF);
            glDrawVLine(h, b->realRect().y2(), b->realRect().x()-1);
            //b->paint();
        }

        Button *b = (*(--m_tabsButton.end()));
        h = b->realRect().y();

        if(b == m_lastTouchedButton)
            h += 3;

        glSetPen(0xFFFFFFFF);
        glDrawVLine(h, b->realRect().y2(), b->realRect().x2());
    }


    Widget::paintEvent();
}


void TabBox::touchEvent(int action, int x, int y)
{
    Widget::touchEvent(action, x, y);
}
