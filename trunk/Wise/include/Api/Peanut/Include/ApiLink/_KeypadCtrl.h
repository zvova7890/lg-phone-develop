/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	PEANUT KEYPAD CONTROL APILINK

	Copyright(c)     -2007 LG Electronics Inc.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT__PEANUT_KEYPADCTRL_H_
#define		_BNSOFT__PEANUT_KEYPADCTRL_H_

#include	"..\KeypadCtrl.h"

typedef H_CTRL			(*T_pfnKeypadCtrl_Create)		(void* pOwner, T_POS X, T_POS Y, T_SIZE W, T_SIZE H);
typedef BOOL			(*T_pfnKeypadCtrl_Destroy)		(H_CTRL hKC);
typedef BOOL			(*T_pfnKeypadCtrl_ResetAllItems)	(H_CTRL hKC);
typedef BOOL			(*T_pfnKeypadCtrl_AddItem)		(H_CTRL hKC, T_CSTR pcszStr, TRect Rect, KEY Key, QUAD Data, QUAD IconID);
typedef BOOL			(*T_pfnKeypadCtrl_DeleteItem)		(H_CTRL hKC, int Index);
typedef BOOL			(*T_pfnKeypadCtrl_EnableItem)		(H_CTRL hKC, int Index, BOOL bEnable);
typedef T_NUM			(*T_pfnKeypadCtrl_GetItemNum)		(H_CTRL hKC);
typedef BOOL			(*T_pfnKeypadCtrl_SetCtrl)		(H_CTRL hKC, H_CTRL hCtrl);
typedef BOOL			(*T_pfnKeypadCtrl_SetBkImage)		(H_CTRL hKC, TImage* pImage);
typedef BOOL			(*T_pfnKeypadCtrl_SetAlphablendLevel)	(H_CTRL hKC, BYTE Level);
typedef H_CTRL			(*T_pfnKeypadCtrl_GetCtrl)		(H_CTRL hKC);
typedef TImage*			(*T_pfnKeypadCtrl_GetBkImage)		(H_CTRL hKC);
typedef BYTE			(*T_pfnKeypadCtrl_GetAlphablendLevel)	(H_CTRL hKC);
typedef BOOL			(*T_pfnKeypadCtrl_SetMethod)		(H_CTRL hKC, QUAD Method);
typedef BOOL			(*T_pfnKeypadCtrl_SetEnableMethod)	(H_CTRL hKC, QUAD Methods);
typedef QUAD			(*T_pfnKeypadCtrl_GetMethod)		(H_CTRL hKC);
typedef QUAD			(*T_pfnKeypadCtrl_GetEnableMethod)	(H_CTRL hKC);
typedef BOOL			(*T_pfnKeypadCtrl_SetItemStr)		(H_CTRL hKC, int Index, T_CSTR pcszStr);
typedef BOOL			(*T_pfnKeypadCtrl_SetItemRange)		(H_CTRL hKC, int Index, TRect Rect);
typedef BOOL			(*T_pfnKeypadCtrl_SetItemKey)		(H_CTRL hKC, int Index, KEY Key);
typedef BOOL			(*T_pfnKeypadCtrl_SetItemData)		(H_CTRL hKC, int Index, QUAD Data);
typedef BOOL			(*T_pfnKeypadCtrl_SetItemIcon)		(H_CTRL hKC, int Index, QUAD IconID);
typedef T_CSTR			(*T_pfnKeypadCtrl_GetItemStr)		(H_CTRL hKC, int Index);
typedef TRect*			(*T_pfnKeypadCtrl_GetItemRange)		(H_CTRL hKC, int Index);
typedef KEY			(*T_pfnKeypadCtrl_GetItemKey)		(H_CTRL hKC, int Index);
typedef QUAD			(*T_pfnKeypadCtrl_GetItemData)		(H_CTRL hKC, int Index);
typedef QUAD			(*T_pfnKeypadCtrl_GetItemIcon)		(H_CTRL hKC, int Index);
typedef	BOOL			(*T_pfnKeypadCtrl_SetQwertyMode)	(H_CTRL hKC, E_QWERTYMODE enMode);
typedef E_QWERTYMODE	(*T_pfnKeypadCtrl_GetQwertyMode)		(H_CTRL hKC);
typedef	BOOL			(*T_pfnKeypadCtrl_EnableQwertyCapsLock)	(H_CTRL hKC, BOOL bEnable);
typedef BOOL			(*T_pfnKeypadCtrl_IsQwertyCapsLock)	(H_CTRL hKC);
typedef BOOL			(*T_pfnKeypadCtrl_SetNextQwertyMode)	(H_CTRL hKC);
typedef BOOL			(*T_pfnKeypadCtrl_AddStatusItem)	(H_CTRL hKC, TRect Rect, QUAD ItemType, QUAD IconID);
typedef BOOL			(*T_pfnKeypadCtrl_DeleteStatusItem)	(H_CTRL hKC, QUAD ItemType);
typedef BOOL			(*T_pfnKeypadCtrl_EnableStatusItem)	(H_CTRL hKC, QUAD ItemType, BOOL bEnable);
typedef BOOL			(*T_pfnKeypadCtrl_ReplaceStatusItem)	(H_CTRL hKC, QUAD ItemType, QUAD NewItemType);
typedef BOOL			(*T_pfnKeypadCtrl_SetStatusItem)	(H_CTRL hKC, int Index, QUAD ItemType);
typedef BOOL			(*T_pfnKeypadCtrl_SetStatusItemRange)	(H_CTRL hKC, QUAD ItemType, TRect Rect);
typedef BOOL			(*T_pfnKeypadCtrl_SetStatusItemIcon)	(H_CTRL hKC, QUAD ItemType, QUAD IconID);
typedef TRect*			(*T_pfnKeypadCtrl_GetStatusItemRange)	(H_CTRL hKC, QUAD ItemType);
typedef QUAD			(*T_pfnKeypadCtrl_GetStatusItemIcon)	(H_CTRL hKC, QUAD ItemType);
typedef BOOL			(*T_pfnKeypadCtrl_DrawStatusItem)	(H_CTRL hKC);
typedef BOOL			(*T_pfnKeypadCtrl_SetKeypadOn)		(H_CTRL hKC, BOOL bUseKeypad);
typedef BOOL			(*T_pfnKeypadCtrl_GetKeypad)		(H_CTRL hKC);
typedef BOOL			(*T_pfnKeypadCtrl_IsKeypadOn)		(H_CTRL hKC);
typedef BOOL			(*T_pfnKeypadCtrl_ClearAllStates)	(H_CTRL hKC);

