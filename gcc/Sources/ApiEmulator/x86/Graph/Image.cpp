
#include <Api/ApiLinkLib/ApiLink.h>
#include "Image.h"
#include <gl.h>

Image Image::null;


Image::Image()
{
    memset(&m_Image, 0, sizeof(m_Image));
}


Image::Image(image_t *img, bool ref)
{
    memcpy(&m_Image, img, sizeof(*img));

    if(!ref) {
        m_Image.bitmap = (unsigned char*)new unsigned char[img->w * img->h * (img->bit/8)];
    } else
        setRefed();
}


Image::Image(int w, int h, int depth) :
    Shared()
{
    m_Image.w = w;
    m_Image.h = h;
    m_Image.bit = depth;
    m_Image.bitmap = (unsigned char*)new unsigned char[w*h*(depth/8)];
}


Image::Image(int w, int h, int depth, const char *data, bool ref)
{
    m_Image.w = w;
    m_Image.h = h;
    m_Image.bit = depth;

    if(!ref) {
        m_Image.bitmap = (unsigned char*)new unsigned char[w*h*(depth/8)];
        memcpy(m_Image.bitmap, data, w*h*(depth/8));
    } else {
        m_Image.bitmap = (void *)data;
        setRefed();
    }
}


Image::Image(const char *file) :
    Shared()
{
    image_t *i = load_png(file, 0);
    if(!i) {
        memset(&m_Image, 0, sizeof(m_Image));
        return;
    }

    memcpy(&m_Image, i, sizeof(*i));
    delete i;
}


Image::Image(const Image &i, bool ref) :
    Shared()
{
    if(ref) {
        Shared::ref(&i);
    } else {
        memcpy(&m_Image, &i.m_Image, sizeof(i.m_Image));
        m_Image.bitmap = (unsigned char*)new unsigned char[m_Image.w * m_Image.h * (m_Image.bit/8)];
    }
}


Image::~Image()
{
    bool ref = Shared::isRefed();
    Shared::clear();

    if(!ref && m_Image.bitmap) {
        delete (char*)m_Image.bitmap;
        m_Image.bitmap = 0;
    }
}


void Image::atref(const Shared *r)
{
    Image *i = (Image*)r;

    memcpy(&m_Image, &i->m_Image, sizeof(i->m_Image));
}


void Image::atderef()
{
    void *bitmap = m_Image.bitmap;
    m_Image.bitmap = (unsigned char*)new unsigned char[m_Image.w * m_Image.h * (m_Image.bit/8)];
    memcpy(m_Image.bitmap, bitmap, m_Image.w * m_Image.h * (m_Image.bit/8));
}



void Image::clear()
{
    bool ref = Shared::isRefed();
    Shared::clear();

    if(!ref && m_Image.bitmap) {
        delete (char*)m_Image.bitmap;
        m_Image.bitmap = 0;
    }

    memset(&m_Image, 0, sizeof(m_Image));
}


unsigned char *Image::bitmap()
{
    deref();
    return (unsigned char *)m_Image.bitmap;
}


Image &Image::operator =(const Image &i)
{
    clear();
    ref(&i);
    return *this;
}


Image &Image::operator =(const Image *i)
{
    clear();
    ref(i);
    return *this;
}



Image Image::grabScreen(Rect r)
{
    if(!r.isZero()) {
        if(r.x() < 0)
            r.setX(0);

        if(r.y() < 0)
            r.setY(0);

        if(r.x2() > (int)GRSYS_WIDTH)
            r.setW(GRSYS_WIDTH-r.x());

        if(r.y2() > (int)GRSYS_HEIGHT)
            r.setH(GRSYS_HEIGHT-r.y());

    } else {
        r = Rect(0, 0, GRSYS_WIDTH, GRSYS_HEIGHT);
    }

    #define __pixelPoint16(buf, w, x, y) (((unsigned short*)buf)+(y*w+x))

    Image i(r.w(), r.h(), 16, (const char *)GrSys_GetGrBuf());

    memcpy(i.bitmap(), (const char*)GrSys_GetGrBuf(), r.w()*r.h()*2);
    return i;
}


Image Image::refScreen(Rect r)
{
    if(!r.isZero()) {
        if(r.x() < 0)
            r.setX(0);

        if(r.y() < 0)
            r.setY(0);

        if(r.x2() > (int)GRSYS_WIDTH)
            r.setW(GRSYS_WIDTH-r.x());

        if(r.y2() > (int)GRSYS_HEIGHT)
            r.setH(GRSYS_HEIGHT-r.y());

    } else {
        r = Rect(0, 0, GRSYS_WIDTH, GRSYS_HEIGHT);
    }


    Image i(r.w(), r.h(), 16, (const char*)GrSys_GetGrBuf(), true);
    return i;
}


Image &Image::scale(int newWidth, int newHeight, Image &newImage)
{
    unsigned short *nbitmap = (unsigned short *)newImage.bitmap();
    const unsigned short *bitmap = (const unsigned short *)constBitmap();

    int xfrom = 0;
    int yfrom = 0;

    for(int y = 0; y < newHeight; y++)
    {
        int dy = (y * height()) / newHeight;
        for(int x = 0; x < newWidth; x++)
        {
            int dx = (x * width()) / newWidth;
            int nx = x+xfrom;
            int ny = y+yfrom;

            //if(nx >= ctx->clip_x1 && nx < ctx->clip_x2 &&  ny >= ctx->clip_y1 && ny < ctx->clip_y2)
                //glPutPixel16c(ctx, nx, ny, *(bitmap + dy*w+dx));

            __glBufPixelPoint16(nbitmap, newImage.width(), nx, ny) = __glBufPixelPoint16(bitmap, width(), dx, dy);
        }
    }

    return newImage;
}


Image Image::scale(int newWidth, int newHeight)
{
    // FIXME
    Image newImage(newWidth, newHeight, 16);
    unsigned short *nbitmap = (unsigned short *)newImage.bitmap();
    const unsigned short *bitmap = (const unsigned short *)constBitmap();

    int xfrom = 0;
    int yfrom = 0;

    for(int y = 0; y < newHeight; y++)
    {
        int dy = (y * height()) / newHeight;
        for(int x = 0; x < newWidth; x++)
        {
            int dx = (x * width()) / newWidth;
            int nx = x+xfrom;
            int ny = y+yfrom;

            //if(nx >= ctx->clip_x1 && nx < ctx->clip_x2 &&  ny >= ctx->clip_y1 && ny < ctx->clip_y2)
                //glPutPixel16c(ctx, nx, ny, *(bitmap + dy*w+dx));

            __glBufPixelPoint16(nbitmap, newImage.width(), nx, ny) = __glBufPixelPoint16(bitmap, width(), dx, dy);
        }
    }

    return newImage;
}

