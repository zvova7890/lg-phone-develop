#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>


#include "elf/elf.h"

/* =================================== GUI ================================== */

#define WINDOW_ID_SCREEN 0x5001

int LGOS_TimerTestEventHandler(int event_id, int item_num, int param);

void LGOS_TimerTestOnInit();
void LGOS_TimerTestClose(int action);
void LGOS_TimerTestOnExit();
void LGOS_TimerTestOnKeyDown(int key);
void LGOS_TimerTestOnKeyUp(int key);
void LGOS_TimerTestOnDraw();
void LGOS_TimerTestOnIndicatorDraw();
void LGOS_TimerTestOnTimer();
void LGOS_TimerTestOnPointing(int action, int position);
void LGOS_TimerTestOnAwake();
void LGOS_TimerTestOnSleep();


LGOS_TIMER timer;
unsigned int button = 0;
unsigned int time = 0;
unsigned int state = 0;

int ButtonHandler(int x, int y, int release)
{
 button = 0;
 
 if (release) return button;
 
 for (int i = 0; i < 4; i++)
 if (x > 10 + 56*0 && x < ( 10 + 50 + 56*i ) && y > 320 && y < (320 + 50)) 
   {
    button = i + 1;
    break;
   }
 return button;
}

void DrawProc()
{
 char u8_text_buffer[2048];
 unsigned short u16_text_buffer[2048];
 
 Graphics_DrawFillRect(0, STATUSBAR_HEIGHT, Graphics_GetScreenWidth(), Graphics_GetScreenHeight(), Graphics_MakeRGBColor(200, 200, 200));
 
 Graphics_DrawFillRect(10 + 56*0, 320, 10 + 50 + 56*0, 320 + 50, Graphics_MakeRGBColor(0, 0, 200));
 Graphics_DrawFillRect(10 + 56*1, 320, 10 + 50 + 56*1, 320 + 50, Graphics_MakeRGBColor(0, 0, 200));
 Graphics_DrawFillRect(10 + 56*2, 320, 10 + 50 + 56*2, 320 + 50, Graphics_MakeRGBColor(0, 0, 200));
 Graphics_DrawFillRect(10 + 56*3, 320, 10 + 50 + 56*3, 320 + 50, Graphics_MakeRGBColor(0, 0, 200));
 
 if (button)
 Graphics_DrawFillRect(10 + 56*(button - 1), 320, 10 + 50 + 56*(button - 1), 320 + 50, Graphics_MakeRGBColor(0, 200, 0));
 
 Graphics_DrawStringSetOutLine(1);
 Graphics_DrawStringSetColor(Graphics_MakeRGBColor(255, 0, 0));
 
 cp1251_2_utf16(u16_text_buffer, "������ ����");
 Graphics_DrawString(0, STATUSBAR_HEIGHT + 16 * 0, u16_text_buffer, 16);
 
 sprintf(u8_text_buffer, "������: %d", time);
 cp1251_2_utf16(u16_text_buffer, u8_text_buffer);
 Graphics_DrawString(0, STATUSBAR_HEIGHT + 16 * 1, u16_text_buffer, 16);
 
 sprintf(u8_text_buffer, "���������: %d", state);
 cp1251_2_utf16(u16_text_buffer, u8_text_buffer);
 Graphics_DrawString(0, STATUSBAR_HEIGHT + 16 * 2, u16_text_buffer, 16);
 
 cp1251_2_utf16(u16_text_buffer, "�������");
 Graphics_DrawString(10 + 0 + 56*0, 320 + 20, u16_text_buffer, 10);
 cp1251_2_utf16(u16_text_buffer, "�����");
 Graphics_DrawString(10 + 3 + 56*1, 320 + 20, u16_text_buffer, 10);
 cp1251_2_utf16(u16_text_buffer, "����");
 Graphics_DrawString(10 + 3 + 56*2, 320 + 20, u16_text_buffer, 10);
 cp1251_2_utf16(u16_text_buffer, "�������");
 Graphics_DrawString(10 + 0 + 56*3, 320 + 20, u16_text_buffer, 10);
 
 Graphics_Repaint();
}

// ��������� ��� �������
void lgos_timer_routune(int arg)
{
 // �������� ������ � ��������� �������
 LGOS_Timer_IsStarted(&timer, &state);
 DrawProc();
 time++;
}

void Timer_Init()
{
 // ������ ������ TIMER_TEST
 LGOS_Timer_Create(&timer, "TIMER_TEST");
 // ������������� ��� ������� ����� �����
 LGOS_Timer_SetLoop(&timer, 1);  
 // ������������� ��� ������� ���������
 LGOS_Timer_SetProc(&timer, lgos_timer_routune, 0);
 // ������������� ��� ������� ������ ������������
 LGOS_Timer_SetPeriodSimple(&timer, 50);
 
 state = 0;
}

void Timer_Start()
{
 // ��������� ������
 LGOS_Timer_Start(&timer);
 
 state = 0;
}

void Timer_Stop()
{
 // ������������� ������
 LGOS_Timer_Stop(&timer);
 
 state = 0;
}
void Timer_DeInit()
{
 // ������������� ������
 LGOS_Timer_Stop(&timer);
 // ��� 200 �����
 NU_Sleep(200);
 // ������� ������
 LGOS_Timer_Delete(&timer);
 // ��� 200 �����
 NU_Sleep(200);
 
 state = 0;
}


//�������� ��� �������� ����
void LGOS_TimerTestOnInit()
{
 printf("LGOS_TimerTestOnInit\r\n"); 
}

