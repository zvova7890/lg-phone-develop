
#ifndef __COMPATIBLE_H__
#define __COMPATIBLE_H__


#ifdef __cplusplus
extern "C" {
#endif



#ifdef __PC_BUILD__


#define TOUCH_ACTION_PRESS 0
#define TOUCH_ACTION_RELEASE 1
#define TOUCH_ACTION_MOVE 2

#include <pxeapi_graphics.h>

void GrSys_Refresh();

int Timer_CreateEvent(int id, int msec, int start_msec);
int Timer_KillEvent(int id);

void TaskMngr_AppExit(int, int, int);

void *Graphics_GetScreenBuffer();
unsigned short Graphics_GetScreenWidth();
unsigned short Graphics_GetScreenHeight();
unsigned char Graphics_GetScreenDepth();

int GrSys_GetGDIID();


#define GRSYS_WIDTH Graphics_GetScreenWidth()
#define GRSYS_HEIGHT Graphics_GetScreenHeight()

#else

#include <pxeapi.h>
#include <pxeapi_timer.h>
#include <Api/ApiLinkLib/ApiLink.h>

#endif

#define TOUCH_ACTION_LONGPRESS 3



#define BUGON(expr) if(!expr) { \
    printf("BUGON %s[%d]: '%s'\n", __FILE__, __LINE__, ""#expr); \
}



#ifdef __cplusplus
}
#endif

#endif /* __COMPATIBLE_H__ */

