/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	PEANUT DIALOG APILINK

	Copyright(c) 1997-2003 BNSoft Corp.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT__PEANUT_DLGCTRL_H_
#define		_BNSOFT__PEANUT_DLGCTRL_H_

#include	"..\Dialog.h"

typedef BOOL			(*T_pfnDlgCtrl_ModifyStyle) (H_CTRL hDlg, T_ID ID, QUAD RemoveStyle, QUAD AddStyle);
typedef BOOL			(*T_pfnDlgCtrl_SetRange)    (H_CTRL hDlg, T_ID ID, T_POS X1, T_POS Y1, T_POS X2, T_POS Y2);
typedef BOOL			(*T_pfnDlgCtrl_SetPos)      (H_CTRL hDlg, T_ID ID, T_POS X, T_POS Y);
typedef BOOL			(*T_pfnDlgCtrl_SetSize)     (H_CTRL hDlg, T_ID ID, T_SIZE W, T_SIZE H);
typedef BOOL			(*T_pfnDlgCtrl_SetFont)     (H_CTRL hDlg, T_ID ID, E_FONT enFont);
typedef E_CTRLTYPE		(*T_pfnDlgCtrl_GetType)     (H_CTRL hDlg, T_ID ID);
typedef TRect*			(*T_pfnDlgCtrl_GetRange)    (H_CTRL hDlg, T_ID ID);
typedef BOOL			(*T_pfnDlgCtrl_Draw)        (H_CTRL hDlg, T_ID ID, BOOL bRefresh);
typedef BOOL			(*T_pfnDlgCtrl_SetVisible)  (H_CTRL hDlg, T_ID ID, BOOL bOn);
typedef BOOL			(*T_pfnDlgCtrl_SetEnable)   (H_CTRL hDlg, T_ID ID, BOOL bOn);
typedef BOOL			(*T_pfnDlgCtrl_SetCanFocus) (H_CTRL hDlg, T_ID ID, BOOL bOn);
typedef BOOL			(*T_pfnDlgCtrl_IsVisible)   (H_CTRL hDlg, T_ID ID);
typedef BOOL			(*T_pfnDlgCtrl_IsEnable)    (H_CTRL hDlg, T_ID ID);
typedef BOOL			(*T_pfnDlgCtrl_IsCanFocus)  (H_CTRL hDlg, T_ID ID);
typedef H_CTRL			(*T_pfnDlgCtrl_GetHandle)   (H_CTRL hDlg, T_ID ID);

typedef struct
{
	T_pfnDlgCtrl_ModifyStyle			pfnModifyStyle;
	T_pfnDlgCtrl_SetRange				pfnSetRange;
	T_pfnDlgCtrl_SetPos				pfnSetPos;
	T_pfnDlgCtrl_SetSize				pfnSetSize;
	T_pfnDlgCtrl_SetFont				pfnSetFont;
	T_pfnDlgCtrl_GetType				pfnGetType;
	T_pfnDlgCtrl_GetRange				pfnGetRange;
	T_pfnDlgCtrl_Draw				pfnDraw;
	T_pfnDlgCtrl_SetVisible				pfnSetVisible;
	T_pfnDlgCtrl_SetEnable				pfnSetEnable;
	T_pfnDlgCtrl_SetCanFocus			pfnSetCanFocus;
	T_pfnDlgCtrl_IsVisible				pfnIsVisible;
	T_pfnDlgCtrl_IsEnable				pfnIsEnable;
	T_pfnDlgCtrl_IsCanFocus				pfnIsCanFocus;
	T_pfnDlgCtrl_GetHandle				pfnGetHandle;
} TApiGrp_DlgCtrl;


#define	DlgCtrl_ModifyStyle(p1,p2,p3,p4)			__ApiLink4(DlgCtrl,ModifyStyle,p1,p2,p3,p4)
#define	DlgCtrl_SetRange(p1,p2,p3,p4,p5,p6)			__ApiLink6(DlgCtrl,SetRange,p1,p2,p3,p4,p5,p6)
#define	DlgCtrl_SetPos(p1,p2,p3,p4)				__ApiLink4(DlgCtrl,SetPos,p1,p2,p3,p4)
#define	DlgCtrl_SetSize(p1,p2,p3,p4)				__ApiLink4(DlgCtrl,SetSize,p1,p2,p3,p4)
#define	DlgCtrl_SetFont(p1,p2,p3)				__ApiLink3(DlgCtrl,SetFont,p1,p2,p3)
#define	DlgCtrl_GetType(p1,p2)					__ApiLink2(DlgCtrl,GetType,p1,p2)
#define	DlgCtrl_GetRange(p1,p2)					__ApiLink2(DlgCtrl,GetRange,p1,p2)
#define	DlgCtrl_Draw(p1,p2,p3)					__ApiLink3(DlgCtrl,Draw,p1,p2,p3)
#define	DlgCtrl_SetVisible(p1,p2,p3)				__ApiLink3(DlgCtrl,SetVisible,p1,p2,p3)
#define	DlgCtrl_SetEnable(p1,p2,p3)				__ApiLink3(DlgCtrl,SetEnable,p1,p2,p3)
#define	DlgCtrl_SetCanFocus(p1,p2,p3)				__ApiLink3(DlgCtrl,SetCanFocus,p1,p2,p3)
#define	DlgCtrl_IsVisible(p1,p2)				__ApiLink2(DlgCtrl,IsVisible,p1,p2)
#define	DlgCtrl_IsEnable(p1,p2)					__ApiLink2(DlgCtrl,IsEnable,p1,p2)
#define	DlgCtrl_IsCanFocus(p1,p2)				__ApiLink2(DlgCtrl,IsCanFocus,p1,p2)
#define	DlgCtrl_GetHandle(p1,p2)				__ApiLink2(DlgCtrl,GetHandle,p1,p2)

#endif	//	_BNSOFT__PEANUT_DLGCTRL_H_
