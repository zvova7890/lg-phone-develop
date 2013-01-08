/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	BASIC API LIBRARY

	Copyright(c) 1997-2003 BNSoft Corp.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT_APILINK_BASICAPILIB_H_
#define		_BNSOFT_APILINK_BASICAPILIB_H_

#include	"ApiLinkDef.h"

#define		_INCLUDE_FILE(H)			#H
#define		INCLUDE_FILE(H)				_INCLUDE_FILE(../BasicApiLib/Include/##H)
#define		INCLUDE_CUST(H)				_INCLUDE_FILE(../BasicApiLib/Adapt/##H)


#include	"../BasicApiLib/Include/Include.h"
#include	"../BasicApiLib/Include/TypeDef.h"

#include	"../BasicApiLib/Include/ApiLink/_App.h"

#include	"../BasicApiLib/Include/ApiLink/_EvHandler.h"

#include	"../BasicApiLib/Include/ApiLink/_ProcMngr.h"
#include	"../BasicApiLib/Include/ApiLink/_TimerUtil.h"
#include	"../BasicApiLib/Include/ApiLink/_TimerCore.h"

#include	"../BasicApiLib/Include/ApiLink/_MsgHandler.h"

#include	"../BasicApiLib/Include/ApiLink/_SysDev.h"

#include	"../BasicApiLib/Include/ApiLink/_GrSys.h"
#include	"../BasicApiLib/Include/ApiLink/_GrFont.h"
#include	"../BasicApiLib/Include/ApiLink/_GrImage.h"
#include	"../BasicApiLib/Include/ApiLink/_GrText.h"

#undef		INCLUDE_FILE
#undef		_INCLUDE_FILE

#endif	//	_BNSOFT_APILINK_BASICAPILIB_H_
