#ifndef __AMEM_H__
#define __AMEM_H__

#define SWINUM_SETBYTE     0x08
#define SWINUM_SETHWRD     0x09
#define SWINUM_SETWORD     0x0A

unsigned char  __amem_setbyte(unsigned long address, unsigned char byte);
unsigned short __amem_sethwrd(unsigned long address, unsigned short hwrd);
unsigned long  __amem_setword(unsigned long address, unsigned long word);

void __amem_init();

#endif // __AMEM_H__

