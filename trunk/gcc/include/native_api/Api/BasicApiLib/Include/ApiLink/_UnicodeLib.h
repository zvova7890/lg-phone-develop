/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	DYNAMIC LINKING LIBRARY

	Copyright(c)     -2003 LG Electronics Inc.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_LGE__UNICODELIB_H_
#define		_LGE__UNICODELIB_H_

#include	"../UnicodeLib.h"

typedef	U_CHAR*		(*T_pfnUniLib_Strcpy)			(U_CHAR* strDest, const U_CHAR* strSource);
typedef	U_CHAR*		(*T_pfnUniLib_Strncpy)			(U_CHAR* strDest, const U_CHAR* strSource, T_SIZE count);
typedef	LONG		(*T_pfnUniLib_Strcmp)			(const U_CHAR* string1, const U_CHAR *string2);
typedef	LONG		(*T_pfnUniLib_Strncmp)			(const U_CHAR* string1, const U_CHAR *string2, T_SIZE count);
typedef	T_SIZE		(*T_pfnUniLib_Strlen)			(const U_CHAR* string);
typedef	U_CHAR*		(*T_pfnUniLib_Strupr)			(U_CHAR* string);
typedef	U_CHAR*		(*T_pfnUniLib_Strlwr)			(U_CHAR* string);
typedef	U_CHAR*		(*T_pfnUniLib_Strset)			(U_CHAR* string, U_CHAR c);
typedef	U_CHAR*		(*T_pfnUniLib_Strnset)			(U_CHAR* string, U_CHAR c, T_SIZE count);
typedef	U_CHAR*		(*T_pfnUniLib_Strcat)			(U_CHAR* strDest, const U_CHAR* strSource);
typedef	U_CHAR*		(*T_pfnUniLib_Strncat)			(U_CHAR* strDest, const U_CHAR* strSource, T_SIZE count);
typedef	int		(*T_pfnUniLib_Vsprintf)			(U_CHAR* buf, const U_CHAR* fmt, va_list args);
typedef	int		(*T_pfnUniLib_Sprintf)			(U_CHAR* buf, const U_CHAR* format, ...);
typedef	U_CHAR*		(*T_pfnUniLib_Strstr)			(const U_CHAR* string, const U_CHAR* strCharSet);
typedef	U_CHAR*		(*T_pfnUniLib_Strchr)			(const U_CHAR* string, U_CHAR c);
typedef U_CHAR*		(*T_pfnUniLib_Strtok)			(U_CHAR *s, const U_CHAR *delim);
typedef int		(*T_pfnUniLib_Atoi)			(const U_CHAR *nptr);
typedef long		(*T_pfnUniLib_Atol)			(const U_CHAR *nptr);
typedef double		(*T_pfnUniLib_Strtod)			(const U_CHAR *nptr, U_CHAR **endptr);
typedef long		(*T_pfnUniLib_Strtol)			(const U_CHAR *nptr, U_CHAR **endptr, int base);
typedef U_CHAR*		(*T_pfnUniLib_Strrchr)			(const U_CHAR* string, int ch);
typedef int		(*T_pfnUniLib_UTF8ToUCS2)		(M_CHAR *utf8, U_CHAR* ucs2_string);
typedef int		(*T_pfnUniLib_UCS2ToUTF8)		(T_CSTR ucs2_string, M_CHAR *utf8);
typedef int 		(*T_pfnUniLib_SJISStrToUCS2Str)	        (M_CHAR* pMultiByteStr, WORD cbMultiByte, U_CHAR* pWideCharStr, WORD cchWideChar);
typedef int		(*T_pfnUniLib_UCS2StrToSJISStr)	        (U_CHAR* pWideCharStr, WORD cchWideChar, char* pMultiByteStr, WORD cbMultiByte);
typedef WORD		(*T_pfnUniLib_SJISToUCS2)		(WORD Code);
typedef WORD		(*T_pfnUniLib_UCS2ToSJIS)		(WORD Code);
typedef WORD		(*T_pfnUniLib_KutenToUCS2)		(WORD Code);
typedef int		(*T_pfnUniLib_RIS506StrToUCS2Str)       (M_CHAR* pMultiByteStr, WORD cbMultiByte, U_CHAR* pWideCharStr, WORD cchWideChar);
typedef int		(*T_pfnUniLib_UCS2StrToRIS506Str)       (U_CHAR* pWideCharStr, WORD cchWideChar, M_CHAR* pMultiByteStr, WORD cbMultiByte);
typedef WORD		(*T_pfnUniLib_RIS506ToUCS2)		(WORD Code);
typedef WORD		(*T_pfnUniLib_UCS2ToRIS506)		(WORD Code);
typedef int 		(*T_pfnUniLib_EUCJPStrToUCS2Str)        (M_CHAR* pMultiByteStr, WORD cbMultiByte, U_CHAR* pWideCharStr, WORD cchWideChar);
typedef WORD		(*T_pfnUniLib_EUCJPToUCS2)		(WORD Code);
typedef int		(*T_pfnUniLib_KSCStrToUCS2Str)	        (M_CHAR* pChar, WORD* pUnicodeBuf);
typedef int		(*T_pfnUniLib_UCS2StrToKSCStr)	        (U_CHAR* pUnicode, M_CHAR* pKscBuf);
typedef WORD		(*T_pfnUniLib_KSCToUCS2)		(WORD KscCode);
typedef WORD		(*T_pfnUniLib_UCS2ToKSC)		(WORD UniCode);

