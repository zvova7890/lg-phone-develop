

#ifndef __RECT_H__
#define __RECT_H__

#include <Point.h>


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


    Rect(const Point &xy, const Point &wh) {
        _x = xy.x();
        _y = xy.y();
        _w = wh.x();
        _h = wh.y();
    }

    Rect(const Rect &r) {
        operator =(r);
    }


    /*Rect & operator =(const Rect &r) {
        _x = r._x;
        _y = r._y;
        _w = r._w;
        _h = r._h;
        return *this;
    }*/


    Rect & operator -(const Rect &r) {
        _x -= r.x();
        _y -= r.y();
        _w -= r.w();
        _h -= r.h();
        return *this;
    }

    Rect & operator -(const Point &p) {
        _x -= p.x();
        _y -= p.y();
        return *this;
    }

    Rect & operator +(const Rect &r) {
        _x += r.x();
        _y += r.y();
        _w += r.w();
        _h += r.h();
        return *this;
    }

    Rect & operator +(const Point &p) {
        _x += p.x();
        _y += p.y();
        return *this;
    }

    inline Rect & setX(int c) {
        _x = c;
        return *this;
    }

    inline Rect & setY(int c) {
        _y = c;
        return *this;
    }

    inline Rect & setXY(const Point &p) {
        _x = p.x();
        _y = p.y();
        return *this;
    }

    inline Rect & setW(int c) {
        _w = c;
        return *this;
    }

    inline Rect & setH(int c) {
        _h = c;
        return *this;
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

    Point wh() const {
        return Point(_w, _h);
    }

    Point xy() const {
        return Point(_x, _y);
    }

private:
    int _x, _y, _w, _h;
};








#endif
