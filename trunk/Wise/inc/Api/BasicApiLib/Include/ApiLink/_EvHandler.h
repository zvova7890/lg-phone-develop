/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	DYNAMIC LINKING LIBRARY

	Copyright(c) 1997-2002 BNSoft Corp.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT__EVHANDLER_H_
#define		_BNSOFT__EVHANDLER_H_

#include	"..\EvHandler.h"

typedef BOOL			(*T_pfnEvHandler_PostEvent)      (T_HANDLE hDst, T_EVENT EventType, T_PARAM wParam, T_PARAM lParam);
typedef BOOL			(*T_pfnEvHandler_SendEvent)      (T_HANDLE hDst, T_EVENT EventType, T_PARAM wParam, T_PARAM lParam);
typedef void			(*T_pfnEvHandler_FlushEvent)     (T_HANDLE hDst);
typedef void			(*T_pfnEvHandler_Process)        (void);
typedef void			(*T_pfnEvHandler_SetLongKey)     (KEY Key, int nDuration);
typedef void			(*T_pfnEvHandler_ResetLongKey)   (void);
typedef void			(*T_pfnEvHandler_SetRepeatKey)   (KEY Key, int nDuration1, int nDuration2);
typedef void			(*T_pfnEvHandler_ResetRepeatKey) (void);
typedef void			(*T_pfnEvHandler_SetLongPoint)		(TRect *pLongPointRect, int nDuration);
typedef void			(*T_pfnEvHandler_ResetLongPoint)	(void);
typedef void			(*T_pfnEvHandler_SetRepeatPoint)	(TRect *pRepeatPointRect, int nDuration1, int nDuration2);
typedef void			(*T_pfnEvHandler_ResetRepeatPoint)	(void);

typedef struct
{
	T_pfnEvHandler_PostEvent		pfnPostEvent;
	T_pfnEvHandler_SendEvent		pfnSendEvent;
	T_pfnEvHandler_FlushEvent		pfnFlushEvent;
	T_pfnEvHandler_Process			pfnProcess;
	T_pfnEvHandler_SetLongKey		pfnSetLongKey;
	T_pfnEvHandler_ResetLongKey		pfnResetLongKey;
	T_pfnEvHandler_SetRepeatKey		pfnSetRepeatKey;
	T_pfnEvHandler_ResetRepeatKey		pfnResetRepeatKey;
	T_pfnEvHandler_SetLongPoint		pfnSetLongPoint;
	T_pfnEvHandler_ResetLongPoint		pfnResetLongPoint;
	T_pfnEvHandler_SetRepeatPoint		pfnSetRepeatPoint;
	T_pfnEvHandler_ResetRepeatPoint		pfnResetRepeatPoint;
        
} TApiGrp_EvHandler;


#define	EvHandler_PostEvent(p1,p2,p3,p4)	__ApiLink4(EvHandler,PostEvent,p1,p2,p3,p4)
#define	EvHandler_SendEvent(p1,p2,p3,p4)	__ApiLink4(EvHandler,SendEvent,p1,p2,p3,p4)
#define	EvHandler_FlushEvent(p1)		__ApiLink1(EvHandler,FlushEvent,p1)
#define	EvHandler_Process()			__ApiLink0(EvHandler,Process)
#define	EvHandler_SetLongKey(p1,p2)		__ApiLink2(EvHandler,SetLongKey,p1,p2)
#define	EvHandler_ResetLongKey()		__ApiLink0(EvHandler,ResetLongKey)
#define	EvHandler_SetRepeatKey(p1,p2,p3)	__ApiLink3(EvHandler,SetRepeatKey,p1,p2,p3)
#define	EvHandler_ResetRepeatKey()		__ApiLink0(EvHandler,ResetRepeatKey)
#define	EvHandler_SetLongPoint(p1,p2)		__ApiLink2(EvHandler,SetLongPoint,p1,p2)	
#define	EvHandler_ResetLongPoint()		__ApiLink0(EvHandler,ResetLongPoint)										
#define	EvHandler_SetRepeatPoint(p1,p2,p3) 	__ApiLink3(EvHandler,SetRepeatPoint,p1,p2,p3)
#define	EvHandler_ResetRepeatPoint()		__ApiLink0(EvHandler,ResetRepeatPoint)

#endif	//	_BNSOFT__EVHANDLER_H_
