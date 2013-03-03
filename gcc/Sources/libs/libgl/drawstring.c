
#include <gl.h>
#include <wchar.h>
#include "freetype_engine.h"



#ifndef __SYSTEM_FONT__

#undef printf
#define printf(...)


uint16_t ftDrawSymbol(void *context, fte_info *fti, uint16_t leter, int x1, int y1, int x2, int y2, unsigned int color,
                      void (*setPixel)(void *context, int x, int y, unsigned int color))
{
    fte_symbol *fte_s = fte_get_symbol(fti, leter);

    if(!fte_s)
        return 0;

    if(!fte_s->bitmap)
        return fte_s->xadvance;

    //unsigned char *alpha_ptr = &(((unsigned char *)&color)[3]);
    uint8_t alpha = (uint8_t)255 - glColorAlpha(color);

    y1 = y1 - fte_s->top;
    x1 += fte_s->left;

    int x, y, adv = fte_s->xadvance;
    int max_w = fte_s->width, max_h = fte_s->height;

    if(x1+max_w > x2)
        max_w -= (x1+max_w) - x2;

    if(y1+max_h > y2)
        max_h -= (y1+max_h) - y2;
    //int ptr = 0;

    for(y = 0; y < max_h; ++y)
    {
        for(x = 0; x < max_w; ++x)
        {
            uint8_t c = fte_s->bitmap[((y)*fte_s->width+(x))];
            if(!c)
                continue;

            (((unsigned char *)&color)[3]) = alpha < c? c - alpha : 0; // alpha chanel

            setPixel(context, x1+x, y1+y, color);
        }
    }

    return adv;
}



uint32_t ftStringMetrics(fte_info *fti, const void *str, uint32_t *height, uint32_t *y_seek, int32_t max_leter_cnt, wchar_t (*conv)(const void **))
{
    uint32_t w = 0, h = 0;
    int t = 0;
    int errs = 0;
    wchar_t smb = conv(&str);
    //w -= fte_get_symbol(ftf->fti, smb)->left;

    while(smb && max_leter_cnt > 0)
    {
        fte_symbol *fte = fte_get_symbol(fti, smb);
        if(!fte) {
            ++errs;
            continue;
        }

        w += fte->xadvance;

        if(t < fte->height - fte->top)
        {
            t = fte->height - fte->top;
        }

        if((int)h < fte->height)
            h = fte->height;
        smb = conv(&str);
        --max_leter_cnt;
    }


    if(height) *height = h;
    if(y_seek) *y_seek = t;
    return w == 0 && errs? -1 : w;
}




