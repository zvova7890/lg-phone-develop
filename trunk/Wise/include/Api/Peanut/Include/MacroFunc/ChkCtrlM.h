/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	PEANUT CHECK CONTROL MACRO FUNCTIONS

	Copyright(c) 1997-2003 BNSoft Corp.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT_PEANUT_CHKCTRL_MACROFUNC_H_
#define		_BNSOFT_PEANUT_CHKCTRL_MACROFUNC_H_

//	ChkCtrl Macro Member Functions
#define		ChkCtrl_SetOwner(hC,O)				BaseCtrl_SetOwner         (hC,O)
#define		ChkCtrl_SetType(hC,T)				BaseCtrl_SetType          (hC,T)
#define		ChkCtrl_SetOemType(hC,T)			BaseCtrl_SetOemType       (hC,T)
#define		ChkCtrl_ModifyOemType(hC,R,A)			BaseCtrl_ModifyOemType    (hC,R,A)
#define		ChkCtrl_ModifyStyle(hC,R,A)			BaseCtrl_ModifyStyle      (hC,R,A)
#define		ChkCtrl_SetState(hC,S)				BaseCtrl_SetState         (hC,S)
#define		ChkCtrl_SetVisible(hC,O)			BaseCtrl_SetVisible       (hC,O)
#define		ChkCtrl_SetEnable(hC,O)				BaseCtrl_SetEnable        (hC,O)
#define		ChkCtrl_SetCanFocus(hC,O)			BaseCtrl_SetCanFocus      (hC,O)
#define		ChkCtrl_SetRange(hC,X1,Y1,X2,Y2)		BaseCtrl_SetRange         (hC,X1,Y1,X2,Y2)
#define		ChkCtrl_SetPos(hC,X,Y)				BaseCtrl_SetPos           (hC,X,Y)
#define		ChkCtrl_SetSize(hC,W,H)				BaseCtrl_SetSize          (hC,W,H)
#define		ChkCtrl_SetFont(hC,F)				BaseCtrl_SetFont          (hC,F)
#define		ChkCtrl_SetColorTbl(hC,pCT)			BaseCtrl_SetColorTbl      (hC,pCT)
#define		ChkCtrl_SetColor(hC,T,I,C)			BaseCtrl_SetColor         (hC,T,I,C)
#define		ChkCtrl_SetSysNotifyProc(hC,N)			BaseCtrl_SetSysNotifyProc (hC,N)
#define		ChkCtrl_SetAppNotifyProc(hC,I,M,N)		BaseCtrl_SetAppNotifyProc (hC,I,M,N)
#define		ChkCtrl_ModifyNotiMask(hC,R,A)			BaseCtrl_ModifyNotiMask   (hC,R,A)

#define		ChkCtrl_GetOwner(hC)				BaseCtrl_GetOwner         (hC)
#define		ChkCtrl_GetType(hC)				BaseCtrl_GetType          (hC)
#define		ChkCtrl_GetOemType(hC)				BaseCtrl_GetOemType       (hC)
#define		ChkCtrl_GetStyle(hC)				BaseCtrl_GetStyle         (hC)
#define		ChkCtrl_GetState(hC)				BaseCtrl_GetState         (hC)
#define		ChkCtrl_IsVisible(hC)				BaseCtrl_IsVisible        (hC)
#define		ChkCtrl_IsEnable(hC)				BaseCtrl_IsEnable         (hC)
#define		ChkCtrl_IsCanFocus(hC)				BaseCtrl_IsCanFocus       (hC)
#define		ChkCtrl_IsFocused(hC)				BaseCtrl_IsFocused        (hC)
#define		ChkCtrl_GetRange(hC)				BaseCtrl_GetRange         (hC)
#define		ChkCtrl_GetPosX(hC)				BaseCtrl_GetPosX          (hC)
#define		ChkCtrl_GetPosY(hC)				BaseCtrl_GetPosY          (hC)
#define		ChkCtrl_GetWidth(hC)				BaseCtrl_GetWidth         (hC)
#define		ChkCtrl_GetHeight(hC)				BaseCtrl_GetHeight        (hC)
#define		ChkCtrl_GetFont(hC)				BaseCtrl_GetFont          (hC)
#define		ChkCtrl_GetColorTbl(hC)				BaseCtrl_GetColorTbl      (hC)
#define		ChkCtrl_GetColor(hC,T,I)			BaseCtrl_GetColor         (hC,T,I)
#define		ChkCtrl_GetSysNotify(hC)			BaseCtrl_GetSysNotify     (hC)
#define		ChkCtrl_GetAppNotify(hC)			BaseCtrl_GetAppNotify     (hC)
#define		ChkCtrl_GetNotiMask(hC)				BaseCtrl_GetNotiMask      (hC)

#define		ChkCtrl_PtInRange(hC,X,Y)			BaseCtrl_PtInRange        (hC,X,Y)
#define		ChkCtrl_SetFocus(hC)				BaseCtrl_SetFocus         (hC)
#define		ChkCtrl_KillFocus(hC)				BaseCtrl_KillFocus        (hC)

#define		ChkCtrl_Handler(hC,M,W,L)			BaseCtrl_Handler          (hC,M,W,L)
#define		ChkCtrl_Refresh(hC)				BaseCtrl_Refresh          (hC)
#define		ChkCtrl_Paint(hC,R)				BaseCtrl_Paint            (hC,R)
#define		ChkCtrl_KeyDown(hC,K,R)				BaseCtrl_KeyDown          (hC,K,R)
#define		ChkCtrl_Timer(hC,R)				BaseCtrl_Timer            (hC,R)
#define		ChkCtrl_Pointing(hC,A,X,Y,R)			BaseCtrl_Pointing         (hC,A,X,Y,R)

#define		ChkCtrl_CreateDummyData(hC,N)			BaseCtrl_CreateDummyData  (hC,N)
#define		ChkCtrl_SetDummyData(hC,I,D)			BaseCtrl_SetDummyData     (hC,I,D)
#define		ChkCtrl_GetDummyData(hC,I)			BaseCtrl_GetDummyData     (hC,I)

#endif	//	_BNSOFT_PEANUT_CHKCTRL_MACROFUNC_H_
