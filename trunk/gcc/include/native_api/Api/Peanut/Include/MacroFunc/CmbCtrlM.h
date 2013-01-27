/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	PEANUT COMBO CONTROL MACRO FUNCTIONS

	Copyright(c) 1997-2003 BNSoft Corp.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT_PEANUT_CMBCTRL_MACROFUNC_H_
#define		_BNSOFT_PEANUT_CMBCTRL_MACROFUNC_H_

#define		CmbCtrl_SetOwner(hC,O)				BaseCtrl_SetOwner         (hC,O)
#define		CmbCtrl_SetType(hC,T)				BaseCtrl_SetType          (hC,T)
#define		CmbCtrl_SetOemType(hC,T)			BaseCtrl_SetOemType       (hC,T)
#define		CmbCtrl_ModifyOemType(hC,R,A)			BaseCtrl_ModifyOemType    (hC,R,A)
#define		CmbCtrl_SetState(hC,S)				BaseCtrl_SetState         (hC,S)
#define		CmbCtrl_SetVisible(hC,O)			BaseCtrl_SetVisible       (hC,O)
#define		CmbCtrl_SetEnable(hC,O)				BaseCtrl_SetEnable        (hC,O)
#define		CmbCtrl_SetCanFocus(hC,O)			BaseCtrl_SetCanFocus      (hC,O)

#define		CmbCtrl_SetFont(hC,F)				BaseCtrl_SetFont          (hC,F)
#define		CmbCtrl_SetColorTbl(hC,pCT)			BaseCtrl_SetColorTbl      (hC,pCT)
#define		CmbCtrl_SetColor(hC,T,I,C)			BaseCtrl_SetColor         (hC,T,I,C)
#define		CmbCtrl_SetSysNotifyProc(hC,N)			BaseCtrl_SetSysNotifyProc (hC,N)
#define		CmbCtrl_SetAppNotifyProc(hC,I,M,N)		BaseCtrl_SetAppNotifyProc (hC,I,M,N)
#define		CmbCtrl_ModifyNotiMask(hC,R,A)			BaseCtrl_ModifyNotiMask   (hC,R,A)

#define		CmbCtrl_GetOwner(hC)				BaseCtrl_GetOwner         (hC)
#define		CmbCtrl_GetType(hC)				BaseCtrl_GetType          (hC)
#define		CmbCtrl_GetOemType(hC)				BaseCtrl_GetOemType       (hC)
#define		CmbCtrl_GetStyle(hC)				BaseCtrl_GetStyle         (hC)
#define		CmbCtrl_GetState(hC)				BaseCtrl_GetState         (hC)
#define		CmbCtrl_IsVisible(hC)				BaseCtrl_IsVisible        (hC)
#define		CmbCtrl_IsEnable(hC)				BaseCtrl_IsEnable         (hC)
#define		CmbCtrl_IsCanFocus(hC)				BaseCtrl_IsCanFocus       (hC)
#define		CmbCtrl_IsFocused(hC)				BaseCtrl_IsFocused        (hC)
#define		CmbCtrl_GetRange(hC)				BaseCtrl_GetRange         (hC)
#define		CmbCtrl_GetPosX(hC)				BaseCtrl_GetPosX          (hC)
#define		CmbCtrl_GetPosY(hC)				BaseCtrl_GetPosY          (hC)
#define		CmbCtrl_GetWidth(hC)				BaseCtrl_GetWidth         (hC)
#define		CmbCtrl_GetHeight(hC)				BaseCtrl_GetHeight        (hC)
#define		CmbCtrl_GetFont(hC)				BaseCtrl_GetFont          (hC)
#define		CmbCtrl_GetColorTbl(hC)				BaseCtrl_GetColorTbl      (hC)
#define		CmbCtrl_GetColor(hC,T,I)			BaseCtrl_GetColor         (hC,T,I)
#define		CmbCtrl_GetSysNotify(hC)			BaseCtrl_GetSysNotify     (hC)
#define		CmbCtrl_GetAppNotify(hC)			BaseCtrl_GetAppNotify     (hC)
#define		CmbCtrl_GetNotiMask(hC)				BaseCtrl_GetNotiMask      (hC)

#define		CmbCtrl_Handler(hC,M,W,L)			BaseCtrl_Handler          (hC,M,W,L)
#define		CmbCtrl_Refresh(hC)				BaseCtrl_Refresh          (hC)
#define		CmbCtrl_Paint(hC,R)				BaseCtrl_Paint            (hC,R)
#define		CmbCtrl_KeyDown(hC,K,R)				BaseCtrl_KeyDown          (hC,K,R)
#define		CmbCtrl_Timer(hC,R)				BaseCtrl_Timer            (hC,R)
#define		CmbCtrl_Pointing(hC,A,X,Y,R)			BaseCtrl_Pointing         (hC,A,X,Y,R)

#define		CmbCtrl_CreateDummyData(hC,N)			BaseCtrl_CreateDummyData  (hC,N)
#define		CmbCtrl_SetDummyData(hC,I,D)			BaseCtrl_SetDummyData     (hC,I,D)
#define		CmbCtrl_GetDummyData(hC,I)			BaseCtrl_GetDummyData     (hC,I)

#endif	//	_BNSOFT_PEANUT_CMBCTRL_MACROFUNC_H_
