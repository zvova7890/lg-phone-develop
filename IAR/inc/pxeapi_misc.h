#ifndef __PXEAPI_MISC_H__
#define __PXEAPI_MISC_H__

/* *****************************************************************************

 В этом файле представлено PXE API, найденное в LG KP501 V10H_00.
 Найдено и оформлено:
  Шамаев Дамир aka Dimadze

***************************************************************************** */

#define FREEZETIMER_PARAM          0
#define FREEZETIMER_ACTION_DISABLE 0
#define FREEZETIMER_ACTION_ENABLE  2

__pxeapi int FreezeTimerControl(int param, int state)
__pxe_api_ret(0x13C/4, 0x14/4, int, param, state)

/* Получение адреса API по имени */
__pxeapi int *GetAPIByName(const unsigned short *name_api)
__pxe_api_ret_onearg(0x30/4, 0x08/4, int *, name_api)


#endif // __PXEAPI_MISC_H__


