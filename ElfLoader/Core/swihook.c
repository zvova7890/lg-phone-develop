
#include "intrinsics.h"
#include "swihook.h"
#include "core.h"
#include "remap.h"

#include "string.h"

unsigned int *__swihook_lib = 0;

void __swihook_bxlr(){};

void __swihook_abort(unsigned short swinum, unsigned int swi_call_lr_address)
{
  __core_lprintf("*** swihandler: no function %d (%03X) LR = 0x%08X\r\n", swinum, swinum, swi_call_lr_address);
}

unsigned int *__swihook_getlib()
{
 if (__swihook_lib)
    return __swihook_lib;
    else return 0;
}


int __swihook_install(unsigned int *swilib)
{
 if (swilib)
  {
       __swihook_lib   = swilib;
       
       int doms =  __MRC(15, 0, 3, 0, 0);
       __MCR(15, 0, 0xFFFFFFFF, 3, 0, 0);

       unsigned int *swij = (unsigned int *)(* ( ( unsigned int *) (SWIHOOK_JUMPER_ADDRESS) ));
         
        swij[0]  = SWIHOOK_JUMPER_OPCODE;
        swij[1]  = ( unsigned int )&__swihandler_start;
        

       __swihook_setfunc(SWINUM_LIBADDRESS, (unsigned int)&__swihook_getlib);
       __swihook_setfunc(SWINUM_SETSWIFUNC, (unsigned int)&__swihook_setfunc);
       __swihook_setfunc(SWINUM_GETSWIFUNC, (unsigned int)&__swihook_getfunc);
       __swihook_setfunc(SWINUM_CLRSWIFUNC, (unsigned int)&__swihook_clearfunc);
       
       
        // Создаём таблицу
        unsigned int *t = __mmu_coarse_malloc();
        if (t)
         {
          //Регистрируем
          __mmu_coarse_set(SWILIB_BASE, (int)t); 
          for (int i = 0; i < 4; i++)
           {
            unsigned char *p = __mmu_coarsepage_malloc();
            if (p)
             {
              __mmu_coarsepage_set(t, SWILIB_BASE + MMU_PAGE_SIZE * i, (unsigned int)p);
             } else { __MCR(15, 0, doms, 3, 0, 0); return 0; }
            }
          
          //Копируем таблицу на новый адрес
          memcpy((void *)SWILIB_BASE, __swihook_lib, SWILIB_SIZE);
          //Устанавливаем новый адрес таблицы
          __swihook_lib = (unsigned int *)SWILIB_BASE;
          
          } else { __MCR(15, 0, doms, 3, 0, 0); return 0; }
          
       
       __MCR(15, 0, doms, 3, 0, 0);
       
       return 1;
  }
 return 0;
}

int __swihook_setfunc(unsigned short swinum, unsigned int address)
{
 if (!__swihook_lib) return 0;
  
 __swihook_lib[swinum] = address;
 return 1;
}

unsigned int __swihook_getfunc(unsigned short swinum)
{
 if (!__swihook_lib) return 0;
  
 unsigned int ret = 0;
 ret = __swihook_lib[swinum];
 return ret;
}

int __swihook_clearfunc(unsigned short swinum)
{
 if (!__swihook_lib) return 0;
 __swihook_lib[swinum] = (unsigned int)& __swihook_bxlr;
 return 1;
}

