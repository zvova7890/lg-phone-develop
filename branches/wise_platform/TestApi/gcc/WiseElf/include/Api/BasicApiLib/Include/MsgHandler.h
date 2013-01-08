/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	MESSAGE HANDLER

	Copyright(c) 1997-2003 BNSoft Corp.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT_MSGHANDLER_H_
#define		_BNSOFT_MSGHANDLER_H_

#include	"Include.h"
#include	"MsgDef.h"

//-------------------------------------------------------------------------------------------------
#define		MAX_MSGPARAM_NUM			16

//-------------------------------------------------------------------------------------------------
#define		PID_ALL						((T_ID)-1)
#define		PID_CURRENT					((T_ID)-2)
#define		PID_BROADCAST				((T_ID)-3)

//-------------------------------------------------------------------------------------------------
typedef		BOOL	(*T_pfnMsgRun)(T_MSG, T_PARAM, T_PARAM);


extern BOOL               MsgHandler_PostMessage           (T_ID PID, T_MSG MsgType, T_PARAM wParam, T_PARAM lParam);
extern void               MsgHandler_SendMessage           (T_ID PID, T_MSG MsgType, T_PARAM wParam, T_PARAM lParam);
extern void	          MsgHandler_FlushMessage          (T_ID PID);
extern void		  MsgHandler_Translate             (T_EVENT EventType, T_PARAM wParam, T_PARAM lParam);
extern void		  MsgHandler_Process               (void);
extern void		  MsgHandler_Terminate             (void);

extern BOOL		  MsgHandler_RegisterProcessor     (T_ID PID, T_pfnMsgRun pfnMsgRun);
extern BOOL		  MsgHandler_SetActivePID          (T_ID PID);
extern BOOL		  MsgHandler_SetActiveProcessor    (T_pfnMsgRun pfnMsgRun);
extern BOOL		  MsgHandler_InsertActivePID       (T_ID PID);
extern BOOL		  MsgHandler_InsertActiveProcessor (T_pfnMsgRun pfnMsgRun);
extern BOOL		  MsgHandler_RemoveActiveProcessor (void);

extern void		  MsgHandler_SetFullScreenMode     (BOOL bFullScrnMode);

extern T_ID		  MsgHandler_GetPID                (void);
extern T_pfnMsgRun        MsgHandler_GetProcessor          (void);
extern T_ID	          MsgHandler_GetOldPID             (void);
extern T_pfnMsgRun	  MsgHandler_GetOldProcessor       (void);

extern void		  MsgHandler_SetParam              (T_INDEX Index, T_PARAM Param);
extern T_PARAM		  MsgHandler_GetParam              (T_INDEX Index);

extern BOOL		  MsgHandler_SetCapture            (void* pObj, QUAD nData1, QUAD nData2);
extern BOOL		  MsgHandler_ReleaseCapture        (void);
extern void*		  MsgHandler_GetCapture            (void);
extern QUAD		  MsgHandler_GetCaptureData        (int i);
extern BOOL		  MsgHandler_SetCaptureIdx	   (int Index);
extern int		  MsgHandler_GetCaptureIdx	   (void);
extern BOOL		  MsgHandler_RemoveProcessor	   (T_pfnMsgRun pfnMsgRun, T_PARAM wParam, T_PARAM lParam);//HSKIM


#endif	//	_BNSOFT_MSGHANDLER_H_
