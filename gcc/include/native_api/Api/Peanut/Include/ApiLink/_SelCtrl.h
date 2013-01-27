/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	PEANUT SELECT CONTROL APILINK

	Copyright(c) 1997-2003 BNSoft Corp.

	그룹 : PEANUT
	구분 : APILINK
	등급 : 공개																						{{BNS_INTERNALCODE()}}
	버전 : 1.00
	일자 : 2003.01.20
	성명 : 박상호
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT__PEANUT_SELCTRL_H_
#define		_BNSOFT__PEANUT_SELCTRL_H_

#include	"../SelCtrl.h"

//-------------------------------------------------------------------------------------------------
typedef H_CTRL			(*T_pfnSelCtrl_Create)         (void* pOwner, T_POS X, T_POS Y, T_SIZE W, T_SIZE H);
typedef BOOL			(*T_pfnSelCtrl_Destroy)        (H_CTRL hBC);
typedef BOOL			(*T_pfnSelCtrl_SetStr)         (H_CTRL hSC, int Index, T_CSTR pcszStr);
typedef BOOL			(*T_pfnSelCtrl_SetData)        (H_CTRL hSC, int Index, QUAD Data);
typedef BOOL			(*T_pfnSelCtrl_SetMoveKey)     (H_CTRL hSC, KEY PrevKey, KEY NextKey);
typedef TSelItem*		(*T_pfnSelCtrl_GetItem)        (H_CTRL hSC, int Index);
typedef T_CSTR			(*T_pfnSelCtrl_GetStr)         (H_CTRL hSC, int Index);
typedef QUAD			(*T_pfnSelCtrl_GetData)        (H_CTRL hSC, int Index);
typedef int				(*T_pfnSelCtrl_GetSelIndex)    (H_CTRL hSC);
typedef TSelItem*		(*T_pfnSelCtrl_GetSelItem)     (H_CTRL hSC);
typedef T_CSTR			(*T_pfnSelCtrl_GetSelStr)      (H_CTRL hSC);
typedef QUAD			(*T_pfnSelCtrl_GetSelData)     (H_CTRL hSC);
typedef BOOL			(*T_pfnSelCtrl_ResetAllItems)  (H_CTRL hSC);
typedef BOOL			(*T_pfnSelCtrl_ResetState)     (H_CTRL hSC);
typedef BOOL			(*T_pfnSelCtrl_AddItem)        (H_CTRL hSC, T_CSTR pcszStr, QUAD Data);
typedef BOOL			(*T_pfnSelCtrl_SelectItem)     (H_CTRL hSC, int Index);
typedef int				(*T_pfnSelCtrl_SelectNextItem) (H_CTRL hSC);
typedef int				(*T_pfnSelCtrl_SelectPrevItem) (H_CTRL hSC);
typedef BOOL			(*T_pfnSelCtrl_AssignStrSet)   (H_CTRL hSC, T_CSTR pStrSet, T_NUM StrNum);
typedef BOOL			(*T_pfnSelCtrl_AssignDataSet)  (H_CTRL hSC, QUAD* pDataSet, T_NUM DataNum);
typedef	BOOL			(*T_pfnSelCtrl_ResetTicker)    (H_CTRL hSC);
//-------------------------------------------------------------------------------------------------
typedef struct
{
	T_pfnSelCtrl_Create					pfnCreate;
	T_pfnSelCtrl_Destroy				pfnDestroy;
	T_pfnSelCtrl_SetStr					pfnSetStr;
	T_pfnSelCtrl_SetData				pfnSetData;
	T_pfnSelCtrl_SetMoveKey				pfnSetMoveKey;
	T_pfnSelCtrl_GetItem				pfnGetItem;
	T_pfnSelCtrl_GetStr					pfnGetStr;
	T_pfnSelCtrl_GetData				pfnGetData;
	T_pfnSelCtrl_GetSelIndex			pfnGetSelIndex;
	T_pfnSelCtrl_GetSelItem				pfnGetSelItem;
	T_pfnSelCtrl_GetSelStr				pfnGetSelStr;
	T_pfnSelCtrl_GetSelData				pfnGetSelData;
	T_pfnSelCtrl_ResetAllItems			pfnResetAllItems;
	T_pfnSelCtrl_ResetState				pfnResetState;
	T_pfnSelCtrl_AddItem				pfnAddItem;
	T_pfnSelCtrl_SelectItem				pfnSelectItem;
	T_pfnSelCtrl_SelectNextItem			pfnSelectNextItem;
	T_pfnSelCtrl_SelectPrevItem			pfnSelectPrevItem;
	T_pfnSelCtrl_AssignStrSet			pfnAssignStrSet;
	T_pfnSelCtrl_AssignDataSet			pfnAssignDataSet;
	T_pfnSelCtrl_ResetTicker			pfnResetTicker;
} TApiGrp_SelCtrl;

