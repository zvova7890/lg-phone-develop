

#include <Widget.h>
#include <TimerCounter.h>
#include <stdio.h>
#include <assert.h>



Widget::Widget(const Rect &rect, Widget *parent) :
    m_parent(parent),
    m_eventManager(parent? parent->eventManager() : 0),
    m_rect(rect)
{
    init();
    updateCoordinates(this);
}


Widget::Widget(const Rect &rect, EventManager *event_manager) :
    m_parent(0),
    m_eventManager(event_manager),
    m_rect(rect)
{
    init();
    updateCoordinates(this);
}


Widget::~Widget()
{
    if(m_longPressTimer) {
        delete m_longPressTimer;
    }

    close();
}


void Widget::init()
{
    m_longPressTimer = 0;
    m_touched = 0;
    m_id = 0;
    m_focused = 0;
    m_hidden = false;
    m_isTouched = false;
    m_isMoved = false;
    m_isMoving = false;
    m_isOffRectTouch = false;
    m_isFullScreenBlocked = false;
    m_isBlockable = true;
    m_isHaveLongPress = false;
    m_isMovable = true;
    m_isFocused = false;
    m_isFocuseable = true;
}


void Widget::updateCoordinates(Widget *widget)
{
    Rect r;

    if(widget->m_parent) {
        const Rect & rc = widget->m_parent->realRect();

        r = Rect(rc.x() + widget->m_rect.x(),
                 rc.y() + widget->m_rect.y(),
                 widget->m_rect.w(),
                 widget->m_rect.h());
    } else {
        r = widget->m_rect;
    }

    widget->m_realRect = r;
}


void Widget::focus()
{
    if(parent()) {
        if(parent()->m_focused)
            parent()->m_focused->unfocusEvent();

        parent()->m_focused = this;
        focusEvent();
    }
}


void Widget::unfocus()
{
    if(parent()) {
        if(parent()->m_focused)
            parent()->m_focused->unfocusEvent();

        parent()->m_focused = 0;
    }

    unfocusEvent();
    m_focused = 0;
}


void Widget::paint()
{
    paintEvent();
}


void Widget::touch(int action, int x, int y)
{
    switch(action)
    {
        case TOUCH_ACTION_PRESS:
            //item->cur_x = item->touched_x = x;
            //item->cur_y = item->touched_y = y;

            m_isMoved = false;
            m_isMoving = false;
            m_isTouched = true;


            if(m_longPressTimer) {

                m_longPressTimer->stop();
                m_longPressTimer->reset(0);
                m_longPressTimer->setFinalComp( [this, x, y](TimerCounter *tc) {

                    if(tc->value() > 1) {
                        touchEvent(TOUCH_ACTION_LONGPRESS, x, y);
                        return true;
                    }

                    return false;
                });

                m_longPressTimer->start(100);
            }

            break;

        case TOUCH_ACTION_MOVE:
            if(m_longPressTimer)
                m_longPressTimer->stop();
            m_isMoved = true;
            m_isMoving = true;
            break;
    }

    touchEvent(action, x, y);

    if(action == TOUCH_ACTION_RELEASE) {
        m_isMoving = false;
        m_isTouched = false;

        if(m_longPressTimer)
            m_longPressTimer->stop();
   }
}

void Widget::paintEvent()
{
    for(Widget *widget : m_childs) {

        assert(widget != NULL);

        if(!widget->m_hidden) {
            updateCoordinates(widget);
            widget->paint();
        }
    }
}


