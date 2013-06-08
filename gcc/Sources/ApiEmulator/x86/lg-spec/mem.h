#ifndef __MEM_H__
#define __MEM_H__




void *mem_malloc(unsigned int size);
void  mem_free(void *ptr);
void *mem_realloc(void *ptr, unsigned int size);
void *mem_zmalloc(unsigned int size);
unsigned int mem_totalsize();
unsigned int mem_usedsize();
unsigned int mem_freesize();
void *mem_getbase();


#ifndef __USE_LIBC__
#define malloc mem_malloc
#define free mem_free
#define realloc mem_realloc
//#define calloc mem_calloc
#endif


#endif // __MEM_H__

