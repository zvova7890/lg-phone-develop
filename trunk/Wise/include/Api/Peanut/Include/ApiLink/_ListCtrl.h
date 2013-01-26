/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	PEANUT LIST CONTROL APILINK

	Copyright(c) 1997-2003 BNSoft Corp.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT__PEANUT_LISTCTRL_H_
#define		_BNSOFT__PEANUT_LISTCTRL_H_

#include	"..\ListCtrl.h"

typedef H_CTRL			(*T_pfnListCtrl_Create)          (void* pOwner, T_POS X, T_POS Y, T_SIZE W, T_SIZE H);
typedef BOOL			(*T_pfnListCtrl_Destroy)         (H_CTRL hLC);
typedef BOOL			(*T_pfnListCtrl_SetLineGap)      (H_CTRL hLC, int LineGap);
typedef BOOL			(*T_pfnListCtrl_SetInvOffset)    (H_CTRL hLC, int InvOffset);
typedef BOOL			(*T_pfnListCtrl_SetStr)          (H_CTRL hLC, int Index, T_CSTR pcszStr);
typedef BOOL			(*T_pfnListCtrl_SetData)         (H_CTRL hLC, int Index, QUAD Data);
typedef BOOL			(*T_pfnListCtrl_SetIcon)         (H_CTRL hLC, int Index, QUAD IconID);
typedef BOOL			(*T_pfnListCtrl_SetIconEx)       (H_CTRL hLC, int Index, int IconIndex, QUAD IconID, int BasePos, int Dist);
typedef BOOL			(*T_pfnListCtrl_SetLeftMargin)   (H_CTRL hLC, int LeftMargin);
typedef BOOL			(*T_pfnListCtrl_SetRightMargin)  (H_CTRL hLC, int RightMargin);
typedef BOOL			(*T_pfnListCtrl_SetMultiLineNum) (H_CTRL hLC, T_NUM MultiLineNum);
typedef TListItem*		(*T_pfnListCtrl_GetItem)         (H_CTRL hLC, int Index);
typedef T_CSTR			(*T_pfnListCtrl_GetStr)          (H_CTRL hLC, int Index);
typedef QUAD			(*T_pfnListCtrl_GetData)         (H_CTRL hLC, int Index);
typedef WORD			(*T_pfnListCtrl_GetStatus)       (H_CTRL hLC, int Index);
typedef WORD			(*T_pfnListCtrl_GetIcon)         (H_CTRL hLC, int Index);
typedef int			(*T_pfnListCtrl_GetLeftMargin)   (H_CTRL hLC);
typedef int			(*T_pfnListCtrl_GetRightMargin)  (H_CTRL hLC);
typedef T_NUM			(*T_pfnListCtrl_GetMultiLineNum) (H_CTRL hLC);
typedef int			(*T_pfnListCtrl_GetSelIndex)     (H_CTRL hLC);
typedef TListItem*		(*T_pfnListCtrl_GetSelItem)      (H_CTRL hLC);
typedef T_CSTR			(*T_pfnListCtrl_GetSelStr)       (H_CTRL hLC);
typedef QUAD			(*T_pfnListCtrl_GetSelData)      (H_CTRL hLC);
typedef TRect*			(*T_pfnListCtrl_GetSelRange)     (H_CTRL hLC);
typedef int			(*T_pfnListCtrl_GetLineGap)      (H_CTRL hLC);
typedef int			(*T_pfnListCtrl_GetInvOffset)    (H_CTRL hLC);
typedef int			(*T_pfnListCtrl_GetItemNum)      (H_CTRL hLC);
typedef BOOL			(*T_pfnListCtrl_AttachIconList)  (H_CTRL hLC, T_HANDLE hIconList);
typedef BOOL			(*T_pfnListCtrl_ResetAllItems)   (H_CTRL hLC);
typedef BOOL			(*T_pfnListCtrl_ResetTicker)     (H_CTRL hLC);
typedef BOOL			(*T_pfnListCtrl_AddItem)         (H_CTRL hLC, T_CSTR pcszStr, QUAD Data, QUAD IconID);
typedef BOOL			(*T_pfnListCtrl_AddSeparator)    (H_CTRL hLC);
typedef BOOL			(*T_pfnListCtrl_InsertItem)      (H_CTRL hLC, int Index, T_CSTR pcszStr, QUAD Data, QUAD IconID);
typedef BOOL			(*T_pfnListCtrl_DeleteItem)      (H_CTRL hLC, int Index);
typedef BOOL			(*T_pfnListCtrl_SelectItem)      (H_CTRL hLC, int Index);
typedef int			(*T_pfnListCtrl_SelectNextItem)  (H_CTRL hLC);
typedef int			(*T_pfnListCtrl_SelectPrevItem)  (H_CTRL hLC);
typedef BOOL			(*T_pfnListCtrl_SetStatus)       (H_CTRL hLC, int Index, WORD RemoveStatus, WORD AddStatus);
typedef BOOL			(*T_pfnListCtrl_CheckItem)       (H_CTRL hLC, int Index, BOOL bCheck);
typedef BOOL			(*T_pfnListCtrl_EnableItem)      (H_CTRL hLC, int Index, BOOL bEnable);
typedef BOOL			(*T_pfnListCtrl_EnsureVisible)   (H_CTRL hLC, int Index);
typedef T_SIZE			(*T_pfnListCtrl_CalcFullHeight)  (H_CTRL hLC);
typedef BOOL			(*T_pfnListCtrl_SetHighlight)	 (H_CTRL hLC, int Index, T_CSTR pcszStr, T_COLOR Color, QUAD Data);	//@lima++ [2007-11-30¿ÀÈÄ 12:00:01], 
typedef BOOL			(*T_pfnListCtrl_GetHighlightInfo)(H_CTRL hLC, int Index, TListHighLight* pInfo);
typedef BOOL			(*T_pfnListCtrl_SetItemHeight)	 (H_CTRL hLC, int Index, T_SIZE Height);
typedef T_SIZE			(*T_pfnListCtrl_GetItemHeight)	 (H_CTRL hLC, int Index);
typedef BOOL			(*T_pfnListCtrl_SetItemCtrl)	 (H_CTRL hLC, int Index, T_ID ID, H_CTRL hCtrl);
typedef H_CTRL			(*T_pfnListCtrl_GetItemCtrl)	 (H_CTRL hLC, int Index, T_ID ID);

