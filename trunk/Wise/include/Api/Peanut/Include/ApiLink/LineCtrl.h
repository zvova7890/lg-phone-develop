/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	PEANUT LINE CONTROL

	Copyright(c) 1997-2003 BNSoft Corp.

	그룹 : PEANUT
	구분 : CONTROL
	등급 : 공개/비공개																				{{BNS_INTERNALCODE()}}
	버전 : 1.00
	일자 : 2003.02.13
	성명 : 이동화,박상호
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT_PEANUT_LINECTRL_H_
#define		_BNSOFT_PEANUT_LINECTRL_H_

#include	"BaseCtrl.h"
#include	"MacroFunc\LineCtrlM.h"

//-------------------------------------------------------------------------------------------------
//	LineCtrl Style의 종류 (TBaseCtrl::Style)
#define		LINESTY_DEF					(0)

//-------------------------------------------------------------------------------------------------
//	NOTIMASK의 종류 (TBaseCtrl::NotiMask)
#define		LINEMASK_ERASEBKGND			NOTIMASK_ERASEBKGND	//	0x80000000	컨트롤의 배경을 그리는 경우에 발생
#define		LINEMASK_POSTDRAW			NOTIMASK_POSTDRAW	//	0x40000000  컨트롤을 그린 후 그래픽버퍼로 출력하기 전에 발생

//-------------------------------------------------------------------------------------------------
//	LineCtrl 색상 정의
typedef enum
{
	LINECOL_FOREGROUND				= 0,
	LINECOL_NUM
} E_LINECOL;

//-------------------------------------------------------------------------------------------------
typedef struct
{
	T_POS				X1;
	T_POS				Y1;
	T_POS				X2;
	T_POS				Y2;
} TLineObj;

//-------------------------------------------------------------------------------------------------
//	LineCtrl 구조체 정의
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

//-------------------------------------------------------------------------------------------------	{{BNS_INTERNALCODE(+)}}
//	LineCtrl Internal Member Functions
#ifdef		BNS_MAIN_VERSION

	extern BOOL				LineCtrl_CreateBody   (TLineCtrl* pLC, void* pOwner, E_CTRLTYPE enType, QUAD Style, T_POS X1, T_POS Y1, T_POS X2, T_POS Y2);
	extern BOOL				LineCtrl_DestroyBody  (TLineCtrl* pLC);

#endif	//	BNS_MAIN_VERSION																	//	{{BNS_INTERNALCODE(-)}}
//-------------------------------------------------------------------------------------------------
//	LineCtrl Member Functions
#ifdef		BNS_MAIN_VERSION

	//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	//	Create & Destroy Functions
	extern H_CTRL			LineCtrl_Create       (void* pOwner, T_POS X1, T_POS Y1, T_POS X2, T_POS Y2);
	extern BOOL				LineCtrl_Destroy      (H_CTRL hLC);

	//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	//	Overriding Functions

	//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	//	LineCtrl Own Functions
	extern BOOL				LineCtrl_SetStartPos  (H_CTRL hLC, int Index, T_POS X, T_POS Y);
	extern BOOL				LineCtrl_SetEndPos    (H_CTRL hLC, int Index, T_POS X, T_POS Y);
	extern BOOL				LineCtrl_SetColor     (H_CTRL hLC, T_COLOR Color);
	extern BOOL				LineCtrl_SetThickness (H_CTRL hLC, T_SIZE Thickness);
	extern BOOL				LineCtrl_SetStroke    (H_CTRL hLC, QUAD Stroke, int StrokeBitNum);

	extern T_COLOR			LineCtrl_GetColor     (H_CTRL hLC);
	extern T_SIZE			LineCtrl_GetThickness (H_CTRL hLC);

	extern BOOL				LineCtrl_AddLine      (H_CTRL hLC, T_POS X1, T_POS Y1, T_POS X2, T_POS Y2);

#endif	//	BNS_MAIN_VERSION
//-------------------------------------------------------------------------------------------------

#endif	//	_BNSOFT_PEANUT_LINECTRL_H_
