
#include <ScrollArea.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <gl.h>


#undef printf
#define printf(...)


ScrollAreaItem *getScrollAreaItem(ScrollArea *area, int index)
{
    if(area->getItem)
        return area->getItem(area, index);

    return 0;
}


static inline void scrollAreaNeedUpdate(ScrollArea *area)
{
    if(area->needUpdate)
        area->needUpdate(area->need_update_user);
}


int scrollAreaUpdateCoordinates(ScrollArea *area, int rectable)
{
    int diff = area->cy;

    if(area->scrolling_route == 1) {

        if(area->item > 0) {

            while(area->cy > 0) {
                area->item --;
                if(area->item < 0) {
                    area->item = 0;
                    break;
                }

                ScrollAreaItem *i = getScrollAreaItem(area, area->item);
                if(!i)
                    break;

                int sub = i->a.h+area->item_step;
                area->cy -= sub;
                area->lcy -= sub;
            }
        }

    } else if(area->scrolling_route == 2) {


        if(area->item < area->icount) {
            ScrollAreaItem *i = getScrollAreaItem(area, area->item);
            if(!i)
                return area->cy - diff;
            while(area->cy < -(i->a.h + area->item_step)) {
                area->item ++;

                if(area->item >= area->icount) {
                    area->item = area->icount-1;
                    break;
                }

                i = getScrollAreaItem(area, area->item);
                if(!i)
                    break;

                int add = i->a.h+area->item_step;
                area->cy += add;
                area->lcy += add;
            }
        }
    }


    if(rectable) {
        ScrollAreaItem *i = getScrollAreaItem(area, area->item);
        if(!i)
            return area->cy - diff;

        if(area->item == 0 && area->cy > (area->t.h) - i->a.h + area->item_step) {
            area->cy = (area->t.h) - i->a.h + area->item_step;
            area->auto_scroll.scroll_may_stop = 1;
        }

        else if(area->item == area->icount-1 && area->cy < 0) {
            area->cy = 0;
            area->auto_scroll.scroll_may_stop = 1;
        }
    }

    return area->cy - diff;
}


int scrollAreaMove(ScrollArea *area, int x, int y)
{
    ((void)x);

    int last_cy = area->cy;
    area->cy = area->lcy + (y - area->t.touched_y);
    char route_changet = 0;

    if(last_cy < area->cy && area->scrolling_route != 1) {
        area->route_changed_y = area->cy;
        area->scrolling_route = 1; // scrolling down
        route_changet = 1;

    } else if(last_cy > area->cy && area->scrolling_route != 2) {
        area->route_changed_y = area->cy;
        area->scrolling_route = 2; // scrolling up
        route_changet = 1;
    }


    return route_changet;
}


void scrollAreaStopAutoScroll(ScrollArea *area)
{
    if(area->speed_meter.m_isActive) {
        timedTrackStopCount(&area->speed_meter);
        TimerStop(&area->auto_scroll.timer);
    }

    area->auto_scroll.active = 0;
    area->is_moving = 0;
    area->is_touched = 0;

    //scrollAreaCheckAndFixScrollPosition(area);
}


int scrollAreaGetItemByCoordinates(ScrollArea *area, int x, int y)
{
    ((void)x);

    if(area->icount < 1)
        return -1;

    ScrollAreaItem *item = getScrollAreaItem(area, area->item);
    if(!item)
        return -1;

    int start_y = item->a.y;
    for(int i=0; area->item+i <area->icount; ++i) {

        item = getScrollAreaItem(area, area->item+i);
        if(!item) {
            printf("That is mega trololo o_O, %d\n", area->item+i);
            break;
        }

        if(y >= start_y && y < start_y+item->a.h) {
            return area->item+i;
        }

        printf("start_y: %d, end_y: %d\n", start_y, start_y+item->a.h);

        start_y += item->a.h + area->item_step;
    }

    printf("Not found item, at: %dx%d, cur: %d, disp: %d\n", x, y, area->item, area->displaying_items);
    return -1;
}


/*
void scrollAreaTimerStart(ScrollArea *area)
{

}
*/

void scrollAreaReleaseActionProvider(ScrollArea *area, int action, int x, int y)
{
    area->is_touched = 0;
    area->is_moving = 0;

    if(area->touched_item) {
        area->touched_item->a.touchEvent((struct _ActiveAreaItem *)area->touched_item, action, x, y);
        area->touched_item = 0;
    }

    scrollAreaCheckAndFixScrollPosition(area);
}


