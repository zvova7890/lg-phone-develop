#include "Brush.h"


typedef std::function<void(Brush &, const Rect &)> brush_func_t;


template <typename T>
void alloc_n_set(void *obj, T s, int pack)
{
    if(!pack) {
        *(T*)obj = s;

    } else {
        T *i = new T(s);
        *(T**)obj = i;
    }
}

template <typename T>
void clear_n_set(void *obj, int packed)
{
    if(!packed) {
        *(void**)obj = 0;
    } else {
        T *t = *(T**)obj;
        delete t;
        *(void**)obj = 0;
    }
}

template <typename T>
T restore_pointer(void *obj)
{
    return *(T*)obj;
}


template <typename T>
T restore_pointer(void * const * obj)
{
    return *(T*)obj;
}


template <typename T>
T *restore_pointer_unpack(void *obj)
{
    T *t = *(T**)obj;
    return t;
}


template <typename T>
T *restore_pointer_unpack(void * const * obj)
{
    T *t = *(T**)obj;
    return t;
}


Brush::Brush()
{
    _type = 0;
    clear_n_set<int>(&_point, 0);
}


Brush::Brush(const Brush &b)
{
    operator=(b);
}


Brush::Brush(GLColor color)
{
    _type = Type::COLOR;
    alloc_n_set(&_point, color, 0);
}


Brush::Brush(GLGradient *gradient)
{
    _type = Type::GRADIENT;
    alloc_n_set(&_point, gradient, 0);
}


Brush::Brush(image_t *image)
{
    _type = Type::IMAGE;
    alloc_n_set(&_point, image, 0);
}


Brush::Brush(const std::function<void(Brush &, const Rect &)> &f)
{
    _type = Type::OWN;
    alloc_n_set(&_point, f, 1);
}


Brush::~Brush()
{
    if(_type == (char)OWN)
        clear_n_set<brush_func_t>(&_point, 1);
}


Brush & Brush::operator =(const Brush &b)
{
    if(_type == (char)OWN)
        clear_n_set<brush_func_t>(&_point, 1);

    switch(b._type)
    {
        case (char)OWN:
            alloc_n_set(&_point, *restore_pointer_unpack<brush_func_t>(&b._point), 1);
            break;

        case (char)IMAGE:
            alloc_n_set(&_point, restore_pointer<image_t*>(&b._point), 0);
            break;

        case (char)COLOR:
            alloc_n_set(&_point, restore_pointer<GLColor>(&b._point), 0);
            break;

        case (char)GRADIENT:
            alloc_n_set(&_point, restore_pointer<GLGradient*>(&b._point), 0);
            break;

        default:
            clear_n_set<int>(&_point, 0);
            break;
    }

    _type = b._type;

    return *this;
}


void Brush::paint(const Rect &r)
{
    paintEvent(r);
}


void Brush::paintEvent(const Rect &r)
{
    switch(_type)
    {
        case (char)Type::COLOR:
            glSetPen(restore_pointer<GLColor>(&_point));
            if(r.w() == 1) {
                glDrawVLine(r.y(), r.y2(), r.x());

            } else if(r.h() == 1) {
                glDrawHLine(r.x(), r.x2(), r.y());

            } else
                glDrawFilledRectange(r.x(), r.y(), r.x2(), r.y2());

            break;

        case (char)Type::GRADIENT:
            printf("Brush::gradient is unimplemented\n");
            break;

        case (char)Type::IMAGE:
        {
            image_t *_image = restore_pointer<image_t*>(&_point);
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

        case (char)Type::OWN:
        {
            brush_func_t & p = *restore_pointer_unpack<brush_func_t>(&_point);
            p(*this, r);
            break;
        }

        default:

            break;
    }
}
