/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	PEANUT LINE CONTROL APILINK

	Copyright(c) 1997-2003 BNSoft Corp.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT__PEANUT_LINECTRL_H_
#define		_BNSOFT__PEANUT_LINECTRL_H_

#include	"../LineCtrl.h"

typedef H_CTRL			(*T_pfnLineCtrl_Create)       (void* pOwner, T_POS X1, T_POS Y1, T_POS X2, T_POS Y2);
typedef BOOL			(*T_pfnLineCtrl_Destroy)      (H_CTRL hLC);
typedef BOOL			(*T_pfnLineCtrl_SetStartPos)  (H_CTRL hLC, int Index, T_POS X, T_POS Y);
typedef BOOL			(*T_pfnLineCtrl_SetEndPos)    (H_CTRL hLC, int Index, T_POS X, T_POS Y);
typedef BOOL			(*T_pfnLineCtrl_SetColor)     (H_CTRL hLC, T_COLOR Color);
typedef BOOL			(*T_pfnLineCtrl_SetThickness) (H_CTRL hLC, T_SIZE Thickness);
typedef BOOL			(*T_pfnLineCtrl_SetStroke)    (H_CTRL hLC, QUAD Stroke, int StrokeBitNum);
typedef T_COLOR			(*T_pfnLineCtrl_GetColor)     (H_CTRL hLC);
typedef T_SIZE			(*T_pfnLineCtrl_GetThickness) (H_CTRL hLC);
typedef BOOL			(*T_pfnLineCtrl_AddLine)      (H_CTRL hLC, T_POS X1, T_POS Y1, T_POS X2, T_POS Y2);

typedef struct
{
	T_pfnLineCtrl_Create				pfnCreate;
	T_pfnLineCtrl_Destroy				pfnDestroy;
	T_pfnLineCtrl_SetStartPos			pfnSetStartPos;
	T_pfnLineCtrl_SetEndPos				pfnSetEndPos;
	T_pfnLineCtrl_SetColor				pfnSetColor;
	T_pfnLineCtrl_SetThickness			pfnSetThickness;
	T_pfnLineCtrl_SetStroke				pfnSetStroke;
	T_pfnLineCtrl_GetColor				pfnGetColor;
	T_pfnLineCtrl_GetThickness			pfnGetThickness;
	T_pfnLineCtrl_AddLine				pfnAddLine;
} TApiGrp_LineCtrl;


#define	LineCtrl_Create(p1,p2,p3,p4,p5)				__ApiLink5(LineCtrl,Create,p1,p2,p3,p4,p5)
#define	LineCtrl_Destroy(p1)						__ApiLink1(LineCtrl,Destroy,p1)
#define	LineCtrl_SetStartPos(p1,p2,p3,p4)			__ApiLink4(LineCtrl,SetStartPos,p1,p2,p3,p4)
#define	LineCtrl_SetEndPos(p1,p2,p3,p4)				__ApiLink4(LineCtrl,SetEndPos,p1,p2,p3,p4)
#define	LineCtrl_SetColor(p1,p2)					__ApiLink2(LineCtrl,SetColor,p1,p2)
#define	LineCtrl_SetThickness(p1,p2)				__ApiLink2(LineCtrl,SetThickness,p1,p2)
#define	LineCtrl_SetStroke(p1,p2,p3)				__ApiLink3(LineCtrl,SetStroke,p1,p2,p3)
#define	LineCtrl_GetColor(p1)						__ApiLink1(LineCtrl,GetColor,p1)
#define	LineCtrl_GetThickness(p1)					__ApiLink1(LineCtrl,GetThickness,p1)
#define	LineCtrl_AddLine(p1,p2,p3,p4,p5)			__ApiLink5(LineCtrl,AddLine,p1,p2,p3,p4,p5)


#endif	//	_BNSOFT__PEANUT_LINECTRL_H_
