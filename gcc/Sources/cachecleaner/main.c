
#include <fs.h>
#include <loader.h>
//#include <dl.h>

__attribute__((swi(0xE)))
void lprintf(const char *, ...);



static inline void notify_destroy()
{
    extern void *__ex;
    elfclose(&__ex);
}



int _start()
{
    int cleaned = dlcache_clean();
    
    if(cleaned > 0)
	lprintf("libcacheclean: %d libraries is cleaned\n", cleaned);
    else if(cleaned < 0)
	lprintf("libcacheclean: no loaded libraries available\n", cleaned);
    else
	lprintf("libcacheclean: not found unused libraries\n", cleaned);
    
    notify_destroy();
    return 0;
}


