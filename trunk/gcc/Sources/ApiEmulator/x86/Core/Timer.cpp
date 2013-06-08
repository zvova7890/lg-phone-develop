
#include <string.h>
#include <stdio.h>
#include "Timer.h"
#include <Core/compatible.h>

#ifndef __PC_BUILD__
#define msec2timer(x) (x > 30? x - 30 : 1)
#else
#define msec2timer(x) (x+25)
#endif


typedef struct
{
    signed int id;
    void (*event)(void *, void *user);
    void *user;
}timers_t;


static timers_t timers[128];

__attribute__((constructor(101)))
void __init_timers()
{
    for(int i=0; i<128; ++i) {
        timers[i].id = -1;
        timers[i].event = 0;
    }
}


int getEmptyTimer()
{
    for(int i = 1; i<128; ++i)
    {
        if(timers[i].id < 0)
            return i;
    }

    return -1;
}


int allocTimerID()
{
    for(int i = 1; i<128; ++i)
    {
        if(timers[i].id < 0) {
            timers[i].id = i;
            return i;
        }
    }

    return -1;
}


extern "C"
void __timer_notifier(int timer_id)
{
    TimerWrap *timer = (TimerWrap *)timers[timer_id].user;

    if(timer_id > 0 && timer_id < 128 && timers[timer_id].id == timer_id && timers[timer_id].event && timer->magic == 0xF3FAFFAC) {
        timers[timer_id].event(timers[timer_id].user, ((TimerWrap*)timers[timer_id].user)->user);
    }
}


int TimerCreate(TimerWrap *timer, int type, void (*event)(TimerWrap *timer, void *user), void *user)
{

    int i = -1;
    timer->event = (void (*)(void *, void *))event;
    timer->user = user;
    timer->magic = 0;
    timer->active = 0;
    timer->type = type;
    timer->magic_id = 0;

    //printf("TimerCreate: type: %d\n", type);
    if(!type) {
        timer->id = -1;
        //i = LGOS_Timer_Create(&timer->timer, "lol");

        //if(!i && !LGOS_Timer_SetProc(&timer->timer, timerHandler, timer))
          //  timer->magic = 0xF3FAFFAC;

    } else {
        int id = allocTimerID();
        //printf("getEmptyTimer: %d\n", id);
        if(id < 0)
            return -1;

        timer->magic_id = 0xAFFDDDFF;
        timer->id = id;
        timers[id].id = id;
        timers[id].event = (void (*)(void *, void *))event;
        timers[id].user = timer;


        i = 0;
    }

    return i;
}


int TimerDestroy(TimerWrap *timer)
{
    if(!timer->type) {
        if(timer->magic == 0xF3FAFFAC) {
            timer->active = 0;
            timer->magic = 0;
            timer->id = -1;
            //NU_Sleep(10);
            //return LGOS_Timer_Delete(&timer->timer);
            return -1;
        }
    } else {
        int i = -1;
        if(timer->magic == 0xF3FAFFAC) {
            i = Timer_KillEvent(timer->id);
        }

        if(timer->magic_id == 0xAFFDDDFF) {

            if(timer->id > 0 && timer->id < 128)
                timers[timer->id].id = -1;
            timer->id = -1;
            timer->magic = 0;
            timer->magic_id = 0;
        }

        return i;
    }

    return -1;
}


int TimerStart(TimerWrap *timer, int period)
{
    timer->period = period;
    if(!timer->type) {
        if(timer->magic == 0xF3FAFFAC) {
            int i = -1;
            //int i = LGOS_Timer_SetLoop(&timer->timer, 1);
            //i += LGOS_Timer_SetPeriod(&timer->timer, period, period);
            //i += LGOS_Timer_Start(&timer->timer);

            if(!i)
                timer->active = 1;

            return i;
        }
    } else {

        //NU_Sleep(10);

        if(timer->magic_id == 0xAFFDDDFF && Timer_CreateEvent(timer->id, msec2timer(period), 1)) {
            timer->magic = 0xF3FAFFAC;
            timer->active = 1;
            //printf("TimerStart - timer->id: %d\n", timer->id);
            return 0;
        }


    }

    return -1;
}

int TimerStop(TimerWrap *timer)
{
    if(!timer->type) {
        if(timer->magic == 0xF3FAFFAC && timer->active) {
            timer->active = 0;
            //return LGOS_Timer_Stop(&timer->timer);
            return -1;
        }
    } else {
        if(timer->magic == 0xF3FAFFAC) {
            timer->magic = 0;
            timer->active = 0;
            return Timer_KillEvent(timer->id);
        }
    }

    return -1;
}


int TimerResetPeriod(TimerWrap *timer, int period)
{
    timer->period = period;

    if(!timer->type) {
        if(timer->magic == 0xF3FAFFAC) {
            //NU_Sleep(10);
            //return LGOS_Timer_SetPeriod(&timer->timer, period, period);
            return -1;
        }
    } else {
        if(timer->magic == 0xF3FAFFAC) {

            Timer_KillEvent(timer->id);
            if(!Timer_CreateEvent(timer->id, msec2timer(period), 1))
                timer->magic = 0;
            else
                return 0;
        }
    }

    return -1;
}






void Timer::timer_event(TimerWrap *tw, void *user)
{
    ((void)tw);

    Timer *self = (Timer *)user;
    self->timerEvent();
}


Timer::Timer() :
    _active(false),
    _created(false)
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

    if(!_created) {
        _created = true;
        TimerCreate(&_timer, 1, timer_event, this);
    }

    _active = true;
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


void Timer::resume()
{
    if(!_active) {
        start(_timer.period);
        _active = true;
    }
}


void Timer::resetPeriod(int p)
{
    if(_created) {
        TimerResetPeriod(&_timer, p);
    }
}

int Timer::period() const
{
    if(_active) {
        return _timer.period;
    }

    return -1;
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
