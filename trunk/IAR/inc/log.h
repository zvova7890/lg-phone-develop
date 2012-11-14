#ifndef __LOG_H__
#define __LOG_H__


#pragma diag_suppress=Ta035

#pragma swi_number=0xD
__swi __arm void lclear();

#pragma swi_number=0xE
__swi __arm void lprintf(const char *format, ...);


#endif // __LOG_H__
