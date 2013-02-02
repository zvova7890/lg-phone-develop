
#include <mem.h>


typedef struct
{
    void (*func)(void*);
    void *object;
    void *next;
}__cxa_atexit_struct;


extern "C"
void __cxa_exec_dtors(__cxa_atexit_struct *__ex_start, void *__ex)
{
    __cxa_atexit_struct *save = 0;

    while(__ex_start)
    {
        __ex_start->func(__ex_start->object);
        save = (__cxa_atexit_struct *)__ex_start->next;
        mem_free(__ex_start);
        __ex_start = save;
    }
}



int __hcxa_atexit(void (*func)(void*), void *arg, void *__dsohandle __attribute__((unused)),
                  __cxa_atexit_struct **__s_exit, __cxa_atexit_struct **__ex_start)
{
    __cxa_atexit_struct *cur;
    if(!*__s_exit)
    {
        *__s_exit = (__cxa_atexit_struct*)malloc(sizeof(__cxa_atexit_struct));
        cur = *__s_exit;
        *__ex_start = *__s_exit;
    }else
    {
        (*__s_exit)->next = (__cxa_atexit_struct*)malloc(sizeof(__cxa_atexit_struct));
        cur = (__cxa_atexit_struct*)(*__s_exit)->next;
    }


    cur->func = func;
    cur->object = arg;
    cur->next = 0;
    *__s_exit = cur;
    return 0;
}

