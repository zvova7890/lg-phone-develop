/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	PEANUT INCLUDE FILE

	Copyright(c) 1997-2003 BNSoft Corp.

	그룹 : PEANUT
	구분 : 개발지원
	등급 : 공개																						{{BNS_INTERNALCODE()}}
	버전 : 1.01
	일자 : 2003.04.08
	성명 : 박상호
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT_PEANUT_INCLUDE_H_
#define		_BNSOFT_PEANUT_INCLUDE_H_

#ifdef		WIN32
#pragma warning(disable : 4100)
#pragma warning(disable : 4115)
#pragma warning(disable : 4127)
#endif

#include	"..\..\BasicApiLib\Include\Include.h"
#include	"..\..\BasicApiLib\BasicApiLib.h"

#include	"..\..\..\PAL\PhonePal\PalDef.h"

#include	"PeanutCust.h"
#include	"PeanutTypeDef.h"
#include	"PeanutCtrlDef.h"
#include	"PeanutErrDef.h"
#include	"PeanutPprDef.h"

#include	"Peanut.h"

//-------------------------------------------------------------------------------------------------
//	PEANUT Version 1.00
#define		PEANUT_VERSION				100
#define		PEANUT_MAJOR_VERSION		1
#define		PEANUT_MINOR_VERSION		0

#define		PEANUT_VERSION_100
//-------------------------------------------------------------------------------------------------

#define		PEANUT_TRACE				SysUtil_WriteLog

#endif	//	_BNSOFT_PEANUT_INCLUDE_H_
