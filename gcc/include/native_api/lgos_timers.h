
#ifndef __LGOS_TIMERS_H__
#define __LGOS_TIMERS_H__

#include "swihelper.h"

typedef struct {
  int    period_ms;
  int    period;
  int    pointer;
  void (*routune)(int arg);
  int    unk_1;
  char   is_loop;
  char   is_start;
  short  unk_2;
}LGOS_TIMER;


__inl
int LGOS_Timer_Create(LGOS_TIMER *timer, char *name)
__def( 0x120, int, timer, name)

__inl
int LGOS_Timer_Delete(LGOS_TIMER *timer)
__def( 0x121, int, timer)

__inl
int LGOS_Timer_SetLoop(LGOS_TIMER *timer, int isloop)
__def( 0x122, int, timer, isloop)

__inl
int LGOS_Timer_SetProc(LGOS_TIMER *timer, void (*routune)(void *user), void *user)
__def( 0x123, int, timer, routune, user)

__inl
int LGOS_Timer_SetPeriod(LGOS_TIMER *timer, int period_ms, int period)
__def( 0x124, int, timer, period_ms, period)

__inl
int LGOS_Timer_Start(LGOS_TIMER *timer)
__def( 0x125, int, timer)

__inl
int LGOS_Timer_Stop(LGOS_TIMER *timer)
__def( 0x126, int, timer)

__inl
int LGOS_Timer_IsStarted(LGOS_TIMER *timer, unsigned int *is_started)
__def( 0x127, int, timer, is_started)


#endif // __LGOS_TIMERS_H__

