/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	PEANUT EDIT CONTROL MACRO FUNCTIONS

	Copyright(c) 1997-2003 BNSoft Corp.

	그룹 : PEANUT
	구분 : CONTROL MACROFUNC
	등급 : 공개																						{{BNS_INTERNALCODE()}}
	버전 : 1.03
	일자 : 2005.03.23
	성명 : 박상호,임영일,길령환,이택길
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT_PEANUT_REDITCTRL_MACROFUNC_H_
#define		_BNSOFT_PEANUT_REDITCTRL_MACROFUNC_H_

//-------------------------------------------------------------------------------------------------
//	REditCtrl Macro Member Functions
#define		REditCtrl_SetOwner(hC,O)				FrmCtrl_SetOwner         (hC,O)
#define		REditCtrl_SetType(hC,T)					FrmCtrl_SetType          (hC,T)
#define		REditCtrl_SetOemType(hC,T)				FrmCtrl_SetOemType       (hC,T)
#define		REditCtrl_ModifyOemType(hC,R,A)			FrmCtrl_ModifyOemType    (hC,R,A)
#define		REditCtrl_ModifyStyle(hC,R,A)			FrmCtrl_ModifyStyle      (hC,R,A)
#define		REditCtrl_SetState(hC,S)				FrmCtrl_SetState         (hC,S)
#define		REditCtrl_SetVisible(hC,O)				FrmCtrl_SetVisible       (hC,O)
#define		REditCtrl_SetEnable(hC,O)				FrmCtrl_SetEnable        (hC,O)
#define		REditCtrl_SetCanFocus(hC,O)				FrmCtrl_SetCanFocus      (hC,O)
#define		REditCtrl_SetRange(hC,X1,Y1,X2,Y2)		FrmCtrl_SetRange         (hC,X1,Y1,X2,Y2)
#define		REditCtrl_SetPos(hC,X,Y)				FrmCtrl_SetPos           (hC,X,Y)
#define		REditCtrl_SetSize(hC,W,H)				FrmCtrl_SetSize          (hC,W,H)
//-------------------------------------------------------------------------------------------------
//	Rich는 BaseCtrl의 Font를 사용하지 않는다. 매크로를 다음과 같이 수정 한다.
#define		REditCtrl_SetFont(hC,F)					{																			\
														REditCtrl_SetDefCharFont	(hC,F);										\
														REditCtrl_SetFontEx			(hC,F,0,REditCtrl_GetStrLen(hC));			\
														FrmCtrl_SetFont				(hC,F);										\
													}
//-------------------------------------------------------------------------------------------------
#define		REditCtrl_SetColorTbl(hC,pCT)			{																			\
														FrmCtrl_SetColorTbl			(hC,pCT);									\
														REditCtrl_SetDefCharColor	(hC,pCT->FocusedCL[REDITCOL_FOREGROUND]);	\
														REditCtrl_SetColorEx		(hC,pCT->FocusedCL[REDITCOL_FOREGROUND],0,REditCtrl_GetStrLen(hC));			\
													}
//-------------------------------------------------------------------------------------------------
#define		REditCtrl_SetColor(hC,T,I,C)			{																			\
														FrmCtrl_SetColor			(hC,T,I,C);									\
														{																		\
															REditCtrl_SetDefCharColor	(hC,C);									\
														}																		\
													}
//-------------------------------------------------------------------------------------------------
#define		REditCtrl_SetSysNotifyProc(hC,N)		FrmCtrl_SetSysNotifyProc (hC,N)
#define		REditCtrl_SetAppNotifyProc(hC,I,M,N)	FrmCtrl_SetAppNotifyProc (hC,I,M,N)
#define		REditCtrl_ModifyNotiMask(hC,R,A)		FrmCtrl_ModifyNotiMask   (hC,R,A)

