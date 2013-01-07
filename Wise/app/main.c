#include	"..\inc\Api\ApiLinkLib\ApiLink.h"

#pragma diag_suppress=Ta035

#pragma swi_number=0xD
__swi __arm void lclear();

#pragma swi_number=0xE
__swi __arm void lprintf(const char *format, ...);

/*  ELF */

#pragma segment="ELF"
const char __elf_build[] = "ElfApp, builded "__TIME__" "__DATE__;
#define __elf_start_address (void *)__segment_begin("ELF")

//����� ��������
H_PROCESS h_proc;
//����� �������
H_TIMER h_timer;
//��������� �� API
TApiLink *g_pApiLink = 0;

/* ��������� ������������� */
void elf_init(int *api)
{
  if (api)
   {
    lprintf("API: 0x%08X\r\n", api[0]);
    g_pApiLink = (TApiLink *)api[0];
   }
}

/* ������� ������ ���������� (��� �������)*/
void elf_timercore_callback(T_HANDLE hOwner, H_TIMERCORE hTimerCore, int nFlags)
{
 lprintf("elf_timercore_callback\r\n");
}

/* ���������� ��������� ��� ���������� #1 */
BOOL elf_msg_run_1(T_MSG msg, T_PARAM wParam, T_PARAM lParam)
{
 switch (msg)
  {
   case MSG_INIT:
     MsgHandler_SetFullScreenMode(TRUE);
     return TRUE;
     
   case MSG_EXIT:
     return TRUE;
     
   case MSG_KEYDOWN:
     {
      switch (wParam)
       {
        case BNS_MENU_K:
          MsgHandler_InsertActivePID(2);
          return TRUE;
          
        case BNS_SIDE1_K:
          h_timer = TimerCore_SetTimer(h_proc, 1000, TRUE, FALSE, elf_timercore_callback);
          return TRUE;
          
        case BNS_SIDE2_K:
          TimerCore_KillTimer(h_timer);
          return TRUE;
          
        case BNS_END_K:
          App_Exit(h_proc, 0);
          return TRUE;
          
        default:
          return TRUE;
       }
     }
      
   default:
     return TRUE;
  }
}

/* ���������� ��������� ��� ���������� #2 */
BOOL elf_msg_run_2(T_MSG msg, T_PARAM wParam, T_PARAM lParam)
{
 switch (msg)
  {
   case MSG_INIT:
     MsgHandler_SetFullScreenMode(FALSE);
     return TRUE;
     
   case MSG_EXIT:
     return TRUE;
     
   case MSG_KEYDOWN:
     {
      switch (wParam)
       {
        case BNS_MENU_K:
          App_RunEx(L"LGAPP/Pxo/TaskList.pxo", 0, FOREGROUND_PRIORITY, TRUE);
          return TRUE;
          
        case BNS_SEND_K:
          return TRUE;
          
        case BNS_END_K:
          MsgHandler_InsertActivePID(1);
          return TRUE;
          
        default:
          return TRUE;
       }
     }
      
   default:
     return TRUE;
    }
}


/* ���������� ������� ��� ���������� */
int elf_run(T_EVENT EventType, T_PARAM wParam, T_PARAM lParam)
{
 BOOL error = 0; 
 switch (EventType)
  {
   case BNS_EVENT_START:
     
      lprintf("APIVer: 0x%X\r\n", SysDev_GetInfo(SYSINFO_API_VERSION, &error));
     
      MsgHandler_RegisterProcessor(1, elf_msg_run_1);
      MsgHandler_RegisterProcessor(2, elf_msg_run_2);
      MsgHandler_SetActivePID(1);
      
      MsgHandler_Process();
      break;
      
   case BNS_EVENT_TERMINATE:
      MsgHandler_RemoveProcessor(elf_msg_run_1, 0, 0);
      MsgHandler_RemoveProcessor(elf_msg_run_2, 0, 0);
      break;
      
   default:
      MsgHandler_Translate(EventType, wParam, lParam);
      break;
  }
 
 return 0;
}


int main(int argc, char argv[])
{
 /* �������� �������� */
 TProcessCI tproc;

 //����������� ��������
 tproc.enAccessLevel = ACCESSLEVEL_SYSTEM;
 //����� ����� ���� (����� ��� �������� ������������� ��������)
 //� ��� ��� ���� ���� �������
 tproc.CodeArea = (T_ADDR)__elf_start_address;
 //����� ����� ������ (����� ��� �������� ������������� ��������)
 //������� ��������
 tproc.DataArea = (T_ADDR)0;
 //������� �-�� ��� ������������� (������ ��� ������������� API)
 tproc.PxeInitAddr = (T_ADDR)elf_init;
 //������� �-�� ��� ��������� ������� ��������
 tproc.PxeRunAddr = (T_ADDR)elf_run;
 //������� ��� ��������
 tproc.pszAppName = L"Process";
 //��������� ���������
 tproc.hAppDrive = 0;
 tproc.hAppDir   = 0;
 
 //������ ��������������� �������
 h_proc = ProcMngr_CreateProcess(&tproc, TRUE);
 lprintf("h_proc = 0x%08X\r\n", h_proc);

 /* ����� �������� */
 ProcMngr_StartProcess(h_proc, 0, FOREGROUND_PRIORITY);
}



