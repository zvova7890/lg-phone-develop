
#include <gl.h>
#include <Core/compatible.h>
#include "ScrollArea.h"



#ifndef __PC_BUILD__
#include <mips.h>
#endif



#define printf(...)


ScrollArea::ScrollArea(const Rect &r, ScrollArea::ScrollType scroll_type, Widget *parent) :
    Widget(r, parent),
    m_timerType(NoWork),
    m_scrollType(scroll_type)
{
    init();
}


ScrollArea::~ScrollArea()
{
}


void ScrollArea::init()
{
    if(m_scrollType == Vertical) {
        dep_type_area_pos = [this](){
            return realRect().y();
        };

        dep_type_area_size = [](const Widget *w) {
            return w->rect().h();
        };
    } else {

        dep_type_area_pos = [this](){
            return realRect().x();
        };

        dep_type_area_size = [](const Widget *w) {
            return w->rect().w();
        };
    }

    m_setClipRegionFunc = [](const Rect &) {};
    m_setRestoreClipRegionFunc = []() {};
    m_item = 0;
    m_coordPos = 0;
    m_pageSize = 0;
    m_touched = 0;
    m_linesCount = 0;
}


Widget *ScrollArea::widgetItem(int id)
{
    if(m_items.size() <= (unsigned)id) {
        return 0;
    }

    return m_items.at(id);
}


int ScrollArea::count() const
{
    return m_linesCount;
}


Widget *ScrollArea::takeItemByCoord(int x, int y)
{
    GL_UNUSED(x);

    if(!count())
        return 0;

    Widget *w = widgetItem(item());
    if(!w)
        return 0; // Oops

    int dep_type_pos = m_scrollType == Vertical? y : x;
    int start_p = dep_type_area_pos()+m_coordPos;
    for(int i=0; item()+i < count(); ++i) {

        w = widgetItem(item()+i);
        if(!w) {
            printf("That is mega trololo o_O, %d\n", item()+i);
            break;
        }

        if(dep_type_pos >= start_p && dep_type_pos < start_p + dep_type_area_size(w)) {
            printf("Take at %d\n", item()+i);
            return widgetItem(item()+i);
        }

        start_p += dep_type_area_size(w);
    }

    return 0;
}


void ScrollArea::touchItemEvent(int item, int action, int x, int y)
{
    Widget *w = widgetItem(item);
    if(!w)
        return;

    w->touch(action, x, y);
}


inline int ScrollArea::checkItemSizes(Widget *w) const
{
    if(!w)
        return 0;

    if(dep_type_area_size(w) <= dep_type_area_size(this))
        return 0;

    return dep_type_area_size(w) - dep_type_area_size(this);
}


inline Widget *ScrollArea::lastWidgetItem()
{
    return widgetItem(count()-1);
}


void ScrollArea::resizeEvent()
{
    m_resizeHandler.trigger(this);

    for(Widget *w : m_items) {
        w->resizeEvent();
    }
}


void ScrollArea::paintEvent()
{
    printf("void HScrollArea::paintEvent()\n");

    int dep_type_pos = 0;
    int i;
    m_pageSize = m_coordPos;
    m_displayingItems = -1;
    m_haveOffscreenItems = false;

    if(!count()) {
        printf(" -> HScrollArea:: no have items for view\n");
    }

    m_setClipRegionFunc(realRect());

    for(i = m_item; i < count(); ++i) {

        Widget *w = widgetItem(i);
        if(!w)
            break;

        w->setId(i);

        if(m_scrollType == Vertical) {
            w->setRealRect( Rect(Point(w->realRect().x(), dep_type_pos+realRect().y()+m_coordPos), w->rect().wh() ) );
        } else {
            w->setRealRect( Rect(Point(dep_type_pos+realRect().x()+m_coordPos, realRect().y()), w->rect().wh() ) );
        }

        w->paint();

        if(dep_type_pos > dep_type_area_size(this)) {
            break;
        }

        dep_type_pos += dep_type_area_size(w);
        m_pageSize += dep_type_area_size(w);

        if(dep_type_pos+m_coordPos >= dep_type_area_size(this) && m_displayingItems == -1) {
            m_displayingItems = i-m_item;
            m_haveOffscreenItems = true;

            if(dep_type_pos+m_coordPos != dep_type_area_size(this))
                m_displayingItems--;
        }
    }

    if(m_displayingItems == -1)
        m_displayingItems = 0;

    Widget::paintEvent();

    m_setRestoreClipRegionFunc();
}


