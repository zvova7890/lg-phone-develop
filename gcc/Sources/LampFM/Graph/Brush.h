#ifndef BRUSH_H
#define BRUSH_H

#include <gl.h>
#include <Graph/Image.h>
#include <Graph/Rect.h>
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
    Brush(Image *image);
    Brush(const std::function<void(Brush &, const Rect &)> &f);
    ~Brush();

    Brush & operator=(const Brush &b);

    void paint(const Rect &r);
    virtual void paintEvent(const Rect &r);

private:
    char  _type;
    void *_point;
};

#endif // BRUSH_H
