/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	PEANUT SOFTMENU APILINK

	Copyright(c) 1997-2003 BNSoft Corp.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT__PEANUT_SOFTMENU_H_
#define		_BNSOFT__PEANUT_SOFTMENU_H_

#include	"..\SoftMenu.h"

typedef T_POS			(*T_pfnSoftMenu_GetAboveY)			(void);
typedef T_POS			(*T_pfnSoftMenu_GetTopY)			(void);
typedef T_SIZE			(*T_pfnSoftMenu_GetHeight)			(void);
typedef void			(*T_pfnSoftMenu_SetFont)			(E_FONT enFont);
typedef void			(*T_pfnSoftMenu_SetOemType)			(QUAD OemType);
typedef void			(*T_pfnSoftMenu_SetStr)				(T_CSTR pcszLSoftMenu, T_CSTR pcszMSoftMenu, T_CSTR pcszRSoftMenu, BOOL bRefresh);
typedef void			(*T_pfnSoftMenu_Refresh)			(void);
typedef void			(*T_pfnSoftMenu_Draw)				(T_CSTR pcszLSoftMenu, T_CSTR pcszMSoftMenu, T_CSTR pcszRSoftMenu);
typedef void			(*T_pfnSoftMenu_DrawEx)				(T_CSTR pcszLSoftMenu, T_CSTR pcszMSoftMenu, T_CSTR pcszRSoftMenu, BOOL bRefresh);
typedef BOOL			(*T_pfnSoftMenu_SetTransparent)			(BOOL bTransparent);
typedef int			(*T_pfnSoftMenu_Pointing)			(int nAction, int X, int Y);
typedef int			(*T_pfnSoftMenu_GetOemType)			(void);

typedef struct
{
	T_pfnSoftMenu_GetAboveY			pfnGetAboveY;
	T_pfnSoftMenu_GetTopY			pfnGetTopY;
	T_pfnSoftMenu_GetHeight			pfnGetHeight;
	T_pfnSoftMenu_SetFont			pfnSetFont;
	T_pfnSoftMenu_SetOemType		pfnSetOemType;
	T_pfnSoftMenu_SetStr			pfnSetStr;
	T_pfnSoftMenu_Refresh			pfnRefresh;
	T_pfnSoftMenu_Draw			pfnDraw;
	T_pfnSoftMenu_DrawEx			pfnDrawEx;
	T_pfnSoftMenu_SetTransparent		pfnSetTransparent;
	T_pfnSoftMenu_Pointing			pfnPointing;
	T_pfnSoftMenu_GetOemType		pfnGetOemType;
} TApiGrp_SoftMenu;


#define		SoftMenu_GetAboveY()					__ApiLink0(SoftMenu,GetAboveY)
#define		SoftMenu_GetTopY()					__ApiLink0(SoftMenu,GetTopY)
#define		SoftMenu_GetHeight()					__ApiLink0(SoftMenu,GetHeight)
#define		SoftMenu_SetFont(p1)					__ApiLink1(SoftMenu,SetFont,p1)
#define		SoftMenu_SetOemType(p1)					__ApiLink1(SoftMenu,SetOemType,p1)
#define		SoftMenu_SetStr(p1,p2,p3,p4)				__ApiLink4(SoftMenu,SetStr,p1,p2,p3,p4)
#define		SoftMenu_Refresh()					__ApiLink0(SoftMenu,Refresh)
#define		SoftMenu_Draw(p1,p2,p3)					__ApiLink3(SoftMenu,Draw,p1,p2,p3)
#define		SoftMenu_DrawEx(p1,p2,p3,p4)				__ApiLink4(SoftMenu,DrawEx,p1,p2,p3,p4)
#define		SoftMenu_SetTransparent(p1)				__ApiLink1(SoftMenu,SetTransparent,p1)	
#define		SoftMenu_Pointing(p1,p2,p3)				__ApiLink3(SoftMenu,Pointing,p1,p2,p3)
#define		SoftMenu_GetOemType()					__ApiLink0(SoftMenu,GetOemType)

#endif	//	_BNSOFT__PEANUT_SOFTMENU_H_
