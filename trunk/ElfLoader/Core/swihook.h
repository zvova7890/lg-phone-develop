#ifndef __SWIHOOK_H__
#define __SWIHOOK_H__

#define SWIHOOK_JUMPER_ADDRESS 0xFFFF0028
#define SWIHOOK_JUMPER_OPCODE  0xE51FF004

#define SWINUM_LIBADDRESS      0x00
#define SWINUM_SETSWIFUNC      0x01
#define SWINUM_GETSWIFUNC      0x02
#define SWINUM_CLRSWIFUNC      0x03

#define SWILIB_LEN             0x1000
#define SWILIB_SIZE            0x4000
#define SWILIB_BASE            0x00300000


unsigned int *__swihook_getlib();

int __swihook_install(unsigned int *swilib);
int __swihook_setfunc(unsigned short swinum, unsigned int address);
unsigned int __swihook_getfunc(unsigned short swinum);
int __swihook_clearfunc(unsigned short swinum);

extern void __swihandler_start();


#endif //__SWIHOOK_H__
