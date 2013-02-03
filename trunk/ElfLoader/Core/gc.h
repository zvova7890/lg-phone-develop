#ifndef __GC_H__
#define __GC_H__

#define GC_TASK_NAME       "GC"
#define GC_TASK_STACK_SIZE 0x2000
#define GC_TASK_PRIO       100


#define SWINUM_GC 0x31


int  __gc_init();
int __gc_cleanup(void *ptr, unsigned int delay);
void __gc_destroy();


#endif /* __GC_H__ */
