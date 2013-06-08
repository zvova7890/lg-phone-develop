

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
                    glDrawPixel16_32ca(context, x1+x, y1+y, color, c - alpha);
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


#if 0
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

    x1 -= fte_get_symbol(fti, smb)->left;

#ifdef __SYSTEM_FONT__
    TGlyphInfo glyph_info;
#define font_ctx font_h

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

#define font_ctx fti

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



    if(type & FT_TEXT_W_LEFT)
    {
        printf("FT_TEXT_W_LEFT\n");
        align += 0;
    }

    if(type & FT_TEXT_W_CENTER)
    {
        printf("FT_TEXT_W_CENTER\n");
        align += 1;
    }

    if(type & FT_TEXT_W_RIGHT)
    {
        printf("FT_TEXT_W_RIGHT\n");
        align += 2;
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


    printf("%s: align: %d\n", __FUNCTION__, align);

    switch(align)
    {
        case 0: // w left
            processing_draw();
        break;

        case 1: // w center
        {
            int s_maxw = ftStringMetrics(font_ctx, mem, 0, 0, max_leter_cnt, conv);

            x1 = x1 + ((mw/2) - (s_maxw/2));
            processing_draw();
            break;
        }

        case 2: // w right
        {
            int s_maxw = ftStringMetrics(font_ctx, mem, 0, 0, max_leter_cnt, conv);

            x1 += mw - s_maxw;
            processing_draw();
            break;
        }


        case 3: // w: left  h: center
        {
            uint32_t s_maxh;

            if(!(type & FT_TEXT_NOCALC_HCENTER))
                /*int s_maxw = */ftStringMetrics(font_ctx, mem, &s_maxh, 0, max_leter_cnt, conv);
            else
                s_maxh = font_h;

            y1 = y1 + ((mh/2) + (s_maxh/2));
            processing_draw();
            break;
        }

        case 4: // w: center  h: center
        {
            uint32_t s_maxh, top;
            int s_maxw = ftStringMetrics(font_ctx, mem, &s_maxh, &top, max_leter_cnt, conv);

            if(type & FT_TEXT_NOCALC_HCENTER)
                s_maxh = font_h;

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
            int s_maxw = ftStringMetrics(font_ctx, mem, &s_maxh, &top, max_leter_cnt, conv);

            if(type & FT_TEXT_NOCALC_HCENTER)
                s_maxh = font_h;

            s_maxh -= top - 1;
            y1 = y1 + ((mh/2) + (s_maxh/2));
            x1 += mw - s_maxw;
            processing_draw();
            break;
        }


        case 6: // w: left  h: down
        {
            uint32_t top;
            /*int s_maxw = */ftStringMetrics(font_ctx, mem, 0, &top, max_leter_cnt, conv);

            y1 += mh - top - 1;
            processing_draw();
            break;
        }


        case 7: // w: center  h: down
        {
            uint32_t top;
            int s_maxw = ftStringMetrics(font_ctx, mem, 0, &top, max_leter_cnt, conv);

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
            uint32_t top;
            int s_maxw = ftStringMetrics(font_ctx, mem, 0, &top, max_leter_cnt, conv);

            y1 += mh - top - 1;
            x1 += mw - s_maxw;
            processing_draw();
            break;
        }


        case 9: // w: left  h: up
        {
            uint32_t s_maxh;

            if(!(type & FT_TEXT_NOCALC_HCENTER))
                /*int s_maxw = */ftStringMetrics(font_ctx, mem, &s_maxh, 0, max_leter_cnt, conv);
            else
                s_maxh = font_h;

            y1 += s_maxh;
            processing_draw();
            break;
        }



        case 10: // w: center  h: up
        {
            uint32_t s_maxh;
            uint32_t s_maxw = ftStringMetrics(font_ctx, mem, &s_maxh, 0, max_leter_cnt, conv);

            if(type & FT_TEXT_NOCALC_HCENTER)
                s_maxh = font_h;

            y1 += s_maxh;
            x1 += x1 + ((mw-x1)/2) - (s_maxw/2);
            processing_draw();
            break;
        }



        case 11: // w: right  h: up
        {
            uint32_t s_maxh, s_maxh_t;
            int s_maxw = ftStringMetrics(font_ctx, mem, &s_maxh, &s_maxh_t, max_leter_cnt, conv);

            if(type & FT_TEXT_NOCALC_HCENTER)
                s_maxh = font_h;

            y1 += s_maxh - s_maxh_t;
            x1 += mw - s_maxw;
            processing_draw();
            break;
        }


    }
#undef processing_draw
    return x1;
}


