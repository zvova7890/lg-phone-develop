/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	PEANUT DIALOG APILINK

	Copyright(c) 1997-2003 BNSoft Corp.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT__PEANUT_DIALOG_H_
#define		_BNSOFT__PEANUT_DIALOG_H_

#include	"..\Dialog.h"

typedef H_CTRL			(*T_pfnDialog_Create)             (void);
typedef BOOL			(*T_pfnDialog_Destroy)            (H_CTRL hDlg);
typedef BOOL			(*T_pfnDialog_ModifyStyle)        (H_CTRL hDlg, QUAD RemoveStyle, QUAD AddStyle);
typedef BOOL			(*T_pfnDialog_SetRange)           (H_CTRL hDlg, T_POS X1, T_POS Y1, T_POS X2, T_POS Y2);
typedef H_CTRL			(*T_pfnDialog_CreateButCtrl)      (H_CTRL hDlg, T_ID ID, T_POS X, T_POS Y, T_SIZE W, T_SIZE H, T_CSTR pcszText);
typedef H_CTRL			(*T_pfnDialog_CreateChkCtrl)      (H_CTRL hDlg, T_ID ID, T_POS X, T_POS Y, T_SIZE W, T_SIZE H, T_CSTR pcszText);
typedef H_CTRL			(*T_pfnDialog_CreateEditCtrl)     (H_CTRL hDlg, T_ID ID, T_POS X, T_POS Y, T_SIZE W, T_SIZE H, T_NUM MaxChar);
typedef H_CTRL			(*T_pfnDialog_CreateEditCtrlEx)   (H_CTRL hDlg, T_ID ID, T_POS X, T_POS Y, T_SIZE W, T_SIZE H, T_NUM MaxChar, QUAD AddStyle);
typedef H_CTRL			(*T_pfnDialog_CreateIconCtrl)     (H_CTRL hDlg, T_ID ID, T_POS X, T_POS Y, TImage* pImage);
typedef H_CTRL			(*T_pfnDialog_CreateImgCtrl)      (H_CTRL hDlg, T_ID ID, T_POS X, T_POS Y, T_SIZE W, T_SIZE H, T_CSTR pcszFileName);
typedef H_CTRL			(*T_pfnDialog_CreateKeypadCtrl)   (H_CTRL hDlg, T_ID ID, T_POS X, T_POS Y, T_SIZE W, T_SIZE H);
typedef H_CTRL			(*T_pfnDialog_CreateLineCtrl)     (H_CTRL hDlg, T_ID ID, T_POS X1, T_POS Y1, T_POS X2, T_POS Y2);
typedef H_CTRL			(*T_pfnDialog_CreateListCtrl)     (H_CTRL hDlg, T_ID ID, T_POS X, T_POS Y, T_SIZE W, T_SIZE H);
typedef H_CTRL			(*T_pfnDialog_CreateRdoCtrl)      (H_CTRL hDlg, T_ID ID, T_POS X, T_POS Y, T_SIZE W, T_SIZE H, T_CSTR pcszText, H_CTRL hGrpRC);
typedef H_CTRL			(*T_pfnDialog_CreateREditCtrl)    (H_CTRL hDlg, T_ID ID, T_POS X, T_POS Y, T_SIZE W, T_SIZE H, T_NUM MaxChar);
typedef H_CTRL			(*T_pfnDialog_CreateREditCtrlEx)  (H_CTRL hDlg, T_ID ID, T_POS X, T_POS Y, T_SIZE W, T_SIZE H, T_NUM MaxChar, QUAD AddStyle);
typedef H_CTRL			(*T_pfnDialog_CreateSelCtrl)      (H_CTRL hDlg, T_ID ID, T_POS X, T_POS Y, T_SIZE W, T_SIZE H);
typedef H_CTRL			(*T_pfnDialog_CreateTextCtrl)     (H_CTRL hDlg, T_ID ID, T_POS X, T_POS Y, T_SIZE W, T_SIZE H, T_CSTR pcszText);
typedef H_CTRL			(*T_pfnDialog_CreateListView)     (H_CTRL hDlg, T_ID ID, T_POS X, T_POS Y, T_SIZE W, T_SIZE H);

