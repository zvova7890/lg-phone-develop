/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	UNICODE LIBRARY

	Copyright(c)     -2002 LG Electronics Inc.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_LGE_UNICODELIB_H_
#define		_LGE_UNICODELIB_H_

#include	"Include.h"
#include	<ctype.h>
//-------------------------------------------------------------------------------------------------
//	UnicodeLib Type Definition

#define				UNI_UNKNOWN_CODE		0xFFFF
#define				JPN_UNKNOWN_CODE		0xFFFF


//-------------------------------------------------------------------------------------------------
//	UnicdeLib Debug Kind

//-------------------------------------------------------------------------------------------------
//	Definition
#define				UniLib_Isalnum(c)		(isalnum((int)c))
#define				UniLib_Isalpha(c)		(isalpha((int)c))
#define				UniLib_Isascii(c)		(isascii((int)c))
#define				UniLib_Iscntrl(c)		(iscntrl((int)c))
#define				UniLib_Isdigit(c)		(isdigit((int)c))
#define				UniLib_Isgraph(c)		(isgraph((int)c))
#define				UniLib_Islower(c)		(islower((int)c))
#define				UniLib_Isprint(c)		(isprint((int)c))
#define				UniLib_Ispunct(c)		(ispunct((int)c))
#define				UniLib_Isspace(c)		(isspace((int)c))
#define				UniLib_Isupper(c)		(isupper((int)c))
#define				UniLib_Isxdigit(c)		(isxdigit((int)c))
#define				UniLib_Toascii(c)		(toascii((int)c))
#define				UniLib_Tolower(ch)		(tolower((int)ch))
#define				UniLib_Toupper(ch)		(toupper((int)ch))


//	UnicdeLib Member Functions

extern U_CHAR*		UniLib_Strcpy			(U_CHAR* strDest, const U_CHAR* strSource);
extern U_CHAR*		UniLib_Strncpy			(U_CHAR* strDest, const U_CHAR* strSource, T_SIZE count);
extern LONG		UniLib_Strcmp			(const U_CHAR* string1, const U_CHAR *string2);
extern LONG		UniLib_Strncmp			(const U_CHAR* string1, const U_CHAR *string2, T_SIZE count);
extern T_SIZE		UniLib_Strlen			(const U_CHAR* string);
extern U_CHAR*		UniLib_Strupr			(U_CHAR* string);
extern U_CHAR*		UniLib_Strlwr			(U_CHAR* string);
extern U_CHAR*		UniLib_Strset			(U_CHAR* string, U_CHAR c);
extern U_CHAR*		UniLib_Strnset			(U_CHAR* string, U_CHAR c, T_SIZE count);
extern U_CHAR*		UniLib_Strcat			(U_CHAR* strDest, const U_CHAR* strSource);
extern U_CHAR*		UniLib_Strncat			(U_CHAR* strDest, const U_CHAR* strSource, T_SIZE count);
extern int		UniLib_Sprintf			(U_CHAR* buf, const U_CHAR* format, ...);
extern int		UniLib_Vsprintf			(U_CHAR* buf, const U_CHAR* fmt, va_list args);
extern U_CHAR*		UniLib_Strstr			(const U_CHAR* string, const U_CHAR* strCharSet);
extern U_CHAR*		UniLib_Strchr			(const U_CHAR* string, U_CHAR c);
extern U_CHAR*		UniLib_Strtok			(U_CHAR *s, const U_CHAR *delim);

extern int		UniLib_Atoi				(const U_CHAR *nptr);
extern long		UniLib_Atol				(const U_CHAR *nptr);
extern double		UniLib_Strtod			(const U_CHAR *nptr, U_CHAR **endptr);
extern long		UniLib_Strtol			(const U_CHAR *nptr, U_CHAR **endptr, int base);
extern U_CHAR*		UniLib_Strrchr			(const U_CHAR* string, int ch);

extern int		UniLib_UTF8ToUCS2		(M_CHAR *s, U_CHAR *uc);
extern int		UniLib_UCS2ToUTF8		(T_CSTR ucs2, M_CHAR *s);

extern int 		UniLib_SJISStrToUCS2Str	(M_CHAR* pMultiByteStr, WORD cbMultiByte, U_CHAR* pWideCharStr, WORD cchWideChar);
extern int		UniLib_UCS2StrToSJISStr	(U_CHAR* pWideCharStr, WORD cchWideChar, char* pMultiByteStr, WORD cbMultiByte);
extern WORD		UniLib_SJISToUCS2		(WORD Code);
extern WORD		UniLib_UCS2ToSJIS		(WORD Code);
extern WORD		UniLib_KutenToUCS2		(WORD Code);

extern int		UniLib_RIS506StrToUCS2Str(M_CHAR* pMultiByteStr, WORD cbMultiByte, U_CHAR* pWideCharStr, WORD cchWideChar);
extern int		UniLib_UCS2StrToRIS506Str(U_CHAR* pWideCharStr, WORD cchWideChar, M_CHAR* pMultiByteStr, WORD cbMultiByte);
extern WORD		UniLib_RIS506ToUCS2		(WORD Code);
extern WORD		UniLib_UCS2ToRIS506		(WORD Code);
extern int 		UniLib_EUCJPStrToUCS2Str(M_CHAR* pMultiByteStr, WORD cbMultiByte, U_CHAR* pWideCharStr, WORD cchWideChar);
extern WORD		UniLib_EUCJPToUCS2		(WORD Code);
extern int		UniLib_KSCStrToUCS2Str	(M_CHAR* pChar, WORD* pUnicodeBuf);
extern int		UniLib_UCS2StrToKSCStr	(U_CHAR* pUnicode, M_CHAR* pKscBuf);
extern WORD		UniLib_KSCToUCS2		(WORD KscCode);
extern WORD		UniLib_UCS2ToKSC		(WORD UniCode);

#endif	//	_LGE_UNICODELIB_H_