void ScrollArea::touchEvent(int action, int x, int y)
{
#ifndef __PC_BUILD__
    auto ticks_diff = [](unsigned long ticks) -> unsigned long {

        unsigned long c = systimer_ticks();

        if(c < ticks)
            c = ULONG_MAX - ticks + c;

        return c - ticks;
    };
#endif

    int dep_type_pos = m_scrollType == Vertical? y : x;
    auto getLastPos = [this]() {
        return m_scrollType == Vertical? m_lastPos.y() :  m_lastPos.x();
    };

    auto getTouchLastPos = [this]() {
        return m_scrollType == Vertical? m_touchLastPos.y() :  m_touchLastPos.x();
    };

    switch(action)
    {
        case TOUCH_ACTION_PRESS:
            printf("touchEvent TOUCH_ACTION_PRESS\n");
            Timer::stop();

            m_lastPos.setX(x).setY(y);
            m_touchLastPos = m_lastPos;
            m_moveDirection = Direction::No;
            m_posDiff = 0;

#ifdef __PC_BUILD__
            m_timerCounter.start(30);
#else
            m_lastTime = systimer_ticks();
#endif

            m_touched = takeItemByCoord(x, y);

            if(m_touched) {
                m_touched->touch(action, x, y);
            }

            break;


        case TOUCH_ACTION_MOVE:
        {
            //if(!isTouched())
                //return;

            if(m_touched) {
                m_touched->touch(action, x, y);
            }

            bool direction_changed = false;
            Direction move_direction;

            if(getLastPos() < dep_type_pos) { // FIXME
                move_direction = Direction::Down;
            } else if(getLastPos() > dep_type_pos){ // FIXME
                move_direction = Direction::Up;
            } else
                move_direction = Direction::No;

            //printf("move_direction: %d - %d | %d\n", move_direction, m_lastPos.y(), y);

            if(move_direction != Direction::No /*&& m_moveDirection != Direction::No*/ && move_direction != m_moveDirection)
                direction_changed = true;


            if(move_direction == Direction::Up) {
                moveUp(getLastPos() - dep_type_pos); // FIXME
            }
            else if(move_direction == Direction::Down) {
                moveDown(dep_type_pos - getLastPos()); // FIXME
            }



            if(direction_changed) {
#ifdef __PC_BUILD__
                m_timerCounter.reset(0);
#else
                m_lastTime = systimer_ticks();
#endif
                m_touchLastPos.setX(x).setY(y);
            } else {

            }

#ifdef __PC_BUILD__
            m_timeStampDiff = m_timerCounter.value();
#else
            m_timeStampDiff = ticks_diff(m_lastTime) / (clocks_per_seccond()/1000) / 30;
            if(!m_timeStampDiff)
                ++m_timeStampDiff;
#endif

            m_posDiff = glAbs(dep_type_pos-getLastPos());

            m_lastPos.setX(x).setY(y);
            m_moveDirection = move_direction;
            break;
        }

        case TOUCH_ACTION_RELEASE:
        {
            if(!isTouched() /*&& !isMoved()*/)
                break;

#ifdef __PC_BUILD__
            m_timerCounter.stop();
#endif

            int speed = 0;
            int fadden = 0;
            int sdiff = glAbs(getTouchLastPos() - getLastPos()); // FIXME

            if(sdiff && m_timeStampDiff)
                speed = (sdiff/2) / m_timeStampDiff;

            fadden = m_timeStampDiff*2;

            /*printf("m_yDiff: %d\n", m_yDiff);
            printf("m_timeStampDiff: %d\n", m_timeStampDiff);*/

            //printf("speed: %d fadden: %d\n", speed, fadden);


            if(m_moveDirection == Direction::Up)
                startMove(speed, fadden, Direction::Up);

            else if(m_moveDirection == Direction::Down)
                startMove(speed, fadden, Direction::Down);

            else {
                printf("no way o_O\n");
                fixupViewPosition();
            }


            if(m_touched) {
                m_touched->touch(action, x, y);
                m_touched = 0;
            }

#ifdef __PC_BUILD__
            m_timerCounter.reset(0);
#else
            m_lastTime = 0;
#endif
            break;
        }

        default:
            if(m_touched) {
                m_touched->touch(action, x, y);
            }
            break;
    }

    Widget::touchEvent(action, x, y);
    eventManager()->updateAfterEvent();
}


