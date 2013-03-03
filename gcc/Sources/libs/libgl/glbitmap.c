
#include <gl.h>
#include <stdio.h>





void glCtxDrawOptionalBitmap(GLContext *ctx, int x, int y,
                  int bit_offset_x, int bit_offset_y, int x2, int y2, unsigned char alpha, int w, int h, int depth, void *bitmap)
{
    unsigned short *bp16 = (unsigned short *)bitmap;
    unsigned int *bp32 = (unsigned int *)bitmap;
    unsigned char _alpha = 0xff-alpha;
    int _x, _y, rcx = x;

    int offset_x = bit_offset_x;
    int offset_y = bit_offset_y;

    int max_h = y2-y;
    int max_w = x2-x;

    int cx = x;
    int cy = y;

    /* Если картинка начинает рисоватся вне экрана */
    if(cx < ctx->clip_x1) {

        /* и если оффсет меньше чем нужно */
        if(offset_x < ctx->clip_x1-cx)
            offset_x = (ctx->clip_x1-cx);

        rcx = cx = ctx->clip_x1;
    }

    if(cy < ctx->clip_y1) {

        if(offset_y < ctx->clip_y1-cy)
            offset_y = (ctx->clip_y1-cy);

        cy = ctx->clip_y1;
    }

    /* оффсеты больше размера картинки - картинка за пределами экрана */
    if(offset_x > w || offset_y > h)
        return;

    /* максимальный размер больше картинки */
    if(max_w > w)
        max_w = w;

    if(max_h > h)
        max_h = h;

    /* выходим за пределы экрана(картинка больше)*/
    if(cx+max_w > ctx->clip_x2)
        max_w = ctx->clip_x2-cx;

    if(cy+max_h > ctx->clip_y2)
        max_h = ctx->clip_y2-cy;

    //int can_store_two_pixels = (max_w-offset_x)/2;
    int max_w_align = __ALIGN_MASK(max_w, 1);
    while(max_w_align > max_w)
        max_w_align -= 2;


#define for_each for(_y = offset_y; _y < max_h; ++_y, ++cy) \
                    for(_x = offset_x, cx = rcx; _x < max_w; ++_x, ++cx)

    switch(ctx->depth)
    {
        case 16:
            switch(depth)
            {
                case 16:  // 16->16 no alpha blend
                    if(alpha == 0)
                        for_each glPutPixel16c(ctx, cx, cy, *(bp16 + (_y*w+_x)));
                    else {
                        for_each {
                            glDrawPixel16_16c(ctx, cx, cy, *(bp16 + (_y*w+_x)), _alpha);
                        }
                    }
                    break;

                case 32: // 32 -> 16 alpha blend
                    if(ctx->attr & GL_ALPHA_TEST) {
                        if(alpha != 0) {
                            for_each {
                                GLColor c = *(bp32 + (_y*w+_x));
                                glDrawPixel16ca(ctx, cx, cy, c, _alpha);
                            }
                        } else {
                            for_each {
                                GLColor c = *(bp32 + (_y*w+_x));
                                unsigned char a = glColorAlpha(c);

                                //if(cx >= ctx->clip_x1 && cy >= ctx->clip_y1 && cx < ctx->clip_x2 && cy < ctx->clip_y2)
                                //{
                                    if(a != 0) {
                                        if(a != 255) {
                                            glDrawPixel16ca(ctx, cx, cy, c, a);
                                        } else {
                                            glPutPixel16c(ctx, cx, cy, rgb32ToRgb16(c));
                                        }
                                    }
                                //}
                            }

                        }
                    } else
                        for_each glPutPixel16c(ctx, cx, cy, rgb32ToRgb16(*(bp32 + (_y*w+_x))));
                    break;
            }
            break;

        case 32:
            switch(depth)
            {
                case 16:
                    if(alpha == 0)
                        for_each glPutPixel32c(ctx, cx, cy, rgb16ToRgb32(*(bp16 + (_y*w+_x))));
                    else
                        for_each glDrawPixel32_16c(ctx, cx, cy, *(bp16 + (_y*w+_x)), _alpha);
                    break;

                case 32:
                    if(ctx->attr & GL_ALPHA_TEST)

                    if(alpha != 0) {
                        for_each {

                            GLColor c = *(bp32 + (_y*w+_x));
                            glDrawPixel32ca(ctx, cx, cy, c, _alpha);
                        }

                    } else {
                        for_each {
                            GLColor c = *(bp32 + (_y*w+_x));
                            unsigned char a = glColorAlpha(c)+alpha;

                            if(a != 0) {
                                if(a != 255)
                                    glDrawPixel32ca(ctx, cx, cy, c, a);
                                else
                                    glPutPixel32c(ctx, cx, cy, c);
                            }
                        }
                    }

                    else
                        for_each glPutPixel32c(ctx, cx, cy, *(bp32 + (_y*w+_x)));
                    break;
            }
            break;
    }
}



void glCtxDrawBitmap(GLContext *ctx, int x, int y, int w, int h, int depth, void *bitmap)
{
    glCtxDrawOptionalBitmap(ctx, x, y, 0, 0, x+w, y+h, 0, w, h, depth, bitmap);
}


void glCtxDrawAlphaBitmap(GLContext *ctx, int x, int y, unsigned char alpha, int w, int h, int depth, void *bitmap)
{
    glCtxDrawOptionalBitmap(ctx, x, y, 0, 0, x+w, y+h, alpha, w, h, depth, bitmap);
}


