/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	API LINK

	Copyright(c) 1997-2003 BNSoft Corp.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT_APILINK_APILINKLIB_H_
#define		_BNSOFT_APILINK_APILINKLIB_H_


#include	"BasicApiLink.h"
#include	"PeanutApiLink.h"

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
	const TApiGrp_ShMem*		        pShMem;
        const void *                            __0x34;
	const TApiGrp_FileSys*		        pFileSys;
	const TApiGrp_RecMngr*		        pRecMngr;
	const TApiGrp_Serial*		        pSerial;
        const void *                            __0x44;
        const TApiGrp_MsgHandler*	        pMsgHandler;
        const void *                            __0x4C;
	const TApiGrp_SysUtil*		        pSysUtil;
        const TApiGrp_SysDev*		        pSysDev;
        const void *                            __0x58;
	const TApiGrp_SysStr*		        pSysStr;
	const TApiGrp_StrUtil*		        pStrUtil;
        const TApiGrp_LnkList*                  pLnkList;
	const TApiGrp_UniLib*		        pUniLib;

        //  BNS_FEATURE_PEANUT
	const TApiGrp_Peanut*		        pPeanut;
	const TApiGrp_AniPaf*		        pAniPaf;	
	const TApiGrp_BaseCtrl*		        pBaseCtrl;
	const TApiGrp_ButCtrl*		        pButCtrl;
	const TApiGrp_ChkCtrl*		        pChkCtrl;
	const TApiGrp_CmbCtrl*		        pCmbCtrl;
	const TApiGrp_ColorTbl*		        pColorTbl;
	const TApiGrp_Dialog*		        pDialog;
	const TApiGrp_DlgCtrl*		        pDlgCtrl;
        const TApiGrp_FrmCtrl*		        pFrmCtrl;
	const TApiGrp_HndlMngr*		        pHndlMngr;
	const TApiGrp_IconCtrl*		        pIconCtrl;
	const TApiGrp_IconList*		        pIconList;
	const TApiGrp_ImgCtrl*		        pImgCtrl;
	const TApiGrp_Indicator*	        pIndicator;
	const TApiGrp_KeypadCtrl*	        pKeypadCtrl;
	const TApiGrp_LineCtrl*		        pLineCtrl;
	const TApiGrp_ListCtrl*		        pListCtrl;
	const TApiGrp_ListView*		        pListView;
	const TApiGrp_PopupCtrl*                pPopupCtrl;
	const void *		                __0xBC; /* тут какая-то одна ф-ия, непонятно от чего она */
	const TApiGrp_RdoCtrl*		        pRdoCtrl;
	const void *		                __0xC4;  // const TApiGrp_REditCtrl*	        pREditCtrl;
	const TApiGrp_SelCtrl*		        pSelCtrl;
        const TApiGrp_TabCtrl*                  pTabCtrl;
	const TApiGrp_TextCtrl*		        pTextCtrl;
	const TApiGrp_SoftMenu*		        pSoftMenu;

	void*					EndOfApiLink;
} TApiLink;


// Task Api

#include	"../Module/TaskApi.h"

#endif	//	_BNSOFT_APILINK_APILINKLIB_H_
