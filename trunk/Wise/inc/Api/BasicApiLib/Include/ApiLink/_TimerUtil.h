/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	DYNAMIC LINKING LIBRARY

	Copyright(c) 1997-2002 BNSoft Corp.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT__TIMER_H_
#define		_BNSOFT__TIMER_H_

#include	"..\TimerUtil.h"

typedef T_ID			(*T_pfnTimer_SetTimer)   (T_ID ID, QUAD Duration, BOOL bRepeat);
typedef T_ID			(*T_pfnTimer_SetTimerEx) (T_ID ID, QUAD Duration, BOOL bRepeat, E_PROCSTATUS enStatus);
typedef BOOL			(*T_pfnTimer_KillTimer)  (T_ID ID);
typedef T_ID			(*T_pfnTimer_GetFreeID)  (void);

typedef struct
{
	T_pfnTimer_SetTimer			pfnSetTimer;
	T_pfnTimer_SetTimerEx			pfnSetTimerEx;
	T_pfnTimer_KillTimer			pfnKillTimer;
	T_pfnTimer_GetFreeID			pfnGetFreeID;
} TApiGrp_Timer;

#define	Timer_SetTimer(p1,p2,p3)		__ApiLink3(Timer,SetTimer,p1,p2,p3)
#define	Timer_SetTimerEx(p1,p2,p3,p4)		__ApiLink4(Timer,SetTimerEx,p1,p2,p3,p4)
#define	Timer_KillTimer(p1)			__ApiLink1(Timer,KillTimer,p1)
#define	Timer_GetFreeID()			__ApiLink0(Timer,GetFreeID)

#endif	//	_BNSOFT__TIMER_H_
