/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	PEANUT SELECT CONTROL MACRO FUNCTIONS

	Copyright(c) 1997-2003 BNSoft Corp.

	그룹 : PEANUT
	구분 : CONTROL MACROFUNC
	등급 : 공개																						{{BNS_INTERNALCODE()}}
	버전 : 1.02
	일자 : 2003.06.10
	성명 : 이동화,박상호,임영일
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT_PEANUT_SELCTRL_MACROFUNC_H_
#define		_BNSOFT_PEANUT_SELCTRL_MACROFUNC_H_

//-------------------------------------------------------------------------------------------------
//	SelCtrl Macro Member Functions
#define		SelCtrl_SetOwner(hC,O)					BaseCtrl_SetOwner         (hC,O)
#define		SelCtrl_SetType(hC,T)					BaseCtrl_SetType          (hC,T)
#define		SelCtrl_SetOemType(hC,T)				BaseCtrl_SetOemType       (hC,T)
#define		SelCtrl_ModifyOemType(hC,R,A)			BaseCtrl_ModifyOemType    (hC,R,A)
#define		SelCtrl_ModifyStyle(hC,R,A)				BaseCtrl_ModifyStyle      (hC,R,A)
#define		SelCtrl_SetState(hC,S)					BaseCtrl_SetState         (hC,S)
#define		SelCtrl_SetVisible(hC,O)				BaseCtrl_SetVisible       (hC,O)
#define		SelCtrl_SetEnable(hC,O)					BaseCtrl_SetEnable        (hC,O)
#define		SelCtrl_SetCanFocus(hC,O)				BaseCtrl_SetCanFocus      (hC,O)
#define		SelCtrl_SetRange(hC,X1,Y1,X2,Y2)		BaseCtrl_SetRange         (hC,X1,Y1,X2,Y2)
#define		SelCtrl_SetPos(hC,X,Y)					BaseCtrl_SetPos           (hC,X,Y)
#define		SelCtrl_SetSize(hC,W,H)					BaseCtrl_SetSize          (hC,W,H)
#define		SelCtrl_SetFont(hC,F)					BaseCtrl_SetFont          (hC,F)
#define		SelCtrl_SetColorTbl(hC,pCT)				BaseCtrl_SetColorTbl      (hC,pCT)
#define		SelCtrl_SetColor(hC,T,I,C)				BaseCtrl_SetColor         (hC,T,I,C)
#define		SelCtrl_SetSysNotifyProc(hC,N)			BaseCtrl_SetSysNotifyProc (hC,N)
#define		SelCtrl_SetAppNotifyProc(hC,I,M,N)		BaseCtrl_SetAppNotifyProc (hC,I,M,N)
#define		SelCtrl_ModifyNotiMask(hC,R,A)			BaseCtrl_ModifyNotiMask   (hC,R,A)

#define		SelCtrl_GetOwner(hC)					BaseCtrl_GetOwner         (hC)
#define		SelCtrl_GetType(hC)						BaseCtrl_GetType          (hC)
#define		SelCtrl_GetOemType(hC)					BaseCtrl_GetOemType       (hC)
#define		SelCtrl_GetStyle(hC)					BaseCtrl_GetStyle         (hC)
#define		SelCtrl_GetState(hC)					BaseCtrl_GetState         (hC)
#define		SelCtrl_IsVisible(hC)					BaseCtrl_IsVisible        (hC)
#define		SelCtrl_IsEnable(hC)					BaseCtrl_IsEnable         (hC)
#define		SelCtrl_IsCanFocus(hC)					BaseCtrl_IsCanFocus       (hC)
#define		SelCtrl_IsFocused(hC)					BaseCtrl_IsFocused        (hC)
#define		SelCtrl_GetRange(hC)					BaseCtrl_GetRange         (hC)
#define		SelCtrl_GetPosX(hC)						BaseCtrl_GetPosX          (hC)
#define		SelCtrl_GetPosY(hC)						BaseCtrl_GetPosY          (hC)
#define		SelCtrl_GetWidth(hC)					BaseCtrl_GetWidth         (hC)
#define		SelCtrl_GetHeight(hC)					BaseCtrl_GetHeight        (hC)
#define		SelCtrl_GetFont(hC)						BaseCtrl_GetFont          (hC)
#define		SelCtrl_GetColorTbl(hC)					BaseCtrl_GetColorTbl      (hC)
#define		SelCtrl_GetColor(hC,T,I)				BaseCtrl_GetColor         (hC,T,I)
#define		SelCtrl_GetSysNotify(hC)				BaseCtrl_GetSysNotify     (hC)
#define		SelCtrl_GetAppNotify(hC)				BaseCtrl_GetAppNotify     (hC)
#define		SelCtrl_GetNotiMask(hC)					BaseCtrl_GetNotiMask      (hC)

#define		SelCtrl_PtInRange(hC,X,Y)				BaseCtrl_PtInRange        (hC,X,Y)

#define		SelCtrl_Handler(hC,M,W,L)				BaseCtrl_Handler          (hC,M,W,L)
#define		SelCtrl_Refresh(hC)						BaseCtrl_Refresh          (hC)
#define		SelCtrl_Paint(hC,R)						BaseCtrl_Paint            (hC,R)
#define		SelCtrl_KeyDown(hC,K,R)					BaseCtrl_KeyDown          (hC,K,R)
#define		SelCtrl_Timer(hC,R)						BaseCtrl_Timer            (hC,R)
#define		SelCtrl_Pointing(hC,A,X,Y,R)			BaseCtrl_Pointing         (hC,A,X,Y,R)

#define		SelCtrl_CreateDummyData(hC,N)			BaseCtrl_CreateDummyData  (hC,N)
#define		SelCtrl_SetDummyData(hC,I,D)			BaseCtrl_SetDummyData     (hC,I,D)
#define		SelCtrl_GetDummyData(hC,I)				BaseCtrl_GetDummyData     (hC,I)

//-------------------------------------------------------------------------------------------------

#endif	//	_BNSOFT_PEANUT_SELCTRL_MACROFUNC_H_
