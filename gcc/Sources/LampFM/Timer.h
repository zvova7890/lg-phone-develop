#ifndef TIMER_H
#define TIMER_H

#include <TimerWrap.h>
#include "signals/signal.h"


class Timer
{
public:
    typedef signal_slot::multi_signal <void(Timer *)> signal;

    Timer(bool system = false);
    ~Timer();

    void start(int period);
    void stop();
    void pause();

    /* на уже рабочем таймере */
    void changePeriod(int period);

    virtual void timerEvent();

    inline signal & timerEventSignal() {
        return _timer_event;
    }

protected:
    static void timer_event(TimerWrap *tw, void *user);

private:
    bool _active, _created;
    char _timer_type;
    TimerWrap _timer;
    signal _timer_event;
};

#endif // TIMER_H
