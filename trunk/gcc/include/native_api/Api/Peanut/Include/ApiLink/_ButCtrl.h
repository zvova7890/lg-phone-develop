/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	PEANUT BUTTON CONTROL APILINK

	Copyright(c) 1997-2002 BNSoft Corp.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT__PEANUT_BUTCTRL_H_
#define		_BNSOFT__PEANUT_BUTCTRL_H_

#include	"../ButCtrl.h"

typedef H_CTRL			(*T_pfnButCtrl_Create)			(void* pOwner, T_POS X, T_POS Y, T_SIZE W, T_SIZE H, T_CSTR pcszText);
typedef BOOL			(*T_pfnButCtrl_Destroy)			(H_CTRL hBC);
typedef BOOL			(*T_pfnButCtrl_SetText)			(H_CTRL hBC, T_CSTR pcszText);
typedef BOOL			(*T_pfnButCtrl_SetImage)		(H_CTRL hBC, TImage* pImage);
typedef BOOL			(*T_pfnButCtrl_SetPressedImage) (H_CTRL hBC, TImage* pImage);
typedef BOOL			(*T_pfnButCtrl_SetSelKey)		(H_CTRL hBC, KEY SelKey);
typedef T_CSTR			(*T_pfnButCtrl_GetText)			(H_CTRL hBC);
typedef TImage*			(*T_pfnButCtrl_GetImage)		(H_CTRL hBC);
typedef KEY			(*T_pfnButCtrl_GetSelKey)		(H_CTRL hBC);
typedef BOOL			(*T_pfnButCtrl_SetTip)	(H_CTRL hBC, T_CSTR	pcszText);


//-------------------------------------------------------------------------------------------------
typedef struct
{
	T_pfnButCtrl_Create			pfnCreate;
	T_pfnButCtrl_Destroy			pfnDestroy;
	T_pfnButCtrl_SetText			pfnSetText;
	T_pfnButCtrl_SetImage			pfnSetImage;
	T_pfnButCtrl_SetPressedImage		pfnSetPressedImage;

	T_pfnButCtrl_SetSelKey			pfnSetSelKey;
	T_pfnButCtrl_GetText			pfnGetText;
	T_pfnButCtrl_GetImage			pfnGetImage;
	T_pfnButCtrl_GetSelKey			pfnGetSelKey;
	T_pfnButCtrl_SetTip			pfnSetTip;

} TApiGrp_ButCtrl;


#define		ButCtrl_Create(p1,p2,p3,p4,p5,p6)		__ApiLink6(ButCtrl,Create,p1,p2,p3,p4,p5,p6)
#define		ButCtrl_Destroy(p1)				__ApiLink1(ButCtrl,Destroy,p1)
#define		ButCtrl_SetText(p1,p2)				__ApiLink2(ButCtrl,SetText,p1,p2)
#define		ButCtrl_SetImage(p1,p2)				__ApiLink2(ButCtrl,SetImage,p1,p2)
#define		ButCtrl_SetPressedImage(p1,p2)			__ApiLink2(ButCtrl,SetPressedImage,p1,p2)

#define		ButCtrl_SetSelKey(p1,p2)			__ApiLink2(ButCtrl,SetSelKey,p1,p2)
#define		ButCtrl_GetText(p1)				__ApiLink1(ButCtrl,GetText,p1)
#define		ButCtrl_GetImage(p1)				__ApiLink1(ButCtrl,GetImage,p1)
#define		ButCtrl_GetSelKey(p1)				__ApiLink1(ButCtrl,GetSelKey,p1)
#define		ButCtrl_SetTip(p1,p2)				__ApiLink2(ButCtrl,SetTip,p1,p2)


#endif	//	_BNSOFT__PEANUT_BUTCTRL_H_
