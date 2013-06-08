

#include <Widget/Widget.h>
#include <Core/TimerCounter.h>
#include <Core/compatible.h>
#include <stdio.h>
#include <assert.h>
#include <Core/safeforeach.h>


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
    m_lastRect = rect();
    m_longPressTimer = 0;
    m_touched = 0;
    m_id = 0;
    m_focused = 0;
    m_attrs = ATTR_BLOCKABLE | ATTR_MOVABLE | ATTR_FOCUSEABLE | ATTR_HIDDEN;
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

            erase_attr(ATTR_MOVED);
            erase_attr(ATTR_MOVING);
            set_attr(ATTR_TOUCHED);


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

            set_attr(ATTR_MOVED);
            set_attr(ATTR_MOVING);
            break;
    }

    touchEvent(action, x, y);

    if(action == TOUCH_ACTION_RELEASE) {
        erase_attr(ATTR_TOUCHED);
        erase_attr(ATTR_MOVING);

        if(m_longPressTimer)
            m_longPressTimer->stop();
   }
}

void Widget::paintEvent()
{
    int at = 0;
    safe_for_each(Widget *, widget, m_childs)
    {
        /*if(widget->__name == "Ololo") {
            if(m_childs.size() == 4444)
                exit(-1);
        }*/

        if(!widget->isHidden()) {
            updateCoordinates(widget);
            widget->paint();
        }

        ++at;
    }
}





void Widget::touchEvent(int action, int x, int y)
{
    auto touched_save = [this, action, x, y](Widget *w){

        switch(action)
        {
            case TOUCH_ACTION_PRESS:

                if(m_touched) {

                    if(m_touched->isBlockable()) {
                        BUGON(m_touched->isBlockable() == false);

                        m_touched->touch(TOUCH_ACTION_RELEASE, x, y);
                        m_touched = 0;
                    }
                }

                m_touched = w;
                break;
        }

    };


    if(m_touched) {

        if(x >= m_touched->realRect().x() && x < m_touched->realRect().x2() &&
                            y >= m_touched->realRect().y() && y < m_touched->realRect().y2())
        {
doit:
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

        } else if(!m_touched->isMovable()) {
            m_touched->set_attr(ATTR_OFFRECT_TOUCH);
            m_touched->touch(TOUCH_ACTION_RELEASE, lastTouchedPosition().x(), lastTouchedPosition().y());
            m_touched->erase_attr(ATTR_OFFRECT_TOUCH);
            m_touched = 0;
        } else {
            goto doit;
        }
    }

__ex:


    safe_revert_for_each(Widget *, widget, m_childs)
    {
        if(!widget->isHidden()) {

            if(x >= widget->realRect().x() &&
                    x < widget->realRect().x2() &&
                    y >= widget->realRect().y() &&
                    y < widget->realRect().y2())
            {

                touched_save(widget);

                assert(widget->parent() == this);

                if(m_focused != widget && widget->isFocuseable()) {
                    widget->focus();
                }

                widget->erase_attr(ATTR_OFFRECT_TOUCH);

                updateCoordinates(widget);
                widget->touch(action, x, y);

                if(widget->isBlockable())
                    break;

            } else if(widget->isFullScreenBlocked()) {
                assert(widget->parent() == this);

                if(m_focused != widget && widget->isFocuseable()) {
                    widget->focus();
                }

                widget->set_attr(ATTR_OFFRECT_TOUCH);
                updateCoordinates(widget);
                widget->touch(action, x, y);

                widget->erase_attr(ATTR_OFFRECT_TOUCH);
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

    set_attr(ATTR_FOCUSED);
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

    erase_attr(ATTR_FOCUSED);
}


void Widget::add(Widget *widget)
{
    if(widget->m_wid.isValid()) {
        printf("WARNING: Double show\n");
    }

    m_childs.push_back(widget);
    widget->m_wid = (--m_childs.end());
    widget->erase_attr(ATTR_HIDDEN);
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


bool Widget::hide()
{
    if(isHidden())
        return false;

    unfocus();
    set_attr(ATTR_HIDDEN);
    return true;
}


bool Widget::show()
{
    if(!isHidden() && m_wid.isValid())
        return false;

    if(!m_wid.isValid() && parent()) {
        printf("void Widget::show() add %lX %s\n", (unsigned long)this, this->__name.c_str());
        parent()->add(this);
    }

    erase_attr(ATTR_HIDDEN);

    //focus();
    return true;
}


bool Widget::showBefore(Widget::wid &id)
{
    if(!m_wid.isValid() && id.isValid()) {
        parent()->insert(id, this);
    }

    erase_attr(ATTR_HIDDEN);
    return true;
}


bool Widget::close()
{
    if(!m_wid.isValid())
        return false;

    if(parent() && parent()->m_focused == this) {
        parent()->m_focused = 0;
    }

    unfocusEvent();
    m_wid.erase();

    set_attr(ATTR_HIDDEN);
    return true;
}


void Widget::addParentToQueue()
{
    if(m_wid.isValid())
        return;

    if(!m_wid.isValid() && parent()) {
        printf("void Widget::show() add %lX\n", (unsigned long)this);
        parent()->add(this);
    }

    set_attr(ATTR_HIDDEN);
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
    if(is)
        set_attr(ATTR_BLOCKABLE);
    else
        erase_attr(ATTR_BLOCKABLE);
}


void Widget::setFullScreenBlock(bool is)
{
    if(is)
        set_attr(ATTR_FULLSCREEN_BLOCK);
    else
        erase_attr(ATTR_FULLSCREEN_BLOCK);
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


void Widget::activateLongPressSupport(bool is)
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
        eventManager()->updateAfterEvent();
        delete this;
    });
}


void Widget::motionSensorEvent(int pos)
{
    (void) pos;
}


void Widget::motionSensorEvent(int x, int y, int z)
{
    (void) x;
    (void) y;
    (void) z;
}


Widget *Widget::rootParent()
{
    Widget *p = parent();
    while(p && p->parent()) {
        p = p->parent();
    }

    return p;
}


void *Widget::providesExtraExtension(const std::string &)
{
    return 0;
}


void Widget::resizeEvent()
{
    auto calc = [](int total, int size, int new_total) -> int {
        int perc = size*100 / total;
        return new_total * perc / 100;
    };

    if(parent()) {
        int newx = calc(parent()->m_lastRect.w(), rect().x(), parent()->rect().w());
        int newy = calc(parent()->m_lastRect.h(), rect().y(), parent()->rect().h());
        int neww = calc(parent()->m_lastRect.w(), rect().x2(), parent()->rect().w()) - newx;
        int newh = calc(parent()->m_lastRect.h(), rect().y2(), parent()->rect().h()) - newy;


        if(test_attr(ATTR_RESIZE_NO_CALC_W))
            neww = rect().w();

        if(test_attr(ATTR_RESIZE_NO_CALC_H))
            newh = rect().h();

        setSize(Rect(newx, newy, neww, newh));
    }

    m_resizeHandler.trigger(this);

    for(Widget *w : m_childs) {
        w->resizeEvent();
    }

    m_lastRect = m_rect;
}


bool Widget::isTop()
{
    if(parent()->directChilds().back() == this) {
        return true;
    }

    return false;
}


bool Widget::toTop()
{
    if(isTop())
        return false;

    if(m_wid.isValid())
    {
        parent()->m_childs.erase(m_wid.m_it);

        parent()->m_childs.push_back(this);
        m_wid.m_it = (--parent()->m_childs.end());

        return true;
    }

    return false;
}
