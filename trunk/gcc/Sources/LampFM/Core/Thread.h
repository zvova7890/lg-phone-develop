#ifndef THREAD_H
#define THREAD_H

#include <nucleus.h>
#include <signals/signal.h>


class Thread
{
public:
    Thread(void *stack = 0, int stack_size = 0);
    virtual ~Thread();

    bool start(int prio = 100);
    bool stop();

    bool suspend();
    bool resume();

    virtual void run();

    signal_slot::signal <Thread *> & onRunSignal() {
        return _on_run;
    }


    void setUserData(void *u) {
        _user = u;
    }

    void *userData() {
        return _user;
    }

private:
    bool started;
    bool own_stack;
    void *stack;
    int stack_size;
    NU_TASK task;

    void *_user;
    signal_slot::signal <Thread *> _on_run;
};

#endif // THREAD_H
