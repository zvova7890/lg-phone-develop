/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	DYNAMIC LINKING LIBRARY

	Copyright(c) 1997-2003 BNSoft Corp.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT__GRFONT_H_
#define		_BNSOFT__GRFONT_H_

#include	"../GrFont.h"

//-------------------------------------------------------------------------------------------------
typedef BOOL				(*T_pfnGrFont_Create)				(void);
typedef	 T_SIZE				(*T_pfnGrFont_GetAscent)			(int Height);
typedef	 T_SIZE				(*T_pfnGrFont_GetDescent)			(int Height);
typedef	 T_SIZE				(*T_pfnGrFont_GetHeight)			(int Height);   // 기존 API 호환용
typedef	 T_SIZE				(*T_pfnGrFont_GetWidth)				(int Height);
typedef	 T_SIZE				(*T_pfnGrFont_GetCharWidth)			(int Height, A_CHAR Code);
typedef void*				(*T_pfnGrFont_GetCharData)			(int Height, A_CHAR Code);
typedef QUAD				(*T_pfnGrFont_GetType)         		(int Height);
typedef void*				(*T_pfnGrFont_GetData)         		(T_CSTR pcszFont);
typedef BOOL				(*T_pfnGrFont_GetGlyphInfo)			(int Height, A_CHAR Code, TGlyphInfo* pInfo);
typedef	T_SIZE				(*T_pfnGrFont_GetUnderlinePosition)	(int Height);
typedef T_CSTR				(*T_pfnGrFont_GetFontPath)			(void);

//-------------------------------------------------------------------------------------------------
typedef struct
{
	T_pfnGrFont_Create					pfnCreate;
	T_pfnGrFont_GetHeight				pfnGetHeight;
	T_pfnGrFont_GetWidth				pfnGetWidth;
	T_pfnGrFont_GetAscent				pfnGetAscent;
	T_pfnGrFont_GetDescent				pfnGetDescent;
	T_pfnGrFont_GetType					pfnGetType;
	T_pfnGrFont_GetData					pfnGetData;
	T_pfnGrFont_GetCharWidth			pfnGetCharWidth;
	T_pfnGrFont_GetCharData				pfnGetCharData;
	T_pfnGrFont_GetGlyphInfo			pfnGetGlyphInfo;
	T_pfnGrFont_GetUnderlinePosition	pfnGetUnderlinePosition;
	T_pfnGrFont_GetFontPath				pfnGetFontPath;
} TApiGrp_GrFont;

//-------------------------------------------------------------------------------------------------
#ifndef		BNS_MAIN_VERSION

	#define		GrFont_Create()						__ApiLink0(GrFont,Create)
	#define		GrFont_GetHeight(p1)				__ApiLink1(GrFont,GetHeight,p1)
	#define		GrFont_GetWidth(p1)					__ApiLink1(GrFont,GetWidth,p1)
	#define		GrFont_GetAscent(p1)				__ApiLink1(GrFont,GetAscent,p1)
	#define		GrFont_GetDescent(p1)				__ApiLink1(GrFont,GetDescent,p1)
	#define		GrFont_GetType(p1)					__ApiLink1(GrFont,GetType,p1)
	#define		GrFont_GetData(p1)					__ApiLink1(GrFont,GetData,p1)
	#define		GrFont_GetCharWidth(p1,p2)			__ApiLink2(GrFont,GetCharWidth,p1,p2)
	#define		GrFont_GetCharData(p1,p2)			__ApiLink2(GrFont,GetCharData,p1,p2)
	#define		GrFont_GetGlyphInfo(p1,p2,p3)		__ApiLink3(GrFont,GetGlyphInfo,p1,p2,p3)
	#define		GrFont_GetUnderlinePosition(p1)		__ApiLink1(GrFont,GetHeight,p1)
	#define		GrFont_GetFontPath()				__ApiLink0(GrFont,GetFontPath)
#endif	//	BNS_MAIN_VERSION
//-------------------------------------------------------------------------------------------------

#endif	//	_BNSOFT__GRFONT_H_
