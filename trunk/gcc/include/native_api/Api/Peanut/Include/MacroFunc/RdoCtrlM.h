/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	PEANUT RADIO CONTROL MACRO FUNCTIONS

	Copyright(c) 1997-2003 BNSoft Corp.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT_PEANUT_RDOCTRL_MACROFUNC_H_
#define		_BNSOFT_PEANUT_RDOCTRL_MACROFUNC_H_

#define		RdoCtrl_SetOwner(hC,O)				ChkCtrl_SetOwner         (hC,O)
#define		RdoCtrl_SetType(hC,T)				ChkCtrl_SetType          (hC,T)
#define		RdoCtrl_SetOemType(hC,T)			ChkCtrl_SetOemType       (hC,T)
#define		RdoCtrl_ModifyOemType(hC,R,A)			ChkCtrl_ModifyOemType    (hC,R,A)
#define		RdoCtrl_SetState(hC,S)				ChkCtrl_SetState         (hC,S)
#define		RdoCtrl_SetVisible(hC,O)			ChkCtrl_SetVisible       (hC,O)
#define		RdoCtrl_SetEnable(hC,O)				ChkCtrl_SetEnable        (hC,O)
#define		RdoCtrl_SetCanFocus(hC,O)			ChkCtrl_SetCanFocus      (hC,O)
#define		RdoCtrl_SetRange(hC,X1,Y1,X2,Y2)		ChkCtrl_SetRange         (hC,X1,Y1,X2,Y2)
#define		RdoCtrl_SetPos(hC,X,Y)				ChkCtrl_SetPos           (hC,X,Y)
#define		RdoCtrl_SetSize(hC,W,H)				ChkCtrl_SetSize          (hC,W,H)
#define		RdoCtrl_SetFont(hC,F)				ChkCtrl_SetFont          (hC,F)
#define		RdoCtrl_SetColorTbl(hC,pCT)			ChkCtrl_SetColorTbl      (hC,pCT)
#define		RdoCtrl_SetColor(hC,T,I,C)			ChkCtrl_SetColor         (hC,T,I,C)
#define		RdoCtrl_SetSysNotifyProc(hC,N)			ChkCtrl_SetSysNotifyProc (hC,N)
#define		RdoCtrl_SetAppNotifyProc(hC,I,M,N)		ChkCtrl_SetAppNotifyProc (hC,I,M,N)
#define		RdoCtrl_ModifyNotiMask(hC,R,A)			ChkCtrl_ModifyNotiMask   (hC,R,A)

#define		RdoCtrl_GetOwner(hC)				ChkCtrl_GetOwner         (hC)
#define		RdoCtrl_GetType(hC)				ChkCtrl_GetType          (hC)
#define		RdoCtrl_GetOemType(hC)				ChkCtrl_GetOemType       (hC)
#define		RdoCtrl_GetStyle(hC)				ChkCtrl_GetStyle         (hC)
#define		RdoCtrl_GetState(hC)				ChkCtrl_GetState         (hC)
#define		RdoCtrl_IsVisible(hC)				ChkCtrl_IsVisible        (hC)
#define		RdoCtrl_IsEnable(hC)				ChkCtrl_IsEnable         (hC)
#define		RdoCtrl_IsCanFocus(hC)				ChkCtrl_IsCanFocus       (hC)
#define		RdoCtrl_IsFocused(hC)				ChkCtrl_IsFocused        (hC)
#define		RdoCtrl_GetRange(hC)				ChkCtrl_GetRange         (hC)
#define		RdoCtrl_GetPosX(hC)				ChkCtrl_GetPosX          (hC)
#define		RdoCtrl_GetPosY(hC)				ChkCtrl_GetPosY          (hC)
#define		RdoCtrl_GetWidth(hC)				ChkCtrl_GetWidth         (hC)
#define		RdoCtrl_GetHeight(hC)				ChkCtrl_GetHeight        (hC)
#define		RdoCtrl_GetFont(hC)				ChkCtrl_GetFont          (hC)
#define		RdoCtrl_GetColorTbl(hC)				ChkCtrl_GetColorTbl      (hC)
#define		RdoCtrl_GetColor(hC,T,I)			ChkCtrl_GetColor         (hC,T,I)
#define		RdoCtrl_GetSysNotify(hC)			ChkCtrl_GetSysNotify     (hC)
#define		RdoCtrl_GetAppNotify(hC)			ChkCtrl_GetAppNotify     (hC)
#define		RdoCtrl_GetNotiMask(hC)				ChkCtrl_GetNotiMask      (hC)

#define		RdoCtrl_PtInRange(hC,X,Y)			ChkCtrl_PtInRange        (hC,X,Y)
#define		RdoCtrl_SetFocus(hC)				ChkCtrl_SetFocus         (hC)
#define		RdoCtrl_KillFocus(hC)				ChkCtrl_KillFocus        (hC)

#define		RdoCtrl_Handler(hC,M,W,L)			ChkCtrl_Handler          (hC,M,W,L)
#define		RdoCtrl_Refresh(hC)				ChkCtrl_Refresh          (hC)
#define		RdoCtrl_Paint(hC,R)				ChkCtrl_Paint            (hC,R)
#define		RdoCtrl_KeyDown(hC,K,R)				ChkCtrl_KeyDown          (hC,K,R)
#define		RdoCtrl_Timer(hC,R)				ChkCtrl_Timer            (hC,R)
#define		RdoCtrl_Pointing(hC,A,X,Y,R)			ChkCtrl_Pointing         (hC,A,X,Y,R)

#define		RdoCtrl_CreateDummyData(hC,N)			ChkCtrl_CreateDummyData  (hC,N)
#define		RdoCtrl_SetDummyData(hC,I,D)			ChkCtrl_SetDummyData     (hC,I,D)
#define		RdoCtrl_GetDummyData(hC,I)			ChkCtrl_GetDummyData     (hC,I)

#define		RdoCtrl_SetText(hC,T)				ChkCtrl_SetText      (hC,T)
#define		RdoCtrl_SetIconWidth(hC,W)			ChkCtrl_SetIconWidth (hC,W)
#define		RdoCtrl_SetSelKey(hC,K)				ChkCtrl_SetSelKey    (hC,K)
#define		RdoCtrl_SetAlignType(hC,A)			ChkCtrl_SetAlignType (hC,A)
#define		RdoCtrl_SetLineGap(hC,G)			ChkCtrl_SetLineGap   (hC,G)

#define		RdoCtrl_GetText(hC)				ChkCtrl_GetText      (hC)
#define		RdoCtrl_GetStatus(hC)				ChkCtrl_GetStatus    (hC)
#define		RdoCtrl_IsChecked(hC)				ChkCtrl_IsChecked    (hC)
#define		RdoCtrl_GetIconWidth(hC)			ChkCtrl_GetIconWidth (hC)
#define		RdoCtrl_GetSelKey(hC)				ChkCtrl_GetSelKey    (hC)
#define		RdoCtrl_GetAlignType(hC)			ChkCtrl_GetAlignType (hC)
#define		RdoCtrl_GetLineGap(hC)				ChkCtrl_GetLineGap   (hC)

#endif	//	_BNSOFT_PEANUT_RDOCTRL_MACROFUNC_H_
