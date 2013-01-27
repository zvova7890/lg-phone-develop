/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	PEANUT CHECK CONTROL APILINK

	Copyright(c) 1997-2003 BNSoft Corp.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT__PEANUT_CHKCTRL_H_
#define		_BNSOFT__PEANUT_CHKCTRL_H_

#include	"../ChkCtrl.h"

typedef H_CTRL			(*T_pfnChkCtrl_Create)       (void* pOwner, T_POS X, T_POS Y, T_SIZE W, T_SIZE H, T_CSTR pcszText);
typedef BOOL			(*T_pfnChkCtrl_Destroy)      (H_CTRL hCC);
typedef BOOL			(*T_pfnChkCtrl_SetText)      (H_CTRL hCC, T_CSTR pcszText);
typedef BOOL			(*T_pfnChkCtrl_SetStatus)    (H_CTRL hCC, E_CHKSTATUS enStatus);
typedef BOOL			(*T_pfnChkCtrl_SetCheck)     (H_CTRL hCC, BOOL bCheck);
typedef BOOL			(*T_pfnChkCtrl_SetIconWidth) (H_CTRL hCC, T_SIZE IconWidth);
typedef BOOL			(*T_pfnChkCtrl_SetSelKey)    (H_CTRL hCC, KEY SelKey);
typedef BOOL			(*T_pfnChkCtrl_SetAlignType) (H_CTRL hCC, int AlignType);
typedef BOOL			(*T_pfnChkCtrl_SetLineGap)   (H_CTRL hCC, int LineGap);
typedef T_CSTR			(*T_pfnChkCtrl_GetText)      (H_CTRL hCC);
typedef E_CHKSTATUS		(*T_pfnChkCtrl_GetStatus)    (H_CTRL hCC);
typedef BOOL			(*T_pfnChkCtrl_IsChecked)    (H_CTRL hCC);
typedef T_SIZE			(*T_pfnChkCtrl_GetIconWidth) (H_CTRL hCC);
typedef KEY			(*T_pfnChkCtrl_GetSelKey)    (H_CTRL hCC);
typedef int			(*T_pfnChkCtrl_GetAlignType) (H_CTRL hCC);
typedef int			(*T_pfnChkCtrl_GetLineGap)   (H_CTRL hCC);

typedef struct
{
	T_pfnChkCtrl_Create				pfnCreate;
	T_pfnChkCtrl_Destroy				pfnDestroy;
	T_pfnChkCtrl_SetText				pfnSetText;
	T_pfnChkCtrl_SetStatus				pfnSetStatus;
	T_pfnChkCtrl_SetCheck				pfnSetCheck;
	T_pfnChkCtrl_SetIconWidth			pfnSetIconWidth;
	T_pfnChkCtrl_SetSelKey				pfnSetSelKey;
	T_pfnChkCtrl_SetAlignType			pfnSetAlignType;
	T_pfnChkCtrl_SetLineGap				pfnSetLineGap;
	T_pfnChkCtrl_GetText				pfnGetText;
	T_pfnChkCtrl_GetStatus				pfnGetStatus;
	T_pfnChkCtrl_IsChecked				pfnIsChecked;
	T_pfnChkCtrl_GetIconWidth			pfnGetIconWidth;
	T_pfnChkCtrl_GetSelKey				pfnGetSelKey;
	T_pfnChkCtrl_GetAlignType			pfnGetAlignType;
	T_pfnChkCtrl_GetLineGap				pfnGetLineGap;
} TApiGrp_ChkCtrl;


#define	ChkCtrl_Create(p1,p2,p3,p4,p5,p6)		__ApiLink6(ChkCtrl,Create,p1,p2,p3,p4,p5,p6)
#define	ChkCtrl_Destroy(p1)				__ApiLink1(ChkCtrl,Destroy,p1)
#define	ChkCtrl_SetText(p1,p2)				__ApiLink2(ChkCtrl,SetText,p1,p2)
#define	ChkCtrl_SetStatus(p1,p2)			__ApiLink2(ChkCtrl,SetStatus,p1,p2)
#define	ChkCtrl_SetCheck(p1,p2)				__ApiLink2(ChkCtrl,SetCheck,p1,p2)
#define	ChkCtrl_SetIconWidth(p1,p2)			__ApiLink2(ChkCtrl,SetIconWidth,p1,p2)
#define	ChkCtrl_SetSelKey(p1,p2)			__ApiLink2(ChkCtrl,SetSelKey,p1,p2)
#define	ChkCtrl_SetAlignType(p1,p2)			__ApiLink2(ChkCtrl,SetAlignType,p1,p2)
#define	ChkCtrl_SetLineGap(p1,p2)			__ApiLink2(ChkCtrl,SetLineGap,p1,p2)
#define	ChkCtrl_GetText(p1)				__ApiLink1(ChkCtrl,GetText,p1)
#define	ChkCtrl_GetStatus(p1)				__ApiLink1(ChkCtrl,GetStatus,p1)
#define	ChkCtrl_IsChecked(p1)				__ApiLink1(ChkCtrl,IsChecked,p1)
#define	ChkCtrl_GetIconWidth(p1)			__ApiLink1(ChkCtrl,GetIconWidth,p1)
#define	ChkCtrl_GetSelKey(p1)				__ApiLink1(ChkCtrl,GetSelKey,p1)
#define	ChkCtrl_GetAlignType(p1)			__ApiLink1(ChkCtrl,GetAlignType,p1)
#define	ChkCtrl_GetLineGap(p1)				__ApiLink1(ChkCtrl,GetLineGap,p1)


#endif	//	_BNSOFT__PEANUT_CHKCTRL_H_
