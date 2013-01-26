/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	APPLICATION CORE

	Copyright(c) 1997-2002 BNSoft Corp.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT_APP_H_
#define		_BNSOFT_APP_H_

#include	"Include.h"
#include	"ProcMngr.h"


typedef enum
{
	APPLEVEL_PUBLIC						= 0,
	APPLEVEL_DEVELOPER,
	APPLEVEL_SYSTEM
} E_APPLEVEL;

typedef struct
{
	QUAD				ProductID;
	WORD				MajorVersion;
	WORD				MinorVersion;
	A_CHAR				ProductName[33];
	A_CHAR				Company[33];
	A_CHAR				Developer[33];
	QUAD				CreateDaySum;						//	from 2000.1.1
	QUAD				NormalIconPos;
	QUAD				LargeIconPos;
	QUAD				ResourcePos;
	E_APPLEVEL			AppLevel;
	QUAD				RunnableCount;
	QUAD				ExpireDaySum;
} TAppInfo;



extern H_PROCESS App_Run     (T_CSTR pcszFile, T_PARAM wParam);
extern H_PROCESS App_RunEx   (T_CSTR pcszFile, T_PARAM wParam, int nPriority, BOOL bIndividual);
extern void	 App_Exit    (H_PROCESS hProc, int ExitCode);
extern void	 App_Resume  (H_PROCESS hProc, T_PARAM wParam);

extern void	 App_Suspends (T_PARAM wParam);  
extern BOOL	 App_GetInfo (T_CSTR pcszFile, TAppInfo* pAppInfo);



#endif	//	_BNSOFT_APP_H_
