
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

#define __glBufPixelPoint16(buf, w, x, y) *(((unsigned short*)buf)+(y*w+x))
#define __glBufPixelPoint32(buf, w, x, y) *(((unsigned int*)buf)+(y*w+x))

#ifndef X2MassBitmap
#define __glPixelPoint16(buf, w, x, y) *(((unsigned short*)buf)+(y*w+x))
#define __glPixelPoint32(buf, w, x, y) *(((unsigned int*)buf)+(y*w+x))
#else
#define __glPixelPoint16(buf, w, x, y) (((unsigned short**)buf)[y][x])
#define __glPixelPoint32(buf, w, x, y) (((unsigned int**)buf)[y][x])
#endif

#define __ALIGN_MASK(x, mask)	(((x) + (mask)) & ~(mask))

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

    unsigned short clip_x1;
    unsigned short clip_y1;
    unsigned short clip_x2;
    unsigned short clip_y2;
    void *clip_queue;
}GLContext;


typedef struct
{
    int x, y;
}GLPoint;

typedef struct
{
    int x1, y1;
    int x2, y2;
}GLRect;

typedef struct
{
    short size;
    short at;
    char can_realloc;
    GLPoint *pts;
}GLPoints;

typedef struct
{
    GLColor color;
    unsigned char pixels;
}GLGradientCell;

typedef struct
{
    GLGradientCell *colors;
    int count;
}GLGradient;


typedef struct
{
    void *prev;
    void *next;
    int   body;
}GLQueueListItem;


typedef struct
{
    GLQueueListItem *first,
                    *last;
}GLQueueList;



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



#define GL_UNUSED(x) ((void)x);

#define glRgb16(r,g,b)  ((uint16_t)((r & 0xF8) << 8) | ((g & 0xFC) << 3) | ((b & 0xF8) >> 3))
#define glRgb32(r,g,b,a)  ((uint32_t)(a << 24) | (r << 16) | (g << 8) | (b))

/*
#define glColorRed16(c) (((c & 0xF800) >> 11) << 3)
#define glColorGreen16(c) (((c & 0x7E0) >> 5) << 2)
#define glColorBlue16(c) ((c & 0x1F) << 3)*/


#define glColorRed16(c) ((c >> 8) & 0xF8)
#define glColorGreen16(c) ((c >> 3) & 0xFC)
#define glColorBlue16(c) ((c << 3) & 0xF8)


#define glColorAlpha(color32) (color32 >> 24)
#define glColorRed(color32) (color32 >> 16 & 0xFF)
#define glColorGreen(color32) (color32 >> 8 & 0xFF)
#define glColorBlue(color32) (color32 & 0xFF)

#define glPutPixel32(ctx, x, y) __glPixelPoint32(ctx->framebuffer, ctx->width, x, y) = ctx->depth_dep_pen
#define glPutPixel16(ctx, x, y) __glPixelPoint16(ctx->framebuffer, ctx->width, x, y) = ctx->depth_dep_pen
#define glGetPixel32(ctx, x, y) __glPixelPoint32(ctx->framebuffer, ctx->width, x, y)
#define glGetPixel16(ctx, x, y) __glPixelPoint16(ctx->framebuffer, ctx->width, x, y)

#define glPutPixel32c(ctx, x, y, c) __glPixelPoint32(ctx->framebuffer, ctx->width, x, y) = c
#define glPutPixel16c(ctx, x, y, c) __glPixelPoint16(ctx->framebuffer, ctx->width, x, y) = c


#define glDrawPixel32(ctx, x, y) glPutPixel32c(ctx, x, y, glAlphaBlend32_32(ctx->pen, glGetPixel32(ctx, x, y),  ctx->alpha))
#define glDrawPixel16(ctx, x, y) glPutPixel16c(ctx, x, y, glAlphaBlend16_16(ctx->depth_dep_pen, glGetPixel16(ctx, x, y),  ctx->alpha))