void scrollAreaCheckAndFixScrollPosition(ScrollArea *area)
{
    printf("scrollAreaCheckAndFixScrollPosition 1\n");

    if(area->icount < 1)
        return;


    printf("area->item: %d area->cy: %d\n", area->item, area->cy);

    if(area->item == 0 && area->cy > 0) {

        TimerStop(&area->auto_scroll.timer);

        area->auto_scroll.sign = 1;

        area->auto_scroll.val_start = 0;
        area->auto_scroll.val_end = area->cy+1;

        area->scrolling_route = 2;

        area->auto_scroll.active = 1;
        area->auto_scroll.type = 2;

        TimerStart(&area->auto_scroll.timer, 5);

    } else {

        TimerStop(&area->auto_scroll.timer);


        ScrollAreaItem *item = 0;

        printf("scrollAreaReleaseActionProvider 3\n");

        int pos_y = 0;

        for(int i = area->item; i<area->icount; ++i)
        {
            item = getScrollAreaItem(area, i);
            if(!item)
                break;

            pos_y += item->a.h + area->item_step;

            if(pos_y+area->cy >= area->t.h) {
                printf("%d > %d???\n", pos_y, area->t.h);
                goto end;
            }
        }


        int lol_h = 0;

        for(int i = area->icount-1; i > -1; --i)
        {
            item = getScrollAreaItem(area, i);
            if(!item)
                break;

            lol_h += item->a.h + area->item_step;
            if(lol_h >= area->t.h) {
                lol_h -= lol_h - area->t.h;
                break;
            }
        }

        printf("lol_h: %d pos_y: %d\n", lol_h, pos_y);

        area->auto_scroll.val_start = 0;
        area->auto_scroll.val_end = lol_h - pos_y - area->cy + 1;

        printf("-> area->auto_scroll.val_end: %d\n", area->auto_scroll.val_end);

        area->scrolling_route = 1;
        area->auto_scroll.sign = 1;

        area->auto_scroll.active = 1;
        area->auto_scroll.type = 2;
        TimerStart(&area->auto_scroll.timer, 5);
    }

end:

    printf("scrollAreaReleaseActionProvider 5\n");
}


static inline void __resetTimer(ScrollArea *area)
{
    timedTrackStopCount(&area->speed_meter);
    timedTrackReset(&area->speed_meter, 0);
    timedTrackStartCount(&area->speed_meter, 20);
}


