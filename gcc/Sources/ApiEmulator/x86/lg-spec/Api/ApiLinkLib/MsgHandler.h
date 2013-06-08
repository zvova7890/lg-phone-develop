
#ifndef __MSG_HANDLER_H__
#define __MSG_HANDLER_H__

#include "Types.h"
#include "MsgDef.h"


typedef int (*MsgHandler_Callback)(unsigned long, unsigned long, unsigned long);


#ifdef __cplusplus
extern "C" {
#endif

int MsgHandler_RegisterProcessor(T_ID id, MsgHandler_Callback cb);
int MsgHandler_SetActivePID(T_ID id);
int MsgHandler_InsertActivePID(T_ID id);
BOOL MsgHandler_RemoveActiveProcessor();
int MsgHandler_Terminate();
unsigned long MsgHandler_GetParam(int id);
void MsgHandler_SetParam(int id, unsigned long);

int MsgHandler_SendMessage(T_ID, unsigned long, unsigned long, unsigned long);
int MsgHandler_Translate(unsigned long, unsigned long, unsigned long);
int MsgHandler_FlushMessage(T_ID );


#ifdef __cplusplus
}
#endif

#endif

