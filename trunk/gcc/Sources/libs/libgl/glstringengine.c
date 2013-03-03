

#include <gl.h>
#include <wchar.h>
#include "freetype_engine.h"

#ifdef __SYSTEM_FONT__
#include <Api/ApiLinkLib/ApiLink.h>
#endif


/* Оптимизированно для работы с контекстом gl */

#undef printf
#define printf(...)


#ifdef __SYSTEM_FONT__
uint16_t glStringEngineDrawSymbol(GLContext *context, int font_h, uint16_t letter, int x1, int y1, int x2, int y2, unsigned int color)
#else
uint16_t glStringEngineDrawSymbol(GLContext *context, fte_info *fti, uint16_t letter, int x1, int y1, int x2, int y2, unsigned int color)
#endif
{
#ifdef __SYSTEM_FONT__
    fte_symbol _fte_s, *fte_s = &_fte_s;

    TGlyphInfo glyph_info;
    GrFont_GetGlyphInfo(font_h, letter, &glyph_info);

    fte_s->width = glyph_info.Width;
    fte_s->height = glyph_info.Height;
    fte_s->top = glyph_info.Top;
    fte_s->left = glyph_info.Left;
    fte_s->xadvance = glyph_info.xAdvance;
    fte_s->yadvance = glyph_info.yAdvance;
    fte_s->bitmap = glyph_info.pBuffer;

#else
    fte_symbol *fte_s = fte_get_symbol(fti, letter);
#endif


    if(!fte_s)
        return -1;

    if(!fte_s->bitmap)
        return fte_s->xadvance;

    //unsigned char *alpha_ptr = &(((unsigned char *)&color)[3]);
    uint8_t alpha = (uint8_t)255 - glColorAlpha(color);

    y1 = y1 - fte_s->top;
    x1 += fte_s->left;

#if 1
    int x, y, adv = fte_s->xadvance;
    int max_w = fte_s->width, max_h = fte_s->height;
    int _x_offset = 0, _y_offset = 0;

// ===
    if(x1 < context->clip_x1)
        _x_offset = context->clip_x1 - x1;

    if(y1 < context->clip_y1)
        _y_offset = context->clip_y1 - y1;
// ===

    if(x1+max_w >= context->clip_x2)
        max_w -= (x1+max_w) - context->clip_x2;

    if(y1+max_h > context->clip_y2)
        max_h -= (y1+max_h) - context->clip_y2;

// ===

    if(x1+max_w > x2)
        max_w -= (x1+max_w) - x2;

    if(y1+max_h > y2)
        max_h -= (y1+max_h) - y2;

// ===

    //int ptr = 0;

    #define for_each for(y = _y_offset; y < max_h; ++y) \
                        for(x = _x_offset; x < max_w; ++x) { \
                            uint8_t c = fte_s->bitmap[((y)*fte_s->width+(x))]; \
                            if(alpha >= c) \
                                continue; \
                                                    \
                            //color =  ((c - alpha) << 24) | (color & 0xFFFFFF);

                            //(((unsigned char *)&color)[3]) = alpha < c? c - alpha : 0; // alpha chanel


    switch(context->depth)
    {
        case 16:

            if(context->attr & GL_ALPHA_TEST) {
                for_each /*{*/
                    glDrawPixel16ca(context, x1+x, y1+y, color, c - alpha);
                }

            } else {
                for_each /*{*/
                    glPutPixel16c(context, x1+x, y1+y, c - alpha);
                }
            }

            break;


        case 32:

            if(context->attr & GL_ALPHA_TEST) {
                for_each /*{*/
                    glDrawPixel32ca(context, x1+x, y1+y, color, c - alpha);
                }

            } else {
                for_each /*{*/
                    glPutPixel32c(context, x1+x, y1+y, c - alpha);
                }
            }

            break;
    }
#else

    int x, y, adv = fte_s->xadvance;
    int max_w = fte_s->width, max_h = fte_s->height;

    /*if(x1+max_w > x2)
        max_w = (x1+max_w) - x2;

    if(y1+max_h > y2)
        max_h = (y1+max_h) - y2;*/
    //int ptr = 0;

    for(y = 0; y < max_h; ++y)
    {
        for(x = 0; x < max_w; ++x)
        {
            uint8_t c = fte_s->bitmap[((y)*fte_s->width+(x))];
            if(!c)
                continue;

            (((unsigned char *)&color)[3]) = alpha < c? c - alpha : 0; // alpha chanel

            context->setColorPixel(context, x1+x, y1+y, color);
        }
    }
#endif

    return adv;
}


