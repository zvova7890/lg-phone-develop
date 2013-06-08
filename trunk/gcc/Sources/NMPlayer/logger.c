


#include <access.h>
#include <stdio.h>
#include <string.h>
#include "logger.h"
#include <swihelper.h>



extern unsigned int hook_data[];
extern unsigned int bxlr[];
extern void test_func();


void logger(unsigned int lr, int hz1, int line, const char *file, const char *msg, int hz2, int hz3, int hz4)
{
    printf("lr=%X %d: %s:%d ", lr, hz1, file, line);
    printf(msg, hz2, hz3, hz4);
    printf("\n");
}



//__attribute__((swi(1)))
__inl int __swihook_setfunc(unsigned short swinum, unsigned int address)
__def(1, int, swinum, address)


__attribute__((noinline))
void install_hook()
{
    unlock_mem_access();
    __swihook_setfunc(28, (unsigned int)test_func);

    memcpy((void*)0x46578A8C, hook_data, 4);

    lock_mem_access();
}


__attribute__((noinline))
void remove_hook()
{
    unlock_mem_access();
    memcpy((void*)0x46578A8C, bxlr, 4);
    lock_mem_access();
}


