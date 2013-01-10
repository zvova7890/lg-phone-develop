/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	ERROR DEFINITION

	Copyright(c) 1997-2002 BNSoft Corp.

	그룹 : BASIC API
	구분 : 개발지원
	등급 : 공개																						{{BNS_INTERNALCODE()}}
	버전 : 1.00
	일자 : 2002.03.18
	성명 : 박상호
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT_ERRORDEF_H_
#define		_BNSOFT_ERRORDEF_H_

//-------------------------------------------------------------------------------------------------
//	Definition of Error Group
#define		ERR_NONE					0
#define		ERR_GENERAL					100
#define		ERR_SERIOUS					200

#define		ERR_APP						1000
#define		ERR_DLL						1100
#define		ERR_EVENTMODEL				1200
#define		ERR_GRAPHIC					1300
#define		ERR_MEMORY					1400
#define		ERR_FILESYS					1500
#define		ERR_MSGHANDLER				1600
#define		ERR_SERIAL					1700
#define		ERR_NETWORK					1800
#define		ERR_SOCKET					1900
#define		ERR_MDA						2000

//-------------------------------------------------------------------------------------------------
//	Definition of General Error
typedef enum
{
	ERR_LOW_LEVEL						= ERR_GENERAL,		//	100
	ERR_MISADAPT,
	ERR_INVALID_HANDLE,
	ERR_INVALID_PARAM,
	ERR_LACK_OF_SPACE
} E_ERR;

//-------------------------------------------------------------------------------------------------
//	Definition of Fatal Error
typedef enum
{
	ERRFATAL_LONG_STRING				= ERR_SERIOUS		//	200
} E_ERRFATAL;

//-------------------------------------------------------------------------------------------------

#endif	//	_BNSOFT_ERRORDEF_H_
//-------------------------------------------------------------------------------------------------
