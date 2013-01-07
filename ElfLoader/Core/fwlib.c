#include "fwlib.h"

/* KP501 V10H_00 */

const FWLIB fw = 
{
 (int   (*)(const char *, unsigned int))0x46FE1199,
 (int   (*)(int, const void *, int))0x46FD406D,
 (int   (*)(int, const void *, int))0x46FDA00D,
 (int   (*)(int, unsigned char, int))0x46FDA059,
 (int   (*)(int))0x46FE1245,
 
 (void *(*)(unsigned int))0x46577225,
 (void  (*)(void *))0x4657723F,
};

