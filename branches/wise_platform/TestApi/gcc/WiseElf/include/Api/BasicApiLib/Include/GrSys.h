/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	PRIMITIVE GRAPHIC LIBRARY

	Copyright(c) 1997-2003 BNSoft Corp.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT_GRSYS_H_
#define		_BNSOFT_GRSYS_H_

#include	"Include.h"
#include	"ConfigGR.h"
#include	"GrFont.h"
#include	"ColorDef.h"

//-------------------------------------------------------------------------------------------------
//	GrSys Info
typedef struct
{
	T_ID				ID;
	T_SIZE				Width;
	T_SIZE				Height;
	T_NUM				ColorBit;
	T_COLOR*			pGrBuf;
} TGrDev;

//-------------------------------------------------------------------------------------------------
//	Text Style
typedef void			(*T_pfnCursorDraw)(int X, int Y, int W, int H);

typedef struct
{
	T_COLOR				TextColor;
	T_COLOR				TextBkColor;
	T_COLOR				InvTextColor;
	T_COLOR				InvTextBkColor;
	T_COLOR				UnderlineColor;
	T_COLOR				StrikeOutColor;
	T_POS				StartX;
	T_POS				EndX;
	T_NUM				MaxLineNum;
	int					LineGap;
	int					CharGap;
	QUAD				Effect;
	BOOL				bPartialDraw;
#if		FEATURE_SUPPORT_WORDBREAK == 1
	BOOL				bWordBreak;
#endif
	BOOL				bBiDi;
} TTextStyle;

typedef struct
{
	T_ADDR				SelStartAddr;
	T_SIZE				SelSize;
	T_ADDR				CursorAddr;
	T_POS				CursorPos;
	T_pfnCursorDraw		pfnCursorDraw;
	BOOL				bForeCursor;
} TTextInfo;

//	Image
typedef struct
{
	BYTE				Width;
	BYTE				Height;
	BYTE				ColorBit;
	BYTE				Data[1];
} TImage;

typedef struct
{
	char				Signature[4];
	T_SIZE				Width;
	T_SIZE				Height;
	T_NUM				ColorBit;
	BYTE				Data[1];
} TImage32;

//-------------------------------------------------------------------------------------------------
//	Vector Font Struct
typedef struct 
{
   BYTE			Width;
   BYTE			Height;
   signed char	Left;
   signed char  Top;
   BYTE			Format;
   BYTE			MaxGrays;
   signed short Pitch;
   signed char  XAdvance;
   signed char  YAdvance;
   BYTE*		pBuffer;
} TVectorFont;

//-------------------------------------------------------------------------------------------------
//	Vector Pixel Mode
typedef enum
{
    GRSYS_VTPIXEL_NONE = 0,
    GRSYS_VTPIXEL_MONO,
    GRSYS_VTPIXEL_GRAY,
    GRSYS_VTPIXEL_GRAY2,
    GRSYS_VTPIXEL_GRAY4,
    GRSYS_VTPIXEL_LCD,
    GRSYS_VTPIXEL_LCD_V,
    GRSYS_VTPIXEL_MAX
} GRSYS_VTPIXEL_FORMAT;


#define		GDI_DEFAULT					0
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
#define		GRSYS_SOLID				0xFFFFFFFF
#define		GRSYS_DOT				0xAAAAAAAA
#define		GRSYS_DOTDOT			        0xCCCCCCCC
#define		GRSYS_DASH				0xF0F0F0F0
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#define		GRDEV_SOLID				GRSYS_SOLID
#define		GRDEV_DOT				GRSYS_DOT
#define		GRDEV_DOTDOT				GRSYS_DOTDOT
#define		GRDEV_DASH				GRSYS_DASH
//-------------------------------------------------------------------------------------------------
#define		GRSYS_OPAQUE				0				
#define		GRSYS_TRANSPARENT			1			
#define		GRSYS_ALPHABLENDING			2				
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#define		GRDEV_OPAQUE				GRSYS_OPAQUE
#define		GRDEV_TRANSPARENT			GRSYS_TRANSPARENT
#define		GRDEV_ALPHABLENDING			GRSYS_ALPHABLENDING
//-------------------------------------------------------------------------------------------------
typedef enum
{
	TEXTSTY_TEXTCOLOR					= 0,
	TEXTSTY_TEXTBKCOLOR,
	TEXTSTY_INVTEXTCOLOR,
	TEXTSTY_INVTEXTBKCOLOR,
	TEXTSTY_UNDERLINECOLOR,
	TEXTSTY_STRIKEOUTCOLOR,
	TEXTSTY_STARTX,
	TEXTSTY_ENDX,
	TEXTSTY_MAXLINENUM,
	TEXTSTY_LINEGAP,
	TEXTSTY_CHARGAP,
	TEXTSTY_EFFECT,
	TEXTSTY_PARTIALDRAW,
	TEXTSTY_WORDBREAK,
	TEXTSTY_BIDI					//	bi-directional writing support
} E_TEXTSTY;

