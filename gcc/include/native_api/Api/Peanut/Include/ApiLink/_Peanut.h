/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	PEANUT LIBRARY APILINK

	Copyright(c) 1997-2003 BNSoft Corp.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT__PEANUT_H_
#define		_BNSOFT__PEANUT_H_

#include	"../Peanut.h"

typedef BOOL			(*T_pfnPeanut_SetEnvValue)	(QUAD Key, QUAD Value);
typedef QUAD			(*T_pfnPeanut_GetEnvValue)	(QUAD Key);
typedef BOOL			(*T_pfnPeanut_SetConfigData)	(int ID, E_RESTYPE Type, void* pData);
typedef void*			(*T_pfnPeanut_GetConfigData)	(int ID, E_RESTYPE Type);
typedef BOOL			(*T_pfnPeanut_SetConfigValue)	(int ID, E_RESTYPE Type, int Item, T_PARAM PARAM);
typedef QUAD			(*T_pfnPeanut_GetConfigValue)	(int ID, E_RESTYPE Type, int Item);
typedef BOOL			(*T_pfnPeanut_GetInterface)	(QUAD* pInfo);
typedef BOOL			(*T_pfnPeanut_SetTip)		(TRect* Rect, T_POS X, T_POS Y, T_CSTR pcszStr);

typedef struct
{
	T_pfnPeanut_SetEnvValue				pfnSetEnvValue;
	T_pfnPeanut_GetEnvValue				pfnGetEnvValue;
	T_pfnPeanut_SetConfigData			pfnSetConfigData;
	T_pfnPeanut_GetConfigData			pfnGetConfigData;
	T_pfnPeanut_SetConfigValue			pfnSetConfigValue;
	T_pfnPeanut_GetConfigValue			pfnGetConfigValue;
	T_pfnPeanut_GetInterface			pfnGetInterface;
	T_pfnPeanut_SetTip				pfnSetTip;
} TApiGrp_Peanut;

#define		Peanut_SetEnvValue(p1,p2)		__ApiLink2(Peanut,SetEnvValue,p1,p2)
#define		Peanut_GetEnvValue(p1)			__ApiLink1(Peanut,GetEnvValue,p1)
#define		Peanut_SetConfigData(p1,p2,p3)		__ApiLink3(Peanut,SetConfigData,p1,p2,p3)
#define		Peanut_GetConfigData(p1,p2)		__ApiLink2(Peanut,GetConfigData,p1,p2)
#define		Peanut_SetConfigValue(p1,p2,p3,p4)	__ApiLink4(Peanut,SetConfigValue,p1,p2,p3,p4)
#define		Peanut_GetConfigValue(p1,p2,p3)		__ApiLink3(Peanut,GetConfigValue,p1,p2,p3)
#define		Peanut_GetInterface(p1)			__ApiLink1(Peanut,GetInterface,p1)
#define		Peanut_SetTip(p1,p2,p3,p4)		__ApiLink4(Peanut,SetTip,p1,p2,p3,p4)

#endif	//	_BNSOFT__PEANUT_H_
