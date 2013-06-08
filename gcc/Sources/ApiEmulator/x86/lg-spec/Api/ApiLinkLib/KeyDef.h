/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	KEY DEFINITION

	Copyright(c) 1997-2002 BNSoft Corp.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT_PDK300_KEYDEF_H_
#define		_BNSOFT_PDK300_KEYDEF_H_

//-------------------------------------------------------------------------------------------------
//	Key Definition
typedef enum 
{
	BNS_NONE_K							= 0,
	BNS_0_K,
	BNS_1_K,
	BNS_2_K,
	BNS_3_K,
	BNS_4_K,
	BNS_5_K,
	BNS_6_K,
	BNS_7_K,
	BNS_8_K,
	BNS_9_K,
	BNS_POUND_K,
	BNS_STAR_K,

	BNS_SEND_K,
	BNS_END_K,
	BNS_CLR_K,
	BNS_MENU_K,
	BNS_BACK_K,
	BNS_OPT_K,		
	BNS_SOFT1_K,
	BNS_SOFT2_K,
	BNS_SOFT3_K,

	BNS_ISOFT1_K,
	BNS_ISOFT2_K,
	BNS_ISOFT3_K,
	BNS_ISOFT4_K,
	BNS_ISOFT5_K,

	BNS_UP_K,
	BNS_DOWN_K,
	BNS_LEFT_K,
	BNS_RIGHT_K,
	BNS_CENTER_K,

	BNS_FLIP_OPEN_K,
	BNS_FLIP_CLOSE_K,
	BNS_SIDE1_K,
	BNS_SIDE2_K,
	BNS_SIDE3_K,
	BNS_SIDE4_K,		
	BNS_SIDE5_K,
	BNS_SIDE6_K,
	BNS_SIDE7_K,
	BNS_SIDE8_K,
	BNS_SIDE9_K,
	BNS_SIDE10_K,
	BNS_SIDE11_K,
	BNS_SIDE12_K,

	BNS_HOT1_K,
	BNS_HOT2_K,
	BNS_HOT3_K,	
	BNS_HOT4_K,
	BNS_HOT5_K,
	BNS_HOT6_K,
	BNS_HOT7_K,
	BNS_HOT8_K,
	BNS_HOT9_K,
	BNS_HOT10_K,
	BNS_HOT11_K,
	BNS_HOT12_K,

	BNS_EXT_PWR_ON_K,
	BNS_EXT_PWR_OFF_K,
	BNS_BATT_WARN_K,   

	BNS_REMOTE_K_START,	
	BNS_HOOK_K,
	BNS_PWR_K,	
	BNS_PTT_K,	
	BNS_REW_K,			//KKG  04/12/22 Earjack Rewind Key
	BNS_FW_K,			//KKG  04/12/22 Earjack Forward Key
	BNS_PLAY_K,			//KKG  04/12/22 Earjack Play Key
	BNS_BT_HOOK_K,		//chosw  05/04/21 Bluetooth Headset Key

	/* START : Added by dkmoon 2005-10-09 */ 
	BNS_BT_AV_PLAY_K,
  	BNS_BT_AV_STOP_K,
  	BNS_BT_AV_PAUSE_K,
  	BNS_BT_AV_FORWARD_K,
  	BNS_BT_AV_BACKWARD_K,
  	BNS_BT_AV_FF_K,
  	BNS_BT_AV_RW_K,
  	/* END : Added by dkmoon 2005-10-09 */ 
	
	BNS_STOP_K,			// cihyun 05/12/01 Earjack stop key
	BNS_EAR_VOLUP_K,	// cihyun 05/12/01 Earjack volume up key
	BNS_EAR_VOLDOWN_K,	// cihyun 05/12/01 Earjack volume down key
	BNS_REMOTE_K_END,	// Remote Keyё¦ ±ёєРЗП±в А§ЗШј­ Аыїл cihyun 2006. 01. 19 
	BNS_TV_K,			//	U960їЎј­  back keyґлЅЕ TV key·О ±вґЙ єЇ°ж µК.
	BNS_LOCK_K,
	BNS_AF_K,

	//	QWERTY key
	WISE_K_NONE					= 0x00000000,
	WISE_K_NUM0					= 0x00000001,
	WISE_K_NUM1 					= 0x00000002,
	WISE_K_NUM2 					= 0x00000003,
	WISE_K_NUM3 					= 0x00000004,
	WISE_K_NUM4 					= 0x00000005,
	WISE_K_NUM5 					= 0x00000006,
	WISE_K_NUM6 					= 0x00000007,
	WISE_K_NUM7 					= 0x00000008,
	WISE_K_NUM8 					= 0x00000009,
	WISE_K_NUM9 					= 0x0000000A,
	WISE_K_POUND					= 0x0000000B,
	WISE_K_STAR 					= 0x0000000C,
	WISE_K_SEND						= 0x0000000D,
	WISE_K_END						= 0x0000000E,
	WISE_K_CLR						= 0x0000000F,
	WISE_K_MENU						= 0x00000010,
	WISE_K_BACK						= 0x00000011,
	WISE_K_SOFT1					= 0x00000012,
	WISE_K_SOFT2					= 0x00000013,
	WISE_K_SOFT3					= 0x00000014,
	WISE_K_CENTER					= 0x00000015,
	WISE_K_OPEN						= 0x00000016,
	WISE_K_CLOSE					= 0x00000017,
	//-------------------------------------------------
	WISE_K_SIDE1					= 0x00000020,
	WISE_K_SIDE2					= 0x00000021,
	WISE_K_SIDE3					= 0x00000022,
	WISE_K_SIDE4					= 0x00000023,
	WISE_K_SIDE5					= 0x00000024,
	WISE_K_SIDE6					= 0x00000025,
	WISE_K_SIDE7					= 0x00000026,
	WISE_K_SIDE8					= 0x00000027,
	WISE_K_SIDE9					= 0x00000028,
	WISE_K_SIDE10					= 0x00000029,
	WISE_K_SIDE11					= 0x0000002A,
	WISE_K_SIDE12					= 0x0000002B,
	//-------------------------------------------------
	WISE_K_HOT1					= 0x00000030,
	WISE_K_HOT2					= 0x00000031,
	WISE_K_HOT3					= 0x00000032,
	WISE_K_HOT4					= 0x00000033,
	WISE_K_HOT5					= 0x00000034,
	WISE_K_HOT6					= 0x00000035,
	WISE_K_HOT7					= 0x00000036,
	WISE_K_HOT8					= 0x00000037,
	WISE_K_HOT9					= 0x00000038,
	WISE_K_HOT10					= 0x00000039,
	WISE_K_HOT11					= 0x0000003A,
	WISE_K_HOT12					= 0x0000003B,

	//-------------------------------------------------
	WISE_K_PLAY					= 0x00000040,		
	WISE_K_STOP					= 0x00000041,
	WISE_K_PAUSE					= 0x00000042,
	WISE_K_REC					= 0x00000043,
	WISE_K_FW					= 0x00000044,	//	fast forward
	WISE_K_FF					= 0x00000045,		
	WISE_K_RW					= 0x00000046,	//	reward
	WISE_K_FR					= 0x00000047,	//	fast reward			

	//-------------------------------------------------
	WISE_K_ESC					= 0x00001000,
	WISE_K_0					= 0x00001001,
	WISE_K_1                        = 0x00001002,
	WISE_K_2                        = 0x00001003,
	WISE_K_3                        = 0x00001004,
	WISE_K_4                        = 0x00001005,
	WISE_K_5                        = 0x00001006,
	WISE_K_6                        = 0x00001007,
	WISE_K_7                        = 0x00001008,
	WISE_K_8                        = 0x00001009,
	WISE_K_9                        = 0x0000100A,
	WISE_K_DASH                     = 0x0000100B,
	WISE_K_EQU                      = 0x0000100C,
	WISE_K_BSPACE                   = 0x0000100D,
	WISE_K_TAB                      = 0x0000100E,
	WISE_K_Q                        = 0x0000100F,
	WISE_K_W                        = 0x00001010,
	WISE_K_E                        = 0x00001011,
	WISE_K_R                        = 0x00001012,
	WISE_K_T                        = 0x00001013,
	WISE_K_Y                        = 0x00001014,
	WISE_K_U                        = 0x00001015,
	WISE_K_I                        = 0x00001016,
	WISE_K_O                        = 0x00001017,
	WISE_K_P                        = 0x00001018,
	WISE_K_LBRCK                    = 0x00001019,
	WISE_K_RBRCK                    = 0x0000101A,
	WISE_K_BSLASH                   = 0x0000101B,
	WISE_K_CAPS                     = 0x0000101C,
	WISE_K_A                        = 0x0000101D,
	WISE_K_S                        = 0x0000101E,
	WISE_K_D                        = 0x0000101F,
	WISE_K_F                        = 0x00001020,
	WISE_K_G                        = 0x00001021,
	WISE_K_H                        = 0x00001022,
	WISE_K_J                        = 0x00001023,
	WISE_K_K                        = 0x00001024,
	WISE_K_L                        = 0x00001025,
	WISE_K_COLON                    = 0x00001026,
	WISE_K_QUOTE                    = 0x00001027,
	WISE_K_ENTER                    = 0x00001028,
	WISE_K_SHIFT                    = 0x00001029,
	WISE_K_Z                        = 0x0000102A,
	WISE_K_X                        = 0x0000102B,
	WISE_K_C                        = 0x0000102C,
	WISE_K_V                        = 0x0000102D,
	WISE_K_B                        = 0x0000102E,
	WISE_K_N                        = 0x0000102F,
	WISE_K_M                        = 0x00001030,
	WISE_K_COMMA                    = 0x00001031,
	WISE_K_PERIOD                   = 0x00001032,
	WISE_K_SLASH                    = 0x00001033,
	WISE_K_CTRL                     = 0x00001034,
	WISE_K_ALT                      = 0x00001035,
	WISE_K_FUNC			= 0x00001036,
	WISE_K_SYMBOL                   = 0x00001037,
	WISE_K_ACCENT                   = 0x00001038,
	WISE_K_EMOTIC                   = 0x00001039,
	WISE_K_SPACE                    = 0x0000103A,
	WISE_K_UP                       = 0x0000103B,
	WISE_K_DOWN                     = 0x0000103C,
	WISE_K_LEFT                     = 0x0000103D,
	WISE_K_RIGHT                    = 0x0000103E,
	WISE_K_IME                      = 0x0000103F,
	WISE_K_OPT			= 0x00001040,	
	WISE_K_DOT_COM			= 0x00001041,			
	WISE_K_ADD			= 0x00001042,	
//naveed added for proximity sensor start
#if defined(LGSI_PROXI_SENSOR)
	WISE_K_PROXY			= 0x00001043,	   
#endif
	WISE_K_MAX			= 0x01FFFFFF,
	//---------------------------------------------
} KEY;

#define		IS_BNS_QWERTY_KEY(key)		(((key) & 0x0000FF00) == 0x00001000)

#define		BNS_VOLUP_K				BNS_SIDE1_K
#define		BNS_VOLDOWN_K				BNS_SIDE2_K
#define		BNS_REC_K				BNS_SIDE3_K
#define 	BNS_CAPTURE_K				BNS_SIDE3_K
#define		BNS_POPUP_K				BNS_REC_K
#define		BNS_DVBH_K				BNS_STOP_K	

#define		WISE_NONE_K				BNS_NONE_K

#endif	//	_BNSOFT_PDK300_KEYDEF_H_
