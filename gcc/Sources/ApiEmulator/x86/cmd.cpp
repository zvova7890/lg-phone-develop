
#include <Api/ApiLinkLib/ApiLink.h>
#include "cmd.h"




int __compile_me_fast = 0x22E00000;



void CMD_MyMusic()
{
#ifndef __PC_BUILD__
    H_SHAREDMEM h = ShMem_GetHandle(L"TaskApi");
    void **d = (void**)ShMem_GetMem(h);

    H_PROCESS proc = App_RunEx(L"LGAPP/Pxo/MyMusic.pxo", 0, 0, 1);

    void *f3 = d[0x38/4];
    ((int (*)(int))f3)( (int) proc );

    T_CMD_INFO *tcinfo = T_CMD_ALLOC(0x8);
    T_CMD_MEMSET(tcinfo, 0, 0x8);

    tcinfo->Msg = 1;

    typedef struct {
        int unk0;
        int unk1;
    }Unk_MsgStruct;

    Unk_MsgStruct *unk = (Unk_MsgStruct*)(tcinfo->Param);
    unk->unk0 = 0;
    unk->unk1 = 1;

    EvHandler_PostEvent(proc, 329800, 0, (int)tcinfo);
#endif
}



void CMD_VoiceRecorder()
{
#ifndef __PC_BUILD__
    H_SHAREDMEM h = ShMem_GetHandle(L"TaskApi");
    void **d = (void**)ShMem_GetMem(h);

    H_PROCESS proc = App_RunEx(L"LGAPP/Pxo/VoiceRecorder.pxo", 0, 0, 1);

    void *f3 = d[0x38/4];
    ((int (*)(int))f3)( (int) proc );

    T_CMD_INFO *tcinfo = T_CMD_ALLOC(0x8);
    T_CMD_MEMSET(tcinfo, 0, 0x8);

    tcinfo->Msg = 1;

    typedef struct {
        int unk0;
        int unk1;
    }Unk_MsgStruct;

    Unk_MsgStruct *unk = (Unk_MsgStruct*)(tcinfo->Param);
    unk->unk0 = 0;
    unk->unk1 = 1;

    EvHandler_PostEvent(proc, 100200, 0, (int)tcinfo);
#endif
}




H_PROCESS CMD_Pxo(const wchar_t *pxo)
{
#ifndef __PC_BUILD__
    H_SHAREDMEM h = ShMem_GetHandle(L"TaskApi");
    void **d = (void**)ShMem_GetMem(h);

    wchar_t def[256] = L"LGAPP/Pxo/";
    UniLib_Strcat(def, pxo);

    H_PROCESS proc = App_RunEx(def, 0, 0, 1);

    void *f3 = d[0x38/4];
    ((int (*)(int))f3)( (int) proc );

    return proc;
#endif
}



void CMD_NewMail()
{
#ifndef __PC_BUILD__
    H_SHAREDMEM h = ShMem_GetHandle(L"TaskApi");
    void **d = (void**)ShMem_GetMem(h);

    H_PROCESS proc = App_RunEx(L"LGAPP/Pxo/EmailComposer.pxo", 0, 0, 1);

    void *f3 = d[0x38/4];
    ((int (*)(int))f3)( (int) proc );

    T_CMD_INFO *tcinfo = T_CMD_ALLOC(0x1C);
    T_CMD_MEMSET(tcinfo, 0, 0x1C);

    tcinfo->Msg = 0x12D;

    typedef struct {
        int unk0;
        int unk1;
        int unk2;
        int unk3;
        int unk4;
        char unk5;
    }Unk_MsgStruct;

    Unk_MsgStruct *unk = (Unk_MsgStruct*)(tcinfo->Param);
    unk->unk0 = 0;
    unk->unk1 = 0;
    unk->unk2 = 0;
    unk->unk3 = 0;
    unk->unk4 = 0;
    unk->unk5 = 0;


    EvHandler_PostEvent(proc, 0x19640, 0, (int)tcinfo);
#endif
}


H_PROCESS CMD_Exec(int cmd)
{
#ifndef __PC_BUILD__
    H_SHAREDMEM h = ShMem_GetHandle(L"TaskApi");
    void **d = (void**)ShMem_GetMem(h);

    void *f = d[0x6c/4];

    int r =  ((int (*)(int, int))f)(cmd, 1);

    void *f2 = d[0x68/4];
    H_PROCESS r1 = ((H_PROCESS (*)(int, int, int))f2)(cmd, r, 1);

    if(r1 == 0) {
        void *f3 = d[0x38/4];
        ((int (*)(int))f3)(cmd);
    }

    return r1;
#endif
}


H_PROCESS CMD_ResetSettings(int cmd)
{
#ifndef __PC_BUILD__
    H_SHAREDMEM h = ShMem_GetHandle(L"TaskApi");
    void **d = (void**)ShMem_GetMem(h);

    void *f = d[0x6c/4];

    int r =  ((int (*)(int, int))f)(cmd, 1);

    void *f2 = d[0x68/4];
    H_PROCESS r1 = ((H_PROCESS (*)(int, int, int))f2)(cmd, r, 1);

    if(r1 != 0) {
        void *f3 = d[0x38/4];
        ((int (*)(int))f3)((int)r1);
    }

    return r1;
#endif
}