typedef struct
{
	T_pfnUniLib_Strcpy		pfnStrcpy;
	T_pfnUniLib_Strncpy		pfnStrncpy;
	T_pfnUniLib_Strcmp		pfnStrcmp;
	T_pfnUniLib_Strncmp		pfnStrncmp;
	T_pfnUniLib_Strlen		pfnStrlen;
	T_pfnUniLib_Strupr		pfnStrupr;
	T_pfnUniLib_Strlwr		pfnStrlwr;
	T_pfnUniLib_Strset		pfnStrset;
	T_pfnUniLib_Strnset		pfnStrnset;
	T_pfnUniLib_Strcat		pfnStrcat;
	T_pfnUniLib_Strncat		pfnStrncat;
	T_pfnUniLib_Vsprintf		pfnVsprintf;
	T_pfnUniLib_Sprintf		pfnSprintf;
	T_pfnUniLib_Strstr		pfnStrstr;
	T_pfnUniLib_Strchr		pfnStrchr;
	T_pfnUniLib_Strtok		pfnStrtok;
	T_pfnUniLib_Atoi		pfnAtoi;
	T_pfnUniLib_Atol		pfnAtol;
	T_pfnUniLib_Strtod		pfnStrtod;
	T_pfnUniLib_Strtol		pfnStrtol;
	T_pfnUniLib_Strrchr		pfnStrrchr;
	T_pfnUniLib_UTF8ToUCS2		pfnUTF8ToUCS2;
	T_pfnUniLib_UCS2ToUTF8		pfnUCS2ToUTF8;
	T_pfnUniLib_SJISStrToUCS2Str	pfnSJISStrToUCS2Str;
	T_pfnUniLib_UCS2StrToSJISStr	pfnUCS2StrToSJISStr;
	T_pfnUniLib_SJISToUCS2		pfnSJISToUCS2;
	T_pfnUniLib_UCS2ToSJIS		pfnUCS2ToSJIS;
	T_pfnUniLib_KutenToUCS2		pfnKutenToUCS2;
	T_pfnUniLib_RIS506StrToUCS2Str	pfnRIS506StrToUCS2Str;
	T_pfnUniLib_UCS2StrToRIS506Str	pfnUCS2StrToRIS506Str;
	T_pfnUniLib_RIS506ToUCS2	pfnRIS506ToUCS2;
	T_pfnUniLib_UCS2ToRIS506	pfnUCS2ToRIS506;
	T_pfnUniLib_EUCJPStrToUCS2Str	pfnEUCJPStrToUCS2Str;
	T_pfnUniLib_EUCJPToUCS2		pfnEUCJPToUCS2;
	T_pfnUniLib_KSCStrToUCS2Str	pfnKSCStrToUCS2Str;
	T_pfnUniLib_UCS2StrToKSCStr	pfnUCS2StrToKSCStr;
	T_pfnUniLib_KSCToUCS2		pfnKSCToUCS2;
	T_pfnUniLib_UCS2ToKSC		pfnUCS2ToKSC;
} TApiGrp_UniLib;



