
#include <stdio.h>
#include <gl.h>
#include "queuelist.h"



typedef struct
{
    unsigned short x1, y1,
                   x2, y2;
}ClipRegion;


void glCtxSetClipRegion(GLContext *ctx, int x1, int y1, int x2, int y2)
{
    if(x1 < 0)
        x1 = 0;

    if(y1 < 0)
        y1 = 0;

    if(x2 < 0)
        x2 = 0;

    if(y2 < 0)
        y2 = 0;

    if(x2 < x1 || x2 > (int)ctx->width)
        x2 = ctx->width;

    if(y2 < y1 || y2 > (int)ctx->height)
        y2 = ctx->height;

    ctx->clip_x1 = x1;
    ctx->clip_x2 = x2;
    ctx->clip_y1 = y1;
    ctx->clip_y2 = y2;
}


void glCtxResetClipRegion(GLContext *ctx)
{
    ctx->clip_x1 = ctx->clip_y1 = 0;
    ctx->clip_x2 = ctx->width;
    ctx->clip_y2 = ctx->height;
}



void glCtxSaveClipRegion(GLContext *ctx)
{
    GLQueueList *list = ctx->clip_queue;
    ClipRegion r;

    r.x1 = ctx->clip_x1;
    r.x2 = ctx->clip_x2;
    r.y1 = ctx->clip_y1;
    r.y2 = ctx->clip_y2;

    glQueueListPush(list, &r, sizeof(ClipRegion));
}


void glCtxRestoreClipRegion(GLContext *ctx)
{
    GLQueueList *list = ctx->clip_queue;

    if(list->last) {
        ClipRegion *r = glQueueListItemBody(list->last, ClipRegion *);

        ctx->clip_x1 = r->x1;
        ctx->clip_x2 = r->x2;
        ctx->clip_y1 = r->y1;
        ctx->clip_y2 = r->y2;

        glQueueListPop(list, list->last);
    }
}



