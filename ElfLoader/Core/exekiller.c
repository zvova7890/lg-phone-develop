
#include "swihook.h"
#include "exekiller.h"
#include "nucleus.h"
#include "fwlib.h"

#include "string.h"

unsigned int exekiller_ptrarray[EXEKILLER_PTRARRAYSIZE];
unsigned int exekiller_count = 0;

NU_TASK exekiller_tsk;
unsigned char exekiller_tsk_stack[EXEKILLER_TASKSTACKSIZE];

void exekiller_thread(unsigned long a, void *b)
{
 while (1)
  {
   for (int a = 0; a < 100; a++)
    {
      for (int i = 0; i < EXEKILLER_PTRARRAYSIZE; i++)
       {
        if (exekiller_ptrarray[i] && exekiller_count > 0)
         {
          fwlib->free((void *)exekiller_ptrarray[i]);
          exekiller_ptrarray[i] = 0;
          if (exekiller_count > 1) exekiller_count--;
           else  break;
         }
        NU_Sleep(1);
       }
      NU_Sleep(10);
    }
    
   NU_Suspend_Task(&exekiller_tsk);
  }
}

int __exekiller_init()
{
 memset(exekiller_ptrarray, 0, EXEKILLER_PTRARRAYSIZE * 4);
 int a = NU_Create_Task(&exekiller_tsk, EXEKILLER_TASKNAME, exekiller_thread, 0, 0, 
               (void *)exekiller_tsk_stack, EXEKILLER_TASKSTACKSIZE, EXEKILLER_TASKPRIO, 0, NU_PREEMPT, NU_NO_START);
 __swihook_setfunc(SWINUM_EXEKILL, (unsigned int)&__exekiller_destroy);
 if (a != NU_SUCCESS) return 0;
  else return 1;
}

void __exekiller_destroy(void *exe)
{
 for (int i = 0; i < EXEKILLER_PTRARRAYSIZE; i++)
   if (!exekiller_ptrarray[i]) { exekiller_ptrarray[i] = (int)exe; exekiller_count++; break; }

 NU_Resume_Task(&exekiller_tsk);
}

void __exekiller_deinit()
{ 
 NU_Suspend_Task(&exekiller_tsk);
 NU_Terminate_Task(&exekiller_tsk);
 NU_Delete_Task(&exekiller_tsk);
}




