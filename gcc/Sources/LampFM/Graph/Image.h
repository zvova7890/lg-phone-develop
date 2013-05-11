#ifndef IMAGE_H
#define IMAGE_H

#include <png_ops.h>


/*
 * Operator = is refering image by default, if you need to copy it
 * use newImage = Image(image, false)
*/


class Image
{
public:

    Image();
    Image(const Image &i, bool ref = true);
    Image(image_t *img, bool ref = true);
    Image(int w, int h, int depth);
    Image(int w, int h, int depth, const char *data, bool ref = false);
    Image(const char *file);
    ~Image();

    Image &operator =(const Image &);
    Image &operator =(const Image *);
    void clear();

    unsigned char *bitmap() {
        return (unsigned char*)m_Image.bitmap;
    }

    const unsigned char *constBitmap() const {
        return (const unsigned char*)m_Image.bitmap;
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



private:
    image_t m_Image;
    bool m_Refed;

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
