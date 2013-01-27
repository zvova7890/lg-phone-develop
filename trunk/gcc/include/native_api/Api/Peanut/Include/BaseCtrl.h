/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	PEANUT BASE CONTROL

	Copyright(c) 1997-2003 BNSoft Corp.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT_PEANUT_BASECTRL_H_
#define		_BNSOFT_PEANUT_BASECTRL_H_

#include	"PeanutInclude.h"
#include	"HndlMngr.h"
#include	"ColorTbl.h"

//-------------------------------------------------------------------------------------------------
//
typedef enum
{
	PERIODIC_UPDATE_INVAID = -1,
	PERIODIC_UPDATE_NONE	= 0,
	PERIODIC_UPDATE_PARTIAL,
	PERIODIC_UPDATE_FULL
} E_PERIODIC_UPDATE_STATE;


typedef struct _TBaseCtrl
{
	H_CTRL				Handle;
	void*				pOwner;
	E_CTRLTYPE			enType;
	QUAD				OemType;
	QUAD				Style;
	QUAD				State;	
	TRect				Range;
	E_FONT				enFont;
	TColorTbl*			pColorTbl;
	T_COLORLIST			pColLst;
	BOOL				(*pfnOwnHandler)(H_CTRL, E_CTRLMSG, T_PARAM, T_PARAM);
	BOOL				(*pfnSysNotify) (struct _TBaseCtrl*, E_NOTIMSG, T_PARAM, T_PARAM);
	BOOL				(*pfnAppNotify) (H_CTRL, T_ID, E_NOTIMSG, T_PARAM, T_PARAM);
	T_ID				NotiID;
	QUAD				NotiMask;
	T_NUM				DummyDataNum;
	QUAD*				pDummyData;
	BOOL				bAssignedColTbl;

	E_PERIODIC_UPDATE_STATE	PeriodicUpdateState;
	TRect				PeriodicUpdateRange;

	QUAD				UserDefCtrlID;		// user define control ID
	void*				pOemBaseCtrl;		// for Oem data
} TBaseCtrl;

typedef		BOOL	(*T_pfnOwnHandler)(H_CTRL hComp, E_CTRLMSG enCtrlMsg, T_PARAM wParam, T_PARAM lParam);
typedef		BOOL	(*T_pfnSysNotify) (TBaseCtrl* pBC, E_NOTIMSG enNotiMsg, T_PARAM wParam, T_PARAM lParam);
typedef		BOOL	(*T_pfnAppNotify) (H_CTRL hComp, T_ID ID, E_NOTIMSG enNotiMsg, T_PARAM wParam, T_PARAM lParam);

//	BaseCtrl Macro Member Functions
#define		BaseCtrl_GetCtrlPtr(hBC)	HndlMngr_FromHandle(hBC)

//	BaseCtrl Member Functions

extern H_CTRL			BaseCtrl_Create           (void* pOwner, E_CTRLTYPE enType, QUAD Style, T_POS X, T_POS Y, T_SIZE W, T_SIZE H);
extern BOOL			BaseCtrl_Destroy          (H_CTRL hBC);

extern BOOL			BaseCtrl_SetOwner         (H_CTRL hBC, void* pOwner);
extern BOOL			BaseCtrl_SetType          (H_CTRL hBC, E_CTRLTYPE enType);
extern BOOL			BaseCtrl_SetOemType       (H_CTRL hBC, QUAD OemType);
extern BOOL			BaseCtrl_ModifyOemType    (H_CTRL hBC, QUAD RemoveType, QUAD AddType);
extern BOOL			BaseCtrl_ModifyStyle      (H_CTRL hBC, QUAD RemoveStyle, QUAD AddStyle);
extern BOOL			BaseCtrl_SetState         (H_CTRL hBC, QUAD State);
extern BOOL			BaseCtrl_SetVisible       (H_CTRL hBC, BOOL bOn);
extern BOOL			BaseCtrl_SetEnable        (H_CTRL hBC, BOOL bOn);
extern BOOL			BaseCtrl_SetCanFocus      (H_CTRL hBC, BOOL bOn);
extern BOOL			BaseCtrl_SetRange         (H_CTRL hBC, T_POS X1, T_POS Y1, T_POS X2, T_POS Y2);
extern BOOL			BaseCtrl_SetPos           (H_CTRL hBC, T_POS X, T_POS Y);
extern BOOL			BaseCtrl_SetSize          (H_CTRL hBC, T_SIZE W, T_SIZE H);
extern BOOL			BaseCtrl_SetFont          (H_CTRL hBC, E_FONT enFont);
extern BOOL			BaseCtrl_SetColorTbl      (H_CTRL hBC, TColorTbl* pColTbl);
extern BOOL			BaseCtrl_SetColor         (H_CTRL hBC, E_COLTYPE ColorType, int ColorIndex, T_COLOR Color);
extern BOOL			BaseCtrl_SetSysNotifyProc (H_CTRL hBC, T_pfnSysNotify pfnSysNotify);
extern BOOL			BaseCtrl_SetAppNotifyProc (H_CTRL hBC, T_ID ID, QUAD NotiMask, T_pfnAppNotify pfnAppNotify);
extern BOOL			BaseCtrl_ModifyNotiMask   (H_CTRL hBC, QUAD RemoveMask, QUAD AddMask);

