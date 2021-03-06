/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	OEM INDICATOR MANAGER

	Copyright(c) 1997-2003 BNSoft Corp.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT_PEANUT_OEMINDICATOR_H_
#define		_BNSOFT_PEANUT_OEMINDICATOR_H_

#define INDICATORIMG_RSSI_LEVEL					8
#define INDICATORIMG_INTE_LEVEL					3
#define INDICATORIMG_BATT_LEVEL					4
#define	INDICATORIMG_DOWN_LEVEL					3
#define	INDICATORIMG_SEARCH_LEVEL				4
#define	INDICATORIMG_MSGSEND_LEVEL				4
#define	INDICATORIMG_4_LEVEL					4
#define	INDICATORIMG_MUSICDB_LEVEL				8
#define	INDICATORIMG_DATATRANS_LEVEL				4

#define	SET_ANI							2 

typedef struct
{
	T_ID	IndiPosID;
	TRect	IndiPosRect;
	BOOL	bShowItem;
} TIndiPosObj;

enum
{
	INDICATOR_RAN_GSM		= 0,		
	INDICATOR_RAN_GPRS,					
	INDICATOR_RAN_3G,	//INDICATOR_RAN_WCDMA�� ����
	INDICATOR_RAN_HSDPA,
	INDICATOR_RAN_EDGE
};

enum
{
	INDICATOR_SVCMODE_NO	= 0,
	INDICATOR_SVCMODE_LIMIT,
	INDICATOR_SVCMODE_FULL
};

enum
{
	INDICATOR_NOCLOCK	= 0,
	INDICATOR_CLK_12HRS,
	INDICATOR_CLK_24HRS
};

enum
{
	INDICATOR_HSDPA_INACTIVE = 0,
	INDICATOR_HSDPA_ACTIVE,
	INDICATOR_HSDPA_SUSPEND
}; 

enum
{
	INDICATOR_PDP_ST_INACTIVE,
	INDICATOR_PDP_ST_ACTPND,
	INDICATOR_PDP_ST_ACT_1,
	INDICATOR_PDP_ST_ACT_2,
	INDICATOR_PDP_ST_ACT_3
};

enum
{
	INDICATOR_EVENT_NONE	= 0,
	INDICATOR_EVENT_DRAW,
	INDICATOR_EVENT_SETTIMER,
	INDICATOR_EVENT_KILLTIMER
};

enum
{
	INDICATOR_IM_MSN	= 1,
	INDICATOR_IM_SKYPE,
	INDICATOR_IM_AIM,
	INDICATOR_IM_YAHOO,
	
};

enum
{
	INDICATOR_IM_NONE					= 0,
	//	MSN
	INDICATOR_IM_MSN_OFFLINE,
	INDICATOR_IM_MSN_ONLINE,
	INDICATOR_IM_MSN_AWAY,
	INDICATOR_IM_MSN_BUSY,
	INDICATOR_IM_MSN_BERIGHTBACK,
	INDICATOR_IM_MSN_ONPHONE,
	INDICATOR_IM_MSN_OUTTOLAUNCH,
	INDICATOR_IM_MSN_UNREAD_MSG,	
	INDICATOR_IM_NOTIFICATION,
	//	SKYPE
	INDICATOR_IM_SKYPE_OFFLINE,
	INDICATOR_IM_SKYPE_ONLINE,
	INDICATOR_IM_SKYPE_AWAY,
	INDICATOR_IM_SKYPE_NOTAVAILABLE,
	INDICATOR_IM_SKYPE_DONOTDISTURB,
	INDICATOR_IM_SKYPE_ME,
	INDICATOR_IM_SKYPE_INVISIBLE,

	INDICATOR_IM_MAX_STATE,

	INDICATOR_IM_YAHOO_ONLINE,
	INDICATOR_IM_MULTI_LOGIN,
	INDICATOR_IM_AIM_ONLINE,
};


#endif	//	_BNSOFT_PEANUT_OEMINDICATOR_H_
