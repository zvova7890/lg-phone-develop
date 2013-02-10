

#include <Api/ApiLinkLib/ApiLink.h>
#include "EventManager.h"



EventManager::EventManager() :
    block_refresh(0),
    block_paint(0)
{
    refreshFunc = paintFunc = [](void *lol) { ((void)lol); };
}


EventManager::~EventManager()
{
    printf("EventManager::~EventManager()\n");
}


void EventManager::paint()
{
    paintFunc(_user_p);
}


void EventManager::refresh()
{
    refreshFunc(_user_r);
}


void EventManager::update()
{
    if(need_upd) {
        need_upd = 0;

        if(!block_paint)
            paint();

        if(!block_refresh)
            refresh();
    }

    for(EventManagerAction & e : _elist)
    {
        e.call(e.user);
    }

    _elist.clear();
}
