#ifndef UACTIVEAREA_H
#define UACTIVEAREA_H

#include <Rect.h>
#include <ActiveArea.h>
#include <TimedTrack.h>


class UActiveArea;


#define TOUCH_ACTION_LONG_PRESS    3


template <class T>
class UActiveAreaItem
{
public:

    UActiveAreaItem(const Rect &r, bool blockable = true) :
        __is_longpressed(false)
    {
        memset(item(), 0, sizeof(T));
        activeAreaItemCreate(activeAreaItem(), r.x(), r.y(), r.w(), r.h(), blockable);
        activeAreaItem()->user = this;

        auto touchEvent = [](struct _ActiveAreaItem *item, int action, int x, int y) {
            auto self = (UActiveAreaItem<T>*)item->user;

            if(action == TOUCH_ACTION_PRESS)
                self->__is_longpressed = false;

            else if(action == TOUCH_ACTION_LONG_PRESS)
                self->__is_longpressed = true;

            self->touchEvent(action, x, y);
        };

        auto paintEvent = [](struct _ActiveAreaItem *item) {
            auto self = (UActiveAreaItem<T>*)item->user;
            self->paintEvent();
        };

        activeAreaItem()->touchEvent = touchEvent;
        activeAreaItem()->paintEvent = paintEvent;
    }

    virtual ~UActiveAreaItem() {

    }


    inline ActiveAreaItem *activeAreaItem() {
        return (ActiveAreaItem*)&_item;
    }

    inline const ActiveAreaItem *constActiveAreaItem() const {
        return (ActiveAreaItem*)&_item;
    }

    inline T *item() {
        return &_item;
    }

    inline const T *constItem() const {
        return &_item;
    }

    inline Rect rect() {
        return Rect(constActiveAreaItem()->x, constActiveAreaItem()->y, constActiveAreaItem()->w, constActiveAreaItem()->h);
    }

    inline void move(int x , int y) {
        activeAreaItem()->x = x;
        activeAreaItem()->y = y;
    }


    inline void moveX(int x) {
        activeAreaItem()->x = x;
    }

    inline void moveY(int y) {
        activeAreaItem()->y = y;
    }

    inline void setWidth(int w) {
        activeAreaItem()->w = w;
    }

    inline void setHeight(int h) {
        activeAreaItem()->h = h;
    }

    virtual void paintEvent() {

    }

    virtual void touchEvent(int action, int x, int y) {
        ((void)action);
        ((void)x);
        ((void)y);
    }

    inline int lastTouchedX() const {
        return constActiveAreaItem()->touched_x;
    }

    inline int lastTouchedY() const {
        return constActiveAreaItem()->touched_y;
    }

    inline bool isTouched() const {
        return constActiveAreaItem()->is_touched;
    }

    inline bool isMoved() const {
        return constActiveAreaItem()->is_moved;
    }

    inline bool isHaveLongPress() const {
        return __is_longpressed;
    }

    inline int touchDiffX() const {
        return constActiveAreaItem()->cur_x - constActiveAreaItem()->touched_x;
    }

    inline int touchDiffY() const {
        return constActiveAreaItem()->cur_y - constActiveAreaItem()->touched_y;
    }

    inline void setFullScreenBlock(bool is) {
        activeAreaItem()->is_fullscreen_blocked = is;
    }

    inline void setFullScreenPaintBlock(bool is) {
        activeAreaItem()->is_fullscreen_paint_blocked = is;
    }

    inline bool isOffRectTouch() const {
        return constActiveAreaItem()->is_offscreen_touch;
    }

protected:
    bool __is_longpressed;
    T _item;
    //UActiveArea *_parent;
};




class UActiveArea
{
public:
    UActiveArea(const Rect &r, bool long_press_support = false);
    ~UActiveArea();

    inline virtual void paintEvent() {
        activeAreaPaintAction((ActiveArea*)&aarea);
    }

    virtual void touchEvent(int action, int x, int y);

    template <class Tm>
    inline void push(Tm *item) {
        activeAreaPushItem((ActiveArea*)&aarea, item->activeAreaItem());
    }

    template <class Tm>
    inline void pushFront(Tm *item) {
        activeAreaPushFrontItem((ActiveArea*)&aarea, item->activeAreaItem());
    }

    template <class Tm>
    inline void pop(Tm *item) {
        activeAreaPopItem((ActiveArea*)&aarea, item->activeAreaItem());
    }

    template <class Tm>
    inline void insert(Tm *item, int at) {
        activeAreaInsertItem((ActiveArea*)&aarea, item->activeAreaItem(), at);
    }

    inline GLQueueList *itemsQueue() {
        return activeAreaItemsQueue((ActiveArea*)&aarea);
    }

    inline ActiveAreaItem *queueItem(int at) {
        return activeAreaQueueItem((ActiveArea*)&aarea, at);
    }

    inline ActiveArea* area() {
        return (ActiveArea *)&aarea;
    }

    inline void move(int x, int y) {
        aarea.x = x;
        aarea.y = y;
    }

    inline Rect rect() {
        return Rect(aarea.x, aarea.y, aarea.w, aarea.h);
    }

    inline void setProntPaint(bool front) {
        aarea.is_front_paint = front;
    }

    inline void setProntTouch(bool front) {
        aarea.is_front_touch = front;
    }

protected:
    int __last_x,__last_y;
    TimedTrack __long_press;
    ActiveArea aarea;
    bool _long_press_enabled;
};






#endif // ACTIVEAREA_H
