/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	PEANUT POPUP CONTROL MACRO FUNCTIONS

	Copyright(c) 1997-2003 BNSoft Corp.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT_PEANUT_POPUPCTRL_MACROFUNC_H_
#define		_BNSOFT_PEANUT_POPUPCTRL_MACROFUNC_H_

#define		PopupCtrl_SetOwner(hC,O)		BaseCtrl_SetOwner         (hC,O)
#define		PopupCtrl_SetType(hC,T)			BaseCtrl_SetType          (hC,T)
#define		PopupCtrl_SetOemType(hC,T)		BaseCtrl_SetOemType       (hC,T)
#define		PopupCtrl_ModifyStyle(hC,R,A)		BaseCtrl_ModifyStyle      (hC,R,A)
#define		PopupCtrl_SetState(hC,S)		BaseCtrl_SetState         (hC,S)
#define		PopupCtrl_SetVisible(hC,O)		BaseCtrl_SetVisible       (hC,O)
#define		PopupCtrl_SetEnable(hC,O)		BaseCtrl_SetEnable        (hC,O)
#define		PopupCtrl_SetCanFocus(hC,O)		BaseCtrl_SetCanFocus      (hC,O)
#define		PopupCtrl_SetRange(hC,X1,Y1,X2,Y2)	BaseCtrl_SetRange         (hC,X1,Y1,X2,Y2)
#define		PopupCtrl_SetPos(hC,X,Y)		BaseCtrl_SetPos           (hC,X,Y)
#define		PopupCtrl_SetSize(hC,W,H)		BaseCtrl_Size             (hC,W,H)
#define		PopupCtrl_SetFont(hC,F)			BaseCtrl_SetFont          (hC,F)
#define		PopupCtrl_SetColorTbl(hC,pCT)		BaseCtrl_SetColorTbl      (hC,pCT)
#define		PopupCtrl_SetColor(hC,T,I,C)		BaseCtrl_SetColor         (hC,T,I,C)
#define		PopupCtrl_SetSysNotifyProc(hC,N)	BaseCtrl_SetSysNotifyProc (hC,N)
#define		PopupCtrl_SetAppNotifyProc(hC,I,M,N)	BaseCtrl_SetAppNotifyProc (hC,I,M,N)
#define		PopupCtrl_ModifyNotiMask(hC,R,A)	BaseCtrl_ModifyNotiMask   (hC,R,A)

#define		PopupCtrl_GetOwner(hC)			BaseCtrl_GetOwner         (hC)
#define		PopupCtrl_GetType(hC)			BaseCtrl_GetType          (hC)
#define		PopupCtrl_GetOemType(hC)		BaseCtrl_GetOemType       (hC)
#define		PopupCtrl_GetStyle(hC)			BaseCtrl_GetStyle         (hC)
#define		PopupCtrl_GetState(hC)			BaseCtrl_GetState         (hC)
#define		PopupCtrl_IsVisible(hC)			BaseCtrl_IsVisible        (hC)
#define		PopupCtrl_IsEnable(hC)			BaseCtrl_IsEnable         (hC)
#define		PopupCtrl_IsCanFocus(hC)		BaseCtrl_IsCanFocus       (hC)
#define		PopupCtrl_IsFocused(hC)			BaseCtrl_IsFocused        (hC)
#define		PopupCtrl_GetRange(hC)			BaseCtrl_GetRange         (hC)
#define		PopupCtrl_GetPosX(hC)			BaseCtrl_GetPosX          (hC)
#define		PopupCtrl_GetPosY(hC)			BaseCtrl_GetPosY          (hC)
#define		PopupCtrl_GetWidth(hC)			BaseCtrl_GetWidth         (hC)
#define		PopupCtrl_GetHeight(hC)			BaseCtrl_GetHeight        (hC)
#define		PopupCtrl_GetFont(hC)			BaseCtrl_GetFont          (hC)
#define		PopupCtrl_GetColorTbl(hC)		BaseCtrl_GetColorTbl      (hC)
#define		PopupCtrl_GetColor(hC,T,I)		BaseCtrl_GetColor         (hC,T,I)
#define		PopupCtrl_GetSysNotify(hC)		BaseCtrl_GetSysNotify     (hC)
#define		PopupCtrl_GetAppNotify(hC)		BaseCtrl_GetAppNotify     (hC)
#define		PopupCtrl_GetNotiMask(hC)		BaseCtrl_GetNotiMask      (hC)

#define		PopupCtrl_PtInRange(hC,X,Y)		BaseCtrl_PtInRange        (hC,X,Y)
#define		PopupCtrl_SetFocus(hC)			BaseCtrl_SetFocus         (hC)
#define		PopupCtrl_KillFocus(hC)			BaseCtrl_KillFocus        (hC)

#define		PopupCtrl_Handler(hC,M,W,L)		BaseCtrl_Handler          (hC,M,W,L)
#define		PopupCtrl_Refresh(hC)			BaseCtrl_Refresh          (hC)
#define		PopupCtrl_Paint(hC,R)			BaseCtrl_Paint            (hC,R)
#define		PopupCtrl_KeyDown(hC,K,R)		BaseCtrl_KeyDown          (hC,K,R)
#define		PopupCtrl_Timer(hC,R)			BaseCtrl_Timer            (hC,R)
#define		PopupCtrl_Pointing(hC,A,X,Y,R)		BaseCtrl_Pointing         (hC,A,X,Y,R)

#define		PopupCtrl_CreateDummyData(hC,N)		BaseCtrl_CreateDummyData  (hC,N)
#define		PopupCtrl_SetDummyData(hC,I,D)		BaseCtrl_SetDummyData     (hC,I,D)
#define		PopupCtrl_GetDummyData(hC,I)		BaseCtrl_GetDummyData     (hC,I)


#endif	//	_BNSOFT_PEANUT_POPUPCTRL_MACROFUNC_H_