void Widget::touchEvent(int action, int x, int y)
{
    auto touched_save = [this, action, x, y](Widget *w){

        switch(action)
        {
            case TOUCH_ACTION_PRESS:

                if(m_touched) {
                    BUGON(m_touched == 0);
                    m_touched->touch(TOUCH_ACTION_RELEASE, lastTouchedPosition().x(), lastTouchedPosition().y());
                    m_touched = 0;
                }

                if(w->isMovable())
                    m_touched = w;
                break;
        }

    };


    if(m_touched) {
        if(action == TOUCH_ACTION_PRESS) {

            BUGON(m_touched == 0);

            m_touched->touch(TOUCH_ACTION_RELEASE, lastTouchedPosition().x(), lastTouchedPosition().y());
            m_touched = 0;
            goto __ex;
        }

        if(action == TOUCH_ACTION_RELEASE) {
            m_touched->touch(action, x, y);
            m_touched = 0;
            return;
        }

        m_touched->touch(action, x, y);
        return;
    }

__ex:


    for(auto wi = m_childs.rbegin(); wi != m_childs.rend(); ++wi) {

        Widget *widget = *wi;

        if(!widget->m_hidden) {

            if(x >= widget->realRect().x() && x < widget->realRect().x2() &&
                                y >= widget->realRect().y() && y < widget->realRect().y2())
            {

                touched_save(widget);

                assert(widget->parent() == this);

                if(m_focused != widget && widget->isFocuseable()) {
                    widget->focus();
                }

                widget->m_isOffRectTouch = false;
                updateCoordinates(widget);
                widget->touch(action, x, y);

                if(widget->isBlockable())
                    break;

            } else if(widget->isFullScreenBlocked()) {
                assert(widget->parent() == this);

                if(m_focused != widget && widget->isFocuseable()) {
                    widget->focus();
                }

                widget->m_isOffRectTouch = true;
                updateCoordinates(widget);
                widget->touch(action, x, y);

                widget->m_isOffRectTouch = false;
                break;
            }
        }
    }

    m_lastAction = action;
    lastTouchedPosition().setX(x).setY(y);
}



void Widget::focusEvent()
{
    /*if(parent() && parent()->m_focused != this) {
        if(parent()->m_focused)
            parent()->m_focused->unfocus();

        parent()->m_focused = this;
    }*/

    m_isFocused = true;
}


void Widget::unfocusChild()
{
    if(m_focused) {
        m_focused->unfocusEvent();
        m_focused = 0;
    }
}


void Widget::unfocusEvent()
{
    if(parent() && parent()->m_focused == this) {
        //parent()->m_focused = 0;
    }

    if(m_focused) {
        m_focused->unfocusEvent();
        m_focused = 0;
    }

    m_isFocused = false;
}


void Widget::add(Widget *widget)
{
    m_childs.push_back(widget);
    widget->m_wid = (--m_childs.end());
}


void Widget::insert(Widget::wid & after, Widget *w)
{
    m_childs.insert(after.iterator(), w);
}


void Widget::remove(Widget::wid & id)
{
    id.erase();
}


void Widget::swap(wid & id1, Widget::wid & id2)
{
    std::swap(id1, id2);
}


void Widget::hide()
{
    unfocus();
    m_hidden = true;
}


void Widget::show()
{
    if(!m_wid.isValid() && parent()) {
        printf("void Widget::show() add %lX\n", (unsigned long)this);
        parent()->add(this);
    }

    m_hidden = false;

    //focus();
}


void Widget::showBefore(Widget::wid &id)
{
    if(!m_wid.isValid() && id.isValid()) {
        parent()->insert(id, this);
    }

    m_hidden = false;
}


void Widget::close()
{
    if(parent() && parent()->m_focused == this) {
        parent()->m_focused = 0;
    }

    unfocusEvent();
    m_wid.erase();
}


void Widget::setWidth(int w)
{
    rect().setW(w);
    updateCoordinates(this);
}


void Widget::setHeight(int h)
{
    rect().setH(h);
    updateCoordinates(this);
}


void Widget::setBlockable(bool is)
{
    m_isBlockable = is;
}


void Widget::setFullScreenBlock(bool is)
{
    m_isFullScreenBlocked = is;
}


void Widget::move(const Point &pos)
{
    m_rect.setXY(pos);
    updateCoordinates(this);
}


void Widget::move(int x, int y)
{
    m_rect.setX(x).setY(y);
    updateCoordinates(this);
}


void Widget::moveX(int x)
{
    m_rect.setX(x);
    updateCoordinates(this);
}


void Widget::moveY(int y)
{
    m_rect.setY(y);
    updateCoordinates(this);
}


void Widget::setSize(const Rect &r)
{
    m_rect = r;
    updateCoordinates(this);
}


Rect Widget::size() const
{
    return m_realRect;
}


void Widget::activateLongPress(bool is)
{
    if(is) {
        if(!m_longPressTimer) {
            m_longPressTimer = new TimerCounter();
        }

    } else {
        if(m_longPressTimer) {
            m_longPressTimer->stop();
            m_longPressTimer = 0;
        }
    }
}


void Widget::deleteLater()
{
    eventManager()->notifyAfterEvent( [this](){
        delete this;
    });
}