#define glDrawPixel32c(ctx, x, y, c) glPutPixel32c(ctx, x, y, glAlphaBlend32_32(c, glGetPixel32(ctx, x, y),  glColorAlpha(c)))
#define glDrawPixel16c(ctx, x, y, c) glPutPixel16c(ctx, x, y, glAlphaBlend16_32(c, glGetPixel16(ctx, x, y),  glColorAlpha(c)))

#define glDrawPixel32ca(ctx, x, y, c, a) glPutPixel32c(ctx, x, y, glAlphaBlend32_32(c, glGetPixel32(ctx, x, y),  a))
#define glDrawPixel16ca(ctx, x, y, c, a) glPutPixel16c(ctx, x, y, glAlphaBlend16_16(c, glGetPixel16(ctx, x, y),  a))


#define glDrawPixel16_16ca(ctx, x, y, c, a) glPutPixel16c(ctx, x, y, glAlphaBlend16_16(c, glGetPixel16(ctx, x, y),  a))
#define glDrawPixel32_16ca(ctx, x, y, c, a) glPutPixel32c(ctx, x, y, glAlphaBlend32_16(c, glGetPixel32(ctx, x, y),  a))
#define glDrawPixel16_32ca(ctx, x, y, c, a) glPutPixel16c(ctx, x, y, glAlphaBlend16_32(c, glGetPixel16(ctx, x, y),  a))


#define glTestAlphaBlend(ctx) (ctx->alpha < 0xff && ctx->attr & GL_ALPHA_TEST)
#define glTestRange(ctx, x, y) (x >= ctx->clip_x1 && y >= ctx->clip_y1 && x < ctx->clip_x2 && y < ctx->clip_y2)

