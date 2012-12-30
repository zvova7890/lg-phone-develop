#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>


#include "elf/elf.h"


extern int thing_w;
extern int thing_h;
extern int thing_d;
extern unsigned char thing_bitmap[];

extern int star_w;
extern int star_h;
extern int star_d;
extern unsigned char star_bitmap[];

/* =================================== GUI ================================== */

#define WINDOW_ID_SCREEN 0x5001

int Screen_EventHandler(int event_id, int item_num, int param);

void Screen_OnInit();
void Screen_Close(int action);
void Screen_OnExit();
void Screen_OnKeyDown(int key);
void Screen_OnKeyUp(int key);
void Screen_OnDraw();
void Screen_OnIndicatorDraw();
void Screen_OnTimer();
void Screen_OnPointing(int action, int position);
void Screen_OnAwake();
void Screen_OnSleep();


int x1 = 0, y1 = 0, x2 = 0, y2 = 0;
int w1 = 0, h1 = 0, w2 = 0, h2 = 0;
int z = 0, d = 0;

unsigned char *b1 = 0, *b2 = 0; 
int de1 = 0, de2 = 0; 

int su = 0;

void Draw()
{
 char  ascii_text_buffer[256];
 unsigned short u16_text_buffer[256];
 
 Graphics_DrawFillRect(0, STATUSBAR_HEIGHT, DISPLAY_WITDH, DISPLAY_HEIGHT, Graphics_MakeRGBColor(0, 0, 0));
 Graphics_DrawStringSetOutLine(1);
 Graphics_DrawStringSetColor(Graphics_MakeRGBColor(200, 0, 0));
 
 cp1251_2_utf16(u16_text_buffer, "Тест тачскрина");
 Graphics_DrawString(0, STATUSBAR_HEIGHT + 16 * 0, u16_text_buffer, 16);
 
 sprintf(ascii_text_buffer, "Координаты #1: X: %d / Y: %d", x1 + w1/2, y1 + h1/2);
 cp1251_2_utf16(u16_text_buffer, ascii_text_buffer);
 Graphics_DrawString(0, STATUSBAR_HEIGHT + 16 * 1, u16_text_buffer, 16);
 
 sprintf(ascii_text_buffer, "Координаты #2: X: %d / Y: %d", x2 + w2/2, y2 + h2/2);
 cp1251_2_utf16(u16_text_buffer, ascii_text_buffer);
 Graphics_DrawString(0, STATUSBAR_HEIGHT + 16 * 2, u16_text_buffer, 16);
  
 if (z == 1) {
  Graphics_DrawBitmap(x1, y1, w1, h1, de1, b1);
  Graphics_DrawBitmap(x2, y2, w2, h2, de2, b2);
 } else
    {
     Graphics_DrawBitmap(x2, y2, w2, h2, de2, b2);
     Graphics_DrawBitmap(x1, y1, w1, h1, de1, b1);
    }
 Graphics_Repaint();
}


//Действие при создании окна
void Screen_OnInit()
{
 printf("Screen_OnInit\r\n"); 
 
 //__pxe_api_imm_onearg(0x344/4, 0x178/4, 1);
 
 x1 = 50;
 x2 = 80;
 y1 = 200;
 y2 = 50;
 
 w1 = thing_w;
 h1 = thing_h;
 w2 = star_w;
 h2 = star_h;
 
 b1 = thing_bitmap;
 b2 = star_bitmap;

 de1 = thing_d;
 de2 = star_d;
 
 z = 0;
 d = 0;
 
 Draw();
}




//Действие при уничтожении окна
void Screen_OnExit()
{
 printf("Screen_OnExit\r\n");
}

//Действие при зажатии настоящией кнопки или рабочей области тачскрина
void Screen_OnKeyDown(int key)
{
 printf("Screen_OnKeyDown key = %d\r\n", key); 
  
 switch (key)
  {
   case KEY_MULTI:
     TaskMngr_ShowTaskList();
     break;
   case KEY_END:
      TaskMngr_AppExit(0, 0, 0);
     break;
  }
 Draw();
}

//Действие при отпускании настоящией кнопки
void Screen_OnKeyUp(int key)
{
  printf("Screen_OnKeyUp key = %d\r\n", key); 
}

//Действие при отрисовке окна
void Screen_OnDraw()
{
  //printf("Screen_OnDraw()\r\n");
  Draw();
}

//Действие при отрисовке статус-бара
void Screen_OnIndicatorDraw()
{
  //printf("Screen_OnIndicatorDraw()\r\n");
  Draw();
}



//Действие при срабатывании таймеров
void Screen_OnTimer(int timer_id, int param)
{
  //printf("Screen_OnTimer: %d / %d\r\n", timer_id, param);
}

