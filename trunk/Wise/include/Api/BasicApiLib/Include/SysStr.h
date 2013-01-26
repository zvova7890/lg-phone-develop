/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	SYSTEM STRING

	Copyright(c) 1997-2003 BNSoft Corp.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT_SYSSTR_H_
#define		_BNSOFT_SYSSTR_H_

#include	"Include.h"
#include	"GrFont.h"

#ifndef		TYPEDEF_E_CHARSET
#define		TYPEDEF_E_CHARSET
typedef		T_ENUM			E_CHARSET;
#endif
#ifndef		TYPEDEF_E_CSUID
#define		TYPEDEF_E_CSUID
typedef		T_ENUM			E_CSUID;
#endif

#ifndef		TYPEDEF_E_FONTSTYLE
#define		TYPEDEF_E_FONTSTYLE
typedef		T_ENUM			E_FONTSTYLE;
#endif

//	Multi Lingual
#define		ML_SIGNATURE		0x01680616

typedef struct
{
	QUAD				Signature;
	const A_CHAR*			pStrTbl;
} TMLStr;


extern void			SysStr_SetCharSet           (E_CHARSET enCharSet);
extern E_CHARSET		SysStr_GetCharSet           (void);
extern BOOL			SysStr_IsUniCode            (void);
extern TMLStr*			SysStr_GetOemStrTbl         (void);
extern T_SIZE			SysStr_SizeOf               (TMLStr* pMLStr);
extern BOOL			SysStr_CopyStr              (void* pDstMem, TMLStr* pMLStr);
extern T_CSTR			SysStr_GetStr               (TMLStr* pMLStr);
extern void			SysStr_SetFontStyle         (E_FONTSTYLE enFontStyle);
extern E_FONTSTYLE		SysStr_GetFontStyle         (void);


#endif	//	_BNSOFT_SYSSTR_H_
