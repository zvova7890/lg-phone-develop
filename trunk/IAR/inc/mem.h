#ifndef __MEM_H__
#define __MEM_H__


#pragma diag_suppress=Ta035

#pragma swi_number=0x20
__swi __arm void *mem_malloc(unsigned int size);

#pragma swi_number=0x21
__swi __arm void  mem_free(void *ptr);

#pragma swi_number=0x22
__swi __arm void *mem_realloc(void *ptr, unsigned int size);

#pragma swi_number=0x23
__swi __arm void *mem_calloc(unsigned int n, unsigned int size);

#pragma swi_number=0x24
__swi __arm void *mem_zmalloc(unsigned int size);

#pragma swi_number=0x25
__swi __arm unsigned int mem_totalsize();

#pragma swi_number=0x26
__swi __arm unsigned int mem_usedsize();

#pragma swi_number=0x27
__swi __arm unsigned int mem_freesize();

#pragma swi_number=0x28
__swi __arm void *mem_getbase();



#endif // __MEM_H__

