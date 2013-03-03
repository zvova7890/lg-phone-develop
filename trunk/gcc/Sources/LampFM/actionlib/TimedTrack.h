

#ifndef __TIMED_TRACK_H__
#define __TIMED_TRACK_H__


#include <TimerWrap.h>



typedef struct
{
    TimerWrap timer;
    int count;
    int add, stop_val;
    char m_isActive;

    void (*action)(void *);
    int action_on_than;
    char _active; // 0 - inactive, 1 - is bigger, 2 - is smaller
    char one_call_action;
    char not_call;
    unsigned int magic;
    void *user;
}TimedTrack;



#ifdef __cplusplus
extern "C" {
#endif


int timedTrackCreate(TimedTrack *t, int initial_count, int timer_type, void *user);
int timedTrackDestroy(TimedTrack *t);
void timedTrackAddingValue(TimedTrack *t, int val);
int timedTrackStartCount(TimedTrack *t, int period);
int timedTrackValue(TimedTrack *t);
int timedTrackStopCount(TimedTrack *t);
int timedTrackSetStopValue(TimedTrack *t, int val);
int timedTrackReset(TimedTrack *t, int count);
int timedTrackSetActionOnBiggerThan(TimedTrack *t, void (*action)(TimedTrack *), int count, char onecall);


#ifdef __cplusplus
}
#endif


#endif
