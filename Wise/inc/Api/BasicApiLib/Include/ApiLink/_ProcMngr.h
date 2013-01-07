/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	DYNAMIC LINKING LIBRARY

	Copyright(c) 1997-2002 BNSoft Corp.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT__PROCMNGR_H_
#define		_BNSOFT__PROCMNGR_H_

#include	"..\ProcMngr.h"

typedef H_PROCESS		(*T_pfnProcMngr_FindHandle)   (H_PROCESS hBase, E_PROCFIND enFind);
typedef BOOL			(*T_pfnProcMngr_MoveHandle)   (H_PROCESS hProc, H_PROCESS hAfter);
typedef T_NUM			(*T_pfnProcMngr_GetNum)       (H_PROCESS hBase, E_PROCTYPE enType);
typedef QUAD			(*T_pfnProcMngr_GetInfo)      (H_PROCESS hProc, E_PROCINFO enProcInfo);
typedef BOOL			(*T_pfnProcMngr_IsAscendant)  (H_PROCESS hBase, H_PROCESS hProc);
typedef BOOL			(*T_pfnProcMngr_IsDescendant) (H_PROCESS hBase, H_PROCESS hProc);
typedef H_PROCESS		(*T_pfnProcMngr_SearchApp)    (T_CSTR rcszAppName);
typedef BOOL			(*T_pfnProcMngr_SetTimer)     (H_PROCESS hProc, T_ID ID, QUAD Duration, BOOL bRepeat, E_PROCSTATUS enStatus);
typedef BOOL			(*T_pfnProcMngr_KillTimer)    (T_ID ID);

typedef struct
{
	T_pfnProcMngr_FindHandle			pfnFindHandle;
	T_pfnProcMngr_MoveHandle			pfnMoveHandle;
	T_pfnProcMngr_GetNum				pfnGetNum;
	T_pfnProcMngr_GetInfo				pfnGetInfo;
	T_pfnProcMngr_IsAscendant			pfnIsAscendant;
	T_pfnProcMngr_IsDescendant			pfnIsDescendant;
	T_pfnProcMngr_SearchApp				pfnSearchApp;
	T_pfnProcMngr_SetTimer				pfnSetTimer;
	T_pfnProcMngr_KillTimer				pfnKillTimer;
} TApiGrp_ProcMngr;

//-------------------------------------------------------------------------------------------------

#define	ProcMngr_FindHandle(p1,p2)		__ApiLink2(ProcMngr,FindHandle,p1,p2)
#define	ProcMngr_MoveHandle(p1,p2)		__ApiLink2(ProcMngr,MoveHandle,p1,p2)
#define	ProcMngr_GetNum(p1,p2)			__ApiLink2(ProcMngr,GetNum,p1,p2)
#define	ProcMngr_GetInfo(p1,p2)			__ApiLink2(ProcMngr,GetInfo,p1,p2)
#define	ProcMngr_IsAscendant(p1,p2)		__ApiLink2(ProcMngr,IsAscendant,p1,p2)
#define	ProcMgr_IsDescendant(p1,p2)		__ApiLink2(ProcMngr,IsDescendant,p1,p2)
#define	ProcMngr_SearchApp(p1)			__ApiLink1(ProcMngr,SearchApp,p1)
#define	ProcMngr_SetTimer(p1,p2,p3,p4,p5)	__ApiLink5(ProcMngr,SetTimer,p1,p2,p3,p4,p5)
#define	ProcMngr_KillTimer(p1)			__ApiLink1(ProcMngr,KillTimer,p1)


#endif	//	_BNSOFT__PROCMNGR_H_
