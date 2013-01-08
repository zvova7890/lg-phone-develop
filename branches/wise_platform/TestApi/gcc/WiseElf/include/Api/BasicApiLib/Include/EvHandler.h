/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	EVENT HANDLER

	Copyright(c) 1997-2002 BNSoft Corp.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT_EVHANDLER_H_
#define		_BNSOFT_EVHANDLER_H_

#include	"Include.h"
#include	"EventDef.h"
#include	"KeyDef.h"
#include	"ConfigEM.h"


//-------------------------------------------------------------------------------------------------
typedef struct
{
	T_HANDLE				hDst;
	T_EVENT					Type;
	T_PARAM					wParam;
	T_PARAM					lParam;
	QUAD					Data;							//	for dummy
} TEvent;


typedef void  (*T_pfnEvHandler_Listener)(T_EVENT EventType, T_PARAM wParam, T_PARAM lParam);

						
extern BOOL	EvHandler_PostEvent      (T_HANDLE hDst, T_EVENT EventType, T_PARAM wParam, T_PARAM lParam);
extern BOOL	EvHandler_SendEvent      (T_HANDLE hDst, T_EVENT EventType, T_PARAM wParam, T_PARAM lParam);
extern void	EvHandler_FlushEvent     (T_HANDLE hDst);
extern void	EvHandler_Process        (void);
extern void	EvHandler_SetLongKey     (KEY Key, int nDuration);
extern void	EvHandler_ResetLongKey   (void);
extern void	EvHandler_SetRepeatKey   (KEY Key, int nDuration1, int nDuration2);
extern void	EvHandler_ResetRepeatKey (void);
	
extern void	EvHandler_SetLongPoint     (TRect *pLongPointRect, int nDuration);	
extern void	EvHandler_ResetLongPoint   (void);				
extern void	EvHandler_SetRepeatPoint	(TRect *pRepeatPointRect, int nDuration1, int nDuration2);
extern void	EvHandler_ResetRepeatPoint	(void);

        
#endif	//	_BNSOFT_EVHANDLER_H_
