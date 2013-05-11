#include <gl.h>
#include "HTextScroller.h"



HTextScroller::HTextScroller(EventManager *em, const Rect &r):
    Timer(),
    m_rect(r),
    m_pos(0),
    m_textAttrs(0),
    m_moveSign(-2),
    m_textSize(15),
    m_isActive(false),
    m_eventMngr(em),
    m_textWidth(0)
{
    //m_timer.timerEventSignal().connect(this, &HTextScroller::timerEvent, std::placeholders::_1);
}


HTextScroller::~HTextScroller()
{
    stop();
}


void HTextScroller::paintEvent()
{
    //if(!m_isActive)
      //  return;

    if(m_textWidth < m_rect.w())
        m_textSmallerThan.trigger(this);

    glSaveClipRegion();

    glSetClipRegion(m_rect.x(), m_rect.y(), m_rect.x2(), m_rect.y2());
    glDrawString(m_text.c_str(), m_rect.x()+m_pos, m_rect.y(), m_rect.x2(), m_rect.y2(), m_textSize, m_textAttrs, 0, 128);

    glRestoreClipRegion();

    if(m_pos >= 0) {
        m_pos = 0;
        m_moveSign = -2;
    }

    if(m_textWidth > m_rect.w() && m_textWidth-m_rect.w() <= glAbs(m_pos)) {
        m_moveSign = 2;
    }
    //printf("m_textWidth: %d  m_moveSign: %d  m_pos: %d\n", m_textWidth, m_moveSign, m_pos);

    if(m_update && m_textWidth > m_rect.w())
        m_pos += m_moveSign;

    m_update = false;
}


void HTextScroller::timerEvent()
{
    m_update = true;
    m_eventMngr->updateAfterEvent();
    //m_eventMngr->paint();
    //m_eventMngr->refresh();
}


void HTextScroller::recalcTextWidth()
{
    unsigned int h, top;
    m_textWidth = glStringMetrics(m_textSize, m_text.c_str(), &h, &top, 128);
}


void HTextScroller::start(int speed)
{
    if(m_isActive)
        return;

    m_speed = speed;
    Timer::start(speed);
    m_isActive = true;
}


void HTextScroller::stop()
{
    if(m_isActive) {
        Timer::stop();
        m_isActive = false;
    }
}


void HTextScroller::pause()
{
    Timer::pause();
}


void HTextScroller::resume()
{
    Timer::resume();
}


void HTextScroller::reset()
{
    m_pos = 0;
}


void HTextScroller::setRect(const Rect &r)
{
    m_rect = r;
}


void HTextScroller::setText(const std::string &t)
{
    m_text = t;
    recalcTextWidth();
}
