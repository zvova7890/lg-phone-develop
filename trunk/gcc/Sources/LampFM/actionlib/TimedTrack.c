
#include <stdio.h>
#include <limits.h>
#include <TimedTrack.h>
#include <nucleus.h>


void timedTrackEventHandler(TimerWrap *t, void *user)
{
    TimedTrack *tt = (TimedTrack*)user;
    tt->count += tt->add;

    //printf("timedTrackEventHandler: %d\n", tt->add);

    if(tt->add > 0) {
        if(tt->count >= tt->stop_val) {
            tt->is_active = 0;
            TimerStop(t);
        }

    } else if(tt->add < 0) {
        if(tt->count <= tt->stop_val) {
            tt->is_active = 0;
            TimerStop(t);
        }
    }

    if(tt->_active == 1) {
        if(tt->count > tt->action_on_than && !tt->not_call) {
            tt->action(tt);
            if(tt->one_call_action)
                tt->not_call = 1;
        }

    } else if(tt->_active == 2) {

        if(tt->count < tt->action_on_than && !tt->not_call) {
            tt->action(tt);
            if(tt->one_call_action)
                tt->not_call = 1;
        }
    }
}



int timedTrackCreate(TimedTrack *t, int initial_count, int timer_type, void *user)
{
    t->count = initial_count;
    t->is_active = 0;
    t->add = 1;
    t->stop_val = INT_MAX;
    t->action = 0;
    t->_active = 0;
    t->user = user;
    t->magic = 0xFFAF33CD;
    return TimerCreate(&t->timer, timer_type, timedTrackEventHandler, t);
}


int timedTrackDestroy(TimedTrack *t)
{
    if(t->magic == 0xFFAF33CD) {
        t->is_active = 0;
        return TimerDestroy(&t->timer);
    }

    return -1;
}


int timedTrackSetStopValue(TimedTrack *t, int val)
{
    t->stop_val = val;
    return 0;
}


void timedTrackAddingValue(TimedTrack *t, int val)
{
    t->add = val;
}


int timedTrackStartCount(TimedTrack *t, int period)
{
    if(t->magic != 0xFFAF33CD)
        return -1;

    if(t->is_active)
        TimerStop(&t->timer);

    //NU_Sleep(10);
    t->is_active = 1;
    return TimerStart(&t->timer, period);
}


int timedTrackValue(TimedTrack *t)
{
    return t->count;
}


int timedTrackStopCount(TimedTrack *t)
{
    if(t->magic != 0xFFAF33CD)
        return -1;

    t->is_active = 0;
    return TimerStop(&t->timer);
}


int timedTrackReset(TimedTrack *t, int count)
{
    t->count = count;
    return 0;
}


int timedTrackSetActionOnBiggerThan(TimedTrack *t, void (*action)(TimedTrack *), int count, char onecall)
{
    t->action = (void (*)(void *))action;
    t->_active = 1; // bigger
    t->action_on_than = count;
    t->one_call_action = onecall;
    t->not_call = 0;
    return 0;
}


int timedTrackSetActionOnSmallerThan(TimedTrack *t, void (*action)(TimedTrack *), int count, char onecall)
{
    t->action = (void (*)(void *))action;
    t->_active = 2; // smaller
    t->action_on_than = count;
    t->one_call_action = onecall;
    t->not_call = 0;
    return 0;
}
