/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	TIMER

	Copyright(c) 1997-2001 BNSoft Corp.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT_TIMER_H_
#define		_BNSOFT_TIMER_H_

#include	"Include.h"
#include	"ProcMngr.h"

typedef		T_HANDLE		H_TIMER;

#define		TIMERID_NONE		((T_ID)-1)

typedef struct
{
	E_PROCSTATUS			enStatus;
	T_ID				ID;
	T_HANDLE			hTimerCore;
	BOOL				bRepeat;
	H_TIMER				hNext;
} TTimer;
																								//	{{BNS_INTERNALCODE(-)}}

extern T_ID	Timer_SetTimer   (T_ID ID, QUAD Duration, BOOL bRepeat);
extern T_ID	Timer_SetTimerEx (T_ID ID, QUAD Duration, BOOL bRepeat, E_PROCSTATUS enStatus);
extern BOOL	Timer_KillTimer  (T_ID ID);
extern T_ID	Timer_GetFreeID  (void);


#endif	//	_BNSOFT_TIMER_H_
