#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>


#include "elf/elf.h"


/* ============================= Поиск приложений =========================== */

typedef struct {
   unsigned short name[64];
   char fname[256];
} EAPP_LIST;


const char elfs_apps_folder[]="/usr/Zbin/apps";


//Создаём список установленных ELF - приложений
EAPP_LIST *ElfAppsList_Build(unsigned int *count)
{
 FS_INFO fs;
 EAPP_LIST *list = 0;

 int c = 0;
 char name[64];
 char path[512];
 
 if (count) *count = 0;
 
 list = mem_malloc(sizeof(EAPP_LIST));
 if (!list) return 0;
 
 int d = fs_opendir(elfs_apps_folder);
 if (d > 0)
  {
   while (!fs_readdir(d, &fs))
    {
     if (fs.attr & FS_ATTR_FOLDER)
      {
       if (!strcmp(fs.name, ".") || !strcmp(fs.name, "..") ) continue;
        else
         {
           strncpy(name, fs.name, 64);
           snprintf(path, 512, "%s/%s/%s.elf", elfs_apps_folder, fs.name, fs.name);
           if (!fs_getinfo(path, &fs))
            {
             list = mem_realloc(list, (c + 1) * sizeof(EAPP_LIST));
             if (list)
              {
               cp1251_2_utf16(list[c].name, name);
               strncpy(list[c].fname, path, 512);
               c++;
              }
            }
         }
      }
    }
   fs_closedir(d); 
   if (count) *count = c;
   return list;
  } else return 0; 
}

//Удаляем список установленных ELF - приложений
void ElfAppsList_Free(EAPP_LIST *list)   
{
 if (list)
   mem_free(list);
}



/* =================================== GUI ================================== */

#define WINDOW_ID_MAINMENU 0xD001

int Menu_EventHandler(int event_id, int item_num, int param);

void Menu_OnInit();
void Menu_Close(int action);
void Menu_OnExit();
void Menu_OnKeyDown(int key);
void Menu_OnKeyUp(int key);
void Menu_OnDraw();
void Menu_OnIndicatorDraw();
void Menu_OnTimer();
void Menu_OnPointing(int action, int position);
void Menu_OnAwake();
void Menu_OnSleep();

int mh, ilh;
EAPP_LIST *list = 0;
unsigned int list_size = 0;

unsigned short u16_menu_header[256];
unsigned short u16_menu_soft1[256];
unsigned short u16_menu_soft2[256];
unsigned short u16_menu_soft3[256];

//Действие при создании окна
void Menu_OnInit()
{
 printf("Menu_OnInit\r\n"); 
  
 //Создаём меню
 mh = Forms_Create();
 
 //Устанавливаем текст заголовка
 cp1251_2_utf16(u16_menu_header, "ELF - приложения");
 Forms_SetTitleText(mh, u16_menu_header);
 
 //Устанавливаем высоту заголовка
 Forms_SetTitleHeight(mh, FORM_TITLE_HEIGHT_NORMAL);
 
 //Устанавливаем шрифт заголовка
 Forms_SetTitleFont(mh, FORM_TITLE_FONT_NORMAL);
 
 //Устанавливаем положение меню X / Y
 Forms_SetPosition(mh, 0, STATUSBAR_HEIGHT);

 __pxe_api_imm(0x74/4, 0x10/4, mh, 0xC0000000);
 __pxe_api_imm(0x88/4, 0x08/4, mh, 0x80000000, 0);
 ilh = Forms_CreateList(mh, 0, 0, 0, 0, 0);
  Forms_SetListStyle(ilh, 0x80000000, 0x12060090); // LIST_ICONS_STYLE_DIGITAL
 __pxe_api_imm(0x74/4, 0x14/4, ilh, 0, 0x80000000);
 
 //Устанавливаем coфтклавиши
 cp1251_2_utf16(u16_menu_soft1, "Запуск");
 cp1251_2_utf16(u16_menu_soft2, "Выход");
 cp1251_2_utf16(u16_menu_soft3, "");
 Forms_SetSoftKeys(mh, u16_menu_soft1, u16_menu_soft2, 0);
  
 list = ElfAppsList_Build(&list_size);
 if (list)
  {
   if (list_size)
    {
     for (int i = 0; i < list_size; i++)
      {
       //Добавляем элементы в список
       Forms_AddListItem(ilh, list[i].name, i, 0xFFFF);
      }
    }
  }
}

void Menu_ElfAppRun(int item)
{
 unsigned int start, ret, err;
 err  = elf_load(list[item].fname, 0, 0, 0, &start, &ret);
 printf("ElfLoad \"%s\", Error = %d => 0x%08X, 0x%08X\r\n", list[item].fname, err, start, ret); 
}


void Menu_Close(int action)
{
 TaskMngr_AppExit(0, 0, TASKAPP_EXIT_RETURN);
 Forms_TouchHandling2(mh, action, 0);
 Forms_TouchHandling(mh, 0);
 Graphics_Repaint();
}

//Действие при уничтожении окна
void Menu_OnExit()
{
 printf("Menu_OnExit\r\n");
 ElfAppsList_Free(list);
 
 Timers_DestroyEvent(-1);
 __pxe_api_imm_onearg(0x70/4, 0x04/4, 1);
 Forms_Destroy(mh);
}