//Действие при манипуляциях с тачскрином
void Screen_OnPointing(int action, int position)
{
 int x, y;
 
 x = PXE_LOWORD(position);
 y = PXE_HIWORD(position);
 
 switch (action)
  {
   case TOUCH_ACTION_PRESS:
     {
      //Если 1-ый объект наверху
      if (z == 0)
       {
         if (x >= x1 && x < (x1 + w1) && y >= y1 && y < (y1 + h1)) d = 1;
         else
          {
           if (x >= x2 && x < (x2 + w2) && y >= y2 && y < (y2 + h2))
            { 
              z = 1;
              d = 1;
            }
          }
      //Если 2-ой объект наверху
       } else
          {
           if (x >= x2 && x < (x2 + w2) && y >= y2 && y < (y2 + h2)) d = 1;
           else
            {
             if (x >= x1 && x < (x1 + w1) && y >= y1 && y < (y1 + h1))
              { 
                z = 0;
                d = 1;
              }
            }
          }
      break;
     }
 
   case TOUCH_ACTION_PRESSED:
     {
      if (d == 1)
       {
        if (z == 0)
         {
           x1 = x;
           y1 = y;
         } else
            {
             x2 = x;
             y2 = y;
            }
       }
      break;
     }
   case TOUCH_ACTION_RELEASE:
     {
      d = 0;
      break;
     }
  }
 
 Draw();
}


//Действие при активации
void Screen_OnAwake()
{
 printf("Screen_OnAwake()\r\n");
}

//Действие при сворачивании
void Screen_OnSleep()
{
 printf("Screen_OnSleep()\r\n");
}

//Главный обработчик окна WINDOW_ID_MAINMENU от приложения
int Window_EventHandler(int cmd, int subcmd, int status)
{
 switch (cmd)
  {
   case Window_OnInit:
     Screen_OnInit();
     break;
   case Window_OnExit:
     Screen_OnExit();
     break;
   case Window_OnAwake:
     Screen_OnAwake();
     break;
   case Window_OnSleep:
     Screen_OnSleep();
     break;
   case Window_OnKeyDown:
     Screen_OnKeyDown(subcmd);
     break;
   case Window_OnKeyUp:
     Screen_OnKeyUp(subcmd);
     break;
   case Window_OnDraw:
     Screen_OnDraw();
     break;
   case Window_OnTimer:
     Screen_OnTimer(subcmd, status);
     break;
   case Window_OnPointing:
     Screen_OnPointing(subcmd, status);
     break;
   case Window_OnIndicatorDraw:
     Screen_OnIndicatorDraw();
     break;
   default:
     break;
  }
 
 return 1;
}


/* ---------------------- Обработчик событий приложения --------------------- */
     


int elf_run(int event_id, int wparam, int lparam)
{
 //printf("elf_run = %d / %d / 0x%08X\r\n", event_id, wparam, lparam);
 switch (event_id)
  {
   //Событие при создании приложения
   case PXE_RUN_CREATE_EVENT:
     //Устанавливаем имя приложения в Диспетчере задач
     TaskMngr_AppSetName(app_handle, 0, 0, 0);
     //Получаем хендл настроек
     su = SetUP_GetHandle();
     //Устанавливаем чувствительность тачпада
     SetUP_SetTouchpadSensitivity(su, TOUCHPAD_SENSITIVITY_SET, 3);
     //Создаём окно
     Windows_Create(WINDOW_ID_SCREEN, Window_EventHandler);
     //Запускаем инициализацию окна
     Windows_Init(WINDOW_ID_SCREEN);
     printf("PXE_RUN_CREATE_EVENT\r\n");
     return 1;
   //Событие при создании приложения
   case PXE_RUN_DESTROY_EVENT:
     //Уничтожаем окно
     Windows_DestroyAll();
     //Закрываем хендл настроек
     SetUP_CloseHandle(su);
     printf("PXE_RUN_DESTROY_EVENT\r\n");
     return 1;
   //Событие при активации приложения 
   case PXE_RUN_RESUME_EVENT:
     printf("PXE_RUN_RESUME_EVENT\r\n");
     //Отправим команду на перерисовку
     Windows_TransEvent(PXE_RUN_PAINT_EVENT, 0, 0);
     //Устанавливаем чувствительность тачпада
     SetUP_SetTouchpadSensitivity(su, TOUCHPAD_SENSITIVITY_SET, 3);
     return 1;
   //Событие при сворачивании приложения 
   case PXE_RUN_SUSPEND_EVENT:
     //Устанавливаем чувствительность тачпада
     SetUP_SetTouchpadSensitivity(su, TOUCHPAD_SENSITIVITY_DEFAULT, 0);
     printf("PXE_RUN_SUSPEND_EVENT\r\n");
     return 1;
   default:
     //Конвертируем остальные события приложения для окна
     Windows_TransEvent(event_id, wparam, lparam);
     return 1;
  }
}


