#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <Core/Application.h>
#include <Core/Timer.h>
#include <Widget/Widget.h>
#include <functional>
#include <vector>


class MainWindow : public Widget
{

    inline void set_attr(int a) {
        if(!(m_flags & a))
            m_flags |= a;
    }

    inline void erase_attr(int a) {
        if(m_flags & a)
            m_flags &= ~a;
    }

    inline bool test_attr(int a) const {
        return m_flags & a;
    }

public:

    enum {
        KEY_UP = 1,
        KEY_DOWN,
        KEY_REPEAT,
        KEY_LONG_PRESS
    };


    enum Flags {
        CONTROL_GDI_STATE = (1 << 1),
        TRANSLATE_COORDS_WITH_GDI_STATE = (1 << 2),
        TOUCHPAD_ADAPTIVE_SENSITIVITY = (1 << 3)
    };

public:
    MainWindow(int id, const Rect &r, EventManager *e);
    virtual ~MainWindow();

    virtual void initEvent();
    virtual void releaseEvent();
    virtual void keyEvent(int type, int key);
    virtual void suspendEvent();
    virtual void resumeEvent();
    virtual bool eventFilter(unsigned long, unsigned long, unsigned long);
    virtual void applicationEvent(unsigned long, unsigned long, unsigned long);

    void setTouchpadSensitivity(int v);


    void setFlags( int flags ) {
        m_flags = flags;
    }

    int flags() const {
        return m_flags;
    }

protected:
    static int event_listener(unsigned long, unsigned long, unsigned long);

private:

    char m_orientationType, lastOrientation;
    int m_id;
    Timer m_fixTmr;
    int m_flags;
    char m_touchpadSensitivity;
    int m_settingsHandler;


#if 0
    Application *m_app;

    class MTimer {
    public:
        MTimer() {

        }

        /*MTimer(H_TIMERCORE t, const std::function<void(H_TIMERCORE)> &c) {
            tmr = t;
            cb = c;
        }*/

        std::function<void(void *)> cb;

        struct LOL_TIMER : public LGOS_TIMER {
            MTimer *mtmr;
        };

        LOL_TIMER tmr;
        MainWindow *my_window;
        int id;
        void *user;
    };

    std::vector< MTimer > m_timerCb;
#endif
};

#endif // MAINWINDOW_H
