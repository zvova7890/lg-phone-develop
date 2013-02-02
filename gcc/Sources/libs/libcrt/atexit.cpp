
//#include <stdio.h>


typedef struct
{
    void (*func)(void*);
    void *object;
    void *next;
}__cxa_atexit_struct;

__cxa_atexit_struct *__s_exit = 0, *__ex_start = 0;
void *__dso_handle = 0;



extern "C" void __cxa_exec_dtors(__cxa_atexit_struct *__ex_start, void *__ex);

extern int __hcxa_atexit(void (*func)(void*), void *arg, void *__dsohandle,
                  __cxa_atexit_struct **__s_exit, __cxa_atexit_struct **__ex_start);


extern "C"
void __destroy_dtors_list(void *ex)
{
    __cxa_exec_dtors(__ex_start, ex);
}

extern "C"
int __cxa_atexit(void (*func)(void*), void *arg, void *__dsohandle)
{
    //printf("__cxa_atexit(%X, %X, %X)\n", func, arg, __dsohandle);
    return __hcxa_atexit(func, arg, __dsohandle, &__s_exit, &__ex_start);
}


extern "C"
int
__aeabi_atexit (void *arg, void (*func) (void *), void *d)
{
    //printf("__aeabi_atexit(%X, %X, %X)\n", arg, func, d);
    return __cxa_atexit (func, arg, d);
}


extern "C"
int
atexit (void (*func) ())
{
  return __cxa_atexit ((void (*)(void*))func, 0, 0);
}
