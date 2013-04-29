
#include <gl.h>
#include "VScrollArea.h"
#include <include.h>

#ifndef __PC_BUILD__
#include <mips.h>
#endif



#define printf(...)


VScrollArea::VScrollArea(const Rect &r, Widget *parent) :
    Widget(r, parent),
    m_timerType(NoWork)
{
    init();
}


VScrollArea::~VScrollArea()
{
}


void VScrollArea::init()
{
    m_item = 0;
    m_coordPos = 0;
    m_pageHeight = 0;
    m_touched = 0;
    m_linesCount = 0;
}


Widget *VScrollArea::widgetItem(int id)
{
    if(m_items.size() <= (unsigned)id) {
        return 0;
    }

    return m_items.at(id);
}


int VScrollArea::count() const
{
    return m_linesCount;
}


Widget *VScrollArea::takeItemByCoord(int x, int y)
{
    GL_UNUSED(x);

    if(!count())
        return 0;

    Widget *w = widgetItem(item());
    if(!w)
        return 0; // Oops


    int start_y = realRect().y()+m_coordPos;
    for(int i=0; item()+i < count(); ++i) {

        w = widgetItem(item()+i);
        if(!w) {
            printf("That is mega trololo o_O, %d\n", item()+i);
            break;
        }

        if(y >= start_y && y < start_y+w->realRect().h()) {
            printf("Take at %d\n", item()+i);
            return widgetItem(item()+i);
        }

        start_y += w->realRect().h();
    }

    return 0;
}


void VScrollArea::touchItemEvent(int item, int action, int x, int y)
{
    Widget *w = widgetItem(item);
    if(!w)
        return;

    w->touch(action, x, y);
}


inline int VScrollArea::checkItemSizes(Widget *w) const
{
    if(!w)
        return 0;

    if(w->realRect().h() <= realRect().h())
        return 0;

    return w->realRect().h() - realRect().h();
}


inline Widget *VScrollArea::lastWidgetItem()
{
    return widgetItem(count()-1);
}


void VScrollArea::paintEvent()
{

    int h = 0;
    int i;
    m_pageHeight = m_coordPos;
    m_displayingItems = -1;
    m_haveOffscreenItems = false;

    if(!count()) {
        printf(" -> VScrollArea:: no have items for view\n");
    }

    for(i = m_item; i < count(); ++i) {

        Widget *w = widgetItem(i);
        if(!w)
            break;

        w->setId(i);
        w->setRealRect( Rect(Point(w->realRect().x(), h+realRect().y()+m_coordPos), w->rect().wh() ) );
        w->paint();

        if(h > realRect().h()) {
            break;
        }

        h += w->realRect().h();
        m_pageHeight += w->realRect().h();

        if(h+m_coordPos >= realRect().h() && m_displayingItems == -1) {
            m_displayingItems = i-m_item;
            m_haveOffscreenItems = true;

            if(h+m_coordPos != realRect().h())
                m_displayingItems--;
        }
    }

    if(m_displayingItems == -1)
        m_displayingItems = 0;
}


