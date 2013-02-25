

#ifndef __RECT_H__
#define __RECT_H__



class Rect
{
public:

    Rect() {
        _x = 0;
        _y = 0;
        _w = 0;
        _h = 0;
    }

    Rect(int x, int y, int w, int h) {
        _x = x;
        _y = y;
        _w = w;
        _h = h;
    }

    Rect(const Rect &r) {
        _x = r.x();
        _y = r.y();
        _w = r.w();
        _h = r.h();
    }

    inline void setX(int c) {
        _x = c;
    }

    inline void setY(int c) {
        _y = c;
    }

    inline void setW(int c) {
        _w = c;
    }

    inline void setH(int c) {
        _h = c;
    }

    inline int x() const {
        return _x;
    }

    inline int y() const {
        return _y;
    }

    inline int w() const {
        return _w;
    }

    inline int h() const {
        return _h;
    }

    inline int x2() const {
        return _x+_w;
    }

    inline int y2() const {
        return _y+_h;
    }

private:
    int _x, _y, _w, _h;
};








#endif
