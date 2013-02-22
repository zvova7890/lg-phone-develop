#ifndef UACTIVEAREA_H
#define UACTIVEAREA_H

#include <Rect.h>
#include <ActiveArea.h>
#include <TimedTrack.h>
#include <sigc++/sigc++.h>


class UActiveArea;


#define TOUCH_ACTION_LONG_PRESS    3


template <class T>
class UActiveAreaItem
{
public:

    UActiveAreaItem(const Rect &r, bool blockable = true) :
        __is_longpressed(false),
        current_touch_state(TOUCH_ACTION_RELEASE)
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

            self->current_touch_state = action;
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

    virtual void parentHasDied() {
        /* main active area has died, free resource here */
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

    inline Rect rect() const {
        return Rect(constActiveAreaItem()->x, constActiveAreaItem()->y, constActiveAreaItem()->w, constActiveAreaItem()->h);
    }

    inline void setSize(const Rect & r) {
        activeAreaItem()->x = r.x();
        activeAreaItem()->y = r.y();
        activeAreaItem()->w = r.w();
        activeAreaItem()->h = r.h();
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
        __paint_event.emit(this);
    }

    virtual void touchEvent(int action, int x, int y) {
        ((void)action);
        ((void)x);
        ((void)y);

        __touch_event.emit(this, action, x, y);
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


    inline void setBlockable(bool is) {
        activeAreaItem()->is_blockable = is;
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

    inline int touchState() const {
        return current_touch_state;
    }

    template <class Tp>
    inline void connectPaintSignal(Tp slot_) {
        __paint_event.connect(slot_);
    }

    template <class Tp>
    inline void connectTouchSignal(Tp slot_) {
        __touch_event.connect(slot_);
    }

    inline void setUserData(void *u) {
        _user_data = u;
    }

    inline void *userData() {
        return _user_data;
    }

protected:
    bool __is_longpressed;
    T _item;

    void *_user_data;
    int current_touch_state;
    sigc::signal <void, UActiveAreaItem<T>* > __paint_event;
    sigc::signal <void, UActiveAreaItem<T>*, int, int, int > __touch_event;
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



    /* Item iteration */
    class iterator
    {
    private:

        iterator(UActiveArea *area, GLQueueListItem *item) {
            _area = area;
            _item = item;
        }

    public:
        iterator(UActiveArea *area, bool last = false) {
            _area = area;
            _item = last? _area->itemsQueue()->last : _area->itemsQueue()->first;
        }


        iterator(const iterator &i) {
            this->operator =( i );
        }

        iterator & operator = (const iterator & i) {
            _area = i._area;
            _item = i._item;
            return *this;
        }

        bool operator == (const iterator & i) const {
            if(_area == i._area &&
                _item == i._item )
                return true;

            return false;
        }

        bool operator != (const iterator & i) const {
            if(_area != i._area ||
                _item != i._item )
                return true;

            return false;
        }

        iterator & operator++() {
            if(_item)
                _item = (GLQueueListItem*)_item->next;

            return *this;
        }

        iterator operator++(int) {
            UActiveArea *_areal = _area;
            GLQueueListItem *_iteml = _item;

            if(_item)
                _item = (GLQueueListItem*)_item->next;

            return iterator(_areal, _iteml);
        }

        iterator & operator--() {
            if(_item && _item->prev)
                _item = (GLQueueListItem*)_item->prev;

            return *this;
        }

        iterator operator--(int) {
            UActiveArea *_areal = _area;
            GLQueueListItem *_iteml = _item;

            if(_item && _item->prev)
                _item = (GLQueueListItem*)_item->prev;

            return iterator(_areal, _iteml);
        }

        ActiveAreaItem * operator*() {
            return (*glQueueListItemBody(_item, ActiveAreaItem**));
        }


    private:
        UActiveArea *_area;
        GLQueueListItem *_item;
    };


    iterator begin() {
        return iterator(this);
    }

    iterator end() {
        iterator it(this, true);
        it++; // end
        return it;
    }

protected:
    int __last_x,__last_y;
    TimedTrack __long_press;
    ActiveArea aarea;
    bool _long_press_enabled;
};






#endif // ACTIVEAREA_H
