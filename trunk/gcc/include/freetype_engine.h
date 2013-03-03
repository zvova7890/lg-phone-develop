

#ifndef __FT_ENGINE_H__
#define __FT_ENGINE_H__

#include <inttypes.h>
#include <ft2build.h>
#include FT_FREETYPE_H

#include <inttypes.h>


//#define __SYSTEM_FONT__


#ifdef __cplusplus
extern "C" {
#endif


typedef struct
{
    int16_t width;
    int16_t height;
    int16_t top;
    int16_t left;
    int16_t xadvance;
    int16_t yadvance;
    uint8_t* bitmap;
}fte_symbol;


typedef struct
{
    uint16_t w, h;
    uint16_t clients;
    void *fte;
    fte_symbol **symbols;
    int symbols_cnt;
}fte_info;

typedef struct
{
    const char    *file;
    FT_Library    library;
    FT_Face          face;
    FT_GlyphSlot     slot;
    FT_Error        error;
    FT_Int32        flags;
    uint32_t       clients;
    fte_info **font_map;
    int font_cnt;
}ft_engine;


typedef struct
{
    ft_engine *fte;
    fte_info *fti;
}ft_font;


ft_engine * fte_open(const char *file);
void fte_close(ft_engine *fte, int);
const char *fte_get_name(ft_engine *fte);
int fte_clear_cache(ft_engine *fte);

fte_info *fte_open_cache_by_metrics(ft_engine *fte, unsigned long size);
int fte_close_cache_metrics(fte_info *fti);
int fte_cache_symbol(fte_info *fti, unsigned long letter);
fte_symbol *fte_get_symbol(fte_info *fti, unsigned long letter);
int fte_clear_cache_by_metrics(fte_info *fti);

FT_Library fte_library_handler(ft_engine *fte);
FT_Face fte_face_handler(ft_engine *fte);
void fte_set_flags(ft_engine *fte, FT_Int32 flag);
FT_Int32 fte_flags(ft_engine *fte);



ft_font *ft_open(const char *font, uint16_t size);
void ft_close(ft_font *f);


enum
{
    FT_TEXT_W_LEFT       = (1 << 0),
    FT_TEXT_W_CENTER     = (1 << 1),
    FT_TEXT_W_RIGHT      = (1 << 2),

    FT_TEXT_H_UP         = (1 << 3),
    FT_TEXT_H_CENTER     = (1 << 4),
    FT_TEXT_H_DOWN       = (1 << 5),

    FT_TEXT_CENTER_BY_XSTART  = (1 << 6),
    FT_TEXT_CENTER_BY_YSTART  = (1 << 7),
    FT_TEXT_WORDBREAK      = (1 << 8),
    FT_TEXT_SENTENCEBREAK  = (1 << 9)
};


#ifndef __SYSTEM_FONT__
uint16_t ftDrawSymbol(void *context, fte_info *fti, uint16_t leter, int x1, int y1, int x2, int y2, unsigned int color,
                      void (*setPixel)(void *context, int x, int y, unsigned int color));
uint32_t ftStringMetrics(fte_info *fti, const void *str, uint32_t *height, uint32_t *y_seek, int32_t max_leter_cnt, wchar_t (*conv)(const void **));

uint16_t ftDrawScrollString(void *context, int width, int height, fte_info *fti, const void *str, int x1, int y1,
                            int x2, int y2, int type, uint8_t leter_step, int32_t max_leter_cnt, wchar_t (*conv)(const void **),
                            unsigned int color, void (*setPixel)(void *context, int x, int y, unsigned int color));
#else

uint32_t ftStringMetrics(int font, const void *str, uint32_t *height, uint32_t *y_seek, int32_t max_leter_cnt, wchar_t (*conv)(const void **));

#endif



#ifdef __cplusplus
}
#endif

#endif
