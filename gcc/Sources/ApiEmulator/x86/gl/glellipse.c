
#include <gl.h>



void glCtxDrawFilledEllipse(GLContext *ctx, int mx, int my, int w, int h)
{
    glPixelSetProc setPixel = ctx->setPixel;

    int x=0,mx1=0,mx2=0,my1=0,my2=0;
    long aq,bq,dx,dy,r,rx,ry,a,b;
    int i;
    int old_y2;

    a=w>>1;
    b=h>>1;

    glCtxDrawLine(ctx, mx-a, my, mx+a, my);

    mx1 = mx-a;my1 = my;
    mx2 = mx+a;my2 = my;

    aq = a * a;
    bq = b * b;
    dx = aq << 1;
    dy = bq << 1;
    r  = a * bq;
    rx = r << 1;
    ry = 0;
    x = a;
    old_y2=-2;
    //old_y1=-2;

    while (x > 0){
        if (r > 0) {
            my1++;my2--;
            ry +=dx;
            r  -=ry;
        }
        if (r <= 0){
            x--;
            mx1++;mx2--;
            rx -=dy;
            r  +=rx;
        }
        if(old_y2!=my2){
            for(i=mx1;i<=mx2;i++){
                setPixel(ctx, i, my1);
            }
        }
        if(old_y2!=my2){
            for(i=mx1;i<=mx2;i++){
                setPixel(ctx, i, my2);
            }
        }
        old_y2 = my2;
        //old_y1 = my1;
    }
}



void glCtxDrawEllipse(GLContext *ctx, int mx, int my, int w, int h)
{
    glPixelSetProc setPixel = ctx->setPixel;
    int x=0,mx1=0,mx2=0,my1=0,my2=0;
    long aq,bq,dx,dy,r,rx,ry,a,b;

    a=w>>1;
    b=h>>1;
    setPixel(ctx, mx+a, my);
    setPixel(ctx, mx-a, my);
    mx1 = mx-a;my1 = my;
    mx2 = mx+a;my2 = my;

    aq = a * a;
    bq = b * b;
    dx = aq << 1;
    dy = bq << 1;
    r  = a * bq;
    rx = r << 1;
    ry = 0;
    x = a;
    while (x > 0){
            if (r > 0) {
                    my1++;my2--;
                    ry +=dx;
                    r  -=ry;
            }
            if (r <= 0){
                    x--;
                    mx1++;mx2--;
                    rx -=dy;
                    r  +=rx;
            }
            setPixel(ctx,mx1, my1);
            setPixel(ctx,mx1, my2);
            setPixel(ctx,mx2, my1);
            setPixel(ctx,mx2, my2);
    }
}
