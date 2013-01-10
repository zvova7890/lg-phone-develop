/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	ERROR DEFINITION OF APPLICATION

	Copyright(c) 1997-2002 BNSoft Corp.

	�׷� : BASIC API
	���� : �ü��
	��� : ����																						{{BNS_INTERNALCODE()}}
	���� : 1.00
	���� : 2002.04.09
	���� : �ڻ�ȣ
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT_ERRORAPP_H_
#define		_BNSOFT_ERRORAPP_H_

#include	"ErrorDef.h"

//-------------------------------------------------------------------------------------------------
//	Definition of Application Errors
typedef enum
{
	ERR_APP_FIRST						= ERR_APP,			//	1000
	ERR_APP_INVALID_FILENAME,
	ERR_APP_INVALID_PXEINFO,
	ERR_APP_NO_CODE_AREA,
	ERR_APP_NO_DATA_AREA,
	ERR_APP_EXHAUSTED,
	ERR_APP_EXPIRED,
	ERR_APP_INVALID_APPINFO,
	ERR_APP_LAST
} E_ERR_APP;

//-------------------------------------------------------------------------------------------------

#endif	//	_BNSOFT_ERRORAPP_H_
