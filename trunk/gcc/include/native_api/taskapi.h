#ifndef __TASKAPI_H__
#define __TASKAPI_H__

#include "pxeapi_macro.h"

/* *****************************************************************************

 В этом файле представлено API для работы c задачами, найденное в LG KP501 V10H_00.
 Найдено и оформлено:
  Шамаев Дамир aka Dimadze

  TASKAPI_EXTERN
  Для самостоятельного задания строчки имени для определения адреса API.
  Дополнительно нужно создать строку где-нибудь:
  const unsigned short __task_api_name_extern[]=TASKAPI_NAME;
  Всё описанное применительно к IAR 4.xx, так как может случиться баг линковки

***************************************************************************** */

#define TASKAPI_NAME L"TaskApi"

#ifdef TASKAPI_EXTERN
extern const unsigned short __task_api_name_extern[];
#define __task_api_array ((int *)__pxe_api_imm_onearg(0x30/4, 0x08/4, __task_api_name_extern))
#else
#define __task_api_array ((int *)__pxe_api_imm_onearg(0x30/4, 0x08/4, TASKAPI_NAME))
#endif

typedef struct {
    int            app0;
    int            app1;
    int            app2;
    int            app3;
    unsigned int   *pxo_header;
    int            app4[10];
    unsigned short fname[32];
    int            app5[15];

}PxoApplicationData;


#define TASKAPP_EXIT_RETURN   0
#define TASKAPP_EXIT_TOIDLE   3

/* Task API */

//Вызов диспетчера задач
#define TaskMngr_Show() ((void (*) ())__task_api_array[0x70/4])()

//Загрузка PXE приложения
__pxeapi int TaskMngr_AppRun(const unsigned short *virt_path, int param)
__pxe_adr_ret(__task_api_array[0x00/4], int, virt_path, param)

//Загрузка PXE приложения
__pxeapi int TaskMngr_AppRunOpt(const unsigned short *virt_path, int param1, int param2, int mode)
__pxe_adr_ret(__task_api_array[0x04/4], int, virt_path, param1, param2, mode)

//Закрытие PXE приложения
__pxeapi int TaskMngr_AppExit(int arg0, int arg1, int goto_after_type)
__pxe_adr_ret(__task_api_array[0x08/4], int, arg0, arg1, goto_after_type)

//Регистрация PXE приложения в диспетчере задач
__pxeapi int TaskMngr_AppRegister(int handle)
__pxe_adr_ret_onearg(__task_api_array[0x38/4], int, handle)

//Именование PXE приложения
__pxeapi int TaskMngr_AppSetName(int handle, int name, int name1, int name2)
__pxe_adr_ret(__task_api_array[0x40/4], int, handle, name, name1, name2)

#endif // __TASKAPI_H__

