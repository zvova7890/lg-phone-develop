/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	DYNAMIC LINKING LIBRARY

	Copyright(c) 1997-2003 BNSoft Corp.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT__MSGHANDLER_H_
#define		_BNSOFT__MSGHANDLER_H_

#include	"../MsgHandler.h"

typedef BOOL			(*T_pfnMsgHandler_PostMessage)           (T_ID PID, T_MSG MsgType, T_PARAM wParam, T_PARAM lParam);
typedef void			(*T_pfnMsgHandler_SendMessage)           (T_ID PID, T_MSG MsgType, T_PARAM wParam, T_PARAM lParam);
typedef void			(*T_pfnMsgHandler_FlushMessage)          (T_ID PID);
typedef void			(*T_pfnMsgHandler_Translate)             (T_EVENT EventType, T_PARAM wParam, T_PARAM lParam);
typedef void			(*T_pfnMsgHandler_Process)               (void);
typedef void			(*T_pfnMsgHandler_Terminate)             (void);
typedef BOOL			(*T_pfnMsgHandler_RegisterProcessor)     (T_ID PID, T_pfnMsgRun pfnMsgRun);
typedef BOOL			(*T_pfnMsgHandler_SetActivePID)          (T_ID PID);
typedef BOOL			(*T_pfnMsgHandler_SetActiveProcessor)    (T_pfnMsgRun pfnMsgRun);
typedef BOOL			(*T_pfnMsgHandler_InsertActivePID)       (T_ID PID);
typedef BOOL			(*T_pfnMsgHandler_InsertActiveProcessor) (T_pfnMsgRun pfnMsgRun);
typedef BOOL			(*T_pfnMsgHandler_RemoveActiveProcessor) (void);
typedef void			(*T_pfnMsgHandler_SetFullScreenMode)     (BOOL bFullScrnMode);
typedef T_ID			(*T_pfnMsgHandler_GetPID)                (void);
typedef T_pfnMsgRun		(*T_pfnMsgHandler_GetProcessor)          (void);
typedef T_ID			(*T_pfnMsgHandler_GetOldPID)             (void);
typedef T_pfnMsgRun		(*T_pfnMsgHandler_GetOldProcessor)       (void);
typedef void			(*T_pfnMsgHandler_SetParam)              (T_INDEX Index, T_PARAM Param);
typedef T_PARAM			(*T_pfnMsgHandler_GetParam)              (T_INDEX Index);
typedef BOOL			(*T_pfnMsgHandler_SetCapture)            (void* pObj, QUAD nData1, QUAD nData2);
typedef BOOL			(*T_pfnMsgHandler_ReleaseCapture)        (void);
typedef void*			(*T_pfnMsgHandler_GetCapture)            (void);
typedef QUAD			(*T_pfnMsgHandler_GetCaptureData)        (int i);
typedef BOOL			(*T_pfnMsgHandler_RemoveProcessor)		 (T_pfnMsgRun pfnMsgRun, T_PARAM wParam, T_PARAM lParam);


typedef struct
{
	T_pfnMsgHandler_PostMessage				pfnPostMessage;
	T_pfnMsgHandler_SendMessage				pfnSendMessage;
	T_pfnMsgHandler_FlushMessage			pfnFlushMessage;
	T_pfnMsgHandler_Translate				pfnTranslate;
	T_pfnMsgHandler_Process					pfnProcess;
	T_pfnMsgHandler_Terminate				pfnTerminate;
	T_pfnMsgHandler_RegisterProcessor		pfnRegisterProcessor;
	T_pfnMsgHandler_SetActivePID			pfnSetActivePID;
	T_pfnMsgHandler_SetActiveProcessor		pfnSetActiveProcessor;
	T_pfnMsgHandler_InsertActivePID			pfnInsertActivePID;
	T_pfnMsgHandler_InsertActiveProcessor	pfnInsertActiveProcessor;
	T_pfnMsgHandler_RemoveActiveProcessor	pfnRemoveActiveProcessor;
	T_pfnMsgHandler_SetFullScreenMode		pfnSetFullScreenMode;
	T_pfnMsgHandler_GetPID					pfnGetPID;
	T_pfnMsgHandler_GetProcessor			pfnGetProcessor;
	T_pfnMsgHandler_GetOldPID				pfnGetOldPID;
	T_pfnMsgHandler_GetOldProcessor			pfnGetOldProcessor;
	T_pfnMsgHandler_SetParam				pfnSetParam;
	T_pfnMsgHandler_GetParam				pfnGetParam;
	T_pfnMsgHandler_SetCapture				pfnSetCapture;
	T_pfnMsgHandler_ReleaseCapture			pfnReleaseCapture;
	T_pfnMsgHandler_GetCapture				pfnGetCapture;
	T_pfnMsgHandler_GetCaptureData			pfnGetCaptureData;
	T_pfnMsgHandler_RemoveProcessor			pfnRemoveProcessor;
} TApiGrp_MsgHandler;


