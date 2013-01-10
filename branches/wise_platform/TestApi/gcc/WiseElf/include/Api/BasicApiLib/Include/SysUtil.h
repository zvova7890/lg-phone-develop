/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	SYSTEM UTILITY

	Copyright(c) 1997-2002 BNSoft Corp.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT_SYSUTIL_H_
#define		_BNSOFT_SYSUTIL_H_

#include	"Include.h"
#include	<stdarg.h>


//	SysUtil Type Definition
typedef struct
{
	int			Year;
	int			Month;
	int			Day;
	int			DayOfWeek;
	int			Hour;
	int			Minute;
	int			Second;
} TLocalTime;

//	Sysutil Clipboard Format
typedef	enum
{

	CLIPBOARD_EMPTY			= 0x00000000,
	CLIPBOARD_SIMPLETEXT,
	CLIPBOARD_RICHTEXT,
	CLIPBOARD_OWNERDISPLAY		= 0x00000080,
	CLIPBOARD_MAX			= 0x80000000
} E_CLIPBOARD;


//	SysUtil Internal Member Functions

extern void	        SysUtil_SetSeed			(int nSeed);
extern int	        SysUtil_GetRandom		(int nRange);
extern QUAD	        SysUtil_GetTickCount		(void);

extern void	        SysUtil_GetLocalTime		(TLocalTime* pLocalTime);
extern void	        SysUtil_GetTime			(int* pHour, int* pMinute, int* pSecond);
extern void	        SysUtil_GetDate			(int* pYear, int* pMonth, int* pDay, int* pDayOfWeek);
extern int	        SysUtil_GetDayOfWeek		(int Year, int Month, int Day);
extern int	        SysUtil_GetDaySum		(int Year, int Month, int Day);
extern void	        SysUtil_GetDateFromDaySum 	(int Sum, int* pYear, int* pMonth, int* pDay);
  
extern void	        SysUtil_SetLastError		(int nError);
extern int	        SysUtil_GetLastError		(void);

extern void	        SysUtil_SetAppDebugEnable	(BOOL bEnable);
extern BOOL	        SysUtil_GetAppDebugEnable 	(void);
extern void	        SysUtil_Fatal			(int nLineNo, const char* pszFileName , char* msg);
extern int	        SysUtil_DebugTraceAppHigh	(char* format, ...);
extern int		SysUtil_DebugTraceAppMid	(char* format, ...);
extern int		SysUtil_DebugTraceAppLow	(char* format, ...);
extern int		SysUtil_DebugTraceAppEx		(unsigned long AppCode, int nLevel, int nLineNo, 
							 const char* pszFileName, char* format, ...);


extern void*		SysUtil_OemMalloc				(T_NUM nSize);
extern void*		SysUtil_OemReAlloc			(void * pBuff,T_NUM nSize);

extern void		SysUtil_OemFree				(void* pPtr);
extern QUAD		SysUtil_OemGetFreeSize		(QUAD *pdwTotal, QUAD *pdwMax);

extern void*		SysUtil_GetBrwHeap(void) ;
extern QUAD		SysUtil_GetBrwHeapSize(void) ;
extern E_CLIPBOARD	SysUtil_GetClipboardFormat(void);
extern void*		SysUtil_GetClipboardData(E_CLIPBOARD Format);
extern BOOL		SysUtil_SetClipboardData(E_CLIPBOARD Format, void* pData);


#endif	//	_BNSOFT_SYSUTIL_H_