void scrollAreaTouchActionHandler(ScrollArea *area, int action, int x, int y)
{
    printf("action: %d x: %d y: %d ty: %d - %d\n", action, x, y, area->t.touched_y, area->is_touched);

    switch(action)
    {
        case TOUCH_ACTION_PRESS:

            if(area->speed_meter.m_isActive) {
                timedTrackStopCount(&area->speed_meter);
                TimerStop(&area->auto_scroll.timer);
            }

            ScrollAreaItem *_item = 0;
            area->auto_scroll.active = 0;
            area->lcx = area->cx;
            area->lcy = area->cy;
            area->last_action_y = y;
            area->is_touched = 1;
            area->is_moving = 0;
            area->touched_item = 0;
            timedTrackSetStopValue(&area->speed_meter, INT_MAX);

            printf("Moving started area->last_action_y: %d\n", area->last_action_y);
            area->auto_scroll.y_cnt = 0;
            area->auto_scroll.timeStamp = 0;
            area->auto_scroll.timeStampDiff = 0;
            area->auto_scroll.impulse_y = y;
            area->auto_scroll.impulse = 0;
            area->auto_scroll.scroll_may_stop = 0;
            __resetTimer(area);

            int item = scrollAreaGetItemByCoordinates(area, x, y);

            if(item > -1) {
                _item = getScrollAreaItem(area, item);
            }

            if(_item && _item->a.touchEvent) {
                area->touched_item = _item;
                area->touched_item->a.touchEvent((struct _ActiveAreaItem*)area->touched_item, action, x, y);
            } else {
                printf("Ololo, on item: %d\n", item);
            }

            break;

        case TOUCH_ACTION_RELEASE:

            if(!area->is_touched)
                return;

            area->is_touched = 0;

            if(area->is_moving) {

                if(area->item == 0 && area->cy > 0) {
                    goto __release_notify;
                } else if(area->icount - area->item == area->displaying_items) {
                    goto __release_notify;
                }

                if(area->auto_scroll.timeStampDiff)
                    area->auto_scroll.timeStampDiff = timedTrackValue(&area->speed_meter);
                else
                    area->auto_scroll.timeStampDiff = (area->auto_scroll.timeStampDiff + (timedTrackValue(&area->speed_meter) - area->auto_scroll.timeStamp))/2;

                timedTrackStopCount(&area->speed_meter);

                int s = abs(glMax(y, area->last_action_y) - glMin(y, area->last_action_y) )+1;
                int ltime_diff = timedTrackValue(&area->speed_meter) - area->auto_scroll.timeStamp;
                int time_diff = (ltime_diff + area->auto_scroll.timeStampDiff)/2;

                /*if(s time_diff)
                    area->auto_scroll.distance = 0;
                else
                    */
                area->auto_scroll.distance /= (time_diff/2);
                area->auto_scroll.distance += (s)+((s/time_diff))*2.5 - (area->auto_scroll.impulse/(time_diff));
                area->auto_scroll.fading = time_diff - (time_diff * 10 / 100) + 1;


                printf(" -- >! last_action_y: %d\n", area->last_action_y);
                printf("area->auto_scroll.fading: %d time_diff: %d, s: %d, s/diff: %d, dist: %d, impulse: %d\n", area->auto_scroll.fading, time_diff, s, s/time_diff,
                       area->auto_scroll.distance, ltime_diff-time_diff);


                if(area->auto_scroll.distance > 0 && area->auto_scroll.fading > 0) {
                    area->auto_scroll.active = 1;
                    area->auto_scroll.type = 1;
                    TimerStart(&area->auto_scroll.timer, 4);
                }

            } else {
__release_notify:
                printf("area->icount - area->item: %d - %d\n", area->icount - area->item, area->displaying_items);
                scrollAreaReleaseActionProvider(area, action, x, y);
            }

            break;

        case TOUCH_ACTION_MOVE:
            if(!area->is_touched)
                break;

            if(area->touched_item) {
                area->touched_item->a.touchEvent((struct _ActiveAreaItem*)area->touched_item, action, x, y);
            }

            if(!area->is_moving) {
                area->is_moving = 1;
            }

            char route_changet = scrollAreaMove(area, x, y);
            scrollAreaUpdateCoordinates(area, 1);

            if(route_changet) {

                area->auto_scroll.timeStamp = timedTrackValue(&area->speed_meter);
                area->auto_scroll.timeStampDiff = 0;
                area->last_action_y = y;
                area->auto_scroll.distance = 0;

                area->auto_scroll.y_cnt = 0;
            }

            area->auto_scroll.impulse = glMax(area->auto_scroll.impulse_y, y)-glMin(area->auto_scroll.impulse_y, y);
            area->auto_scroll.impulse_y = y;

            area->auto_scroll.y_cnt += abs(glMax(area->last_action_y, y) - glMin(area->last_action_y, y));

            if(timedTrackValue(&area->speed_meter) > area->auto_scroll.timeStamp+10) {
                area->last_action_y = y;

                if(area->auto_scroll.timeStampDiff)
                    area->auto_scroll.timeStampDiff = timedTrackValue(&area->speed_meter);
                else
                    area->auto_scroll.timeStampDiff = (area->auto_scroll.timeStampDiff + (timedTrackValue(&area->speed_meter) - area->auto_scroll.timeStamp))/2;

                area->auto_scroll.timeStamp = timedTrackValue(&area->speed_meter);
                area->auto_scroll.y_cnt = 0;
            }

            break;


        default:
        {
            ScrollAreaItem *_item = 0;
            int item = scrollAreaGetItemByCoordinates(area, x, y);

            if(item > -1) {
                _item = getScrollAreaItem(area, item);
            }


            if(_item && _item->a.touchEvent) {
                area->touched_item = _item;
                area->touched_item->a.touchEvent((struct _ActiveAreaItem*)area->touched_item, action, x, y);
            } else {
                printf("Ololo, on item: %d\n", item);
            }
            break;
        }

    }

    scrollAreaNeedUpdate(area);
}



static void timerKineticScrollAreaHandler(TimerWrap *timer, void *user)
{
    ((void)user);

    ScrollArea *area = timer->user;
    if(area->auto_scroll.active == 0)
        return;

    int val = 0;

    /* distance depended */
    if(area->auto_scroll.type == 2) {

        if(area->auto_scroll.sign > 0) {

            if(area->auto_scroll.val_start >= area->auto_scroll.val_end) {
                goto __fading_dep_end;
            }

            int left = abs(area->auto_scroll.val_end - area->auto_scroll.val_start);
            val = left * 50 / 100;
            if(val < 1)
                val = 1;

            area->auto_scroll.val_start += val;
            printf("area->auto_scroll.val_start: %d\n", area->auto_scroll.val_start);

            if(area->auto_scroll.val_start + val > area->auto_scroll.val_end)
                val -= (area->auto_scroll.val_start + val) - area->auto_scroll.val_end;

            if(val < 1) {
                area->auto_scroll.val_start = area->auto_scroll.val_end;
                goto __fading_dep_end;
            }

        } else {

            if(area->auto_scroll.val_start <= area->auto_scroll.val_end) {
                goto __fading_dep_end;
            }

            int left = abs(area->auto_scroll.val_start -  area->auto_scroll.val_end);
            val = left * 50 / 100;
            if(val < 1)
                val = 1;

            area->auto_scroll.val_start -= val;

            if(area->auto_scroll.val_start - val < area->auto_scroll.val_end)
                val -= area->auto_scroll.val_end - (area->auto_scroll.val_start - val);

            if(val < 1) {
                area->auto_scroll.val_start = area->auto_scroll.val_end;
                goto __fading_dep_end;
            }
        }
    } else {

        if(area->auto_scroll.scroll_may_stop)
            goto __distance_dep_end;

        val = area->auto_scroll.distance * area->auto_scroll.fading / 100;

        if(val < 1) {
            goto __distance_dep_end;
        }

        area->auto_scroll.distance -= val;

    }


    printf(" -->b area->cy: %d\n", area->cy);

    if(area->scrolling_route == 2) {
        area->cy -= val;
    } else if(area->scrolling_route == 1){
        area->cy += val;

    }

    printf(" --> area->cy: %d\n", area->cy);
    scrollAreaUpdateCoordinates(area, 0);
    scrollAreaNeedUpdate(area);

    return;



__fading_dep_end:
    TimerStop(timer);
    area->auto_scroll.active = 0;
    scrollAreaNeedUpdate(area);
    return;


__distance_dep_end:
    TimerStop(timer);
    area->auto_scroll.active = 0;

    scrollAreaReleaseActionProvider(area, TOUCH_ACTION_RELEASE, area->cx, area->touched_item->a.y-area->cy);

    //area->need_update = 1;
}


