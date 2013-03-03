

#include <gl.h>



void glCtxDrawHLine(GLContext *ctx, int x1, int x2, int y)
{
    if(y < ctx->clip_y1 || y >= ctx->clip_y2)
        return;

    int sx = glMin(x1, x2);
    int ex = glMax(x1, x2);

    if(sx < ctx->clip_x1 && ex < ctx->clip_x1)
        return;

    if(sx < ctx->clip_x1)
        sx = ctx->clip_x1;

    if(ex > ctx->clip_x2)
        ex = ctx->clip_x2;


    switch(ctx->depth)
    {
        case 16:
            if(glTestAlphaBlend(ctx)) {
                for(; sx < ex; ++sx)
                    glDrawPixel16(ctx, sx, y);
            } else {
                for(; sx < ex; ++sx)
                    glPutPixel16(ctx, sx, y);
            }
            break;

        case 32:
            if(glTestAlphaBlend(ctx)) {
                for(; sx < ex; ++sx)
                    glDrawPixel32(ctx, sx, y);
            } else {
                for(; sx < ex; ++sx)
                    glPutPixel32(ctx, sx, y);
            }
            break;
    }
}



void glCtxDrawVLine(GLContext *ctx, int y1, int y2, int x)
{
    if(x < ctx->clip_x1 || x >= ctx->clip_x2)
        return;

    int sy = glMin(y1, y2);
    int ey = glMax(y1, y2);

    if(sy < ctx->clip_y1 && ey < ctx->clip_y1)
        return;

    if(sy < ctx->clip_y1)
        sy = ctx->clip_y1;

    if(ey > ctx->clip_y2)
        ey = ctx->clip_y2;

    switch(ctx->depth)
    {
        case 16:
            if(glTestAlphaBlend(ctx)) {
                for(; sy < ey; ++sy)
                    glDrawPixel16(ctx, x, sy);
            } else {
                for(; sy < ey; ++sy)
                    glPutPixel16(ctx, x, sy);
            }
            break;

        case 32:
            if(glTestAlphaBlend(ctx)) {
                for(; sy < ey; ++sy)
                    glDrawPixel32(ctx, x, sy);
            } else {
                for(; sy < ey; ++sy)
                    glPutPixel32(ctx, x, sy);
            }
            break;
    }
}

#include <math.h>
#include <stdlib.h>


void glCtxDrawLine(GLContext *ctx, int x1, int y1, int x2, int y2)
{
    if(y1 == y2) {
        glCtxDrawHLine(ctx, x1, x2, y1);
        return;
    }

    if(x1 == x2) {
        glCtxDrawVLine(ctx, y1, y2, x1);
        return;
    }

    int deltaX = glAbs(x2 - x1);
    int deltaY = glAbs(y2 - y1);
    int signX = x1 < x2 ? 1 : -1;
    int signY = y1 < y2 ? 1 : -1;
    int error = deltaX - deltaY;

    if(ctx->depth == 32)
        goto __ctx32;

    if(glTestAlphaBlend(ctx)) {
        for (;;)
        {
            if(x1 >= ctx->clip_x1 && y1 >= ctx->clip_y1 && x1 < ctx->clip_x2 && y1 < ctx->clip_y2) {
                glDrawPixel16(ctx, x1, y1);
            }

            if(x1 == x2 && y1 == y2)
                break;

            int error2 = error * 2;

            if(error2 > -deltaY)
            {
                error -= deltaY;
                x1 += signX;
            }

            if(error2 < deltaX)
            {
                error += deltaX;
                y1 += signY;
            }
        }
    } else {

        for (;;)
        {
            if(x1 >= ctx->clip_x1 && y1 >= ctx->clip_y1 && x1 < ctx->clip_x2 && y1 < ctx->clip_y2)
                glPutPixel16(ctx, x1, y1);

            if(x1 == x2 && y1 == y2)
                break;

            int error2 = error * 2;

            if(error2 > -deltaY)
            {
                error -= deltaY;
                x1 += signX;
            }

            if(error2 < deltaX)
            {
                error += deltaX;
                y1 += signY;
            }
        }
    }

    return;

__ctx32:

    if(glTestAlphaBlend(ctx)) {
        for (;;)
        {
            if(x1 >= ctx->clip_x1 && y1 >= ctx->clip_y1 && x1 < ctx->clip_x2 && y1 < ctx->clip_y2) {
                glDrawPixel32(ctx, x1, y1);
            }

            if(x1 == x2 && y1 == y2)
                break;

            int error2 = error * 2;

            if(error2 > -deltaY)
            {
                error -= deltaY;
                x1 += signX;
            }

            if(error2 < deltaX)
            {
                error += deltaX;
                y1 += signY;
            }
        }
    } else {
        for (;;)
        {
            if(x1 >= ctx->clip_x1 && y1 >= ctx->clip_y1 && x1 < ctx->clip_x2 && y1 < ctx->clip_y2) {
                glPutPixel32(ctx, x1, y1);
            }

            if(x1 == x2 && y1 == y2)
                break;

            int error2 = error * 2;

            if(error2 > -deltaY)
            {
                error -= deltaY;
                x1 += signX;
            }

            if(error2 < deltaX)
            {
                error += deltaX;
                y1 += signY;
            }
        }
    }
}



