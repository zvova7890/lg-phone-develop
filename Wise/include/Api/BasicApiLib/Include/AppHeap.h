/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	APPLICATION HEAP MANAGER (DOUBLE POINTING HEAP)

	Copyright(c) 1997-2002 BNSoft Corp.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT_APPHEAP_H_
#define		_BNSOFT_APPHEAP_H_

#include	"Include.h"
#include	"HeapCore.h"

//	AppHeap Macro Member Functions
#define		AppHeap_GetMem(H)			*(H)

typedef		void*					  H_MEMBLOCK;

																								//	{{BNS_INTERNALCODE(-)}}
//	AppHeap Member Functions

extern H_MEMBLOCK		AppHeap_Alloc              (T_SIZE MemSize);
extern void			AppHeap_Free               (H_MEMBLOCK hMemBlock);
extern H_MEMBLOCK		AppHeap_Grow               (H_MEMBLOCK hMemBlock, int nGrowSize);
extern H_MEMBLOCK		AppHeap_Realloc            (H_MEMBLOCK hMemBlock, T_SIZE MemSize);
extern H_MEMBLOCK		AppHeap_Calloc             (T_SIZE MemSize);

extern T_SIZE			AppHeap_GetSize            (H_MEMBLOCK hMemBlock);
extern T_SIZE			AppHeap_GetTotalSize       (void);
extern T_SIZE			AppHeap_GetUsedSize        (void);
extern T_SIZE			AppHeap_GetFreeSize        (void);
extern T_SIZE			AppHeap_GetLargestFreeSize (void);

extern void			AppHeap_MarkLeakage        (void);
extern BOOL			AppHeap_CheckLeakage       (void);

#endif	//	_BNSOFT_APPHEAP_H_
