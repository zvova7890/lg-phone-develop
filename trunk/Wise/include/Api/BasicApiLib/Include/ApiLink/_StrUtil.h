/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	DYNAMIC LINKING LIBRARY

	Copyright(c) 1997-2002 BNSoft Corp.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT__STRUTIL_H_
#define		_BNSOFT__STRUTIL_H_

#include	"..\StrUtil.h"

typedef int			(*T_pfnStrUtil_LowerCompare)  (T_CSTR pszStr1, T_CSTR pszStr2);
typedef int			(*T_pfnStrUtil_LowerNCompare) (T_CSTR pszStr1, T_CSTR pszStr2, T_SIZE Count);
typedef void			(*T_pfnStrUtil_MakeLower)     (T_STR pszStr);
typedef void			(*T_pfnStrUtil_MakeUpper)     (T_STR pszStr);
typedef int			(*T_pfnStrUtil_Find)          (T_CSTR pszStr, T_CSTR pszFind);
typedef int			(*T_pfnStrUtil_FindFromEnd)   (T_CSTR pszStr, T_CSTR pszFind);
typedef BOOL			(*T_pfnStrUtil_FromQuad)      (T_STR pszStr, QUAD Value, BOOL bComma, T_SIZE BufSize);
typedef BOOL			(*T_pfnStrUtil_FromLong)      (T_STR pszStr, long Value, BOOL bComma, T_SIZE BufSize);
typedef M_CODE			(*T_pfnStrUtil_Unicode2Mbcs)  (U_CHAR uCode);
typedef T_NUM			(*T_pfnStrUtil_GetUnicodeLen) (const U_CHAR* pcszuCode);

typedef struct
{
	T_pfnStrUtil_LowerCompare			pfnLowerCompare;
	T_pfnStrUtil_LowerNCompare			pfnLowerNCompare;
	T_pfnStrUtil_MakeLower				pfnMakeLower;
	T_pfnStrUtil_MakeUpper				pfnMakeUpper;
	T_pfnStrUtil_Find				pfnFind;
	T_pfnStrUtil_FindFromEnd			pfnFindFromEnd;
	T_pfnStrUtil_FromQuad				pfnFromQuad;
	T_pfnStrUtil_FromLong				pfnFromLong;
	T_pfnStrUtil_Unicode2Mbcs			pfnUnicode2Mbcs;
	T_pfnStrUtil_GetUnicodeLen			pfnGetUnicodeLen;
} TApiGrp_StrUtil;


#define		StrUtil_LowerCompare(p1,p2)		__ApiLink2(StrUtil,LowerCompare,p1,p2)
#define		StrUtil_LowerNCompare(p1,p2,p3)		__ApiLink3(StrUtil,LowerNCompare,p1,p2,p3)
#define		StrUtil_MakeLower(p1)			__ApiLink1(StrUtil,MakeLower,p1)
#define		StrUtil_MakeUpper(p1)			__ApiLink1(StrUtil,MakeUpper,p1)
#define		StrUtil_Find(p1,p2)			__ApiLink2(StrUtil,Find,p1,p2)
#define		StrUtil_FindFromEnd(p1,p2)		__ApiLink2(StrUtil,FindFromEnd,p1,p2)
#define		StrUtil_FromQuad(p1,p2,p3,p4)		__ApiLink4(StrUtil,FromQuad,p1,p2,p3,p4)
#define		StrUtil_FromLong(p1,p2,p3,p4)		__ApiLink4(StrUtil,FromLong,p1,p2,p3,p4)
#define		StrUtil_Unicode2Mbcs(p1)		__ApiLink1(StrUtil,Unicode2Mbcs,p1)
#define		StrUtil_GetUnicodeLen(p1)		__ApiLink1(StrUtil,GetUnicodeLen,p1)

#endif	//	_BNSOFT__STRUTIL_H_
