/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	PEANUT BASE CONTROL APILINK

	Copyright(c) 1997-2003 BNSoft Corp.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT__PEANUT_BASECTRL_H_
#define		_BNSOFT__PEANUT_BASECTRL_H_

#include	"../BaseCtrl.h"

typedef H_CTRL			(*T_pfnBaseCtrl_Create)           (void* pOwner, E_CTRLTYPE enType, QUAD Style, T_POS X, T_POS Y, T_SIZE W, T_SIZE H);
typedef BOOL			(*T_pfnBaseCtrl_Destroy)          (H_CTRL hBC);
typedef BOOL			(*T_pfnBaseCtrl_SetOwner)         (H_CTRL hBC, void* pOwner);
typedef BOOL			(*T_pfnBaseCtrl_SetType)          (H_CTRL hBC, E_CTRLTYPE enType);
typedef BOOL			(*T_pfnBaseCtrl_SetOemType)       (H_CTRL hBC, QUAD OemType);
typedef BOOL			(*T_pfnBaseCtrl_ModifyOemType)    (H_CTRL hBC, QUAD RemoveType, QUAD AddType);
typedef BOOL			(*T_pfnBaseCtrl_ModifyStyle)      (H_CTRL hBC, QUAD RemoveStyle, QUAD AddStyle);
typedef BOOL			(*T_pfnBaseCtrl_SetState)         (H_CTRL hBC, QUAD State);
typedef BOOL			(*T_pfnBaseCtrl_SetVisible)       (H_CTRL hBC, BOOL bOn);
typedef BOOL			(*T_pfnBaseCtrl_SetEnable)        (H_CTRL hBC, BOOL bOn);
typedef BOOL			(*T_pfnBaseCtrl_SetCanFocus)      (H_CTRL hBC, BOOL bOn);
typedef BOOL			(*T_pfnBaseCtrl_SetRange)         (H_CTRL hBC, T_POS X1, T_POS Y1, T_POS X2, T_POS Y2);
typedef BOOL			(*T_pfnBaseCtrl_SetPos)           (H_CTRL hBC, T_POS X, T_POS Y);
typedef BOOL			(*T_pfnBaseCtrl_SetSize)          (H_CTRL hBC, T_SIZE W, T_SIZE H);
typedef BOOL			(*T_pfnBaseCtrl_SetFont)          (H_CTRL hBC, E_FONT Font);
typedef BOOL			(*T_pfnBaseCtrl_SetColorTbl)      (H_CTRL hBC, TColorTbl* pColTbl);
typedef BOOL			(*T_pfnBaseCtrl_SetColor)         (H_CTRL hBC, E_COLTYPE ColorType, int ColorIndex, T_COLOR Color);
typedef BOOL			(*T_pfnBaseCtrl_SetSysNotifyProc) (H_CTRL hBC, T_pfnSysNotify pfnSysNotify);
typedef BOOL			(*T_pfnBaseCtrl_SetAppNotifyProc) (H_CTRL hBC, T_ID ID, QUAD NotiMask, T_pfnAppNotify pfnAppNotify);
typedef BOOL			(*T_pfnBaseCtrl_ModifyNotiMask)   (H_CTRL hBC, QUAD RemoveMask, QUAD AddMask);
typedef void*			(*T_pfnBaseCtrl_GetOwner)         (H_CTRL hBC);
typedef E_CTRLTYPE		(*T_pfnBaseCtrl_GetType)          (H_CTRL hBC);
typedef QUAD			(*T_pfnBaseCtrl_GetOemType)       (H_CTRL hBC);
typedef QUAD			(*T_pfnBaseCtrl_GetStyle)         (H_CTRL hBC);
typedef QUAD			(*T_pfnBaseCtrl_GetState)         (H_CTRL hBC);
typedef BOOL			(*T_pfnBaseCtrl_IsVisible)        (H_CTRL hBC);
typedef BOOL			(*T_pfnBaseCtrl_IsEnable)         (H_CTRL hBC);
typedef BOOL			(*T_pfnBaseCtrl_IsCanFocus)       (H_CTRL hBC);
typedef BOOL			(*T_pfnBaseCtrl_IsFocused)        (H_CTRL hBC);
typedef TRect*			(*T_pfnBaseCtrl_GetRange)         (H_CTRL hBC);
typedef T_POS			(*T_pfnBaseCtrl_GetPosX)          (H_CTRL hBC);
typedef T_POS			(*T_pfnBaseCtrl_GetPosY)          (H_CTRL hBC);
typedef T_SIZE			(*T_pfnBaseCtrl_GetWidth)         (H_CTRL hBC);
typedef T_SIZE			(*T_pfnBaseCtrl_GetHeight)        (H_CTRL hBC);
typedef E_FONT			(*T_pfnBaseCtrl_GetFont)          (H_CTRL hBC);
typedef TColorTbl*		(*T_pfnBaseCtrl_GetColorTbl)      (H_CTRL hBC);
typedef T_COLOR			(*T_pfnBaseCtrl_GetColor)         (H_CTRL hBC, E_COLTYPE ColorType, int ColorIndex);
typedef T_pfnSysNotify	        (*T_pfnBaseCtrl_GetSysNotify)     (H_CTRL hBC);
typedef T_pfnAppNotify	        (*T_pfnBaseCtrl_GetAppNotify)     (H_CTRL hBC);
typedef QUAD			(*T_pfnBaseCtrl_GetNotiMask)      (H_CTRL hBC);
typedef BOOL			(*T_pfnBaseCtrl_PtInRange)        (H_CTRL hBC, int X, int Y);
typedef BOOL			(*T_pfnBaseCtrl_SetFocus)         (H_CTRL hBC);
typedef BOOL			(*T_pfnBaseCtrl_KillFocus)        (H_CTRL hBC);
typedef BOOL			(*T_pfnBaseCtrl_Handler)          (H_CTRL hBC, E_CTRLMSG enCtrlMsg, T_PARAM wParam, T_PARAM lParam);
typedef BOOL			(*T_pfnBaseCtrl_Refresh)          (H_CTRL hBC);
typedef BOOL			(*T_pfnBaseCtrl_Paint)            (H_CTRL hBC, BOOL bRefresh);
typedef BOOL			(*T_pfnBaseCtrl_KeyDown)          (H_CTRL hBC, KEY Key, BOOL bRefresh);
typedef BOOL			(*T_pfnBaseCtrl_LongKeyDown)      (H_CTRL hBC, KEY Key, BOOL bRefresh);
typedef BOOL			(*T_pfnBaseCtrl_Timer)            (H_CTRL hBC, BOOL bRefresh);
typedef int			(*T_pfnBaseCtrl_Pointing)         (H_CTRL hBC, int nAction, T_POS X, T_POS Y, BOOL bRefresh);
typedef BOOL			(*T_pfnBaseCtrl_CreateDummyData)  (H_CTRL hBC, T_NUM DataNum);
typedef BOOL			(*T_pfnBaseCtrl_SetDummyData)     (H_CTRL hBC, T_INDEX Index, QUAD Data);
typedef QUAD			(*T_pfnBaseCtrl_GetDummyData)     (H_CTRL hBC, T_INDEX Index);

