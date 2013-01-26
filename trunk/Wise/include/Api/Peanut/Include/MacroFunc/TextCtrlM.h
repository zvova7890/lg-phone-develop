/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	PEANUT TEXT CONTROL MACRO FUNCTIONS

	Copyright(c) 1997-2003 BNSoft Corp.


~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT_PEANUT_TEXTCTRL_MACROFUNC_H_
#define		_BNSOFT_PEANUT_TEXTCTRL_MACROFUNC_H_

//	TextCtrl Macro Member Functions
#define		TextCtrl_SetOwner(hC,O)				BaseCtrl_SetOwner         (hC,O)
#define		TextCtrl_SetType(hC,T)				BaseCtrl_SetType          (hC,T)
#define		TextCtrl_SetOemType(hC,T)			BaseCtrl_SetOemType       (hC,T)
#define		TextCtrl_ModifyOemType(hC,R,A)			BaseCtrl_ModifyOemType    (hC,R,A)
#define		TextCtrl_ModifyStyle(hC,R,A)			BaseCtrl_ModifyStyle      (hC,R,A)
#define		TextCtrl_SetState(hC,S)				BaseCtrl_SetState         (hC,S)
#define		TextCtrl_SetVisible(hC,O)			BaseCtrl_SetVisible       (hC,O)
#define		TextCtrl_SetEnable(hC,O)			BaseCtrl_SetEnable        (hC,O)
#define		TextCtrl_SetCanFocus(hC,O)			BaseCtrl_SetCanFocus      (hC,O)
#define		TextCtrl_SetRange(hC,X1,Y1,X2,Y2)		BaseCtrl_SetRange         (hC,X1,Y1,X2,Y2)
#define		TextCtrl_SetPos(hC,X,Y)				BaseCtrl_SetPos           (hC,X,Y)
#define		TextCtrl_SetSize(hC,W,H)			BaseCtrl_SetSize          (hC,W,H)
#define		TextCtrl_SetFont(hC,F)				BaseCtrl_SetFont          (hC,F)
#define		TextCtrl_SetColorTbl(hC,pCT)			BaseCtrl_SetColorTbl      (hC,pCT)
#define		TextCtrl_SetColor(hC,T,I,C)			BaseCtrl_SetColor         (hC,T,I,C)
#define		TextCtrl_SetSysNotifyProc(hC,N)			BaseCtrl_SetSysNotifyProc (hC,N)
#define		TextCtrl_SetAppNotifyProc(hC,I,M,N)		BaseCtrl_SetAppNotifyProc (hC,I,M,N)
#define		TextCtrl_ModifyNotiMask(hC,R,A)			BaseCtrl_ModifyNotiMask   (hC,R,A)

#define		TextCtrl_GetOwner(hC)				BaseCtrl_GetOwner         (hC)
#define		TextCtrl_GetType(hC)				BaseCtrl_GetType          (hC)
#define		TextCtrl_GetOemType(hC)				BaseCtrl_GetOemType       (hC)
#define		TextCtrl_GetStyle(hC)				BaseCtrl_GetStyle         (hC)
#define		TextCtrl_GetState(hC)				BaseCtrl_GetState         (hC)
#define		TextCtrl_IsVisible(hC)				BaseCtrl_IsVisible        (hC)
#define		TextCtrl_IsEnable(hC)				BaseCtrl_IsEnable         (hC)
#define		TextCtrl_IsCanFocus(hC)				BaseCtrl_IsCanFocus       (hC)
#define		TextCtrl_IsFocused(hC)				BaseCtrl_IsFocused        (hC)
#define		TextCtrl_GetRange(hC)				BaseCtrl_GetRange         (hC)
#define		TextCtrl_GetPosX(hC)				BaseCtrl_GetPosX          (hC)
#define		TextCtrl_GetPosY(hC)				BaseCtrl_GetPosY          (hC)
#define		TextCtrl_GetWidth(hC)				BaseCtrl_GetWidth         (hC)
#define		TextCtrl_GetHeight(hC)				BaseCtrl_GetHeight        (hC)
#define		TextCtrl_GetFont(hC)				BaseCtrl_GetFont          (hC)
#define		TextCtrl_GetColorTbl(hC)			BaseCtrl_GetColorTbl      (hC)
#define		TextCtrl_GetColor(hC,T,I)			BaseCtrl_GetColor         (hC,T,I)
#define		TextCtrl_GetSysNotify(hC)			BaseCtrl_GetSysNotify     (hC)
#define		TextCtrl_GetAppNotify(hC)			BaseCtrl_GetAppNotify     (hC)
#define		TextCtrl_GetNotiMask(hC)			BaseCtrl_GetNotiMask      (hC)

#define		TextCtrl_PtInRange(hC,X,Y)			BaseCtrl_PtInRange        (hC,X,Y)
#define		TextCtrl_SetFocus(hC)				BaseCtrl_SetFocus         (hC)
#define		TextCtrl_KillFocus(hC)				BaseCtrl_KillFocus        (hC)

#define		TextCtrl_Handler(hC,M,W,L)			BaseCtrl_Handler          (hC,M,W,L)
#define		TextCtrl_Refresh(hC)				BaseCtrl_Refresh          (hC)
#define		TextCtrl_Paint(hC,R)				BaseCtrl_Paint            (hC,R)
#define		TextCtrl_KeyDown(hC,K,R)			BaseCtrl_KeyDown          (hC,K,R)
#define		TextCtrl_Timer(hC,R)				BaseCtrl_Timer            (hC,R)
#define		TextCtrl_Pointing(hC,A,X,Y,R)			BaseCtrl_Pointing         (hC,A,X,Y,R)

#define		TextCtrl_CreateDummyData(hC,N)			BaseCtrl_CreateDummyData  (hC,N)
#define		TextCtrl_SetDummyData(hC,I,D)			BaseCtrl_SetDummyData     (hC,I,D)
#define		TextCtrl_GetDummyData(hC,I)			BaseCtrl_GetDummyData     (hC,I)


#endif	//	_BNSOFT_PEANUT_TEXTCTRL_MACROFUNC_H_
