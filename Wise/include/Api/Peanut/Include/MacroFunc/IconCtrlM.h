/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	PEANUT BUTTON CONTROL MACRO FUNCTIONS

	Copyright(c) 1997-2003 BNSoft Corp.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT_PEANUT_ICONCTRL_MACROFUNC_H_
#define		_BNSOFT_PEANUT_ICONCTRL_MACROFUNC_H_

#define		IconCtrl_SetOwner(hC,O)				BaseCtrl_SetOwner         (hC,O)
#define		IconCtrl_SetType(hC,T)				BaseCtrl_SetType          (hC,T)
#define		IconCtrl_SetOemType(hC,T)			BaseCtrl_SetOemType       (hC,T)
#define		IconCtrl_ModifyOemType(hC,R,A)			BaseCtrl_ModifyOemType    (hC,R,A)
#define		IconCtrl_ModifyStyle(hC,R,A)			BaseCtrl_ModifyStyle      (hC,R,A)
#define		IconCtrl_SetState(hC,S)				BaseCtrl_SetState         (hC,S)
#define		IconCtrl_SetVisible(hC,O)			BaseCtrl_SetVisible       (hC,O)
#define		IconCtrl_SetEnable(hC,O)			BaseCtrl_SetEnable        (hC,O)
#define		IconCtrl_SetCanFocus(hC,O)			BaseCtrl_SetCanFocus      (hC,O)
#define		IconCtrl_SetRange(hC,X1,Y1,X2,Y2)		BaseCtrl_SetRange         (hC,X1,Y1,X2,Y2)
#define		IconCtrl_SetPos(hC,X,Y)				BaseCtrl_SetPos           (hC,X,Y)
#define		IconCtrl_SetSize(hC,W,H)			BaseCtrl_SetSize          (hC,W,H)
#define		IconCtrl_SetSysNotifyProc(hC,N)			BaseCtrl_SetSysNotifyProc (hC,N)
#define		IconCtrl_SetAppNotifyProc(hC,I,M,N)		BaseCtrl_SetAppNotifyProc (hC,I,M,N)
#define		IconCtrl_ModifyNotiMask(hC,R,A)			BaseCtrl_ModifyNotiMask   (hC,R,A)

#define		IconCtrl_GetOwner(hC)				BaseCtrl_GetOwner         (hC)
#define		IconCtrl_GetType(hC)				BaseCtrl_GetType          (hC)
#define		IconCtrl_GetOemType(hC)				BaseCtrl_GetOemType       (hC)
#define		IconCtrl_GetStyle(hC)				BaseCtrl_GetStyle         (hC)
#define		IconCtrl_GetState(hC)				BaseCtrl_GetState         (hC)
#define		IconCtrl_IsVisible(hC)				BaseCtrl_IsVisible        (hC)
#define		IconCtrl_IsEnable(hC)				BaseCtrl_IsEnable         (hC)
#define		IconCtrl_IsCanFocus(hC)				BaseCtrl_IsCanFocus       (hC)
#define		IconCtrl_IsFocused(hC)				BaseCtrl_IsFocused        (hC)
#define		IconCtrl_GetRange(hC)				BaseCtrl_GetRange         (hC)
#define		IconCtrl_GetPosX(hC)				BaseCtrl_GetPosX          (hC)
#define		IconCtrl_GetPosY(hC)				BaseCtrl_GetPosY          (hC)
#define		IconCtrl_GetWidth(hC)				BaseCtrl_GetWidth         (hC)
#define		IconCtrl_GetHeight(hC)				BaseCtrl_GetHeight        (hC)
#define		IconCtrl_GetSysNotify(hC)			BaseCtrl_GetSysNotify     (hC)
#define		IconCtrl_GetAppNotify(hC)			BaseCtrl_GetAppNotify     (hC)
#define		IconCtrl_GetNotiMask(hC)			BaseCtrl_GetNotiMask      (hC)

#define		IconCtrl_PtInRange(hC,X,Y)			BaseCtrl_PtInRange        (hC,X,Y)
#define		IconCtrl_SetFocus(hC)				BaseCtrl_SetFocus         (hC)
#define		IconCtrl_KillFocus(hC)				BaseCtrl_KillFocus        (hC)

#define		IconCtrl_Handler(hC,M,W,L)			BaseCtrl_Handler          (hC,M,W,L)
#define		IconCtrl_Refresh(hC)				BaseCtrl_Refresh          (hC)
#define		IconCtrl_Paint(hC,R)				BaseCtrl_Paint            (hC,R)
#define		IconCtrl_KeyDown(hC,K,R)			BaseCtrl_KeyDown          (hC,K,R)
#define		IconCtrl_Timer(hC,R)				BaseCtrl_Timer            (hC,R)
#define		IconCtrl_Pointing(hC,A,X,Y,R)			BaseCtrl_Pointing         (hC,A,X,Y,R)

#define		IconCtrl_CreateDummyData(hC,N)			BaseCtrl_CreateDummyData  (hC,N)
#define		IconCtrl_SetDummyData(hC,I,D)			BaseCtrl_SetDummyData     (hC,I,D)
#define		IconCtrl_GetDummyData(hC,I)			BaseCtrl_GetDummyData     (hC,I)


#endif	//	_BNSOFT_PEANUT_ICONCTRL_MACROFUNC_H_