//Действие при зажатии настоящией кнопки или рабочей области тачскрина
void Menu_OnKeyDown(int key)
{
 printf("Menu_OnKeyDown key = %d\r\n", key); 
  
 switch (key)
  {
   case KEY_MULTI:
     TaskMngr_ShowTaskList();
     break;
   case KEY_END:
     Menu_Close(key);
     break;
   case THS_SOFT1:
     Menu_ElfAppRun(Forms_GetSelectListItem(ilh));
     break;
   case THS_SOFT2:
     Menu_Close(key);
     break;
   case THS_OTHER:
     Menu_ElfAppRun(Forms_GetSelectListItem(ilh));
     break;
  }
 
 Graphics_Repaint();
}

//Действие при отпускании настоящией кнопки
void Menu_OnKeyUp(int key)
{
 printf("Menu_OnKeyUp key = %d\r\n", key); 
// gui_redraw();
}

/*
//Действие при отрисовке окна
void Menu_OnDraw()
{
  printf("Menu_OnDraw()\r\n");
 __pxe_api_imm_onearg(0xA4/4, 0x10/4, 1);
 __pxe_api_imm_onearg(0xA4/4, 0x38/4, 1);
 gui_form_touchhandling0(mh, 0);
 
 gui_redraw();
}

//Действие при отрисовке статус-бара
void Menu_OnIndicatorDraw()
{
  printf("Menu_OnIndicatorDraw()\r\n");
 __pxe_api_imm_onearg(0xA4/4, 0x10/4, 1);
 __pxe_api_imm_onearg(0xA4/4, 0x38/4, 1);
 gui_form_touchhandling0(mh, 0);
 
 gui_redraw();
}
*/
void Menu_OnDraw()
{
  printf("Menu_OnDraw()\r\n");
 __pxe_api_imm_onearg(0xA4/4, 0x10/4, 1);
 __pxe_api_imm_onearg(0xA4/4, 0x38/4, 1);
 __pxe_api_imm(0x74/4, 0xB4/4, mh, 0);
 
 Graphics_Repaint();
}

void Menu_OnIndicatorDraw()
{
  printf("Menu_OnIndicatorDraw()\r\n");
 __pxe_api_imm_onearg(0xA4/4, 0x10/4, 1);
 __pxe_api_imm_onearg(0xA4/4, 0x38/4, 1);
 __pxe_api_imm(0x74/4, 0xB4/4, mh, 0);
 
 Graphics_Repaint();
}


//Действие при срабатывании таймеров
void Menu_OnTimer(int timer_id, int param)
{
  //printf("Menu_OnTimer: %d / %d\r\n", timer_id, param);
}

//Действие при манипуляциях с тачскрином
void Menu_OnPointing(int action, int position)
{
 int x, y;
 
 x = PXE_LOWORD(position);
 y = PXE_HIWORD(position);
 
 Forms_TouchHandling3(mh, action, x, y, 1);
 Graphics_Repaint();
}


//Действие при активации
void Menu_OnAwake()
{
 printf("Menu_OnAwake()\r\n");
}

//Действие при сворачивании
void Menu_OnSleep()
{
 printf("Menu_OnSleep()\r\n");
}

//Главный обработчик окна WINDOW_ID_MAINMENU от приложения
int Menu_EventHandler(int cmd, int subcmd, int status)
{
 switch (cmd)
  {
   case Window_OnInit:
     Menu_OnInit();
     break;
   case Window_OnExit:
     Menu_OnExit();
     break;
   case Window_OnAwake:
     Menu_OnAwake();
     break;
   case Window_OnSleep:
     Menu_OnSleep();
     break;
   case Window_OnKeyDown:
     Menu_OnKeyDown(subcmd);
     break;
   case Window_OnKeyUp:
     Menu_OnKeyUp(subcmd);
     break;
   case Window_OnDraw:
     Menu_OnDraw();
     break;
   case Window_OnTimer:
     Menu_OnTimer(subcmd, status);
     break;
   case Window_OnPointing:
     Menu_OnPointing(subcmd, status);
     break;
   case Window_OnIndicatorDraw:
     Menu_OnIndicatorDraw();
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
     //Создаём окно
     Windows_Create(WINDOW_ID_MAINMENU, Menu_EventHandler);
     //Запускаем инициализацию окна
     Windows_Init(WINDOW_ID_MAINMENU);
     printf("PXE_RUN_CREATE_EVENT\r\n");
     return 1;
   //Событие при создании приложения
   case PXE_RUN_DESTROY_EVENT:
     //Уничтожаем окно
     Windows_DestroyAll();
     printf("PXE_RUN_DESTROY_EVENT\r\n");
     return 1;
   //Событие при активации приложения 
   case PXE_RUN_RESUME_EVENT:
     printf("PXE_RUN_RESUME_EVENT\r\n");
     //Отправим команду на перерисовку
     Windows_TransEvent(PXE_RUN_PAINT_EVENT, 0, 0);
     return 1;
   //Событие при сворачивании приложения 
   case PXE_RUN_SUSPEND_EVENT:
     printf("PXE_RUN_SUSPEND_EVENT\r\n");
     return 1;
   default:
     //Конвертируем остальные события приложения для окна
     Windows_TransEvent(event_id, wparam, lparam);
     return 1;
  }
}