typedef enum
{
	STRPROC_NONE						= 0,
	STRPROC_GET_HEIGHT,
	STRPROC_GET_WIDTH,
	STRPROC_GET_CHARNUM,
	STRPROC_GET_STR_WIDTH,
	STRPROC_WRT_STR,
	STRPROC_GET_DISPLAY_STR		//20110412 dooyoung.hwang@lge.com(torch)
} E_STRPROC;

//-------------------------------------------------------------------------------------------------
#define		TEXT_NORMAL				0x00000000
#define		TEXT_INVERSE				0x80000000			//	텍스트를 반전시켜서 출력시킨다.
#define		TEXT_BOLD				0x40000000			//	텍스트를 볼드체로 출력한다.
#define		TEXT_UNDERLINE				0x20000000			//	텍스트를 출력한 후 밑줄을 긋는다.
#define		TEXT_ITALIC				0x10000000			//	텍스트를 이텔릭체로 출력한다.
#define		TEXT_OUTLINE				0x08000000			//	외곽선 폰트로 출력한다.
#define		TEXT_STRIKETHROUGH			0x04000000			//	텍스트에 취소선을 그린다(REditCtrl에만 적용).
#define		TEXT_SYSINVERSE				0x00000008			//	텍스트를 반전시켜서 출력시킨다.
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//	GrSys Macro Functions
#define		GrSys_SetPixel(X,Y,C)		GrSys_PutPixel(X,Y,C)
#define		GrSys_ClearRect(L,T,R,B)	GrSys_FillRect(L,T,R,B,(T_COLOR)-1)
#define		BNSRGB(R,G,B)			GrSys_RGB(R,G,B)

//-------------------------------------------------------------------------------------------------	{{BNS_INTERNALCODE(+)}}
//	GrSys Internal Member Functions

	//---------------------------------------------------------------------------------------------
	//	Definition of GDI Handle
	typedef		T_HANDLE					H_GDI;


	extern BOOL				GrSys_Create                (TGrDev* pGrDev);
	extern H_GDI			GrSys_SetGDIHandle          (H_GDI hGDI);
	extern H_GDI			GrSys_GetGDIHandle          (T_ID ID);
	extern void				GrSys_Reset                 (void);
	extern BOOL				GrSys_TestWordBreak         (T_POS X1, T_POS X2, T_CSTR pcszStr, E_FONT enFont);
	extern void				GrSys_EnableRefresh         (void);
	extern void				GrSys_DisableRefresh        (void);
	extern BOOL				GrSys_GetRefreshRequest		(void) ;
	extern void				GrSys_SetRefreshRequest		(BOOL bRequest) ;
	extern void				GrSys_PutAlphaBlendPixel    (T_POS X, T_POS  Y, T_COLOR Color, BYTE Level);
	extern void				GrSys_DrawVLayerImage		(T_POS X, T_POS Y, T_SIZE Width, T_SIZE Height, TImage* pHImage, TImage* pBImage, TImage* pTImage);
	extern void				GrSys_DrawHLayerImage		(T_POS X, T_POS Y, T_SIZE Width, T_SIZE Height, TImage* pLImage, TImage* pBImage, TImage* pRImage);
	extern void				GrSys_DrawExtendedImage		(T_POS X, T_POS Y, T_SIZE Width, T_SIZE Height, TImage* pImage);
	extern void				GrSys_PutChEx				(T_POS X, T_POS Y, WORD Code, E_FONT enFont);
	extern void				GrSys_DrawVectorFont		(T_POS X, T_POS Y, T_SIZE FontWidth, T_SIZE FontHeight, BYTE* pFontData);
	//---------------------------------------------------------------------------------------------
	// Layer Image의 Alphablending 추가 [Temp code, 2007.07.24/ by heyviolet]
	extern void				GrSys_DrawAlphaVLayerImage	(T_POS X, T_POS Y, T_SIZE Width, T_SIZE Height, TImage* pHImage, TImage* pBImage, TImage* pTImage, BYTE Level);
	extern void				GrSys_DrawAlphaHLayerImage	(T_POS X, T_POS Y, T_SIZE Width, T_SIZE Height, TImage* pLImage, TImage* pBImage, TImage* pRImage, BYTE Level);
	extern void				GrSys_DrawAlphaExtendedImage(T_POS X, T_POS Y, T_SIZE Width, T_SIZE Height, TImage* pImage, BYTE Level);
	//---------------------------------------------------------------------------------------------
	extern BOOL				GrSys_SetTipInfo			(TRect* Rect, T_CSTR pcszStr, T_COLOR BkColor, E_FONT enFont, T_COLOR FontColor, T_SIZE Margin, T_COLOR BorderColor);
															//	{{BNS_INTERNALCODE(-)}}