#endif




int glDrawStringHelper(GLContext *ctx, fte_info *fti, const void *str, int x1, int y1, int x2, int y2, int step_width,
         int max_leter_cnt, int type, GLColor color, wchar_t (*conv)(const void **))
{
    wchar_t letter = conv((void *)&str);

    int _x1 = x1;
    int _y1 = y1;
    int max_h;
    int sentence_break = type & FT_TEXT_SENTENCEBREAK;
    // Fixup leftover position
    _x1 -= fte_get_symbol(fti, letter)->left;

    while(letter && max_leter_cnt > 0)
    {
        if(sentence_break && letter == L'\n') {
            _y1 += fti->h;
            _x1 = x1;
            letter = conv((void *)&str);
            _x1 -= fte_get_symbol(fti, letter)->left;
        }

        _x1 += glStringEngineDrawSymbol(ctx, fti, (uint16_t)letter, _x1, _y1, x2, y2, color) + step_width;
        if(_x1 >= ctx->clip_x2 || _x1 >= x2) break;
        fte_symbol *s = fte_get_symbol(fti, letter);
        if(s && max_h < s->height)
            max_h = s->height;

        letter = conv((void *)&str);
        --max_leter_cnt;
    }

    return _x1;
}


/*
 *FT_TEXT_W_LEFT       = (1 << 0),
    FT_TEXT_W_CENTER     = (1 << 1),
    FT_TEXT_W_RIGHT      = (1 << 2),

    FT_TEXT_H_UP         = (1 << 3),
    FT_TEXT_H_CENTER     = (1 << 4),
    FT_TEXT_H_DOWN       = (1 << 5),

    FT_TEXT_CENTER_BY_XSTART  = (1 << 6),
    FT_TEXT_CENTER_BY_YSTART  = (1 << 7),
    FT_TEXT_WORDBREAK      = (1 << 8),
    FT_TEXT_SENTENCEBREAK  = (1 << 9),
    FT_TEXT_NOCALC_HCENTER = (1 << 10)
*/


uint16_t glStringEngineDrawScrollString(GLContext *ctx, fte_info *fti, const void *str, int x1, int y1,
                            int x2, int y2, int type, uint8_t leter_step, int32_t max_leter_cnt, wchar_t (*conv)(const void **),
                            unsigned int color)
{
#define font_ctx fti

    ft_metrics metr = {0};
    int s_maxw = 0, s_maxh = 0;
    int max_width = x2-x1;
    int max_height = y2-y1;

#define metre() if(!metr.str) { \
        s_maxw = ftStringMetrics(font_ctx, str, &metr, max_leter_cnt, type, conv); \
        if( !(type & FT_TEXT_NOCALC_HCENTER) ) \
            s_maxh = metr.height; \
    }

    if( type & FT_TEXT_NOCALC_HCENTER )
        s_maxh = fti->h;


    if( type & FT_TEXT_W_CENTER ) {
        metre();

        if( !(type & FT_TEXT_CENTER_BY_XSTART) || s_maxw < max_width ) {
                x1 = x1 + ((max_width/2) - (s_maxw/2));
        }

    }
    else if( type & FT_TEXT_W_RIGHT ) {
        metre();
        x1 += max_width - s_maxw;
    }

    if( type & FT_TEXT_H_UP ) {
        metre();
        y1 += s_maxh;
    }
    else if( type & FT_TEXT_H_CENTER ) {
        metre();

        if(!(type & FT_TEXT_CENTER_BY_YSTART) || s_maxh < max_height) {
            y1 = y1 + ((max_height/2) + (s_maxh/2));
        }
    }
    else if( type & FT_TEXT_H_DOWN ) {
        metre();
        y1 += max_height - metr.top - 1;
    }

    return glDrawStringHelper(ctx, fti, str, x1, y1, x2, y2, leter_step, max_leter_cnt, type, color, conv);
}