typedef BOOL			(*T_pfnDialog_DestroyCtrl)        (H_CTRL hDlg, H_CTRL hCtrl);
typedef BOOL			(*T_pfnDialog_DestroyAllCtrls)    (H_CTRL hDlg);
typedef BOOL			(*T_pfnDialog_AttachCtrl)         (H_CTRL hDlg, T_ID ID, H_CTRL hCtrl);
typedef BOOL			(*T_pfnDialog_DettachCtrl)		  (H_CTRL hDlg, H_CTRL hCtrl);
typedef BOOL			(*T_pfnDialog_SetSize)            (H_CTRL hDlg, T_SIZE W, T_SIZE H);
typedef BOOL			(*T_pfnDialog_SetSoftMenu)        (H_CTRL hDlg, T_CSTR rcszLSoftMenu, T_CSTR rcszMSoftMenu, T_CSTR rcszRSoftMenu);
typedef BOOL			(*T_pfnDialog_SetScroll)          (H_CTRL hDlg, T_POS ScrollX, T_POS ScrollY);
typedef BOOL			(*T_pfnDialog_SetMoveKey)         (H_CTRL hDlg, KEY PrevKey, KEY NextKey);
typedef T_POS			(*T_pfnDialog_GetScrollX)         (H_CTRL hDlg);
typedef T_POS			(*T_pfnDialog_GetScrollY)         (H_CTRL hDlg);
typedef TDlgCtrl*		(*T_pfnDialog_GetActiveCtrl)      (H_CTRL hDlg);
typedef BOOL			(*T_pfnDialog_SetActiveCtrl)      (H_CTRL hDlg, T_ID ID);
typedef T_ID			(*T_pfnDialog_MoveActiveCtrl)     (H_CTRL hDlg, int nOffset);
typedef BOOL			(*T_pfnDialog_EnsureVisible)      (H_CTRL hDlg, T_ID ID);
typedef BOOL			(*T_pfnDialog_ShowCursor)         (H_CTRL hDlg, BOOL bShow);
typedef BOOL			(*T_pfnDialog_SetLocalOrigin)     (H_CTRL hDlg);
typedef BOOL			(*T_pfnDialog_DrawSoftMenu)       (H_CTRL hDlg, BOOL bRefresh);
typedef BOOL			(*T_pfnDialog_DoModal)            (H_CTRL hDlg, int LifeTime);
typedef BOOL			(*T_pfnDialog_StopModal)          (void);
typedef BOOL			(*T_pfnDialog_EndModal)           (void);
typedef T_SIZE			(*T_pfnDialog_GetScrollMaxY)      (H_CTRL hDlg);
typedef H_CTRL			(*T_pfnDialog_CreateTitleButCtrl) (H_CTRL hDlg, T_ID ID, T_POS X, T_POS Y, T_SIZE W, T_SIZE H, T_CSTR pcszText);
typedef BOOL			(*T_pfnDialog_SetSoftMenuIcon)    (H_CTRL hDlg, QUAD IconID1, QUAD IconID2, QUAD IconID3, QUAD IconID4, QUAD IconID5);

