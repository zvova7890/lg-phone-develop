/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	BASIC API LIBRARY

	Copyright(c) 1997-2003 BNSoft Corp.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT_APILINK_BASICAPILIB_H_
#define		_BNSOFT_APILINK_BASICAPILIB_H_

#include	"ApiLinkDef.h"

#define		_INCLUDE_FILE(H)			#H
#define		INCLUDE_FILE(H)				_INCLUDE_FILE(..\\BasicApiLib\\Include\\##H)
#define		INCLUDE_CUST(H)				_INCLUDE_FILE(..\\BasicApiLib\\Adapt\\##H)


#include	INCLUDE_FILE(Include.h)
#include	INCLUDE_FILE(TypeDef.h)

#include	INCLUDE_FILE(ApiLink\_App.h)

#include	INCLUDE_FILE(ApiLink\_EvHandler.h)

#include	INCLUDE_FILE(ApiLink\_ProcMngr.h)
#include	INCLUDE_FILE(ApiLink\_TimerUtil.h)
#include	INCLUDE_FILE(ApiLink\_TimerCore.h)

#include	INCLUDE_FILE(ApiLink\_MsgHandler.h)

#undef		INCLUDE_FILE
#undef		_INCLUDE_FILE

#endif	//	_BNSOFT_APILINK_BASICAPILIB_H_
