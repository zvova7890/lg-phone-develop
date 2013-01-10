/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	DYNAMIC LINKING LIBRARY

	Copyright(c) 1997-2003 BNSoft Corp.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT__GRSYS_H_
#define		_BNSOFT__GRSYS_H_

#include	"../GrSys.h"

//-------------------------------------------------------------------------------------------------
typedef BOOL			(*T_pfnGrSys_Create)		    (TGrDev* pGrDev);
typedef	H_GDI			(*T_pfnGrSys_SetGDIHandle)          (H_GDI hGDI);
typedef H_GDI			(*T_pfnGrSys_GetGDIHandle)          (T_ID ID);
typedef T_ID			(*T_pfnGrSys_SelectGDI)             (T_ID ID);
typedef	T_ID			(*T_pfnGrSys_GetGDIID)		    (void);
typedef void			(*T_pfnGrSys_Refresh)               (void);
typedef void			(*T_pfnGrSys_RefreshRect)           (T_POS Left, T_POS Top, T_POS Right, T_POS Bottom);
typedef void			(*T_pfnGrSys_Refresh_Direct)        (void);
typedef void			(*T_pfnGrSys_RefreshRect_Direct)    (T_POS Left, T_POS Top, T_POS Right, T_POS Bottom);
typedef void			(*T_pfnGrSys_SetGrBuf)              (T_COLOR* pBuf);
typedef T_COLOR*		(*T_pfnGrSys_GetGrBuf)              (void);
typedef BOOL			(*T_pfnGrSys_GetInfo)               (T_ID ID, TGrDev* pGrDev);
typedef T_SIZE			(*T_pfnGrSys_GetWidth)              (void);
typedef T_SIZE			(*T_pfnGrSys_GetHeight)             (void);
typedef T_NUM			(*T_pfnGrSys_GetColorBit)           (void);
typedef void			(*T_pfnGrSys_SetOrigin)             (T_POS OriginX, T_POS OriginY);
typedef T_POS			(*T_pfnGrSys_GetOriginX)            (void);
typedef T_POS			(*T_pfnGrSys_GetOriginY)            (void);
typedef void			(*T_pfnGrSys_SetClipRect)           (T_POS Left, T_POS Top, T_POS Right, T_POS Bottom);
typedef void			(*T_pfnGrSys_IntersectClipRect)     (T_POS Left, T_POS Top, T_POS Right, T_POS Bottom);
typedef void			(*T_pfnGrSys_ResetClipRect)         (void);
typedef void			(*T_pfnGrSys_SaveClipRect)          (TRect* pSaveRect);
typedef void			(*T_pfnGrSys_RestoreClipRect)       (TRect* pSaveRect);
typedef void			(*T_pfnGrSys_Clear)                 (void);
typedef void			(*T_pfnGrSys_GrayRect)              (T_POS Left, T_POS Top, T_POS Right, T_POS Bottom);
typedef void			(*T_pfnGrSys_InverseRect)           (T_POS Left, T_POS Top, T_POS Right, T_POS Bottom);
typedef void			(*T_pfnGrSys_AlphaBlendRect)        (T_POS Left, T_POS Top, T_POS Right, T_POS Bottom, T_COLOR Color, BYTE Level);
typedef void			(*T_pfnGrSys_AlphaBlendByImage)     (T_POS X, T_POS Y, TImage* pImage, BYTE Level);
typedef void			(*T_pfnGrSys_PutPixel)              (T_POS X, T_POS Y, T_COLOR Color);
typedef T_COLOR			(*T_pfnGrSys_GetPixel)              (T_POS X, T_POS Y);
typedef void			(*T_pfnGrSys_DrawLine)              (T_POS X1, T_POS Y1, T_POS X2, T_POS Y2, T_COLOR Color);
typedef void			(*T_pfnGrSys_DrawLineEx)            (T_POS X1, T_POS Y1, T_POS X2, T_POS Y2, T_COLOR Color, T_SIZE Thickness, T_STROKE Stroke, int nStrokeBitNum);
typedef void			(*T_pfnGrSys_DrawHLine)             (T_POS Y,  T_POS X1, T_POS X2, T_COLOR Color);
typedef void			(*T_pfnGrSys_DrawVLine)             (T_POS X,  T_POS Y1, T_POS Y2, T_COLOR Color);
typedef void			(*T_pfnGrSys_DrawRect)              (T_POS X1, T_POS Y1, T_POS X2, T_POS Y2, T_COLOR Color);
typedef void			(*T_pfnGrSys_DrawRectEx)            (T_POS X1, T_POS Y1, T_POS X2, T_POS Y2, T_COLOR Color, T_SIZE Thickness, T_STROKE Stroke, int nStrokeBitNum);
typedef void			(*T_pfnGrSys_FillRect)              (T_POS X1, T_POS Y1, T_POS X2, T_POS Y2, T_COLOR FillColor);
typedef void			(*T_pfnGrSys_DrawRoundRect)         (T_POS X1, T_POS Y1, T_POS X2, T_POS Y2, T_SIZE CornerWidth, T_SIZE CornerHeight, T_COLOR Color);
typedef void			(*T_pfnGrSys_DrawRoundRectEx)       (T_POS X1, T_POS Y1, T_POS X2, T_POS Y2, T_SIZE CornerWidth, T_SIZE CornerHeight, T_COLOR Color, T_SIZE Thickness, T_STROKE Stroke, int nStrokeBitNum);
typedef void			(*T_pfnGrSys_FillRoundRect)         (T_POS X1, T_POS Y1, T_POS X2, T_POS Y2, T_SIZE CornerWidth, T_SIZE CornerHeight, T_COLOR FillColor);
typedef void			(*T_pfnGrSys_DrawCircle)            (T_POS X, T_POS Y, T_SIZE Diameter, T_COLOR Color);
typedef void			(*T_pfnGrSys_DrawCircleEx)          (T_POS X, T_POS Y, T_SIZE Diameter, T_COLOR Color, T_SIZE Thickness, T_STROKE Stroke, int nStrokeBitNum);
typedef void			(*T_pfnGrSys_FillCircle)            (T_POS X, T_POS Y, T_SIZE Diameter, T_COLOR FillColor);
typedef void			(*T_pfnGrSys_DrawEllipse)           (T_POS X1, T_POS Y1, T_POS X2, T_POS Y2, T_COLOR Color);
typedef void			(*T_pfnGrSys_DrawEllipseEx)         (T_POS X1, T_POS Y1, T_POS X2, T_POS Y2, T_COLOR Color, T_SIZE Thickness, T_STROKE Stroke, int nStrokeBitNum);
typedef void			(*T_pfnGrSys_FillEllipse)           (T_POS X1, T_POS Y1, T_POS X2, T_POS Y2, T_COLOR FillColor);
typedef void			(*T_pfnGrSys_DrawArc)               (T_POS X1, T_POS Y1, T_POS X2, T_POS Y2, T_POS StartAngle, int ArcAngle, T_COLOR Color);
typedef void			(*T_pfnGrSys_DrawArcEx)             (T_POS X1, T_POS Y1, T_POS X2, T_POS Y2, T_POS StartAngle, int ArcAngle, T_COLOR Color, T_SIZE Thickness, T_STROKE Stroke, int nStrokeBitNum);
typedef void			(*T_pfnGrSys_DrawPie)               (T_POS X1, T_POS Y1, T_POS X2, T_POS Y2, T_POS StartAngle, int ArcAngle, T_COLOR Color);
typedef void			(*T_pfnGrSys_DrawPieEx)             (T_POS X1, T_POS Y1, T_POS X2, T_POS Y2, T_POS StartAngle, int ArcAngle, T_COLOR Color, T_SIZE Thickness, T_STROKE Stroke, int nStrokeBitNum);
typedef void			(*T_pfnGrSys_FillPie)               (T_POS X1, T_POS Y1, T_POS X2, T_POS Y2, T_POS StartAngle, int ArcAngle, T_COLOR FillColor);
typedef void			(*T_pfnGrSys_FloodFill)             (T_POS X, T_POS Y, T_COLOR FillColor, T_COLOR BorderColor);
typedef void			(*T_pfnGrSys_PutImage)              (T_POS X, T_POS Y, TImage* pImage);
typedef void			(*T_pfnGrSys_AlphaPutImage)         (T_POS X, T_POS Y, TImage* pImage, BYTE Level);
typedef void			(*T_pfnGrSys_PutImageEx)            (T_POS X, T_POS Y, T_SIZE ImageWidth, T_SIZE ImageHeight, T_SIZE ImageColorBit, BYTE* pImageData);
typedef void			(*T_pfnGrSys_SetDefPalette)         (T_COLOR* pPalette);
typedef void			(*T_pfnGrSys_PutPaletteImage)       (T_POS X, T_POS Y, T_SIZE ImageWidth, T_SIZE ImageHeight, T_COLOR* pPalette, BYTE* pImageData);
typedef T_NUM			(*T_pfnGrSys_GetImage)              (T_POS Left, T_POS Top, T_POS Right, T_POS Bottom, TImage* pImage, T_SIZE ImageBufSize);
typedef T_NUM			(*T_pfnGrSys_GetImage32)            (T_POS Left, T_POS Top, T_POS Right, T_POS Bottom, TImage32* pImage, T_SIZE ImageBufSize);
typedef T_SIZE			(*T_pfnGrSys_GetImageWidth)         (TImage* pImage);
typedef T_SIZE			(*T_pfnGrSys_GetImageHeight)        (TImage* pImage);
typedef T_NUM			(*T_pfnGrSys_GetImageColorBit)      (TImage* pImage);
typedef void			(*T_pfnGrSys_DrawFont)              (T_POS X, T_POS Y, T_SIZE FontWidth, T_SIZE FontHeight, BYTE* pFontData);
typedef void			(*T_pfnGrSys_SetAlign)              (int nAlignType);
typedef int				(*T_pfnGrSys_GetAlign)              (void);
typedef T_NUM			(*T_pfnGrSys_WriteStr)              (T_POS X, T_POS Y, T_CSTR pszStr, E_FONT enFont);
typedef T_NUM			(*T_pfnGrSys_WriteStrFromLeft)      (T_POS X, T_POS Y, T_CSTR pszStr, E_FONT enFont);
typedef T_NUM			(*T_pfnGrSys_WriteStrFromRight)     (T_POS X, T_POS Y, T_CSTR pszStr, E_FONT enFont);
typedef T_NUM			(*T_pfnGrSys_WriteBiDiStr)          (T_POS X1, T_POS X2, T_POS Y, T_CSTR pszStr, E_FONT enFont);
typedef T_SIZE			(*T_pfnGrSys_TestWriteStr)          (T_POS X, T_POS Y, T_CSTR pszStr, E_FONT enFont);
typedef T_SIZE			(*T_pfnGrSys_TestWriteStrFromLeft)  (T_POS X, T_POS Y, T_CSTR pszStr, E_FONT enFont);
typedef T_SIZE			(*T_pfnGrSys_TestWriteStrFromRight) (T_POS X, T_POS Y, T_CSTR pszStr, E_FONT enFont);
typedef T_NUM			(*T_pfnGrSys_TestWriteStrByCharNum) (T_POS X1, T_POS X2, T_CSTR pcszStr, E_FONT enFont);
typedef T_SIZE			(*T_pfnGrSys_CalcStrWidth)          (T_CSTR pcszStr, E_FONT enFont);
typedef void			(*T_pfnGrSys_PutCh)                 (T_POS X, T_POS Y, WORD Code, E_FONT enFont);
typedef void			(*T_pfnGrSys_SetTextInfo)           (T_CSTR pszStr, T_POS StartPos, T_POS EndPos, T_POS CursorPos);
typedef void			(*T_pfnGrSys_SetCursorDrawProc)     (T_pfnCursorDraw pfnCursorDraw);
typedef void			(*T_pfnGrSys_SetForeCursor)         (BOOL bForeCursor);
typedef void			(*T_pfnGrSys_ResetTextStyle)        (void);
typedef void			(*T_pfnGrSys_ModifyTextStyle)       (QUAD nType, QUAD nValue);
typedef void			(*T_pfnGrSys_GetTextStyle)          (TTextStyle* pTextStyle);
typedef void			(*T_pfnGrSys_SetTextStyle)          (TTextStyle* pTextStyle);
typedef void			(*T_pfnGrSys_SetTextColor)          (T_COLOR Color);
typedef T_COLOR			(*T_pfnGrSys_GetTextColor)          (void);
typedef void			(*T_pfnGrSys_SetBkColor)            (T_COLOR Color);
typedef T_COLOR			(*T_pfnGrSys_GetBkColor)            (void);
typedef void			(*T_pfnGrSys_SetBold)               (BOOL bBold);
typedef BOOL			(*T_pfnGrSys_GetBold)               (void);
typedef void			(*T_pfnGrSys_SetItalic)             (BOOL bItalic);
typedef BOOL			(*T_pfnGrSys_GetItalic)             (void);
typedef void			(*T_pfnGrSys_SetBkMode)             (int nMode);
typedef int				(*T_pfnGrSys_GetBkMode)             (void);
typedef T_POS			(*T_pfnGrSys_GetCurrTextX)          (void);
typedef void			(*T_pfnGrSys_SetCurrTextX)          (T_POS X);
typedef T_POS			(*T_pfnGrSys_GetCurrTextY)          (void);
typedef void			(*T_pfnGrSys_SetCurrTextY)          (T_POS Y);
typedef T_COLOR			(*T_pfnGrSys_RGB)                   (BYTE r, BYTE g, BYTE b);
typedef void			(*T_pfnGrSys_GetRGB)                (T_COLOR Color, BYTE* pr, BYTE* pg, BYTE* pb);
typedef BYTE			(*T_pfnGrSys_GetRValue)             (T_COLOR Color);
typedef BYTE			(*T_pfnGrSys_GetGValue)             (T_COLOR Color);
typedef BYTE			(*T_pfnGrSys_GetBValue)             (T_COLOR Color);
typedef T_COLOR			(*T_pfnGrSys_SetTransparentColor)   (T_COLOR Color);
typedef T_COLOR			(*T_pfnGrSys_GetTransparentColor)   (void);

