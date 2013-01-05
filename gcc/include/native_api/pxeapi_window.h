#ifndef __PXEAPI_WINDOWS_H__
#define __PXEAPI_WINDOWS_H__

/* *****************************************************************************

 В этом файле представлено API для работы с окнами, найденное в LG KP501 V10H_00.
 Найдено и оформлено:
  Шамаев Дамир aka Dimadze

***************************************************************************** */

//Альтернативные имена функций

/* ************************************************************************** */


//Создание окна
__pxeapi int Window_Create(int window_id, int (*evt_handler)(int cmd, int subcmd, int status))
__pxe_api_ret(0x48/4, 0x18/4, int, window_id, evt_handler)

//Инициализация окна (посылка события инициализации)
__pxeapi int Window_Init(int window_id)
__pxe_api_ret_onearg(0x48/4, 0x1C/4, int, window_id)

//Уничтожение всех окон приложения
__pxeapi int Window_DestroyAll()
__pxe_api_ret_noargs(0x48/4, 0x14/4, int)

//Перенаправление событий приложения в окна
__pxeapi int Window_TransEvent(int cmd, int subcmd, int status)
__pxe_api_ret(0x48/4, 0x0C/4, int, cmd, subcmd, status)

//Отправка события в окно
__pxeapi int Window_SendEvent(int window_id, int cmd, int subcmd, int status)
__pxe_api_ret(0x48/4, 0x00/4, int, window_id, cmd, subcmd, status)

//Запуск окна
__pxeapi int Window_Show(int window_id)
__pxe_api_ret_onearg(0x48/4, 0x24/4, int, window_id)

#endif // __PXEAPI_WINDOWS_H__


