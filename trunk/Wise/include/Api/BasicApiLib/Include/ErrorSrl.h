/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	ERROR DEFINITION OF SERIAL COMMUNICATION

	Copyright(c) 1997-2002 BNSoft Corp.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT_ERRORSRL_H_
#define		_BNSOFT_ERRORSRL_H_

#include	"ErrorDef.h"

//	Definition of Application Errors
typedef enum
{
	ERR_SERIAL_FIRST			= ERR_SERIAL,		//	1700
	ERR_SERIAL_INVALID_COMPORT,
	ERR_SERIAL_ALREADY_OPENED,
	ERR_SERIAL_LOWER_LEVEL,
	ERR_SERIAL_LAST
} E_ERR_SERIAL;


#endif	//	_BNSOFT_ERRORSRL_H_