#define		REditCtrl_GetOwner(hC)					FrmCtrl_GetOwner         (hC)
#define		REditCtrl_GetType(hC)					FrmCtrl_GetType          (hC)
#define		REditCtrl_GetOemType(hC)				FrmCtrl_GetOemType       (hC)
#define		REditCtrl_GetStyle(hC)					FrmCtrl_GetStyle         (hC)
#define		REditCtrl_GetState(hC)					FrmCtrl_GetState         (hC)
#define		REditCtrl_IsVisible(hC)					FrmCtrl_IsVisible        (hC)
#define		REditCtrl_IsEnable(hC)					FrmCtrl_IsEnable         (hC)
#define		REditCtrl_IsCanFocus(hC)				FrmCtrl_IsCanFocus       (hC)
#define		REditCtrl_IsFocused(hC)					FrmCtrl_IsFocused        (hC)
#define		REditCtrl_GetRange(hC)					FrmCtrl_GetRange         (hC)
#define		REditCtrl_GetPosX(hC)					FrmCtrl_GetPosX          (hC)
#define		REditCtrl_GetPosY(hC)					FrmCtrl_GetPosY          (hC)
#define		REditCtrl_GetWidth(hC)					FrmCtrl_GetWidth         (hC)
#define		REditCtrl_GetHeight(hC)					FrmCtrl_GetHeight        (hC)
//@#define		REditCtrl_GetFont(hC)					FrmCtrl_GetFont          (hC)
#define		REditCtrl_GetColorTbl(hC)				FrmCtrl_GetColorTbl      (hC)
//@#define		REditCtrl_GetColor(hC,T,I)				FrmCtrl_GetColor         (hC,T,I)
#define		REditCtrl_GetSysNotify(hC)				FrmCtrl_GetSysNotify     (hC)
#define		REditCtrl_GetAppNotify(hC)				FrmCtrl_GetAppNotify     (hC)
#define		REditCtrl_GetNotiMask(hC)				FrmCtrl_GetNotiMask      (hC)

#define		REditCtrl_PtInRange(hC,X,Y)				FrmCtrl_PtInRange        (hC,X,Y)
#define		REditCtrl_SetFocus(hC)					FrmCtrl_SetFocus         (hC)
#define		REditCtrl_KillFocus(hC)					FrmCtrl_KillFocus        (hC)

#define		REditCtrl_Handler(hC,M,W,L)				FrmCtrl_Handler          (hC,M,W,L)
#define		REditCtrl_Refresh(hC)					FrmCtrl_Refresh          (hC)
#define		REditCtrl_Paint(hC,R)					FrmCtrl_Paint            (hC,R)
#define		REditCtrl_KeyDown(hC,K,R)				FrmCtrl_KeyDown          (hC,K,R)
#define		REditCtrl_LongKeyDown(hC,K,R)			FrmCtrl_LongKeyDown      (hC,K,R)
#define		REditCtrl_Timer(hC,R)					FrmCtrl_Timer            (hC,R)
#define		REditCtrl_Pointing(hC,A,X,Y,R)			FrmCtrl_Pointing         (hC,A,X,Y,R)

#define		REditCtrl_CreateDummyData(hC,N)			FrmCtrl_CreateDummyData  (hC,N)
#define		REditCtrl_SetDummyData(hC,I,D)			FrmCtrl_SetDummyData     (hC,I,D)
#define		REditCtrl_GetDummyData(hC,I)			FrmCtrl_GetDummyData     (hC,I)

//-	- -	- -	- -	- -	- -	- -	- -	- -	- -	- -	- -	- -	- -	- -	- -	- -	- -	- -	- -	- -	- -	- -	- -	- -

