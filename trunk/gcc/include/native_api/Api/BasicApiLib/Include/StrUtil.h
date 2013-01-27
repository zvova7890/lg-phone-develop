/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	STRING UTILITY

	Copyright(c) 1997-2002 BNSoft Corp.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT_STRUTIL_H_
#define		_BNSOFT_STRUTIL_H_

#include	"Include.h"


extern int	StrUtil_LowerCompare  (T_CSTR pszStr1, T_CSTR pszStr2);
extern int	StrUtil_LowerNCompare (T_CSTR pszStr1, T_CSTR pszStr2, T_SIZE Count);
extern void	StrUtil_MakeLower     (T_STR pszStr);
extern void	StrUtil_MakeUpper     (T_STR pszStr);
extern int	StrUtil_Find          (T_CSTR pszStr, T_CSTR pszFind);
extern int	StrUtil_FindFromEnd   (T_CSTR pszStr, T_CSTR pszFind);
extern BOOL	StrUtil_FromQuad      (T_STR pszStr, QUAD Value, BOOL bComma, T_SIZE BufSize);
extern BOOL	StrUtil_FromLong      (T_STR pszStr, long Value, BOOL bComma, T_SIZE BufSize);


extern M_CODE	StrUtil_Unicode2Mbcs  (U_CHAR uCode);
extern T_NUM	StrUtil_GetUnicodeLen (const U_CHAR* pcszuCode);
	

#endif	//	_BNSOFT_STRUTIL_H_
