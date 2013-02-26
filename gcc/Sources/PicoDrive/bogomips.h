
#ifndef __BOGOMIPS_H__
#define __BOGOMIPS_H__

volatile static unsigned int cur_seconds() {
    return *((volatile unsigned int *)( 0xF470001C ));
}

volatile static unsigned long get_ticks() {
    return *((volatile unsigned long *)0xF4B00010);
}


void delay_loop(unsigned long loops);

int calculate_bogomips(unsigned long *clock_per_second, unsigned long *loops, double *bogomips);



#endif

