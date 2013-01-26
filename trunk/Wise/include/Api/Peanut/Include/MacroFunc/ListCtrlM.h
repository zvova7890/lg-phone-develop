/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	PEANUT LIST CONTROL MACRO FUNCTIONS

	Copyright(c) 1997-2003 BNSoft Corp.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT_PEANUT_LISTCTRL_MACROFUNC_H_
#define		_BNSOFT_PEANUT_LISTCTRL_MACROFUNC_H_

//-------------------------------------------------------------------------------------------------
//	ListCtrl Macro Member Functions
#define		ListCtrl_SetOwner(hC,O)				FrmCtrl_SetOwner         (hC,O)
#define		ListCtrl_SetType(hC,T)				FrmCtrl_SetType          (hC,T)
#define		ListCtrl_SetOemType(hC,T)			FrmCtrl_SetOemType       (hC,T)
#define		ListCtrl_ModifyOemType(hC,R,A)			FrmCtrl_ModifyOemType    (hC,R,A)
#define		ListCtrl_ModifyStyle(hC,R,A)			FrmCtrl_ModifyStyle      (hC,R,A)
#define		ListCtrl_SetState(hC,S)				FrmCtrl_SetState         (hC,S)
#define		ListCtrl_SetVisible(hC,O)			FrmCtrl_SetVisible       (hC,O)
#define		ListCtrl_SetEnable(hC,O)			FrmCtrl_SetEnable        (hC,O)
#define		ListCtrl_SetCanFocus(hC,O)			FrmCtrl_SetCanFocus      (hC,O)
#define		ListCtrl_SetRange(hC,X1,Y1,X2,Y2)		FrmCtrl_SetRange         (hC,X1,Y1,X2,Y2)
#define		ListCtrl_SetPos(hC,X,Y)				FrmCtrl_SetPos           (hC,X,Y)
#define		ListCtrl_SetSize(hC,W,H)			FrmCtrl_SetSize          (hC,W,H)
#define		ListCtrl_SetFont(hC,F)				FrmCtrl_SetFont          (hC,F)
#define		ListCtrl_SetColorTbl(hC,pCT)			FrmCtrl_SetColorTbl      (hC,pCT)
#define		ListCtrl_SetColor(hC,T,I,C)			FrmCtrl_SetColor         (hC,T,I,C)
#define		ListCtrl_SetSysNotifyProc(hC,N)			FrmCtrl_SetSysNotifyProc (hC,N)
#define		ListCtrl_SetAppNotifyProc(hC,I,M,N)		FrmCtrl_SetAppNotifyProc (hC,I,M,N)
#define		ListCtrl_ModifyNotiMask(hC,R,A)			FrmCtrl_ModifyNotiMask   (hC,R,A)

#define		ListCtrl_GetOwner(hC)				FrmCtrl_GetOwner         (hC)
#define		ListCtrl_GetType(hC)				FrmCtrl_GetType          (hC)
#define		ListCtrl_GetOemType(hC)				FrmCtrl_GetOemType       (hC)
#define		ListCtrl_GetStyle(hC)				FrmCtrl_GetStyle         (hC)
#define		ListCtrl_GetState(hC)				FrmCtrl_GetState         (hC)
#define		ListCtrl_IsVisible(hC)				FrmCtrl_IsVisible        (hC)
#define		ListCtrl_IsEnable(hC)				FrmCtrl_IsEnable         (hC)
#define		ListCtrl_IsCanFocus(hC)				FrmCtrl_IsCanFocus       (hC)
#define		ListCtrl_IsFocused(hC)				FrmCtrl_IsFocused        (hC)
#define		ListCtrl_GetRange(hC)				FrmCtrl_GetRange         (hC)
#define		ListCtrl_GetPosX(hC)				FrmCtrl_GetPosX          (hC)
#define		ListCtrl_GetPosY(hC)				FrmCtrl_GetPosY          (hC)
#define		ListCtrl_GetWidth(hC)				FrmCtrl_GetWidth         (hC)
#define		ListCtrl_GetHeight(hC)				FrmCtrl_GetHeight        (hC)
#define		ListCtrl_GetFont(hC)				FrmCtrl_GetFont          (hC)
#define		ListCtrl_GetColorTbl(hC)			FrmCtrl_GetColorTbl      (hC)
#define		ListCtrl_GetColor(hC,T,I)			FrmCtrl_GetColor         (hC,T,I)
#define		ListCtrl_GetSysNotify(hC)			FrmCtrl_GetSysNotify     (hC)
#define		ListCtrl_GetAppNotify(hC)			FrmCtrl_GetAppNotify     (hC)
#define		ListCtrl_GetNotiMask(hC)			FrmCtrl_GetNotiMask      (hC)

#define		ListCtrl_PtInRange(hC,X,Y)			FrmCtrl_PtInRange        (hC,X,Y)
#define		ListCtrl_SetFocus(hC)				FrmCtrl_SetFocus         (hC)
#define		ListCtrl_KillFocus(hC)				FrmCtrl_KillFocus        (hC)

