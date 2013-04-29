#ifndef VSCROLLAREA_H
#define VSCROLLAREA_H

#include <Widget.h>
#include <Timer.h>
#include <TimerCounter.h>
#include <vector>


class VScrollArea : public Widget, protected Timer
{
public:

    class ScrollState {
    public:
        ScrollState(int item = 0, int coord_tate = 0) {
            this->item = item;
            this->coord_tate = coord_tate;
        }

        ScrollState & operator =(const ScrollState &ss) {
            item = ss.item;
            coord_tate = ss.coord_tate;
            return *this;
        }

        int item;
        int coord_tate;
    };

    enum Direction {
        No = 0,
        Up = 1,
        Down
    };

    enum TimerWork {
        NoWork = 0,
        ScrollFading = 1,
        ScrollFixup
    };

public:
    VScrollArea(const Rect &, Widget *parent = 0);
    virtual ~VScrollArea();

    virtual void touchItemEvent(int item, int action, int x, int y);
    virtual int count() const;


    void fixupViewPosition();
    void breakScrolling();
    void resetViewPosition();
    void setViewCoord(int c);
    void setItem(int c);
    void setLinesCount(int c);
    bool isAutoScrollActive() const;

    void addItem(Widget *);
    void clear();

    int listHeightInRect();

    /* return a free space after last item */
    int leastFreePage();


    void setScrollState(const ScrollState &s) {
        m_item = s.item;
        m_coordPos = s.coord_tate;
    }

    ScrollState scrollState() const {
        return ScrollState(item(), m_coordPos);
    }

    const std::vector<Widget*> & items() const {
        return m_items;
    }

    inline int item() const {
        return m_item;
    }

    void setMoveDirection(VScrollArea::Direction d) {
        m_moveDirection = d;
    }

    int displayingItems() const {
        return m_displayingItems;
    }

    int itemCoord() const {
        return m_coordPos;
    }

    bool isHaveOffscreenItems() const {
        return m_haveOffscreenItems;
    }

    int viewPageHeight() const {
        return m_pageHeight;
    }

protected:

    virtual void paintEvent();
    virtual void touchEvent(int action, int x, int y);

    virtual Widget *widgetItem(int id);


    void init();
    bool moveUp(int steps);
    bool moveDown(int steps);
    void timerEvent();

    void startMove(int speed, int potencial, Direction d);


    Widget* takeItemByCoord(int x, int y);

    int checkItemSizes(Widget *) const;
    inline Widget *lastWidgetItem();


private:

    std::vector<Widget*> m_items;

    int m_linesCount;
    int m_item;
    int m_coordPos;
    int m_pageHeight;
    int m_displayingItems;
    bool m_haveOffscreenItems;
    Direction m_moveDirection;
    Point m_touchLastPos, m_lastPos;
    Widget *m_touched;


    TimerWork m_timerType;
    float m_timerSpeed, m_potencialOfHiding;
    int m_timerValue;
    Direction m_timerDirectionMove;

#ifdef __PC_BUILD__
    TimerCounter m_timerCounter;
#else
    unsigned long m_lastTime;
#endif

    int m_timeStampDiff;

    int m_yDiff;

    struct {
        Direction direction;
        int distance;
        int speed;
        int boost;

    }PosFixup;
};



#endif // VSCROLLAREA_H
