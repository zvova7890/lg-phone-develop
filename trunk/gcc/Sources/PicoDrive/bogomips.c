

#include <nucleus.h>
#include "bogomips.h"




__attribute__((naked))
void delay_loop(unsigned long loops)
{
    asm volatile("CMP     R0, #0\n"
                 "MOVMI   PC, LR\n"
                 "loc_24: \n"
                 "SUBS    R0, R0, #1\n"
                 "BPL     loc_24\n"
                 "bx lr\n");
}

static inline void __lock_itterupts()
{
    asm volatile("MRS R0, CPSR \n "
                 "ORR R0, R0, #0xC0\n "
                 "MSR CPSR_c, R0\n");
}


static inline void __unlock_itterupts()
{
    asm volatile("MRS R0, CPSR \n "
                 "BIC R0, R0, #0xC0\n "
                 "MSR CPSR_c, R0\n");
}


#define lock_itterrupts() __lock_itterupts()
#define unlock_itterrupts() __unlock_itterupts()



__attribute__((noinline))
void sleep_suka(unsigned int count)
{
    NU_Sleep(count);
}


int calculate_bogomips(unsigned long *clock_per_second, unsigned long *_loops, double *_bogomips)
{
    char s[256];
    unsigned long CLOCKS_PER_SEC;

    unsigned long time = 0;

    lock_itterrupts();

    time = cur_seconds();
    while(time == cur_seconds());

    CLOCKS_PER_SEC = get_ticks();

    time ++;
    while(time == cur_seconds());

    CLOCKS_PER_SEC = get_ticks() - CLOCKS_PER_SEC;
    /*bogomips = CLOCKS_PER_SEC;
    unlock_itterrupts();
    return 0;*/

    unsigned long loops = 1;
    while ((loops <<= 1)) {
        unsigned long ticks;

        ticks = get_ticks();
        delay_loop(loops);
        ticks = get_ticks() - ticks;

        if (ticks >= CLOCKS_PER_SEC) {
            //return (1.0 * loops / ticks) * (CLOCKS_PER_SEC / 500000.0);
            if(_bogomips)
                *_bogomips = (1.0f * (float)loops / (float)ticks) * ((float)CLOCKS_PER_SEC / 500000.0f);

            if(clock_per_second)
                *clock_per_second = CLOCKS_PER_SEC;

            if(_loops)
                *_loops = loops;
            unlock_itterrupts();
            return 0;
        }
    }

    if(clock_per_second) *clock_per_second = CLOCKS_PER_SEC;
    unlock_itterrupts();
    return -1;
}