typedef struct
{
	T_pfnKeypadCtrl_Create				pfnCreate;
	T_pfnKeypadCtrl_Destroy				pfnDestroy;
	T_pfnKeypadCtrl_ResetAllItems			pfnResetAllItems;
	T_pfnKeypadCtrl_AddItem				pfnAddItem;
	T_pfnKeypadCtrl_DeleteItem			pfnDeleteItem;
	T_pfnKeypadCtrl_EnableItem			pfnEnableItem;
	T_pfnKeypadCtrl_GetItemNum			pfnGetItemNum;
	T_pfnKeypadCtrl_SetCtrl				pfnSetCtrl;
	T_pfnKeypadCtrl_SetBkImage			pfnSetBkImage;
	T_pfnKeypadCtrl_SetAlphablendLevel		pfnSetAlphablendLevel;
	T_pfnKeypadCtrl_GetCtrl				pfnGetCtrl;
	T_pfnKeypadCtrl_GetBkImage			pfnGetBkImage;
	T_pfnKeypadCtrl_GetAlphablendLevel		pfnGetAlphablendLevel;
	T_pfnKeypadCtrl_SetMethod			pfnSetMethod;
	T_pfnKeypadCtrl_SetEnableMethod			pfnSetEnableMethod;
	T_pfnKeypadCtrl_GetMethod			pfnGetMethod;
	T_pfnKeypadCtrl_GetEnableMethod			pfnGetEnableMethod;
	T_pfnKeypadCtrl_SetItemStr			pfnSetItemStr;
	T_pfnKeypadCtrl_SetItemRange			pfnSetItemRange;
	T_pfnKeypadCtrl_SetItemKey			pfnSetItemKey;
	T_pfnKeypadCtrl_SetItemData			pfnSetItemData;
	T_pfnKeypadCtrl_SetItemIcon			pfnSetItemIcon;
	T_pfnKeypadCtrl_GetItemStr			pfnGetItemStr;
	T_pfnKeypadCtrl_GetItemRange			pfnGetItemRange;
	T_pfnKeypadCtrl_GetItemKey			pfnGetItemKey;
	T_pfnKeypadCtrl_GetItemData			pfnGetItemData;
	T_pfnKeypadCtrl_GetItemIcon			pfnGetItemIcon;
	T_pfnKeypadCtrl_SetQwertyMode			pfnSetQwertyMode;
	T_pfnKeypadCtrl_GetQwertyMode			pfnGetQwertyMode;
	T_pfnKeypadCtrl_EnableQwertyCapsLock	        pfnEnableQwertyCapsLock;
	T_pfnKeypadCtrl_IsQwertyCapsLock		pfnIsQwertyCapsLock;
	T_pfnKeypadCtrl_SetNextQwertyMode		pfnSetNextQwertyMode;
	T_pfnKeypadCtrl_AddStatusItem			pfnAddStatusItem;
	T_pfnKeypadCtrl_DeleteStatusItem		pfnDeleteStatusItem;
	T_pfnKeypadCtrl_EnableStatusItem		pfnEnableStatusItem;
	T_pfnKeypadCtrl_ReplaceStatusItem		pfnReplaceStatusItem;
	T_pfnKeypadCtrl_SetStatusItem			pfnSetStatusItem;
	T_pfnKeypadCtrl_SetStatusItemRange		pfnSetStatusItemRange;
	T_pfnKeypadCtrl_SetStatusItemIcon		pfnSetStatusItemIcon;
	T_pfnKeypadCtrl_GetStatusItemRange		pfnGetStatusItemRange;
	T_pfnKeypadCtrl_GetStatusItemIcon		pfnGetStatusItemIcon;
	T_pfnKeypadCtrl_DrawStatusItem			pfnDrawStatusItem;
	T_pfnKeypadCtrl_SetKeypadOn			pfnSetKeypadOn;
	T_pfnKeypadCtrl_GetKeypad			pfnGetKeypad;
	T_pfnKeypadCtrl_IsKeypadOn			pfnIsKeypadOn;
} TApiGrp_KeypadCtrl;


