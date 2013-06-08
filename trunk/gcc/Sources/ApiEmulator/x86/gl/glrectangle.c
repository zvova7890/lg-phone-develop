
#include <gl.h>
void glCtxFillRegion(GLContext *ctx, int x1, int y1, int x2, int y2, GLColor color);





void glCtxDrawRectange(GLContext *ctx, int x1, int y1, int x2, int y2)
{
    glCtxDrawVLine(ctx, y1, y2, x1);
    glCtxDrawVLine(ctx, y1, y2, x2);

    glCtxDrawHLine(ctx, x1, x2, y1);
    glCtxDrawHLine(ctx, x1, x2, y2);
}



void glCtxDrawFilledRectange(GLContext *ctx, int x1, int y1, int x2, int y2)
{
    int x, y;
    int my = glMax(y1, y2);
    int mx = glMax(x1, x2);

    int ny = glMin(y1, y2);
    int nx = glMin(x1, x2);

    if(mx < ctx->clip_x1 || my < ctx->clip_y1)
        return;

    if(nx < ctx->clip_x1)
        nx = ctx->clip_x1;

    if(ny < ctx->clip_y1)
        ny = ctx->clip_y1;

    if(mx > ctx->clip_x2)
        mx = ctx->clip_x2;

    if(my > ctx->clip_y2)
        my = ctx->clip_y2;


    switch(ctx->depth)
    {
        case 16:
            if(glTestAlphaBlend(ctx)) {
                for(y = ny; y < my; ++y) {
                    for(x = nx; x < mx; ++x)
                        glDrawPixel16(ctx, x, y);
                }

            } else {
                glCtxFillRegion(ctx, nx, ny, mx, my, ctx->pen);
                /*for(y = ny; y < my; ++y) {
                    for(x = nx; x < mx; ++x)
                        glPutPixel16(ctx, x, y);
                }*/
            }
            break;

        case 32:
            if(glTestAlphaBlend(ctx)) {
                for(y = ny; y < my; ++y)
                    for(x = nx; x < mx; ++x)
                        glDrawPixel32(ctx, x, y);
            } else {
                for(y = ny; y < my; ++y)
                    for(x = nx; x < mx; ++x)
                        glPutPixel32(ctx, x, y);
            }

            break;
    }
}



