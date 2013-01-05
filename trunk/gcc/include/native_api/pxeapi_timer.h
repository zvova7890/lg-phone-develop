#ifndef __PXEAPI_TIMERS_H__
#define __PXEAPI_TIMERS_H__

/* *****************************************************************************

 � ���� ����� ������������ API ��� ��������, ��������� � LG KP501 V10H_00.
 ������� � ���������:
  ������ ����� aka Dimadze

***************************************************************************** */

//������� ������� ��� ����������
#define PXE_RUN_TIMER_EVENT        106
//������� ������� ��� ����
#define Window_OnTimer             11

//��� ������� ������� ��� ��������
#define TIMER_TYPE_ONEEVENT        0
#define TIMER_TYPE_LOOP            1

//�������������� ���� �������
#define CreateTimerEvent Timer_CreateEvent
#define KillTimerEvent   Timer_KillEvent

//������� ������� �������
__pxeapi int Timer_CreateEvent(int timer_id, int expirate_period, int type)
__pxe_api_ret(0x14/4, 0x00/4, int, timer_id, expirate_period, type)

//������� ������� �������
__pxeapi int Timer_KillEvent(int timer_id)
__pxe_api_ret_onearg(0x14/4, 0x08/4, int, timer_id)


#endif // __PXEAPI_TIMERS_H__


