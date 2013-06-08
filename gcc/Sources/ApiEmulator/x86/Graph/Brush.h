#ifndef BRUSH_H
#define BRUSH_H

#include <gl.h>
#include <Graph/Image.h>
#include <Graph/Rect.h>
#include <functional>


class Brush
{
public:
    typedef enum {
        OWN = -1,
        RECT = 0x01,
        FILLRECT = 0x02,
        IMAGE,
        GRADIENT
    }Type;

public:
    Brush();
    Brush(const Brush &b);
    Brush(GLColor color, bool fill = true);
    Brush(GLGradient *gradient);
    Brush(Image *image);
    Brush(const std::function<void(Brush &, const Rect &)> &f);
    ~Brush();

    Brush & operator=(const Brush &b);

    void paint(const Rect &r);
    void paint(const Rect &r, int round_x, int round_y);
    virtual void paintEvent(const Rect &r, int round_x = 0, int round_y = 0);

private:
    char  m_type;
    void *m_point;
};

#endif // BRUSH_H
