#include "UActiveArea.h"



UActiveArea::UActiveArea(const Rect &r, bool long_press_support) :
    _long_press_enabled(long_press_support)
{
    activeAreaCreate((ActiveArea*)&aarea, r.x(), r.y(), r.w(), r.h());

    memset(&__long_press, 0, sizeof(__long_press));

    if(long_press_support)
        timedTrackCreate(&__long_press, 0, 1, this);
}



UActiveArea::~UActiveArea()
{
    timedTrackDestroy(&__long_press);
    activeAreaDestroy((ActiveArea*)&aarea);
}



void UActiveArea::touchEvent(int action, int x, int y)
{
    switch(action)
    {
        case TOUCH_ACTION_PRESS:
            __last_x = x;
            __last_y = y;

            if(_long_press_enabled) {
                timedTrackSetActionOnBiggerThan(&__long_press, [](TimedTrack *tt){
                    auto self = (UActiveArea*)tt->user;
                    timedTrackStopCount(&self->__long_press);
                    activeAreaTouchAction((ActiveArea*)&self->aarea, TOUCH_ACTION_LONG_PRESS, self->__last_x, self->__last_y);

                }, 5, 1);

                timedTrackStopCount(&__long_press);
                timedTrackReset(&__long_press, 0);
                timedTrackStartCount(&__long_press, 5);
            }
            break;

        case TOUCH_ACTION_MOVE:
        case TOUCH_ACTION_RELEASE:
            if(_long_press_enabled)
                timedTrackStopCount(&__long_press);
            break;
    }

    activeAreaTouchAction((ActiveArea*)&aarea, action, x, y);
}

