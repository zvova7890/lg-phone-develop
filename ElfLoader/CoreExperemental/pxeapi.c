
#include "intrinsics.h"
#include "pxeapi.h"
#include "core.h"
#include "remap.h"
#include "swihook.h"

#include "string.h"

unsigned int **__pxeapi_lib = 0;

unsigned int **__pxeapi_getlib()
{
 if (__pxeapi_lib)
    return __pxeapi_lib;
    else return 0;
}


int __pxeapi_init()
{
  __pxeapi_lib = (unsigned int **)PXEAPI_ADDRESS;
  
  
  int doms =  __MRC(15, 0, 3, 0, 0);
  __MCR(15, 0, 0xFFFFFFFF, 3, 0, 0);


  __swihook_setfunc(SWINUM_GETPXEAPI, (unsigned int)&__pxeapi_getlib);

   // Создаём таблицу
   unsigned int *t = __mmu_coarse_malloc();
    if (t)
     {
      //Регистрируем
       __mmu_coarse_set(PXEAPI_BASE, (int)t); 
       for (int i = 0; i < 4; i++)
        {
         unsigned char *p = __mmu_coarsepage_malloc();
         if (p)
           {
            __mmu_coarsepage_set(t, PXEAPI_BASE + MMU_PAGE_SIZE * i, (unsigned int)p);
           } else { __MCR(15, 0, doms, 3, 0, 0); return 0; }
        }
          
       //Копируем таблицу на новый адрес
       memcpy((void *)PXEAPI_BASE, __pxeapi_lib, PXEAPI_SIZE);
       //Устанавливаем новый адрес таблицы
       __pxeapi_lib = (unsigned int **)PXEAPI_BASE;
          
    } else { __MCR(15, 0, doms, 3, 0, 0); return 0; }
          
   __MCR(15, 0, doms, 3, 0, 0);
    return 1;
}

