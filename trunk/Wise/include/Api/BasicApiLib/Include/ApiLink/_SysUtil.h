/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	DYNAMIC LINKING LIBRARY

	Copyright(c) 1997-2002 BNSoft Corp.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT__SYSUTIL_H_
#define		_BNSOFT__SYSUTIL_H_

#include	"../SysUtil.h"

//-------------------------------------------------------------------------------------------------
typedef void			(*T_pfnSysUtil_SetSeed)           (int nSeed);
typedef int			(*T_pfnSysUtil_GetRandom)         (int nRange);
typedef QUAD			(*T_pfnSysUtil_GetTickCount)      (void);
typedef void			(*T_pfnSysUtil_GetLocalTime)      (TLocalTime* pLocalTime);
typedef void			(*T_pfnSysUtil_GetTime)           (int* pHour, int* pMinute, int* pSecond);
typedef void			(*T_pfnSysUtil_GetDate)           (int* pYear, int* pMonth, int* pDay, int* pDayOfWeek);
typedef int			(*T_pfnSysUtil_GetDayOfWeek)      (int Year, int Month, int Day);
typedef int			(*T_pfnSysUtil_GetDaySum)         (int Year, int Month, int Day);
typedef void			(*T_pfnSysUtil_GetDateFromDaySum) (int Sum, int* pYear, int* pMonth, int* pDay);
typedef void			(*T_pfnSysUtil_SetLastError)      (int nError);
typedef int			(*T_pfnSysUtil_GetLastError)      (void);
typedef void			(*T_pfnSysUtil_SetAppDebugEnable) (BOOL bEnable);
typedef BOOL			(*T_pfnSysUtil_GetAppDebugEnable)    ();
typedef void			(*T_pfnSysUtil_Fatal)				(int nLineNo, const char* pszFileName , M_CHAR* msg);
typedef int			(*T_pfnSysUtil_DebugTraceAppHigh)		(M_CHAR* format, ...);
typedef int			(*T_pfnSysUtil_DebugTraceAppMid)		(M_CHAR* format, ...);
typedef int			(*T_pfnSysUtil_DebugTraceAppLow)		(M_CHAR* format, ...);
typedef int			(*T_pfnSysUtil_DebugTraceAppEx)		(unsigned long AppCode, int nLevel, int nLineNo, const char* pszFileName, M_CHAR* foramt, ...);
typedef void*			(*T_pfnSysUtil_OemMalloc)          (T_NUM nSize);
typedef void			(*T_pfnSysUtil_OemFree)            (void* pPtr);
typedef void*			(*T_pfnSysUtil_OemReAlloc)        (void * pBuff, T_NUM nSize);

typedef QUAD			(*T_pfnSysUtil_OemGetFreeSize)	 (QUAD * pdwTotal, QUAD * pdwMax);

typedef void*			(*T_pfnSysUtil_GetBrwHeap)      (void);
typedef QUAD			(*T_pfnSysUtil_GetBrwHeapSize)      (void);
typedef	E_CLIPBOARD		(*T_pfnSysUtil_GetClipboardFormat)	(void);
typedef	void*			(*T_pfnSysUtil_GetClipboardData)	(E_CLIPBOARD Format);
typedef	BOOL			(*T_pfnSysUtil_SetClipboardData)	(E_CLIPBOARD Format, void* pData);




typedef struct
{
	T_pfnSysUtil_SetSeed			pfnSetSeed;
	T_pfnSysUtil_GetRandom			pfnGetRandom;
	T_pfnSysUtil_GetTickCount		pfnGetTickCount;
	T_pfnSysUtil_GetLocalTime       	pfnGetLocalTime;
	T_pfnSysUtil_GetTime			pfnGetTime;
	T_pfnSysUtil_GetDate			pfnGetDate;
	T_pfnSysUtil_GetDayOfWeek		pfnGetDayOfWeek;
	T_pfnSysUtil_GetDaySum			pfnGetDaySum;
	T_pfnSysUtil_GetDateFromDaySum		pfnGetDateFromDaySum;
	T_pfnSysUtil_SetLastError		pfnSetLastError;
	T_pfnSysUtil_GetLastError		pfnGetLastError;
	T_pfnSysUtil_SetAppDebugEnable		pfnSetAppDebugEnable;
	T_pfnSysUtil_GetAppDebugEnable		pfnGetAppDebugEnable;

        int                                     __0x34;

	T_pfnSysUtil_Fatal			pfnFatal;

	T_pfnSysUtil_DebugTraceAppHigh		pfnDebugTraceAppHigh;
	T_pfnSysUtil_DebugTraceAppMid		pfnDebugTraceAppMid;
	T_pfnSysUtil_DebugTraceAppLow		pfnDebugTraceAppLow;
	T_pfnSysUtil_DebugTraceAppEx		pfnDebugTraceAppEx;
	T_pfnSysUtil_OemMalloc			pfnOemMalloc;
	T_pfnSysUtil_OemFree			pfnOemFree;
	T_pfnSysUtil_OemReAlloc			pfnOemReAlloc;
	T_pfnSysUtil_OemGetFreeSize		pfnOemGetFreeSize;

        int                                     __0x5C;
        int                                     __0x60;
        int                                     __0x64;
        int                                     __0x68;
        int                                     __0x6C;
        int                                     __0x70;
        int                                     __0x74;
        int                                     __0x78;

	T_pfnSysUtil_GetBrwHeap			pfnGetBrwHeap;
	T_pfnSysUtil_GetBrwHeapSize		pfnGetBrwHeapSize;
	T_pfnSysUtil_GetClipboardFormat		pfnGetClipboardFormat;
	T_pfnSysUtil_GetClipboardData		pfnGetClipboardData;
	T_pfnSysUtil_SetClipboardData		pfnSetClipboardData;

} TApiGrp_SysUtil;


