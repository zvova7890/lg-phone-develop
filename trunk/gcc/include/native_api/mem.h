#ifndef __MEM_H__
#define __MEM_H__

#include "swihelper.h"


__inl
void *mem_malloc(unsigned int size)
__def( 0x20, void *, size)

__inl
void  mem_free(void *ptr)
__defn( 0x21, ptr)

__inl
void *mem_realloc(void *ptr, unsigned int size)
__def( 0x22, void *, ptr, size)
/*
__inl
void *mem_calloc(unsigned int n, unsigned int size)
__def( 0x23, void *, n, size)
*/
__inl
void *mem_zmalloc(unsigned int size)
__def( 0x24, void *, size)

__inl
unsigned int mem_totalsize()
__def( 0x25, unsigned int)

__inl
unsigned int mem_usedsize()
__def( 0x26, unsigned int)

__inl
unsigned int mem_freesize()
__def( 0x27, unsigned int)

__inl
void *mem_getbase()
__def( 0x28, void *)

#ifndef __USE_LIBC__
#define malloc mem_malloc
#define free mem_free
#define realloc mem_realloc
//#define calloc mem_calloc
#endif


#endif // __MEM_H__