#define		KeypadCtrl_Create(p1,p2,p3,p4,p5)		__ApiLink5(KeypadCtrl,Create,p1,p2,p3,p4,p5)
#define		KeypadCtrl_Destroy(p1)				__ApiLink1(KeypadCtrl,Destroy,p1)
#define		KeypadCtrl_ResetAllItems(p1)			__ApiLink1(KeypadCtrl,ResetAllItems,p1)
#define		KeypadCtrl_AddItem(p1,p2,p3,p4,p5,p6)		__ApiLink6(KeypadCtrl,AddItem,p1,p2,p3,p4,p5,p6)
#define		KeypadCtrl_DeleteItem(p1,p2)			__ApiLink2(KeypadCtrl,DeleteItem,p1,p2)
#define		KeypadCtrl_EnableItem(p1,p2,p3)			__ApiLink3(KeypadCtrl,EnableItem,p1,p2,p3)
#define		KeypadCtrl_GetItemNum(p1)			__ApiLink1(KeypadCtrl,GetItemNum,p1)
#define		KeypadCtrl_SetCtrl(p1,p2)			__ApiLink2(KeypadCtrl,SetCtrl,p1,p2)
#define		KeypadCtrl_SetBkImage(p1,p2)			__ApiLink2(KeypadCtrl,SetBkImage,p1,p2)
#define		KeypadCtrl_SetAlphablendLevel(p1,p2)		__ApiLink2(KeypadCtrl,SetAlphablendLevel,p1,p2)
#define		KeypadCtrl_GetCtrl(p1)				__ApiLink1(KeypadCtrl,GetCtrl,p1)
#define		KeypadCtrl_GetBkImage(p1)			__ApiLink1(KeypadCtrl,GetBkImage,p1)
#define		KeypadCtrl_GetAlphablendLevel(p1)		__ApiLink1(KeypadCtrl,GetAlphablendLevel,p1)
#define		KeypadCtrl_SetMethod(p1,p2)			__ApiLink2(KeypadCtrl,SetMethod,p1,p2)
#define		KeypadCtrl_SetEnableMethod(p1,p2)		__ApiLink2(KeypadCtrl,SetEnableMethod,p1,p2)
#define		KeypadCtrl_GetMethod(p1)			__ApiLink1(KeypadCtrl,GetMethod,p1)
#define		KeypadCtrl_GetEnableMethod(p1)			__ApiLink1(KeypadCtrl,GetEnableMethod,p1)
#define		KeypadCtrl_SetItemStr(p1,p2,p3)			__ApiLink3(KeypadCtrl,SetItemStr,p1,p2,p3)
#define		KeypadCtrl_SetItemRange(p1,p2,p3)		__ApiLink3(KeypadCtrl,SetItemRange,p1,p2,p3)
#define		KeypadCtrl_SetItemKey(p1,p2,p3)			__ApiLink3(KeypadCtrl,SetItemKey,p1,p2,p3)
#define		KeypadCtrl_SetItemData(p1,p2,p3)		__ApiLink3(KeypadCtrl,SetItemData,p1,p2,p3)
#define		KeypadCtrl_SetItemIcon(p1,p2,p3)		__ApiLink3(KeypadCtrl,SetItemIcon,p1,p2,p3)	
#define		KeypadCtrl_GetItemStr(p1,p2)			__ApiLink2(KeypadCtrl,GetItemStr,p1,p2)
#define		KeypadCtrl_GetItemRange(p1,p2)			__ApiLink2(KeypadCtrl,GetItemRange,p1,p2)
#define		KeypadCtrl_GetItemKey(p1,p2)			__ApiLink2(KeypadCtrl,GetItemKey,p1,p2)
#define		KeypadCtrl_GetItemData(p1,p2)			__ApiLink2(KeypadCtrl,GetItemData,p1,p2)
#define		KeypadCtrl_GetItemIcon(p1,p2)			__ApiLink2(KeypadCtrl,GetItemIcon,p1,p2)
#define		KeypadCtrl_SetQwertyMode(p1,p2)			__ApiLink2(KeypadCtrl,SetQwertyMode,p1,p2)
#define		KeypadCtrl_GetQwertyMode(p1)			__ApiLink1(KeypadCtrl,GetQwertyMode,p1)
#define		KeypadCtrl_EnableQwertyCapsLock(p1,p2)		__ApiLink2(KeypadCtrl,EnableQwertyCapsLock,p1,p2)
#define		KeypadCtrl_IsQwertyCapsLock(p1)			__ApiLink1(KeypadCtrl,IsQwertyCapsLock,p1)
#define		KeypadCtrl_SetNextQwertyMode(p1)		__ApiLink1(KeypadCtrl,SetNextQwertyMode,p1)
#define		KeypadCtrl_AddStatusItem(p1,p2,p3,p4)		__ApiLink4(KeypadCtrl,AddStatusItem,p1,p2,p3,p4)
#define		KeypadCtrl_DeleteStatusItem(p1,p2)		__ApiLink2(KeypadCtrl,DeleteStatusItem,p1,p2)
#define		KeypadCtrl_EnableStatusItem(p1,p2,p3)		__ApiLink3(KeypadCtrl,EnableStatusItem,p1,p2,p3)
#define		KeypadCtrl_ReplaceStatusItem(p1,p2,p3)		__ApiLink3(KeypadCtrl,ReplaceStatusItem,p1,p2,p3)
#define		KeypadCtrl_SetStatusItem(p1,p2,p3)		__ApiLink3(KeypadCtrl,SetStatusItem,p1,p2,p3)
#define		KeypadCtrl_SetStatusItemRange(p1,p2,p3)		__ApiLink3(KeypadCtrl,SetStatusItemRange,p1,p2,p3)
#define		KeypadCtrl_SetStatusItemIcon(p1,p2,p3)		__ApiLink3(KeypadCtrl,SetStatusItemIcon,p1,p2,p3)
#define		KeypadCtrl_GetStatusItemRange(p1,p2)		__ApiLink2(KeypadCtrl,GetStatusItemRange,p1,p2)
#define		KeypadCtrl_GetStatusItemIcon(p1,p2)		__ApiLink2(KeypadCtrl,GetStatusItemIcon,p1,p2)
#define		KeypadCtrl_DrawStatusItem(p1)			__ApiLink1(KeypadCtrl,DrawStatusItem,p1)
#define		KeypadCtrl_SetKeypadOn(p1,p2)			__ApiLink2(KeypadCtrl,SetKeypadOn,p1,p2)
#define		KeypadCtrl_GetKeypad(p1)			__ApiLink1(KeypadCtrl,GetKeypad,p1)
#define		KeypadCtrl_IsKeypadOn(p1)			__ApiLink1(KeypadCtrl,IsKeypadOn,p1)

#endif	//	_BNSOFT__PEANUT_KEYPADCTRL_H_

