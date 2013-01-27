/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	PEANUT KEYPAD CONTROL MACRO FUNCTIONS

	Copyright(c)     -2007 LG Electronics Inc.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT_PEANUT_KEYPADCTRL_MACROFUNC_H_
#define		_BNSOFT_PEANUT_KEYPADCTRL_MACROFUNC_H_

#define		KeypadCtrl_SetOwner(hC,O)			FrmCtrl_SetOwner         (hC,O)
#define		KeypadCtrl_SetType(hC,T)			FrmCtrl_SetType          (hC,T)
#define		KeypadCtrl_SetOemType(hC,T)			FrmCtrl_SetOemType       (hC,T)
#define		KeypadCtrl_ModifyOemType(hC,R,A)		FrmCtrl_ModifyOemType    (hC,R,A)
#define		KeypadCtrl_ModifyStyle(hC,R,A)			FrmCtrl_ModifyStyle      (hC,R,A)
#define		KeypadCtrl_SetState(hC,S)			FrmCtrl_SetState         (hC,S)
#define		KeypadCtrl_SetVisible(hC,O)			FrmCtrl_SetVisible       (hC,O)
#define		KeypadCtrl_SetEnable(hC,O)			FrmCtrl_SetEnable        (hC,O)
#define		KeypadCtrl_SetCanFocus(hC,O)			FrmCtrl_SetCanFocus      (hC,O)
#define		KeypadCtrl_SetRange(hC,X1,Y1,X2,Y2)		FrmCtrl_SetRange         (hC,X1,Y1,X2,Y2)
#define		KeypadCtrl_SetPos(hC,X,Y)			FrmCtrl_SetPos           (hC,X,Y)
#define		KeypadCtrl_SetSize(hC,W,H)			FrmCtrl_SetSize          (hC,W,H)
#define		KeypadCtrl_SetFont(hC,F)			FrmCtrl_SetFont          (hC,F)
#define		KeypadCtrl_SetColorTbl(hC,pCT)			FrmCtrl_SetColorTbl      (hC,pCT)
#define		KeypadCtrl_SetColor(hC,T,I,C)			FrmCtrl_SetColor         (hC,T,I,C)
#define		KeypadCtrl_SetSysNotifyProc(hC,N)		FrmCtrl_SetSysNotifyProc (hC,N)
#define		KeypadCtrl_SetAppNotifyProc(hC,I,M,N)		FrmCtrl_SetAppNotifyProc (hC,I,M,N)
#define		KeypadCtrl_ModifyNotiMask(hC,R,A)		FrmCtrl_ModifyNotiMask   (hC,R,A)

#define		KeypadCtrl_GetOwner(hC)				FrmCtrl_GetOwner         (hC)
#define		KeypadCtrl_GetType(hC)				FrmCtrl_GetType          (hC)
#define		KeypadCtrl_GetOemType(hC)			FrmCtrl_GetOemType       (hC)
#define		KeypadCtrl_GetStyle(hC)				FrmCtrl_GetStyle         (hC)
#define		KeypadCtrl_GetState(hC)				FrmCtrl_GetState         (hC)
#define		KeypadCtrl_IsVisible(hC)			FrmCtrl_IsVisible        (hC)
#define		KeypadCtrl_IsEnable(hC)				FrmCtrl_IsEnable         (hC)
#define		KeypadCtrl_IsCanFocus(hC)			FrmCtrl_IsCanFocus       (hC)
#define		KeypadCtrl_IsFocused(hC)			FrmCtrl_IsFocused        (hC)
#define		KeypadCtrl_GetRange(hC)				FrmCtrl_GetRange         (hC)
#define		KeypadCtrl_GetPosX(hC)				FrmCtrl_GetPosX          (hC)
#define		KeypadCtrl_GetPosY(hC)				FrmCtrl_GetPosY          (hC)
#define		KeypadCtrl_GetWidth(hC)				FrmCtrl_GetWidth         (hC)
#define		KeypadCtrl_GetHeight(hC)			FrmCtrl_GetHeight        (hC)
#define		KeypadCtrl_GetFont(hC)				FrmCtrl_GetFont          (hC)
#define		KeypadCtrl_GetColorTbl(hC)			FrmCtrl_GetColorTbl      (hC)
#define		KeypadCtrl_GetColor(hC,T,I)			FrmCtrl_GetColor         (hC,T,I)
#define		KeypadCtrl_GetSysNotify(hC)			FrmCtrl_GetSysNotify     (hC)
#define		KeypadCtrl_GetAppNotify(hC)			FrmCtrl_GetAppNotify     (hC)
#define		KeypadCtrl_GetNotiMask(hC)			FrmCtrl_GetNotiMask      (hC)

#define		KeypadCtrl_PtInRange(hC,X,Y)			FrmCtrl_PtInRange        (hC,X,Y)
#define		KeypadCtrl_SetFocus(hC)				FrmCtrl_SetFocus         (hC)
#define		KeypadCtrl_KillFocus(hC)			FrmCtrl_KillFocus        (hC)

