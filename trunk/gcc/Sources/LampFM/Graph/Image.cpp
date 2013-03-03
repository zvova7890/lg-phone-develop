#include "Image.h"

Image Image::null;


Image::Image() :
    m_Refed(false)
{
    memset(&m_Image, 0, sizeof(m_Image));
}


Image::Image(image_t *img, bool ref) :
    m_Refed(ref)
{
    memcpy(&m_Image, img, sizeof(*img));

    if(!m_Refed) {
        m_Image.bitmap = (unsigned char*)new unsigned char[img->w * img->h * (img->bit/8)];
    }

}


Image::Image(int w, int h, int depth) :
    m_Refed(false)
{
    m_Image.w = w;
    m_Image.h = h;
    m_Image.bit = depth;
    m_Image.bitmap = (unsigned char*)new unsigned char[w*h*(depth/8)];
}


Image::Image(const char *file) :
    m_Refed(false)
{
    image_t *i = load_png(file, 0);
    if(!i) {
        memset(&m_Image, 0, sizeof(m_Image));
        return;
    }

    memcpy(&m_Image, i, sizeof(*i));
    delete i;
}


Image::Image(const Image &i, bool ref)
{
    if(ref) {
        memcpy(&m_Image, &i.m_Image, sizeof(i.m_Image));
        m_Refed = true;
    } else {
        memcpy(&m_Image, &i.m_Image, sizeof(i.m_Image));
        m_Image.bitmap = (unsigned char*)new unsigned char[m_Image.w * m_Image.h * (m_Image.bit/8)];
        m_Refed = false;
    }
}


Image::~Image()
{
    if(!m_Refed && m_Image.bitmap) {
        delete (char*)m_Image.bitmap;
    }
}


Image &Image::operator =(const Image &i)
{
    memcpy(&m_Image, &i.m_Image, sizeof(i.m_Image));
    m_Refed = true;
    return *this;
}


Image &Image::operator =(const Image *i)
{
    memcpy(&m_Image, &i->m_Image, sizeof(i->m_Image));
    m_Refed = true;
    return *this;
}