typedef struct
{
	T_pfnDialog_Create				pfnCreate;
	T_pfnDialog_Destroy				pfnDestroy;
	T_pfnDialog_ModifyStyle				pfnModifyStyle;
	T_pfnDialog_SetRange				pfnSetRange;
	T_pfnDialog_CreateButCtrl			pfnCreateButCtrl;
	T_pfnDialog_CreateChkCtrl			pfnCreateChkCtrl;
	T_pfnDialog_CreateEditCtrl			pfnCreateEditCtrl;
	T_pfnDialog_CreateEditCtrlEx		pfnCreateEditCtrlEx;
	T_pfnDialog_CreateIconCtrl			pfnCreateIconCtrl;
	T_pfnDialog_CreateImgCtrl			pfnCreateImgCtrl;
	T_pfnDialog_CreateKeypadCtrl		pfnCreateKeypadCtrl;
	T_pfnDialog_CreateLineCtrl			pfnCreateLineCtrl;
	T_pfnDialog_CreateListCtrl			pfnCreateListCtrl;
	T_pfnDialog_CreateRdoCtrl			pfnCreateRdoCtrl;
	T_pfnDialog_CreateREditCtrl			pfnCreateREditCtrl;
	T_pfnDialog_CreateREditCtrlEx		pfnCreateREditCtrlEx;
	T_pfnDialog_CreateSelCtrl			pfnCreateSelCtrl;
	T_pfnDialog_CreateTextCtrl			pfnCreateTextCtrl;
	T_pfnDialog_CreateListView			pfnCreateListView;
	T_pfnDialog_DestroyCtrl				pfnDestroyCtrl;
	T_pfnDialog_DestroyAllCtrls			pfnDestroyAllCtrls;
	T_pfnDialog_AttachCtrl				pfnAttachCtrl;
	T_pfnDialog_DettachCtrl				pfnDettachCtrl;
	T_pfnDialog_SetSize					pfnSetSize;
	T_pfnDialog_SetSoftMenu				pfnSetSoftMenu;
	T_pfnDialog_SetScroll				pfnSetScroll;
	T_pfnDialog_SetMoveKey				pfnSetMoveKey;
	T_pfnDialog_GetScrollX				pfnGetScrollX;
	T_pfnDialog_GetScrollY				pfnGetScrollY;
	T_pfnDialog_GetActiveCtrl			pfnGetActiveCtrl;
	T_pfnDialog_SetActiveCtrl			pfnSetActiveCtrl;
	T_pfnDialog_MoveActiveCtrl			pfnMoveActiveCtrl;
	T_pfnDialog_EnsureVisible			pfnEnsureVisible;
	T_pfnDialog_ShowCursor				pfnShowCursor;
	T_pfnDialog_SetLocalOrigin			pfnSetLocalOrigin;
	T_pfnDialog_DrawSoftMenu			pfnDrawSoftMenu;
	T_pfnDialog_DoModal					pfnDoModal;
	T_pfnDialog_StopModal				pfnStopModal;
	T_pfnDialog_EndModal				pfnEndModal;
	T_pfnDialog_GetScrollMaxY			pfnGetScrollMaxY;
	T_pfnDialog_CreateTitleButCtrl		pfnCreateTitleButCtrl;
	T_pfnDialog_SetSoftMenuIcon			pfnSetSoftMenuIcon;
} TApiGrp_Dialog;


