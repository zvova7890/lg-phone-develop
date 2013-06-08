#ifndef POINT_H
#define POINT_H



class Point
{
public:

    Point(int x = 0, int y = 0) :
        m_x(x),
        m_y(y)
    {}


    int x() const {
        return m_x;
    }


    int y() const {
        return m_y;
    }


    Point & setX(int x) {
        m_x = x;
        return *this;
    }

    Point & setY(int y) {
        m_y = y;
        return *this;
    }

private:
    int m_x, m_y;
};





#endif // POINT_H
