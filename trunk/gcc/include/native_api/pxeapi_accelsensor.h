#ifndef __PXEAPI_ACCELSENSOR_H__
#define __PXEAPI_ACCELSENSOR_H__

/* *****************************************************************************

 В этом файле представлено API для акселерометра, найденное в LG KP501 V10H_00.
 Найдено и оформлено:
  Шамаев Дамир aka Dimadze

***************************************************************************** */



/* ************************************************************************** */

/* События акселерометра */
#define PXE_RUN_ACCELSENSOR_EVENT  3600  // Акселерометр (значительное изменение положения)
#define Window_OnAccelSensor       3600  // Событие акселерометра для окна

#define ACCELSENSOR_DIRECT_NORTH 0 
#define ACCELSENSOR_DIRECT_SOUTH 1
#define ACCELSENSOR_DIRECT_EAST  2
#define ACCELSENSOR_DIRECT_WEST  3

//Включить акселерометр
__pxeapi int AccelSensor_Enable()
__pxe_api_ret_noargs(0x1B8/4, 0x190/4, int)

//Выключить акселерометр
__pxeapi int AccelSensor_Disable()
__pxe_api_ret_noargs(0x1B8/4, 0x194/4, int)

//Проверка акселерометра
__pxeapi int AccelSensor_IsEnable()
__pxe_api_ret_noargs(0x1B8/4, 0x1C8/4, int)

//Разрешить / запретить события от акселерометра
__pxeapi int AccelSensor_EventsEnable(int enable)
__pxe_api_ret_onearg(0x1B8/4, 0x1C0/4, int, enable)

//Получить координаты акселерометра
__pxeapi int AccelSensor_GetPosition(short *x, short *y, short *z)
__pxe_api_ret(0x1B8/4, 0x1A0/4, int, x, y, z)


#endif // __PXEAPI_ACCELSENSOR_H__


