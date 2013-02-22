#include "Brush.h"



Brush::Brush()
{
    _type = Type::OWN;
}


Brush::Brush(const Brush &b)
{
    operator=(b);
}


Brush::Brush(GLColor color)
{
    _type = Type::COLOR;
    _color = color;
}


Brush::Brush(GLGradient *gradient)
{
    _type = Type::GRADIENT;
    _gradient = gradient;
}


Brush::Brush(image_t *image)
{
    _type = Type::IMAGE;
    _image = image;
}


Brush::Brush(const std::function<void(Brush &)> &f)
{
    _type = Type::IMAGE;
    _paint_event = f;
}


void Brush::paint(const Rect &r)
{
    paintEvent(r);
}


void Brush::paintEvent(const Rect &r)
{
    switch(_type)
    {
        case Type::COLOR:
            glSetPen(_color);
            glDrawFilledRectange(r.x(), r.y(), r.x2(), r.y2());
            break;

        case Type::GRADIENT:
            printf("Brush::gradient is unimplemented\n");
            break;

        case Type::IMAGE:
        {
            int x = r.x(),
                y = r.y();

            int w = r.w(),
                h = r.h();

            int last_x = 0;
            int last_y = 0;

            if(_image->w > r.w())
                last_x = (_image->w-w)/2;

            if(_image->h > r.h())
                last_y = (_image->h-h)/2;

            glDrawOptionalBitmap(x-last_x, y-last_y, 0, 0, x+w+last_x, y+h+last_y, 0, _image->w, _image->h, _image->bit, _image->bitmap);
            break;
        }

        default: case Type::OWN:
            _paint_event(*this);
            break;
    }
}