#ifdef __cplusplus
extern "C" {
#endif

extern GLContext *DefaultGLContext;


GLContext *glCreateContext(unsigned short width, unsigned short height, unsigned short depth, void *framebuffer);
void glSetContextProp(GLContext *ctx, int width, int height, int depth, void *framebuffer);
void glDestroyContext(GLContext *ctx);

#define glActivateContext(ctx) DefaultGLContext = ctx
#define glActiveContext() DefaultGLContext


__attribute__((always_inline))
static inline GLColor glAlphaBlend32_32(GLColor color, GLColor background, unsigned char alpha)
{
    unsigned char a = glColorAlpha(background);
    unsigned char alpha2 = 0xff - alpha;
    unsigned int r = (glColorRed(color) * alpha + (glColorRed(background) * alpha2) ) >> 8;
    unsigned int g = (glColorGreen(color) * alpha + (glColorGreen(background) * alpha2) ) >> 8;
    unsigned int b = (glColorBlue(color) * alpha + (glColorBlue(background) * alpha2) ) >> 8;

    return glRgb32(r, g, b, a);
}


__attribute__((always_inline))
static inline unsigned short glAlphaBlend16_32(GLColor color, unsigned short background, unsigned char alpha)
{
    unsigned char alpha2 = 0xff - alpha;

    unsigned char r = (glColorRed(color) * alpha + (glColorRed16(background) * alpha2) ) >> 8;
    unsigned char g = (glColorGreen(color) * alpha + (glColorGreen16(background) * alpha2) ) >> 8;
    unsigned char b = (glColorBlue(color) * alpha + (glColorBlue16(background) * alpha2) ) >> 8;

    return glRgb16(r, g, b);
}


__attribute__((always_inline))
static inline GLColor glAlphaBlend32_16(unsigned short color, unsigned short background, unsigned char alpha)
{
    unsigned char alpha2 = 0xff - alpha;

    unsigned char r = (glColorRed16(color) * alpha + (glColorRed16(background) * alpha2) ) >> 8;
    unsigned char g = (glColorGreen16(color) * alpha + (glColorGreen16(background) * alpha2) ) >> 8;
    unsigned char b = (glColorBlue16(color) * alpha + (glColorBlue16(background) * alpha2) ) >> 8;

    return glRgb32(r, g, b, 0xff);
}


__attribute__((always_inline))
static inline unsigned short glAlphaBlend16_16(unsigned short color, unsigned short background, unsigned char alpha)
{
    unsigned char alpha2 = 0xff - alpha;

    unsigned char r = (glColorRed16(color) * alpha + (glColorRed16(background) * alpha2) ) >> 8;
    unsigned char g = (glColorGreen16(color) * alpha + (glColorGreen16(background) * alpha2) ) >> 8;
    unsigned char b = (glColorBlue16(color) * alpha + (glColorBlue16(background) * alpha2) ) >> 8;

    return glRgb16(r, g, b);
}


__attribute__((always_inline))
static inline void glCtxSetPen(GLContext *ctx, GLColor color) {
    ctx->pen = color;
    ctx->alpha = glColorAlpha(color);

    switch(ctx->depth)
    {
        case 16:
            ctx->depth_dep_pen = rgb32ToRgb16(color);
            break;

        case 32:
            ctx->depth_dep_pen = color;
            break;
    }
}


static inline void glPointsPut(GLPoints *pts, int x, int y) {
    if(pts->at+1 < pts->size) {
        __set:
        pts->pts[pts->at].x = x;
        pts->pts[pts->at++].y = y;
    } else if(pts->can_realloc) {
        pts->size += 56;
        pts->pts = (GLPoint*)realloc(pts->pts, pts->size*sizeof(GLPoint));
        goto __set;
    }
}


glPixelSetProc glGetPixelProc(GLContext *ctx);
glCPixelSetProc glGetCPixelProc(GLContext *ctx);


int glLine(GLContext *ctx, GLPoints *pts, int x1, int y1, int x2, int y2, int range_check);
int glArc(GLContext *ctx, GLPoints *pts, int cx, int cy, int w, int h, int s, int e, int range_check);

void glCtxEnable(GLContext *ctx, int mode);
#define glEnable(mode) glCtxEnable(DefaultGLContext, mode)
void glCtxDisable(GLContext *ctx, int mode);
#define glDisable(mode) glCtxDisable(DefaultGLContext, mode)

#define glSetPen(color) glCtxSetPen(DefaultGLContext, color)

void glCtxSetClipRegion(GLContext *ctx, int x1, int y1, int x2, int y2);
#define glSetClipRegion(x1, y1, x2, y2) glCtxSetClipRegion(DefaultGLContext, x1, y1, x2, y2)
void glCtxResetClipRegion(GLContext *ctx);
#define glResetClipRegion() glCtxResetClipRegion(DefaultGLContext)
void glCtxSaveClipRegion(GLContext *ctx);
#define glSaveClipRegion() glCtxSaveClipRegion(DefaultGLContext)
void glCtxRestoreClipRegion(GLContext *ctx);
#define glRestoreClipRegion() glCtxRestoreClipRegion(DefaultGLContext)

void glCtxSetRenderRegion(GLContext *ctx, int x, int y, int width, int height);
#define glSetRenderRegion(x, y, width, height) glCtxSetRenderRegion(DefaultGLContext, x, y, width, height)
void glCtxResetRenderRegion(GLContext *ctx);
#define glResetRenderRegion() glCtxResetRenderRegion(DefaultGLContext)

void glCtxClear(GLContext *ctx, GLColor color);
#define glClear(color) glCtxClear(DefaultGLContext, color)

void glCtxDrawHLine(GLContext *ctx, int x1, int x2, int y);
#define glDrawHLine(x1, x2, y) glCtxDrawHLine(DefaultGLContext, x1, x2, y)
void glCtxDrawVLine(GLContext *ctx, int y1, int y2, int x);
#define glDrawVLine(y1, y2, x) glCtxDrawVLine(DefaultGLContext, y1, y2, x)
void glCtxDrawLine(GLContext *ctx, int x1, int y1, int x2, int y2);
#define glDrawLine(x1, y1, x2, y2) glCtxDrawLine(DefaultGLContext, x1, y1, x2, y2)

void glCtxDrawRectange(GLContext *ctx, int x1, int y1, int x2, int y2);
#define glDrawRectange(x1, y1, x2, y2) glCtxDrawRectange(DefaultGLContext, x1, y1, x2, y2)
void glCtxDrawFilledRectange(GLContext *ctx, int x1, int y1, int x2, int y2);
#define glDrawFilledRectange(x1, y1, x2, y2) glCtxDrawFilledRectange(DefaultGLContext, x1, y1, x2, y2)

void glCtxDrawRoundedRect(GLContext *ctx, int x, int y, int w, int h, int round_x, int round_y);
#define glDrawRoundedRect(x, y, w, h, round_x, round_y) glCtxDrawRoundedRect(DefaultGLContext, x, y, w, h, round_x, round_y)
void glCtxFillRoundedRect(GLContext *ctx, int x, int y, int w, int h, int round_x, int round_y);
#define glFillRoundedRect(x, y, w, h, round_x, round_y) glCtxFillRoundedRect(DefaultGLContext, x, y, w, h, round_x, round_y)

void glCtxDrawCircle(GLContext *ctx, int x, int y, int r);
#define glDrawCircle(x, y, r) glCtxDrawCircle(DefaultGLContext, x, y, r)
void glCtxDrawFilledCircle(GLContext *ctx, int x, int y, int r);
#define glDrawFilledCircle(x, y, r) glCtxDrawFilledCircle(DefaultGLContext, x, y, r)

void glCtxDrawPolygon (GLContext *ctx, GLPoint *p, int n);
#define glDrawPolygon(p, n) glCtxDrawPolygon(DefaultGLContext, p, n)
void glCtxDrawFilledPolygon (GLContext *ctx, GLPoint *p, int n);
#define glDrawFilledPolygon(p, n) glCtxDrawFilledPolygon(DefaultGLContext, p, n)

void glCtxDrawArc (GLContext *ctx, int cx, int cy, int w, int h, int s, int e);
#define glDrawArc(cx, cy, w, h, s, e) glCtxDrawArc(DefaultGLContext, cx, cy, w, h, s, e)
void glCtxDrawFilledArc (GLContext *ctx, int cx, int cy, int w, int h, int s, int e, int style);
#define glDrawFilledArc(cx, cy, w, h, s, e, style) glCtxDrawFilledArc(DefaultGLContext, cx, cy, w, h, s, e, style)

void glCtxDrawEllipse(GLContext *ctx, int mx, int my, int w, int h);
#define glDrawEllipse(mx, my, w, h) glCtxDrawEllipse(DefaultGLContext, mx, my, w, h)
void glCtxDrawFilledEllipse(GLContext *ctx, int mx, int my, int w, int h);
#define glDrawFilledEllipse(mx, my, w, h) glCtxDrawFilledEllipse(DefaultGLContext, mx, my, w, h)

void glCtxDrawFilledTriangle(GLContext *ctx, int x1, int y1, int x2, int y2, int x3, int y3);
#define glDrawFilledTriangle(x1, y1, x2, y2, x3, y3) glCtxDrawFilledTriangle(DefaultGLContext, x1, y1, x2, y2, x3, y3)

void glFillRoundRectange(GLContext *ctx, int x, int y, int w, int h, int ew, int eh);

void glCtxDrawTriangle(GLContext *ctx, int x1, int y1, int x2, int y2, int x3, int y3);
#define glDrawTriangle(x1, y1, x2, y2, x3, y3) glCtxDrawTriangle(DefaultGLContext, x1, y1, x2, y2, x3, y3)

void glCtxDrawOptionalBitmap(GLContext *ctx, int x, int y,
                  int bit_offset_x, int bit_offset_y, int x2, int y2, unsigned char alpha, int w, int h, int depth, const void *bitmap);
#define glDrawOptionalBitmap(x, y, bit_offset_x, bit_offset_y, x2, y2, alpha, w, h, depth, bitmap) \
            glCtxDrawOptionalBitmap(DefaultGLContext, x, y, bit_offset_x, bit_offset_y, x2, y2, alpha, w, h, depth, bitmap)
void glCtxDrawBitmap(GLContext *ctx, int x, int y, int w, int h, int depth, const void *bitmap);
#define glDrawBitmap(x, y, w, h, depth, bitmap) glCtxDrawBitmap(DefaultGLContext, x, y, w, h, depth, bitmap)
void glCtxDrawAlphaBitmap(GLContext *ctx, int x, int y, unsigned char alpha, int w, int h, int depth, const void *bitmap);
#define glDrawAlphaBitmap(x, y, alpha, w, h, depth, bitmap) glCtxDrawAlphaBitmap(DefaultGLContext, x, y, alpha, w, h, depth, bitmap)


GLGradient *glAllocateGradient(GLGradient *g, int count);
void glDestroyGradient(GLGradient *g);
void glCtxDrawGradient(GLContext *ctx, int x, int y, int w, int h, int type, GLGradient *g);
#define glDrawGradient(x, y, w, h, type, g) glCtxDrawGradient(DefaultGLContext, x, y, w, h, type, g)


#ifndef __SYSTEM_FONT__
unsigned int glUCSStringMetrics(fte_info *fti, const wchar_t *str, ft_metrics *metr, int32_t max_width, int flags, int32_t max_leter_cnt);
unsigned int glDrawUCSString(GLContext *ctx, fte_info *fti, const wchar_t *str, int x1, int y1,
                        int x2, int y2, int align, uint8_t leter_step, int32_t max_leter_cnt);

unsigned int glUTF8StringMetrics(fte_info *fti, const char *str, ft_metrics *metr, int32_t max_width, int flags, int32_t max_leter_cnt);
unsigned int glUTF8DrawString(GLContext *ctx, fte_info *fti, const char *str, int x1, int y1,
                        int x2, int y2, int align, uint8_t leter_step, int32_t max_leter_cnt);
#else

unsigned int glUCSStringMetrics(int font, const wchar_t *str, uint32_t *height, uint32_t *top, int32_t max_leter_cnt);
unsigned int glDrawUCSString(GLContext *ctx, int font, const wchar_t *str, int x1, int y1,
                        int x2, int y2, int align, uint8_t leter_step, int32_t max_leter_cnt);

unsigned int glUTF8StringMetrics(int font, const char *str, uint32_t *height, uint32_t *top, int32_t max_leter_cnt);
unsigned int glUTF8DrawString(GLContext *ctx, int font, const char *str, int x1, int y1,
                        int x2, int y2, int align, uint8_t leter_step, int32_t max_leter_cnt);

#endif

unsigned int glCtxDrawString(GLContext *ctx, const char *str, int x1, int y1, int x2, int y2, int font, int flags, uint8_t leter_step, int32_t max_leter_cnt);
#define glDrawString(str, x1, y1, x2, y2, font, flags, leter_step, max_leter_cnt) \
            glCtxDrawString(DefaultGLContext, str, x1, y1, x2, y2, font, flags, leter_step, max_leter_cnt)
unsigned int glCtxDrawUString(GLContext *ctx, const wchar_t *str, int x1, int y1, int x2, int y2, int font, int flags, uint8_t leter_step, int32_t max_leter_cnt);
#define glDrawUString(str, x1, y1, x2, y2, font, flags, leter_step, max_leter_cnt) \
            glCtxDrawUString(DefaultGLContext, str, x1, y1, x2, y2, font, flags, leter_step, max_leter_cnt)


int glStringMetrics(int font, const char *str, ft_metrics *metr, int32_t max_width, int flags, int32_t max_leter_cnt);



int glQueueListCreate(GLQueueList *list);
int glQueueListDestroy(GLQueueList *list);
GLQueueListItem *glQueueListPush(GLQueueList *list, void *body, int body_size /* must be aligned by 4! */);
GLQueueListItem *glQueueListPushFront(GLQueueList *list, void *body, int body_size);

/* Warning: dont use that functions on big lists */
GLQueueListItem *glQueueListInsert(GLQueueList *list, void *body, int body_size, int at);
GLQueueListItem *glQueueListItem(GLQueueList *list, int at);

int glQueueListPop(GLQueueList *list, GLQueueListItem *item);
#define glQueueListItemBody(item, type) (type)(((char *)item) + sizeof(void*)*2)


#ifdef __cplusplus
}
#endif


#endif

