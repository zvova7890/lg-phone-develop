#ifndef TIMERCOUNTER_H
#define TIMERCOUNTER_H


#include <functional>
#include <Core/Timer.h>



class TimerCounter : private Timer
{
public:
    TimerCounter(int initial_cout = 0);


    void start(int msec);
    void pause();
    void stop();
    void setFinalComp(std::function<bool(TimerCounter*)> f);
    void setValueOp(std::function<int(TimerCounter*)> f);


    inline int value() const {
        return m_value;
    }

    inline void reset(int v) {
        m_value = v;
    }

private:
    void timerEvent();

private:
    int m_value;
    char m_status;
    std::function<bool (TimerCounter *)> m_comp;
    std::function<int(TimerCounter*)> m_vop;
};

#endif // TIMERCOUNTER_H