bool ScrollArea::moveDown(int steps)
{
    m_coordPos += steps;

    Widget *w = widgetItem(item());
    while(w && 0 < (m_coordPos)) {

        if(m_item < 1)
            break;

        m_item --;


        m_coordPos -= dep_type_area_size(w);
        w = widgetItem(item());
    }

    if(item() == 0) {

        Widget *w = widgetItem(0);
        if(!w)
            return false; //Oops

        if(m_coordPos - checkItemSizes(w) > dep_type_area_size(this) - dep_type_area_size(w)) {
            m_coordPos = checkItemSizes(w) + dep_type_area_size(this) - dep_type_area_size(w);
            return false;
        }
    }

    return true;
}


bool ScrollArea::moveUp(int steps)
{
    m_coordPos -= steps;

    Widget *w = widgetItem(item());
    while(w && dep_type_area_size(w) < -(m_coordPos)) {

        if(m_item+1 >= count())
            break;

        m_item ++;


        m_coordPos += dep_type_area_size(w);
        w = widgetItem(item());
    }


    if(item() == count()-1) {

        Widget *w = widgetItem(item());
        if(!w)
            return false; //Oops

        if(m_coordPos + checkItemSizes(w) < 0) {
            m_coordPos = -checkItemSizes(w);
            return false;
        }
    }

    return true;
}



void ScrollArea::startMove(int speed, int potencial, Direction d)
{
    //printf("startMove()\n");

    m_timerType = TimerWork::ScrollFading;
    m_timerSpeed = speed;
    m_potencialOfHiding = potencial;
    m_timerValue = 0;
    m_timerDirectionMove = d;

    Timer::start(30);
}



void ScrollArea::fixupViewPosition()
{
    //auto w = lastWidgetItem();

    if(item() == 0 && m_coordPos/*-checkItemSizes(w)*/ > 0) {

        //printf(" -> m_coordPos: %d\n", m_coordPos);

        PosFixup.distance = m_coordPos;
        PosFixup.speed = 10;
        PosFixup.boost = 30;//%
        PosFixup.direction = Direction::Up;

        m_timerType = TimerWork::ScrollFixup;
        Timer::start(30);
    } else {

        int least = leastFreePage();

        if(least < 1)
            return;

        //printf("least: %d\n", least);


        PosFixup.distance = least;
        PosFixup.speed = 10;
        PosFixup.boost = 30;//%
        PosFixup.direction = Direction::Down;

        m_timerType = TimerWork::ScrollFixup;
        Timer::start(30);
    }
}


void ScrollArea::breakScrolling()
{
    if(m_timerType == TimerWork::ScrollFading) {
        Timer::stop();
    }
}


void ScrollArea::resetViewPosition()
{
    Timer::stop();

    if(m_touched) {
        // don`t know, this is correct behaviour?
        m_touched->touch(TOUCH_ACTION_RELEASE, lastTouchedPosition().x(), lastTouchedPosition().y());
        m_touched = 0;
    }

    m_item = 0;
    m_coordPos = 0;
}


void ScrollArea::setViewCoord(int c)
{
    m_coordPos = c;
}


void ScrollArea::setItem(int c)
{
    if(c < 0 || c >= m_linesCount)
        return;

    m_item = c;
}


void ScrollArea::setLinesCount(int c)
{
    m_linesCount = c;
}


bool ScrollArea::isAutoScrollActive() const
{
    if(m_timerType != TimerWork::NoWork && Timer::isActive())
        return true;
    return false;
}



void ScrollArea::addItem(Widget *w)
{
    m_items.push_back(w);

    w->handleResizeEvent().connect( [this](Widget *w) {
        w->setSize( Rect(0, 0, rect().w(), w->rect().h()) );
    });
}


void ScrollArea::clear()
{
    m_items.clear();
}


int ScrollArea::listHeightInRect()
{
    int dep_type_pos = 0;
    int i = 0;

    for(i = count()-1; i> -1; --i) {

        Widget *w = widgetItem(i);
        if(!w)
            break;

        dep_type_pos += dep_type_area_size(w);
        if(dep_type_pos >= dep_type_area_size(this))
            break;
    }

    return dep_type_pos;
}


