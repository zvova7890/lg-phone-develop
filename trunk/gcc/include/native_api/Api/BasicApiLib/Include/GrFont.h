/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	PRIMITIVE GRAPHIC FONT

	Copyright(c) 1997-2003 BNSoft Corp.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT_GRFONT_H_
#define		_BNSOFT_GRFONT_H_

#include	"Include.h"
#include	"ConfigGR.h"

#define		GRFONT_DEFAULT		22

typedef		unsigned int		E_FONT;

//	Font Type
#define		GRFONT_NORMAL		0x00000000
#define		GRFONT_ITALIC		0x10000000
#define		GRFONT_BOLD		0x40000000

enum
{
	FONTTYPE_BFF		= 0,
	FONTTYPE_TTF		= 1 
};

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
    BYTE		Width;		//	The bitmap width in pixels.
    BYTE		Height;		//	The bitmap height in pixels.
    signed char		Left;		//	The horizontal distance from the pen position to the left bitmap border("left side bearing")
    signed char		Top;		//	The vertical distance from the pen position (on the baseline) to the upper bitmap border("top side bearing")

    BYTE		Format;		//	The format of the glyph bitmap (monochrome or gray)
    BYTE		Maxgrays;	//	Maximum gray level value (in the range 1 to 255)
    signed short	Pitch;		//	The number of bytes per bitmap line
    signed char		xAdvance;	//	The horizontal advance width in pixels.
    signed char		yAdvance;	//	The vertical advance height in pixels.

    BYTE		DataType;	//	Data Type (Bff/TTF)
    BYTE*		pBuffer;	//	A pointer to the bitmap pixels.

    int		        GlyphIndex;
    int		        SourceIndex;
} TGlyphInfo;

//-------------------------------------------------------------------------------------------------
typedef struct
{
	int			FileType;
	A_CHAR			pName[32];
	A_CHAR			pPath[64];
	void*			pAddr;
} TFontObj;

//#define			GrFont_GetHeight							GrFont_GetFontHeight
//#define			GrFont_GetWidth(Height)						GrFont_GetCharWidth(Height, 0)
#define				GrFont_GetCharWidthEx(Height, Code, Data)	GrFont_GetCharWidth(Height, Code)
//#define			GrFont_GetAscent							GrFont_GetFontAscent
//#define			GrFont_GetDescent							GrFont_GetFontDescent



extern BOOL			GrFont_Create				(void);

extern T_SIZE			GrFont_GetHeight			(int Height);
extern T_SIZE			GrFont_GetWidth				(int Height);
extern T_SIZE			GrFont_GetAscent			(int Height);
extern T_SIZE			GrFont_GetDescent			(int Height);
extern QUAD			GrFont_GetType				(int Height);
extern void*			GrFont_GetData				(T_CSTR pcszFont);
extern T_SIZE			GrFont_GetCharWidth			(int Height, A_CHAR Code);
extern void*			GrFont_GetCharData			(int Height, A_CHAR Code); 
extern void			GrFont_SetFont				(T_CSTR pcszFontName, T_CSTR* pcszFilePath);
extern T_CSTR			GrFont_GetFont				(void);
extern T_SIZE			GrFont_GetUnderlinePosition (int Height);
extern T_CSTR			GrFont_GetFontPath			(void);

extern TFontObj*		GrFont_CreateFont			(A_CHAR* pcszFontName, A_CHAR* pcszFilePath);
extern BOOL			GrFont_DestroyFont			(TFontObj* pObj);
	
extern TFontObj*		GrFont_SetCurrentFont		(TFontObj* pObj);
extern TFontObj*		GrFont_GetCurrentFont		(void);

extern void			GrFont_SetFontItalic		(BOOL bStyle);
extern BOOL			GrFont_GetFontItalic		(void);
extern void			GrFont_SetFontBold			(int Weight);
extern int			GrFont_GetFontBold			(void);

extern BOOL			GrFont_GetFontInfo			(int Height, TFontInfo* pInfo);
extern QUAD			GrFont_GetEffectByID		(int Height);
extern T_SIZE			GrFont_GetAscent			(int Height);
extern T_SIZE			GrFont_GetDescent			(int Height);
extern T_SIZE			GrFont_GetHeight			(int Height); 

extern T_SIZE			GrFont_GetCharWidth			(int Height, A_CHAR Code);
extern BOOL			GrFont_GetCharDataEx		(int Height, A_CHAR Code, TGlyphInfo* pInfo);
extern int			GrFont_GetCharKerning		(int Height, A_CHAR PreCode, A_CHAR Code);
extern T_SIZE			GrFont_GetUnderlinePosition (int Height);

extern TFontObj*		GrFont_SetCurrentFontbyID	(int nFontFamily);

extern BOOL			GrFont_GetGlyphInfo			(int Height, A_CHAR Code, TGlyphInfo* pInfo);
extern BOOL			GrFont_SetFontEffect		(QUAD Style);
extern QUAD			GrFont_GetFontEffect		(void);
extern BOOL			GrFont_IsKerningFont		(void);


#endif	//	_BNSOFT_GRFONT_H_
