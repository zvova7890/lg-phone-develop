/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	PEANUT DIALOG MACRO FUNCTIONS

	Copyright(c) 1997-2003 BNSoft Corp.

	그룹 : PEANUT
	구분 : CONTROL MACROFUNC
	등급 : 공개																						{{BNS_INTERNALCODE()}}
	버전 : 1.02
	일자 : 2003.06.10
	성명 : 박상호,임영일
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT_PEANUT_DIALOG_MACROFUNC_H_
#define		_BNSOFT_PEANUT_DIALOG_MACROFUNC_H_

//-------------------------------------------------------------------------------------------------
//	Dialog Macro Member Functions
#define		Dialog_SetOwner(hC,O)					FrmCtrl_SetOwner         (hC,O)
#define		Dialog_SetType(hC,T)					FrmCtrl_SetType          (hC,T)
#define		Dialog_SetOemType(hC,T)					FrmCtrl_SetOemType       (hC,T)
#define		Dialog_ModifyOemType(hC,R,A)			FrmCtrl_ModifyOemType    (hC,R,A)
//#define	Dialog_ModifyStyle(hC,R,A)				[OVERRIDDEN]
#define		Dialog_SetState(hC,S)					FrmCtrl_SetState         (hC,S)
#define		Dialog_SetVisible(hC,O)					FrmCtrl_SetVisible       (hC,O)
#define		Dialog_SetEnable(hC,O)					FrmCtrl_SetEnable        (hC,O)
#define		Dialog_SetCanFocus(hC,O)				FrmCtrl_SetCanFocus      (hC,O)
//#define	Dialog_SetRange(hC,X1,Y1,X2,Y2)			[OVERRIDDEN]
#define		Dialog_SetPos(hC,X,Y)					FrmCtrl_SetPos           (hC,X,Y)
//#define	Dialog_SetSize(hC,W,H)					[OVERRIDDEN]
#define		Dialog_SetFont(hC,F)					FrmCtrl_SetFont          (hC,F)
#define		Dialog_SetColorTbl(hC,pCT)				FrmCtrl_SetColorTbl      (hC,pCT)
#define		Dialog_SetColor(hC,T,I,C)				FrmCtrl_SetColor         (hC,T,I,C)
#define		Dialog_SetSysNotifyProc(hC,N)			FrmCtrl_SetSysNotifyProc (hC,N)
#define		Dialog_SetAppNotifyProc(hC,I,M,N)		FrmCtrl_SetAppNotifyProc (hC,I,M,N)
#define		Dialog_ModifyNotiMask(hC,R,A)			FrmCtrl_ModifyNotiMask   (hC,R,A)

#define		Dialog_GetOwner(hC)						FrmCtrl_GetOwner         (hC)
#define		Dialog_GetType(hC)						FrmCtrl_GetType          (hC)
#define		Dialog_GetOemType(hC)					FrmCtrl_GetOemType       (hC)
#define		Dialog_GetStyle(hC)						FrmCtrl_GetStyle         (hC)
#define		Dialog_GetState(hC)						FrmCtrl_GetState         (hC)
#define		Dialog_IsVisible(hC)					FrmCtrl_IsVisible        (hC)
#define		Dialog_IsEnable(hC)						FrmCtrl_IsEnable         (hC)
#define		Dialog_IsCanFocus(hC)					FrmCtrl_IsCanFocus       (hC)
#define		Dialog_IsFocused(hC)					FrmCtrl_IsFocused        (hC)
#define		Dialog_GetRange(hC)						FrmCtrl_GetRange         (hC)
#define		Dialog_GetPosX(hC)						FrmCtrl_GetPosX          (hC)
#define		Dialog_GetPosY(hC)						FrmCtrl_GetPosY          (hC)
#define		Dialog_GetWidth(hC)						FrmCtrl_GetWidth         (hC)
#define		Dialog_GetHeight(hC)					FrmCtrl_GetHeight        (hC)
#define		Dialog_GetFont(hC)						FrmCtrl_GetFont          (hC)
#define		Dialog_GetColorTbl(hC)					FrmCtrl_GetColorTbl      (hC)
#define		Dialog_GetColor(hC,T,I)					FrmCtrl_GetColor         (hC,T,I)
#define		Dialog_GetSysNotify(hC)					FrmCtrl_GetSysNotify     (hC)
#define		Dialog_GetAppNotify(hC)					FrmCtrl_GetAppNotify     (hC)
#define		Dialog_GetNotiMask(hC)					FrmCtrl_GetNotiMask      (hC)

#define		Dialog_PtInRange(hC,X,Y)				FrmCtrl_PtInRange        (hC,X,Y)
#define		Dialog_SetFocus(hC)						FrmCtrl_SetFocus         (hC)
#define		Dialog_KillFocus(hC)					FrmCtrl_KillFocus        (hC)

