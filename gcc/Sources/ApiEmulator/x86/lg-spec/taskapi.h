#ifndef ___TASKAPI_H___
#define ___TASKAPI_H___


/* *****************************************************************************

 В этом файле представлено API для работы c задачами, найденное в LG KP501 V10H_00.
 Найдено и оформлено:
  Шамаев Дамир aka Dimadze

  TASKAPI_EXTERN
  Для самостоятельного задания строчки имени для определения адреса API.
  Дополнительно нужно создать строку где-нибудь:
  const unsigned short __task_api_name_extern[]=TASKAPI_NAME;
  Всё описанное применительно к IAR 4.xx, так как может случиться баг линковки

***************************************************************************** */

#define TASKAPI_NAME L"TaskApi"



typedef struct {
    int            app0;
    int            app1;
    int            app2;
    int            app3;
    unsigned int   *pxo_header;
    int            app4[10];
    unsigned short fname[32];
    int            app5[15];

}PxoApplicationData;


#define TASKAPP_EXIT_RETURN   0
#define TASKAPP_EXIT_TOIDLE   3

/* Task API */

//Вызов диспетчера задач
#define TaskMngr_Show() 

#ifdef __cplusplus
extern "C" {
#endif

int TaskMngr_AppRun(const unsigned short *virt_path, int param);
int TaskMngr_AppRunOpt(const unsigned short *virt_path, int param1, int param2, int mode);
int TaskMngr_AppExit(int arg0, int arg1, int goto_after_type);
int TaskMngr_AppRegister(int handle);
int TaskMngr_AppSetName(int handle, int name, int name1, int name2);



#ifdef __cplusplus
}
#endif

#endif // ___TASKAPI_H___

