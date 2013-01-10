/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	PRIMITIVE GRAPHIC FONT

	Copyright(c) 1997-2003 BNSoft Corp.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT_GRFONT_H_
#define		_BNSOFT_GRFONT_H_

#include	"Include.h"
#include	"ConfigGR.h"

//-------------------------------------------------------------------------------------------------
#define		GRFONT_DEFAULT		22
typedef		unsigned int		E_FONT;

//-------------------------------------------------------------------------------------------------
//	Font Type의 종류
#define		GRFONT_NORMAL			0x00000000
#define		GRFONT_ITALIC			0x10000000
#define		GRFONT_BOLD			0x40000000

//-------------------------------------------------------------------------------------------------
enum
{
	FONTTYPE_BFF		= 0,
	FONTTYPE_TTF		= 1 
};

//-------------------------------------------------------------------------------------------------
//	Glyph Pixel Mode Format
typedef enum
{
    GRFONT_GLYPHPIXEL_NONE = 0,
    GRFONT_GLYPHPIXEL_MONO,
    GRFONT_GLYPHPIXEL_GRAY,
    GRFONT_GLYPHPIXEL_GRAY2,
    GRFONT_GLYPHPIXEL_GRAY4,
    GRFONT_GLYPHPIXEL_LCD,
    GRFONT_GLYPHPIXEL_LCD_V,
    GRFONT_GLYPHPIXEL_MAX
} GRFONT_GLYPHPIXEL_FORMAT;

//-------------------------------------------------------------------------------------------------
//	Font Structure
typedef struct
{
	T_SIZE			Width;			//	Default Width
	T_SIZE			Height;
	BYTE			Ascender;
	BYTE			Descender;
	T_CSTR			pcszFontName;
	T_CSTR			pcszFilePath;
} TFontInfo;

//	Glyph Structure
typedef struct
{
    BYTE			Width;			//	The bitmap width in pixels.
    BYTE			Height;			//	The bitmap height in pixels.
    signed char		Left;			//	The horizontal distance from the pen position to the left bitmap border("left side bearing")
    signed char		Top;			//	The vertical distance from the pen position (on the baseline) to the upper bitmap border("top side bearing")

    BYTE			Format;			//	The format of the glyph bitmap (monochrome or gray)
    BYTE			Maxgrays;		//	Maximum gray level value (in the range 1 to 255)
    signed short	Pitch;			//	The number of bytes per bitmap line
    signed char		xAdvance;		//	The horizontal advance width in pixels.
    signed char		yAdvance;		//	The vertical advance height in pixels.

	BYTE			DataType;		//	Data Type (Bff/TTF)
    BYTE*			pBuffer;		//	A pointer to the bitmap pixels.

	int				GlyphIndex;
	int				SourceIndex;
} TGlyphInfo;

//-------------------------------------------------------------------------------------------------
typedef struct
{
	int				FileType;
	A_CHAR			pName[32];
	A_CHAR			pPath[64];
	void*			pAddr;
} TFontObj;

//#define			GrFont_GetHeight							GrFont_GetFontHeight
//#define			GrFont_GetWidth(Height)						GrFont_GetCharWidth(Height, 0)
#define				GrFont_GetCharWidthEx(Height, Code, Data)	GrFont_GetCharWidth(Height, Code)
//#define			GrFont_GetAscent							GrFont_GetFontAscent
//#define			GrFont_GetDescent							GrFont_GetFontDescent


//-------------------------------------------------------------------------------------------------	{{BNS_INTERNALCODE(+)}}
//	GrFont Internal Structure & Member Functions
#ifdef		BNS_MAIN_VERSION

	extern BOOL				GrFont_Init            (void);
	extern void				GrFont_Exit            (void);
	extern BOOL				GrFont_GetFaceName	   (A_CHAR* pPath, A_CHAR* pName);
	extern E_FONT			GrFont_GetFontID		(int nHeight, BOOL bWeight, BOOL bItalic);
#endif	//	BNS_MAIN_VERSION																	//	{{BNS_INTERNALCODE(-)}}
//-------------------------------------------------------------------------------------------------

