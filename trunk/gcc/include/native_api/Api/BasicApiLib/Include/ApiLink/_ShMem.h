/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	DYNAMIC LINKING LIBRARY

	Copyright(c) 1997-2002 BNSoft Corp.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT__SHMEM_H_
#define		_BNSOFT__SHMEM_H_

#include	"../ShMem.h"

typedef	H_SHAREDMEM		(*T_pfnShMem_Create)    (T_CSTR pMemName, T_SIZE MemSize);
typedef void			(*T_pfnShMem_Destroy)   (H_SHAREDMEM hShMem);
typedef H_SHAREDMEM		(*T_pfnShMem_GetHandle) (T_CSTR pMemName);
typedef void*			(*T_pfnShMem_GetMem)    (H_SHAREDMEM hShMem);
typedef BOOL			(*T_pfnShMem_IsExistHandle) (T_CSTR pMemName);

typedef struct
{
	T_pfnShMem_Create				pfnCreate;   
	T_pfnShMem_Destroy				pfnDestroy;
	T_pfnShMem_GetHandle				pfnGetHandle;
	T_pfnShMem_GetMem				pfnGetMem;
	T_pfnShMem_IsExistHandle			pfnIsExistHandle;
} TApiGrp_ShMem;


#define		ShMem_Create(p1,p2)			__ApiLink2(ShMem,Create,p1,p2)
#define		ShMem_Destroy(p1)			__ApiLink1(ShMem,Destroy,p1)
#define		ShMem_GetHandle(p1)			__ApiLink1(ShMem,GetHandle,p1)
#define		ShMem_GetMem(p1)			__ApiLink1(ShMem,GetMem,p1)
#define		ShMem_IsExistHandle(p1)			__ApiLink1(ShMem,IsExistHandle,p1)

#endif	//	_BNSOFT__SHMEM_H_
