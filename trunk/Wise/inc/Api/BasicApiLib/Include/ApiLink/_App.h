/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	DYNAMIC LINKING LIBRARY

	Copyright(c) 1997-2002 BNSoft Corp.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT__APP_H_
#define		_BNSOFT__APP_H_

#include	"..\App.h"

//-------------------------------------------------------------------------------------------------
typedef H_PROCESS		(*T_pfnApp_Run)       (T_CSTR pszFile, T_PARAM wParam);
typedef H_PROCESS		(*T_pfnApp_RunEx)     (T_CSTR pszFile, T_PARAM wParam, int nPriority, BOOL bIndividual);
typedef void			(*T_pfnApp_Exit)      (H_PROCESS hProc, int ExitCode);
typedef void			(*T_pfnApp_Resume)    (H_PROCESS hProc, T_PARAM wParam);
typedef void			(*T_pfnApp_Suspend)   (T_PARAM wParam);
typedef BOOL			(*T_pfnApp_GetInfo)   (T_CSTR pszFile, TAppInfo* pAppInfo);

//-------------------------------------------------------------------------------------------------
typedef struct
{
	T_pfnApp_Run						pfnRun;
	T_pfnApp_RunEx						pfnRunEx;
	T_pfnApp_Exit						pfnExit;
	T_pfnApp_Resume						pfnResume;
	T_pfnApp_Suspend					pfnSuspend;
	T_pfnApp_GetInfo					pfnGetInfo;
} TApiGrp_App;


#define	App_Run(p1,p2)		__ApiLink2(App,Run,p1,p2)
#define	App_RunEx(p1,p2,p3,p4)	__ApiLink4(App,RunEx,p1,p2,p3,p4)
#define	App_Exit(p1,p2)		__ApiLink2(App,Exit,p1,p2)
#define	App_Resume(p1,p2)	__ApiLink2(App,Resume,p1,p2)
#define	App_Suspends(p1)	__ApiLink1(App,Suspend,p1)
#define	App_GetInfo(p1,p2)	__ApiLink2(App,GetInfo,p1,p2)

//-------------------------------------------------------------------------------------------------

#endif	//	_BNSOFT__APP_H_
