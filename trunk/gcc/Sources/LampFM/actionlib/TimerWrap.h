
#ifndef __TIMER_WRAP_H__
#define __TIMER_WRAP_H__

#include <lgos_timers.h>


typedef struct
{
    LGOS_TIMER timer;

    int id;
    void *user;
    int period;
    char type, active;
    unsigned int magic, magic_id;
    void (*event)(void *timer, void *user);
}TimerWrap;


typedef struct
{
    signed int id;
    void (*event)(void *, void *user);
    void *user;
}timers_t;




#ifdef __cplusplus
extern "C" {
#endif


int TimerCreate(TimerWrap *timer, int type, void (*event)(TimerWrap *timer, void *user), void *user);
int TimerDestroy(TimerWrap *timer);
int TimerStart(TimerWrap *timer, int period);
int TimerStop(TimerWrap *timer);
int TimerResetPeriod(TimerWrap *timer, int period);






#ifdef __cplusplus
}
#endif



#endif

