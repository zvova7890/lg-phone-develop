
#include <string.h>
#include <gl.h>


void glCtxFillRegion(GLContext *ctx, int x1, int y1, int x2, int y2, GLColor color);





void glCtxClear(GLContext *ctx, GLColor color)
{
    glCtxFillRegion(ctx, ctx->clip_x1, ctx->clip_y1, ctx->clip_x2, ctx->clip_y2, color);
}



void glCtxEnable(GLContext *ctx, int mode)
{
    if(ctx->attr & mode)
        return;

    ctx->attr |= mode;

    ctx->setPixel = glGetPixelProc(ctx);
    ctx->setColorPixel = glGetCPixelProc(ctx);
}



void glCtxDisable(GLContext *ctx, int mode)
{
    if(ctx->attr & mode)
        ctx->attr &= ~mode;
    else
        return;

    ctx->setPixel = glGetPixelProc(ctx);
    ctx->setColorPixel = glGetCPixelProc(ctx);
}



/***************************************************************************************/
/******************************** glGetPixelProc  **************************************/
/***************************************************************************************/

static void _put_pixel16(GLContext *ctx, int x, int y) {
    if(x >= ctx->clip_x1 && x < ctx->clip_x2 &&  y >= ctx->clip_y1 && y < ctx->clip_y2)
        glPutPixel16(ctx, x, y);
}

static void _put_pixel16blend(GLContext *ctx, int x, int y) {
    if(x >= ctx->clip_x1 && x < ctx->clip_x2 &&  y >= ctx->clip_y1 && y < ctx->clip_y2)
        glDrawPixel16(ctx, x, y);
}

static void _put_pixel32(GLContext *ctx, int x, int y) {
    if(x >= ctx->clip_x1 && x < ctx->clip_x2 &&  y >= ctx->clip_y1 && y < ctx->clip_y2)
        glPutPixel32(ctx, x, y);
}

static void _put_pixel32blend(GLContext *ctx, int x, int y) {
    if(x >= ctx->clip_x1 && x < ctx->clip_x2 &&  y >= ctx->clip_y1 && y < ctx->clip_y2)
        glDrawPixel32(ctx, x, y);
}


glPixelSetProc glGetPixelProc(GLContext *ctx)
{
    glPixelSetProc pixel = 0;
    switch(ctx->depth)
    {
        case 16:
            if(!glTestAlphaBlend(ctx)) {
                pixel = (glPixelSetProc)_put_pixel16;
            } else {
                pixel = (glPixelSetProc)_put_pixel16blend;
            }
            break;

        case 32:
            if(!glTestAlphaBlend(ctx)) {
                pixel = (glPixelSetProc)_put_pixel32;
            } else {
                pixel = (glPixelSetProc)_put_pixel32blend;
            }
            break;
    }

    return pixel;
}



/***************************************************************************************/
/******************************* glGetCPixelProc  **************************************/
/***************************************************************************************/

void _xput_pixel16(GLContext *ctx, int x, int y, GLColor c) {
    if(x >= ctx->clip_x1 && x < ctx->clip_x2 &&  y >= ctx->clip_y1 && y < ctx->clip_y2)
        glPutPixel16c(ctx, x, y, c);
}

void _xput_pixel16blend(GLContext *ctx, int x, int y, GLColor c) {
    if(x >= ctx->clip_x1 && x < ctx->clip_x2 &&  y >= ctx->clip_y1 && y < ctx->clip_y2)
        glDrawPixel16c(ctx, x, y, c);
}

void _xput_pixel32(GLContext *ctx, int x, int y, GLColor c) {
    if(x >= ctx->clip_x1 && x < ctx->clip_x2 &&  y >= ctx->clip_y1 && y < ctx->clip_y2)
        glPutPixel32c(ctx, x, y, c);
}


void _xput_pixel32blend(GLContext *ctx, int x, int y, GLColor c) {
    if(x >= ctx->clip_x1 && x < ctx->clip_x2 &&  y >= ctx->clip_y1 && y < ctx->clip_y2)
        glDrawPixel32c(ctx, x, y, c);
}


glCPixelSetProc glGetCPixelProc(GLContext *ctx)
{
    glCPixelSetProc pixel = 0;
    switch(ctx->depth)
    {
        case 16:
            if(!glTestAlphaBlend(ctx)) {
                pixel = (glCPixelSetProc)_xput_pixel16;
            } else {
                pixel = (glCPixelSetProc)_xput_pixel16blend;
            }
            break;

        case 32:
            if(!glTestAlphaBlend(ctx)) {
                pixel = (glCPixelSetProc)_xput_pixel32;
            } else {
                pixel = (glCPixelSetProc)_xput_pixel32blend;
            }
            break;
    }

    return pixel;
}


