/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	WISE TEXT LAYOUT

	Copyright(c) 2007 -	 LGE Inc.

	그룹 : Text Layout
	구분 : LAYOUT
	등급 : 공개/비공개																						
	버전 : 2.00

	Date		Name		Version		Description
	----------	------		----------	-----------------------------------------------------------

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_LGE_WLAYOUTINFO_H_
#define		_LGE_WLAYOUTINFO_H_

#include	"..\..\BasicApiLib\Include\Include.h"
#include	"..\..\BasicApiLib\Include\SysHeap.h"
#include	"..\..\BasicApiLib\Include\UnicodeLib.h"
#include	"..\..\BasicApiLib\Include\AdaptSys.h"
#include	"..\..\BasicApiLib\Include\GrDevInfo.h"

	//---------------------------------------------------------------------------------------------
	extern	void*			WLayout_Heap_Alloc					(T_SIZE MemSize);
	extern	void			WLayout_Heap_Free					(void* pMem);
	extern	void*			WLayout_Heap_Realloc				(void* pMem, T_SIZE MemSize);
	
	extern	T_COLOR			WLayout_RGBColor					(BYTE r, BYTE g, BYTE b);

	extern void				WLayout_GetTextStyle				(TTextStyle* pTextStyle);
	extern void				WLayout_SetTextStyle				(TTextStyle* pTextStyle);

	extern void				WLayout_DrawLine					(T_POS X1, T_POS Y1, T_POS X2, T_POS Y2, T_COLOR Color);
	extern void				WLayout_DrawLineEx					(T_POS X1, T_POS Y1, T_POS X2, T_POS Y2, T_COLOR Color, T_SIZE Thickness, T_STROKE Stroke, int nStrokeBitNum);
	extern void				WLayout_DrawHLine					(T_POS Y,  T_POS X1, T_POS X2, T_COLOR Color);
	extern void				WLayout_DrawVLine					(T_POS X,  T_POS Y1, T_POS Y2, T_COLOR Color);

	extern void				WLayout_GrSetTextColor				(T_COLOR Color);
	extern void				WLayout_PutCh						(T_POS X, T_POS Y, WORD Code, E_FONT enFont);
	extern void				WLayout_FillRect					(T_POS X1, T_POS Y1, T_POS X2, T_POS Y2, T_COLOR FillColor);
	extern void				WLayout_InverseRect					(T_POS Left, T_POS Top, T_POS Right, T_POS Bottom);
	extern void				WLayout_SetBkMode					(int nMode);
	extern T_POS			WLayout_GetOriginX					(void);
	extern T_POS			WLayout_GetOriginY					(void);
	extern void				WLayout_SaveClipRect				(TRect* pSaveRect);
	extern int				WLayout_GetTextAlign				(void);

	extern T_ID				WLayout_GetGDIID					(void);
	extern T_HANDLE			WLayout_GetGDIHandle				(T_ID ID);

	extern void				WLayout_ModifyTextStyle				(QUAD nType, QUAD nValue);
	extern void				WLayout_PutChEx						(T_POS X, T_POS Y, WORD Code, E_FONT enFont);

	extern	T_NUM			WLayout_WriteStrFromRight			(T_POS X, T_POS Y, T_CSTR pcszStr, E_FONT enFont);
	extern	T_NUM			WLayout_WriteStrFromLeft			(T_POS X, T_POS Y, T_CSTR pcszStr, E_FONT enFont);
	extern	T_NUM			WLayout_WriteStr					(T_POS X, T_POS Y, T_CSTR pcszStr, E_FONT enFont);

	extern	T_SIZE			WLayout_StringProcess				(T_POS X1, T_POS X2, T_POS Y1, T_CSTR pcszStr, E_FONT enFont, E_STRPROC enProc);
	
	extern	T_NUM			WLayout_DrawStrFromRight			(T_POS X1, T_POS X2, T_POS Y1, T_CSTR pcszStr, E_FONT enFont);
	extern	T_NUM			WLayout_DrawStrFromLeft				(T_POS X1, T_POS X2, T_POS Y1, T_CSTR pcszStr, E_FONT enFont);

	extern	BOOL			WLayout_IsRToLStr					(T_CSTR pcszStr);
	extern	T_NUM			WLayout_WriteStrFromLeft_FileName	(T_POS X, T_POS Y, T_CSTR pcszStr, E_FONT enFont, A_CHAR Type);

	extern T_SIZE			WLayout_GetFontHeight				(int Height);
	extern T_SIZE			WLayout_GetFontAscent				(int Height);
	extern T_SIZE			WLayout_GetFontDescent				(int Height);
	extern T_SIZE			WLayout_GetFontCharWidth			(int Height, A_CHAR Code);
	extern T_SIZE			WLayout_GetCharWidth				(int Height, A_CHAR Code);
	extern BOOL				WLayout_GetCharDataEx				(int Height, A_CHAR Code, TGlyphInfo* pInfo);
	extern int				WLayout_GetCharKerning				(int Height, A_CHAR PreCode, A_CHAR Code);
	extern BOOL				WLayout_IsKerningFont				(void);
	extern BOOL				WLayout_GetFontInfo					(int Height, TFontInfo* pInfo);

	extern void				WLayout_SetFontItalic				(BOOL bStyle);
	extern BOOL				WLayout_GetFontItalic				(void);
	extern void				WLayout_SetFontBold					(int Weight);
	extern int				WLayout_GetFontBold					(void);

	extern BOOL				WLayout_GetFontGlyphInfo			(int Height, A_CHAR Code, TGlyphInfo* pInfo);

	extern TFontObj*		WLayout_SetCurrentFontbyID			(int nFontFamily);

	extern BOOL				WLayout_IsMBCSLocale				(void);

	extern void				WLayout_DrawFontEx					(T_POS X, T_POS Y, TGlyphInfo* pInfo);
	extern void				WLayout_SetCurrTextX				(T_POS X);
	extern void				WLayout_SetCurrTextY				(T_POS Y);
	extern BOOL				WLayout_SetFontEffect				(QUAD Style);

	extern void				WLayout_DrawRoundRect				(T_POS X1, T_POS Y1, T_POS X2, T_POS Y2, T_SIZE CornerWidth, T_SIZE CornerHeight, T_COLOR Color);
	extern T_SIZE			WLayout_GetUnderlinePosition		(int Height);
//Defect ID : 5451
#ifdef LGETU_T500_ARAB_CA
	extern T_CSTR	 		WLayout_GetBiDiStr( T_CSTR pcszStr,T_POS X1, T_POS X2, T_POS Y1) ;
#endif
//T500 ARAB OPEN JABRI Karim 17/04/2011 [END]
	//---------------------------------------------------------------------------------------------

#endif


