


#include <gl.h>
#include <stdlib.h>
#include <stdio.h>
#include "queuelist.h"



GLContext *glCreateContext(unsigned short width, unsigned short height, unsigned short depth, void *framebuffer)
{
    GLContext *ctx = calloc(1, sizeof *ctx);

    ctx->clip_x1 = ctx->clip_y1 = 0;
    ctx->clip_x2 = ctx->width = width;
    ctx->clip_y2 = ctx->height = height;
    ctx->depth = depth;
    ctx->attr = 0;
    ctx->setPixel = glGetPixelProc(ctx);
    ctx->setColorPixel = glGetCPixelProc(ctx);
    ctx->polyInts = 0;
    ctx->polyIntsCnt = 0;
    ctx->clip_queue = malloc(sizeof(GLQueueList));
    glQueueListCreate(ctx->clip_queue);

    glSetContextProp(ctx, width, height, depth, framebuffer);
    return ctx;
}


void glDestroyContext(GLContext *ctx)
{
    if(ctx->polyIntsCnt > 0)
        free(ctx->polyInts);

#ifdef X2MassBitmap
    free(ctx->framebuffer);
#endif

    GLQueueList *list = ctx->clip_queue;
    GLQueueListItem *item = list->first;

    for(; item; )
    {
        GLQueueListItem *next = item->next;

        free(item);

        item = next;
    }
    list->first = list->last = 0;

    free(ctx->clip_queue);
    free(ctx);
}



void glCtxSetRenderRegion(GLContext *ctx, int x, int y, int width, int height)
{
#ifdef X2MassBitmap
    int i;
    void *framebuffer = ctx->bitmap;
    switch(ctx->depth)
    {
        case 16: {
            unsigned short **bitmap = (unsigned short**)ctx->framebuffer;
            unsigned short *fb = (unsigned short *)framebuffer;

            fb += width*y;
            for(i =0; i<height; ++i) {
                bitmap[i] = (fb + x);
                fb += width;
            }
            break;
        }

        case 32: {
            unsigned int **bitmap = (unsigned int**)ctx->framebuffer;
            unsigned int *fb = (unsigned int *)framebuffer;

            fb += (width*y);
            for(i =0; i<height; ++i) {
                bitmap[i] = (fb + x);
                fb += width;
            }
            break;
        }
    }

    ctx->clip_x2 = width;
    ctx->clip_y2 = height;
#else
#warning glSetRenderRegion not support
#endif
}


void glCtxResetRenderRegion(GLContext *ctx)
{
    glCtxSetRenderRegion(ctx, 0, 0, ctx->width, ctx->height);
}


void glSetContextProp(GLContext *ctx, int width, int height, int depth, void *framebuffer)
{
#ifndef X2MassBitmap
    ctx->depth = depth;
    ctx->framebuffer = framebuffer;
#else

    ctx->depth = depth;
    ctx->bitmap = framebuffer;
    ctx->framebuffer = realloc(ctx->framebuffer, height * sizeof(void*));
    int i;
    switch(depth)
    {
        case 16: {
            unsigned short **bitmap = (unsigned short**)ctx->framebuffer;
            unsigned short *fb = (unsigned short *)framebuffer;

            for(i =0; i<height; ++i) {
                bitmap[i] = fb;
                fb += width;
            }
            break;
        }

        case 32: {
            unsigned int **bitmap = (unsigned int**)ctx->framebuffer;
            unsigned int *fb = (unsigned int *)framebuffer;

            for(i =0; i<height; ++i) {
                bitmap[i] = fb;
                fb += width;
            }
            break;
        }
    }

    ctx->clip_x2 = ctx->width = width;
    ctx->clip_y2 = ctx->height = height;
#endif
}