#define		SysUtil_SetSeed(p1)			__ApiLink1(SysUtil,SetSeed,p1)
#define		SysUtil_GetRandom(p1)			__ApiLink1(SysUtil,GetRandom,p1)
#define		SysUtil_GetTickCount()			__ApiLink0(SysUtil,GetTickCount)
#define		SysUtil_SetLocalTime()			__ApiLink0(SysUtil,SetLocalTime)
#define		SysUtil_GetLocalTime(p1)		__ApiLink1(SysUtil,GetLocalTime,p1)
#define		SysUtil_GetTime(p1,p2,p3)		__ApiLink3(SysUtil,GetTime,p1,p2,p3)
#define		SysUtil_GetDate(p1,p2,p3,p4)		__ApiLink4(SysUtil,GetDate,p1,p2,p3,p4)
#define		SysUtil_GetDayOfWeek(p1,p2,p3)		__ApiLink3(SysUtil,GetDayOfWeek,p1,p2,p3)
#define		SysUtil_GetDaySum(p1,p2,p3)		__ApiLink3(SysUtil,GetDaySum,p1,p2,p3)
#define		SysUtil_GetDateFromDaySum(p1,p2,p3,p4)	__ApiLink4(SysUtil,GetDateFromDaySum,p1,p2,p3,p4)
#define		SysUtil_SetLastError(p1)		__ApiLink1(SysUtil,SetLastError,p1)
#define		SysUtil_GetLastError()			__ApiLink0(SysUtil,GetLastError)
#define		SysUtil_SetAppDebugEnable(p1)		__ApiLink1(SysUtil,SetAppDebugEnable,p1)
#define		SysUtil_GetAppDebugEnable()		__ApiLink0(SysUtil,GetAppDebugEnable)
#define		SysUtil_Fatal(p1,p2,p3)			__ApiLink3(SysUtil,Fatal,p1,p2,p3)
#define		SysUtil_Assert(p1,p2,p3)		__ApiLink3(SysUtil,Assert,p1,p2,p3)
#define		SysUtil_DebugTraceAppHigh		__ApiLinkV(SysUtil,DebugTraceAppHigh)
#define		SysUtil_DebugTraceAppMid		__ApiLinkV(SysUtil,DebugTraceAppMid)
#define		SysUtil_DebugTraceAppLow		__ApiLinkV(SysUtil,DebugTraceAppLow)
#define		SysUtil_DebugTraceAppEx			__ApiLinkV(SysUtil,DebugTraceAppEx)

#define		SysUtil_OemMalloc(p1)			__ApiLink1(SysUtil,OemMalloc,p1)
#define		SysUtil_OemReAlloc(p1, p2)		__ApiLink2(SysUtil,OemReAlloc,p1,p2)

#define		SysUtil_OemFree(p1)			__ApiLink1(SysUtil,OemFree,p1)

#define		SysUtil_OemGetFreeSize(p1, p2)		__ApiLink2(SysUtil,OemGetFreeSize,p1,p2)

#define		SysUtil_GetBrwHeap()			__ApiLink0(SysUtil,GetBrwHeap)
#define		SysUtil_GetBrwHeapSize()		__ApiLink0(SysUtil,GetBrwHeapSize)
#define		SysUtil_GetClipboardFormat()		__ApiLink0(SysUtil,GetClipboardFormat)
#define		SysUtil_GetClipboardData(p1)		__ApiLink1(SysUtil,GetClipboardData,p1)
#define		SysUtil_SetClipboardData(p1,p2)		__ApiLink2(SysUtil,SetClipboardData,p1,p2)



#endif	//	_BNSOFT__SYSUTIL_H_
