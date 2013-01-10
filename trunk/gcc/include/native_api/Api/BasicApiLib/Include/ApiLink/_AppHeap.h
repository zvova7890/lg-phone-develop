/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	DYNAMIC LINKING LIBRARY

	Copyright(c) 1997-2002 BNSoft Corp.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT__APPHEAP_H_
#define		_BNSOFT__APPHEAP_H_

#include	"../AppHeap.h"

typedef H_MEMBLOCK		(*T_pfnAppHeap_Alloc)              (T_SIZE MemSize);
typedef void			(*T_pfnAppHeap_Free)               (H_MEMBLOCK hMemBlock);
typedef H_MEMBLOCK		(*T_pfnAppHeap_Grow)               (H_MEMBLOCK hMemBlock, int nGrowSize);
typedef H_MEMBLOCK		(*T_pfnAppHeap_Realloc)            (H_MEMBLOCK hMemBlock, T_SIZE MemSize);
typedef H_MEMBLOCK		(*T_pfnAppHeap_Calloc)             (T_SIZE MemSize);
typedef T_SIZE			(*T_pfnAppHeap_GetSize)            (H_MEMBLOCK hMemBlock);
typedef T_SIZE			(*T_pfnAppHeap_GetTotalSize)       (void);
typedef T_SIZE			(*T_pfnAppHeap_GetUsedSize)        (void);
typedef T_SIZE			(*T_pfnAppHeap_GetFreeSize)        (void);
typedef T_SIZE			(*T_pfnAppHeap_GetLargestFreeSize) (void);
typedef void			(*T_pfnAppHeap_MarkLeakage)        (void);
typedef BOOL			(*T_pfnAppHeap_CheckLeakage)       (void);


//-------------------------------------------------------------------------------------------------
typedef struct
{
	T_pfnAppHeap_Alloc			pfnAlloc;
	T_pfnAppHeap_Free			pfnFree;
	T_pfnAppHeap_Grow			pfnGrow;
	T_pfnAppHeap_Realloc			pfnRealloc;
	T_pfnAppHeap_Calloc			pfnCalloc;

        int                                     __0x14;
        int                                     __0x18;

	T_pfnAppHeap_GetSize			pfnGetSize;
	T_pfnAppHeap_GetTotalSize		pfnGetTotalSize;
	T_pfnAppHeap_GetUsedSize		pfnGetUsedSize;
	T_pfnAppHeap_GetFreeSize		pfnGetFreeSize;
	T_pfnAppHeap_GetLargestFreeSize		pfnGetLargestFreeSize;
	T_pfnAppHeap_MarkLeakage		pfnMarkLeakage;
	T_pfnAppHeap_CheckLeakage		pfnCheckLeakage;
} TApiGrp_AppHeap;


#define		AppHeap_Alloc(p1)			__ApiLink1(AppHeap,Alloc,p1)
#define		AppHeap_Free(p1)			__ApiLink1(AppHeap,Free,p1)
#define		AppHeap_Grow(p1,p2)			__ApiLink2(AppHeap,Grow,p1,p2)
#define		AppHeap_Realloc(p1,p2)			__ApiLink2(AppHeap,Realloc,p1,p2)
#define		AppHeap_Calloc(p1)			__ApiLink1(AppHeap,Calloc,p1)
#define		AppHeap_GetSize(p1)			__ApiLink1(AppHeap,GetSize,p1)
#define		AppHeap_GetTotalSize()			__ApiLink0(AppHeap,GetTotalSize)
#define		AppHeap_GetUsedSize()			__ApiLink0(AppHeap,GetUsedSize)
#define		AppHeap_GetFreeSize()			__ApiLink0(AppHeap,GetFreeSize)
#define		AppHeap_GetLargestFreeSize()		__ApiLink0(AppHeap,GetLargestFreeSize)
#define		AppHeap_MarkLeakage()			__ApiLink0(AppHeap,MarkLeakage)
#define		AppHeap_CheckLeakage()			__ApiLink0(AppHeap,CheckLeakage)

#endif	//	_BNSOFT__APPHEAP_H_
