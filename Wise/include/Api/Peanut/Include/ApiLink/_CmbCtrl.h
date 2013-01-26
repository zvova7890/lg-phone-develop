/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	PEANUT COMBO CONTROL APILINK

	Copyright(c) 1997-2003 BNSoft Corp.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT__PEANUT_CMBCTRL_H_
#define		_BNSOFT__PEANUT_CMBCTRL_H_

#include	"..\CmbCtrl.h"

typedef H_CTRL			(*T_pfnCmbCtrl_Create)           (void* pOwner, T_POS X, T_POS Y, T_SIZE W, T_SIZE H);
typedef BOOL			(*T_pfnCmbCtrl_Destroy)          (H_CTRL hCC);
typedef BOOL			(*T_pfnCmbCtrl_ModifyStyle)      (H_CTRL hCC, QUAD RemoveStyle, QUAD AddStyle);
typedef BOOL			(*T_pfnCmbCtrl_SetRange)         (H_CTRL hCC, T_POS X1, T_POS Y1, T_POS X2, T_POS Y2);
typedef BOOL			(*T_pfnCmbCtrl_SetPos)           (H_CTRL hCC, T_POS X, T_POS Y);
typedef BOOL			(*T_pfnCmbCtrl_SetSize)          (H_CTRL hCC, T_SIZE W, T_SIZE H);
typedef BOOL			(*T_pfnCmbCtrl_PtInRange)        (H_CTRL hCC, T_POS X, T_POS Y);
typedef BOOL			(*T_pfnCmbCtrl_SetFocus)         (H_CTRL hCC);
typedef BOOL			(*T_pfnCmbCtrl_KillFocus)        (H_CTRL hCC);
typedef BOOL			(*T_pfnCmbCtrl_SetMaxListHeight) (H_CTRL hCC, T_SIZE Height);
typedef H_CTRL			(*T_pfnCmbCtrl_GetEditHandle)    (H_CTRL hCC);
typedef H_CTRL			(*T_pfnCmbCtrl_GetListHandle)    (H_CTRL hCC);
typedef BOOL			(*T_pfnCmbCtrl_IsExpanded)       (H_CTRL hCC);
typedef T_SIZE			(*T_pfnCmbCtrl_GetMaxListHeight) (H_CTRL hCC);
typedef BOOL			(*T_pfnCmbCtrl_ResetAllItems)    (H_CTRL hCC);
typedef BOOL			(*T_pfnCmbCtrl_AddItem)          (H_CTRL hCC, T_CSTR pcszStr, QUAD Data, QUAD IconID);
typedef BOOL			(*T_pfnCmbCtrl_AddSeparator)     (H_CTRL hCC);
typedef BOOL			(*T_pfnCmbCtrl_SelectItem)       (H_CTRL hCC, int Index);
typedef int			(*T_pfnCmbCtrl_SelectNextItem)   (H_CTRL hCC);
typedef int			(*T_pfnCmbCtrl_SelectPrevItem)   (H_CTRL hCC);
typedef BOOL			(*T_pfnCmbCtrl_Expand)           (H_CTRL hCC);
typedef BOOL			(*T_pfnCmbCtrl_Collapse)         (H_CTRL hCC);

