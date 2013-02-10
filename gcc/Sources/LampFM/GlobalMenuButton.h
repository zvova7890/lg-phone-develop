#ifndef GLOBALMENUBUTTON_H
#define GLOBALMENUBUTTON_H

#include "UButton.h"
#include "png_ops.h"
#include <TimerWrap.h>



class GlobalMenuButton : public UButton
{
public:
    GlobalMenuButton(EventManager *e, const Rect &r);
    void paintEvent();
    void touchEvent(int action, int x, int y);
    void timerEvent();


    template <class T>
    inline void connectTouchAction(T slot_) {
        _move.connect(slot_);
    }

private:
    sigc::signal <void, GlobalMenuButton *, int, int, int> _move;
    image_t background;
};

#endif // GLOBALMENUBUTTON_H
