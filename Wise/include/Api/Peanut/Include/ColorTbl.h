/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	PEANUT COLOR TABLE

	Copyright(c) 1997-2003 BNSoft Corp.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT_PEANUT_COLORTBL_H_
#define		_BNSOFT_PEANUT_COLORTBL_H_

#include	"PeanutInclude.h"

//	Color 
typedef enum
{
	COLTYPE_NONE			= 0,
	COLTYPE_FOCUSED,
	COLTYPE_NORMAL,
	COLTYPE_DISABLE,
	COLTYPE_MAX
} E_COLTYPE;

//	T_COLORLIST
typedef		T_COLOR*		T_COLORLIST;

//	ColorTbl
typedef struct
{
	T_NUM				Num;
	T_COLORLIST			FocusedCL;
	T_COLORLIST			NormalCL;
	T_COLORLIST			DisableCL;
} TColorTbl;


extern TColorTbl*	ColorTbl_Create   (int TblType);
extern BOOL		ColorTbl_Destroy  (TColorTbl* pColorTbl);
extern BOOL		ColorTbl_SetColor (TColorTbl* pColorTbl, E_COLTYPE ColorType, int ColorIndex, T_COLOR Color);
extern T_COLOR		ColorTbl_GetColor (TColorTbl* pColorTbl, E_COLTYPE ColorType, int ColorIndex);


#endif	//	_BNSOFT_PEANUT_COLORTBL_H_
