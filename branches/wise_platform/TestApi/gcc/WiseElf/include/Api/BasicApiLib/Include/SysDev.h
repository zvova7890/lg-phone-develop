/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	SYSTEM DEVICE

	Copyright(c) 1997-2002 BNSoft Corp.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT_SYSDEV_H_
#define		_BNSOFT_SYSDEV_H_

#include	"Include.h"

//	Type of System Information
typedef enum
{
	SYSINFO_FIRST_ITEM					= 0,

	//	Secret Info
	SYSINFO_ESN_NUMBER,					

	//	Normal Info
	SYSINFO_COMPANY_NAME,						
	SYSINFO_MODEL_NAME,						
	SYSINFO_MODEL_ID,					
	SYSINFO_MODEL_VERSION,				
	SYSINFO_API_VERSION,					
	SYSINFO_API_MAJOR_VER,			
	SYSINFO_API_MINOR_VER,									
	SYSINFO_PHONE_NUMBER_NUM,								
	SYSINFO_PHONE_NUMBER,									
	SYSINFO_PHONE_NUMBER_1,								
	SYSINFO_PHONE_NUMBER_2,								
	SYSINFO_PHONE_NUMBER_3,									
	SYSINFO_USER_NAME,										
	SYSINFO_DISPLAY_NUM,									
	SYSINFO_LED_NUM,										
	SYSINFO_SERIAL_NUM,										
	SYSINFO_SNDDEV_NUM,										
	SYSINFO_VOCDEV_NUM,										
	SYSINFO_MAX_RSSI_LEVEL,									
	SYSINFO_MAX_BATT_LEVEL,									
	SYSINFO_SYSINIT_LEVEL,									
	SYSINFO_LAST_ITEM
} E_SYSINFO;

//	Type of System Value
typedef enum
{
	SYSVAL_FIRST_ITEM					= 0,
	SYSVAL_RSSI_LEVEL,										
	SYSVAL_BATT_LEVEL,										
	SYSVAL_LED_0,											
	SYSVAL_LED_1,											
	SYSVAL_LED_2,											
	SYSVAL_LED_3,											
	SYSVAL_SNDDEV_0,										
	SYSVAL_SNDDEV_1,										
	SYSVAL_SNDDEV_2,										
	SYSVAL_SNDDEV_3,										
	SYSVAL_VOCDEV_0,										
	SYSVAL_VOCDEV_1,										
	SYSVAL_VOCDEV_2,										
	SYSVAL_VOCDEV_3,										
	SYSVAL_TONE_VOLUME,										
	SYSVAL_TONE_VOLUME_MIN,									
	SYSVAL_TONE_VOLUME_MAX,									
	SYSVAL_SND_VOLUME,								
	SYSVAL_SND_VOLUME_MIN,								
	SYSVAL_SND_VOLUME_MAX,							
	SYSVAL_REC_VOLUME,							
	SYSVAL_REC_VOLUME_MIN,							
	SYSVAL_REC_VOLUME_MAX,									
	SYSVAL_LAST_ITEM
} E_SYSVAL;

typedef	enum
{
	SYSINIT_LEVEL_0			= 0,
	SYSINIT_LEVEL_1,				// Setup
	SYSINIT_LEVEL_2,				// PowerOff Charging
	SYSINIT_LEVEL_3,				// PowerOff Alarm
	SYSINIT_LEVEL_4,				// Pin Input
	SYSINIT_LEVEL_5,				// PowerOn Animation
	SYSINIT_LEVEL_6, 				// Idle State
	SYSINIT_LEVEL_7,				// Power Off
	SYSINIT_LEVEL_8,
	SYSINIT_LAST_ITEM
} E_SYSINIT;



extern QUAD	SysDev_GetInfo        (E_SYSINFO enSysInfo, BOOL* pbError);
extern QUAD	SysDev_GetSecretInfo  (E_SYSINFO enSysInfo, BOOL* pbError);
extern QUAD	SysDev_GetValue       (E_SYSVAL enSysValue);
extern BOOL	SysDev_SetValue       (E_SYSVAL enSysValue, QUAD Value);

extern void	SysDev_ResetPhone     (void);
extern void	SysDev_TurnOffPhone   (void);
extern void	SysDev_EnableSleep    (BOOL bOn);
extern void	SysDev_EnableWatchDog (BOOL bOn);
extern void	SysDev_KickDog        (void);

extern void	SysDev_SetBackLight   (T_ID LcdID, QUAD Color, QUAD Duration);
extern void	SysDev_SetVibrator    (QUAD Level, QUAD Duration);
extern BOOL	SysDev_VoiceCall      (M_CSTR pcszNum, M_CSTR pcszName, BOOL bSecret);
extern void	SysDev_EndCall        (void);
extern void	SysDev_AcceptCall     (void);
extern void	SysDev_RejectCall     (void);
extern void	SysDev_SetSysInitLevel(E_SYSINIT enLevel);
extern BOOL	SysDev_GetDisplayLockFlag(void);
extern void	SysDev_SetDisplayLockFlag(BOOL bOn);


#endif	//	_BNSOFT_SYSDEV_H_
