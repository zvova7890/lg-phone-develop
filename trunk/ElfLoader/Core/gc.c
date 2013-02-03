
#include <intrinsics.h>
#include "swihook.h"
#include "gc.h"
#include "nucleus.h"
#include "fwlib.h"
#include "string.h"


typedef struct _GCQueueItem
{
    void *next;
    void *body;
    unsigned int delay;
}GCQueueItem;


typedef struct
{
    GCQueueItem *first, *last;
    char busy;
}GCQueue;


GCQueue gc_queue;
NU_TASK gc_tsk;


static void gc_thread(unsigned long a, void *b)
{
    while (1)
    {
	/* wait for operations on queue */
	while(gc_queue.busy)
	    NU_Sleep(40);
	
	/* block queue */
	gc_queue.busy = 1;
	
	/* getting first item */
	GCQueueItem *i = gc_queue.first;
	
	/* if we have it... */
	if(i) {
	    /* ... set the next item as first */
	    gc_queue.first = i->next;
	    
	    /* if it`s last item, so ... */
	    if(!gc_queue.first)
		gc_queue.last = 0;
	    
	} else {
	    gc_queue.last = 0;
	}
	
	/* unblock queue */
	gc_queue.busy = 0;
	
	if(i) {
	    NU_Sleep(i->delay);
	    fwlib->free(i->body);
	    fwlib->free(i);
	    
	    /* we go to the next item */
	    continue;
	    
	} else
	    NU_Suspend_Task(&gc_tsk);
    }
}


int __gc_init()
{
    static char gc_tsk_stack[GC_TASK_STACK_SIZE];
    int a = NU_Create_Task(&gc_tsk, GC_TASK_NAME, gc_thread, 0, 0, 
			   gc_tsk_stack, GC_TASK_STACK_SIZE, GC_TASK_PRIO, 
			   0, NU_PREEMPT, NU_NO_START);
    
    __disable_interrupt();
    __swihook_setfunc(SWINUM_GC, (unsigned int)&__gc_cleanup);
    __enable_interrupt();
    
    memset(&gc_queue, 0, sizeof(gc_queue));
    return a;
}


int __gc_cleanup(void *ptr, unsigned int delay)
{
    GCQueueItem *i = fwlib->malloc(sizeof *i);
    if(!i)
	return -1;
    
    i->next = 0;
    i->body = ptr;
    i->delay = delay;
    
    /* wait for cleanup thread will done */
    while(gc_queue.busy)
	NU_Sleep(40);
    
    gc_queue.busy = 1;
    
    if(gc_queue.first) {
	gc_queue.last->next = i;
	gc_queue.last = i;
    } else {
	gc_queue.first = gc_queue.last = i;
    }
    
    gc_queue.busy = 0;
    
    /* Resume garbage collector thread */
    NU_Resume_Task(&gc_tsk);
    return 0;
}


void __gc_destroy()
{ 
    NU_Suspend_Task(&gc_tsk);
    NU_Terminate_Task(&gc_tsk);
    NU_Delete_Task(&gc_tsk);
}




