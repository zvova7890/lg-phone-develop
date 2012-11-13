#ifndef __EXEKILLER_H__
#define __EXEKILLER_H__

#define EXEKILLER_TASKNAME      "ExeKill"
#define EXEKILLER_TASKSTACKSIZE 0x4000
#define EXEKILLER_TASKPRIO      100

#define EXEKILLER_PTRARRAYSIZE  0x1000


#define SWINUM_EXEKILL 0x31

void exekiller_thread(unsigned long a, void *b);

int  __exekiller_init();
void __exekiller_destroy(void *exe);
void __exekiller_deinit();


#endif //__EXEKILLER_H__
