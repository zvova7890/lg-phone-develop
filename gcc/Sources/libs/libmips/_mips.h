

#ifndef __MIPS_H__
#define __MIPS_H__


#ifdef __cplusplus
extern "C" {
#endif




static unsigned int rtc_seconds() {
    return *((volatile unsigned int *)( 0xF470001C ));
}

static unsigned long systimer_ticks() {
    return *((volatile unsigned long *)0xF4B00010);
}



unsigned long clocks_per_seccond();
unsigned long loops_per_seccond();
float bogomips_result();






#ifdef __cplusplus
}
#endif


#endif
