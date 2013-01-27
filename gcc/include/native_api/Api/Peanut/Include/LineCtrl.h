/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	PEANUT LINE CONTROL

	Copyright(c) 1997-2003 BNSoft Corp.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT_PEANUT_LINECTRL_H_
#define		_BNSOFT_PEANUT_LINECTRL_H_

#include	"BaseCtrl.h"
#include	"MacroFunc/LineCtrlM.h"

#define		LINESTY_DEF			(0)

#define		LINEMASK_ERASEBKGND		NOTIMASK_ERASEBKGND	// 0x80000000
#define		LINEMASK_POSTDRAW		NOTIMASK_POSTDRAW	// 0x40000000

typedef enum
{
	LINECOL_FOREGROUND			= 0,
	LINECOL_NUM
} E_LINECOL;

typedef struct
{
	T_POS				X1;
	T_POS				Y1;
	T_POS				X2;
	T_POS				Y2;
} TLineObj;

typedef struct
{
	TBaseCtrl			Base;
	T_COLOR				Color;
	QUAD				Stroke;
	T_NUM				StrokeBitNum;
	T_SIZE				Thickness;
	T_NUM				LineNum;
	TLineObj*			pLineTbl;
} TLineCtrl;

//	Create & Destroy Functions
extern H_CTRL		LineCtrl_Create       (void* pOwner, T_POS X1, T_POS Y1, T_POS X2, T_POS Y2);
extern BOOL		LineCtrl_Destroy      (H_CTRL hLC);

//	Overriding Functions

//	LineCtrl Own Functions
extern BOOL		LineCtrl_SetStartPos  (H_CTRL hLC, int Index, T_POS X, T_POS Y);
extern BOOL		LineCtrl_SetEndPos    (H_CTRL hLC, int Index, T_POS X, T_POS Y);
extern BOOL		LineCtrl_SetColor     (H_CTRL hLC, T_COLOR Color);
extern BOOL		LineCtrl_SetThickness (H_CTRL hLC, T_SIZE Thickness);
extern BOOL		LineCtrl_SetStroke    (H_CTRL hLC, QUAD Stroke, int StrokeBitNum);

extern T_COLOR		LineCtrl_GetColor     (H_CTRL hLC);
extern T_SIZE		LineCtrl_GetThickness (H_CTRL hLC);

extern BOOL		LineCtrl_AddLine      (H_CTRL hLC, T_POS X1, T_POS Y1, T_POS X2, T_POS Y2);


#endif	//	_BNSOFT_PEANUT_LINECTRL_H_
