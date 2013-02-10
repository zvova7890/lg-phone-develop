

#ifndef __REDRAWMANAGER_H__
#define __REDRAWMANAGER_H__


#include "Rect.h"
#include <vector>
#include <list>



class PaintManagerInformer
{
public:
    virtual void paintManagerEvent() {

    }
};


class EventManager
{
public:

    EventManager();
    ~EventManager();

    inline void setPaintFunc(void (*func)(void *user), void *user) {
        paintFunc = func;
        _user_p = user;
    }

    inline void setPaintFunc(void (*func)()) {
        paintFunc = (decltype(paintFunc))func;
    }


    inline void setRefreshFunc(void (*func)(void *), void *user) {
        refreshFunc = func;
        _user_r = user;
    }

    inline void setRefreshFunc(void (*func)()) {
        refreshFunc = (decltype(paintFunc))func;
    }

    inline void blockRefresh() {
        block_refresh = 1;
    }

    inline void blockPaint() {
        block_paint = 1;
    }

    inline void unblockRefresh() {
        block_refresh = 0;
    }

    inline void unblockPaint() {
        block_paint = 0;
    }

    void updateAfterEvent() {
        need_upd = 1;
    }

    void resetUpdate() {
        need_upd = 0;
    }

    void paint();
    void refresh();
    void update();


    struct EventManagerAction {
        EventManagerAction(void (*c)(void *), void *u) {
            call = c;
            user = u;
        }

        void (*call)(void *);
        void *user;
    };


    void notifyAfterEvent(const EventManagerAction & e) {
        _elist.push_back(e);
    }

private:

    std::list<EventManagerAction> _elist;

    void *_user_p, *_user_r;
    void (*paintFunc)(void *);
    void (*refreshFunc)(void *);
    int need_upd;
    char block_refresh, block_paint;
};







#endif
