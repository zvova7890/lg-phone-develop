/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	HEAP CORE

	Copyright(c) 1997-2002 BNSoft Corp.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/


#ifndef		_BNSOFT_HEAPCORE_H_
#define		_BNSOFT_HEAPCORE_H_

#include	"Include.h"

typedef struct
{
	BYTE*				pBuf;		//	Start address of heap
	T_SIZE				Size;		//	Total size of heap
	void**				pFreeList;	//	Free list pointer of heap
	T_SIZE				FreeListSize;	//	Max index of free list
	T_SIZE				HeapBlockSize;	//	Threshold size to determine sequential or buddy algorithm
} THeapDesc;


#endif	//	_BNSOFT_HEAPCORE_H_


