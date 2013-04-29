
#ifndef __INC_CORE_H__
#define __INC_CORE_H__


#ifdef __cplusplus
extern "C" {
#endif



#ifdef __PC_BUILD__


#define TOUCH_ACTION_PRESS 0
#define TOUCH_ACTION_RELEASE 1
#define TOUCH_ACTION_MOVE 2


void GrSys_Refresh();

int Timer_CreateEvent(int id, int msec, int start_msec);
int Timer_KillEvent(int id);

void TaskMngr_AppExit(int, int, int);

#else

#include <pxeapi.h>
#include <pxeapi_timer.h>

#endif

#define TOUCH_ACTION_LONGPRESS 3



#define BUGON(expr) if(!expr) { \
    printf("BUGON %s[%d]: '%s'\n", __FILE__, __LINE__, ""#expr); \
}



#ifdef __cplusplus
}
#endif

#endif /* __INC_CORE_H__ */

