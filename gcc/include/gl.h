
#ifndef __GL_H__
#define __GL_H__

#include "freetype_engine.h"

#define glMin(x, y) (x > y? y : x)
#define glMax(x, y) (x < y? y : x)
#define glAbs(x) (((x) < 0) ? -(x) : (x))

typedef unsigned int GLColor;
typedef void (*glPixelSetProc)(void *ctx, int x, int y);
typedef void (*glCPixelSetProc)(void *ctx, int x, int y, GLColor c);

#define X2MassBitmap

#ifndef X2MassBitmap
#define __glPixelPoint16(buf, w, x, y) *(((unsigned short*)buf)+(y*w+x))
#define __glPixelPoint32(buf, w, x, y) *(((unsigned int*)buf)+(y*w+x))
#else
#define __glPixelPoint16(buf, w, x, y) (((unsigned short**)buf)[y][x])
#define __glPixelPoint32(buf, w, x, y) (((unsigned int**)buf)[y][x])
#endif



typedef struct
{
    unsigned short width, height;
    unsigned char depth;
    void *framebuffer;
#ifdef X2MassBitmap
    void *bitmap;
#endif
    GLColor pen;
    GLColor depth_dep_pen;
    unsigned char alpha;
    int attr;
    glPixelSetProc setPixel;
    glCPixelSetProc setColorPixel;
    int *polyInts;
    int polyIntsCnt;

    unsigned short clip_x;
    unsigned short clip_y;
    unsigned short clip_w;
    unsigned short clip_h;
}GLContext;


typedef struct
{
    int x, y;
}GLPoint;


#define GL_ALPHA_TEST (1 << 1)


#define GL_ARC     0
#define GL_CHORD   1
#define GL_NO_FILL 2
#define GL_EDGED   4


static inline GLColor rgb32ToRgb16(const GLColor rgb32) {
    return (rgb32 >> 8 & 0xF800) | (rgb32 >> 5 & 0x07E0) | (rgb32 >> 3 & 0x001F);
}


static inline GLColor rgb16ToRgb32(GLColor c) {
    return 0xff000000
        | ((((c) << 3) & 0xf8) | (((c) >> 2) & 0x7))
        | ((((c) << 5) & 0xfc00) | (((c) >> 1) & 0x300))
        | ((((c) << 8) & 0xf80000) | (((c) << 3) & 0x70000));
}




#define glRgb16(r,g,b)  ((uint16_t)((r & 0xF8) << 8) | ((g & 0xFC) << 3) | ((b & 0xF8) >> 3))
#define glRgb32(r,g,b,a)  ((uint32_t)(a << 24) | (r << 16) | (g << 8) | (b))


#define glColorRed16(c) (((c & 0xF800) >> 11) << 3)
#define glColorGreen16(c) (((c & 0x7E0) >> 5) << 2)
#define glColorBlue16(c) ((c & 0x1F) << 3)


#define glColorAlpha(color32) (color32 >> 24 & 0xff)
#define glColorRed(color32) (color32 >> 16 & 0xFF)
#define glColorGreen(color32) (color32 >> 8 & 0xFF)
#define glColorBlue(color32) (color32 & 0xFF)

#define glPutPixel32(ctx, x, y) __glPixelPoint32(ctx->framebuffer, ctx->width, x, y) = ctx->depth_dep_pen
#define glPutPixel16(ctx, x, y) __glPixelPoint16(ctx->framebuffer, ctx->width, x, y) = ctx->depth_dep_pen
#define glGetPixel32(ctx, x, y) __glPixelPoint32(ctx->framebuffer, ctx->width, x, y)
#define glGetPixel16(ctx, x, y) __glPixelPoint16(ctx->framebuffer, ctx->width, x, y)

#define glPutPixel32c(ctx, x, y, c) __glPixelPoint32(ctx->framebuffer, ctx->width, x, y) = c
#define glPutPixel16c(ctx, x, y, c) __glPixelPoint16(ctx->framebuffer, ctx->width, x, y) = c


#define glDrawPixel32(ctx, x, y) glPutPixel32c(ctx, x, y, glAlphaBlend(ctx->pen, glGetPixel32(ctx, x, y),  ctx->alpha))
#define glDrawPixel16(ctx, x, y) glPutPixel16c(ctx, x, y, glAlphaBlend16c(ctx->depth_dep_pen, glGetPixel16(ctx, x, y),  ctx->alpha))


