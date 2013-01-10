/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	API LINK

	Copyright(c) 1997-2003 BNSoft Corp.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT_APILINK_APILINKLIB_H_
#define		_BNSOFT_APILINK_APILINKLIB_H_


#include	"BasicApiLink.h"
//#include	"PeanutApiLink.h"

typedef struct
{
    //  BASICAPILIB APILINK
        const TApiGrp_App*			pApp;
        const void *                            __0x04;
        const void *                            __0x08;
        const TApiGrp_EvHandler*		pEvHandler;
        const TApiGrp_ProcMngr*		        pProcMngr;
        const TApiGrp_Timer*			pTimer;
        const TApiGrp_TimerCore*		pTimerCore;
        const TApiGrp_GrSys*			pGrSys;
        const TApiGrp_GrFont*			pGrFont;
        const TApiGrp_GrImage*			pGrImage;
        const TApiGrp_GrText*			pGrText;
	const TApiGrp_AppHeap*		        pAppHeap;
        const void *                            __0x30;
        const void *                            __0x34;
	const TApiGrp_FileSys*		        pFileSys;
        const void *                            __0x3C;
	const TApiGrp_Serial*		        pSerial;
        const void *                            __0x44;
        const TApiGrp_MsgHandler*	        pMsgHandler;
        const void *                            __0x4C;
	const TApiGrp_SysUtil*		        pSysUtil;
        const TApiGrp_SysDev*		        pSysDev;
        const void *                            __0x58;
        const void *                            __0x5C;
        const void *                            __0x60;
        const void *                            __0x64;
	const TApiGrp_UniLib*		        pUniLib;
        const void *                            __0x6C;

        //  BNS_FEATURE_PEANUT

        const void *                            __0x70;
        const void *                            __0x74;
        const void *                            __0x78;
        const void *                            __0x7C;
        const void *                            __0x80;
        const void *                            __0x84;
	//const TApiGrp_Dialog*		        pDialog;

	void*					EndOfApiLink;
} TApiLink;



#endif	//	_BNSOFT_APILINK_APILINKLIB_H_