#define		Dialog_Create()								__ApiLink0(Dialog,Create)
#define		Dialog_Destroy(p1)							__ApiLink1(Dialog,Destroy,p1)
#define		Dialog_ModifyStyle(p1,p2,p3)				__ApiLink3(Dialog,ModifyStyle,p1,p2,p3)
#define		Dialog_SetRange(p1,p2,p3,p4,p5)				__ApiLink5(Dialog,SetRange,p1,p2,p3,p4,p5)
#define		Dialog_CreateButCtrl(p1,p2,p3,p4,p5,p6,p7)	__ApiLink7(Dialog,CreateButCtrl,p1,p2,p3,p4,p5,p6,p7)
#define		Dialog_CreateChkCtrl(p1,p2,p3,p4,p5,p6,p7)	__ApiLink7(Dialog,CreateChkCtrl,p1,p2,p3,p4,p5,p6,p7)
#define		Dialog_CreateEditCtrl(p1,p2,p3,p4,p5,p6,p7)	__ApiLink7(Dialog,CreateEditCtrl,p1,p2,p3,p4,p5,p6,p7)
#define		Dialog_CreateEditCtrlEx(p1,p2,p3,p4,p5,p6,p7,p8)	__ApiLink8(Dialog,CreateEditCtrlEx,p1,p2,p3,p4,p5,p6,p7,p8)
#define		Dialog_CreateIconCtrl(p1,p2,p3,p4,p5)		__ApiLink5(Dialog,CreateIconCtrl,p1,p2,p3,p4,p5)
#define		Dialog_CreateImgCtrl(p1,p2,p3,p4,p5,p6,p7)	__ApiLink7(Dialog,CreateImgCtrl,p1,p2,p3,p4,p5,p6,p7)
#define		Dialog_CreateKeypadCtrl(p1,p2,p3,p4,p5,p6)	__ApiLink6(Dialog,CreateKeypadCtrl,p1,p2,p3,p4,p5,p6)
#define		Dialog_CreateLineCtrl(p1,p2,p3,p4,p5,p6)	__ApiLink6(Dialog,CreateLineCtrl,p1,p2,p3,p4,p5,p6)
#define		Dialog_CreateListCtrl(p1,p2,p3,p4,p5,p6)	__ApiLink6(Dialog,CreateListCtrl,p1,p2,p3,p4,p5,p6)
#define		Dialog_CreateRdoCtrl(p1,p2,p3,p4,p5,p6,p7,p8)	__ApiLink8(Dialog,CreateRdoCtrl,p1,p2,p3,p4,p5,p6,p7,p8)
#define		Dialog_CreateREditCtrl(p1,p2,p3,p4,p5,p6,p7)	__ApiLink7(Dialog,CreateREditCtrl,p1,p2,p3,p4,p5,p6,p7)
#define		Dialog_CreateREditCtrlEx(p1,p2,p3,p4,p5,p6,p7,p8)	__ApiLink8(Dialog,CreateREditCtrlEx,p1,p2,p3,p4,p5,p6,p7,p8)
#define		Dialog_CreateSelCtrl(p1,p2,p3,p4,p5,p6)		__ApiLink6(Dialog,CreateSelCtrl,p1,p2,p3,p4,p5,p6)
#define		Dialog_CreateTextCtrl(p1,p2,p3,p4,p5,p6,p7)	__ApiLink7(Dialog,CreateTextCtrl,p1,p2,p3,p4,p5,p6,p7)
#define		Dialog_CreateListView(p1,p2,p3,p4,p5,p6)	__ApiLink6(Dialog,CreateListView,p1,p2,p3,p4,p5,p6)
#define		Dialog_DestroyCtrl(p1,p2)					__ApiLink2(Dialog,DestroyCtrl,p1,p2)
#define		Dialog_DestroyAllCtrls(p1)					__ApiLink1(Dialog,DestroyAllCtrls,p1)
#define		Dialog_AttachCtrl(p1,p2,p3)					__ApiLink3(Dialog,AttachCtrl,p1,p2,p3)
#define 	Dialog_DettachCtrl(p1, p2)					__ApiLink2(Dialog,DettachCtrl,p1,p2)
#define		Dialog_SetSize(p1,p2,p3)					__ApiLink3(Dialog,SetSize,p1,p2,p3)
#define		Dialog_SetSoftMenu(p1,p2,p3,p4)				__ApiLink4(Dialog,SetSoftMenu,p1,p2,p3,p4)
#define		Dialog_SetScroll(p1,p2,p3)					__ApiLink3(Dialog,SetScroll,p1,p2,p3)
#define		Dialog_SetMoveKey(p1,p2,p3)					__ApiLink3(Dialog,SetMoveKey,p1,p2,p3)
#define		Dialog_GetScrollX(p1)						__ApiLink1(Dialog,GetScrollX,p1)
#define		Dialog_GetScrollY(p1)						__ApiLink1(Dialog,GetScrollY,p1)
#define		Dialog_GetActiveCtrl(p1)					__ApiLink1(Dialog,GetActiveCtrl,p1)
#define		Dialog_SetActiveCtrl(p1,p2)					__ApiLink2(Dialog,SetActiveCtrl,p1,p2)
#define		Dialog_MoveActiveCtrl(p1,p2)				__ApiLink2(Dialog,MoveActiveCtrl,p1,p2)
#define		Dialog_EnsureVisible(p1,p2)					__ApiLink2(Dialog,EnsureVisible,p1,p2)
#define		Dialog_ShowCursor(p1,p2)					__ApiLink2(Dialog,ShowCursor,p1,p2)
#define		Dialog_SetLocalOrigin(p1)					__ApiLink1(Dialog,SetLocalOrigin,p1)
#define		Dialog_DrawSoftMenu(p1,p2)					__ApiLink2(Dialog,DrawSoftMenu,p1,p2)
#define		Dialog_DoModal(p1,p2)						__ApiLink2(Dialog,DoModal,p1,p2)
#define		Dialog_StopModal()							__ApiLink0(Dialog,StopModal)
#define		Dialog_EndModal()							__ApiLink0(Dialog,EndModal)
#define		Dialog_GetScrollMaxY(p1)					__ApiLink1(Dialog,GetScrollMaxY,p1)
#define		Dialog_CreateTitleButCtrl(p1,p2,p3,p4,p5,p6,p7)	__ApiLink7(Dialog,CreateTitleButCtrl,p1,p2,p3,p4,p5,p6,p7)
#define		Dialog_SetSoftMenuIcon(p1,p2,p3,p4,p5,p6)	__ApiLink6(Dialog,SetSoftMenuIcon,p1,p2,p3,p4,p5,p6)

#endif	//	_BNSOFT__PEANUT_DIALOG_H_
