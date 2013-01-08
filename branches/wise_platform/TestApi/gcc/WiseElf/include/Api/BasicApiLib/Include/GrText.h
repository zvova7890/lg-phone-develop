/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	GRAPHIC TEXT

	Copyright(c) 1997-2003 BNSoft Corp.

	그룹 : BASIC API
	구분 : 그래픽
	등급 : 공개																						{{BNS_INTERNALCODE()}}
	버전 : 1.08
	일자 : 2003.02.12
	성명 : 박상호
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT_GRTEXT_H_
#define		_BNSOFT_GRTEXT_H_

#include	"Include.h"
#include	"GrSys.h"

//-------------------------------------------------------------------------------------------------
//	GrText Member Functions
#ifdef		BNS_MAIN_VERSION

	extern void				GrText_Reset                  (void);

	extern void				GrText_SetRange               (T_POS X1, T_POS Y1, T_POS X2, T_POS Y2);
	extern void				GrText_SetFont                (E_FONT enFont);
	extern void				GrText_SetColor               (T_COLOR Color);
	extern void				GrText_SetLineGap             (int nLineGap);
	extern void				GrText_SetCharGap             (int nCharGap);
	extern void				GrText_SetAlign               (int nAlignType);
	extern void				GrText_SetWordBreak           (BOOL bWordBreak);
	extern void				GrText_SetMultiLine           (BOOL bMultiLine);
	extern void				GrText_SetBold                (BOOL bBold);
	extern void				GrText_SetUnderLine           (BOOL bUnderLine);
	extern void				GrText_SetItalic              (BOOL bItalic);
	extern void				GrText_SetOutLine             (BOOL bOutLine);
	extern void				GrText_SetStrikeThrough       (BOOL bStrikeThrough);
	extern void				GrText_SetSeparator           (QUAD Stroke);
	extern void				GrText_SetSepXRange           (T_POS X1, T_POS X2);
	extern void				GrText_SetSelection           (T_POS nStartPos, T_POS nEndPos);
	extern void				GrText_SetCursorPos           (T_POS nCursorPos);
	extern void				GrText_SetBiDi                (BOOL bBiDi);
	extern void				GrText_Draw                   (T_CSTR pcszStr);

#endif	//	BNS_MAIN_VERSION
//-------------------------------------------------------------------------------------------------

#endif	//	_BNSOFT_GRIMAGE_H_