#ifdef __SYSTEM_FONT__
uint32_t ftStringMetrics(int font_h, const void *str, uint32_t *height, uint32_t *y_seek, int32_t max_leter_cnt, wchar_t (*conv)(const void **))
{
    uint32_t w = 0, h = 0;
    int t = 0;
    TGlyphInfo glyph_info;
    wchar_t smb = conv(&str);
    //w -= fte_get_symbol(ftf->fti, smb)->left;

    while(smb && max_leter_cnt > 0)
    {
        GrFont_GetGlyphInfo(font_h, smb, &glyph_info);
        w += glyph_info.xAdvance;

        if(t < glyph_info.Height - glyph_info.Top)
        {
            t = glyph_info.Height - glyph_info.Top;
        }

        if((int)h < glyph_info.Height)
            h = glyph_info.Height;
        smb = conv(&str);
        --max_leter_cnt;
    }


    if(height) *height = h;
    if(y_seek) *y_seek = t;
    return w;
}
#endif


#ifndef __SYSTEM_FONT__
uint16_t glStringEngineDrawScrollString(GLContext *ctx, fte_info *fti, const void *str, int x1, int y1,
                            int x2, int y2, int type, uint8_t leter_step, int32_t max_leter_cnt, wchar_t (*conv)(const void **),
                            unsigned int color)
#else
uint16_t glStringEngineDrawScrollString(GLContext *ctx, int font_h, const void *str, int x1, int y1,
                            int x2, int y2, int type, uint8_t leter_step, int32_t max_leter_cnt, wchar_t (*conv)(const void **),
                            unsigned int color)