#define		Dialog_Handler(hC,M,W,L)				FrmCtrl_Handler          (hC,M,W,L)
#define		Dialog_Refresh(hC)						FrmCtrl_Refresh          (hC)
#define		Dialog_Paint(hC,R)						FrmCtrl_Paint            (hC,R)
#define		Dialog_KeyDown(hC,K,R)					FrmCtrl_KeyDown          (hC,K,R)
#define		Dialog_LongKeyDown(hC,K,R)				FrmCtrl_LongKeyDown      (hC,K,R)
#define		Dialog_Timer(hC,R)						FrmCtrl_Timer            (hC,R)
#define		Dialog_Pointing(hC,A,X,Y,R)				FrmCtrl_Pointing         (hC,A,X,Y,R)

#define		Dialog_CreateDummyData(hC,N)			FrmCtrl_CreateDummyData  (hC,N)
#define		Dialog_SetDummyData(hC,I,D)				FrmCtrl_SetDummyData     (hC,I,D)
#define		Dialog_GetDummyData(hC,I)				FrmCtrl_GetDummyData     (hC,I)

//-	- -	- -	- -	- -	- -	- -	- -	- -	- -	- -	- -	- -	- -	- -	- -	- -	- -	- -	- -	- -	- -	- -	- -	- -

#define		Dialog_SetClientRect(hC,X1,Y1,X2,Y2)	FrmCtrl_SetClientRect    (hC,X1,Y1,X2,Y2)
#define		Dialog_SetClientPos(hC,X,Y)				FrmCtrl_SetClientPos     (hC,X,Y)
#define		Dialog_SetClientSize(hC,W,H)			FrmCtrl_SetClientSize    (hC,W,H)
#define		Dialog_SetDelta(hC,X,Y)					FrmCtrl_SetDelta         (hC,X,Y)
#define		Dialog_SetDelta2(hC,X,Y)				FrmCtrl_SetDelta2        (hC,X,Y)
#define		Dialog_SetTitle(hC,T)					FrmCtrl_SetTitle         (hC,T)
#if defined (WISE_PEANUT_DUALSIM_SUPPORT)
#define 		Dialog_SetTitleIcon(hC,S1,S2)				FrmCtrl_SetTitleIcon(hC, S1,S2)
#define			Dialog_SetTitleColor(hC, S1)				FrmCtrl_SetTitleColor(hC, S1)
#endif
#define		Dialog_SetTitleFont(hC,F)				FrmCtrl_SetTitleFont     (hC,F)
#define		Dialog_SetTitleHeight(hC,H)				FrmCtrl_SetTitleHeight   (hC,H)
#define		Dialog_SetTitleLeftMargin(hC,X)			FrmCtrl_SetTitleLeftMargin(hC,X)
#define		Dialog_SetTitleRightMargin(hC,X)		FrmCtrl_SetTitleRightMargin(hC,X)
#define		Dialog_GetClientRect(hC)				FrmCtrl_GetClientRect    (hC)
#define		Dialog_GetClientPosX(hC)				FrmCtrl_GetClientPosX    (hC)
#define		Dialog_GetClientPosY(hC)				FrmCtrl_GetClientPosY    (hC)
#define		Dialog_GetClientWidth(hC)				FrmCtrl_GetClientWidth   (hC)
#define		Dialog_GetClientHeight(hC)				FrmCtrl_GetClientHeight  (hC)
#define		Dialog_GetWorkArea(hC)					FrmCtrl_GetWorkArea      (hC)
#define		Dialog_GetWorkPosX(hC)					FrmCtrl_GetWorkPosX      (hC)
#define		Dialog_GetWorkPosY(hC)					FrmCtrl_GetWorkPosY      (hC)
#define		Dialog_GetWorkWidth(hC)					FrmCtrl_GetWorkWidth     (hC)
#define		Dialog_GetWorkHeight(hC)				FrmCtrl_GetWorkHeight    (hC)
#define		Dialog_GetDeltaX1(hC)					FrmCtrl_GetDeltaX1       (hC)
#define		Dialog_GetDeltaY1(hC)					FrmCtrl_GetDeltaY1       (hC)
#define		Dialog_GetDeltaX2(hC)					FrmCtrl_GetDeltaX2       (hC)
#define		Dialog_GetDeltaY2(hC)					FrmCtrl_GetDeltaY2       (hC)
#define		Dialog_GetTitle(hC)						FrmCtrl_GetTitle         (hC)
#define		Dialog_GetTitleFont(hC)					FrmCtrl_GetTitleFont     (hC)
#define		Dialog_GetTitleHeight(hC)				FrmCtrl_GetTitleHeight   (hC)
#define		Dialog_GetTitleLeftMargin(hC)			FrmCtrl_GetTitleLeftMargin(hC)
#define		Dialog_GetTitleRightMargin(hC)			FrmCtrl_GetTitleRightMargin(hC)

#define		Dialog_AdjustRange(hC)					FrmCtrl_AdjustRange      (hC)
#define		Dialog_AdjustClientRect(hC)				FrmCtrl_AdjustClientRect (hC)
#define		Dialog_AdjustScrollBar(hC)				FrmCtrl_AdjustScrollBar  (hC)
#define		Dialog_PtInClientRect(hC,X,Y)			FrmCtrl_PtInClientRect   (hC,X,Y)

//-------------------------------------------------------------------------------------------------

#endif	//	_BNSOFT_PEANUT_DIALOG_MACROFUNC_H_
