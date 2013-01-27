/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	PEANUT TABCTRL MACRO FUNCTIONS

	Copyright(c) 1997-2003 BNSoft Corp.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT_PEANUT_TABCTRL_MACROFUNC_H_
#define		_BNSOFT_PEANUT_TABCTRL_MACROFUNC_H_

//	TabCtrl Macro Member Functions
#define		TabCtrl_SetOwner(hC,O)				FrmCtrl_SetOwner         (hC,O)
#define		TabCtrl_SetType(hC,T)				FrmCtrl_SetType          (hC,T)
#define		TabCtrl_SetOemType(hC,T)			FrmCtrl_SetOemType       (hC,T)
#define		TabCtrl_ModifyOemType(hC,R,A)			FrmCtrl_ModifyOemType    (hC,R,A)
#define		TabCtrl_ModifyStyle(hC,R,A)			FrmCtrl_ModifyStyle      (hC,R,A)
#define		TabCtrl_SetState(hC,S)				FrmCtrl_SetState         (hC,S)
#define		TabCtrl_SetVisible(hC,O)			FrmCtrl_SetVisible       (hC,O)
#define		TabCtrl_SetEnable(hC,O)				FrmCtrl_SetEnable        (hC,O)
#define		TabCtrl_SetCanFocus(hC,O)			FrmCtrl_SetCanFocus      (hC,O)
#define		TabCtrl_SetRange(hC,X1,Y1,X2,Y2)		FrmCtrl_SetRange         (hC,X1,Y1,X2,Y2)
#define		TabCtrl_SetPos(hC,X,Y)				FrmCtrl_SetPos           (hC,X,Y)
#define		TabCtrl_SetSize(hC,W,H)				FrmCtrl_SetSize          (hC,W,H)
#define		TabCtrl_SetFont(hC,F)				FrmCtrl_SetFont          (hC,F)
#define		TabCtrl_SetColorTbl(hC,pCT)			FrmCtrl_SetColorTbl      (hC,pCT)
#define		TabCtrl_SetColor(hC,T,I,C)			FrmCtrl_SetColor         (hC,T,I,C)
#define		TabCtrl_SetSysNotifyProc(hC,N)			FrmCtrl_SetSysNotifyProc (hC,N)
#define		TabCtrl_SetAppNotifyProc(hC,I,M,N)		FrmCtrl_SetAppNotifyProc (hC,I,M,N)
#define		TabCtrl_ModifyNotiMask(hC,R,A)			FrmCtrl_ModifyNotiMask   (hC,R,A)

#define		TabCtrl_GetOwner(hC)				FrmCtrl_GetOwner         (hC)
#define		TabCtrl_GetType(hC)				FrmCtrl_GetType          (hC)
#define		TabCtrl_GetOemType(hC)				FrmCtrl_GetOemType       (hC)
#define		TabCtrl_GetStyle(hC)				FrmCtrl_GetStyle         (hC)
#define		TabCtrl_GetState(hC)				FrmCtrl_GetState         (hC)
#define		TabCtrl_IsVisible(hC)				FrmCtrl_IsVisible        (hC)
#define		TabCtrl_IsEnable(hC)				FrmCtrl_IsEnable         (hC)
#define		TabCtrl_IsCanFocus(hC)				FrmCtrl_IsCanFocus       (hC)
#define		TabCtrl_IsFocused(hC)				FrmCtrl_IsFocused        (hC)
#define		TabCtrl_GetRange(hC)				FrmCtrl_GetRange         (hC)
#define		TabCtrl_GetPosX(hC)				FrmCtrl_GetPosX          (hC)
#define		TabCtrl_GetPosY(hC)				FrmCtrl_GetPosY          (hC)
#define		TabCtrl_GetWidth(hC)				FrmCtrl_GetWidth         (hC)
#define		TabCtrl_GetHeight(hC)				FrmCtrl_GetHeight        (hC)
#define		TabCtrl_GetFont(hC)				FrmCtrl_GetFont          (hC)
#define		TabCtrl_GetColorTbl(hC)				FrmCtrl_GetColorTbl      (hC)
#define		TabCtrl_GetColor(hC,T,I)			FrmCtrl_GetColor         (hC,T,I)
#define		TabCtrl_GetSysNotify(hC)			FrmCtrl_GetSysNotify     (hC)
#define		TabCtrl_GetAppNotify(hC)			FrmCtrl_GetAppNotify     (hC)
#define		TabCtrl_GetNotiMask(hC)				FrmCtrl_GetNotiMask      (hC)

#define		TabCtrl_PtInRange(hC,X,Y)			FrmCtrl_PtInRange        (hC,X,Y)
#define		TabCtrl_SetFocus(hC)				FrmCtrl_SetFocus         (hC)
#define		TabCtrl_KillFocus(hC)				FrmCtrl_KillFocus        (hC)