#define		KeypadCtrl_Handler(hC,M,W,L)			FrmCtrl_Handler          (hC,M,W,L)
#define		KeypadCtrl_Refresh(hC)				FrmCtrl_Refresh          (hC)
#define		KeypadCtrl_Paint(hC,R)				FrmCtrl_Paint            (hC,R)
#define		KeypadCtrl_KeyDown(hC,K,R)			FrmCtrl_KeyDown          (hC,K,R)
#define		KeypadCtrl_Timer(hC,R)				FrmCtrl_Timer            (hC,R)
#define		KeypadCtrl_Pointing(hC,A,X,Y,R)			FrmCtrl_Pointing         (hC,A,X,Y,R)

#define		KeypadCtrl_CreateDummyData(hC,N)		FrmCtrl_CreateDummyData  (hC,N)
#define		KeypadCtrl_SetDummyData(hC,I,D)			FrmCtrl_SetDummyData     (hC,I,D)
#define		KeypadCtrl_GetDummyData(hC,I)			FrmCtrl_GetDummyData     (hC,I)

#define		KeypadCtrl_SetClientRect(hC,X1,Y1,X2,Y2)	FrmCtrl_SetClientRect    (hC,X1,Y1,X2,Y2)
#define		KeypadCtrl_SetClientPos(hC,X,Y)			FrmCtrl_SetClientPos     (hC,X,Y)
#define		KeypadCtrl_SetClientSize(hC,W,H)		FrmCtrl_SetClientSize    (hC,W,H)
#define		KeypadCtrl_SetDelta(hC,X,Y)			FrmCtrl_SetDelta         (hC,X,Y)
#define		KeypadCtrl_SetDelta2(hC,X,Y)			FrmCtrl_SetDelta2        (hC,X,Y)
#define		KeypadCtrl_SetTitle(hC,T)			FrmCtrl_SetTitle         (hC,T)
#define		KeypadCtrl_SetTitleFont(hC,F)			FrmCtrl_SetTitleFont     (hC,F)
#define		KeypadCtrl_SetTitleHeight(hC,H)			FrmCtrl_SetTitleHeight   (hC,H)
#define		KeypadCtrl_SetTitleLeftMargin(hC,X)		FrmCtrl_SetTitleLeftMargin(hC,X)
#define		KeypadCtrl_SetTitleRightMargin(hC,X)		FrmCtrl_SetTitleRightMargin(hC,X)

#define		KeypadCtrl_GetClientRect(hC)			FrmCtrl_GetClientRect    (hC)
#define		KeypadCtrl_GetClientPosX(hC)			FrmCtrl_GetClientPosX    (hC)
#define		KeypadCtrl_GetClientPosY(hC)			FrmCtrl_GetClientPosY    (hC)
#define		KeypadCtrl_GetClientWidth(hC)			FrmCtrl_GetClientWidth   (hC)
#define		KeypadCtrl_GetClientHeight(hC)			FrmCtrl_GetClientHeight  (hC)
#define		KeypadCtrl_GetWorkArea(hC)			FrmCtrl_GetWorkArea      (hC)
#define		KeypadCtrl_GetWorkPosX(hC)			FrmCtrl_GetWorkPosX      (hC)
#define		KeypadCtrl_GetWorkPosY(hC)			FrmCtrl_GetWorkPosY      (hC)
#define		KeypadCtrl_GetWorkWidth(hC)			FrmCtrl_GetWorkWidth     (hC)
#define		KeypadCtrl_GetWorkHeight(hC)			FrmCtrl_GetWorkHeight    (hC)
#define		KeypadCtrl_GetDeltaX1(hC)			FrmCtrl_GetDeltaX1       (hC)
#define		KeypadCtrl_GetDeltaY1(hC)			FrmCtrl_GetDeltaY1       (hC)
#define		KeypadCtrl_GetDeltaX2(hC)			FrmCtrl_GetDeltaX2       (hC)
#define		KeypadCtrl_GetDeltaY2(hC)			FrmCtrl_GetDeltaY2       (hC)
#define		KeypadCtrl_GetTitle(hC)				FrmCtrl_GetTitle         (hC)
#define		KeypadCtrl_GetTitleFont(hC)			FrmCtrl_GetTitleFont     (hC)
#define		KeypadCtrl_GetTitleHeight(hC)			FrmCtrl_GetTitleHeight   (hC)
#define		KeypadCtrl_GetTitleLeftMargin(hC)		FrmCtrl_GetTitleLeftMargin(hC)
#define		KeypadCtrl_GetTitleRightMargin(hC)		FrmCtrl_GetTitleRightMargin(hC)

#define		KeypadCtrl_AdjustRange(hC)			FrmCtrl_AdjustRange      (hC)
#define		KeypadCtrl_AdjustClientRect(hC)			FrmCtrl_AdjustClientRect (hC)
#define		KeypadCtrl_AdjustScrollBar(hC)			FrmCtrl_AdjustScrollBar  (hC)
#define		KeypadCtrl_PtInClientRect(hC,X,Y)		FrmCtrl_PtInClientRect   (hC,X,Y)


#endif	//	_BNSOFT_PEANUT_KEYPADCTRL_MACROFUNC_H_

