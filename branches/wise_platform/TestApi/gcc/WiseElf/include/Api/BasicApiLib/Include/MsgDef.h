/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	MESSAGE DEFINITION

	Copyright(c) 1997-2002 BNSoft Corp.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT_MSGDEF_H_
#define		_BNSOFT_MSGDEF_H_


//	Application Message Type
typedef enum
{
	MSG_NONE							= 0,
	
	MSG_INIT,
	MSG_EXIT,
	MSG_AWAKE,
	MSG_SLEEP,
	
	MSG_KEYDOWN,
	MSG_KEYUP,
	MSG_CHAR,
	MSG_LONGKEY,
	MSG_REPEATKEY,
	
	MSG_DRAW,
	MSG_TIMER,
	MSG_POINTING,
	MSG_INDICATOR,			//@20031111
	MSG_NETWORK,			//added by ellio 2003.02.26
	MSG_SOCKET,
	MSG_SERIAL,
	MSG_EXPIRE,				//Added by SURESH for handling expired PUSH message. 17th dec 2003
	MSG_RESUME,
	MSG_NM,					// Lee Chang Hwan(Lipi Lee) June 1, 2005
	MSG_MUVEE,				//added by muvee, 20100316
	MSG_FOR_FLAG,			//added by Song Ki uk, to use FOR_FLAG value from Enginerring mode
	MSG_MMS_CANCEL,			// mjkang 2004-10-01
	MSG_MMS_AWAKE,			// mjkang 2004-10-01
	MSG_MMS_NOTI,			// mjkang 2004-10-01
	MSG_MMS_READ_REPLY,		// mjkang 2005-09-20
	MSG_COMMAND,
	MSG_PS_DEFAULT,			//syang 2005-12-9
	MSG_PS_ALL_LOCK,		//KMJ 2005-12-21

	MSG_SYSTEM = 1000,

	MSG_PSDATA	= 1700,		// modified by momo 2005.4.17
	MSG_CSDATA,				// added by momo 2005.4.17
	MSG_DATACOM_PDPC,
#ifdef LGE_FEATURE_PHONE_INSPECTOR
	MSG_PHONEINSPECTOR,		//added by Led2571 2007-12-09					
#endif	
	MSG_LAUNCH,				//added by susu for AMC
	MSG_SETVALUE,
	MSG_GETVARS,
	MSG_SETVARS,
	MSG_USERDEFINE = 30000

} E_MSG;
//-------------------------------------------------------------------------------------------------

//#include	"..\..\..\Pal\PhonePal\Include\PalMsgDef.h"

#endif	//	_BNSOFT_MSGDEF_H_
