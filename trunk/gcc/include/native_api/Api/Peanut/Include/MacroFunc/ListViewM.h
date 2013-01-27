/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	PEANUT LIST CONTROL MACRO FUNCTIONS

	Copyright(c) 1997-2003 BNSoft Corp.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT_PEANUT_ListView_MACROFUNC_H_
#define		_BNSOFT_PEANUT_ListView_MACROFUNC_H_

#define		ListView_SetOwner(hC,O)				FrmCtrl_SetOwner         (hC,O)
#define		ListView_SetType(hC,T)				FrmCtrl_SetType          (hC,T)
#define		ListView_SetOemType(hC,T)			FrmCtrl_SetOemType       (hC,T)
#define		ListView_ModifyOemType(hC,R,A)			FrmCtrl_ModifyOemType    (hC,R,A)
#define		ListView_ModifyStyle(hC,R,A)			FrmCtrl_ModifyStyle      (hC,R,A)
#define		ListView_SetState(hC,S)				FrmCtrl_SetState         (hC,S)
#define		ListView_SetVisible(hC,O)			FrmCtrl_SetVisible       (hC,O)
#define		ListView_SetEnable(hC,O)			FrmCtrl_SetEnable        (hC,O)
#define		ListView_SetCanFocus(hC,O)			FrmCtrl_SetCanFocus      (hC,O)
#define		ListView_SetRange(hC,X1,Y1,X2,Y2)		FrmCtrl_SetRange         (hC,X1,Y1,X2,Y2)
#define		ListView_SetPos(hC,X,Y)				FrmCtrl_SetPos           (hC,X,Y)
#define		ListView_SetSize(hC,W,H)			FrmCtrl_SetSize          (hC,W,H)
#define		ListView_SetFont(hC,F)				FrmCtrl_SetFont          (hC,F)
#define		ListView_SetColorTbl(hC,pCT)			FrmCtrl_SetColorTbl      (hC,pCT)
#define		ListView_SetColor(hC,T,I,C)			FrmCtrl_SetColor         (hC,T,I,C)
#define		ListView_SetSysNotifyProc(hC,N)			FrmCtrl_SetSysNotifyProc (hC,N)
#define		ListView_SetAppNotifyProc(hC,I,M,N)		FrmCtrl_SetAppNotifyProc (hC,I,M,N)
#define		ListView_ModifyNotiMask(hC,R,A)			FrmCtrl_ModifyNotiMask   (hC,R,A)

#define		ListView_GetOwner(hC)				FrmCtrl_GetOwner         (hC)
#define		ListView_GetType(hC)				FrmCtrl_GetType          (hC)
#define		ListView_GetOemType(hC)				FrmCtrl_GetOemType       (hC)
#define		ListView_GetStyle(hC)				FrmCtrl_GetStyle         (hC)
#define		ListView_GetState(hC)				FrmCtrl_GetState         (hC)
#define		ListView_IsVisible(hC)				FrmCtrl_IsVisible        (hC)
#define		ListView_IsEnable(hC)				FrmCtrl_IsEnable         (hC)
#define		ListView_IsCanFocus(hC)				FrmCtrl_IsCanFocus       (hC)
#define		ListView_IsFocused(hC)				FrmCtrl_IsFocused        (hC)
#define		ListView_GetRange(hC)				FrmCtrl_GetRange         (hC)
#define		ListView_GetPosX(hC)				FrmCtrl_GetPosX          (hC)
#define		ListView_GetPosY(hC)				FrmCtrl_GetPosY          (hC)
#define		ListView_GetWidth(hC)				FrmCtrl_GetWidth         (hC)
#define		ListView_GetHeight(hC)				FrmCtrl_GetHeight        (hC)
#define		ListView_GetFont(hC)				FrmCtrl_GetFont          (hC)
#define		ListView_GetColorTbl(hC)			FrmCtrl_GetColorTbl      (hC)
#define		ListView_GetColor(hC,T,I)			FrmCtrl_GetColor         (hC,T,I)
#define		ListView_GetSysNotify(hC)			FrmCtrl_GetSysNotify     (hC)
#define		ListView_GetAppNotify(hC)			FrmCtrl_GetAppNotify     (hC)
#define		ListView_GetNotiMask(hC)			FrmCtrl_GetNotiMask      (hC)

#define		ListView_PtInRange(hC,X,Y)			FrmCtrl_PtInRange        (hC,X,Y)
#define		ListView_SetFocus(hC)				FrmCtrl_SetFocus         (hC)
#define		ListView_KillFocus(hC)				FrmCtrl_KillFocus        (hC)