typedef void			(*T_pfnGrSys_EnableRefresh)         (void);
typedef void			(*T_pfnGrSys_DisableRefresh)        (void);
typedef	void			(*T_pfnGrSys_SetVFontDrawType)		(int DrawType);
typedef	BOOL			(*T_pfnGrSys_IsRToLStr)				(T_CSTR pcszStr);
typedef T_NUM			(*T_pfnGrSys_WriteStrFromLeft_FileName)      (T_POS X, T_POS Y, T_CSTR pszStr, E_FONT enFont, A_CHAR Type);
#ifndef BNS_EMULATOR
typedef void			(*T_pfnGrSys_GDI32To16	)			(T_ID ID);
typedef void			(*T_pfnGrSys_GDI16To32	)			(T_ID ID);
#endif
// inserted by kim.yongbae 2010-12-03 [START]
typedef	void			(*T_pfnGrSys_DrawVLayerImage)		(T_POS X, T_POS Y, T_SIZE Width, T_SIZE Height, TImage* pHImage, TImage* pBImage, TImage* pTImage);//imsi
// inserted by kim.yongbae 2010-12-03 [END]

//20110221 dooyoung.hwang@lge.com(torch) (Modified At DAKOTA)
typedef	void 			(*T_pfnGrSys_DrawHLayerImage)		(T_POS X, T_POS Y, T_SIZE Width, T_SIZE Height, TImage* pLImage, TImage* pBImage, TImage* pRImage);

