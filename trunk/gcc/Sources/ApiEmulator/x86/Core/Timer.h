#ifndef __TIMER_H__
#define __TIMER_H__


#include <signals/signal.h>
#include <Widget/EventManager.h>


typedef struct
{
    int id;
    void *user;
    int period;
    char type, active;
    unsigned int magic, magic_id;
    void (*event)(void *timer, void *user);
}TimerWrap;




class Timer
{
public:
    typedef signal_slot::multi_signal <Timer *> signal;

    Timer();
    virtual ~Timer();

    void start(int period);
    void stop();
    void pause();
    void resume();
    void resetPeriod(int p);
    int period() const;


    /* на уже рабочем таймере */
    void changePeriod(int period);

    virtual void timerEvent();

    inline signal & timerEventSignal() {
        return _timer_event;
    }

    inline void setUserData(void *u) {
        m_userData = u;
    }

    void *userData() {
        return m_userData;
    }

    bool isActive() const {
        return _active && _created;
    }


public:
    template<typename Connection>
    static void oneShoot(EventManager *m,  int p, Connection s ) {
        auto t = new Timer();

        auto sig = new signal_slot::multi_signal<>();
        sig->connect(s);
        t->setUserData(sig);

        t->timerEventSignal().connect([m](Timer *t) {

            auto sig = (signal_slot::multi_signal<> *)t->userData();
            sig->trigger();

            t->stop();
            m->notifyAfterEvent( [sig, t]() {
                delete sig;
                delete t;
            });
        });

        t->start(p);
    }

protected:
    static void timer_event(TimerWrap *tw, void *user);

private:
    bool _active, _created;
    TimerWrap _timer;
    signal _timer_event;

    void *m_userData;
};

#endif // __TIMER_H__