typedef struct
{
	T_pfnBaseCtrl_Create			pfnCreate;
	T_pfnBaseCtrl_Destroy			pfnDestroy;
	T_pfnBaseCtrl_SetOwner			pfnSetOwner;
	T_pfnBaseCtrl_SetType			pfnSetType;
	T_pfnBaseCtrl_SetOemType		pfnSetOemType;
	T_pfnBaseCtrl_ModifyOemType		pfnModifyOemType;
	T_pfnBaseCtrl_ModifyStyle		pfnModifyStyle;
	T_pfnBaseCtrl_SetState			pfnSetState;
	T_pfnBaseCtrl_SetVisible		pfnSetVisible;
	T_pfnBaseCtrl_SetEnable			pfnSetEnable;
	T_pfnBaseCtrl_SetCanFocus		pfnSetCanFocus;
	T_pfnBaseCtrl_SetRange			pfnSetRange;
	T_pfnBaseCtrl_SetPos			pfnSetPos;
	T_pfnBaseCtrl_SetSize			pfnSetSize;
	T_pfnBaseCtrl_SetFont			pfnSetFont;
	T_pfnBaseCtrl_SetColorTbl		pfnSetColorTbl;
	T_pfnBaseCtrl_SetColor			pfnSetColor;
	T_pfnBaseCtrl_SetSysNotifyProc		pfnSetSysNotifyProc;
	T_pfnBaseCtrl_SetAppNotifyProc		pfnSetAppNotifyProc;
	T_pfnBaseCtrl_ModifyNotiMask		pfnModifyNotiMask;
	T_pfnBaseCtrl_GetOwner			pfnGetOwner;
	T_pfnBaseCtrl_GetType			pfnGetType;
	T_pfnBaseCtrl_GetOemType		pfnGetOemType;
	T_pfnBaseCtrl_GetStyle			pfnGetStyle;
	T_pfnBaseCtrl_GetState			pfnGetState;
	T_pfnBaseCtrl_IsVisible			pfnIsVisible;
	T_pfnBaseCtrl_IsEnable			pfnIsEnable;
	T_pfnBaseCtrl_IsCanFocus		pfnIsCanFocus;
	T_pfnBaseCtrl_IsFocused			pfnIsFocused;
	T_pfnBaseCtrl_GetRange			pfnGetRange;
	T_pfnBaseCtrl_GetPosX			pfnGetPosX;
	T_pfnBaseCtrl_GetPosY			pfnGetPosY;
	T_pfnBaseCtrl_GetWidth			pfnGetWidth;
	T_pfnBaseCtrl_GetHeight			pfnGetHeight;
	T_pfnBaseCtrl_GetFont			pfnGetFont;
	T_pfnBaseCtrl_GetColorTbl		pfnGetColorTbl;
	T_pfnBaseCtrl_GetColor			pfnGetColor;
	T_pfnBaseCtrl_GetSysNotify		pfnGetSysNotify;
	T_pfnBaseCtrl_GetAppNotify		pfnGetAppNotify;
	T_pfnBaseCtrl_GetNotiMask		pfnGetNotiMask;
	T_pfnBaseCtrl_PtInRange			pfnPtInRange;
	T_pfnBaseCtrl_SetFocus			pfnSetFocus;
	T_pfnBaseCtrl_KillFocus			pfnKillFocus;
	T_pfnBaseCtrl_Handler			pfnHandler;
	T_pfnBaseCtrl_Refresh			pfnRefresh;
	T_pfnBaseCtrl_Paint			pfnPaint;
	T_pfnBaseCtrl_KeyDown			pfnKeyDown;
	T_pfnBaseCtrl_LongKeyDown		pfnLongKeyDown;
	T_pfnBaseCtrl_Timer			pfnTimer;
	T_pfnBaseCtrl_Pointing			pfnPointing;
	T_pfnBaseCtrl_CreateDummyData		pfnCreateDummyData;
	T_pfnBaseCtrl_SetDummyData		pfnSetDummyData;
	T_pfnBaseCtrl_GetDummyData		pfnGetDummyData;
} TApiGrp_BaseCtrl;