#define		UniLib_Strcpy(p1,p2)			__ApiLink2(UniLib,Strcpy,p1,p2)
#define		UniLib_Strncpy(p1,p2,p3)		__ApiLink3(UniLib,Strncpy,p1,p2,p3)
#define		UniLib_Strcmp(p1,p2)			__ApiLink2(UniLib,Strcmp,p1,p2)
#define		UniLib_Strncmp(p1,p2,p3)		__ApiLink3(UniLib,Strncmp,p1,p2,p3)
#define		UniLib_Strlen(p1)			__ApiLink1(UniLib,Strlen,p1)
#define		UniLib_Strupr(p1)			__ApiLink1(UniLib,Strupr,p1)
#define		UniLib_Strlwr(p1)			__ApiLink1(UniLib,Strlwr,p1)
#define		UniLib_Strset(p1,p2)			__ApiLink2(UniLib,Strset,p1,p2)
#define		UniLib_Strnset(p1,p2,p3)		__ApiLink3(UniLib,Strnset,p1,p2,p3)
#define		UniLib_Strcat(p1,p2)			__ApiLink2(UniLib,Strcat,p1,p2)
#define		UniLib_Strncat(p1,p2,p3)		__ApiLink3(UniLib,Strncat,p1,p2,p3)
#define		UniLib_Vsprintf(p1,p2,p3)		__ApiLink3(UniLib,Vsprintf,p1,p2,p3)
#define		UniLib_Sprintf				__ApiLinkV(UniLib,Sprintf)
#define		UniLib_Strstr(p1,p2)			__ApiLink2(UniLib,Strstr,p1,p2)
#define		UniLib_Strchr(p1,p2)			__ApiLink2(UniLib,Strchr,p1,p2)
#define		UniLib_Strtok(p1,p2)			__ApiLink2(UniLib,Strtok,p1,p2)

#define		UniLib_Atoi(p1)				__ApiLink1(UniLib,Atoi,p1)
#define		UniLib_Atol(p1)				__ApiLink1(UniLib,Atol,p1)
#define		UniLib_Strtod(p1,p2)			__ApiLink2(UniLib,Strtod,p1,p2)
#define		UniLib_Strtol(p1,p2,p3)			__ApiLink3(UniLib,Strtol,p1,p2,p3)
#define		UniLib_Strrchr(p1,p2)			__ApiLink2(UniLib,Strrchr,p1,p2)


#define		UniLib_UTF8ToUCS2(p1,p2)		__ApiLink2(UniLib,UTF8ToUCS2,p1,p2)
#define		UniLib_UCS2ToUTF8(p1,p2)		__ApiLink2(UniLib,UCS2ToUTF8,p1,p2)
#define		UniLib_SJISStrToUCS2Str(p1,p2,p3,p4)	__ApiLink4(UniLib,SJISStrToUCS2Str,p1,p2,p3,p4)
#define		UniLib_UCS2StrToSJISStr(p1,p2,p3,p4)	__ApiLink4(UniLib,UCS2StrToSJISStr,p1,p2,p3,p4)
#define		UniLib_SJISToUCS2(p1)			__ApiLink1(UniLib,SJISToUCS2,p1)
#define		UniLib_UCS2ToSJIS(p1)			__ApiLink1(UniLib,UCS2ToSJIS,p1)
#define		UniLib_KutenToUCS2(p1)			__ApiLink1(UniLib,KutenToUCS2,p1)
#define		UniLib_RIS506StrToUCS2Str(p1,p2,p3,p4)	__ApiLink4(UniLib,RIS506StrToUCS2Str,p1,p2,p3,p4)
#define		UniLib_UCS2StrToRIS506Str(p1,p2,p3,p4)	__ApiLink4(UniLib,UCS2StrToRIS506Str,p1,p2,p3,p4)
#define		UniLib_RIS506ToUCS2(p1)			__ApiLink1(UniLib,RIS506ToUCS2,p1)
#define		UniLib_UCS2ToRIS506(p1)			__ApiLink1(UniLib,UCS2ToRIS506,p1)
#define		UniLib_EUCJPStrToUCS2Str(p1,p2,p3,p4)	__ApiLink4(UniLib,EUCJPStrToUCS2Str,p1,p2,p3,p4)
#define		UniLib_EUCJPToUCS2(p1)			__ApiLink1(UniLib,EUCJPToUCS2,p1)
#define		UniLib_KSCStrToUCS2Str(p1,p2)		__ApiLink2(UniLib,KSCStrToUCS2Str,p1,p2)
#define		UniLib_UCS2StrToKSCStr(p1,p2)		__ApiLink2(UniLib,UCS2StrToKSCStr,p1,p2)
#define		UniLib_KSCToUCS2(p1)			__ApiLink1(UniLib,KSCToUCS2,p1)
#define		UniLib_UCS2ToKSC(p1)			__ApiLink1(UniLib,UCS2ToKSC,p1)

#endif	//	_LGE__UNICODELIB_H_