int scrollAreaCreate(ScrollArea *area, int item_step, void *user)
{
    printf(" ============================= LOL ========================== \n");
    printf("scrollAreaCreate(%d, %d, %d, %d)\n",  area->t.x, area->t.y, area->t.w, area->t.h);

    area->item = 0;
    timedTrackCreate(&area->speed_meter, 0, 0, 0);
    timedTrackAddingValue(&area->speed_meter, 1);
    TimerCreate(&area->auto_scroll.timer, 1, timerKineticScrollAreaHandler, area);

    area->item_step = item_step;
    area->user = user;
    return 0;
}


int scrollAreaDestroy(ScrollArea *area)
{
    timedTrackDestroy(&area->speed_meter);
    TimerDestroy(&area->auto_scroll.timer);

    return scrollAreaCleanupItems(area);
}



int scrollAreaCleanupItems(ScrollArea *area)
{
    area->touched_item = 0;
    area->icount = 0;
    area->item = 0;
    return 0;
}


int scrollAreaResetScroll(ScrollArea *area)
{
    area->item = 0;
    area->touched_item = 0;

    scrollAreaStopAutoScroll(area);

    area->cx = 0;
    area->cy = 0;
    return 0;
}


int scrollAreaFullReset(ScrollArea *area)
{
    area->item = 0;
    area->touched_item = 0;
    area->icount = 0;
    area->cx = 0;
    area->cy = 0;
    area->displaying_items = 0;

    scrollAreaStopAutoScroll(area);
    return 0;
}


void scrollAreaPaint(ScrollArea *area)
{
    int x = area->cx + area->t.x, y = area->cy + area->t.y;

    area->displaying_items = 0;

    for(int i = area->item; i<area->icount; ++i)
    {
        ScrollAreaItem *item = getScrollAreaItem(area, i);
        if(!item)
            break;

        /*printf("X: %d\n", item->a.i.x);
        printf("paintEvent: %X\n", item->paintEvent);
        printf("scroll_area: %X\n", item->scroll_area);*/

        item->id = i;
        item->a.x = x;
        item->a.y = y;
        item->a.paintEvent((struct _ActiveAreaItem*)item);

        /*printf("Y: %d - %d; h: %d\n", item->a.y, x, item->a.h);
        printf("paintEvent: %X\n", item->a.paintEvent);
        printf("scroll_area: %X\n", item->scroll_area);*/


        y += item->a.h + area->item_step;
        area->displaying_items ++;

        if(y > area->t.y+area->t.h) {
            break;
        }
    }

}


void scrollAreaTouch(ScrollArea *area, int action, int x, int y)
{
    scrollAreaTouchActionHandler(area, action, x, y);
}


ScrollAreaItem *scrollAreaCreateItem(ScrollAreaItem *item, ScrollArea *area,
                                     void (*paint)(ScrollAreaItem *item),
                                     void (*touch)(ScrollAreaItem *item, int action, int x, int y),
                                     void *user)
{
    //printf("scrollAreaPushItem(%X, %X)\n", item, area);
    //activeAreaCreate((ActiveArea*)item, 0, 0, w, h);

    item->freeable = 1;
    item->a.paintEvent = (void (*)(struct _ActiveAreaItem*))paint;
    item->a.touchEvent = (void (*)(struct _ActiveAreaItem*, int, int, int))touch;
    item->scroll_area = area;
    item->user = user;

    return item;
}

