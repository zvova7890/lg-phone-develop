

#include <gl.h>
#include "freetype_engine.h"

#ifndef __SYSTEM_FONT__
uint16_t glStringEngineDrawScrollString(GLContext *ctx, fte_info *fti, const void *str, int x1, int y1,
                            int x2, int y2, int type, uint8_t leter_step, int32_t max_leter_cnt, wchar_t (*conv)(const void **),
                            unsigned int color);
#else
uint16_t glStringEngineDrawScrollString(GLContext *ctx, int font_h, const void *str, int x1, int y1,
                            int x2, int y2, int type, uint8_t leter_step, int32_t max_leter_cnt, wchar_t (*conv)(const void **),
                            unsigned int color);
#endif

/* UCS */

static inline wchar_t ucs_conv(const void **data)
{
    wchar_t **str = (wchar_t**)data;
    wchar_t tmp = **str;
    *str = *str+1;
    return tmp;
}



#ifndef __SYSTEM_FONT__
inline unsigned int glDrawUCSString(GLContext *ctx, fte_info *fti, const wchar_t *str, int x1, int y1, int x2, int y2,
                             int align, uint8_t leter_step, int32_t max_leter_cnt)
{
    return glStringEngineDrawScrollString(ctx, fti, (const void*)str, x1, y1, x2, y2, align, leter_step,
                       max_leter_cnt, ucs_conv, ctx->pen);
}


inline unsigned int glUCSStringMetrics(fte_info *fti, const wchar_t *str, uint32_t *height, uint32_t *top, int32_t max_leter_cnt)
{
    return ftStringMetrics(fti, (const void*)str, height, top, max_leter_cnt, ucs_conv);
}

#else

inline unsigned int glDrawUCSString(GLContext *ctx, int font, const wchar_t *str, int x1, int y1, int x2, int y2,
                             int align, uint8_t leter_step, int32_t max_leter_cnt)
{
    return glStringEngineDrawScrollString(ctx, font, (const void*)str, x1, y1, x2, y2, align, leter_step,
                       max_leter_cnt, ucs_conv, ctx->pen);
}


inline unsigned int glUCSStringMetrics(int font, const wchar_t *str, uint32_t *height, uint32_t *top, int32_t max_leter_cnt)
{
    return ftStringMetrics(font, (const void*)str, height, top, max_leter_cnt, ucs_conv);
}
#endif



/* UTF-8 */

static inline wchar_t utf8_to_ucs2(const void **__word)
{
    wchar_t ret;
    const char **_word = (const char**)__word;
    const char *s = *_word;

    /* Assumes correct input and no characters outside the BMP. */

    if((s[0]&0x80)==0)
    {
        ret = s[0];
        s++;
    }
    else if((s[0]&0x20)==0)
    {
        ret = (s[0]&0x1F)<<6 | (s[1]&0x3F);
        s+=2;
    }
    else if((s[0]&0x10)==0)
    {
        ret = (s[0]&0x0F)<<12 | (s[1]&0x3F)<<6 | (s[2]&0x3F);
        s+=3;
    }
    else {
            if(s[0] == 0)
                ret = 0;
            else
                ret = L'?';
    }

    *_word = s;
    return ret;
}



#ifndef __SYSTEM_FONT__
inline unsigned int glUTF8StringMetrics(fte_info *fti, const char *str, uint32_t *height, uint32_t *top, int32_t max_leter_cnt)
{
    return ftStringMetrics(fti, (const void*)str, height, top, max_leter_cnt, utf8_to_ucs2);
}


inline unsigned int glUTF8DrawString(GLContext *ctx, fte_info *fti, const char *str, int x1, int y1, int x2, int y2,
                              int align, uint8_t leter_step, int32_t max_leter_cnt)
{
    return glStringEngineDrawScrollString(ctx, fti, (const void*)str, x1, y1, x2, y2, align, leter_step,
                       max_leter_cnt, utf8_to_ucs2, ctx->pen);
}

#else
inline unsigned int glUTF8StringMetrics(int font, const char *str, uint32_t *height, uint32_t *top, int32_t max_leter_cnt)
{
    return ftStringMetrics(font, (const void*)str, height, top, max_leter_cnt, utf8_to_ucs2);
}


inline unsigned int glUTF8DrawString(GLContext *ctx, int font, const char *str, int x1, int y1, int x2, int y2,
                              int align, uint8_t leter_step, int32_t max_leter_cnt)
{
    return glStringEngineDrawScrollString(ctx, font, (const void*)str, x1, y1, x2, y2, align, leter_step,
                       max_leter_cnt, utf8_to_ucs2, ctx->pen);
}

#endif




/* Default font */
#ifndef __SYSTEM_FONT__
static ft_engine *default_font = 0;
static fte_info *fonts[256] = {0};
#endif

void initGLStringFont()
{
    memset(fonts, 0, sizeof(fonts));
#ifndef __SYSTEM_FONT__
    default_font = fte_open("arial.ttf");
#endif
}


void finiGLStringFont()
{
#ifndef __SYSTEM_FONT__
    int i;
    for(i=0; i<256; ++i)
        if(fonts[i])
            fte_close_cache_metrics(fonts[i]);

    fte_close(default_font, 0);
#endif
}


#ifndef __SYSTEM_FONT__
static inline fte_info *getFont(int size)
{
    if(!default_font) {
        initGLStringFont();
        if(!default_font)
            return 0;
    }

    if(size < 0 || size >= 256)
        return 0;

    if(fonts[size])
        return fonts[size];
    else
        return fonts[size] = fte_open_cache_by_metrics(default_font, size);
}
#endif

/*
unsigned int glStringMetrics(const char *str, int font, uint32_t *height, uint32_t *top, int32_t max_leter_cnt)
{

}
*/

unsigned int glCtxDrawString(GLContext *ctx, const char *str, int x1, int y1, int x2, int y2, int font, int align, uint8_t leter_step, int32_t max_leter_cnt)
{
#ifndef __SYSTEM_FONT__
    fte_info *fti = getFont(font);
    if(fti)
        return glUTF8DrawString(ctx, fti, str, x1, y1, x2, y2, align, leter_step, max_leter_cnt);
    return 0;
#else
    return glUTF8DrawString(ctx, font, str, x1, y1, x2, y2, align, leter_step, max_leter_cnt);
#endif
}


unsigned int glCtxDrawUString(GLContext *ctx, const wchar_t *str, int x1, int y1, int x2, int y2, int font, int align, uint8_t leter_step, int32_t max_leter_cnt)
{
#ifndef __SYSTEM_FONT__
    fte_info *fti = getFont(font);
    if(fti)
        return glDrawUCSString(ctx, fti, str, x1, y1, x2, y2, align, leter_step, max_leter_cnt);
    return 0;
#else
    return glDrawUCSString(ctx, font, str, x1, y1, x2, y2, align, leter_step, max_leter_cnt);
#endif
}


int glStringMetrics(int font, const char *str, uint32_t *height, uint32_t *top, int32_t max_leter_cnt)
{
#ifndef __SYSTEM_FONT__
    fte_info *fti = getFont(font);
    if(fti)
        return glUTF8StringMetrics(fti, str, height, top, max_leter_cnt);
    return -1;
#else
    return glUTF8StringMetrics(font, str, height, top, max_leter_cnt);
#endif
}