#define		ListView_Handler(hC,M,W,L)			FrmCtrl_Handler          (hC,M,W,L)
#define		ListView_Refresh(hC)				FrmCtrl_Refresh          (hC)
#define		ListView_Paint(hC,R)				FrmCtrl_Paint            (hC,R)
#define		ListView_KeyDown(hC,K,R)			FrmCtrl_KeyDown          (hC,K,R)
#define		ListView_Timer(hC,R)				FrmCtrl_Timer            (hC,R)
#define		ListView_Pointing(hC,A,X,Y,R)			FrmCtrl_Pointing         (hC,A,X,Y,R)

#define		ListView_CreateDummyData(hC,N)			FrmCtrl_CreateDummyData  (hC,N)
#define		ListView_SetDummyData(hC,I,D)			FrmCtrl_SetDummyData     (hC,I,D)
#define		ListView_GetDummyData(hC,I)			FrmCtrl_GetDummyData     (hC,I)


#define		ListView_SetClientRect(hC,X1,Y1,X2,Y2)	        FrmCtrl_SetClientRect    (hC,X1,Y1,X2,Y2)
#define		ListView_SetClientPos(hC,X,Y)			FrmCtrl_SetClientPos     (hC,X,Y)
#define		ListView_SetClientSize(hC,W,H)			FrmCtrl_SetClientSize    (hC,W,H)
#define		ListView_SetDelta(hC,X,Y)			FrmCtrl_SetDelta         (hC,X,Y)
#define		ListView_SetDelta2(hC,X,Y)			FrmCtrl_SetDelta2        (hC,X,Y)
#define		ListView_SetTitle(hC,T)				FrmCtrl_SetTitle         (hC,T)
#define		ListView_SetTitleFont(hC,F)			FrmCtrl_SetTitleFont     (hC,F)
#define		ListView_SetTitleHeight(hC,H)			FrmCtrl_SetTitleHeight   (hC,H)
#define		ListView_SetTitleLeftMargin(hC,X)		FrmCtrl_SetTitleLeftMargin(hC,X)
#define		ListView_SetTitleRightMargin(hC,X)		FrmCtrl_SetTitleRightMargin(hC,X)

#define		ListView_GetClientRect(hC)			FrmCtrl_GetClientRect    (hC)
#define		ListView_GetClientPosX(hC)			FrmCtrl_GetClientPosX    (hC)
#define		ListView_GetClientPosY(hC)			FrmCtrl_GetClientPosY    (hC)
#define		ListView_GetClientWidth(hC)			FrmCtrl_GetClientWidth   (hC)
#define		ListView_GetClientHeight(hC)			FrmCtrl_GetClientHeight  (hC)
#define		ListView_GetWorkArea(hC)			FrmCtrl_GetWorkArea      (hC)
#define		ListView_GetWorkPosX(hC)			FrmCtrl_GetWorkPosX      (hC)
#define		ListView_GetWorkPosY(hC)			FrmCtrl_GetWorkPosY      (hC)
#define		ListView_GetWorkWidth(hC)			FrmCtrl_GetWorkWidth     (hC)
#define		ListView_GetWorkHeight(hC)			FrmCtrl_GetWorkHeight    (hC)
#define		ListView_GetDeltaX1(hC)				FrmCtrl_GetDeltaX1       (hC)
#define		ListView_GetDeltaY1(hC)				FrmCtrl_GetDeltaY1       (hC)
#define		ListView_GetDeltaX2(hC)				FrmCtrl_GetDeltaX2       (hC)
#define		ListView_GetDeltaY2(hC)				FrmCtrl_GetDeltaY2       (hC)
#define		ListView_GetTitle(hC)				FrmCtrl_GetTitle         (hC)
#define		ListView_GetTitleFont(hC)			FrmCtrl_GetTitleFont     (hC)
#define		ListView_GetTitleHeight(hC)			FrmCtrl_GetTitleHeight   (hC)
#define		ListView_GetTitleLeftMargin(hC)			FrmCtrl_GetTitleLeftMargin(hC)
#define		ListView_GetTitleRightMargin(hC)		FrmCtrl_GetTitleRightMargin(hC)

#define		ListView_AdjustRange(hC)			FrmCtrl_AdjustRange      (hC)
#define		ListView_AdjustClientRect(hC)			FrmCtrl_AdjustClientRect (hC)
#define		ListView_AdjustScrollBar(hC)			FrmCtrl_AdjustScrollBar  (hC)
#define		ListView_PtInClientRect(hC,X,Y)			FrmCtrl_PtInClientRect   (hC,X,Y)

//-------------------------------------------------------------------------------------------------

#endif	//	_BNSOFT_PEANUT_ListView_MACROFUNC_H_
