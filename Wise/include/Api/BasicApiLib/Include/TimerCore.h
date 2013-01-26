/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	TIMER CORE

	Copyright(c) 1997-2003 BNSoft Corp.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT_TIMERCORE_H_
#define		_BNSOFT_TIMERCORE_H_

#include	"Include.h"

typedef	T_HANDLE	H_TIMERCORE;
typedef	void	      (*T_pfnTimerCallBack)(T_HANDLE hOwner, H_TIMERCORE hTimerCore, int nFlags);



extern H_TIMERCORE	TimerCore_SetTimer(T_HANDLE hOwner, int nDuration, BOOL bRepeat, BOOL bSleep, T_pfnTimerCallBack pfnTCB);
extern BOOL		TimerCore_KillTimer(H_TIMERCORE hTimerCore);
extern void 		TimerCore_SetTicks(void);


#endif	//	_BNSOFT_TIMERCORE_H_
