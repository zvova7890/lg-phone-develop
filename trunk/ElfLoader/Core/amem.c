#include "intrinsics.h"

#include "amem.h"
#include "swihook.h"

unsigned char  __amem_setbyte(unsigned long address, unsigned char byte)
{
 unsigned char ret;
 int doms =  __MRC(15, 0, 3, 0, 0);
 __MCR(15, 0, 0xFFFFFFFF, 3, 0, 0);
         
 __disable_interrupt(); 
 ret = *( ( unsigned char *) address );
 *( ( unsigned char *) address ) = byte;
 __enable_interrupt(); 
        
 __MCR(15, 0, doms, 3, 0, 0);
 return ret;
}

unsigned short __amem_sethwrd(unsigned long address, unsigned short hwrd)
{
 unsigned short ret;
 int doms =  __MRC(15, 0, 3, 0, 0);
 __MCR(15, 0, 0xFFFFFFFF, 3, 0, 0);
 
 address &= ~ 1;
          
 __disable_interrupt(); 
 ret = *( ( unsigned short *) address );
 *( ( unsigned short *) address ) = hwrd;
 __enable_interrupt();    
 
 __MCR(15, 0, doms, 3, 0, 0);
 return ret;
}


unsigned long  __amem_setword(unsigned long address, unsigned long word)
{
 unsigned long ret;
 int doms =  __MRC(15, 0, 3, 0, 0);
 __MCR(15, 0, 0xFFFFFFFF, 3, 0, 0);
 
 address &= ~ 3;
          
 __disable_interrupt(); 
 ret = *( ( unsigned long *) address );
 *( ( unsigned long *) address ) = word;
 __enable_interrupt();
 
 __MCR(15, 0, doms, 3, 0, 0);
 return ret;
}

void __amem_init()
{
 __disable_interrupt(); 
 __swihook_setfunc(SWINUM_SETBYTE, (int)__amem_setbyte);
 __swihook_setfunc(SWINUM_SETHWRD, (int)__amem_sethwrd);
 __swihook_setfunc(SWINUM_SETWORD, (int)__amem_setword);
 __enable_interrupt();
}
