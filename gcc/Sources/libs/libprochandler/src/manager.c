

#include <Api/ApiLinkLib/ApiLink.h>
#include <access.h>
#include <stdio.h>
#include <string.h>
#include <loader.h>
#include <prochandler.h>
#include "logger.h"


extern ProcHandlerStruct handlers[56];
extern unsigned int hook_data[];
extern unsigned int hook_addr[];
extern unsigned int bxlr[];
extern void test_func();
short save[10];


#define HOOK_AT 0x46575772



unsigned long name_hash(const unsigned short *name)
{
    unsigned long hash = 0;
    unsigned long hi;
    /* два раза *name требует больше времени */
    register unsigned short c = *name++;

    while (c != '\0')
    {
        hash = (hash << 4) + c;
        hi = hash & 0xf0000000;
        hash ^= hi;
        hash ^= hi >> 24;

        c = *name++;
    }
    return hash;
}



ProcHandlerStruct *allocHandler()
{
    for(int i=0; i<56; ++i) {

        if(handlers[i].id < 0) {
            handlers[i].id = i;
            return &handlers[i];
        }
    }

    return 0;
}


void freeHandler(int id)
{
    if(id < 0 || id >= 56)
        return;

    handlers[id].id = -1;
}



int getHandlerByName(const unsigned short *name, int len)
{
    unsigned long hash = name_hash(name);
    for(int i=0; i<56; ++i) {

        if(handlers[i].id > -1) {

            //printf("len: %d == %d\n", handlers[i].name_len, len);
            //printf("name_hash: %d == %d\n", handlers[i].name_hash, hash);

            if(handlers[i].name_len == len &&
                    handlers[i].name_hash == hash &&
                    !memcmp(handlers[i].name, name, len*2)) {

                return i;
            }
        }
    }

    return -1;
}



ProcHandlerStruct *proc_handler_hook(int id)
{
    if(id < 0 || id >= 56)
        return 0;

    return &handlers[id];
}



int proc_handler_install_hook(const unsigned short name[128], char replace,
                            void (*init)(void *),
                            int (*listener)(unsigned long, unsigned long, unsigned long),
                            void (*hook_at_erase)(int))
{
    unsigned long _name_hash = name_hash((unsigned short *)name);
    unsigned long _name_len = UniLib_Strlen((U_CHAR*)name);
    ProcHandlerStruct *h = 0;

    int fd = getHandlerByName(name, _name_len);
    if(fd > -1 && !replace) {
        printf("ProcHacker_InstallHook: Hook already installed\n");
        return -1;

    } else if(fd > -1) {

        h = proc_handler_hook(fd);
        if(h && h->hook_erasing)
            h->hook_erasing(h->id);
    }


    if(!h)
        h = allocHandler();

    if(!h)  {
        printf("ProcHacker_InstallHook: No more handlers available\n");
        return -2;
    }


    memset(h, 0, sizeof(*h));
    h->init = init;
    h->listener = listener;
    h->name_hash = _name_hash;
    h->name_len = _name_len;
    h->hook_erasing = hook_at_erase;
    h->enabled = 1;

    memcpy(h->name, name, _name_len*2);

    return h->id;
}


int proc_handler_enable_hook(int id)
{
    if(id < 0 || id >= 56)
        return -1;

    ProcHandlerStruct *h = &handlers[id];
    h->enabled = 1;
    return 0;
}


int proc_handler_disable_hook(int id)
{
    if(id < 0 || id >= 56)
        return -1;

    ProcHandlerStruct *h = &handlers[id];
    h->enabled = 0;
    return 0;
}


int proc_handler_erase_hook(int id)
{
    if(id < 0 || id >= 56)
        return -1;

    ProcHandlerStruct *h = &handlers[id];
    if(h->hook_erasing)
        h->hook_erasing(id);

    h->id = -1;
    return 0;
}


ProcHandlerStruct *lookup(const unsigned short *name, int len)
{
    int h = getHandlerByName(name, len);
    if(h > -1) {
        return &handlers[h];
    }

    return 0;
}


void logger(TProcessCI *tproc, BOOL individual)
{
    int len = UniLib_Strlen(tproc->pszAppName);

    char lol[256];
    UniLib_UCS2ToUTF8(tproc->pszAppName, lol);
    printf("Create Process %s, individual = %s\n", lol, individual==TRUE? "true" : "false");


    ProcHandlerStruct *h = lookup(tproc->pszAppName, len);
    if(!h || !h->enabled)
        return;

    memcpy(&h->tproc, tproc, sizeof *tproc);
    h->old_init = tproc->PxeInitAddr;
    h->old_listener = tproc->PxeRunAddr;

    tproc->PxeInitAddr = h->init;
    tproc->PxeRunAddr = h->listener;

    printf("Handler replaced!\n");
}




__attribute__((noinline))
void install_hook()
{
    unlock_mem_access();

    memcpy(save, (void*)HOOK_AT, 10);
    hook_addr[0] = ((unsigned int)test_func);
    memcpy((void*)HOOK_AT, hook_data, 10);

    lock_mem_access();
}


__attribute__((noinline))
void remove_hook()
{
    unlock_mem_access();
    memcpy((void*)HOOK_AT, save, 10);
    lock_mem_access();
}