//20110413 dooyoung.hwang@lge.com(torch) (Modified At DAKOTA)
typedef	BOOL 			(*T_pfnGrSys_GetDisplayStr)			(T_CSTR pcszStr, T_STR pOutBuf, int nBufSize);


//-------------------------------------------------------------------------------------------------
typedef struct
{
	//T_pfnGrSys_Create					pfnCreate;
	//T_pfnGrSys_SetGDIHandle				pfnSetGDIHandle;
	T_pfnGrSys_GetGDIHandle				pfnGetGDIHandle;
	T_pfnGrSys_SelectGDI				pfnSelectGDI;
	T_pfnGrSys_GetGDIID					pfnGetGDIID;
	T_pfnGrSys_Refresh					pfnRefresh;
	T_pfnGrSys_RefreshRect				pfnRefreshRect;
//@#ifdef		POST_REFRESH_METHOD
	//T_pfnGrSys_Refresh_Direct			pfnRefresh_Direct;
	//T_pfnGrSys_RefreshRect_Direct		pfnRefreshRect_Direct;
//@#endif
	T_pfnGrSys_SetGrBuf					pfnSetGrBuf;
	T_pfnGrSys_GetGrBuf					pfnGetGrBuf;
	T_pfnGrSys_GetInfo					pfnGetInfo;
	T_pfnGrSys_GetWidth					pfnGetWidth;
	T_pfnGrSys_GetHeight				pfnGetHeight;
	T_pfnGrSys_GetColorBit				pfnGetColorBit;
	T_pfnGrSys_SetOrigin				pfnSetOrigin;
	T_pfnGrSys_GetOriginX				pfnGetOriginX;
	T_pfnGrSys_GetOriginY				pfnGetOriginY;
	T_pfnGrSys_SetClipRect				pfnSetClipRect;
	T_pfnGrSys_IntersectClipRect		pfnIntersectClipRect;
	T_pfnGrSys_ResetClipRect			pfnResetClipRect;
	T_pfnGrSys_SaveClipRect				pfnSaveClipRect;
	T_pfnGrSys_RestoreClipRect			pfnRestoreClipRect;
	T_pfnGrSys_Clear					pfnClear;
	T_pfnGrSys_GrayRect					pfnGrayRect;
	T_pfnGrSys_InverseRect				pfnInverseRect;
	T_pfnGrSys_AlphaBlendRect			pfnAlphaBlendRect;
	T_pfnGrSys_AlphaBlendByImage		pfnAlphaBlendByImage;
	T_pfnGrSys_PutPixel					pfnPutPixel;
	T_pfnGrSys_GetPixel					pfnGetPixel;
	T_pfnGrSys_DrawLine					pfnDrawLine;
	T_pfnGrSys_DrawLineEx				pfnDrawLineEx;
	T_pfnGrSys_DrawHLine				pfnDrawHLine;
	T_pfnGrSys_DrawVLine				pfnDrawVLine;
	T_pfnGrSys_DrawRect					pfnDrawRect;
	T_pfnGrSys_DrawRectEx				pfnDrawRectEx;
	T_pfnGrSys_FillRect					pfnFillRect;
	T_pfnGrSys_DrawRoundRect			pfnDrawRoundRect;
	T_pfnGrSys_DrawRoundRectEx			pfnDrawRoundRectEx;
	T_pfnGrSys_FillRoundRect			pfnFillRoundRect;
	T_pfnGrSys_DrawCircle				pfnDrawCircle;
	T_pfnGrSys_DrawCircleEx				pfnDrawCircleEx;
	T_pfnGrSys_FillCircle				pfnFillCircle;
	T_pfnGrSys_DrawEllipse				pfnDrawEllipse;
	T_pfnGrSys_DrawEllipseEx			pfnDrawEllipseEx;
	T_pfnGrSys_FillEllipse				pfnFillEllipse;
	T_pfnGrSys_DrawArc					pfnDrawArc;
	T_pfnGrSys_DrawArcEx				pfnDrawArcEx;
	T_pfnGrSys_DrawPie					pfnDrawPie;
	T_pfnGrSys_DrawPieEx				pfnDrawPieEx;
	T_pfnGrSys_FillPie					pfnFillPie;
	T_pfnGrSys_FloodFill				pfnFloodFill;
	T_pfnGrSys_PutImage					pfnPutImage;
	T_pfnGrSys_AlphaPutImage			pfnAlphaPutImage;
	T_pfnGrSys_PutImageEx				pfnPutImageEx;
	T_pfnGrSys_SetDefPalette			pfnSetDefPalette;
	T_pfnGrSys_PutPaletteImage			pfnPutPaletteImage;
	T_pfnGrSys_GetImage					pfnGetImage;
	T_pfnGrSys_GetImage32				pfnGetImage32;
	T_pfnGrSys_GetImageWidth			pfnGetImageWidth;
	T_pfnGrSys_GetImageHeight			pfnGetImageHeight;
	T_pfnGrSys_GetImageColorBit			pfnGetImageColorBit;
	T_pfnGrSys_DrawFont					pfnDrawFont;
	T_pfnGrSys_SetAlign					pfnSetAlign;
	T_pfnGrSys_GetAlign					pfnGetAlign;
	T_pfnGrSys_WriteStr					pfnWriteStr;
	T_pfnGrSys_WriteStrFromLeft			pfnWriteStrFromLeft;
	T_pfnGrSys_WriteStrFromRight		pfnWriteStrFromRight;
	T_pfnGrSys_WriteBiDiStr				pfnWriteBiDiStr;
	T_pfnGrSys_TestWriteStr				pfnTestWriteStr;
	T_pfnGrSys_TestWriteStrFromLeft		pfnTestWriteStrFromLeft;
	T_pfnGrSys_TestWriteStrFromRight	pfnTestWriteStrFromRight;
	T_pfnGrSys_TestWriteStrByCharNum	pfnTestWriteStrByCharNum;
	unsigned int niibu_wtf;
	T_pfnGrSys_CalcStrWidth				pfnCalcStrWidth;
	T_pfnGrSys_PutCh					pfnPutCh;
	T_pfnGrSys_SetTextInfo				pfnSetTextInfo;
	T_pfnGrSys_SetCursorDrawProc		pfnSetCursorDrawProc;
	T_pfnGrSys_SetForeCursor			pfnSetForeCursor;
	T_pfnGrSys_ResetTextStyle			pfnResetTextStyle;
	T_pfnGrSys_ModifyTextStyle			pfnModifyTextStyle;
	T_pfnGrSys_GetTextStyle				pfnGetTextStyle;
	T_pfnGrSys_SetTextStyle				pfnSetTextStyle;
	T_pfnGrSys_SetTextColor				pfnSetTextColor;
	T_pfnGrSys_GetTextColor				pfnGetTextColor;
	T_pfnGrSys_SetBkColor				pfnSetBkColor;
	T_pfnGrSys_GetBkColor				pfnGetBkColor;
	T_pfnGrSys_SetBold					pfnSetBold;
	T_pfnGrSys_GetBold					pfnGetBold;
	T_pfnGrSys_SetItalic				pfnSetItalic;
	T_pfnGrSys_GetItalic				pfnGetItalic;
	T_pfnGrSys_SetBkMode				pfnSetBkMode;
	T_pfnGrSys_GetBkMode				pfnGetBkMode;
	T_pfnGrSys_GetCurrTextX				pfnGetCurrTextX;
	T_pfnGrSys_GetCurrTextY				pfnGetCurrTextY;
	T_pfnGrSys_RGB						pfnRGB;
	T_pfnGrSys_GetRGB					pfnGetRGB;
	T_pfnGrSys_GetRValue				pfnGetRValue;
	T_pfnGrSys_GetGValue				pfnGetGValue;
	T_pfnGrSys_GetBValue				pfnGetBValue;
	T_pfnGrSys_SetTransparentColor		pfnSetTransparentColor;
	T_pfnGrSys_GetTransparentColor		pfnGetTransparentColor;
	T_pfnGrSys_EnableRefresh			pfnEnableRefresh;
	T_pfnGrSys_DisableRefresh			pfnDisableRefresh;
	T_pfnGrSys_SetVFontDrawType			pfnSetVFontDrawType;
	T_pfnGrSys_IsRToLStr				pfnIsRToLStr;
	T_pfnGrSys_WriteStrFromLeft_FileName pfnWriteStrFromLeft_FileName;
#ifndef BNS_EMULATOR
	T_pfnGrSys_GDI32To16				pfnGDI32To16;                                       //add by yrdo
	T_pfnGrSys_GDI16To32				pfnGDI16To32;	                                   //add by yrdo
#endif
// inserted by kim.yongbae 2010-12-03 [START]
	T_pfnGrSys_DrawVLayerImage 			pfnDrawVLayerImage;
// inserted by kim.yongbae 2010-12-03 [END]

	//20110221 dooyoung.hwang@lge.com(torch)
	T_pfnGrSys_DrawHLayerImage			pfnDrawHLayerImage;

	//20110413 dooyoung.hwang@lge.com(torch) (Modified At DAKOTA)
	T_pfnGrSys_GetDisplayStr			pfnGetDisplayStr;

} TApiGrp_GrSys;

