
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Thread.h"




Thread::Thread(void *stack, int stack_size) :
    started(false)
{
    this->stack = stack;
    this->stack_size = stack_size;
    memset(&task, 0, sizeof task);

    if(!stack) {
        own_stack = true;
        this->stack_size = 0x4000;
        this->stack = malloc(this->stack_size);
    } else {
        own_stack = false;
    }
}


Thread::~Thread()
{
    if(started)
        stop();

    if(own_stack) {
        free(this->stack);
        this->stack_size = 0;
        own_stack = false;
    }
}


bool Thread::start(int prio)
{
    if(started) {
        printf("Thread is allready running\n");
        return false;
    }

    auto entry = [](unsigned long argc, void *argv) {
        ((void)argc);

        Thread *self = (Thread *)argv;
        self->run();
    };

    int err = NU_Create_Task(&task, (CHAR*)"task", entry, 1, this, stack, stack_size, prio, 0, NU_PREEMPT, NU_START);
    if(err == NU_SUCCESS)
        started = true;

    return err == NU_SUCCESS;
}


bool Thread::stop()
{
    int r = NU_Terminate_Task(&task);
    r += NU_Delete_Task(&task);

    started = false;
    return r == NU_SUCCESS;
}


bool Thread::suspend()
{
    return NU_Suspend_Task(&task) == NU_SUCCESS;
}


bool Thread::resume()
{
    return NU_Resume_Task(&task) == NU_SUCCESS;
}


void Thread::run()
{
    _on_run.trigger(this);
}


void Thread::sleep(int tick)
{
    NU_Sleep(tick);
}
