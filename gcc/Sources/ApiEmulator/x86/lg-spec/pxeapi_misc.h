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

#define TOUCHPAD_SENSITIVITY_DEFAULT 0
#define TOUCHPAD_SENSITIVITY_SET     1



#ifdef __cplusplus
extern "C" {
#endif


//Получить хендл настроек
int SetUP_GetHandle();

//Настройка событий от тачпада при перетаскивании, если type = TOUCHPAD_SENSITIVITY_SET, то события будут приходить 
//каждый через количество sensitivity пикселей, таким образом настраиваеться плавность перетаскивания
int SetUP_SetTouchpadSensitivity(int handle, unsigned char type, unsigned short sensitivity);

//Закрыть хендл настроек
void SetUP_CloseHandle(int handle);

//Управление таймером перехода на IDLE и гашения подсветки
int FreezeTimerControl(int param, int state);

//Получение адреса API по имени
int *GetAPIByName(const unsigned short *name_api);




#ifdef __cplusplus
}
#endif

#endif // __PXEAPI_MISC_H__