//-------------------------------------------------------------------------------------------------
#ifndef		BNS_MAIN_VERSION

	#define		SelCtrl_Create(p1,p2,p3,p4,p5)				__ApiLink5(SelCtrl,Create,p1,p2,p3,p4,p5)
	#define		SelCtrl_Destroy(p1)							__ApiLink1(SelCtrl,Destroy,p1)
	#define		SelCtrl_SetStr(p1,p2,p3)					__ApiLink3(SelCtrl,SetStr,p1,p2,p3)
	#define		SelCtrl_SetData(p1,p2,p3)					__ApiLink3(SelCtrl,SetData,p1,p2,p3)
	#define		SelCtrl_SetMoveKey(p1,p2,p3)				__ApiLink3(SelCtrl,SetMoveKey,p1,p2,p3)
	#define		SelCtrl_GetItem(p1,p2)						__ApiLink2(SelCtrl,GetItem,p1,p2)
	#define		SelCtrl_GetStr(p1,p2)						__ApiLink2(SelCtrl,GetStr,p1,p2)
	#define		SelCtrl_GetData(p1,p2)						__ApiLink2(SelCtrl,GetData,p1,p2)
	#define		SelCtrl_GetSelIndex(p1)						__ApiLink1(SelCtrl,GetSelIndex,p1)
	#define		SelCtrl_GetSelItem(p1)						__ApiLink1(SelCtrl,GetSelItem,p1)
	#define		SelCtrl_GetSelStr(p1)						__ApiLink1(SelCtrl,GetSelStr,p1)
	#define		SelCtrl_GetSelData(p1)						__ApiLink1(SelCtrl,GetSelData,p1)
	#define		SelCtrl_ResetAllItems(p1)					__ApiLink1(SelCtrl,ResetAllItems,p1)
	#define		SelCtrl_ResetState(p1)						__ApiLink1(SelCtrl,ResetState,p1)
	#define		SelCtrl_AddItem(p1,p2,p3)					__ApiLink3(SelCtrl,AddItem,p1,p2,p3)
	#define		SelCtrl_SelectItem(p1,p2)					__ApiLink2(SelCtrl,SelectItem,p1,p2)
	#define		SelCtrl_SelectNextItem(p1)					__ApiLink1(SelCtrl,SelectNextItem,p1)
	#define		SelCtrl_SelectPrevItem(p1)					__ApiLink1(SelCtrl,SelectPrevItem,p1)
	#define		SelCtrl_AssignStrSet(p1,p2,p3)				__ApiLink3(SelCtrl,AssignStrSet,p1,p2,p3)
	#define		SelCtrl_AssignDataSet(p1,p2,p3)				__ApiLink3(SelCtrl,AssignDataSet,p1,p2,p3)
	#define		SelCtrl_ResetTicker(p1)						__ApiLink1(SelCtrl,ResetTicker,p1)
#endif	//	BNS_MAIN_VERSION
//-------------------------------------------------------------------------------------------------

#endif	//	_BNSOFT__PEANUT_SELCTRL_H_
