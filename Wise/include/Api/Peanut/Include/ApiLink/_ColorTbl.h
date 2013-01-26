/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	PEANUT COLOR TABLE APILINK

	Copyright(c) 1997-2003 BNSoft Corp.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT__PEANUT_COLORTBL_H_
#define		_BNSOFT__PEANUT_COLORTBL_H_

#include	"..\ColorTbl.h"

typedef TColorTbl*	(*T_pfnColorTbl_Create)   (int TblType);
typedef BOOL		(*T_pfnColorTbl_Destroy)  (TColorTbl* pColorTbl);
typedef BOOL		(*T_pfnColorTbl_SetColor) (TColorTbl* pColorTbl, E_COLTYPE ColorType, int ColorIndex, T_COLOR Color);
typedef T_COLOR		(*T_pfnColorTbl_GetColor) (TColorTbl* pColorTbl, E_COLTYPE ColorType, int ColorIndex);

typedef struct
{
	T_pfnColorTbl_Create				pfnCreate;
	T_pfnColorTbl_Destroy				pfnDestroy;
	T_pfnColorTbl_SetColor				pfnSetColor;
	T_pfnColorTbl_GetColor				pfnGetColor;
} TApiGrp_ColorTbl;


#define	ColorTbl_Create(p1)				__ApiLink1(ColorTbl,Create,p1)
#define	ColorTbl_Destroy(p1)				__ApiLink1(ColorTbl,Destroy,p1)
#define	ColorTbl_SetColor(p1,p2,p3,p4)			__ApiLink4(ColorTbl,SetColor,p1,p2,p3,p4)
#define	ColorTbl_GetColor(p1,p2,p3)			__ApiLink3(ColorTbl,GetColor,p1,p2,p3)

#endif	//	_BNSOFT__PEANUT_COLORTBL_H_
