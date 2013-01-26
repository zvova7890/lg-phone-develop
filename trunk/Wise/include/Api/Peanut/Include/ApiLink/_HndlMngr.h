/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	PEANUT HANDLE MANAGER APILINK

	Copyright(c) 1997-2003 BNSoft Corp.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT__PEANUT_HNDLMNGR_H_
#define		_BNSOFT__PEANUT_HNDLMNGR_H_

#include	"..\HndlMngr.h"

typedef T_HANDLE		(*T_pfnHndlMngr_CreateHandle)   (T_PTR pObj);
typedef BOOL			(*T_pfnHndlMngr_DestroyHandle)  (T_HANDLE Handle);
typedef T_PTR			(*T_pfnHndlMngr_FromHandle)     (T_HANDLE Handle);
typedef T_PTR			(*T_pfnHndlMngr_FromHandleSafe) (T_HANDLE Handle);
typedef T_HANDLE		(*T_pfnHndlMngr_FindHandle)     (T_PTR pObj);

typedef struct
{
	T_pfnHndlMngr_CreateHandle		pfnCreateHandle;
	T_pfnHndlMngr_DestroyHandle		pfnDestroyHandle;
	T_pfnHndlMngr_FromHandle		pfnFromHandle;
	T_pfnHndlMngr_FromHandleSafe		pfnFromHandleSafe;
	T_pfnHndlMngr_FindHandle		pfnFindHandle;
} TApiGrp_HndlMngr;


#define	HndlMngr_CreateHandle(p1)		__ApiLink1(HndlMngr,CreateHandle,p1)
#define	HndlMngr_DestroyHandle(p1)		__ApiLink1(HndlMngr,DestroyHandle,p1)
#define	HndlMngr_FromHandle(p1)			__ApiLink1(HndlMngr,FromHandle,p1)
#define	HndlMngr_FromHandleSafe(p1)		__ApiLink1(HndlMngr,FromHandleSafe,p1)
#define	HndlMngr_FindHandle(p1)			__ApiLink1(HndlMngr,FindHandle,p1)


#endif	//	_BNSOFT__PEANUT_HNDLMNGR_H_
