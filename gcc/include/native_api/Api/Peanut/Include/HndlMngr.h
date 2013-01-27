/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	HANDLEMANAGER	

	Copyright(c) 1997-2002 BNSoft Corp.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT_HNDLMNGR_H_
#define		_BNSOFT_HNDLMNGR_H_

#include	"PeanutInclude.h"


#define		HNDLMNGR_DEBUG_MODE			1


//	Handle Manager Member Functions

extern T_HANDLE		HndlMngr_CreateHandle   (T_PTR pObj);
extern BOOL		HndlMngr_DestroyHandle  (T_HANDLE Handle);

extern T_PTR		HndlMngr_FromHandle     (T_HANDLE Handle);
extern T_PTR		HndlMngr_FromHandleSafe (T_HANDLE Handle);
extern T_HANDLE		HndlMngr_FindHandle     (T_PTR pObj);


#endif	//	_BNSOFT_HNDLMNGR_H_