//-------------------------------------------------------------------------------------------------
#ifndef		BNS_MAIN_VERSION

	#define		GrSys_Create(p1)										__ApiLink1(GrSys,Create,p1)
	#define		GrSys_SetGDIHandle(p1)									__ApiLink1(GrSys,SetGDIHandle,p1)
	#define		GrSys_GetGDIHandle(p1)									__ApiLink1(GrSys,GetGDIHandle,p1)
	#define		GrSys_SelectGDI(p1)										__ApiLink1(GrSys,SelectGDI,p1)
	#define		GrSys_GetGDIID()										__ApiLink0(GrSys,GetGDIID)
	#define		GrSys_Refresh()											__ApiLink0(GrSys,Refresh)
	#define		GrSys_RefreshRect(p1,p2,p3,p4)							__ApiLink4(GrSys,RefreshRect,p1,p2,p3,p4)
//@#ifdef		POST_REFRESH_METHOD
	#define		GrSys_Refresh_Direct()									__ApiLink0(GrSys,Refresh_Direct)
	#define		GrSys_RefreshRect_Direct(p1,p2,p3,p4)					__ApiLink4(GrSys,RefreshRect_Direct,p1,p2,p3,p4)
//@#endif
	#define		GrSys_SetGrBuf(p1)										__ApiLink1(GrSys,SetGrBuf,p1)
	#define		GrSys_GetGrBuf()										__ApiLink0(GrSys,GetGrBuf)
	#define		GrSys_GetInfo(p1,p2)									__ApiLink2(GrSys,GetInfo,p1,p2)
	#define		GrSys_GetWidth()										__ApiLink0(GrSys,GetWidth)
	#define		GrSys_GetHeight()										__ApiLink0(GrSys,GetHeight)
	#define		GrSys_GetColorBit()										__ApiLink0(GrSys,GetColorBit)
	#define		GrSys_SetOrigin(p1,p2)									__ApiLink2(GrSys,SetOrigin,p1,p2)
	#define		GrSys_GetOriginX()										__ApiLink0(GrSys,GetOriginX)
	#define		GrSys_GetOriginY()										__ApiLink0(GrSys,GetOriginY)
	#define		GrSys_SetClipRect(p1,p2,p3,p4)							__ApiLink4(GrSys,SetClipRect,p1,p2,p3,p4)
	#define		GrSys_IntersectClipRect(p1,p2,p3,p4)					__ApiLink4(GrSys,IntersectClipRect,p1,p2,p3,p4)
	#define		GrSys_ResetClipRect()									__ApiLink0(GrSys,ResetClipRect)
	#define		GrSys_SaveClipRect(p1)									__ApiLink1(GrSys,SaveClipRect,p1)
	#define		GrSys_RestoreClipRect(p1)								__ApiLink1(GrSys,RestoreClipRect,p1)
	#define		GrSys_Clear()											__ApiLink0(GrSys,Clear)
	#define		GrSys_GrayRect(p1,p2,p3,p4)								__ApiLink4(GrSys,GrayRect,p1,p2,p3,p4)
	#define		GrSys_InverseRect(p1,p2,p3,p4)							__ApiLink4(GrSys,InverseRect,p1,p2,p3,p4)
	#define		GrSys_AlphaBlendRect(p1,p2,p3,p4,p5,p6)					__ApiLink6(GrSys,AlphaBlendRect,p1,p2,p3,p4,p5,p6)
	#define		GrSys_AlphaBlendByImage(p1,p2,p3,p4)					__ApiLink4(GrSys,AlphaBlendByImage,p1,p2,p3,p4)
	#define		GrSys_PutPixel(p1,p2,p3)								__ApiLink3(GrSys,PutPixel,p1,p2,p3)
	#define		GrSys_GetPixel(p1,p2)									__ApiLink2(GrSys,GetPixel,p1,p2)
	#define		GrSys_DrawLine(p1,p2,p3,p4,p5)							__ApiLink5(GrSys,DrawLine,p1,p2,p3,p4,p5)
	#define		GrSys_DrawLineEx(p1,p2,p3,p4,p5,p6,p7,p8)				__ApiLink8(GrSys,DrawLineEx,p1,p2,p3,p4,p5,p6,p7,p8)
	#define		GrSys_DrawHLine(p1,p2,p3,p4)							__ApiLink4(GrSys,DrawHLine,p1,p2,p3,p4)
	#define		GrSys_DrawVLine(p1,p2,p3,p4)							__ApiLink4(GrSys,DrawVLine,p1,p2,p3,p4)
	#define		GrSys_DrawRect(p1,p2,p3,p4,p5)							__ApiLink5(GrSys,DrawRect,p1,p2,p3,p4,p5)
	#define		GrSys_DrawRectEx(p1,p2,p3,p4,p5,p6,p7,p8)				__ApiLink8(GrSys,DrawRectEx,p1,p2,p3,p4,p5,p6,p7,p8)
	#define		GrSys_FillRect(p1,p2,p3,p4,p5)							__ApiLink5(GrSys,FillRect,p1,p2,p3,p4,p5)
	#define		GrSys_DrawRoundRect(p1,p2,p3,p4,p5,p6,p7)				__ApiLink7(GrSys,DrawRoundRect,p1,p2,p3,p4,p5,p6,p7)
	#define		GrSys_DrawRoundRectEx(p1,p2,p3,p4,p5,p6,p7,p8,p9,pA)	__ApiLinkA(GrSys,DrawRoundRectEx,p1,p2,p3,p4,p5,p6,p7,p8,p9,pA)
	#define		GrSys_FillRoundRect(p1,p2,p3,p4,p5,p6,p7)				__ApiLink7(GrSys,FillRoundRect,p1,p2,p3,p4,p5,p6,p7)
	#define		GrSys_DrawCircle(p1,p2,p3,p4)							__ApiLink4(GrSys,DrawCircle,p1,p2,p3,p4)
	#define		GrSys_DrawCircleEx(p1,p2,p3,p4,p5,p6,p7)				__ApiLink7(GrSys,DrawCircleEx,p1,p2,p3,p4,p5,p6,p7)
	#define		GrSys_FillCircle(p1,p2,p3,p4)							__ApiLink4(GrSys,FillCircle,p1,p2,p3,p4)
	#define		GrSys_DrawEllipse(p1,p2,p3,p4,p5)						__ApiLink5(GrSys,DrawEllipse,p1,p2,p3,p4,p5)
	#define		GrSys_DrawEllipseEx(p1,p2,p3,p4,p5,p6,p7,p8)			__ApiLink8(GrSys,DrawEllipseEx,p1,p2,p3,p4,p5,p6,p7,p8)
	#define		GrSys_FillEllipse(p1,p2,p3,p4,p5)						__ApiLink5(GrSys,FillEllipse,p1,p2,p3,p4,p5)
	#define		GrSys_DrawArc(p1,p2,p3,p4,p5,p6,p7)						__ApiLink7(GrSys,DrawArc,p1,p2,p3,p4,p5,p6,p7)
	#define		GrSys_DrawArcEx(p1,p2,p3,p4,p5,p6,p7,p8,p9,pA)			__ApiLinkA(GrSys,DrawArcEx,p1,p2,p3,p4,p5,p6,p7,p8,p9,pA)
	#define		GrSys_DrawPie(p1,p2,p3,p4,p5,p6,p7)						__ApiLink7(GrSys,DrawPie,p1,p2,p3,p4,p5,p6,p7)
	#define		GrSys_DrawPieEx(p1,p2,p3,p4,p5,p6,p7,p8,p9,pA)			__ApiLinkA(GrSys,DrawPieEx,p1,p2,p3,p4,p5,p6,p7,p8,p9,pA)
	#define		GrSys_FillPie(p1,p2,p3,p4,p5,p6,p7)						__ApiLink7(GrSys,FillPie,p1,p2,p3,p4,p5,p6,p7)
	#define		GrSys_FloodFill(p1,p2,p3,p4)							__ApiLink4(GrSys,FloodFill,p1,p2,p3,p4)
	#define		GrSys_PutImage(p1,p2,p3)								__ApiLink3(GrSys,PutImage,p1,p2,p3)
	#define		GrSys_AlphaPutImage(p1,p2,p3,p4)						__ApiLink4(GrSys,AlphaPutImage,p1,p2,p3,p4)
	#define		GrSys_PutImageEx(p1,p2,p3,p4,p5,p6)						__ApiLink6(GrSys,PutImageEx,p1,p2,p3,p4,p5,p6)
	#define		GrSys_SetDefPalette(p1)									__ApiLink1(GrSys,SetDefPalette,p1)
	#define		GrSys_PutPaletteImage(p1,p2,p3,p4,p5,p6)				__ApiLink6(GrSys,PutPaletteImage,p1,p2,p3,p4,p5,p6)
	#define		GrSys_GetImage(p1,p2,p3,p4,p5,p6)						__ApiLink6(GrSys,GetImage,p1,p2,p3,p4,p5,p6)
	#define		GrSys_GetImage32(p1,p2,p3,p4,p5,p6)						__ApiLink6(GrSys,GetImage32,p1,p2,p3,p4,p5,p6)
	#define		GrSys_GetImageWidth(p1)									__ApiLink1(GrSys,GetImageWidth,p1)
	#define		GrSys_GetImageHeight(p1)								__ApiLink1(GrSys,GetImageHeight,p1)
	#define		GrSys_GetImageColorBit(p1)								__ApiLink1(GrSys,GetImageColorBit,p1)
	#define		GrSys_DrawFont(p1,p2,p3,p4,p5)							__ApiLink5(GrSys,DrawFont,p1,p2,p3,p4,p5)
	#define		GrSys_SetAlign(p1)										__ApiLink1(GrSys,SetAlign,p1)
	#define		GrSys_GetAlign()										__ApiLink0(GrSys,GetAlign)
	#define		GrSys_WriteStr(p1,p2,p3,p4)								__ApiLink4(GrSys,WriteStr,p1,p2,p3,p4)
	#define		GrSys_WriteStrFromLeft(p1,p2,p3,p4)						__ApiLink4(GrSys,WriteStrFromLeft,p1,p2,p3,p4)
	#define		GrSys_WriteStrFromRight(p1,p2,p3,p4)					__ApiLink4(GrSys,WriteStrFromRight,p1,p2,p3,p4)
	#define		GrSys_WriteBiDiStr(p1,p2,p3,p4,p5)	  					__ApiLink5(GrSys,WriteBiDiStr,p1,p2,p3,p4,p5)
	#define		GrSys_TestWriteStr(p1,p2,p3,p4)							__ApiLink4(GrSys,TestWriteStr,p1,p2,p3,p4)
	#define		GrSys_TestWriteStrFromLeft(p1,p2,p3,p4)					__ApiLink4(GrSys,TestWriteStrFromLeft,p1,p2,p3,p4)
	#define		GrSys_TestWriteStrFromRight(p1,p2,p3,p4)				__ApiLink4(GrSys,TestWriteStrFromRight,p1,p2,p3,p4)
	#define		GrSys_TestWriteStrByCharNum(p1,p2,p3,p4)				__ApiLink4(GrSys,TestWriteStrByCharNum,p1,p2,p3,p4)
	#define		GrSys_CalcStrWidth(p1,p2)								__ApiLink2(GrSys,CalcStrWidth,p1,p2)
	#define		GrSys_PutCh(p1,p2,p3,p4)								__ApiLink4(GrSys,PutCh,p1,p2,p3,p4)
	#define		GrSys_SetTextInfo(p1,p2,p3,p4)							__ApiLink4(GrSys,SetTextInfo,p1,p2,p3,p4)
	#define		GrSys_SetCursorDrawProc(p1)								__ApiLink1(GrSys,SetCursorDrawProc,p1)
	#define		GrSys_SetForeCursor(p1)									__ApiLink1(GrSys,SetForeCursor,p1)
	#define		GrSys_ResetTextStyle()									__ApiLink0(GrSys,ResetTextStyle)
	#define		GrSys_ModifyTextStyle(p1,p2)							__ApiLink2(GrSys,ModifyTextStyle,p1,p2)
	#define		GrSys_GetTextStyle(p1)									__ApiLink1(GrSys,GetTextStyle,p1)
	#define		GrSys_SetTextStyle(p1)									__ApiLink1(GrSys,SetTextStyle,p1)
	#define		GrSys_SetTextColor(p1)									__ApiLink1(GrSys,SetTextColor,p1)
	#define		GrSys_GetTextColor()									__ApiLink0(GrSys,GetTextColor)
	#define		GrSys_SetBkColor(p1)									__ApiLink1(GrSys,SetBkColor,p1)
	#define		GrSys_GetBkColor()										__ApiLink0(GrSys,GetBkColor)
	#define		GrSys_SetBold(p1)										__ApiLink1(GrSys,SetBold,p1)
	#define		GrSys_GetBold()											__ApiLink0(GrSys,GetBold)
	#define		GrSys_SetItalic(p1)										__ApiLink1(GrSys,SetItalic,p1)
	#define		GrSys_GetItalic()										__ApiLink0(GrSys,GetItalic)
	#define		GrSys_SetBkMode(p1)										__ApiLink1(GrSys,SetBkMode,p1)
	#define		GrSys_GetBkMode()										__ApiLink0(GrSys,GetBkMode)
	#define		GrSys_GetCurrTextX()									__ApiLink0(GrSys,GetCurrTextX)
	#define		GrSys_SetCurrTextX(p1)									__ApiLink1(GrSys,SetCurrTextX, p1)
	#define		GrSys_GetCurrTextY()									__ApiLink0(GrSys,GetCurrTextY)
	#define		GrSys_SetCurrTextY(p1)									__ApiLink1(GrSys,SetCurrTextY, p1)
	#define		GrSys_RGB(p1,p2,p3)										__ApiLink3(GrSys,RGB,p1,p2,p3)
	#define		GrSys_GetRGB(p1,p2,p3,p4)								__ApiLink4(GrSys,GetRGB,p1,p2,p3,p4)
	#define		GrSys_GetRValue(p1)										__ApiLink1(GrSys,GetRValue,p1)
	#define		GrSys_GetGValue(p1)										__ApiLink1(GrSys,GetGValue,p1)
	#define		GrSys_GetBValue(p1)										__ApiLink1(GrSys,GetBValue,p1)
	#define		GrSys_SetTransparentColor(p1)							__ApiLink1(GrSys,SetTransparentColor,p1)
	#define		GrSys_GetTransparentColor()								__ApiLink0(GrSys,GetTransparentColor)

	#define		GrSys_EnableRefresh()									__ApiLink0(GrSys,EnableRefresh)
	#define		GrSys_DisableRefresh()									__ApiLink0(GrSys,DisableRefresh)
	#define		GrSys_SetVFontDrawType(p1)								__ApiLink1(GrSys,SetVFontDrawType,p1)
	#define		GrSys_IsRToLStr(p1)										__ApiLink1(GrSys,IsRToLStr,p1)
	#define		GrSys_WriteStrFromLeft_FileName(p1,p2,p3,p4,p5)			__ApiLink5(GrSys,WriteStrFromLeft_FileName,p1,p2,p3,p4,p5)
