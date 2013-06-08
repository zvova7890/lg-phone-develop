
#ifndef __LGOS_TIMERS_H__
#define __LGOS_TIMERS_H__



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

#ifdef __cplusplus
extern "C" {
#endif


int LGOS_Timer_Create(LGOS_TIMER *timer, const char *name);
int LGOS_Timer_Delete(LGOS_TIMER *timer);
int LGOS_Timer_SetLoop(LGOS_TIMER *timer, int isloop);
int LGOS_Timer_SetProc(LGOS_TIMER *timer, void (*routune)(void *user), void *user);
int LGOS_Timer_SetPeriod(LGOS_TIMER *timer, int period_ms, int period);
int LGOS_Timer_Start(LGOS_TIMER *timer);
int LGOS_Timer_Stop(LGOS_TIMER *timer);
int LGOS_Timer_IsStarted(LGOS_TIMER *timer, unsigned int *is_started);


#ifdef __cplusplus
}
#endif

#endif // __LGOS_TIMERS_H__

