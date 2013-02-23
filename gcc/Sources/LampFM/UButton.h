#ifndef UBUTTON_H
#define UBUTTON_H


#include <EventManager.h>
#include <UActiveArea.h>
#include <string>
#include "signals/signal.h"



/* Simple button */


class UButton : public UActiveAreaItem<ActiveAreaItem>
{
public:
    UButton(EventManager *e, const Rect & rc, bool blockable = true) :
        UActiveAreaItem<ActiveAreaItem>(rc, blockable),
        event_mngr(e)
    {
    }


    void paintEvent() {
        //glDrawEllipse()

        if(isTouched())
            glSetPen(0x6FFF0010);
        else
            glSetPen(0x6F9FFF9F);

       /* glSaveClipRegion();
        glSetClipRegion(rect().x(), rect().y(), rect().x2(), rect().y2());


        int s = (rect().h() + rect().w())/2;
        glDrawFilledEllipse(rect().x()+rect().w()/2, rect().y()+rect().h()/2, rect().w() + s/2 - 20, rect().h()+s/2 - 20);
        glRestoreClipRegion();*/

        glDrawFilledRectange(rect().x(), rect().y(), rect().x2(), rect().y2());

        glSetPen(0x9FF01F00);
        glDrawString(_name.c_str(), rect().x(), rect().y(), rect().x2(), rect().y2(), 20, FT_TEXT_H_CENTER | FT_TEXT_W_CENTER, 0, 128);
    }

    void touchEvent(int action, int x, int y) {
        ((void)x);
        ((void)y);

        if(!isMoved()) {
            if(action == TOUCH_ACTION_RELEASE) {
                _released.trigger(this);
            } else if(action == TOUCH_ACTION_PRESS) {
                _pressed.trigger(this);
            }
        }

        event_mngr->updateAfterEvent();
    }


    typedef signal_slot::multi_signal <void(UButton *)> signal;
    static typename signal_slot::multi_signal <void(UButton *)> &_sig;


    auto releasedSignal() -> decltype(_sig) {
        return _released;
    }

    auto pressedSignal() -> decltype(_sig) {
        return _pressed;
    }


private:

    signal _pressed, _released;
    std::string _name;
    EventManager *event_mngr;
};



#endif // UBUTTON_H
