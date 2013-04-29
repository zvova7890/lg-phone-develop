

#ifndef __REDRAWMANAGER_H__
#define __REDRAWMANAGER_H__



#include <functional>
#include <signals/signal.h>
#include <vector>
#include <list>



class EventManager
{
public:

    EventManager();
    ~EventManager();

    inline void setPaintFunc(std::function<void(void *)> func, void *user) {
        paintFunc = func;
        _user_p = user;
    }

    inline void setPaintFunc(std::function<void(void *)> func) {
        paintFunc = func;
    }


    inline void setRefreshFunc(std::function<void(void *)> func, void *user) {
        refreshFunc = func;
        _user_r = user;
    }

    inline void setRefreshFunc(std::function<void(void *)> func) {
        refreshFunc = func;
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

    template <typename T>
    void notifyAfterEvent(T t) {
        //_elist.push_back(e);
        m_listeners.connect(t);
    }

    static void setGlobalInstance(EventManager *s);
    static EventManager *self();

private:

    signal_slot::multi_signal<> m_listeners;
    //std::list<EventManagerAction> _elist;

    void *_user_p, *_user_r;
    std::function<void(void *)> paintFunc;
    std::function<void(void *)> refreshFunc;
    int need_upd;
    char block_refresh, block_paint;
    EventManager *m_self;
};







#endif
