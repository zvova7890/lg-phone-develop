
#ifndef __EVHANDLER_H__
#define __EVHANDLER_H__


#include "ProcMngr.h"


#ifdef __cplusplus
extern "C" {
#endif


extern BOOL	EvHandler_PostEvent(T_HANDLE hDst, T_EVENT EventType, T_PARAM wParam, T_PARAM lParam);
extern BOOL	EvHandler_SendEvent(T_HANDLE hDst, T_EVENT EventType, T_PARAM wParam, T_PARAM lParam);
extern void	EvHandler_FlushEvent(T_HANDLE hDst);




#ifdef __cplusplus
}
#endif

#endif