extern void*			BaseCtrl_GetOwner         (H_CTRL hBC);
extern E_CTRLTYPE		BaseCtrl_GetType          (H_CTRL hBC);
extern QUAD			BaseCtrl_GetOemType       (H_CTRL hBC);
extern QUAD			BaseCtrl_GetStyle         (H_CTRL hBC);
extern QUAD			BaseCtrl_GetState         (H_CTRL hBC);
extern BOOL			BaseCtrl_IsVisible        (H_CTRL hBC);
extern BOOL			BaseCtrl_IsEnable         (H_CTRL hBC);
extern BOOL			BaseCtrl_IsCanFocus       (H_CTRL hBC);
extern BOOL			BaseCtrl_IsFocused        (H_CTRL hBC);
extern TRect*			BaseCtrl_GetRange         (H_CTRL hBC);
extern T_POS			BaseCtrl_GetPosX          (H_CTRL hBC);
extern T_POS			BaseCtrl_GetPosY          (H_CTRL hBC);
extern T_SIZE			BaseCtrl_GetWidth         (H_CTRL hBC);
extern T_SIZE			BaseCtrl_GetHeight        (H_CTRL hBC);
extern E_FONT			BaseCtrl_GetFont          (H_CTRL hBC);
extern TColorTbl*		BaseCtrl_GetColorTbl      (H_CTRL hBC);
extern T_COLOR			BaseCtrl_GetColor         (H_CTRL hBC, E_COLTYPE ColorType, int ColorIndex);
extern T_pfnSysNotify	        BaseCtrl_GetSysNotify     (H_CTRL hBC);
extern T_pfnAppNotify	        BaseCtrl_GetAppNotify     (H_CTRL hBC);
extern QUAD			BaseCtrl_GetNotiMask      (H_CTRL hBC);

extern BOOL			BaseCtrl_PtInRange        (H_CTRL hBC, int X, int Y);
extern BOOL			BaseCtrl_SetFocus         (H_CTRL hBC);
extern BOOL			BaseCtrl_KillFocus        (H_CTRL hBC);

extern BOOL			BaseCtrl_Handler          (H_CTRL hBC, E_CTRLMSG enCtrlMsg, T_PARAM wParam, T_PARAM lParam);
extern BOOL			BaseCtrl_Refresh          (H_CTRL hBC);
extern BOOL			BaseCtrl_Paint            (H_CTRL hBC, BOOL bRefresh);
extern BOOL			BaseCtrl_KeyDown          (H_CTRL hBC, KEY Key, BOOL bRefresh);
extern BOOL			BaseCtrl_LongKeyDown	  (H_CTRL hBC, KEY Key, BOOL bRefresh);
extern BOOL			BaseCtrl_Timer            (H_CTRL hBC, BOOL bRefresh);
extern int			BaseCtrl_Pointing         (H_CTRL hBC, int nAction, T_POS X, T_POS Y, BOOL bRefresh);

extern BOOL			BaseCtrl_CreateDummyData  (H_CTRL hBC, T_NUM DataNum);
extern BOOL			BaseCtrl_SetDummyData     (H_CTRL hBC, T_INDEX Index, QUAD Data);
extern QUAD			BaseCtrl_GetDummyData     (H_CTRL hBC, T_INDEX Index);

extern BOOL			BaseCtrl_SetPeriodicUpdateRange	(H_CTRL hBC, T_POS X1, T_POS Y1, T_POS X2, T_POS Y2);
extern BOOL			BaseCtrl_GetPeriodicUpdateRange	(H_CTRL hBC, TRect* pUpdateRange);
extern void			BaseCtrl_SetPeriodicUpdateState	(H_CTRL hBC, E_PERIODIC_UPDATE_STATE enState);
extern E_PERIODIC_UPDATE_STATE	BaseCtrl_GetPeriodicUpdateState	(H_CTRL hBC);
extern BOOL			BaseCtrl_PeriodicUpdate	(H_CTRL hBC);

#endif	//	_BNSOFT_PEANUT_BASECTRL_H_