//-------------------------------------------------------------------------------------------------
//	GrSys Member Functions

	//---------------------------------------------------------------------------------------------
	//	Graphic Device Interface
	extern T_ID				GrSys_SelectGDI             (T_ID ID);
	extern T_ID				GrSys_GetGDIID              (void);

	//---------------------------------------------------------------------------------------------
	//	Initialize & Manage
	extern void				GrSys_Update                (void);
	extern void				GrSys_Refresh               (void);
	extern void				GrSys_RefreshRect           (T_POS Left, T_POS Top, T_POS Right, T_POS Bottom);
	extern void				GrSys_SetGrBuf              (T_COLOR* pBuf);
	extern T_COLOR*			GrSys_GetGrBuf              (void);
	extern BOOL				GrSys_GetInfo               (T_ID ID, TGrDev* pGrDev);
	extern T_SIZE			GrSys_GetWidth              (void);
	extern T_SIZE			GrSys_GetHeight             (void);
	extern T_NUM			GrSys_GetColorBit           (void);
	extern TRect*			GrSys_GetInvalidateRect     (T_ID ID);

	//---------------------------------------------------------------------------------------------
	//	Origine
	extern void				GrSys_SetOrigin             (T_POS OriginX, T_POS OriginY);
	extern T_POS			GrSys_GetOriginX            (void);
	extern T_POS			GrSys_GetOriginY            (void);

	//---------------------------------------------------------------------------------------------
	//	Clip Region
	extern void				GrSys_SetClipRect           (T_POS Left, T_POS Top, T_POS Right, T_POS Bottom);
	extern void				GrSys_IntersectClipRect     (T_POS Left, T_POS Top, T_POS Right, T_POS Bottom);
	extern void				GrSys_ResetClipRect         (void);
	extern void				GrSys_SaveClipRect          (TRect* pSaveRect);
	extern void				GrSys_RestoreClipRect       (TRect* pSaveRect);

	//---------------------------------------------------------------------------------------------
	//	Clear
	extern void				GrSys_Clear                 (void);

	//---------------------------------------------------------------------------------------------
	//	Effect
	extern void			GrSys_GrayRect              (T_POS Left, T_POS Top, T_POS Right, T_POS Bottom);
	extern void			GrSys_WhiteRect             (T_POS Left, T_POS Top, T_POS Right, T_POS Bottom);
	extern void			GrSys_InverseRect           (T_POS Left, T_POS Top, T_POS Right, T_POS Bottom);
	extern void			GrSys_AlphaBlendRect        (T_POS Left, T_POS Top, T_POS Right, T_POS Bottom, T_COLOR Color, BYTE Level);
	extern void			GrSys_AlphaBlendByImage     (T_POS X, T_POS Y, TImage* pImage, BYTE Level);
	//---------------------------------------------------------------------------------------------
	//	Pixel
	extern void			GrSys_PutPixel              (T_POS X, T_POS Y, T_COLOR Color);
	extern T_COLOR			GrSys_GetPixel              (T_POS X, T_POS Y);
	//---------------------------------------------------------------------------------------------
	//	Line
	extern void			GrSys_DrawLine              (T_POS X1, T_POS Y1, T_POS X2, T_POS Y2, T_COLOR Color);
	extern void			GrSys_DrawLineEx            (T_POS X1, T_POS Y1, T_POS X2, T_POS Y2, T_COLOR Color, T_SIZE Thickness, T_STROKE Stroke, int nStrokeBitNum);
	extern void			GrSys_DrawHLine             (T_POS Y,  T_POS X1, T_POS X2, T_COLOR Color);
	extern void			GrSys_DrawVLine             (T_POS X,  T_POS Y1, T_POS Y2, T_COLOR Color);
	//---------------------------------------------------------------------------------------------
	//	Rectangle
	extern void			GrSys_DrawRect              (T_POS X1, T_POS Y1, T_POS X2, T_POS Y2, T_COLOR Color);
	extern void			GrSys_DrawRectEx            (T_POS X1, T_POS Y1, T_POS X2, T_POS Y2, T_COLOR Color, T_SIZE Thickness, T_STROKE Stroke, int nStrokeBitNum);
	extern void			GrSys_FillRect              (T_POS X1, T_POS Y1, T_POS X2, T_POS Y2, T_COLOR FillColor);
	//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	//	Round Rectangle
	extern void			GrSys_DrawRoundRect         (T_POS X1, T_POS Y1, T_POS X2, T_POS Y2, T_SIZE CornerWidth, T_SIZE CornerHeight, T_COLOR Color);
	extern void			GrSys_DrawRoundRectEx       (T_POS X1, T_POS Y1, T_POS X2, T_POS Y2, T_SIZE CornerWidth, T_SIZE CornerHeight, T_COLOR Color, T_SIZE Thickness, T_STROKE Stroke, int nStrokeBitNum);
	extern void			GrSys_FillRoundRect         (T_POS X1, T_POS Y1, T_POS X2, T_POS Y2, T_SIZE CornerWidth, T_SIZE CornerHeight, T_COLOR FillColor);
	//---------------------------------------------------------------------------------------------
	//	Circle & Ellipse
	extern void			GrSys_DrawCircle            (T_POS X, T_POS Y, T_SIZE Diameter, T_COLOR Color);
	extern void			GrSys_DrawCircleEx          (T_POS X, T_POS Y, T_SIZE Diameter, T_COLOR Color, T_SIZE Thickness, T_STROKE Stroke, int nStrokeBitNum);
	extern void			GrSys_FillCircle            (T_POS X, T_POS Y, T_SIZE Diameter, T_COLOR FillColor);
	extern void			GrSys_DrawEllipse           (T_POS X1, T_POS Y1, T_POS X2, T_POS Y2, T_COLOR Color);
	extern void			GrSys_DrawEllipseEx         (T_POS X1, T_POS Y1, T_POS X2, T_POS Y2, T_COLOR Color, T_SIZE Thickness, T_STROKE Stroke, int nStrokeBitNum);
	extern void			GrSys_FillEllipse           (T_POS X1, T_POS Y1, T_POS X2, T_POS Y2, T_COLOR FillColor);

	//---------------------------------------------------------------------------------------------
	//	Arc & Pie
	extern void			GrSys_DrawArc               (T_POS X1, T_POS Y1, T_POS X2, T_POS Y2, T_POS StartAngle, int ArcAngle, T_COLOR Color);
	extern void			GrSys_DrawArcEx             (T_POS X1, T_POS Y1, T_POS X2, T_POS Y2, T_POS StartAngle, int ArcAngle, T_COLOR Color, T_SIZE Thickness, T_STROKE Stroke, int nStrokeBitNum);
	extern void			GrSys_DrawPie               (T_POS X1, T_POS Y1, T_POS X2, T_POS Y2, T_POS StartAngle, int ArcAngle, T_COLOR Color);
	extern void			GrSys_DrawPieEx             (T_POS X1, T_POS Y1, T_POS X2, T_POS Y2, T_POS StartAngle, int ArcAngle, T_COLOR Color, T_SIZE Thickness, T_STROKE Stroke, int nStrokeBitNum);
	extern void			GrSys_FillPie               (T_POS X1, T_POS Y1, T_POS X2, T_POS Y2, T_POS StartAngle, int ArcAngle, T_COLOR FillColor);

	//---------------------------------------------------------------------------------------------
	//	Filling
	extern void			GrSys_FloodFill             (T_POS X, T_POS Y, T_COLOR FillColor, T_COLOR BorderColor);

	//---------------------------------------------------------------------------------------------
	//	Image
	extern void			GrSys_PutImage              (T_POS X, T_POS Y, TImage* pImage);
	extern void			GrSys_AlphaPutImage         (T_POS X, T_POS Y, TImage* pImage, BYTE Level);
	extern void			GrSys_PutImageEx            (T_POS X, T_POS Y, T_SIZE ImageWidth, T_SIZE ImageHeight, T_SIZE ImageColorBit, BYTE* pImageData);
	extern void			GrSys_SetDefPalette         (T_COLOR* pPalette);
	extern void			GrSys_PutPaletteImage       (T_POS X, T_POS Y, T_SIZE ImageWidth, T_SIZE ImageHeight, T_COLOR* pPalette, BYTE* pImageData);
	extern T_NUM			GrSys_GetImage              (T_POS Left, T_POS Top, T_POS Right, T_POS Bottom, TImage* pImage, T_SIZE ImageBufSize);
	extern T_NUM			GrSys_GetImage32			(T_POS  Left, T_POS Top, T_POS  Right, T_POS  Bottom, TImage32* pImage, T_SIZE ImageBufSize);
	extern T_SIZE			GrSys_GetImageWidth         (TImage* pImage);
	extern T_SIZE			GrSys_GetImageHeight        (TImage* pImage);
	extern T_NUM			GrSys_GetImageColorBit      (TImage* pImage);
	extern void				GrSys_StretchPutImage		(T_POS nSrcX1, T_POS nSrcY1, T_SIZE nSrcWidth, T_SIZE nSrcHeight, 
														 T_POS nDestX1, T_POS nDestY1, T_SIZE nDestWidth, T_SIZE nDestHeight,
														 TImage* pImage, T_COLOR* pPalette);
	extern void				GrSys_StretchPutImageEx		(T_POS nSrcX1, T_POS nSrcY1, T_SIZE nSrcWidth, T_SIZE nSrcHeight, 
														 T_POS nDestX1, T_POS nDestY1, T_SIZE nDestWidth, T_SIZE nDestHeight,
														 T_SIZE nImageWidth, T_SIZE nImageHeight, T_SIZE nImageColorBit, BYTE* pImageData, T_COLOR* pPalette);