//�������� ��� ����������� ����
void LGOS_TimerTestOnExit()
{
 printf("LGOS_TimerTestOnExit\r\n");
 Timer_DeInit();
}

//�������� ��� ������� ���������� ������ ��� ������� ������� ���������
void LGOS_TimerTestOnKeyDown(int key)
{
 printf("LGOS_TimerTestOnKeyDown key = %d\r\n", key); 
  
 switch (key)
  {
   case KEY_MULTI:
     TaskMngr_ShowTaskList();
     break;
   case KEY_END:
     TaskMngr_AppExit(0, 0, 0);
     break;
   case KEY_SEND:
     break;
   case KEY_SIDE1:
     break;
   case KEY_SIDE2:
     break;
   case KEY_CAMERA:
     break;
  }
}





//�������� ��� ���������� ���������� ������
void LGOS_TimerTestOnKeyUp(int key)
{
 printf("LGOS_TimerTestOnKeyUp key = %d\r\n", key); 
}

//�������� ��� ��������� ����
void LGOS_TimerTestOnDraw()
{
 printf("LGOS_TimerTestOnDraw()\r\n");
}

//�������� ��� ��������� ������-����
void LGOS_TimerTestOnIndicatorDraw()
{
  printf("LGOS_TimerTestOnIndicatorDraw()\r\n");
}



//�������� ��� ������������ ��������
void LGOS_TimerTestOnTimer(int timer_id, int param)
{
 
}

//�������� ��� ������������ � ����������
void LGOS_TimerTestOnPointing(int action, int position)
{
 int x, y;
 
 x = PXE_LOWORD(position);
 y = PXE_HIWORD(position);
 
 switch (action)
  {
   case TOUCH_ACTION_PRESS:
      switch (ButtonHandler(x, y, 0))
       {
        case 1:
           Timer_Init();
           break;
        case 2:
           Timer_Start();
           break;
        case 3:
           Timer_Stop();
           break;
        case 4:
           Timer_DeInit();
           break;
       }
      break;
   case TOUCH_ACTION_PRESSED:
      break;
   case TOUCH_ACTION_RELEASE:
      ButtonHandler(x, y, 1);
      break;
  }
}


//�������� ��� ���������
void LGOS_TimerTestOnAwake()
{
 //printf("Screen_OnAwake()\r\n");
}

//�������� ��� ������������
void LGOS_TimerTestOnSleep()
{
 //printf("Screen_OnSleep()\r\n");
}

//������� ���������� ���� WINDOW_ID_MAINMENU �� ����������
int Window_EventHandler(int cmd, int subcmd, int status)
{
 switch (cmd)
  {
   case Window_OnInit:
     LGOS_TimerTestOnInit();
     break;
   case Window_OnExit:
     LGOS_TimerTestOnExit();
     break;
   case Window_OnAwake:
     LGOS_TimerTestOnAwake();
     break;
   case Window_OnSleep:
     LGOS_TimerTestOnSleep();
     break;
   case Window_OnKeyDown:
     LGOS_TimerTestOnKeyDown(subcmd);
     break;
   case Window_OnKeyUp:
     LGOS_TimerTestOnKeyUp(subcmd);
     break;
   case Window_OnDraw:
     LGOS_TimerTestOnDraw();
     break;
   case Window_OnTimer:
     LGOS_TimerTestOnTimer(subcmd, status);
     break;
   case Window_OnPointing:
     LGOS_TimerTestOnPointing(subcmd, status);
     break;
   case Window_OnIndicatorDraw:
     LGOS_TimerTestOnIndicatorDraw();
     break;
   default:
     break;
  }
 DrawProc();
 return 1;
}


/* ---------------------- ���������� ������� ���������� --------------------- */
     


int elf_run(int event_id, int wparam, int lparam)
{
 //printf("elf_run = %d / %d / 0x%08X\r\n", event_id, wparam, lparam);
 switch (event_id)
  {
   //������� ��� �������� ����������
   case PXE_RUN_CREATE_EVENT:
     Graphics_ChangeGDI(GDI_STATE_NORMAL);
     //������������� ��� ���������� � ���������� �����
     TaskMngr_AppSetName(app_handle, 0, 0, 0);
     //������ ����
     Windows_Create(WINDOW_ID_SCREEN, Window_EventHandler);
     //��������� ������������� ����
     Windows_Init(WINDOW_ID_SCREEN);
     printf("PXE_RUN_CREATE_EVENT\r\n");
     return 1;
   //������� ��� �������� ����������
   case PXE_RUN_DESTROY_EVENT:
     //���������� ����
     Windows_DestroyAll();
     printf("PXE_RUN_DESTROY_EVENT\r\n");
     return 1;
   //������� ��� ��������� ���������� 
   case PXE_RUN_RESUME_EVENT:
     Graphics_ChangeGDI(GDI_STATE_NORMAL);
     printf("PXE_RUN_RESUME_EVENT\r\n");
     //�������� ������� �� �����������
     Windows_TransEvent(PXE_RUN_PAINT_EVENT, 0, 0);
     return 1;
   //������� ��� ������������ ���������� 
   case PXE_RUN_SUSPEND_EVENT:
     printf("PXE_RUN_SUSPEND_EVENT\r\n");
     return 1;
   default:
     //������������ ��������� ������� ���������� ��� ����
     Windows_TransEvent(event_id, wparam, lparam);
     return 1;
  }
}