//	GrFont Member Functions
#ifdef		BNS_MAIN_VERSION
	//---------------------------------------------------------------------------------------------
	//	Font : 종류가 결정되면, Path, Name 만 정해 진다.
	//	Char : height가 결정되어야, Ascent, Descent 정보 및 각 Char 별로 Width가 결정 된다.
	//---------------------------------------------------------------------------------------------

	//  APP의 기존 호환성을 위해서..
	extern BOOL				GrFont_Create				(void);

	extern T_SIZE			GrFont_GetHeight			(int Height);
	extern T_SIZE			GrFont_GetWidth				(int Height);
	extern T_SIZE			GrFont_GetAscent			(int Height);
	extern T_SIZE			GrFont_GetDescent			(int Height);
	extern QUAD				GrFont_GetType				(int Height);
	extern void*			GrFont_GetData				(T_CSTR pcszFont);
	extern T_SIZE			GrFont_GetCharWidth			(int Height, A_CHAR Code);
	extern void*			GrFont_GetCharData			(int Height, A_CHAR Code); 
	extern void				GrFont_SetFont				(T_CSTR pcszFontName, T_CSTR* pcszFilePath);
	extern T_CSTR			GrFont_GetFont				(void);
	extern T_SIZE			GrFont_GetUnderlinePosition (int Height);
	extern T_CSTR			GrFont_GetFontPath			(void);

	//	폰트를 List에 추가/삭제 한다.
	extern TFontObj*		GrFont_CreateFont			(A_CHAR* pcszFontName, A_CHAR* pcszFilePath);
	extern BOOL				GrFont_DestroyFont			(TFontObj* pObj);
	
	//---------------------------------------------------------------------------------------------
	//	현재 폰트 종류를 설정 한다.
	extern TFontObj*		GrFont_SetCurrentFont		(TFontObj* pObj);
	extern TFontObj*		GrFont_GetCurrentFont		(void);

	//---------------------------------------------------------------------------------------------
	//	Font Style & Weight는 정해진 font가 아니라, 모든 종류의 폰트에 설정된다.
	extern void				GrFont_SetFontItalic		(BOOL bStyle);
	extern BOOL				GrFont_GetFontItalic		(void);
	extern void				GrFont_SetFontBold			(int Weight);
	extern int				GrFont_GetFontBold			(void);

	//---------------------------------------------------------------------------------------------
	//	현재 설정된 폰트에 대한 정보만을 알려준다.
	//	현재 설정된 폰트에 Height가 반드시 정해져야 한다.
	extern BOOL				GrFont_GetFontInfo			(int Height, TFontInfo* pInfo);
	extern QUAD				GrFont_GetEffectByID		(int Height);
	extern T_SIZE			GrFont_GetAscent			(int Height);
	extern T_SIZE			GrFont_GetDescent			(int Height);
	extern T_SIZE			GrFont_GetHeight			(int Height);   // 기존 API 호환용

	extern T_SIZE			GrFont_GetCharWidth			(int Height, A_CHAR Code);
	extern BOOL				GrFont_GetCharDataEx		(int Height, A_CHAR Code, TGlyphInfo* pInfo);
	extern int				GrFont_GetCharKerning		(int Height, A_CHAR PreCode, A_CHAR Code);
	extern T_SIZE			GrFont_GetUnderlinePosition (int Height);


	//---------------------------------------------------------------------------------------------
	//	기존의 Font ID를 사용 하던 방식 지원
//	extern T_SIZE			GrFont_GetHeight			(int Height);
	extern TFontObj*		GrFont_SetCurrentFontbyID	(int nFontFamily);

	extern BOOL				GrFont_GetGlyphInfo			(int Height, A_CHAR Code, TGlyphInfo* pInfo);
	extern BOOL				GrFont_SetFontEffect		(QUAD Style);
	extern QUAD				GrFont_GetFontEffect		(void);
	extern BOOL				GrFont_IsKerningFont		(void);

#endif	//	BNS_MAIN_VERSION
//-------------------------------------------------------------------------------------------------

#endif	//	_BNSOFT_GRFONT_H_