//---------------------------------------------------------------------------------------------
//	Text
extern void			GrSys_DrawFont              (T_POS X, T_POS Y, T_SIZE FontWidth, T_SIZE FontHeight, BYTE* pFontData);
extern void			GrSys_DrawFontEx            (T_POS X, T_POS Y, TGlyphInfo* pInfo);
extern T_NUM			GrSys_WriteStr              (T_POS X, T_POS Y, T_CSTR pcszStr, E_FONT enFont);
extern T_NUM			GrSys_WriteStrFromLeft      (T_POS X, T_POS Y, T_CSTR pcszStr, E_FONT enFont);
extern T_NUM			GrSys_WriteStrFromRight     (T_POS X, T_POS Y, T_CSTR pcszStr, E_FONT enFont);
extern T_NUM			GrSys_WriteBiDiStr          (T_POS X1, T_POS X2, T_POS Y, T_CSTR pcszStr, E_FONT enFont);

extern T_SIZE			GrSys_TestWriteStr          (T_POS X, T_POS Y, T_CSTR pcszStr, E_FONT enFont);
extern T_SIZE			GrSys_TestWriteStrFromLeft  (T_POS X, T_POS Y, T_CSTR pcszStr, E_FONT enFont);
extern T_SIZE			GrSys_TestWriteStrFromRight (T_POS X, T_POS Y, T_CSTR pcszStr, E_FONT enFont);
extern T_NUM			GrSys_TestWriteStrByCharNum (T_POS X1, T_POS X2, T_CSTR pcszStr, E_FONT enFont);
extern T_SIZE			GrSys_CalcStrWidth          (T_CSTR pcszStr, E_FONT enFont);


