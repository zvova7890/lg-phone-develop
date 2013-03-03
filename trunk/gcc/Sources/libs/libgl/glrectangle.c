
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


typedef struct
{
    short x, y;
    short width, height;
    short angle1, angle2;
}XArc;


void glFillRoundRectange(GLContext *ctx, int x, int y, int w, int h, int ew, int eh)
{
    XArc arcs[8];
    int ew2, eh2;

    if ((ew2 = (ew << 1)) > w)
        ew2 = ew = 0;
    if ((eh2 = (eh << 1)) > h)
        eh2 = eh = 0;

    arcs[0].x = x;
    arcs[0].y = y;
    arcs[0].width = ew2;
    arcs[0].height = eh2;
    arcs[0].angle1 = 180;
    arcs[0].angle2 = 90;

    arcs[1].x = x + ew;
    arcs[1].y = y;
    arcs[1].width = w - ew2;
    arcs[1].height = 0;
    arcs[1].angle1 = 180;
    arcs[1].angle2 = 180;

    arcs[2].x = x + w - ew2;
    arcs[2].y = y;
    arcs[2].width = ew2;
    arcs[2].height = eh2;
    arcs[2].angle1 = 0;
    arcs[2].angle2 = 90;

    arcs[3].x = x + w;
    arcs[3].y = y + eh;
    arcs[3].width = 0;
    arcs[3].height = h - eh2;
    arcs[3].angle1 = 90;
    arcs[3].angle2 = 180;

    arcs[4].x = x + w - ew2;
    arcs[4].y = y + h - eh2;
    arcs[4].width = ew2;
    arcs[4].height = eh2;
    arcs[4].angle1 = 0;
    arcs[4].angle2 = 90;

    arcs[5].x = x + ew;
    arcs[5].y = y + h;
    arcs[5].width = w - ew2;
    arcs[5].height = 0;
    arcs[5].angle1 = 0;
    arcs[5].angle2 = 180;

    arcs[6].x = x;
    arcs[6].y = y + h - eh2;
    arcs[6].width = ew2;
    arcs[6].height = eh2;
    arcs[6].angle1 = 270;
    arcs[6].angle2 = 90;

    arcs[7].x = x;
    arcs[7].y = y + eh;
    arcs[7].width = 0;
    arcs[7].height = h - eh2;
    arcs[7].angle1 = 270;
    arcs[7].angle2 = 180;

    //XDrawArcs(dpy, draw, gc, arcs, 8);

    //
    for(int i=0; i<8; ++i) {
        glCtxDrawArc(ctx, arcs[i].x, arcs[i].y, arcs[i].width, arcs[i].height, arcs[i].angle1, arcs[i].angle2);
    }
}










