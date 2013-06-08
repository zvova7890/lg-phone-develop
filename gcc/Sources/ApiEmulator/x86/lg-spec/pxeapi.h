#ifndef __PXEAPI_H__
#define __PXEAPI_H__


//События для приложения
#define PXE_RUN_CREATE_EVENT       1
#define PXE_RUN_DESTROY_EVENT      2
#define PXE_RUN_RESUME_EVENT       3
#define PXE_RUN_SUSPEND_EVENT      4
#define PXE_RUN_KEYDOWN_EVENT      101
#define PXE_RUN_KEYUP_EVENT        102
#define PXE_RUN_TIMER_EVENT        106
#define PXE_RUN_PAINT_EVENT        107
#define PXE_RUN_TOUCH_EVENT        111
#define PXE_RUN_INDDRAW_EVENT      112
#define PXE_RUN_ACCELSENSOR_EVENT  3600  // Акселерометр (значительное изменение положения)

//События для окна
#define Window_OnInit              1     // Событие создания окна
#define Window_OnExit              2     // Событие выхода из окна
#define Window_OnAwake             3     // Событие активации окна
#define Window_OnSleep             4     // Событие деактивации окна
#define Window_OnKeyDown           5     // Событие нажатии клавиши (в том числе сенсорные софт-клавиши, просто манипуляции с тачскрином)
#define Window_OnKeyUp             6     // Событие отпускании клавиши
#define Window_OnDraw              10    // События для отрисовки окна
#define Window_OnTimer             11    // События таймера
#define Window_OnPointing          12    // События для более полного восприятия тачскрина (тип прикосновения, координаты)
#define Window_OnIndicatorDraw     13    // Событие отрисовки индикатора (статус-бара)
#define Window_OnAccelSensor       3600  // Событие акселерометра
#define Window_OnCameraNotify      30600

#define TOUCH_ACTION_PRESS      0 // Момент первого нажатия на тачскрин
#define TOUCH_ACTION_RELEASE    1 // Момент отпускания
#define TOUCH_ACTION_MOVE    2 // Момент ведения по тачскрину (В обработчик поочередно передадутся все координаты путя ведения)

#define KEY_SIDE1        34 // Клавиша прибавления громкости
#define KEY_SIDE2        35 // Клавиша уменьшения громкости
#define KEY_SEND         13 // Клавиша посыла вызова (зелёная кнопка)
#define KEY_MULTI        16 // Клавиша вызова Диспетчера задач
#define KEY_END          14 // Клавиша завершения вызова (красная кнопка)
#define KEY_LOCK         81 // Клавиша блокировки
#define KEY_CAMERA       36 // Клавиша вызова камеры
#define KEY_HEADSET      62 // Клавиша наушников

//Только для форм (Виртуальные клавиши)
#define THS_SOFT1        19 // Софт-клавиша 1 тачскрина
#define THS_SOFT2        20 // Софт-клавиша 2 тачскрина
#define THS_SOFT3        21 // Софт-клавиша 3 тачскрина
#define THS_OTHER        31 // Любое нажатие на тачскрин (кроме существующих областей софт-клавиш)

#define LIST_ICONS_STYLE_NONE    0x00000000
#define LIST_ICONS_STYLE_DIGITAL 0x20000890
#define LIST_ICONS_STYLE_CUBUS   0x12060090

#define PXE_LOWORD(w) ( w >>  0) & 0xFFFF
#define PXE_HIWORD(w) ( w >> 16) & 0xFFFF
 

typedef struct {
  int (*evt_handler)(int event_id, int cmd, int subcmd);
  void *base;
  void *userdata;
}ELF_PARASITE_INFO;

#ifdef __cplusplus
extern "C" {
#endif



int RegisterApplicationEventListener( ELF_PARASITE_INFO *pi,
                                      int (*handler)(unsigned long event_id, unsigned long wparam, unsigned long lparam),
                                      const wchar_t *name );



#ifdef __cplusplus
}
#endif

#include <pxeapi_graphics.h>
#include <pxeapi_misc.h>


#endif