extern BOOL				GrSys_GetDisplayStr			(T_CSTR pcszStr, T_STR pOutBuf, int nBufSize);	


extern void				GrSys_PutCh                 (T_POS X, T_POS Y, WORD Code, E_FONT enFont);

	extern void				GrSys_SetTextInfo           (T_CSTR pcszStr, T_POS StartPos, T_POS EndPos, T_POS CursorPos);
	extern void				GrSys_SetCursorDrawProc     (T_pfnCursorDraw pfnCursorDraw);
	extern void				GrSys_SetForeCursor         (BOOL bForeCursor);

	extern void				GrSys_ResetTextStyle        (void);
	extern void				GrSys_ModifyTextStyle       (QUAD nType, QUAD nValue);
	extern void				GrSys_GetTextStyle          (TTextStyle* pTextStyle);
	extern void				GrSys_SetTextStyle          (TTextStyle* pTextStyle);

	extern void				GrSys_SetTextColor          (T_COLOR Color);
	extern T_COLOR			GrSys_GetTextColor          (void);
	extern void				GrSys_SetBkColor            (T_COLOR Color);
	extern T_COLOR			GrSys_GetBkColor            (void);
	extern void				GrSys_SetBold               (BOOL bBold);
	extern BOOL				GrSys_GetBold               (void);
	extern void				GrSys_SetItalic             (BOOL bItalic);
	extern BOOL				GrSys_GetItalic             (void);
	extern void				GrSys_SetBkMode             (int nMode);
	extern int				GrSys_GetBkMode             (void);
	extern T_POS			GrSys_GetCurrTextX          (void);
	extern void				GrSys_SetCurrTextX			(T_POS X);
	extern T_POS			GrSys_GetCurrTextY          (void);
	extern void				GrSys_SetCurrTextY			(T_POS Y);
	extern void				GrSys_SetAlign              (int nAlignType);
	extern int				GrSys_GetAlign				(void);

	//---------------------------------------------------------------------------------------------
	//	Color
	extern T_COLOR			GrSys_RGB                   (BYTE r, BYTE g, BYTE b);
	extern void				GrSys_GetRGB                (T_COLOR Color, BYTE* pr, BYTE* pg, BYTE* pb);
	extern BYTE				GrSys_GetRValue             (T_COLOR Color);
	extern BYTE				GrSys_GetGValue             (T_COLOR Color);
	extern BYTE				GrSys_GetBValue             (T_COLOR Color);
	extern T_COLOR			GrSys_SetTransparentColor   (T_COLOR Color);
	extern T_COLOR			GrSys_GetTransparentColor   (void);
