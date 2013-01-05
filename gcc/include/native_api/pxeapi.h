#ifndef __PXEAPI_H__
#define __PXEAPI_H__

#include <wchar.h>
#include "swihelper.h"

//������� ��� ����������
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
#define PXE_RUN_ACCELSENSOR_EVENT  3600  // ������������ (������������ ��������� ���������)

//������� ��� ����
#define Window_OnInit              1     // ������� �������� ����
#define Window_OnExit              2     // ������� ������ �� ����
#define Window_OnAwake             3     // ������� ��������� ����
#define Window_OnSleep             4     // ������� ����������� ����
#define Window_OnKeyDown           5     // ������� ������� ������� (� ��� ����� ��������� ����-�������, ������ ����������� � ����������)
#define Window_OnKeyUp             6     // ������� ���������� �������
#define Window_OnDraw              10    // ������� ��� ��������� ����
#define Window_OnTimer             11    // ������� �������
#define Window_OnPointing          12    // ������� ��� ����� ������� ���������� ��������� (��� �������������, ����������)
#define Window_OnIndicatorDraw     13    // ������� ��������� ���������� (������-����)
#define Window_OnAccelSensor       3600  // ������� �������������
#define Window_OnCameraNotify      30600

#define TOUCH_ACTION_PRESS      0 // ������ ������� ������� �� ��������
#define TOUCH_ACTION_RELEASE    1 // ������ ����������
#define TOUCH_ACTION_MOVE    2 // ������ ������� �� ��������� (� ���������� ���������� ����������� ��� ���������� ���� �������)

#define KEY_SIDE1        34 // ������� ����������� ���������
#define KEY_SIDE2        35 // ������� ���������� ���������
#define KEY_SEND         13 // ������� ������ ������ (������ ������)
#define KEY_MULTI        16 // ������� ������ ���������� �����
#define KEY_END          14 // ������� ���������� ������ (������� ������)
#define KEY_LOCK         81 // ������� ����������
#define KEY_CAMERA       36 // ������� ������ ������
#define KEY_HEADSET      62 // ������� ���������

//������ ��� ���� (����������� �������)
#define THS_SOFT1        19 // ����-������� 1 ���������
#define THS_SOFT2        20 // ����-������� 2 ���������
#define THS_SOFT3        21 // ����-������� 3 ���������
#define THS_OTHER        31 // ����� ������� �� �������� (����� ������������ �������� ����-������)

#define LIST_ICONS_STYLE_NONE    0x00000000
#define LIST_ICONS_STYLE_DIGITAL 0x20000890
#define LIST_ICONS_STYLE_CUBUS   0x12060090

typedef struct {
  int (*evt_handler)(int event_id, int cmd, int subcmd);
  void *base;
  void *userdata;
}ELF_PARASITE_INFO;

#ifdef __cplusplus
extern "C" {
#endif


__inl
unsigned int **__pxeapi_getlib()
__def( 0x30, unsigned int **)


int RegisterApplicationEventListener( ELF_PARASITE_INFO *pi, int (*handler)(int event_id, int wparam, int lparam),
                                      const wchar_t *name );

#include "pxeapi_macro.h"

#include "pxeapi_window.h"
#include "pxeapi_form.h"
#include "pxeapi_timer.h"
#include "pxeapi_accelsensor.h"
#include "pxeapi_kpdctrl.h"
#include "pxeapi_graphics.h"
#include "pxeapi_misc.h"

#ifdef __cplusplus
}
#endif

#endif // __PXEAPI_H__

