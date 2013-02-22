

#include "ActiveArea.h"
#include <stdlib.h>
#include <stdio.h>

void activeAreaPaint(ActiveArea *field);


static void *__first_item_back(GLQueueList *q) {
    return q->first;
}

static void *__next_item_back(GLQueueListItem *q) {
    return q->next;
}


static void *__first_item_front(GLQueueList *q) {
    return q->last;
}

static void *__next_item_front(GLQueueListItem *q) {
    return q->prev;
}


void activeAreaActionHandler(ActiveArea *field, int action, int x, int y)
{
    if(field->touched_item) {
        if(action == TOUCH_ACTION_RELEASE) {
            activeAreaTouchItem(field->touched_item, action, x, y, 1);
            field->touched_item = 0;
            return;
        }

        field->touched_item->is_moving = 1;

        activeAreaTouchItem(field->touched_item, action, x, y, 1);
        return;
    }

    void *(*_fitem)(GLQueueList *) = 0;
    void *(*_nitem)(GLQueueListItem *) = 0;

    if(field->is_front_touch) {
        _fitem = __first_item_front;
        _nitem = __next_item_front;
    } else {
        _fitem = __first_item_back;
        _nitem = __next_item_back;
    }

    for(GLQueueListItem *item = _fitem(&field->item_list); item; item = _nitem(item))
    {
        ActiveAreaItem *titem = *glQueueListItemBody(item, ActiveAreaItem **);

        if(titem->is_fullscreen_blocked) {

            if(x >= field->x+titem->x && x < field->x+titem->x+titem->w &&
                    y >= field->y+titem->y && y < field->y+titem->y+titem->h)
            {

                field->touched_item = titem;
                field->touched_item->is_offscreen_touch = 0;
                activeAreaTouchItem(titem, action, x, y, 1);

            } else {
                field->touched_item = titem;
                field->touched_item->is_offscreen_touch = 1;
                activeAreaTouchItem(titem, action, x, y, 1);
            }

            // полноэкранная блокировка
            break;

        } else {
            if(x >= field->x+titem->x && x < field->x+titem->x+titem->w &&
                    y >= field->y+titem->y && y < field->y+titem->y+titem->h)
            {

                field->touched_item = titem;
                field->touched_item->is_offscreen_touch = 0;
                activeAreaTouchItem(titem, action, x, y, 1);

                if(titem->is_blockable)
                    break;
            }
        }
    }
}




int activeAreaCreate(ActiveArea *field, int x, int y, int w, int h)
{
    glQueueListCreate(&field->item_list);
    field->touched_item = 0;
    field->is_front_paint = 1;
    field->is_front_touch = 0;
    field->x = x;
    field->y = y;
    field->w = w;
    field->h = h;
    return 0;
}


int activeAreaDestroy(ActiveArea *field)
{
    for(GLQueueListItem *i = field->item_list.first; i;)
    {
        GLQueueListItem *tmp = i;
        i = i->next;
        free(tmp);
    }

    field->item_list.first = 0;
    field->item_list.last = 0;

    glQueueListDestroy(&field->item_list);
    return 0;
}


int activeAreaItemCreate(ActiveAreaItem *item, int x, int y, int w, int h, int blockabdle)
{
    item->is_blockable = blockabdle;
    item->is_fullscreen_blocked = 0;
    item->is_offscreen_touch = 0;
    item->is_fullscreen_paint_blocked = 0;
    item->x = x;
    item->y = y;
    item->w = w;
    item->h = h;
    return 0;
}


int activeAreaPushItem(ActiveArea *field, ActiveAreaItem *item)
{
    if(!item)
        return -1;

    return glQueueListPush(&field->item_list, &item, sizeof(item))? 0 : -1;
}


int activeAreaPushFrontItem(ActiveArea *field, ActiveAreaItem *item)
{
    if(!item)
        return -1;

    return glQueueListPushFront(&field->item_list, &item, sizeof(item))? 0 : -1;
}


int activeAreaInsertItem(ActiveArea *field, ActiveAreaItem *item, int at)
{
    if(!item)
        return -1;

    return glQueueListInsert(&field->item_list, &item, sizeof(item), at)? 0 : -1;
}


GLQueueList *activeAreaItemsQueue(ActiveArea *field)
{
    return &field->item_list;
}


ActiveAreaItem *activeAreaQueueItem(ActiveArea *field, int at)
{
    if(!field || at < 0)
        return 0;

    GLQueueListItem *i = glQueueListItem(&field->item_list, at);

    return i? *glQueueListItemBody(i, ActiveAreaItem **) : 0;
}


int activeAreaPopItem(ActiveArea *field, ActiveAreaItem *_item)
{
    if(!_item)
        return -1;
    GLQueueListItem *item = 0;

    for(item = field->item_list.first; item; item = item->next)
    {
        ActiveAreaItem *titem = *glQueueListItemBody(item, ActiveAreaItem **);
        if(titem == _item)
            goto __found;
    }

    printf("activeAreaPopItem(%X): Not found\n", (unsigned int)_item);
    return -1;

__found:
    glQueueListPop(&field->item_list, item);

    return 0;
}


void activeAreaTouchAction(ActiveArea *field, int action, int x, int y)
{
    activeAreaActionHandler(field, action, x, y);
}




void activeAreaPaintAction(ActiveArea *field)
{
    void *(*_fitem)(GLQueueList *) = 0;
    void *(*_nitem)(GLQueueListItem *) = 0;

    if(field->is_front_paint) {
        _fitem = __first_item_front;
        _nitem = __next_item_front;
    } else {
        _fitem = __first_item_back;
        _nitem = __next_item_back;
    }

    for(GLQueueListItem *item = _fitem(&field->item_list); item; item = _nitem(item))
    {
        ActiveAreaItem *titem = *glQueueListItemBody(item, ActiveAreaItem **);
        if(titem->paintEvent)
            titem->paintEvent(titem);

        if(titem->is_fullscreen_paint_blocked)
            break;
    }
}


void activeAreaTouchItem(ActiveAreaItem *item, int action, int x, int y, char invoke)
{
    switch(action)
    {
        case TOUCH_ACTION_PRESS:
            item->cur_x = item->touched_x = x;
            item->cur_y = item->touched_y = y;

            item->is_moved = 0;
            item->is_moving = 0;
            item->is_touched = 1;
            break;

        /*case TOUCH_ACTION_RELEASE:
            item->is_moving = 0;
            item->is_touched = 0;
            break;*/

        case TOUCH_ACTION_MOVE:
            item->is_moving = 1;
            item->is_moved = 1;
            break;
    }

    if(invoke && item->touchEvent)
        item->touchEvent(item, action, x, y);

    if(action == TOUCH_ACTION_RELEASE) {
        item->is_moving = 0;
        item->is_touched = 0;
    }
}
