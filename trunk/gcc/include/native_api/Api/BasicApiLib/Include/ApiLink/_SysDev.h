/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	DYNAMIC LINKING LIBRARY

	Copyright(c) 1997-2003 BNSoft Corp.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT__SYSDEV_H_
#define		_BNSOFT__SYSDEV_H_

#include	"../SysDev.h"

typedef QUAD			(*T_pfnSysDev_GetInfo)        (E_SYSINFO enSysInfo, BOOL* pbError);
typedef QUAD			(*T_pfnSysDev_GetSecretInfo)  (E_SYSINFO enSysInfo, BOOL* pbError);
typedef QUAD			(*T_pfnSysDev_GetValue)       (E_SYSVAL enSysValue);
typedef BOOL			(*T_pfnSysDev_SetValue)       (E_SYSVAL enSysValue, QUAD Value);
typedef void			(*T_pfnSysDev_ResetPhone)     (void);
typedef void			(*T_pfnSysDev_TurnOffPhone)   (void);
typedef void			(*T_pfnSysDev_EnableSleep)    (BOOL bOn);
typedef void			(*T_pfnSysDev_EnableWatchDog) (BOOL bOn);
typedef void			(*T_pfnSysDev_KickDog)        (void);
typedef void			(*T_pfnSysDev_SetBackLight)   (T_ID LcdID, QUAD Color, QUAD Duration);
typedef void			(*T_pfnSysDev_SetVibrator)    (QUAD Level, QUAD Duration);
typedef BOOL			(*T_pfnSysDev_VoiceCall)      (M_CSTR pcszNum, M_CSTR pcszName, BOOL bSecret);
typedef void			(*T_pfnSysDev_EndCall)        (void);
typedef void			(*T_pfnSysDev_AcceptCall)     (void);
typedef void			(*T_pfnSysDev_RejectCall)     (void);
typedef void			(*T_pfnSysDev_SetSysInitLevel) (E_SYSINIT Level);
typedef BOOL			(*T_pfnSysDev_GetDisplayLockFlag)    (void);
typedef	void			(*T_pfnSysDev_SetDisplayLockFlag)    (BOOL bOn);

typedef struct
{
	T_pfnSysDev_GetInfo			pfnGetInfo;
	T_pfnSysDev_GetSecretInfo		pfnGetSecretInfo;
	T_pfnSysDev_GetValue			pfnGetValue;
	T_pfnSysDev_SetValue			pfnSetValue;
	T_pfnSysDev_ResetPhone			pfnResetPhone;
	T_pfnSysDev_TurnOffPhone		pfnTurnOffPhone;
	T_pfnSysDev_EnableSleep			pfnEnableSleep;
	T_pfnSysDev_EnableWatchDog		pfnEnableWatchDog;
	T_pfnSysDev_KickDog			pfnKickDog;
	T_pfnSysDev_SetBackLight		pfnSetBackLight;
	T_pfnSysDev_SetVibrator			pfnSetVibrator;
	T_pfnSysDev_VoiceCall			pfnVoiceCall;
	T_pfnSysDev_EndCall			pfnEndCall;
	T_pfnSysDev_AcceptCall			pfnAcceptCall;
	T_pfnSysDev_RejectCall			pfnRejectCall;
	T_pfnSysDev_SetSysInitLevel		pfnSetSysInitLevel;
	T_pfnSysDev_GetDisplayLockFlag		pfnGetDisplayLockFlag;
	T_pfnSysDev_SetDisplayLockFlag		pfnSetDisplayLockFlag;
} TApiGrp_SysDev;


#define		SysDev_GetInfo(p1,p2)			__ApiLink2(SysDev,GetInfo,p1,p2)
#define		SysDev_GetSecretInfo(p1,p2)		__ApiLink2(SysDev,GetSecretInfo,p1,p2)
#define		SysDev_GetValue(p1)			__ApiLink1(SysDev,GetValue,p1)
#define		SysDev_SetValue(p1,p2)			__ApiLink2(SysDev,SetValue,p1,p2)
#define		SysDev_ResetPhone()			__ApiLink0(SysDev,ResetPhone)
#define		SysDev_TurnOffPhone()			__ApiLink0(SysDev,TurnOffPhone)
#define		SysDev_EnableSleep(p1)			__ApiLink1(SysDev,EnableSleep,p1)
#define		SysDev_EnableWatchDog(p1)		__ApiLink1(SysDev,EnableWatchDog,p1)
#define		SysDev_KickDog()			__ApiLink0(SysDev,KickDog)
#define		SysDev_SetBackLight(p1,p2,p3)		__ApiLink3(SysDev,SetBackLight,p1,p2,p3)
#define		SysDev_SetVibrator(p1,p2)		__ApiLink2(SysDev,SetVibrator,p1,p2)
#define		SysDev_VoiceCall(p1,p2,p3)		__ApiLink3(SysDev,VoiceCall,p1,p2,p3)
#define		SysDev_EndCall()			__ApiLink0(SysDev,EndCall)
#define		SysDev_AcceptCall()			__ApiLink0(SysDev,AcceptCall)
#define		SysDev_RejectCall()			__ApiLink0(SysDev,RejectCall)
#define		SysDev_SetSysInitLevel(p1)		__ApiLink1(SysDev,SetSysInitLevel,p1)
#define		SysDev_GetDisplayLockFlag()			__ApiLink0(SysDev,GetDisplayLockFlag)
#define		SysDev_SetDisplayLockFlag(p1)		__ApiLink1(SysDev,SetDisplayLockFlag,p1)


#endif	//	_BNSOFT__SYSDEV_H_
