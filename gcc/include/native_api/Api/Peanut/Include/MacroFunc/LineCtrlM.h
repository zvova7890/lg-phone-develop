/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	PEANUT LINE CONTROL MACRO FUNCTIONS

	Copyright(c) 1997-2003 BNSoft Corp.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT_PEANUT_LINECTRL_MACROFUNC_H_
#define		_BNSOFT_PEANUT_LINECTRL_MACROFUNC_H_

#define		LineCtrl_SetOwner(hC,O)				BaseCtrl_SetOwner         (hC,O)
#define		LineCtrl_SetType(hC,T)				BaseCtrl_SetType          (hC,T)
#define		LineCtrl_SetOemType(hC,T)			BaseCtrl_SetOemType       (hC,T)
#define		LineCtrl_ModifyOemType(hC,R,A)			BaseCtrl_ModifyOemType    (hC,R,A)
#define		LineCtrl_ModifyStyle(hC,R,A)			BaseCtrl_ModifyStyle      (hC,R,A)
#define		LineCtrl_SetState(hC,S)				BaseCtrl_SetState         (hC,S)
#define		LineCtrl_SetVisible(hC,O)			BaseCtrl_SetVisible       (hC,O)
#define		LineCtrl_SetEnable(hC,O)			BaseCtrl_SetEnable        (hC,O)
#define		LineCtrl_SetCanFocus(hC,O)			BaseCtrl_SetCanFocus      (hC,O)
#define		LineCtrl_SetRange(hC,X1,Y1,X2,Y2)		BaseCtrl_SetRange         (hC,X1,Y1,X2,Y2)
#define		LineCtrl_SetPos(hC,X,Y)				BaseCtrl_SetPos           (hC,X,Y)
#define		LineCtrl_SetSize(hC,W,H)			BaseCtrl_SetSize          (hC,W,H)
#define		LineCtrl_SetFont(hC,F)				BaseCtrl_SetFont          (hC,F)
#define		LineCtrl_SetColorTbl(hC,pCT)			BaseCtrl_SetColorTbl      (hC,pCT)
#define		LineCtrl_SetSysNotifyProc(hC,N)			BaseCtrl_SetSysNotifyProc (hC,N)
#define		LineCtrl_SetAppNotifyProc(hC,I,M,N)		BaseCtrl_SetAppNotifyProc (hC,I,M,N)
#define		LineCtrl_ModifyNotiMask(hC,R,A)			BaseCtrl_ModifyNotiMask   (hC,R,A)

#define		LineCtrl_GetOwner(hC)				BaseCtrl_GetOwner         (hC)
#define		LineCtrl_GetType(hC)				BaseCtrl_GetType          (hC)
#define		LineCtrl_GetOemType(hC)				BaseCtrl_GetOemType       (hC)
#define		LineCtrl_GetStyle(hC)				BaseCtrl_GetStyle         (hC)
#define		LineCtrl_GetState(hC)				BaseCtrl_GetState         (hC)
#define		LineCtrl_IsVisible(hC)				BaseCtrl_IsVisible        (hC)
#define		LineCtrl_IsEnable(hC)				BaseCtrl_IsEnable         (hC)
#define		LineCtrl_IsCanFocus(hC)				BaseCtrl_IsCanFocus       (hC)
#define		LineCtrl_IsFocused(hC)				BaseCtrl_IsFocused        (hC)
#define		LineCtrl_GetRange(hC)				BaseCtrl_GetRange         (hC)
#define		LineCtrl_GetPosX(hC)				BaseCtrl_GetPosX          (hC)
#define		LineCtrl_GetPosY(hC)				BaseCtrl_GetPosY          (hC)
#define		LineCtrl_GetWidth(hC)				BaseCtrl_GetWidth         (hC)
#define		LineCtrl_GetHeight(hC)				BaseCtrl_GetHeight        (hC)
#define		LineCtrl_GetFont(hC)				BaseCtrl_GetFont          (hC)
#define		LineCtrl_GetColorTbl(hC)			BaseCtrl_GetColorTbl      (hC)
#define		LineCtrl_GetSysNotify(hC)			BaseCtrl_GetSysNotify     (hC)
#define		LineCtrl_GetAppNotify(hC)			BaseCtrl_GetAppNotify     (hC)
#define		LineCtrl_GetNotiMask(hC)			BaseCtrl_GetNotiMask      (hC)

#define		LineCtrl_PtInRange(hC,X,Y)			BaseCtrl_PtInRange        (hC,X,Y)
#define		LineCtrl_SetFocus(hC)				BaseCtrl_SetFocus         (hC)
#define		LineCtrl_KillFocus(hC)				BaseCtrl_KillFocus        (hC)

#define		LineCtrl_Handler(hC,M,W,L)			BaseCtrl_Handler          (hC,M,W,L)
#define		LineCtrl_Refresh(hC)				BaseCtrl_Refresh          (hC)
#define		LineCtrl_Paint(hC,R)				BaseCtrl_Paint            (hC,R)
#define		LineCtrl_KeyDown(hC,K,R)			BaseCtrl_KeyDown          (hC,K,R)
#define		LineCtrl_Timer(hC,R)				BaseCtrl_Timer            (hC,R)
#define		LineCtrl_Pointing(hC,A,X,Y,R)			BaseCtrl_Pointing         (hC,A,X,Y,R)

#define		LineCtrl_CreateDummyData(hC,N)			BaseCtrl_CreateDummyData  (hC,N)
#define		LineCtrl_SetDummyData(hC,I,D)			BaseCtrl_SetDummyData     (hC,I,D)
#define		LineCtrl_GetDummyData(hC,I)			BaseCtrl_GetDummyData     (hC,I)


#endif	//	_BNSOFT_PEANUT_LINECTRL_MACROFUNC_H_