typedef struct
{
	T_pfnListCtrl_Create			pfnCreate;
	T_pfnListCtrl_Destroy			pfnDestroy;
	T_pfnListCtrl_SetLineGap		pfnSetLineGap;
	T_pfnListCtrl_SetInvOffset		pfnSetInvOffset;
	T_pfnListCtrl_SetStr			pfnSetStr;
	T_pfnListCtrl_SetData			pfnSetData;
	T_pfnListCtrl_SetIcon			pfnSetIcon;
	T_pfnListCtrl_SetIconEx			pfnSetIconEx;
	T_pfnListCtrl_SetLeftMargin		pfnSetLeftMargin;
	T_pfnListCtrl_SetRightMargin		pfnSetRightMargin;
	T_pfnListCtrl_SetMultiLineNum		pfnSetMultiLineNum;
	T_pfnListCtrl_GetItem			pfnGetItem;
	T_pfnListCtrl_GetStr			pfnGetStr;
	T_pfnListCtrl_GetData			pfnGetData;
	T_pfnListCtrl_GetStatus			pfnGetStatus;
	T_pfnListCtrl_GetIcon			pfnGetIcon;
	T_pfnListCtrl_GetLeftMargin		pfnGetLeftMargin;
	T_pfnListCtrl_GetRightMargin		pfnGetRightMargin;
	T_pfnListCtrl_GetMultiLineNum		pfnGetMultiLineNum;
	T_pfnListCtrl_GetSelIndex		pfnGetSelIndex;
	T_pfnListCtrl_GetSelItem		pfnGetSelItem;
	T_pfnListCtrl_GetSelStr			pfnGetSelStr;
	T_pfnListCtrl_GetSelData		pfnGetSelData;
	T_pfnListCtrl_GetSelRange		pfnGetSelRange;
	T_pfnListCtrl_GetLineGap		pfnGetLineGap;
	T_pfnListCtrl_GetInvOffset		pfnGetInvOffset;
	T_pfnListCtrl_GetItemNum		pfnGetItemNum;
	T_pfnListCtrl_AttachIconList		pfnAttachIconList;
	T_pfnListCtrl_ResetAllItems		pfnResetAllItems;
	T_pfnListCtrl_ResetTicker		pfnResetTicker;
	T_pfnListCtrl_AddItem			pfnAddItem;
	T_pfnListCtrl_AddSeparator		pfnAddSeparator;
	T_pfnListCtrl_InsertItem		pfnInsertItem;
	T_pfnListCtrl_DeleteItem		pfnDeleteItem;
	T_pfnListCtrl_SelectItem		pfnSelectItem;
	T_pfnListCtrl_SelectNextItem		pfnSelectNextItem;
	T_pfnListCtrl_SelectPrevItem		pfnSelectPrevItem;
	T_pfnListCtrl_SetStatus			pfnSetStatus;
	T_pfnListCtrl_CheckItem			pfnCheckItem;
	T_pfnListCtrl_EnableItem		pfnEnableItem;
	T_pfnListCtrl_EnsureVisible		pfnEnsureVisible;
	T_pfnListCtrl_CalcFullHeight		pfnCalcFullHeight;
	T_pfnListCtrl_SetItemHeight		pfnSetItemHeight;
	T_pfnListCtrl_GetItemHeight		pfnGetItemHeight;
	T_pfnListCtrl_SetHighlight		pfnSetHighlight;
	T_pfnListCtrl_GetHighlightInfo		pfnGetHighlightInfo;
	T_pfnListCtrl_SetItemCtrl		pfnSetItemCtrl;
	T_pfnListCtrl_GetItemCtrl		pfnGetItemCtrl;
} TApiGrp_ListCtrl;