#ifndef BNS_EMULATOR
	#define		GrSys_GDI32To16(p1)									      __ApiLink1(GrSys,GDI32To16,p1)
	#define		GrSys_GDI16To32(p1)									      __ApiLink1(GrSys,GDI16To32,p1)
#endif
// inserted by kim.yongbae 2010-12-03 [START]
	#define		GrSys_DrawVLayerImage(p1,p2,p3,p4,p5,p6,p7)				__ApiLink7(GrSys,DrawVLayerImage,p1,p2,p3,p4,p5,p6,p7)
// inserted by kim.yongbae 2010-12-03 [END]

	//20110221 dooyoung.hwang@lge.com(torch) (Modified At DAKOTA)
	#define		GrSys_DrawHLayerImage(p1,p2,p3,p4,p5,p6,p7)				__ApiLink7(GrSys,DrawHLayerImage,p1,p2,p3,p4,p5,p6,p7)

	//20110413 dooyoung.hwang@lge.com(torch) (Modified At DAKOTA)
	#define		GrSys_GetDisplayStr(p1,p2,p3)							__ApiLink3(GrSys,GetDisplayStr,p1,p2,p3)

#endif	//	BNS_MAIN_VERSION
//-------------------------------------------------------------------------------------------------

#endif	//	_BNSOFT__GRSYS_H_
