#ifndef UBUTTON_H
#define UBUTTON_H


#include "EventManager.h"
#include "UActiveArea.h"
#include "signals/signal.h"
#include <string>



/* Simple button */


class UButton : public UActiveAreaItem<ActiveAreaItem>
{
public:
    UButton(UActiveArea *parent, const Rect & rc, const std::string &text, bool blockable = true);


    void paintEvent();
    void touchEvent(int action, int x, int y);

    typedef signal_slot::multi_signal <void(UButton *)> signal;
    static typename signal_slot::multi_signal <void(UButton *)> &_sig;


    signal & releasedSignal() {
        return m_released;
    }

    signal & pressedSignal() {
        return m_pressed;
    }


private:

    signal m_pressed, m_released;
    std::string m_text;
};



#endif // UBUTTON_H
