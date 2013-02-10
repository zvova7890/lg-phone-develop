#ifndef ACTIVELIST_H
#define ACTIVELIST_H

#include <UActiveArea.h>
#include <ScrollArea.h>
#include <EventManager.h>



class ActiveList;

class ActiveListItem : public UActiveAreaItem<ScrollAreaItem>
{
private:
    static void __paint(ScrollAreaItem *item) {
        auto self = (ActiveListItem*)item->user;
        self->paintEvent();
    }

    static void __touch(ScrollAreaItem *item, int action, int x, int y) {
        auto self = (ActiveListItem*)item->user;

        /* for setup variables, call but not invoke */
        activeAreaTouchItem((ActiveAreaItem*)item, action, x, y, 0);

        self->touchEvent(action, x, y);
    }

public:

    ActiveListItem(ActiveList *parent, int w, int h) :
        UActiveAreaItem<ScrollAreaItem>(Rect(0, 0, w, h), true),
        _parent(parent)
    {
#if 0
        auto paint = [](ScrollAreaItem *item) {
            auto self = (ActiveListItem*)item->user;
            self->paintEvent();
        };

        auto touch = [](ScrollAreaItem *item, int action, int x, int y) {
            auto self = (ActiveListItem*)item->user;

            /* for setup variables, call but not invoke */
            activeAreaTouchItem((ActiveAreaItem*)item, action, x, y, 0);

            self->touchEvent(action, x, y);
        };
#endif
        scrollAreaCreateItem(item(), (((UActiveAreaItem<ScrollArea>*)parent)->item()), __paint, __touch, this);
    }

    virtual ~ActiveListItem() {

    }


    inline ActiveList *parent() {
        return _parent;
    }

    inline int currentDisplayID() const {
        return constItem()->id;
    }


protected:
    ActiveList *_parent;
};


class ActiveList : public UActiveAreaItem<ScrollArea>
{
private:
    static ScrollAreaItem *__getItem(void *_area, int index) {
        auto *self = static_cast<ActiveList*>(static_cast<ScrollArea*>(_area)->user);
        return self->getListItem(index);
    }

    static void __needUpdate(void *user) {
        auto *self = (ActiveList*)user;
        self->event_mngr->updateAfterEvent();
    }


public:
    ActiveList(const Rect &r, EventManager *e) :
        UActiveAreaItem<ScrollArea>(r),
        _item_step(0),
        event_mngr(e)
    {
        scrollAreaCreate(area(), _item_step, this);
        area()->need_update_user = this;

        /*auto _getItem = [](void *_area, int index) {
            auto *self = static_cast<ActiveList*>(static_cast<ScrollArea*>(_area)->user);
            return self->getListItem(index);
        };

        auto _needUpdate = [](void *user) {
            auto *self = (ActiveList*)user;
            self->paint_mngr->updateAfterAction();
        };*/

        area()->getItem = __getItem;
        area()->needUpdate = __needUpdate;
    }

    virtual ~ActiveList() {
        printf("~ActiveList()\n");
        scrollAreaDestroy(area());
    }

    void paintEvent() {
        scrollAreaPaint(area());
    }


    void touchEvent(int action, int x, int y) {
        scrollAreaTouch(area(), action, x, y);
    }

    inline void pushBack(ActiveListItem *item) {
        _items.push_back(item);
    }

    inline std::vector <ActiveListItem*> *itemList() {
        return &_items;
    }

    inline int linesCount() {
        return area()->icount;
    }

    inline int displayingLines() {
        return area()->displaying_items;
    }

    inline void setLinesCount(int c) {
        area()->icount = c;
    }

    inline void resetViewListPosition() {
        scrollAreaResetScroll(area());
    }

    inline void fullResetViewList() {
        scrollAreaFullReset(area());
    }

    inline void stopScroll() {
        scrollAreaStopAutoScroll(area());
    }

    inline void fixScrollPosition() {
        scrollAreaCheckAndFixScrollPosition(area());
    }

    inline void setViewListScrollCoordinateY(int y) {
        area()->cy = y;
    }

    inline ScrollArea *area() {
        return (ScrollArea *)UActiveAreaItem<ScrollArea>::item();
    }

    inline int lineItem() {
        return area()->item;
    }

    inline int setLineItem(int item) {
        if(linesCount() <= item || item < 0)
            return -1;

        area()->item = item;
        return 0;
    }


protected:
    virtual ScrollAreaItem *getListItem(int index) {
        if(index < 0 || index >= (int)_items.size())
            return 0;

        return _items[index]->item();
    }


protected:
    int _item_step;
    std::vector <ActiveListItem*> _items;

public:
    EventManager *event_mngr;
};



#endif // ACTIVELIST_H
