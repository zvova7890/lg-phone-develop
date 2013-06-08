

#include <Api/ApiLinkLib/ApiLink.h>
#include <nucleus.h>
#include <fs.h>
#include <mips.h>
#include <string.h>


#define tmpdir "/usr/zbin/tmp/"
unsigned int restored_bogomips = 0;
unsigned int _clocks_per_second = 0;
unsigned int _loops_per_second = 0;
static float bogomips = 0.0f;
static char loaded = 0;


unsigned int rtc_seconds()
{
    return *((volatile unsigned int *)( 0xF470001C ));
}


unsigned long systimer_ticks()
{
    return *((volatile unsigned long *) 0xF4B00010 );
}



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
static void sleep_suka(unsigned int count)
{
    NU_Sleep(count);
}


int calc_bogomips(unsigned int *clock_per_second, unsigned int *_loops, float *_bogomips)
{
    char s[256];
    unsigned long CLOCKS_PER_SEC;

    unsigned long time = 0;

    lock_itterrupts();

    time = rtc_seconds();
    while(time == rtc_seconds());

    CLOCKS_PER_SEC = systimer_ticks();

    time ++;
    while(time == rtc_seconds());

    CLOCKS_PER_SEC = systimer_ticks() - CLOCKS_PER_SEC;

    unsigned long loops = 1;
    while ((loops <<= 1)) {
        unsigned long ticks;

        ticks = systimer_ticks();
        delay_loop(loops);
        ticks = systimer_ticks() - ticks;

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


static void save_bogomips()
{
    char file[256] = tmpdir "CLOCKS_PER_SEC";
    int fp = fs_open(file, FILE_OPEN_CREATE | FILE_OPEN_TRUNCATE | FILE_OPEN_WRITE);

    if(fp > 0) {

        int r =
             fs_write(fp, &_clocks_per_second, sizeof(_clocks_per_second));
        r += fs_write(fp, &_loops_per_second, sizeof(_loops_per_second));
        r += fs_write(fp, &bogomips, sizeof(bogomips));

        fs_close(fp);
    }
}

__attribute__((noinline, optimize("-O0")))
static void restore_bogomips()
{
    char file[256] = tmpdir "CLOCKS_PER_SEC";
    int fp = fs_open(file, FILE_OPEN_READ);
    if(fp > 0)
    {
        int r = fs_read(fp, &_clocks_per_second, sizeof(_clocks_per_second));
        r +=    fs_read(fp, &_loops_per_second, sizeof(_loops_per_second));
        r +=    fs_read(fp, &bogomips, sizeof(bogomips));

        fs_close(fp);

        if(r == (sizeof(_clocks_per_second)*2)+sizeof(bogomips))
            restored_bogomips = 1;
    }
}


void __mips_init()
{
    //restore_bogomips();
/*
    if(!restored_bogomips) {
        if(calc_bogomips(&_clocks_per_second, &_loops_per_second, &bogomips)) {
            // OLOLO! Can`t calculate bogomips?!
        }
    }*/
}



void __mips_fini()
{
    if(!restored_bogomips) {
        fs_mkdir("/usr/zbin");
        fs_mkdir("/usr/zbin/tmp");

        save_bogomips();
    }
}



static void check()
{
    if(!loaded) {
        restore_bogomips();

        if(!restored_bogomips) {
            if(calc_bogomips(&_clocks_per_second, &_loops_per_second, &bogomips)) {
                // OLOLO! Can`t calculate bogomips?!
            }
        }

        loaded = 1;
    }
}


unsigned int clocks_per_seccond()
{
    check();
    return _clocks_per_second;
}


unsigned int loops_per_seccond()
{
    check();
    return _loops_per_second;
}


float bogomips_result()
{
    check();
    return bogomips;
}












