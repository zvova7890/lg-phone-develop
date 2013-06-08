

#include <nucleus.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

extern int pthread_attr_setstack (pthread_attr_t *__attr, void *__stackaddr,
                  size_t __stacksize) __THROW __nonnull ((1));

extern int usleep (__useconds_t __useconds);



void *pthread_start_rountine(void *argv)
{
    NU_TASK *task = argv;

    task->task_entry(task->argc, task->argv);
    return 0;
}



STATUS NU_Create_Task(NU_TASK *task, CHAR *name,
                                    VOID (*task_entry)(UNSIGNED, VOID *), UNSIGNED argc,
                                    VOID *argv, VOID *stack_address, UNSIGNED stack_size,
                                    OPTION priority, UNSIGNED time_slice,
                                    OPTION preempt, OPTION auto_start)
{
    ((void)name);
    ((void)priority);
    ((void)time_slice);
    ((void)preempt);

    task->task_entry = task_entry;
    task->argc = argc;
    task->argv = argv;
    task->started = 0;
    task->task_ptr = task;


    pthread_attr_init(&task->attr);
    pthread_attr_setstack(&task->attr, stack_address, stack_size);

    if(auto_start) {
        // FIXME

        int c = pthread_create(&task->thread, &task->attr, pthread_start_rountine, (void*)task);
        if(!c)
            task->started = 1;
        else
            task->started = 2; // fail

        return c;
    }
    else
        return NU_SUCCESS;
}


STATUS NU_Delete_Task(NU_TASK *task)
{
    if(task->started == 1) {
        return NU_INVALID_DELETE;
    }

    memset(task, 0, sizeof(*task));
    return NU_SUCCESS;
}


STATUS NU_Reset_Task(NU_TASK *task, UNSIGNED argc, VOID *argv)
{
    ((void)task);
    ((void)argc);
    ((void)argv);


    printf("NU_Reset_Task is unimplemented!\n");
    return NU_INVALID_OPERATION;
}


STATUS NU_Terminate_Task(NU_TASK *task)
{
    int r = pthread_cancel(task->thread);
    r += pthread_join(task->thread, NULL);
    task->started = 0;

    return r;
}


STATUS NU_Resume_Task(NU_TASK *task)
{
    if(!task->started) {
        int c = pthread_create(&task->thread, &task->attr, pthread_start_rountine, task);
        if(!c)
            task->started = 1;
        else
            task->started = 2; // fail

        return c;
    }

    return NU_INVALID_START;
}


STATUS NU_Suspend_Task(NU_TASK *task)
{
    if(task->started != 1)
        return NU_INVALID_SUSPEND;

    /*pthread_mutex_lock(&task->suspend_mtx);

    do {
        pthread_cond_wait(&m_ResumeCond, &m_SuspendMutex);
    } while (suspended);

    pthread_mutex_unlock(&m_SuspendMutex);*/

    printf("NU_Suspend_Task is not implemented\n");
    return NU_INVALID_SUSPEND;
}


VOID NU_Sleep(UNSIGNED ticks)
{
    // FIXME
    usleep(ticks);
}


OPTION NU_Change_Priority(NU_TASK *task, OPTION new_priority)
{
    ((void)task);
    ((void)new_priority);

    printf("NU_Change_Priority is not implemented\n");
    return NU_INVALID_PRIORITY;
}


NU_TASK  *NU_Current_Task_Pointer(VOID)
{
    pthread_t self = pthread_self();

    return ((NU_TASK *)&self)->task_ptr;
}

