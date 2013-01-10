/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	ERROR DEFINITION OF EVENT MODEL

	Copyright(c) 1997-2002 BNSoft Corp.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT_ERRORMH_H_
#define		_BNSOFT_ERRORMH_H_

#include	"ErrorDef.h"

//	Definition of EventModel Errors
typedef enum
{
	ERR_MH_FIRST						= ERR_MSGHANDLER,	//	1600
	ERR_MH_LACK_OF_HANDLE,
	ERR_MH_FULL_MSG_OBJ,
	ERR_MH_FULL_MSGPROC_OBJ,
	ERR_MH_NO_MSGHANDLER,
	ERR_MH_INVALID_PID,
	ERR_MH_INVALID_MSGRUN,
	ERR_MH_INVALID_NEWPROC,
	ERR_MH_NO_ACTMSGPROC,
	ERR_MH_LAST
} E_ERR_MH;


#endif	//	_BNSOFT_ERRORMH_H_
