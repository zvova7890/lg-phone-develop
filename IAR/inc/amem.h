#ifndef __AMEM_H__
#define __AMEM_H__


#pragma diag_suppress=Ta035

#pragma swi_number=0x8
__swi __arm unsigned char  amem_setbyte(unsigned long address, unsigned char byte);

#pragma swi_number=0x9
__swi __arm unsigned short amem_sethwrd(unsigned long address, unsigned short hwrd);

#pragma swi_number=0xA
__swi __arm unsigned long  amem_setword(unsigned long address, unsigned long word);


#endif // __AMEM_H__

