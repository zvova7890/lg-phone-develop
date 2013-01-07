/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	BASIC API LIBRARY HEADER FILES

	Copyright(c) 1997-2002 BNSoft Corp.

	그룹 : BASIC API
	구분 : 개발지원
	등급 : 공개																						{{BNS_INTERNALCODE()}}
	버전 : 1.01
	일자 : 2002.12.15
	성명 : 박상호
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT_BASICAPILIB_H_
#define		_BNSOFT_BASICAPILIB_H_

#include	"Include\BasicApi.h"

#include	"Include\LnkList.h"
#include	"Include\App.h"
#include	"Include\Dll.h"
#include	"Include\EvHandler.h"
#include	"Include\ProcMngr.h"
#include	"Include\TimerUtil.h"
#include	"Include\TimerCore.h"
#include	"Include\GrSys.h"
#include	"Include\GrFont.h"
#include	"Include\GrImage.h"
#include	"Include\GrText.h"
#include	"Include\AppHeap.h"
#include	"Include\HeapCore.h"
#if defined	(WISE_FEATURE_RECMNGR_SUPPORT)		// 20101020 flora.shin@lge.com for DeFeaturing : RecMngr Feature 사용 
#include	"Include\SysDB.h"
#endif
#include	"Include\SysHeap.h"
#include	"include\ShMem.h"
//#include	"Include\Drive.h"
#include	"Include\FileSys.h"
#include	"Include\MemDev.h"
#if defined	(WISE_FEATURE_RECMNGR_SUPPORT)		// 20101020 flora.shin@lge.com for DeFeaturing : RecMngr Feature 사용 
#include	"Include\RecMngr.h"
#endif

// 20101020 flora.shin@lge.com for DeFeaturing
#if WISE_FEATURE_BASICOLDFEATURE == 1
#include	"Include\Serial.h"
#endif
#include	"Include\NvDB.h"
// 20101020 flora.shin@lge.com for DeFeaturing
#if WISE_FEATURE_BASICOLDFEATURE == 1
#include	"Include\MediaDev.h"
#endif
#include	"Include\MsgHandler.h"
#include	"Include\SysUtil.h"
#include	"Include\SysDev.h"
#include	"Include\SysStr.h"
#include	"Include\StrUtil.h"
#include	"Include\UnicodeLib.h"
#ifdef  LGE_FEATURE_POWERAPI_SG
#include	"Include\PowerApiLib.h"
#endif
// 20070511 WISE 1.1.1 begin - MTM 통합
#if defined(LGE_FEATURE_MTM)
#include	"Include\DrunLib.h"
#endif
// 20070511 WISE 1.1.1 end
// [LGE_DUTI_S]
#if defined(FEATURE_LGE_DUTI)
#include	"Include\DUTIPorting.h"
#endif	/* FEATURE_LGE_DUTI */
// [LGE_DUTI_E]

// 20101020 flora.shin@lge.com for DeFeaturing [START]
#include "Cache\Include\CacheMngr.h"
#include "Cache\Include\CacheCore.h"
#include "Cache\Include\CacheMru.h"
#include "Cache\Include\CacheMem.h"
// 20101020 flora.shin@lge.com for DeFeaturing [END]
#endif	//	_BNSOFT_BASICAPILIB_H_
