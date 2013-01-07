/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	PEANUT FRAME CONTROL MACRO FUNCTIONS

	Copyright(c) 1997-2003 BNSoft Corp.

	그룹 : PEANUT
	구분 : CONTROL MACROFUNC
	등급 : 공개																						{{BNS_INTERNALCODE()}}
	버전 : 1.02
	일자 : 2003.04.08
	성명 : 박상호
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT_PEANUT_FRMCTRL_MACROFUNC_H_
#define		_BNSOFT_PEANUT_FRMCTRL_MACROFUNC_H_

//-------------------------------------------------------------------------------------------------
//	FrmCtrl Macro Member Functions
#define		FrmCtrl_SetOwner(hC,O)					BaseCtrl_SetOwner         (hC,O)
#define		FrmCtrl_SetType(hC,T)					BaseCtrl_SetType          (hC,T)
#define		FrmCtrl_SetOemType(hC,T)				BaseCtrl_SetOemType       (hC,T)
#define		FrmCtrl_ModifyOemType(hC,R,A)			BaseCtrl_ModifyOemType    (hC,R,A)
//#define	FrmCtrl_ModifyStyle(hC,R,A)				[OVERRIDDEN]
#define		FrmCtrl_SetState(hC,S)					BaseCtrl_SetState         (hC,S)
#define		FrmCtrl_SetVisible(hC,O)				BaseCtrl_SetVisible       (hC,O)
#define		FrmCtrl_SetEnable(hC,O)					BaseCtrl_SetEnable        (hC,O)
#define		FrmCtrl_SetCanFocus(hC,O)				BaseCtrl_SetCanFocus      (hC,O)
//#define	FrmCtrl_SetRange(hC,X1,Y1,X2,Y2)		[OVERRIDDEN]
//#define	FrmCtrl_SetPos(hC,X,Y)					[OVERRIDDEN]
//#define	FrmCtrl_SetSize(hC,W,H)					[OVERRIDDEN]
#define		FrmCtrl_SetFont(hC,F)					BaseCtrl_SetFont          (hC,F)
#define		FrmCtrl_SetColorTbl(hC,pCT)				BaseCtrl_SetColorTbl      (hC,pCT)
#define		FrmCtrl_SetColor(hC,T,I,C)				BaseCtrl_SetColor         (hC,T,I,C)
#define		FrmCtrl_SetSysNotifyProc(hC,N)			BaseCtrl_SetSysNotifyProc (hC,N)
#define		FrmCtrl_SetAppNotifyProc(hC,I,M,N)		BaseCtrl_SetAppNotifyProc (hC,I,M,N)
#define		FrmCtrl_ModifyNotiMask(hC,R,A)			BaseCtrl_ModifyNotiMask   (hC,R,A)

#define		FrmCtrl_GetOwner(hC)					BaseCtrl_GetOwner         (hC)
#define		FrmCtrl_GetType(hC)						BaseCtrl_GetType          (hC)
#define		FrmCtrl_GetOemType(hC)					BaseCtrl_GetOemType       (hC)
#define		FrmCtrl_GetStyle(hC)					BaseCtrl_GetStyle         (hC)
#define		FrmCtrl_GetState(hC)					BaseCtrl_GetState         (hC)
#define		FrmCtrl_IsVisible(hC)					BaseCtrl_IsVisible        (hC)
#define		FrmCtrl_IsEnable(hC)					BaseCtrl_IsEnable         (hC)
#define		FrmCtrl_IsCanFocus(hC)					BaseCtrl_IsCanFocus       (hC)
#define		FrmCtrl_IsFocused(hC)					BaseCtrl_IsFocused        (hC)
#define		FrmCtrl_GetRange(hC)					BaseCtrl_GetRange         (hC)
#define		FrmCtrl_GetPosX(hC)						BaseCtrl_GetPosX          (hC)
#define		FrmCtrl_GetPosY(hC)						BaseCtrl_GetPosY          (hC)
#define		FrmCtrl_GetWidth(hC)					BaseCtrl_GetWidth         (hC)
#define		FrmCtrl_GetHeight(hC)					BaseCtrl_GetHeight        (hC)
#define		FrmCtrl_GetFont(hC)						BaseCtrl_GetFont          (hC)
#define		FrmCtrl_GetColorTbl(hC)					BaseCtrl_GetColorTbl      (hC)
#define		FrmCtrl_GetColor(hC,T,I)				BaseCtrl_GetColor         (hC,T,I)
#define		FrmCtrl_GetSysNotify(hC)				BaseCtrl_GetSysNotify     (hC)
#define		FrmCtrl_GetAppNotify(hC)				BaseCtrl_GetAppNotify     (hC)
#define		FrmCtrl_GetNotiMask(hC)					BaseCtrl_GetNotiMask      (hC)

#define		FrmCtrl_PtInRange(hC,X,Y)				BaseCtrl_PtInRange        (hC,X,Y)
#define		FrmCtrl_SetFocus(hC)					BaseCtrl_SetFocus         (hC)
#define		FrmCtrl_KillFocus(hC)					BaseCtrl_KillFocus        (hC)

#define		FrmCtrl_Handler(hC,M,W,L)				BaseCtrl_Handler          (hC,M,W,L)
#define		FrmCtrl_Refresh(hC)						BaseCtrl_Refresh          (hC)
#define		FrmCtrl_Paint(hC,R)						BaseCtrl_Paint            (hC,R)
#define		FrmCtrl_KeyDown(hC,K,R)					BaseCtrl_KeyDown          (hC,K,R)
#define		FrmCtrl_LongKeyDown(hC,K,R)				BaseCtrl_LongKeyDown      (hC,K,R)
#define		FrmCtrl_Timer(hC,R)						BaseCtrl_Timer            (hC,R)
#define		FrmCtrl_Pointing(hC,A,X,Y,R)			BaseCtrl_Pointing         (hC,A,X,Y,R)

#define		FrmCtrl_CreateDummyData(hC,N)			BaseCtrl_CreateDummyData  (hC,N)
#define		FrmCtrl_SetDummyData(hC,I,D)			BaseCtrl_SetDummyData     (hC,I,D)
#define		FrmCtrl_GetDummyData(hC,I)				BaseCtrl_GetDummyData     (hC,I)

//-------------------------------------------------------------------------------------------------

#endif	//	_BNSOFT_PEANUT_FRMCTRL_MACROFUNC_H_
