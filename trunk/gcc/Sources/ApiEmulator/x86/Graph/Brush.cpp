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
    m_type = 0;
    clear_n_set<int>(&m_point, 0);
}


Brush::Brush(const Brush &b)
{
    operator=(b);
}


Brush::Brush(GLColor color, bool fill)
{
    m_type = fill? Type::FILLRECT : Type::RECT;
    alloc_n_set(&m_point, color, 0);
}


Brush::Brush(GLGradient *gradient)
{
    m_type = Type::GRADIENT;
    alloc_n_set(&m_point, gradient, 0);
}


Brush::Brush(Image *image)
{
    m_type = Type::IMAGE;
    alloc_n_set(&m_point, image, 0);
}


Brush::Brush(const std::function<void(Brush &, const Rect &)> &f)
{
    m_type = Type::OWN;
    alloc_n_set(&m_point, f, 1);
}


Brush::~Brush()
{
    if(m_type == (char)OWN)
        clear_n_set<brush_func_t>(&m_point, 1);
}


Brush & Brush::operator =(const Brush &b)
{
    if(m_type == (char)OWN)
        clear_n_set<brush_func_t>(&m_point, 1);

    switch(b.m_type)
    {
        case (char)OWN:
            alloc_n_set(&m_point, *restore_pointer_unpack<brush_func_t>(&b.m_point), 1);
            break;

        case (char)IMAGE:
            alloc_n_set(&m_point, restore_pointer<Image*>(&b.m_point), 0);
            break;

        case (char)RECT:
            alloc_n_set(&m_point, restore_pointer<GLColor>(&b.m_point), 0);
            break;

        case (char)FILLRECT:
            alloc_n_set(&m_point, restore_pointer<GLColor>(&b.m_point), 0);
            break;

        case (char)GRADIENT:
            alloc_n_set(&m_point, restore_pointer<GLGradient*>(&b.m_point), 0);
            break;

        default:
            clear_n_set<int>(&m_point, 0);
            break;
    }

    m_type = b.m_type;

    return *this;
}


void Brush::paint(const Rect &r)
{
    paintEvent(r);
}


void Brush::paint(const Rect &r, int round_x, int round_y)
{
    paintEvent(r, round_x, round_y);
}


void Brush::paintEvent(const Rect &r, int round_x, int round_y)
{
    switch(m_type)
    {
        case (char)Type::FILLRECT:
            glSetPen(restore_pointer<GLColor>(&m_point));

            if(r.w() == 1) {
                glDrawVLine(r.y(), r.y2(), r.x());

            } else if(r.h() == 1) {
                glDrawHLine(r.x(), r.x2(), r.y());

            } else {
                if(round_x > 0 || round_y > 0)
                    glFillRoundedRect(r.x(), r.y(), r.w(), r.h(), round_x, round_y);
                else
                    glDrawFilledRectange(r.x(), r.y(), r.x2(), r.y2());
            }
            break;

        case (char)Type::RECT:
            glSetPen(restore_pointer<GLColor>(&m_point));

            if(round_x > 0 || round_y > 0)
                glDrawRoundedRect(r.x(), r.y(), r.w(), r.h(), round_x, round_y);
            else
                glDrawRectange(r.x(), r.y(), r.x2(), r.y2());
            break;

        case (char)Type::GRADIENT:
            printf("Brush::gradient is unimplemented\n");
            break;

        case (char)Type::IMAGE:
        {
            Image *_image = restore_pointer<Image*>(&m_point);
            int x = r.x(),
                y = r.y();

            int w = r.w(),
                h = r.h();

            int last_x = 0;
            int last_y = 0;

            if(_image->width() > r.w())
                last_x = (_image->width()-w)/2;

            if(_image->height() > r.h())
                last_y = (_image->height()-h)/2;

            glDrawOptionalBitmap(x-last_x, y-last_y, 0, 0, x+w+last_x, y+h+last_y, 0,
                                 _image->width(), _image->height(), _image->depth(), (void*)_image->constBitmap());
            break;
        }

        case (char)Type::OWN:
        {
            brush_func_t & p = *restore_pointer_unpack<brush_func_t>(&m_point);
            p(*this, r);
            break;
        }

        default:

            break;
    }
}
