

#ifndef __CMD_H__
#define __CMD_H__

#include <Api/ApiLinkLib/BasicApiLib.h>


void CMD_MyMusic();
void CMD_VoiceRecorder();
H_PROCESS CMD_Pxo(const wchar_t *pxo);
void CMD_NewMail();
H_PROCESS CMD_Exec(int cmd);
H_PROCESS CMD_ResetSettings(int cmd);



#endif
