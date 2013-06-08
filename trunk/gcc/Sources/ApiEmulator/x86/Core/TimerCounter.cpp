#include "TimerCounter.h"




TimerCounter::TimerCounter(int initial_cout) :
    m_value(initial_cout),
    m_status(0)
{
    m_comp = [](TimerCounter *tc) {

        if(tc->value() > 65536)
            return true;

        return false;
    };

    m_vop = [](TimerCounter *tc) -> int {
        return tc->value()+1;
    };
}


void TimerCounter::start(int msec)
{
    //if(m_status != 2) {
    //    m_value = 0;
    //}

    if(m_status) {
        TimerCounter::stop();
    }

    Timer::start(msec);
    m_status = 1;
}


void TimerCounter::pause()
{
    if(m_status == 1) {
        Timer::pause();
        m_status = 2;
    }
}


void TimerCounter::stop()
{
    if(m_status) {
        Timer::stop();
        m_status = 0;
    }
}


void TimerCounter::setFinalComp(std::function<bool (TimerCounter *)> f)
{
    m_comp = f;
}


void TimerCounter::setValueOp(std::function<int (TimerCounter *)> f)
{
    m_vop = f;
}


void TimerCounter::timerEvent()
{
    if(m_comp(this)) {
        stop();
        return;
    }

    m_value = m_vop(this);
}

