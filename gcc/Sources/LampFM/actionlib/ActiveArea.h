
#ifndef __ACTIVE_AREA_H__
#define __ACTIVE_AREA_H__

#include <pxeapi.h>
#include <gl.h>

/*
#define TOUCH_ACTION_PRESS 1
#define TOUCH_ACTION_MOVE 2
#define TOUCH_ACTION_RELEASE 3
*/


typedef struct _ActiveAreaItem
{
    short x, y;
    short w, h;
    void (*touchEvent)(struct _ActiveAreaItem *item, int action, int x, int y); // callback
    void (*paintEvent)(struct _ActiveAreaItem *item); // callback

    int touched_x, touched_y, cur_x, cur_y;
    char is_moving, is_blockable, is_touched, is_moved,
         is_fullscreen_blocked, is_fullscreen_paint_blocked, is_offscreen_touch;
    void *user;
}ActiveAreaItem;


typedef struct _ActiveArea
{
    short x, y;
    short w, h;
    GLQueueList item_list;
    ActiveAreaItem *touched_item;

    short touched_x, touched_y;
    char is_front_paint, is_front_touch;

    //void (*touchEvent)(struct _ActiveArea *field, int action, int x, int y); // call it for activate ActiveArea event
    //void (*paintEvent)(struct _ActiveArea *);
    void *user;
}ActiveArea;



#ifdef __cplusplus
extern "C" {
#endif



int activeAreaCreate(ActiveArea *field, int x, int y, int w, int h);
int activeAreaDestroy(ActiveArea *field);
int activeAreaItemCreate(ActiveAreaItem *item, int x, int y, int w, int h, int blockabdle);
int activeAreaPushItem(ActiveArea *field, ActiveAreaItem *item);
int activeAreaPushFrontItem(ActiveArea *field, ActiveAreaItem *item);
int activeAreaInsertItem(ActiveArea *field, ActiveAreaItem *item, int at);
GLQueueList *activeAreaItemsQueue(ActiveArea *field);
ActiveAreaItem *activeAreaQueueItem(ActiveArea *field, int at);
int activeAreaPopItem(ActiveArea *field, ActiveAreaItem *_item);
void activeAreaTouchAction(ActiveArea *field, int action, int x, int y);
void activeAreaPaintAction(ActiveArea *field);

void activeAreaTouchItem(ActiveArea *field, ActiveAreaItem *item, int action, int x, int y, char invoke);

#ifdef __cplusplus
}
#endif


#endif /*__TOUCH_FIELD_H__*/
