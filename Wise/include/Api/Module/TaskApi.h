#ifndef __TASKAPI_H__
#define __TASKAPI_H__


#include        "ModuleApiMacro.h"
#include	"../BasicApiLib/Include/App.h"


/* Задайте адрес TaskApi */
extern int *g_pTaskApiLink;

#define MODULEAPI_TASKAPI      L"TaskApi"

#define TASKAPI_EXIT_RETURN    0
#define TASKAPI_EXIT_TOIDLE    3

#define TASKAPI_GETINFO_LANGID 3

/* Task API */

//Вызов диспетчера задач
#define TaskMngr_CallTaskMan() ((void (*) ())g_pTaskApiLink[0x70/4])()


//Загрузка приложения
__mapi H_PROCESS TaskMngr_App_Run(T_CSTR pcszFile, T_PARAM wParam)
__mapi_adr_ret(g_pTaskApiLink[0x00/4], H_PROCESS, pcszFile, wParam)

//Загрузка приложения 
__mapi H_PROCESS TaskMngr_App_RunEx(T_CSTR pcszFile, T_PARAM wParam, int nPriority, BOOL bIndividual)
__mapi_adr_ret(g_pTaskApiLink[0x04/4], H_PROCESS, pcszFile, wParam, nPriority, bIndividual)

//Закрытие приложения 
__mapi void TaskMngr_App_Exit(H_PROCESS hProc, int ExitCode, int ExitType)
__mapi_adr_void(g_pTaskApiLink[0x08/4], hProc, ExitCode, ExitType)

//Закрытие приложения 
__mapi void TaskMngr_App_Resume(H_PROCESS hProc, T_PARAM wParam)
__mapi_adr_void(g_pTaskApiLink[0x0C/4], hProc, wParam)


//Резюмирование приложения 
__mapi void TaskMngr_App_ResumeEx(H_PROCESS hProc, T_PARAM wParam, int unk)
__mapi_adr_void(g_pTaskApiLink[0x10/4], hProc, wParam, unk)

//Добавление в список задач
__mapi BOOL TaskMngr_App_Insert(H_PROCESS hProc)
__mapi_adr_ret_onearg(g_pTaskApiLink[0x38/4], BOOL, hProc)

//Задание имени приложения
__mapi BOOL TaskMngr_App_SetName(H_PROCESS hProc, int name, int name1, int name2)
__mapi_adr_ret(g_pTaskApiLink[0x40/4], BOOL, hProc, name, name1, name2)

__mapi int TaskMngr_GetJavaApps()
__mapi_adr_ret_noargs(g_pTaskApiLink[0xEC/4], int)

__mapi QUAD TaskMngr_GetTaskInfo(H_PROCESS hProc, int id)
__mapi_adr_ret(g_pTaskApiLink[0xC8/4], QUAD, hProc, id)

#endif // __TASKAPI_H__

