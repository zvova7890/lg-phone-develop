
#include <stdio.h>
#include <pxeapi.h>
#include <TimerWrap.h>
#include <nucleus.h>


static timers_t timers[128];


#undef NU_Sleep
#define NU_Sleep(x)

__attribute__((constructor(101)))
void __init_timers()
{
    //printf("void __init_timers()\n");

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


void __timer_notifier(int timer_id)
{
    //printf("__timer_notifier: %d\n", timer_id);
    TimerWrap *timer = timers[timer_id].user;

    if(timer_id > 0 && timer_id < 128 && timers[timer_id].id == timer_id && timers[timer_id].event && timer->magic == 0xF3FAFFAC) {
        timers[timer_id].event(timers[timer_id].user, ((TimerWrap*)timers[timer_id].user)->user);
    }
}


static void timerHandler(void *user)
{
    TimerWrap *timer = user;

    if(timer->magic == 0xF3FAFFAC)
        timer->event(timer, timer->user);
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
        NU_Sleep(10);
        i = LGOS_Timer_Create(&timer->timer, "lol");

        NU_Sleep(10);
        if(!i && !LGOS_Timer_SetProc(&timer->timer, timerHandler, timer))
            timer->magic = 0xF3FAFFAC;

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
            NU_Sleep(10);
            return LGOS_Timer_Delete(&timer->timer);
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
            NU_Sleep(10);
            int i = LGOS_Timer_SetLoop(&timer->timer, 1);
            NU_Sleep(15);
            i += LGOS_Timer_SetPeriod(&timer->timer, period, period);
            NU_Sleep(15);
            i += LGOS_Timer_Start(&timer->timer);

            if(!i)
                timer->active = 1;

            return i;
        }
    } else {
        //printf("TimerStart - timer->id: %d\n", timer->id);
        NU_Sleep(10);

        if(timer->magic_id == 0xAFFDDDFF && Timer_CreateEvent(timer->id, period, 1)) {
            timer->magic = 0xF3FAFFAC;
            timer->active = 1;
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
            NU_Sleep(15);
            return LGOS_Timer_Stop(&timer->timer);
        }
    } else {
        if(timer->magic == 0xF3FAFFAC) {
            timer->magic = 0;
            timer->active = 0;
            NU_Sleep(10);
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
            NU_Sleep(10);
            return LGOS_Timer_SetPeriod(&timer->timer, period, period);
        }
    } else {
        if(timer->magic == 0xF3FAFFAC) {

            Timer_KillEvent(timer->id);
            NU_Sleep(60);
            if(!Timer_CreateEvent(timer->id, period, 1))
                timer->magic = 0;
            else
                return 0;
        }
    }

    return -1;
}