//@#ifdef		POST_REFRESH_METHOD
	extern void				GrSys_Refresh_Direct(void);
	extern void				GrSys_RefreshRect_Direct(T_POS Left, T_POS Top, T_POS Right, T_POS Bottom);
	extern void				GrSys_RefreshAll(void);
//@#endif
	extern 	void			GrSys_SetVFontDrawType		(int DrawType);
#ifndef BNS_EMULATOR
	extern void				GrSys_GDI32To16				(T_ID ID);
	extern void				GrSys_GDI16To32				(T_ID ID);
#endif	
	T_COLOR					GrSys_ConvertRBG			(T_COLOR Color);  
	extern	BOOL			GrSys_IsRToLStr				(T_CSTR pcszStr);
	extern	T_NUM			GrSys_WriteStrFromLeft_FileName(T_POS X, T_POS Y, T_CSTR pcszStr, E_FONT enFont, A_CHAR Type);
	extern	int				GrSys_GetLastDispGDI(void);

	extern void			 	GrSys_SaveRect				(BYTE* pBuf, T_POS X1, T_POS Y1, T_POS X2, T_POS Y2);
	extern void				GrSys_RestoreRect			(BYTE* pBuf, T_POS X1, T_POS Y1, T_POS X2, T_POS Y2);

	extern void				GrSys_Memcpy64(int* dst, int* src, int n);
//LGSI_T3_MEA_OPEN_CA_Sharad_08Nov_2011_Start
#ifdef LGETU_T500_ARAB_CA	
	extern T_CSTR			GrSys_GetBiDiStr( T_CSTR pcszStr,T_POS X1, T_POS X2, T_POS Y1);
#endif
	//---------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
#define		GRSYS_WIDTH					GrSys_GetWidth()
#define		GRSYS_HEIGHT				GrSys_GetHeight()
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#define		GRDEV_WIDTH					GRSYS_WIDTH
#define		GRDEV_HEIGHT				GRSYS_HEIGHT
//-------------------------------------------------------------------------------------------------
#define		GRSYS_MIN_X					0
#define		GRSYS_MAX_X					(GRSYS_WIDTH - 1)
#define		GRSYS_MIN_Y					0
#define		GRSYS_MAX_Y					(GRSYS_HEIGHT - 1)
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#define		GRDEV_MIN_X					GRSYS_MIN_X
#define		GRDEV_MAX_X					GRSYS_MAX_X
#define		GRDEV_MIN_Y					GRSYS_MIN_Y
#define		GRDEV_MAX_Y					GRSYS_MAX_Y
//-------------------------------------------------------------------------------------------------
#endif	//	_BNSOFT_GRSYS_H_
