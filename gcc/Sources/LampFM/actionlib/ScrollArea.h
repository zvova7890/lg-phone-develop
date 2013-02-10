

#ifndef __SCROLL_AREA_H__
#define __SCROLL_AREA_H__


#include <ActiveArea.h>
#include <TimedTrack.h>



#define MAX_TIMER_SCROLL_VALUE 30
#define MAX_TIMER_SCROLL_VALUE_2 10


typedef struct
{
    ActiveAreaItem a;
    int id;
    char freeable;
    void *scroll_area;
    //void (*paintEvent)(void *area, int x, int y);
    //void (*touchEvent)(void *area, int action, int x, int y);
    //void (*destroyEvent)(void *area);
    void *user;
}ScrollAreaItem;



typedef struct
{
    ActiveAreaItem t;
    ScrollAreaItem *touched_item;
    TimedTrack speed_meter;
    int icount;
    int item;
    int item_step;

    char is_touched, is_moving;
    int cx, cy, lcx, lcy;
    int last_action_y;
    int route_changed_x, route_changed_y;
    int scrolling_route;
    int displaying_items;


    /* automatic scroll */
    struct {
        TimerWrap timer;
        char active;
        int val_start, val_end, distance, sign;
        int fading;
        int y_cnt;
        int timeStamp, timeStampDiff;
        int impulse, impulse_y;
        char type, scroll_may_stop;

    } auto_scroll;

    ScrollAreaItem *(*getItem)(void *, int index);
    void *user;
    void (*needUpdate)(void *user);
    void *need_update_user;
}ScrollArea;


#ifdef __cplusplus
extern "C" {
#endif



int scrollAreaCreate(ScrollArea *area, int item_step, void *user);
int scrollAreaDestroy(ScrollArea *area);
int scrollAreaCleanupItems(ScrollArea *area);
void scrollAreaPaint(ScrollArea *area);
void scrollAreaTouch(ScrollArea *area, int action, int x, int y);
int scrollAreaResetScroll(ScrollArea *area);
void scrollAreaStopAutoScroll(ScrollArea *area);
void scrollAreaCheckAndFixScrollPosition(ScrollArea *area);
int scrollAreaFullReset(ScrollArea *area);

ScrollAreaItem *scrollAreaCreateItem(ScrollAreaItem *item, ScrollArea *area, void (*paint)(ScrollAreaItem *), void (*touch)(ScrollAreaItem *, int, int, int), void *user);


#ifdef __cplusplus
}
#endif

#endif