void VScrollArea::touchEvent(int action, int x, int y)
{
#ifndef __PC_BUILD__
    auto ticks_diff = [](unsigned long ticks) -> unsigned long {

        unsigned long c = systimer_ticks();

        if(c < ticks)
            c = ULONG_MAX - ticks + c;

        return c - ticks;
    };
#endif

    switch(action)
    {
        case TOUCH_ACTION_PRESS:
            printf("touchEvent TOUCH_ACTION_PRESS\n");
            Timer::stop();

            m_lastPos.setX(x).setY(y);
            m_touchLastPos = m_lastPos;
            m_moveDirection = Direction::No;
            m_yDiff = 0;

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
            if(m_touched) {
                m_touched->touch(action, x, y);
            }

            bool direction_changed = false;
            Direction move_direction;

            if(m_lastPos.y() < y) {
                move_direction = Direction::Down;
            } else if(m_lastPos.y() > y){
                move_direction = Direction::Up;
            } else
                move_direction = Direction::No;

            //printf("move_direction: %d - %d | %d\n", move_direction, m_lastPos.y(), y);

            if(move_direction != Direction::No /*&& m_moveDirection != Direction::No*/ && move_direction != m_moveDirection)
                direction_changed = true;


            if(move_direction == Direction::Up) {
                moveUp(m_lastPos.y() - y);
            }
            else if(move_direction == Direction::Down) {
                moveDown(y - m_lastPos.y());
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

            m_yDiff = glAbs(y-m_lastPos.y());

            m_lastPos.setX(x).setY(y);
            m_moveDirection = move_direction;
            break;
        }

        case TOUCH_ACTION_RELEASE:
        {
            if(!isTouched())
                break;

#ifdef __PC_BUILD__
            m_timerCounter.stop();
#endif

            int speed = 0;
            int fadden = 0;
            int ydiff = glAbs(m_touchLastPos.y() - m_lastPos.y());

            if(ydiff && m_timeStampDiff)
                speed = (ydiff/2) / m_timeStampDiff;

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

    eventManager()->updateAfterEvent();
}


bool VScrollArea::moveDown(int steps)
{
    m_coordPos += steps;

    Widget *w = widgetItem(item());
    while(w && 0 < (m_coordPos)) {

        if(m_item < 1)
            break;

        m_item --;


        m_coordPos -= w->realRect().h();
        w = widgetItem(item());
    }

    if(item() == 0) {

        Widget *w = widgetItem(0);
        if(!w)
            return false; //Oops

        if(m_coordPos - checkItemSizes(w) > realRect().h() - w->realRect().h()) {
            m_coordPos = checkItemSizes(w) + realRect().h() - w->realRect().h();
            return false;
        }
    }

    return true;
}


bool VScrollArea::moveUp(int steps)
{
    m_coordPos -= steps;

    Widget *w = widgetItem(item());
    while(w && w->realRect().h() < -(m_coordPos)) {

        if(m_item+1 >= count())
            break;

        m_item ++;


        m_coordPos += w->realRect().h();
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



void VScrollArea::startMove(int speed, int potencial, Direction d)
{
    //printf("startMove()\n");

    m_timerType = TimerWork::ScrollFading;
    m_timerSpeed = speed;
    m_potencialOfHiding = potencial;
    m_timerValue = 0;
    m_timerDirectionMove = d;

    Timer::start(30);
}



void VScrollArea::fixupViewPosition()
{
    //auto w = lastWidgetItem();

    if(item() == 0 && m_coordPos/*-checkItemSizes(w)*/ > 0) {

        //printf(" -> m_coordPos: %d\n", m_coordPos);

        PosFixup.distance = m_coordPos;
        PosFixup.speed = 10;
        PosFixup.boost = 20;//%
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
        PosFixup.boost = 20;//%
        PosFixup.direction = Direction::Down;

        m_timerType = TimerWork::ScrollFixup;
        Timer::start(30);
    }
}


void VScrollArea::breakScrolling()
{
    if(m_timerType == TimerWork::ScrollFading) {
        Timer::stop();
    }
}


void VScrollArea::resetViewPosition()
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


void VScrollArea::setViewCoord(int c)
{
    m_coordPos = c;
}


void VScrollArea::setItem(int c)
{
    if(c < 0 || c >= m_linesCount)
        return;

    m_item = c;
}


void VScrollArea::setLinesCount(int c)
{
    m_linesCount = c;
}


bool VScrollArea::isAutoScrollActive() const
{
    if(m_timerType != TimerWork::NoWork && Timer::isActive())
        return true;
    return false;
}



void VScrollArea::addItem(Widget *w)
{
    m_items.push_back(w);
}


void VScrollArea::clear()
{
    m_items.clear();
}


int VScrollArea::listHeightInRect()
{
    int h = 0;
    int i = 0;

    for(i = count()-1; i> -1; --i) {

        Widget *w = widgetItem(i);
        if(!w)
            break;

        h += w->realRect().h();
        if(h >= realRect().h())
            break;
    }

    return h;
}


int VScrollArea::leastFreePage()
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
    int pos_y = 0;

    for(int i = m_item; i < count(); ++i)
    {
        item = widgetItem(i);
        if(!item)
            break;

        pos_y += item->rect().h();

        if(pos_y+m_coordPos >= rect().h()) {
            return 0;
        }
    }


    int lol_h = 0;

    for(int i = count()-1; i > -1; --i)
    {
        item = widgetItem(i);
        if(!item)
            break;

        lol_h += item->rect().h();
        if(lol_h >= rect().h()) {
            lol_h -= lol_h - rect().h();
            break;
        }
    }

    //printf("lol_h: %d pos_y: %d\n", lol_h, pos_y);
    return lol_h - pos_y - m_coordPos;
}


void VScrollArea::timerEvent()
{
    switch(m_timerType)
    {
        case TimerWork::ScrollFading:

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
                        m_potencialOfHiding += 4;
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
                        m_potencialOfHiding += 4;
                    }
                    break;
                }

                case Direction::No:
                    break;
            }

            eventManager()->updateAfterEvent();
            break;


        case TimerWork::ScrollFixup:

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


        case TimerWork::NoWork:
            break;
    }
}