#define		REditCtrl_SetClientRect(hC,X1,Y1,X2,Y2)	FrmCtrl_SetClientRect    (hC,X1,Y1,X2,Y2)
#define		REditCtrl_SetClientPos(hC,X,Y)			FrmCtrl_SetClientPos     (hC,X,Y)
#define		REditCtrl_SetClientSize(hC,W,H)			FrmCtrl_SetClientSize    (hC,W,H)
#define		REditCtrl_SetDelta(hC,X,Y)				FrmCtrl_SetDelta         (hC,X,Y)
#define		REditCtrl_SetDelta2(hC,X,Y)				FrmCtrl_SetDelta2        (hC,X,Y)
#define		REditCtrl_SetTitle(hC,T)				FrmCtrl_SetTitle         (hC,T)
#if defined (WISE_PEANUT_DUALSIM_SUPPORT)
#define 		REditCtrl_SetTitleIcon(hC,S1,S2)				FrmCtrl_SetTitleIcon(hC, S1,S2)
#endif

#define		REditCtrl_SetTitleFont(hC,F)			FrmCtrl_SetTitleFont     (hC,F)
#define		REditCtrl_SetTitleHeight(hC,H)			FrmCtrl_SetTitleHeight   (hC,H)
#define		REditCtrl_SetTitleLeftMargin(hC,X)		FrmCtrl_SetTitleLeftMargin(hC,X)
#define		REditCtrl_SetTitleRightMargin(hC,X)		FrmCtrl_SetTitleRightMargin(hC,X)

#define		REditCtrl_GetClientRect(hC)				FrmCtrl_GetClientRect    (hC)
#define		REditCtrl_GetClientPosX(hC)				FrmCtrl_GetClientPosX    (hC)
#define		REditCtrl_GetClientPosY(hC)				FrmCtrl_GetClientPosY    (hC)
#define		REditCtrl_GetClientWidth(hC)			FrmCtrl_GetClientWidth   (hC)
#define		REditCtrl_GetClientHeight(hC)			FrmCtrl_GetClientHeight  (hC)
#define		REditCtrl_GetWorkArea(hC)				FrmCtrl_GetWorkArea      (hC)
#define		REditCtrl_GetWorkPosX(hC)				FrmCtrl_GetWorkPosX      (hC)
#define		REditCtrl_GetWorkPosY(hC)				FrmCtrl_GetWorkPosY      (hC)
#define		REditCtrl_GetWorkWidth(hC)				FrmCtrl_GetWorkWidth     (hC)
#define		REditCtrl_GetWorkHeight(hC)				FrmCtrl_GetWorkHeight    (hC)
#define		REditCtrl_GetDeltaX1(hC)				FrmCtrl_GetDeltaX1       (hC)
#define		REditCtrl_GetDeltaY1(hC)				FrmCtrl_GetDeltaY1       (hC)
#define		REditCtrl_GetDeltaX2(hC)				FrmCtrl_GetDeltaX2       (hC)
#define		REditCtrl_GetDeltaY2(hC)				FrmCtrl_GetDeltaY2       (hC)
#define		REditCtrl_GetTitle(hC)					FrmCtrl_GetTitle         (hC)
#define		REditCtrl_GetTitleFont(hC)				FrmCtrl_GetTitleFont     (hC)
#define		REditCtrl_GetTitleHeight(hC)			FrmCtrl_GetTitleHeight   (hC)
#define		REditCtrl_GetTitleLeftMargin(hC)		FrmCtrl_GetTitleLeftMargin(hC)
#define		REditCtrl_GetTitleRightMargin(hC)		FrmCtrl_GetTitleRightMargin(hC)

#define		REditCtrl_AdjustRange(hC)				FrmCtrl_AdjustRange      (hC)
#define		REditCtrl_AdjustClientRect(hC)			FrmCtrl_AdjustClientRect (hC)
#define		REditCtrl_AdjustScrollBar(hC)			FrmCtrl_AdjustScrollBar  (hC)
#define		REditCtrl_PtInClientRect(hC,X,Y)		FrmCtrl_PtInClientRect   (hC,X,Y)

//-------------------------------------------------------------------------------------------------

#endif	//	_BNSOFT_PEANUT_REDITCTRL_MACROFUNC_H_