typedef struct
{
	T_pfnCmbCtrl_Create				pfnCreate;
	T_pfnCmbCtrl_Destroy				pfnDestroy;
	T_pfnCmbCtrl_ModifyStyle			pfnModifyStyle;
	T_pfnCmbCtrl_SetRange				pfnSetRange;
	T_pfnCmbCtrl_SetPos				pfnSetPos;
	T_pfnCmbCtrl_SetSize				pfnSetSize;
	T_pfnCmbCtrl_PtInRange				pfnPtInRange;
	T_pfnCmbCtrl_SetFocus				pfnSetFocus;
	T_pfnCmbCtrl_KillFocus				pfnKillFocus;
	T_pfnCmbCtrl_SetMaxListHeight		        pfnSetMaxListHeight;
	T_pfnCmbCtrl_GetEditHandle			pfnGetEditHandle;
	T_pfnCmbCtrl_GetListHandle			pfnGetListHandle;
	T_pfnCmbCtrl_IsExpanded				pfnIsExpanded;
	T_pfnCmbCtrl_GetMaxListHeight		        pfnGetMaxListHeight;
	T_pfnCmbCtrl_ResetAllItems			pfnResetAllItems;
	T_pfnCmbCtrl_AddItem				pfnAddItem;
	T_pfnCmbCtrl_AddSeparator			pfnAddSeparator;
	T_pfnCmbCtrl_SelectItem				pfnSelectItem;
	T_pfnCmbCtrl_SelectNextItem			pfnSelectNextItem;
	T_pfnCmbCtrl_SelectPrevItem			pfnSelectPrevItem;
	T_pfnCmbCtrl_Expand					pfnExpand;
	T_pfnCmbCtrl_Collapse				pfnCollapse;
} TApiGrp_CmbCtrl;


#define	CmbCtrl_Create(p1,p2,p3,p4,p5)			__ApiLink5(CmbCtrl,Create,p1,p2,p3,p4,p5)
#define	CmbCtrl_Destroy(p1)				__ApiLink1(CmbCtrl,Destroy,p1)
#define	CmbCtrl_ModifyStyle(p1,p2,p3)			__ApiLink3(CmbCtrl,ModifyStyle,p1,p2,p3)
#define	CmbCtrl_SetRange(p1,p2,p3,p4,p5)		__ApiLink5(CmbCtrl,SetRange,p1,p2,p3,p4,p5)
#define	CmbCtrl_SetPos(p1,p2,p3)			__ApiLink3(CmbCtrl,SetPos,p1,p2,p3)
#define	CmbCtrl_SetSize(p1,p2,p3)			__ApiLink3(CmbCtrl,SetSize,p1,p2,p3)
#define	CmbCtrl_PtInRange(p1,p2,p3)			__ApiLink3(CmbCtrl,PtInRange,p1,p2,p3)
#define	CmbCtrl_SetFocus(p1)				__ApiLink1(CmbCtrl,SetFocus,p1)
#define	CmbCtrl_KillFocus(p1)				__ApiLink1(CmbCtrl,KillFocus,p1)
#define	CmbCtrl_SetMaxListHeight(p1,p2)			__ApiLink2(CmbCtrl,SetMaxListHeight,p1,p2)
#define	CmbCtrl_GetEditHandle(p1)			__ApiLink1(CmbCtrl,GetEditHandle,p1)
#define	CmbCtrl_GetListHandle(p1)			__ApiLink1(CmbCtrl,GetListHandle,p1)
#define	CmbCtrl_IsExpanded(p1)				__ApiLink1(CmbCtrl,IsExpanded,p1)
#define	CmbCtrl_GetMaxListHeight(p1)			__ApiLink1(CmbCtrl,GetMaxListHeight,p1)
#define	CmbCtrl_ResetAllItems(p1)			__ApiLink1(CmbCtrl,ResetAllItems,p1)
#define	CmbCtrl_AddItem(p1,p2,p3,p4)			__ApiLink4(CmbCtrl,AddItem,p1,p2,p3,p4)
#define	CmbCtrl_AddSeparator(p1)			__ApiLink1(CmbCtrl,AddSeparator,p1)
#define	CmbCtrl_SelectItem(p1,p2)			__ApiLink2(CmbCtrl,SelectItem,p1,p2)
#define	CmbCtrl_SelectNextItem(p1)			__ApiLink1(CmbCtrl,SelectNextItem,p1)
#define	CmbCtrl_SelectPrevItem(p1)			__ApiLink1(CmbCtrl,SelectPrevItem,p1)
#define	CmbCtrl_Expand(p1)				__ApiLink1(CmbCtrl,Expand,p1)
#define	CmbCtrl_Collapse(p1)				__ApiLink1(CmbCtrl,Collapse,p1)


#endif	//	_BNSOFT__PEANUT_CMBCTRL_H_