#endif
{

    uint16_t h;
    char align;
    const void *mem;
    uint16_t smb;
    int mw;
    int mh;
#ifndef __SYSTEM_FONT__
    int font_h = fti->h;
#endif
    int mx1 = x1;
    int my1 = y1;


draw_again:
    h = 0;
    align = 0;
    mem = str;
    smb = conv((void *)&str);

    mw = x2-mx1;
    mh = y2-my1;


#ifdef __SYSTEM_FONT__
    TGlyphInfo glyph_info;


#define processing_draw() while(smb && max_leter_cnt > 0)\
            {\
                x1 += glStringEngineDrawSymbol(ctx, font_h, (uint16_t)smb, x1, y1, x2, y2, color) + leter_step;\
                if(x1 >= ctx->clip_x2 || x1 >= x2) break;\
                GrFont_GetGlyphInfo(font_h, smb, &glyph_info); \
                if(h < glyph_info.Height)\
                    h = glyph_info.Height;\
                smb = conv((void *)&str);\
                --max_leter_cnt;\
            }
#else

#define processing_draw() while(smb && max_leter_cnt > 0)\
            {\
                if(smb == L'\n' && type & FT_TEXT_SENTENCEBREAK) {     \
                    y1 = my1+(y1-my1)+4;                                    \
                    x1 = mx1;                                          \
                    goto draw_again;                                   \
                }                                                      \
                x1 += glStringEngineDrawSymbol(ctx, fti, (uint16_t)smb, x1, y1, x2, y2, color) + leter_step;\
                if(x1 >= ctx->clip_x2 || x1 >= x2) break;\
                fte_symbol *s = fte_get_symbol(fti, smb);\
                if(s && h < s->height)\
                    h = s->height;\
                smb = conv((void *)&str);\
                --max_leter_cnt;\
            }
#endif

    char fix_left = 0;

    if(type & FT_TEXT_W_LEFT)
    {
        printf("FT_TEXT_W_LEFT\n");
        align += 0;
        fix_left = 1;
    }

    if(type & FT_TEXT_W_CENTER)
    {
        printf("FT_TEXT_W_CENTER\n");
        align += 1;
        fix_left = 0;
    }

    if(type & FT_TEXT_W_RIGHT)
    {
        printf("FT_TEXT_W_RIGHT\n");
        align += 2;
        fix_left = 0;
    }


    if(type & FT_TEXT_H_UP)
    {
        printf("FT_TEXT_H_UP\n");
        align += 9;
    }

    if(type & FT_TEXT_H_CENTER)
    {
        printf("FT_TEXT_H_CENTER\n");
        align += 3;
    }

    if(type & FT_TEXT_H_DOWN)
    {
        printf("FT_TEXT_H_DOWN\n");
        align += 6;
    }

    if(fix_left)
        x1 -= fte_get_symbol(fti, smb)->left;

    printf("%s: align: %d\n", __FUNCTION__, align);

    switch(align)
    {
        case 0: // w left
            processing_draw();
        break;

        case 1: // w center
        {
#ifdef __SYSTEM_FONT__
            int s_maxw = ftStringMetrics(font_h, mem, 0, 0, max_leter_cnt, conv);
#else
            int s_maxw = ftStringMetrics(fti, mem, 0, 0, max_leter_cnt, conv);
#endif


            if(!(type & FT_TEXT_CENTER_BY_XSTART) || s_maxw < mw) {
                x1 = x1 + ((mw/2) - (s_maxw/2));
            }

            processing_draw();
            break;
        }

        case 2: // w right
        {
#ifdef __SYSTEM_FONT__
            int s_maxw = ftStringMetrics(font_h, mem, 0, 0, max_leter_cnt, conv);
#else
            int s_maxw = ftStringMetrics(fti, mem, 0, 0, max_leter_cnt, conv);
#endif
            x1 += mw - s_maxw;
            processing_draw();
            break;
        }


        case 3: // w: left  h: center
        {
            uint32_t s_maxh;
#ifdef __SYSTEM_FONT__
            /*int s_maxw = */ftStringMetrics(font_h, mem, &s_maxh, 0, max_leter_cnt, conv);
#else
            /*int s_maxw = */ftStringMetrics(fti, mem, &s_maxh, 0, max_leter_cnt, conv);
#endif

            y1 = y1 + ((mh/2) + (s_maxh/2));
            processing_draw();
            break;
        }

        case 4: // w: center  h: center
        {
            uint32_t s_maxh, top;
#ifdef __SYSTEM_FONT__
            int s_maxw = ftStringMetrics(font_h, mem, &s_maxh, &top, max_leter_cnt, conv);
#else
            int s_maxw = ftStringMetrics(fti, mem, &s_maxh, &top, max_leter_cnt, conv);
#endif

            s_maxh -= top - 1;
            y1 = y1 + ((mh/2) + (s_maxh/2));

            if(!(type & FT_TEXT_CENTER_BY_XSTART) || s_maxw < mw) {
                x1 = x1 + ((mw/2) - (s_maxw/2));
            }
            processing_draw();
            break;
        }


        case 5: // w: right  h: center
        {
            uint32_t s_maxh, top;
#ifdef __SYSTEM_FONT__
            int s_maxw = ftStringMetrics(font_h, mem, &s_maxh, &top, max_leter_cnt, conv);
#else
            int s_maxw = ftStringMetrics(fti, mem, &s_maxh, &top, max_leter_cnt, conv);
#endif

            s_maxh -= top - 1;
            y1 = y1 + ((mh/2) + (s_maxh/2));
            x1 += mw - s_maxw;
            processing_draw();
            break;
        }


        case 6: // w: left  h: down
        {
            uint32_t s_maxh, top;
#ifdef __SYSTEM_FONT__
            /*int s_maxw = */ftStringMetrics(font_h, mem, &s_maxh, &top, max_leter_cnt, conv);
#else
            /*int s_maxw = */ftStringMetrics(fti, mem, &s_maxh, &top, max_leter_cnt, conv);
#endif

            y1 += mh - top - 1;
            processing_draw();
            break;
        }


        case 7: // w: center  h: down
        {
            uint32_t s_maxh, top;
#ifdef __SYSTEM_FONT__
            int s_maxw = ftStringMetrics(font_h, mem, &s_maxh, &top, max_leter_cnt, conv);
#else
            int s_maxw = ftStringMetrics(fti, mem, &s_maxh, &top, max_leter_cnt, conv);
#endif

            y1 += mh - top - 1;

            if(type & FT_TEXT_CENTER_BY_XSTART && s_maxw >= mw) {

            } else {
                x1 += ((mw/2) - (s_maxw/2));
            }

            processing_draw();
            break;
        }


        case 8: // w: right  h: down
        {
            uint32_t s_maxh, top;
#ifdef __SYSTEM_FONT__
            int s_maxw = ftStringMetrics(font_h, mem, &s_maxh, &top, max_leter_cnt, conv);
#else
            int s_maxw = ftStringMetrics(fti, mem, &s_maxh, &top, max_leter_cnt, conv);
#endif

            y1 += mh - top - 1;
            x1 += mw - s_maxw;
            processing_draw();
            break;
        }


        case 9: // w: left  h: up
        {
            uint32_t s_maxh, s_maxh_t;
#ifdef __SYSTEM_FONT__
            /*int s_maxw = */ftStringMetrics(font_h, mem, &s_maxh, &s_maxh_t, max_leter_cnt, conv);
#else
            /*int s_maxw = */ftStringMetrics(fti, mem, &s_maxh, &s_maxh_t, max_leter_cnt, conv);
#endif

            y1 += s_maxh;
            processing_draw();
            break;
        }



        case 10: // w: center  h: up
        {
            uint32_t s_maxh;
#ifdef __SYSTEM_FONT__
            uint32_t s_maxw = ftStringMetrics(font_h, mem, &s_maxh, 0, max_leter_cnt, conv);
#else
            uint32_t s_maxw = ftStringMetrics(fti, mem, &s_maxh, 0, max_leter_cnt, conv);
#endif

            y1 += s_maxh;
            x1 += x1 + ((mw-x1)/2) - (s_maxw/2);
            processing_draw();
            break;
        }



        case 11: // w: right  h: up
        {
            uint32_t s_maxh, s_maxh_t;
#ifdef __SYSTEM_FONT__
            int s_maxw = ftStringMetrics(font_h, mem, &s_maxh, &s_maxh_t, max_leter_cnt, conv);
#else
            int s_maxw = ftStringMetrics(fti, mem, &s_maxh, &s_maxh_t, max_leter_cnt, conv);
#endif

            y1 += s_maxh - s_maxh_t;
            x1 += mw - s_maxw;
            processing_draw();
            break;
        }


    }
#undef processing_draw
    return h;
}


