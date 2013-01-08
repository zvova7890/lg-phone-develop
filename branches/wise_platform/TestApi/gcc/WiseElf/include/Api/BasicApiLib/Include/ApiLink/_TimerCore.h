/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	DYNAMIC LINKING LIBRARY

	Copyright(c) 1997-2002 BNSoft Corp.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT__TIMERCORE_H_
#define		_BNSOFT__TIMERCORE_H_

#include	"../TimerCore.h"

typedef H_TIMERCORE		(*T_pfnTimerCore_SetTimer)          (T_HANDLE hOwner, int nDuration, BOOL bRepeat, BOOL bSleep, T_pfnTimerCallBack pfnTCB);
typedef BOOL			(*T_pfnTimerCore_KillTimer)         (H_TIMERCORE hTimerCore);
typedef void			(*T_pfnTimerCore_SetTicks)          (void);

typedef struct
{
	T_pfnTimerCore_SetTimer				pfnSetTimer;
	T_pfnTimerCore_KillTimer			pfnKillTimer;
	T_pfnTimerCore_SetTicks				pfnSetTicks;
} TApiGrp_TimerCore;


#define	TimerCore_SetTimer(p1,p2,p3,p4,p5)	__ApiLink5(TimerCore,SetTimer,p1,p2,p3,p4,p5)
#define	TimerCore_KillTimer(p1)			__ApiLink1(TimerCore,KillTimer,p1)
#define TimerCore_SetTicks()			__ApiLink0(TimerCore,SetTicks)


#endif	//	_BNSOFT__TIMERCORE_H_