#define		ListCtrl_Handler(hC,M,W,L)			FrmCtrl_Handler          (hC,M,W,L)
#define		ListCtrl_Refresh(hC)				FrmCtrl_Refresh          (hC)
#define		ListCtrl_Paint(hC,R)				FrmCtrl_Paint            (hC,R)
#define		ListCtrl_KeyDown(hC,K,R)			FrmCtrl_KeyDown          (hC,K,R)
#define		ListCtrl_Timer(hC,R)				FrmCtrl_Timer            (hC,R)
#define		ListCtrl_Pointing(hC,A,X,Y,R)			FrmCtrl_Pointing         (hC,A,X,Y,R)

#define		ListCtrl_CreateDummyData(hC,N)			FrmCtrl_CreateDummyData  (hC,N)
#define		ListCtrl_SetDummyData(hC,I,D)			FrmCtrl_SetDummyData     (hC,I,D)
#define		ListCtrl_GetDummyData(hC,I)			FrmCtrl_GetDummyData     (hC,I)

#define		ListCtrl_SetClientRect(hC,X1,Y1,X2,Y2)    	FrmCtrl_SetClientRect    (hC,X1,Y1,X2,Y2)
#define		ListCtrl_SetClientPos(hC,X,Y)			FrmCtrl_SetClientPos     (hC,X,Y)
#define		ListCtrl_SetClientSize(hC,W,H)			FrmCtrl_SetClientSize    (hC,W,H)
#define		ListCtrl_SetDelta(hC,X,Y)			FrmCtrl_SetDelta         (hC,X,Y)
#define		ListCtrl_SetDelta2(hC,X,Y)			FrmCtrl_SetDelta2        (hC,X,Y)
#define		ListCtrl_SetTitle(hC,T)				FrmCtrl_SetTitle         (hC,T)
#define		ListCtrl_SetTitleFont(hC,F)			FrmCtrl_SetTitleFont     (hC,F)
#define		ListCtrl_SetTitleHeight(hC,H)			FrmCtrl_SetTitleHeight   (hC,H)
#define		ListCtrl_SetTitleLeftMargin(hC,X)		FrmCtrl_SetTitleLeftMargin(hC,X)
#define		ListCtrl_SetTitleRightMargin(hC,X)		FrmCtrl_SetTitleRightMargin(hC,X)

#define		ListCtrl_GetClientRect(hC)			FrmCtrl_GetClientRect    (hC)
#define		ListCtrl_GetClientPosX(hC)			FrmCtrl_GetClientPosX    (hC)
#define		ListCtrl_GetClientPosY(hC)			FrmCtrl_GetClientPosY    (hC)
#define		ListCtrl_GetClientWidth(hC)			FrmCtrl_GetClientWidth   (hC)
#define		ListCtrl_GetClientHeight(hC)			FrmCtrl_GetClientHeight  (hC)
#define		ListCtrl_GetWorkArea(hC)			FrmCtrl_GetWorkArea      (hC)
#define		ListCtrl_GetWorkPosX(hC)			FrmCtrl_GetWorkPosX      (hC)
#define		ListCtrl_GetWorkPosY(hC)			FrmCtrl_GetWorkPosY      (hC)
#define		ListCtrl_GetWorkWidth(hC)			FrmCtrl_GetWorkWidth     (hC)
#define		ListCtrl_GetWorkHeight(hC)			FrmCtrl_GetWorkHeight    (hC)
#define		ListCtrl_GetDeltaX1(hC)				FrmCtrl_GetDeltaX1       (hC)
#define		ListCtrl_GetDeltaY1(hC)				FrmCtrl_GetDeltaY1       (hC)
#define		ListCtrl_GetDeltaX2(hC)				FrmCtrl_GetDeltaX2       (hC)
#define		ListCtrl_GetDeltaY2(hC)				FrmCtrl_GetDeltaY2       (hC)
#define		ListCtrl_GetTitle(hC)				FrmCtrl_GetTitle         (hC)
#define		ListCtrl_GetTitleFont(hC)			FrmCtrl_GetTitleFont     (hC)
#define		ListCtrl_GetTitleHeight(hC)			FrmCtrl_GetTitleHeight   (hC)
#define		ListCtrl_GetTitleLeftMargin(hC)			FrmCtrl_GetTitleLeftMargin(hC)
#define		ListCtrl_GetTitleRightMargin(hC)		FrmCtrl_GetTitleRightMargin(hC)

#define		ListCtrl_AdjustRange(hC)			FrmCtrl_AdjustRange      (hC)
#define		ListCtrl_AdjustClientRect(hC)			FrmCtrl_AdjustClientRect (hC)
#define		ListCtrl_AdjustScrollBar(hC)			FrmCtrl_AdjustScrollBar  (hC)
#define		ListCtrl_PtInClientRect(hC,X,Y)			FrmCtrl_PtInClientRect   (hC,X,Y)


#endif	//	_BNSOFT_PEANUT_LISTCTRL_MACROFUNC_H_