#define		ListCtrl_Create(p1,p2,p3,p4,p5)			__ApiLink5(ListCtrl,Create,p1,p2,p3,p4,p5)
#define		ListCtrl_Destroy(p1)				__ApiLink1(ListCtrl,Destroy,p1)
#define		ListCtrl_SetLineGap(p1,p2)			__ApiLink2(ListCtrl,SetLineGap,p1,p2)
#define		ListCtrl_SetInvOffset(p1,p2)			__ApiLink2(ListCtrl,SetInvOffset,p1,p2)
#define		ListCtrl_SetStr(p1,p2,p3)			__ApiLink3(ListCtrl,SetStr,p1,p2,p3)
#define		ListCtrl_SetData(p1,p2,p3)			__ApiLink3(ListCtrl,SetData,p1,p2,p3)
#define		ListCtrl_SetIcon(p1,p2,p3)			__ApiLink3(ListCtrl,SetIcon,p1,p2,p3)
#define		ListCtrl_SetIconEx(p1,p2,p3,p4,p5,p6)		__ApiLink6(ListCtrl,SetIconEx,p1,p2,p3,p4,p5,p6)
#define		ListCtrl_SetLeftMargin(p1,p2)			__ApiLink2(ListCtrl,SetLeftMargin,p1,p2)
#define		ListCtrl_SetRightMargin(p1,p2)			__ApiLink2(ListCtrl,SetRightMargin,p1,p2)
#define		ListCtrl_SetMultiLineNum(p1,p2)			__ApiLink2(ListCtrl,SetMultiLineNum,p1,p2)
#define		ListCtrl_GetItem(p1,p2)				__ApiLink2(ListCtrl,GetItem,p1,p2)
#define		ListCtrl_GetStr(p1,p2)				__ApiLink2(ListCtrl,GetStr,p1,p2)
#define		ListCtrl_GetData(p1,p2)				__ApiLink2(ListCtrl,GetData,p1,p2)
#define		ListCtrl_GetStatus(p1,p2)			__ApiLink2(ListCtrl,GetStatus,p1,p2)
#define		ListCtrl_GetIcon(p1,p2)				__ApiLink2(ListCtrl,GetIcon,p1,p2)
#define		ListCtrl_GetLeftMargin(p1)			__ApiLink1(ListCtrl,GetLeftMargin,p1)
#define		ListCtrl_GetRightMargin(p1)			__ApiLink1(ListCtrl,GetRightMargin,p1)
#define		ListCtrl_GetMultiLineNum(p1)			__ApiLink1(ListCtrl,GetMultiLineNum,p1)
#define		ListCtrl_GetSelIndex(p1)			__ApiLink1(ListCtrl,GetSelIndex,p1)
#define		ListCtrl_GetSelItem(p1)				__ApiLink1(ListCtrl,GetSelItem,p1)
#define		ListCtrl_GetSelStr(p1)				__ApiLink1(ListCtrl,GetSelStr,p1)
#define		ListCtrl_GetSelData(p1)				__ApiLink1(ListCtrl,GetSelData,p1)
#define		ListCtrl_GetSelRange(p1)			__ApiLink1(ListCtrl,GetSelRange,p1)
#define		ListCtrl_GetLineGap(p1)				__ApiLink1(ListCtrl,GetLineGap,p1)
#define		ListCtrl_GetInvOffset(p1)			__ApiLink1(ListCtrl,GetInvOffset,p1)
#define		ListCtrl_GetItemNum(p1)				__ApiLink1(ListCtrl,GetItemNum,p1)
#define		ListCtrl_AttachIconList(p1,p2)			__ApiLink2(ListCtrl,AttachIconList,p1,p2)
#define		ListCtrl_ResetAllItems(p1)			__ApiLink1(ListCtrl,ResetAllItems,p1)
#define		ListCtrl_ResetTicker(p1)			__ApiLink1(ListCtrl,ResetTicker,p1)
#define		ListCtrl_AddItem(p1,p2,p3,p4)			__ApiLink4(ListCtrl,AddItem,p1,p2,p3,p4)
#define		ListCtrl_AddSeparator(p1)			__ApiLink1(ListCtrl,AddSeparator,p1)
#define		ListCtrl_InsertItem(p1,p2,p3,p4,p5)		__ApiLink5(ListCtrl,InsertItem,p1,p2,p3,p4,p5)
#define		ListCtrl_DeleteItem(p1,p2)			__ApiLink2(ListCtrl,DeleteItem,p1,p2)
#define		ListCtrl_SelectItem(p1,p2)			__ApiLink2(ListCtrl,SelectItem,p1,p2)
#define		ListCtrl_SelectNextItem(p1)			__ApiLink1(ListCtrl,SelectNextItem,p1)
#define		ListCtrl_SelectPrevItem(p1)			__ApiLink1(ListCtrl,SelectPrevItem,p1)
#define		ListCtrl_SetStatus(p1,p2,p3,p4)			__ApiLink4(ListCtrl,SetStatus,p1,p2,p3,p4)
#define		ListCtrl_CheckItem(p1,p2,p3)			__ApiLink3(ListCtrl,CheckItem,p1,p2,p3)
#define		ListCtrl_EnableItem(p1,p2,p3)			__ApiLink3(ListCtrl,EnableItem,p1,p2,p3)
#define		ListCtrl_EnsureVisible(p1,p2)			__ApiLink2(ListCtrl,EnsureVisible,p1,p2)
#define		ListCtrl_CalcFullHeight(p1)			__ApiLink1(ListCtrl,CalcFullHeight,p1)
#define		ListCtrl_SetHighlight(p1,p2,p3,p4,p5)		__ApiLink5(ListCtrl,SetHighlight,p1,p2,p3,p4,p5)
#define		ListCtrl_GetHighlightInfo(p1,p2,p3)		__ApiLink3(ListCtrl,GetHighlightInfo,p1,p2,p3)

#define		ListCtrl_SetItemHeight(p1,p2,p3)		__ApiLink3(ListCtrl,SetItemHeight,p1,p2,p3)
#define		ListCtrl_GetItemHeight(p1,p2)			__ApiLink2(ListCtrl,GetItemHeight,p1,p2)
#define		ListCtrl_SetItemCtrl(p1,p2,p3,p4)		__ApiLink4(ListCtrl,SetItemCtrl,p1,p2,p3,p4)
#define		ListCtrl_GetItemCtrl(p1,p2,p3)			__ApiLink3(ListCtrl,GetItemCtrl,p1,p2,p3) 

#endif	//	_BNSOFT__PEANUT_LISTCTRL_H_
