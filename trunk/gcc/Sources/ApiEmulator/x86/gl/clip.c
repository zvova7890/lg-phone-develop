
#include <stdio.h>
#include <gl.h>
#include "queuelist.h"



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



void glCtxSaveClipRegionTo(GLContext *ctx, GLRect *rect)
{
    rect->x1 = ctx->clip_x1;
    rect->x2 = ctx->clip_x2;
    rect->y1 = ctx->clip_y1;
    rect->y2 = ctx->clip_y2;
}


void glCtxRestoreClipRegionFrom(GLContext *ctx, GLRect *rect)
{
    ctx->clip_x1 = rect->x1;
    ctx->clip_x2 = rect->x2;
    ctx->clip_y1 = rect->y1;
    ctx->clip_y2 = rect->y2;
}


void glCtxSaveClipRegion(GLContext *ctx)
{
    GLRect r;
    GLQueueList *list = ctx->clip_queue;
    
    glCtxSaveClipRegionTo(ctx, &r);
    glQueueListPush(list, &r, sizeof(GLRect));
}


void glCtxRestoreClipRegion(GLContext *ctx)
{
    GLQueueList *list = ctx->clip_queue;

    if(list->last) {
        GLRect *r = glQueueListItemBody(list->last, GLRect *);

        glCtxRestoreClipRegionFrom(ctx, r);
        glQueueListPop(list, list->last);
    }
}



