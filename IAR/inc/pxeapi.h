#ifndef __PXEAPI_H__
#define __PXEAPI_H__

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
#define TOUCH_ACTION_PRESSED    2 // ������ ������� �� ��������� (� ���������� ���������� ����������� ��� ���������� ���� �������)

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

#pragma diag_suppress=Ta035
#pragma swi_number=0x30
__swi __arm unsigned int **__pxeapi_getlib();

#include "pxeapi_macro.h"

#include "pxeapi_windows.h"
#include "pxeapi_forms.h"
#include "pxeapi_timers.h"
#include "pxeapi_accelsensor.h"
#include "pxeapi_kpdctrl.h"
#include "pxeapi_graphics.h"
#include "pxeapi_misc.h"


#endif // __PXEAPI_H__

