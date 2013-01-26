/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	DYNAMIC LINKING LIBRARY

	Copyright(c) 1997-2003 BNSoft Corp.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT__SYSSTR_H_
#define		_BNSOFT__SYSSTR_H_

#include	"..\SysStr.h"

typedef void			(*T_pfnSysStr_SetCharSet)   (E_CHARSET enCharSet);
typedef E_CHARSET		(*T_pfnSysStr_GetCharSet)   (void);
typedef BOOL			(*T_pfnSysStr_IsUniCode)    (void);
typedef TMLStr*			(*T_pfnSysStr_GetOemStrTbl) (void);
typedef T_SIZE			(*T_pfnSysStr_SizeOf)       (TMLStr* pMLStr);
typedef BOOL			(*T_pfnSysStr_CopyStr)      (void* pDstMem, TMLStr* pMLStr);
typedef T_CSTR			(*T_pfnSysStr_GetStr)       (TMLStr* pMLStr);
typedef void			(*T_pfnSysStr_SetFontStyle) (E_FONTSTYLE enFontStyle);
typedef E_FONTSTYLE		(*T_pfnSysStr_GetFontStyle) (void);

typedef struct
{
	T_pfnSysStr_SetCharSet				pfnSetCharSet;
	T_pfnSysStr_GetCharSet				pfnGetCharSet;
	T_pfnSysStr_IsUniCode				pfnIsUniCode;
	T_pfnSysStr_GetOemStrTbl			pfnGetOemStrTbl;
	T_pfnSysStr_SizeOf				pfnSizeOf;
	T_pfnSysStr_CopyStr				pfnCopyStr;
	T_pfnSysStr_GetStr				pfnGetStr;
	T_pfnSysStr_SetFontStyle			pfnSetFontStyle;
	T_pfnSysStr_GetFontStyle			pfnGetFontStyle;
} TApiGrp_SysStr;


#define	SysStr_SetCharSet(p1)				__ApiLink1(SysStr,SetCharSet,p1)
#define	SysStr_GetCharSet()				__ApiLink0(SysStr,GetCharSet)
#define	SysStr_IsUniCode()				__ApiLink0(SysStr,IsUniCode)
#define	SysStr_GetOemStrTbl()				__ApiLink0(SysStr,GetOemStrTbl)
#define	SysStr_SizeOf(p1)				__ApiLink1(SysStr,SizeOf,p1)
#define	SysStr_CopyStr(p1,p2)				__ApiLink2(SysStr,CopyStr,p1,p2)
#define	SysStr_GetStr(p1)				__ApiLink1(SysStr,GetStr,p1)
#define	SysStr_SetFontStyle(p1)				__ApiLink1(SysStr,SetFontStyle,p1)
#define	SysStr_GetFontStyle()				__ApiLink0(SysStr,GetFontStyle)


#endif	//	_BNSOFT__SYSSTR_H_
