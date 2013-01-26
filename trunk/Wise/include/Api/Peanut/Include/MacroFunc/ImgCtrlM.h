/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	PEANUT IMAGE CONTROL MACRO FUNCTIONS

	Copyright(c) 1997-2003 BNSoft Corp.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT_PEANUT_IMGCTRL_MACROFUNC_H_
#define		_BNSOFT_PEANUT_IMGCTRL_MACROFUNC_H_

#define		ImgCtrl_SetOwner(hC,O)				BaseCtrl_SetOwner         (hC,O)
#define		ImgCtrl_SetType(hC,T)				BaseCtrl_SetType          (hC,T)
#define		ImgCtrl_SetOemType(hC,T)			BaseCtrl_SetOemType       (hC,T)
#define		ImgCtrl_ModifyOemType(hC,R,A)			BaseCtrl_ModifyOemType    (hC,R,A)
#define		ImgCtrl_ModifyStyle(hC,R,A)			BaseCtrl_ModifyStyle      (hC,R,A)
#define		ImgCtrl_SetState(hC,S)				BaseCtrl_SetState         (hC,S)
#define		ImgCtrl_SetVisible(hC,O)			BaseCtrl_SetVisible       (hC,O)
#define		ImgCtrl_SetEnable(hC,O)				BaseCtrl_SetEnable        (hC,O)
#define		ImgCtrl_SetCanFocus(hC,O)			BaseCtrl_SetCanFocus      (hC,O)
#define		ImgCtrl_SetRange(hC,X1,Y1,X2,Y2)		BaseCtrl_SetRange         (hC,X1,Y1,X2,Y2)
#define		ImgCtrl_SetPos(hC,X,Y)				BaseCtrl_SetPos           (hC,X,Y)
#define		ImgCtrl_SetSize(hC,W,H)				BaseCtrl_SetSize          (hC,W,H)
#define		ImgCtrl_SetSysNotifyProc(hC,N)			BaseCtrl_SetSysNotifyProc (hC,N)
#define		ImgCtrl_SetAppNotifyProc(hC,I,M,N)		BaseCtrl_SetAppNotifyProc (hC,I,M,N)
#define		ImgCtrl_ModifyNotiMask(hC,R,A)			BaseCtrl_ModifyNotiMask   (hC,R,A)

#define		ImgCtrl_GetOwner(hC)				BaseCtrl_GetOwner         (hC)
#define		ImgCtrl_GetType(hC)				BaseCtrl_GetType          (hC)
#define		ImgCtrl_GetOemType(hC)				BaseCtrl_GetOemType       (hC)
#define		ImgCtrl_GetStyle(hC)				BaseCtrl_GetStyle         (hC)
#define		ImgCtrl_GetState(hC)				BaseCtrl_GetState         (hC)
#define		ImgCtrl_IsVisible(hC)				BaseCtrl_IsVisible        (hC)
#define		ImgCtrl_IsEnable(hC)				BaseCtrl_IsEnable         (hC)
#define		ImgCtrl_IsCanFocus(hC)				BaseCtrl_IsCanFocus       (hC)
#define		ImgCtrl_IsFocused(hC)				BaseCtrl_IsFocused        (hC)
#define		ImgCtrl_GetRange(hC)				BaseCtrl_GetRange         (hC)
#define		ImgCtrl_GetPosX(hC)				BaseCtrl_GetPosX          (hC)
#define		ImgCtrl_GetPosY(hC)				BaseCtrl_GetPosY          (hC)
#define		ImgCtrl_GetWidth(hC)				BaseCtrl_GetWidth         (hC)
#define		ImgCtrl_GetHeight(hC)				BaseCtrl_GetHeight        (hC)
#define		ImgCtrl_GetSysNotify(hC)			BaseCtrl_GetSysNotify     (hC)
#define		ImgCtrl_GetAppNotify(hC)			BaseCtrl_GetAppNotify     (hC)
#define		ImgCtrl_GetNotiMask(hC)				BaseCtrl_GetNotiMask      (hC)

#define		ImgCtrl_PtInRange(hC,X,Y)			BaseCtrl_PtInRange        (hC,X,Y)
#define		ImgCtrl_SetFocus(hC)				BaseCtrl_SetFocus         (hC)
#define		ImgCtrl_KillFocus(hC)				BaseCtrl_KillFocus        (hC)

#define		ImgCtrl_Handler(hC,M,W,L)			BaseCtrl_Handler          (hC,M,W,L)
#define		ImgCtrl_Refresh(hC)				BaseCtrl_Refresh          (hC)
#define		ImgCtrl_Paint(hC,R)				BaseCtrl_Paint            (hC,R)
#define		ImgCtrl_KeyDown(hC,K,R)				BaseCtrl_KeyDown          (hC,K,R)
#define		ImgCtrl_Timer(hC,R)				BaseCtrl_Timer            (hC,R)
#define		ImgCtrl_Pointing(hC,A,X,Y,R)			BaseCtrl_Pointing         (hC,A,X,Y,R)

#define		ImgCtrl_CreateDummyData(hC,N)			BaseCtrl_CreateDummyData  (hC,N)
#define		ImgCtrl_SetDummyData(hC,I,D)			BaseCtrl_SetDummyData     (hC,I,D)
#define		ImgCtrl_GetDummyData(hC,I)			BaseCtrl_GetDummyData     (hC,I)

#endif	//	_BNSOFT_PEANUT_IMGCTRL_MACROFUNC_H_