#define		TabCtrl_Handler(hC,M,W,L)			FrmCtrl_Handler          (hC,M,W,L)
#define		TabCtrl_Refresh(hC)				FrmCtrl_Refresh          (hC)
#define		TabCtrl_Paint(hC,R)				FrmCtrl_Paint            (hC,R)
#define		TabCtrl_KeyDown(hC,K,R)				FrmCtrl_KeyDown          (hC,K,R)
#define		TabCtrl_Timer(hC,R)				FrmCtrl_Timer            (hC,R)
#define		TabCtrl_Pointing(hC,A,X,Y,R)			FrmCtrl_Pointing         (hC,A,X,Y,R)

#define		TabCtrl_CreateDummyData(hC,N)			FrmCtrl_CreateDummyData  (hC,N)
#define		TabCtrl_SetDummyData(hC,I,D)			FrmCtrl_SetDummyData     (hC,I,D)
#define		TabCtrl_GetDummyData(hC,I)			FrmCtrl_GetDummyData     (hC,I)


#define		TabCtrl_SetClientRect(hC,X1,Y1,X2,Y2)	        FrmCtrl_SetClientRect    (hC,X1,Y1,X2,Y2)
#define		TabCtrl_SetClientPos(hC,X,Y)			FrmCtrl_SetClientPos     (hC,X,Y)
#define		TabCtrl_SetClientSize(hC,W,H)			FrmCtrl_SetClientSize    (hC,W,H)
#define		TabCtrl_SetDelta(hC,X,Y)			FrmCtrl_SetDelta         (hC,X,Y)
#define		TabCtrl_SetDelta2(hC,X,Y)			FrmCtrl_SetDelta2        (hC,X,Y)
#define		TabCtrl_SetTitle(hC,T)				FrmCtrl_SetTitle         (hC,T)

#define		TabCtrl_SetTitleFont(hC,F)			FrmCtrl_SetTitleFont     (hC,F)
#define		TabCtrl_SetTitleHeight(hC,H)			FrmCtrl_SetTitleHeight   (hC,H)
#define		TabCtrl_SetTitleLeftMargin(hC,X)		FrmCtrl_SetTitleLeftMargin(hC,X)
#define		TabCtrl_SetTitleRightMargin(hC,X)		FrmCtrl_SetTitleRightMargin(hC,X)

#define		TabCtrl_GetClientRect(hC)			FrmCtrl_GetClientRect    (hC)
#define		TabCtrl_GetClientPosX(hC)			FrmCtrl_GetClientPosX    (hC)
#define		TabCtrl_GetClientPosY(hC)			FrmCtrl_GetClientPosY    (hC)
#define		TabCtrl_GetClientWidth(hC)			FrmCtrl_GetClientWidth   (hC)
#define		TabCtrl_GetClientHeight(hC)			FrmCtrl_GetClientHeight  (hC)
#define		TabCtrl_GetWorkArea(hC)				FrmCtrl_GetWorkArea      (hC)
#define		TabCtrl_GetWorkPosX(hC)				FrmCtrl_GetWorkPosX      (hC)
#define		TabCtrl_GetWorkPosY(hC)				FrmCtrl_GetWorkPosY      (hC)
#define		TabCtrl_GetWorkWidth(hC)			FrmCtrl_GetWorkWidth     (hC)
#define		TabCtrl_GetWorkHeight(hC)			FrmCtrl_GetWorkHeight    (hC)
#define		TabCtrl_GetDeltaX1(hC)				FrmCtrl_GetDeltaX1       (hC)
#define		TabCtrl_GetDeltaY1(hC)				FrmCtrl_GetDeltaY1       (hC)
#define		TabCtrl_GetDeltaX2(hC)				FrmCtrl_GetDeltaX2       (hC)
#define		TabCtrl_GetDeltaY2(hC)				FrmCtrl_GetDeltaY2       (hC)
#define		TabCtrl_GetTitle(hC)				FrmCtrl_GetTitle         (hC)
#define		TabCtrl_GetTitleFont(hC)			FrmCtrl_GetTitleFont     (hC)
#define		TabCtrl_GetTitleHeight(hC)			FrmCtrl_GetTitleHeight   (hC)
#define		TabCtrl_GetTitleLeftMargin(hC)			FrmCtrl_GetTitleLeftMargin(hC)
#define		TabCtrl_GetTitleRightMargin(hC)			FrmCtrl_GetTitleRightMargin(hC)

#define		TabCtrl_AdjustRange(hC)				FrmCtrl_AdjustRange      (hC)
#define		TabCtrl_AdjustClientRect(hC)			FrmCtrl_AdjustClientRect (hC)
#define		TabCtrl_AdjustScrollBar(hC)			FrmCtrl_AdjustScrollBar  (hC)
#define		TabCtrl_PtInClientRect(hC,X,Y)			FrmCtrl_PtInClientRect   (hC,X,Y)

#endif	//	_BNSOFT_PEANUT_TABCTRL_MACROFUNC_H_
