#include "Timer.h"
#include <string.h>


void Timer::timer_event(TimerWrap *tw, void *user)
{
    ((void)tw);

    Timer *self = (Timer *)user;
    self->timerEvent();
}


Timer::Timer(bool system) :
    _active(false),
    _created(false),
    _timer_type(system? 0:1)
{
    memset(&_timer, 0, sizeof(_timer));
}


Timer::~Timer()
{
    if(_created) {
        TimerDestroy(&_timer);
        _created = false;
        _active = false;
    }
}


void Timer::start(int period)
{
    if(_active) {
        TimerStop(&_timer);
    }
    else if(!_created) {
        _created = true;
        TimerCreate(&_timer, _timer_type, timer_event, this);
    }

    TimerStart(&_timer, period);
}


void Timer::stop()
{
    if(_active) {
        TimerStop(&_timer);
        _active = false;
    }
    else if(_created) {
        _created = false;
        TimerDestroy(&_timer);
    }
}


void Timer::pause()
{
    if(_active) {
        TimerStop(&_timer);
        _active = false;
    }
}


void Timer::timerEvent()
{
    _timer_event.trigger(this);
}


void Timer::changePeriod(int period)
{
    if(_active) {
        TimerResetPeriod(&_timer, period);
    }
}