uint16_t ftDrawScrollString(void *context, int width, int height, fte_info *fti, const void *str, int x1, int y1,
                            int x2, int y2, int type, uint8_t leter_step, int32_t max_leter_cnt, wchar_t (*conv)(const void **),
                            unsigned int color, void (*setPixel)(void *context, int x, int y, unsigned int color))
{
    uint16_t h = 0;
    char align = 0;
    const void *mem = str;
    uint16_t smb = conv((void *)&str);
    uint32_t maximum_h = height;
    int mw = x2-x1;
    int mh = y2-y1;

    //x -= fte_get_symbol(ftf->fti, smb)->left;


#define processing_draw() while(smb && max_leter_cnt > 0)\
            {\
                x1 += ftDrawSymbol(context, fti, (uint16_t)smb, x1, y1, x2, y2, color, setPixel) + leter_step;\
                if(x1 >= width || x1 >= x2) break;\
                fte_symbol *s = fte_get_symbol(fti, smb);\
                if(h < s->height)\
                    h = s->height;\
                smb = conv((void *)&str);\
                --max_leter_cnt;\
            }


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
            int s_maxw = ftStringMetrics(fti, mem, 0, 0, max_leter_cnt, conv);
            x1 = x1 + ((mw/2) - (s_maxw/2));
            processing_draw();
            break;
        }

        case 2: // w right
        {
            int s_maxw = ftStringMetrics(fti, mem, 0, 0, max_leter_cnt, conv);
            x1 += mw - s_maxw;
            processing_draw();
            break;
        }


        case 3: // w: left  h: center
        {
            uint32_t s_maxh;
            /*int s_maxw = */ftStringMetrics(fti, mem, &s_maxh, 0, max_leter_cnt, conv);
            y1 = y1 + ((mh/2) + (s_maxh/2));
            processing_draw();
            break;
        }

        case 4: // w: center  h: center
        {
            uint32_t s_maxh, top;
            int s_maxw = ftStringMetrics(fti, mem, &s_maxh, &top, max_leter_cnt, conv);
            s_maxh -= top - 1;
            y1 = y1 + ((mh/2) + (s_maxh/2));
            x1 = x1 + ((mw/2) - (s_maxw/2));
            processing_draw();
            break;
        }


        case 5: // w: right  h: center
        {
            uint32_t s_maxh, top;
            int s_maxw = ftStringMetrics(fti, mem, &s_maxh, &top, max_leter_cnt, conv);
            s_maxh -= top - 1;
            y1 += y1 + ((maximum_h-y1)/2) + (s_maxh/2);
            x1 += mw - s_maxw;
            processing_draw();
            break;
        }


        case 6: // w: left  h: down
        {
            uint32_t s_maxh, top;
            /*int s_maxw = */ftStringMetrics(fti, mem, &s_maxh, &top, max_leter_cnt, conv);
            y1 += mh - top - 1;
            processing_draw();
            break;
        }


        case 7: // w: center  h: down
        {
            uint32_t s_maxh, top;
            int s_maxw = ftStringMetrics(fti, mem, &s_maxh, &top, max_leter_cnt, conv);
            y1 += maximum_h - top - 1;
            x1 += x1 + ((mw-x1)/2) - s_maxw/2;
            processing_draw();
            break;
        }


        case 8: // w: right  h: down
        {
            uint32_t s_maxh, top;
            int s_maxw = ftStringMetrics(fti, mem, &s_maxh, &top, max_leter_cnt, conv);
            y1 += maximum_h - top - 1;
            x1 += mw - s_maxw;
            processing_draw();
            break;
        }


        case 9: // w: left  h: up
        {
            uint32_t s_maxh, s_maxh_t;
            /*int s_maxw = */ftStringMetrics(fti, mem, &s_maxh, &s_maxh_t, max_leter_cnt, conv);
            y1 += s_maxh;
            processing_draw();
            break;
        }



        case 10: // w: center  h: up
        {
            uint32_t s_maxh;
            uint32_t s_maxw = ftStringMetrics(fti, mem, &s_maxh, 0, max_leter_cnt, conv);
            y1 += s_maxh;
            x1 += x1 + ((mw-x1)/2) - (s_maxw/2);
            processing_draw();
            break;
        }



        case 11: // w: right  h: up
        {
            uint32_t s_maxh, s_maxh_t;
            int s_maxw = ftStringMetrics(fti, mem, &s_maxh, &s_maxh_t, max_leter_cnt, conv);
            y1 += s_maxh - s_maxh_t;
            x1 += mw - s_maxw;
            processing_draw();
            break;
        }


    }
#undef processing_draw
    return h;
}


/*
uint32_t ftDrawString(GLContext *ctx, ft_font *ftf, const void *str, int16_t x, int16_t y,
                 int mw, int mh, int type, uint8_t leter_step, int32_t _max_leter_cnt, wchar_t (*conv)(const void **))
{
    void *mem = (void *)str;
    int32_t max_leter_cnt = 0;
    int32_t _y = y;
    wchar_t c = conv(&str);


    while(c != L'\x0' && _max_leter_cnt > 0)
    {
        if(c == L'\r' || c == L'\n')
        {
            void *_m = (void *)str;
            wchar_t _c = conv((const void **)&_m);
            if(c == L'\r' && _c == L'\n' ) {
                str = _m;
            }

            uint32_t h = ftDrawString(ctx, ftf, mem, x, _y, mw, mh, type, leter_step, max_leter_cnt, conv);
            _y += h;
            mem = (void *)str;
            max_leter_cnt = 0;
        }

        ++max_leter_cnt;
        c = conv(&str);
        --_max_leter_cnt;
    }

    if(max_leter_cnt)
    {
        //uint32_t h = ftDrawString(ctx, ftf, mem, x, _y, mw, mh, type, leter_step, max_leter_cnt, conv);
        //_y += h+2;
    }

    return _y;
}
*/


#endif



