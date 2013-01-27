/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	PEANUT BUTTON CONTROL MACRO FUNCTIONS

	Copyright(c) 1997-2003 BNSoft Corp.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT_PEANUT_BUTCTRL_MACROFUNC_H_
#define		_BNSOFT_PEANUT_BUTCTRL_MACROFUNC_H_

//	ButCtrl Macro Member Functions
#define		ButCtrl_SetOwner(hC,O)					BaseCtrl_SetOwner         (hC,O)
#define		ButCtrl_SetType(hC,T)					BaseCtrl_SetType          (hC,T)
#define		ButCtrl_SetOemType(hC,T)				BaseCtrl_SetOemType       (hC,T)
#define		ButCtrl_ModifyOemType(hC,R,A)			BaseCtrl_ModifyOemType    (hC,R,A)
#define		ButCtrl_ModifyStyle(hC,R,A)				BaseCtrl_ModifyStyle      (hC,R,A)
#define		ButCtrl_SetState(hC,S)					BaseCtrl_SetState         (hC,S)
#define		ButCtrl_SetVisible(hC,O)				BaseCtrl_SetVisible       (hC,O)
#define		ButCtrl_SetEnable(hC,O)					BaseCtrl_SetEnable        (hC,O)
#define		ButCtrl_SetCanFocus(hC,O)				BaseCtrl_SetCanFocus      (hC,O)
#define		ButCtrl_SetRange(hC,X1,Y1,X2,Y2)		BaseCtrl_SetRange         (hC,X1,Y1,X2,Y2)
#define		ButCtrl_SetPos(hC,X,Y)					BaseCtrl_SetPos           (hC,X,Y)
#define		ButCtrl_SetSize(hC,W,H)					BaseCtrl_SetSize          (hC,W,H)
#define		ButCtrl_SetFont(hC,F)					BaseCtrl_SetFont          (hC,F)
#define		ButCtrl_SetColorTbl(hC,pCT)				BaseCtrl_SetColorTbl      (hC,pCT)
#define		ButCtrl_SetColor(hC,T,I,C)				BaseCtrl_SetColor         (hC,T,I,C)
#define		ButCtrl_SetSysNotifyProc(hC,N)			BaseCtrl_SetSysNotifyProc (hC,N)
#define		ButCtrl_SetAppNotifyProc(hC,I,M,N)		BaseCtrl_SetAppNotifyProc (hC,I,M,N)
#define		ButCtrl_ModifyNotiMask(hC,R,A)			BaseCtrl_ModifyNotiMask   (hC,R,A)

#define		ButCtrl_GetOwner(hC)					BaseCtrl_GetOwner         (hC)
#define		ButCtrl_GetType(hC)						BaseCtrl_GetType          (hC)
#define		ButCtrl_GetOemType(hC)					BaseCtrl_GetOemType       (hC)
#define		ButCtrl_GetStyle(hC)					BaseCtrl_GetStyle         (hC)
#define		ButCtrl_GetState(hC)					BaseCtrl_GetState         (hC)
#define		ButCtrl_IsVisible(hC)					BaseCtrl_IsVisible        (hC)
#define		ButCtrl_IsEnable(hC)					BaseCtrl_IsEnable         (hC)
#define		ButCtrl_IsCanFocus(hC)					BaseCtrl_IsCanFocus       (hC)
#define		ButCtrl_IsFocused(hC)					BaseCtrl_IsFocused        (hC)
#define		ButCtrl_GetRange(hC)					BaseCtrl_GetRange         (hC)
#define		ButCtrl_GetPosX(hC)						BaseCtrl_GetPosX          (hC)
#define		ButCtrl_GetPosY(hC)						BaseCtrl_GetPosY          (hC)
#define		ButCtrl_GetWidth(hC)					BaseCtrl_GetWidth         (hC)
#define		ButCtrl_GetHeight(hC)					BaseCtrl_GetHeight        (hC)
#define		ButCtrl_GetFont(hC)						BaseCtrl_GetFont          (hC)
#define		ButCtrl_GetColorTbl(hC)					BaseCtrl_GetColorTbl      (hC)
#define		ButCtrl_GetColor(hC,T,I)				BaseCtrl_GetColor         (hC,T,I)
#define		ButCtrl_GetSysNotify(hC)				BaseCtrl_GetSysNotify     (hC)
#define		ButCtrl_GetAppNotify(hC)				BaseCtrl_GetAppNotify     (hC)
#define		ButCtrl_GetNotiMask(hC)					BaseCtrl_GetNotiMask      (hC)

#define		ButCtrl_PtInRange(hC,X,Y)				BaseCtrl_PtInRange        (hC,X,Y)
#define		ButCtrl_SetFocus(hC)					BaseCtrl_SetFocus         (hC)
#define		ButCtrl_KillFocus(hC)					BaseCtrl_KillFocus        (hC)

#define		ButCtrl_Handler(hC,M,W,L)				BaseCtrl_Handler          (hC,M,W,L)
#define		ButCtrl_Refresh(hC)						BaseCtrl_Refresh          (hC)
#define		ButCtrl_Paint(hC,R)						BaseCtrl_Paint            (hC,R)
#define		ButCtrl_KeyDown(hC,K,R)					BaseCtrl_KeyDown          (hC,K,R)
#define		ButCtrl_Timer(hC,R)						BaseCtrl_Timer            (hC,R)
#define		ButCtrl_Pointing(hC,A,X,Y,R)			BaseCtrl_Pointing         (hC,A,X,Y,R)

#define		ButCtrl_CreateDummyData(hC,N)			BaseCtrl_CreateDummyData  (hC,N)
#define		ButCtrl_SetDummyData(hC,I,D)			BaseCtrl_SetDummyData     (hC,I,D)
#define		ButCtrl_GetDummyData(hC,I)				BaseCtrl_GetDummyData     (hC,I)


#endif	//	_BNSOFT_PEANUT_BUTCTRL_MACROFUNC_H_
