/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	PEANUT TEXT CONTROL APILINK

	Copyright(c) 1997-2003 BNSoft Corp.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT__PEANUT_TEXTCTRL_H_
#define		_BNSOFT__PEANUT_TEXTCTRL_H_

#include	"../TextCtrl.h"

//-------------------------------------------------------------------------------------------------
typedef H_CTRL			(*T_pfnTextCtrl_Create)   (void* pOwner, T_POS X, T_POS Y, T_SIZE W, T_SIZE H, T_CSTR pcszText);
typedef BOOL			(*T_pfnTextCtrl_Destroy)  (H_CTRL hTC);
typedef BOOL			(*T_pfnTextCtrl_SetText)  (H_CTRL hTC, T_CSTR pcszText);
typedef BOOL			(*T_pfnTextCtrl_SetAlign) (H_CTRL hTC, int Align);
typedef T_CSTR			(*T_pfnTextCtrl_GetText)  (H_CTRL hTC);
typedef int			(*T_pfnTextCtrl_GetAlign) (H_CTRL hTC);

typedef struct
{
	T_pfnTextCtrl_Create				pfnCreate;
	T_pfnTextCtrl_Destroy				pfnDestroy;
	T_pfnTextCtrl_SetText				pfnSetText;
	T_pfnTextCtrl_SetAlign				pfnSetAlign;
	T_pfnTextCtrl_GetText				pfnGetText;
	T_pfnTextCtrl_GetAlign				pfnGetAlign;
} TApiGrp_TextCtrl;


#define		TextCtrl_Create(p1,p2,p3,p4,p5,p6)		__ApiLink6(TextCtrl,Create,p1,p2,p3,p4,p5,p6)
#define		TextCtrl_Destroy(p1)				__ApiLink1(TextCtrl,Destroy,p1)
#define		TextCtrl_SetText(p1,p2)				__ApiLink2(TextCtrl,SetText,p1,p2)
#define		TextCtrl_SetAlign(p1,p2)			__ApiLink2(TextCtrl,SetAlign,p1,p2)
#define		TextCtrl_GetText(p1)				__ApiLink1(TextCtrl,GetText,p1)
#define		TextCtrl_GetAlign(p1)				__ApiLink1(TextCtrl,GetAlign,p1)


#endif	//	_BNSOFT__PEANUT_TEXTCTRL_H_