#define glDrawPixel32c(ctx, x, y, c) glPutPixel32c(ctx, x, y, glAlphaBlend(c, glGetPixel32(ctx, x, y),  glColorAlpha(c)))
#define glDrawPixel16c(ctx, x, y, c) glPutPixel16c(ctx, x, y, glAlphaBlend16(c, glGetPixel16(ctx, x, y),  glColorAlpha(c)))


#define glTestAlphaBlend(ctx) (ctx->alpha < 0xff && ctx->attr & GL_ALPHA_TEST)

#ifdef __cplusplus
extern "C" {
#endif


GLContext *glCreateContext(unsigned short width, unsigned short height, unsigned short depth, void *framebuffer);
void glDestroyContext(GLContext *ctx);


GLColor _glAlphaBlend(GLColor color, GLColor background, unsigned char alpha);
unsigned short _glAlphaBlend16(GLColor color, unsigned short background, unsigned char alpha);
unsigned short _glAlphaBlend16c(unsigned short color, unsigned short background, unsigned char alpha);

__attribute__((always_inline))
static inline GLColor glAlphaBlend(GLColor color, GLColor background, unsigned char alpha) {
    if(alpha == 0xFF)
        return color;
    return _glAlphaBlend(color, background, alpha);
}

__attribute__((always_inline))
static inline unsigned short glAlphaBlend16(GLColor color, unsigned short background, unsigned char alpha) {
    if(alpha == 0xFF)
        return rgb32ToRgb16(color);
    return _glAlphaBlend16(color, background, alpha);
}

__attribute__((always_inline))
static inline unsigned short glAlphaBlend16c(unsigned short color, unsigned short background, unsigned char alpha) {
    if(alpha == 0xFF)
        return color;
    return _glAlphaBlend16c(color, background, alpha);
}



glPixelSetProc glGetPixelProc(GLContext *ctx);
glCPixelSetProc glGetCPixelProc(GLContext *ctx);

void glEnable(GLContext *ctx, int mode);
void glDisable(GLContext *ctx, int mode);

void glSetPen(GLContext *ctx, GLColor color);
void glSetClipRegion(GLContext *ctx, int x, int y, int w, int h);
void glResetClipRegion(GLContext *ctx);
void glSetRenderRegion(GLContext *ctx, int x, int y, int width, int height);

void glClear(GLContext *ctx, GLColor color);

void glDrawHLine(GLContext *ctx, int x1, int x2, int y);
void glDrawVLine(GLContext *ctx, int y1, int y2, int x);
void glDrawLine(GLContext *ctx, int x1, int y1, int x2, int y2);

void glDrawRectange(GLContext *ctx, int x1, int y1, int x2, int y2);
void glDrawFilledRectange(GLContext *ctx, int x1, int y1, int x2, int y2);

void glDrawCircle(GLContext *ctx, int x, int y, int r);
void glDrawFilledCircle(GLContext *ctx, int x, int y, int r);

void glDrawPolygon (GLContext *ctx, GLPoint *p, int n);
void glDrawFilledPolygon (GLContext *ctx, GLPoint *p, int n);

void glDrawArc (GLContext *ctx, int cx, int cy, int w, int h, int s, int e);
void glDrawFilledArc (GLContext *ctx, int cx, int cy, int w, int h, int s, int e, int style);

void glDrawEllipse(GLContext *ctx, int mx, int my, int w, int h);
void glDrawFilledEllipse(GLContext *ctx, int mx, int my, int w, int h);

void glDrawFilledTriangle(GLContext *ctx, int x1, int y1, int x2, int y2, int x3, int y3);
void glDrawTriangle(GLContext *ctx, int x1, int y1, int x2, int y2, int x3, int y3);

void glDrawBitmap(GLContext *ctx, int x, int y, int w, int h, int depth, void *bitmap);


unsigned int glUCSStringMetrics(fte_info *fti, const wchar_t *str, uint32_t *height, uint32_t *top, int32_t max_leter_cnt);
unsigned int glDrawUCSString(GLContext *ctx, fte_info *fti, const wchar_t *str, int x1, int y1,
                        int x2, int y2, int align, uint8_t leter_step, int32_t max_leter_cnt);

unsigned int glUTF8StringMetrics(fte_info *fti, const char *str, uint32_t *height, uint32_t *top, int32_t max_leter_cnt);
unsigned int glUTF8DrawString(GLContext *ctx, fte_info *fti, const char *str, int x1, int y1,
                        int x2, int y2, int align, uint8_t leter_step, int32_t max_leter_cnt);

unsigned int glDrawString(GLContext *ctx, const char *str, int x1, int y1, int x2, int y2, int font, int align, uint8_t leter_step, int32_t max_leter_cnt);

#ifdef __cplusplus
}
#endif


#endif

