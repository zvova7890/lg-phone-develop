#ifndef IMAGE_H
#define IMAGE_H

#include <Core/Rect.h>
#include <png_ops.h>
#include <Core/Shared.h>


/*
 * Operator = is refering image by default, if you need to copy it
 * use newImage = Image(image, false)
*/


class Image : Shared
{
public:

    Image();
    Image(const Image &i, bool atref = true);
    Image(image_t *img, bool atref = true);
    Image(int w, int h, int depth);
    Image(int w, int h, int depth, const char *data, bool atref = false);
    Image(const char *file);
    ~Image();

    Image &operator =(const Image &);
    Image &operator =(const Image *);
    void clear();

    Image scale(int w, int h);
    Image &scale(int w, int h, Image &);

    static Image grabScreen(Rect r = Rect());
    static Image refScreen(Rect r = Rect());

    unsigned char *bitmap();
    unsigned char *constBitmap() const {
        return (unsigned char*)m_Image.bitmap;
    }

    int depth() const {
        return m_Image.bit;
    }

    int width() const {
        return m_Image.w;
    }

    int height() const {
        return m_Image.h;
    }

    inline bool isEmpty() const {
        return m_Image.bitmap == 0;
    }


protected:
    void atref(const Shared *);
    void atderef();

private:
    image_t m_Image;

public:
    static Image null;
};



static inline void drawImage(int x, int y, Image *image) {
    if(image && !image->isEmpty())
        glDrawBitmap(x, y, image->width(), image->height(), image->depth(), (void*)image->constBitmap());
}

static inline void drawImage(int x, int y, const Image *image) {
    if(image && !image->isEmpty())
        glDrawBitmap(x, y, image->width(), image->height(), image->depth(), (void*)image->constBitmap());
}


#endif // IMAGE_H
