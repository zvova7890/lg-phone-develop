/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	PROCESS MANAGER

	Copyright(c) 1997-2002 BNSoft Corp.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT_PROCMNGR_H_
#define		_BNSOFT_PROCMNGR_H_

#include	"Include.h"
#include	"EvHandler.h"

#define          swi_ProcMngr                 0x400
#define          swi_ProcMngr_CreateProcess   swi_ProcMngr + 0
#define          swi_ProcMngr_StartProcess    swi_ProcMngr + 1

//	Access Level Definition
#ifndef		ACCESSLEVEL_DEFINED
#define		ACCESSLEVEL_DEFINED
typedef enum
{
	ACCESSLEVEL_PUBLIC					= 0,
	ACCESSLEVEL_DEVELOPER,
	ACCESSLEVEL_SYSTEM
} E_ACCESSLEVEL;
#endif	//	ACCESSLEVEL_DEFINED

#define		H_PROCESS_NONE			((H_PROCESS)0)
#define		H_PROCESS_FIRST			((H_PROCESS)-1)
#define		H_PROCESS_LAST			((H_PROCESS)-2)
#define		H_PROCESS_REMOVE		((H_PROCESS)-3)
#define		H_PROCESS_BACKGROUND		((H_PROCESS)-4)
#define		H_PROCESS_ACTIVE		H_PROCESS_FIRST
#define		H_PROCESS_BROADCAST		((H_PROCESS)-5)
#define		H_PROCESS_CURRENT		((H_PROCESS)-6)
#define		H_PROCESS_NEXT			((H_PROCESS)-7)

#define		FOREGROUND_PRIORITY		0

//	Application
#define		MAX_APP_NAME			32
#define		MAX_APP_PATH			64

#define		MAX_DLL_SLOT_NUM		128

//	Type of Process Status
typedef enum
{
	PROCSTATUS_NONE				= 0,
	PROCSTATUS_ACTIVATE,
	PROCSTATUS_DEACTIVATE,
	PROCSTATUS_BACKGROUND,
	PROCSTATUS_FREE
} E_PROCSTATUS;

//	Type of Process Find Options
typedef enum
{
	PROCFIND_FIRST				= 0,
	PROCFIND_CURRENT,
	PROCFIND_PREV,
	PROCFIND_NEXT,
	PROCFIND_LAST,
	PROCFIND_FIRST_BACKGROUND,
	PROCFIND_LAST_BACKGROUND,
	PROCFIND_PARENT,
	PROCFIND_CHILD,
	PROCFIND_SIBLING
} E_PROCFIND;

//	Type of Process Type
typedef enum
{
	PROCTYPE_FOREGROUND			= 0,
	PROCTYPE_BACKGROUND,
	PROCTYPE_CHILD,
	PROCTYPE_SIBLING,
	PROCTYPE_ASCENDANT,
	PROCTYPE_DESCENDANT
} E_PROCTYPE;

//	Type of Process Information Options
typedef enum
{
	PROCINFO_ACCESSLEVEL				= 0,
	PROCINFO_CODEAREA,
	PROCINFO_DATAAREA,
	PROCINFO_STATUS,
	PROCINFO_PRIORITY,
	PROCINFO_TIMER,
	PROCINFO_APPNAME,
	PROCINFO_APPDRIVE,
	PROCINFO_APPDIR
} E_PROCINFO;

//	Definition of Process Create Information
typedef struct
{
	E_ACCESSLEVEL		enAccessLevel;
	T_ADDR			CodeArea;
	T_ADDR			DataArea;
	T_ADDR			PxeInitAddr;
	T_ADDR			PxeRunAddr;
	T_CSTR			pszAppName;
	T_HANDLE		hAppDrive;
	T_HANDLE		hAppDir;
} TProcessCI;

typedef		T_HANDLE					H_PROCESS;
typedef		T_HANDLE					H_RESOURCE;

#define		ProcMngr_GetAccessLevel(hP)	(E_ACCESSLEVEL)ProcMngr_GetInfo(hP, PROCINFO_ACCESSLEVEL)
#define		ProcMngr_GetCodeArea(hP)	(T_ADDR)       ProcMngr_GetInfo(hP, PROCINFO_CODEAREA)
#define		ProcMngr_GetDataArea(hP)	(T_ADDR)       ProcMngr_GetInfo(hP, PROCINFO_DATAAREA)
#define		ProcMngr_GetStatus(hP)		(E_PROCSTATUS) ProcMngr_GetInfo(hP, PROCINFO_STATUS)
#define		ProcMngr_GetPriority(hP)	(int)          ProcMngr_GetInfo(hP, PROCINFO_PRIORITY)
#define		ProcMngr_GetTimer(hP)		(H_TIMER)      ProcMngr_GetInfo(hP, PROCINFO_TIMER)
#define		ProcMngr_GetAppName(hP)		(T_CSTR)       ProcMngr_GetInfo(hP, PROCINFO_APPNAME)
#define		ProcMngr_GetAppDrive(hP)	(QUAD)         ProcMngr_GetInfo(hP, PROCINFO_APPDRIVE)
#define		ProcMngr_GetAppDir(hP)		(QUAD)         ProcMngr_GetInfo(hP, PROCINFO_APPDIR)


extern H_PROCESS ProcMngr_FindHandle   (H_PROCESS hBase, E_PROCFIND enFind);
extern BOOL	 ProcMngr_MoveHandle   (H_PROCESS hProc, H_PROCESS hAfter);

extern T_NUM	 ProcMngr_GetNum       (H_PROCESS hBase, E_PROCTYPE enType);
extern QUAD	 ProcMngr_GetInfo      (H_PROCESS hProc, E_PROCINFO enProcInfo);

extern BOOL	 ProcMngr_IsAscendant  (H_PROCESS hBase, H_PROCESS hProc);
extern BOOL	 ProcMngr_IsDescendant (H_PROCESS hBase, H_PROCESS hProc);

extern H_PROCESS ProcMngr_SearchApp    (T_CSTR rcszAppName);

extern BOOL	 ProcMngr_SetTimer(H_PROCESS hProc, T_ID ID, QUAD Duration, BOOL bRepeat, E_PROCSTATUS enStatus);
extern BOOL	 ProcMngr_KillTimer (T_ID ID);

#ifdef __GNUC__

__attribute__((swi(0x400)))
H_PROCESS ProcMngr_CreateProcess(TProcessCI *pProcCI, BOOL bIndividual);

__attribute__((swi(0x401)))
BOOL ProcMngr_StartProcess(H_PROCESS hProc, T_PARAM wParam, int nPriority);

#else

#pragma diag_suppress=Ta035

#pragma swi_number=swi_ProcMngr_CreateProcess
__swi __arm H_PROCESS ProcMngr_CreateProcess(TProcessCI *pProcCI, BOOL bIndividual);

#pragma swi_number=swi_ProcMngr_StartProcess
__swi __arm BOOL ProcMngr_StartProcess(H_PROCESS hProc, T_PARAM wParam, int nPriority);

#endif


#endif	//	_BNSOFT_PROCMNGR_H_
