
#include <Api/ApiLinkLib/ApiLink.h>
#include <pxeapi.h>
#include <gl.h>
#include "objectmap.h"




static GLQueueList __global_map;



void initObjectMap()
{
    glQueueListCreate(&__global_map);
}



void clearObjectMap()
{
    GLQueueListItem *item = __global_map.first;

    for(; item; )
    {
        void *next = item->next;
        free(item);
        item = next;
    }

    memset(&__global_map, 0, sizeof(__global_map));
}



void objectMapPush(UIObject *obj)
{
    // we push a pointer on pointer
    glQueueListPush(&__global_map, &obj, sizeof(void*));
}



void objectMapPaintEvent()
{
    GLQueueListItem *item = __global_map.first;

    for(; item; item = item->next)
    {
        UIObject *obj = *glQueueListItemBody(item, UIObject**);

        if(obj->paintEvent)
            obj->paintEvent(obj);
    }
}



int objectMapTouchEvent(int action, int x, int y)
{
    static UIObject *_cobject = 0;
    GLQueueListItem *item = __global_map.first;

    int have_tbIk = 0;

    //printf(" --> x: %d\ny: %d\n", x, y);
    if( GrSys_GetGDIID() == 1) {
	
	/* retranslate coordinates */
        int t = x;

        x = y;
        y = 240-t;
    }


    if(_cobject) {

        _cobject->touchEvent(_cobject, action, x, y);

        if(action == TOUCH_ACTION_RELEASE) {
            _cobject->have_touch = 0;
            _cobject->have_move = 0;
            _cobject = 0;
        }

        if(action == TOUCH_ACTION_MOVE)
            _cobject->have_move = 1;

        have_tbIk++;
        return have_tbIk;
    }

    for(; item; item = item->next)
    {
        UIObject *obj = *glQueueListItemBody(item, UIObject**);


        if( x >= obj->x && x <= obj->x+obj->w &&
            y >= obj->y && y <= obj->y+obj->h) {

            if(obj->touchEvent) {

                if(action == TOUCH_ACTION_PRESS) {
                    obj->have_touch = 1;

                    if(!obj->no_mem_touch)
                        _cobject = obj;
                }

                if(action == TOUCH_ACTION_MOVE)
                    obj->have_move = 1;

                obj->touchEvent(obj, action, x, y);

                if(action == TOUCH_ACTION_RELEASE) {
                    obj->have_touch = 0;
                }

                have_tbIk++;
            }
        } else {
            if((obj->have_touch || obj->have_move) && obj->no_mem_touch) {
                if(obj->touchEvent)
                    obj->touchEvent(obj, TOUCH_ACTION_RELEASE, x, y);

                obj->have_move = 0;
                obj->have_touch = 0;
            }
        }
    }

    return have_tbIk;
}












