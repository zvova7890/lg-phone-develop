/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	DYNAMIC LINKING LIBRARY

	Copyright(c) 1997-2002 BNSoft Corp.

	그룹 : BASIC API
	구분 : APILINK
	등급 : 공개																						{{BNS_INTERNALCODE()}}
	버전 : 1.00
	일자 : 2002.06.27
	성명 : 박상호
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT__GRTEXT_H_
#define		_BNSOFT__GRTEXT_H_

#include	"../GrText.h"

//-------------------------------------------------------------------------------------------------
typedef void			(*T_pfnGrText_Reset)              (void);
typedef void			(*T_pfnGrText_SetRange)           (T_POS X1, T_POS Y1, T_POS X2, T_POS Y2);
typedef void			(*T_pfnGrText_SetFont)            (E_FONT enFont);
typedef void			(*T_pfnGrText_SetColor)           (T_COLOR Color);
typedef void			(*T_pfnGrText_SetLineGap)         (int nLineGap);
typedef void			(*T_pfnGrText_SetCharGap)         (int nCharGap);
typedef void			(*T_pfnGrText_SetAlign)           (int nAlignType);
typedef void			(*T_pfnGrText_SetWordBreak)       (BOOL bWordBreak);
typedef void			(*T_pfnGrText_SetMultiLine)       (BOOL bMultiLine);
typedef void			(*T_pfnGrText_SetBold)            (BOOL bBold);
typedef void			(*T_pfnGrText_SetUnderLine)       (BOOL bUnderLine);
typedef void			(*T_pfnGrText_SetItalic)          (BOOL bItalic);
typedef void			(*T_pfnGrText_SetOutLine)         (BOOL bOutLine);
typedef void			(*T_pfnGrText_SetStrikeThrough)   (BOOL bStrikeThrough);
typedef void			(*T_pfnGrText_SetSeparator)       (QUAD Stroke);
typedef void			(*T_pfnGrText_SetSepXRange)       (T_POS X1, T_POS X2);
typedef void			(*T_pfnGrText_SetSelection)       (T_POS nStartPos, T_POS nEndPos);
typedef void			(*T_pfnGrText_SetCursorPos)       (T_POS nCursorPos);
typedef void			(*T_pfnGrText_SetBiDi)            (BOOL bBiDi);
typedef void			(*T_pfnGrText_Draw)               (T_CSTR pStr);

//-------------------------------------------------------------------------------------------------
typedef struct
{
	T_pfnGrText_Reset					pfnReset;
	T_pfnGrText_SetRange				pfnSetRange;
	T_pfnGrText_SetFont					pfnSetFont;
	T_pfnGrText_SetColor				pfnSetColor;
	T_pfnGrText_SetLineGap				pfnSetLineGap;
	T_pfnGrText_SetCharGap				pfnSetCharGap;
	T_pfnGrText_SetAlign				pfnSetAlign;
	T_pfnGrText_SetWordBreak			pfnSetWordBreak;
	T_pfnGrText_SetMultiLine			pfnSetMultiLine;
	T_pfnGrText_SetBold					pfnSetBold;
	T_pfnGrText_SetUnderLine			pfnSetUnderLine;
	T_pfnGrText_SetItalic				pfnSetItalic;
	T_pfnGrText_SetOutLine				pfnSetOutLine;
	T_pfnGrText_SetStrikeThrough		pfnSetStrikeThrough;
	T_pfnGrText_SetSeparator			pfnSetSeparator;
	T_pfnGrText_SetSepXRange			pfnSetSepXRange;
	T_pfnGrText_SetSelection			pfnSetSelection;
	T_pfnGrText_SetCursorPos			pfnSetCursorPos;
	T_pfnGrText_SetBiDi					pfnSetBiDi;
	T_pfnGrText_Draw					pfnDraw;
} TApiGrp_GrText;

//-------------------------------------------------------------------------------------------------
#ifndef		BNS_MAIN_VERSION

	#define		GrText_Reset()						__ApiLink0(GrText,Reset)
	#define		GrText_SetRange(p1,p2,p3,p4)		__ApiLink4(GrText,SetRange,p1,p2,p3,p4)
	#define		GrText_SetFont(p1)					__ApiLink1(GrText,SetFont,p1)
	#define		GrText_SetColor(p1)					__ApiLink1(GrText,SetColor,p1)
	#define		GrText_SetLineGap(p1)				__ApiLink1(GrText,SetLineGap,p1)
	#define		GrText_SetCharGap(p1)				__ApiLink1(GrText,SetCharGap,p1)
	#define		GrText_SetAlign(p1)					__ApiLink1(GrText,SetAlign,p1)
	#define		GrText_SetWordBreak(p1)				__ApiLink1(GrText,SetWordBreak,p1)
	#define		GrText_SetMultiLine(p1)				__ApiLink1(GrText,SetMultiLine,p1)
	#define		GrText_SetBold(p1)					__ApiLink1(GrText,SetBold,p1)
	#define		GrText_SetUnderLine(p1)				__ApiLink1(GrText,SetUnderLine,p1)
	#define		GrText_SetItalic(p1)				__ApiLink1(GrText,SetItalic,p1)
	#define		GrText_SetOutLine(p1)				__ApiLink1(GrText,SetOutLine,p1)
	#define		GrText_SetStrikeThrough(p1)			__ApiLink1(GrText,SetStrikeThrough,p1)
	#define		GrText_SetSeparator(p1)				__ApiLink1(GrText,SetSeparator,p1)
	#define		GrText_SetSepXRange(p1,p2)			__ApiLink2(GrText,SetSepXRange,p1,p2)
	#define		GrText_SetSelection(p1,p2)			__ApiLink2(GrText,SetSelection,p1,p2)
	#define		GrText_SetCursorPos(p1)				__ApiLink1(GrText,SetCursorPos,p1)
	#define		GrText_SetBiDi(p1)					__ApiLink1(GrText,SetBiDi,p1)
	#define		GrText_Draw(p1)						__ApiLink1(GrText,Draw,p1)

#endif	//	BNS_MAIN_VERSION
//-------------------------------------------------------------------------------------------------

#endif	//	_BNSOFT__GRTEXT_H_
