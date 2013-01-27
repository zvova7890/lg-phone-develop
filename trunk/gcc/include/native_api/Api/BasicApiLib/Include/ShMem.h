/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	SHARED MEMORY MANAGER

	Copyright(c) 1997-2002 BNSoft Corp.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT_SHMEM_H_
#define		_BNSOFT_SHMEM_H_

#include	"Include.h"

typedef		T_HANDLE	H_SHAREDMEM;

extern H_SHAREDMEM		ShMem_Create    (T_CSTR pcszMemName, T_SIZE MemSize);
extern void			ShMem_Destroy   (H_SHAREDMEM hShMem);
extern H_SHAREDMEM		ShMem_GetHandle (T_CSTR pcszMemName);
extern void*			ShMem_GetMem    (H_SHAREDMEM hShMem);
extern BOOL			ShMem_IsExistHandle(T_CSTR pcszMemName);	

#endif	//	_BNSOFT_SHMEM_H_
