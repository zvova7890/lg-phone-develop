

#include "EventManager.h"


static EventManager *gself = 0;


EventManager::EventManager() :
    block_refresh(0),
    block_paint(0)
{
    refreshFunc = m_paintFunc = [](void *lol) { ((void)lol); };
}


EventManager::~EventManager()
{

}


void EventManager::paint()
{
    m_paintFunc(_user_p);
}


void EventManager::refresh()
{
    refreshFunc(_user_r);
}


void EventManager::update()
{
    if(need_upd) {
        need_upd = 0;

        m_listeners.trigger();
        m_listeners.clear();

        if(!block_paint)
            paint();

        if(!block_refresh)
            refresh();
    }
}


void EventManager::setGlobalInstance(EventManager *s)
{
    gself = s;
}


EventManager *EventManager::self()
{
    return gself;
}





