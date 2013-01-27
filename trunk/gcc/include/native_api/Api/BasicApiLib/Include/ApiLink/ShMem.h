/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	SHARED MEMORY MANAGER

	Copyright(c) 1997-2002 BNSoft Corp.

	그룹 : BASIC API
	구분 : 메모리관리
	등급 : 공개																						{{BNS_INTERNALCODE()}}
	버전 : 1.08
	일자 : 2006.03.16
	성명 : 박상호,길령환,오윤주,맹현수
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT_SHMEM_H_
#define		_BNSOFT_SHMEM_H_

#include	"Include.h"

typedef		T_HANDLE					H_SHAREDMEM;

//-------------------------------------------------------------------------------------------------
//	ShMem Member Functions
#ifdef		BNS_MAIN_VERSION

	extern void				ShMem_Init      (void);
	extern void				ShMem_Exit      (void);
	extern H_SHAREDMEM		ShMem_Create    (T_CSTR pcszMemName, T_SIZE MemSize);
	extern void				ShMem_Destroy   (H_SHAREDMEM hShMem);
	extern H_SHAREDMEM		ShMem_GetHandle (T_CSTR pcszMemName);
	extern void*			ShMem_GetMem    (H_SHAREDMEM hShMem);

	// 김기훈 2008.5.15 (Thursday)
	extern BOOL				ShMem_IsExistHandle(T_CSTR pcszMemName);	
#endif	//	BNS_MAIN_VERSION
//-------------------------------------------------------------------------------------------------

#endif	//	_BNSOFT_SHMEM_H_
