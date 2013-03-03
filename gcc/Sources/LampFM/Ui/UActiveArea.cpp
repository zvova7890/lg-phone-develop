#include "UActiveArea.h"



UActiveArea::UActiveArea(EventManager *event, const Rect &r, bool long_press_support) :
    m_longPressEnabled(long_press_support),
    m_eventMgr(event)
{
    activeAreaCreate((ActiveArea*)&m_aarea, r.x(), r.y(), r.w(), r.h());

    memset(&m_longPress, 0, sizeof(m_longPress));

    if(long_press_support)
        timedTrackCreate(&m_longPress, 0, 1, this);
}



UActiveArea::~UActiveArea()
{
    timedTrackDestroy(&m_longPress);
    activeAreaDestroy((ActiveArea*)&m_aarea);
}



void UActiveArea::touchEvent(int action, int x, int y)
{
    switch(action)
    {
        case TOUCH_ACTION_PRESS:
            __last_x = x;
            __last_y = y;

            if(m_longPressEnabled) {
                timedTrackSetActionOnBiggerThan(&m_longPress, [](TimedTrack *tt){
                    auto self = (UActiveArea*)tt->user;
                    timedTrackStopCount(&self->m_longPress);
                    activeAreaTouchAction((ActiveArea*)&self->m_aarea, TOUCH_ACTION_LONG_PRESS, self->__last_x, self->__last_y);

                }, 5, 1);

                timedTrackStopCount(&m_longPress);
                timedTrackReset(&m_longPress, 0);
                timedTrackStartCount(&m_longPress, 5);
            }
            break;

        case TOUCH_ACTION_MOVE:
        case TOUCH_ACTION_RELEASE:
            if(m_longPressEnabled)
                timedTrackStopCount(&m_longPress);
            break;
    }

    activeAreaTouchAction((ActiveArea*)&m_aarea, action, x, y);
}