int ScrollArea::leastFreePage()
{
    /*bool haveEndItem = false;
    int h = 0;
    int cur_used_h = 0;
    int i = 0;

    for(i = count()-1; i> -1; --i) {

        Widget *w = widgetItem(i);
        if(!w)
            break;

        if(i >= item()) {
            cur_used_h += w->realRect().h();
        }

        if(i == item())
            haveEndItem = true;


        h += w->realRect().h();
        if(h >= realRect().h())
            break;
    }

    printf("realRect().h(): %d\n", realRect().h());

    if(h == cur_used_h && !haveEndItem)
        return 0;

    Widget *w = lastWidgetItem();

    cur_used_h += m_coordPos;
    return h - cur_used_h - checkItemSizes(w);*/


    Widget *item = 0;
    int dept_type_pos = 0;

    for(int i = m_item; i < count(); ++i)
    {
        item = widgetItem(i);
        if(!item)
            break;

        dept_type_pos += dep_type_area_size(item);

        if(dept_type_pos+m_coordPos >= dep_type_area_size(this)) {
            return 0;
        }
    }


    int dep_type_pos_check = 0;

    for(int i = count()-1; i > -1; --i)
    {
        item = widgetItem(i);
        if(!item)
            break;

        dep_type_pos_check += dep_type_area_size(item);
        if(dep_type_pos_check >= dep_type_area_size(this)) {
            dep_type_pos_check -= dep_type_pos_check - dep_type_area_size(this);
            break;
        }
    }

    //printf("lol_h: %d pos_y: %d\n", lol_h, pos_y);
    return dep_type_pos_check - dept_type_pos - m_coordPos;
}


void ScrollArea::timerEvent()
{
    switch(m_timerType)
    {
        case ScrollFading:

            m_timerSpeed -= (m_timerSpeed * m_potencialOfHiding / 100);

            if(m_timerSpeed < 1) {

                printf("Fixuping list...\n");
                Timer::stop();
                m_timerType = TimerWork::NoWork;
                fixupViewPosition();
                break;
            }

            //printf("m_timerSpeed: %f, %d, m_pageHeight: %d\n", m_timerSpeed, m_coordPos, m_pageHeight);

            switch(m_timerDirectionMove)
            {
                case Direction::Up:
                    if(!moveUp(m_timerSpeed)) {
                        m_timerSpeed = 0;
                    }

                    if(leastFreePage() > 0) {
                        //printf("Offscreen UP fadding down quikly\n");
                        m_potencialOfHiding += 16;
                    }
                    break;

                case Direction::Down:
                {
                    if(!moveDown(m_timerSpeed)) {
                        m_timerSpeed = 0;
                    }

                    auto w = lastWidgetItem();

                    if(m_coordPos-checkItemSizes(w) > 0) {
                        //printf("Offscreen DOWN fadding down quikly\n");
                        m_potencialOfHiding += 16;
                    }
                    break;
                }

                case Direction::No:
                    break;
            }

            eventManager()->updateAfterEvent();
            break;


        case ScrollFixup:

            PosFixup.speed += (PosFixup.speed * PosFixup.boost / 100);


            if(PosFixup.distance < PosFixup.speed) {
                PosFixup.speed = PosFixup.distance;
                PosFixup.distance = 0;
            }
            else
                PosFixup.distance -= PosFixup.speed;



            switch(PosFixup.direction)
            {
                case Direction::Up:
                    moveUp(PosFixup.speed);
                    eventManager()->updateAfterEvent();
                    break;

                case Direction::Down:
                    moveDown(PosFixup.speed);
                    eventManager()->updateAfterEvent();
                    break;

                case Direction::No:
                    break;
            }

            if(!PosFixup.distance) {
                Timer::stop();
                printf("Fixup complete: m_coordPos %d\n", m_coordPos);

                m_timerType = TimerWork::NoWork;
            }

            break;

        case ScrollToStartEnd:
        {
            PosFixup.speed += (PosFixup.speed * PosFixup.boost / 100);

            auto stop_and_fix = [this]() {

                m_timerType = TimerWork::NoWork;
                Timer::stop();
                fixupViewPosition();
            };

            switch(PosFixup.direction)
            {
                case Direction::Up:
                    if(!moveUp(PosFixup.speed))
                        stop_and_fix();

                    eventManager()->updateAfterEvent();
                    break;

                case Direction::Down:
                    if(!moveDown(PosFixup.speed))
                        stop_and_fix();

                    eventManager()->updateAfterEvent();
                    break;

                case Direction::No:
                    break;
            }

            break;
        }

        case TimerWork::NoWork:
            break;
    }
}



void ScrollArea::toStart()
{
    PosFixup.speed = 10;
    PosFixup.boost = 20;//%
    PosFixup.direction = Direction::Down;

    m_timerType = TimerWork::ScrollToStartEnd;
    Timer::start(30);
}


void ScrollArea::toEnd()
{
    PosFixup.speed = 10;
    PosFixup.boost = 20;//%
    PosFixup.direction = Direction::Up;

    m_timerType = TimerWork::ScrollToStartEnd;
    Timer::start(30);
}


