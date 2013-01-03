#ifndef __LGOS_TIMERS_H__
#define __LGOS_TIMERS_H__

typedef struct {
  int    period_ms;
  int    period;
  int    pointer;
  void (*routune)(int arg);
  int    unk_1;
  char   is_loop;
  char   is_start;
  short  unk_2;
}LGOS_TIMER;

#pragma diag_suppress=Ta035

// ������� ������, ��������� LGOS_TIMER ����������� ��� ������
#pragma swi_number=0x120
__swi __arm int LGOS_Timer_Create(LGOS_TIMER *timer, char *name);

// ������� ������
#pragma swi_number=0x121
__swi __arm int LGOS_Timer_Delete(LGOS_TIMER *timer);

// ���������� ����� ����� ������� (isloop = 0 -> ������ ��������� ���� ��� / isloop = 1 -> ����)
#pragma swi_number=0x122
__swi __arm int LGOS_Timer_SetLoop(LGOS_TIMER *timer, int isloop);

// ���������� ��������� �������
#pragma swi_number=0x123
__swi __arm int LGOS_Timer_SetProc(LGOS_TIMER *timer, void (*routune)(int arg), int arg);

// ���������� ������ ������� � ����������� period_ms, period - ���������� ��������, 
// ������ ����� period_ms, �� �� ������ ���� ������ ���, ��������� �� ��� ��� ������
#pragma swi_number=0x124
__swi __arm int LGOS_Timer_SetPeriod(LGOS_TIMER *timer, int period_ms, int period);

// ���������� ������ ������� � ����������� period
#define         LGOS_Timer_SetPeriodSimple(timer, period) LGOS_Timer_SetPeriod(timer, period, period)

//������ �������
#pragma swi_number=0x125
__swi __arm int LGOS_Timer_Start(LGOS_TIMER *timer);

//���� �������
#pragma swi_number=0x126
__swi __arm int LGOS_Timer_Stop(LGOS_TIMER *timer);

//�������� �� ������������ �������
#pragma swi_number=0x127
__swi __arm int LGOS_Timer_IsStarted(LGOS_TIMER *timer, unsigned int *is_started);

#endif // __LGOS_TIMERS_H__

