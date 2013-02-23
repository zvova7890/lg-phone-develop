#ifndef BRUSH_H
#define BRUSH_H

#include <gl.h>
#include <png_ops.h>
#include <Rect.h>
#include <functional>


typedef struct
{
    GLColor *colors;
    int count;
}GLGradient;



class Brush
{
public:
    typedef enum {
        OWN = -1,
        COLOR = 0x01,
        IMAGE,
        GRADIENT
    }Type;

public:
    Brush();
    Brush(const Brush &b);
    Brush(GLColor color);
    Brush(GLGradient *gradient);
    Brush(image_t *image);
    Brush(const std::function<void(Brush &, const Rect &)> &f);


    Brush & operator=(const Brush &b) {
        _type = b._type;
        _color = b._color;
        _gradient = b._gradient;
        _image = b._image;
        _paint_event = b._paint_event;
        return *this;
    }

    void paint(const Rect &r);

    virtual void paintEvent(const Rect &r);

private:
    Type _type;

    GLColor _color;
    GLGradient *_gradient;
    image_t *_image;
    std::function<void(Brush &, const Rect &)> _paint_event;
};

#endif // BRUSH_H