#define		BaseCtrl_Create(p1,p2,p3,p4,p5,p6,p7)		__ApiLink7(BaseCtrl,Create,p1,p2,p3,p4,p5,p6,p7)
#define		BaseCtrl_Destroy(p1)				__ApiLink1(BaseCtrl,Destroy,p1)
#define		BaseCtrl_SetOwner(p1,p2)			__ApiLink2(BaseCtrl,SetOwner,p1,p2)
#define		BaseCtrl_SetType(p1,p2)				__ApiLink2(BaseCtrl,SetType,p1,p2)
#define		BaseCtrl_SetOemType(p1,p2)			__ApiLink2(BaseCtrl,SetOemType,p1,p2)
#define		BaseCtrl_ModifyOemType(p1,p2,p3)		__ApiLink3(BaseCtrl,ModifyOemType,p1,p2,p3)
#define		BaseCtrl_ModifyStyle(p1,p2,p3)			__ApiLink3(BaseCtrl,ModifyStyle,p1,p2,p3)
#define		BaseCtrl_SetState(p1,p2)			__ApiLink2(BaseCtrl,SetState,p1,p2)
#define		BaseCtrl_SetVisible(p1,p2)			__ApiLink2(BaseCtrl,SetVisible,p1,p2)
#define		BaseCtrl_SetEnable(p1,p2)			__ApiLink2(BaseCtrl,SetEnable,p1,p2)
#define		BaseCtrl_SetCanFocus(p1,p2)			__ApiLink2(BaseCtrl,SetCanFocus,p1,p2)
#define		BaseCtrl_SetRange(p1,p2,p3,p4,p5)		__ApiLink5(BaseCtrl,SetRange,p1,p2,p3,p4,p5)
#define		BaseCtrl_SetPos(p1,p2,p3)			__ApiLink3(BaseCtrl,SetPos,p1,p2,p3)
#define		BaseCtrl_SetSize(p1,p2,p3)			__ApiLink3(BaseCtrl,SetSize,p1,p2,p3)
#define		BaseCtrl_SetFont(p1,p2)				__ApiLink2(BaseCtrl,SetFont,p1,p2)
#define		BaseCtrl_SetColorTbl(p1,p2)			__ApiLink2(BaseCtrl,SetColorTbl,p1,p2)
#define		BaseCtrl_SetColor(p1,p2,p3,p4)			__ApiLink4(BaseCtrl,SetColor,p1,p2,p3,p4)
#define		BaseCtrl_SetSysNotifyProc(p1,p2)		__ApiLink2(BaseCtrl,SetSysNotifyProc,p1,p2)
#define		BaseCtrl_SetAppNotifyProc(p1,p2,p3,p4)		__ApiLink4(BaseCtrl,SetAppNotifyProc,p1,p2,p3,p4)
#define		BaseCtrl_ModifyNotiMask(p1,p2,p3)		__ApiLink3(BaseCtrl,ModifyNotiMask,p1,p2,p3)
#define		BaseCtrl_GetOwner(p1)				__ApiLink1(BaseCtrl,GetOwner,p1)
#define		BaseCtrl_GetType(p1)				__ApiLink1(BaseCtrl,GetType,p1)
#define		BaseCtrl_GetOemType(p1)				__ApiLink1(BaseCtrl,GetOemType,p1)
#define		BaseCtrl_GetStyle(p1)				__ApiLink1(BaseCtrl,GetStyle,p1)
#define		BaseCtrl_GetState(p1)				__ApiLink1(BaseCtrl,GetState,p1)
#define		BaseCtrl_IsVisible(p1)				__ApiLink1(BaseCtrl,IsVisible,p1)
#define		BaseCtrl_IsEnable(p1)				__ApiLink1(BaseCtrl,IsEnable,p1)
#define		BaseCtrl_IsCanFocus(p1)				__ApiLink1(BaseCtrl,IsCanFocus,p1)
#define		BaseCtrl_IsFocused(p1)				__ApiLink1(BaseCtrl,IsFocused,p1)
#define		BaseCtrl_GetRange(p1)				__ApiLink1(BaseCtrl,GetRange,p1)
#define		BaseCtrl_GetPosX(p1)				__ApiLink1(BaseCtrl,GetPosX,p1)
#define		BaseCtrl_GetPosY(p1)				__ApiLink1(BaseCtrl,GetPosY,p1)
#define		BaseCtrl_GetWidth(p1)				__ApiLink1(BaseCtrl,GetWidth,p1)
#define		BaseCtrl_GetHeight(p1)				__ApiLink1(BaseCtrl,GetHeight,p1)
#define		BaseCtrl_GetFont(p1)				__ApiLink1(BaseCtrl,GetFont,p1)
#define		BaseCtrl_GetColorTbl(p1)			__ApiLink1(BaseCtrl,GetColorTbl,p1)
#define		BaseCtrl_GetColor(p1,p2,p3)			__ApiLink3(BaseCtrl,GetColor,p1,p2,p3)
#define		BaseCtrl_GetSysNotify(p1)			__ApiLink1(BaseCtrl,GetSysNotify,p1)
#define		BaseCtrl_GetAppNotify(p1)			__ApiLink1(BaseCtrl,GetAppNotify,p1)
#define		BaseCtrl_GetNotiMask(p1)			__ApiLink1(BaseCtrl,GetNotiMask,p1)
#define		BaseCtrl_PtInRange(p1,p2,p3)			__ApiLink3(BaseCtrl,PtInRange,p1,p2,p3)
#define		BaseCtrl_SetFocus(p1)				__ApiLink1(BaseCtrl,SetFocus,p1)
#define		BaseCtrl_KillFocus(p1)				__ApiLink1(BaseCtrl,KillFocus,p1)
#define		BaseCtrl_Handler(p1,p2,p3,p4)			__ApiLink4(BaseCtrl,Handler,p1,p2,p3,p4)
#define		BaseCtrl_Refresh(p1)				__ApiLink1(BaseCtrl,Refresh,p1)
#define		BaseCtrl_Paint(p1,p2)				__ApiLink2(BaseCtrl,Paint,p1,p2)
#define		BaseCtrl_KeyDown(p1,p2,p3)			__ApiLink3(BaseCtrl,KeyDown,p1,p2,p3)
#define		BaseCtrl_LongKeyDown(p1,p2,p3)			__ApiLink3(BaseCtrl,LongKeyDown,p1,p2,p3)
#define		BaseCtrl_Timer(p1,p2)				__ApiLink2(BaseCtrl,Timer,p1,p2)
#define		BaseCtrl_Pointing(p1,p2,p3,p4,p5)		__ApiLink5(BaseCtrl,Pointing,p1,p2,p3,p4,p5)
#define		BaseCtrl_CreateDummyData(p1,p2)			__ApiLink2(BaseCtrl,CreateDummyData,p1,p2)
#define		BaseCtrl_SetDummyData(p1,p2,p3)			__ApiLink3(BaseCtrl,SetDummyData,p1,p2,p3)
#define		BaseCtrl_GetDummyData(p1,p2)			__ApiLink2(BaseCtrl,GetDummyData,p1,p2)


#endif	//	_BNSOFT__PEANUT_BASECTRL_H_