#define	    MsgHandler_PostMessage(p1,p2,p3,p4)		__ApiLink4(MsgHandler,PostMessage,p1,p2,p3,p4)
#define	    MsgHandler_SendMessage(p1,p2,p3,p4)		__ApiLink4(MsgHandler,SendMessage,p1,p2,p3,p4)
#define	    MsgHandler_FlushMessage(p1)				__ApiLink1(MsgHandler,FlushMessage,p1)
#define	    MsgHandler_Translate(p1,p2,p3)			__ApiLink3(MsgHandler,Translate,p1,p2,p3)
#define	    MsgHandler_Process()					__ApiLink0(MsgHandler,Process)
#define	    MsgHandler_Terminate()					__ApiLink0(MsgHandler,Terminate)
#define	    MsgHandler_RegisterProcessor(p1,p2)		__ApiLink2(MsgHandler,RegisterProcessor,p1,p2)
#define	    MsgHandler_SetActivePID(p1)				__ApiLink1(MsgHandler,SetActivePID,p1)
#define	    MsgHandler_SetActiveProcessor(p1)		__ApiLink1(MsgHandler,SetActiveProcessor,p1)
#define	    MsgHandler_InsertActivePID(p1)			__ApiLink1(MsgHandler,InsertActivePID,p1)
#define	    MsgHandler_InsertActiveProcessor(p1)	__ApiLink1(MsgHandler,InsertActiveProcessor,p1)
#define	    MsgHandler_RemoveActiveProcessor()		__ApiLink0(MsgHandler,RemoveActiveProcessor)
#define	    MsgHandler_SetFullScreenMode(p1)		__ApiLink1(MsgHandler,SetFullScreenMode,p1)
#define	    MsgHandler_GetPID()						__ApiLink0(MsgHandler,GetPID)
#define	    MsgHandler_GetProcessor()				__ApiLink0(MsgHandler,GetProcessor)
#define	    MsgHandler_GetOldPID()					__ApiLink0(MsgHandler,GetOldPID)
#define	    MsgHandler_GetOldProcessor()			__ApiLink0(MsgHandler,GetOldProcessor)
#define	    MsgHandler_SetParam(p1,p2)				__ApiLink2(MsgHandler,SetParam,p1,p2)
#define	    MsgHandler_GetParam(p1)					__ApiLink1(MsgHandler,GetParam,p1)
#define	    MsgHandler_SetCapture(p1,p2,p3)			__ApiLink3(MsgHandler,SetCapture,p1,p2,p3)
#define	    MsgHandler_ReleaseCapture()				__ApiLink0(MsgHandler,ReleaseCapture)
#define	    MsgHandler_GetCapture()					__ApiLink0(MsgHandler,GetCapture)
#define	    MsgHandler_GetCaptureData(p1)			__ApiLink1(MsgHandler,GetCaptureData,p1)
#define	    MsgHandler_RemoveProcessor(p1,p2,p3)	__ApiLink3(MsgHandler,RemoveProcessor,p1,p2,p3)

#endif	//	_BNSOFT__MSGHANDLER_H_
