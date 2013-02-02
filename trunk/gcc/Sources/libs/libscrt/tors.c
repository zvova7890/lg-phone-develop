

#include <loader.h>
#include <string.h>
#include <swihelper.h>


/* constructors */
void executeInitializersArray(Elf32_Exec *ex)
{
    if(!ex->dyn[DT_INIT_ARRAY]) return;

    size_t sz = ex->dyn[DT_INIT_ARRAYSZ] / sizeof (void*);
    void ** arr = (void**)(ex->body + ex->dyn[DT_INIT_ARRAY] - ex->v_addr);


    for(int i=0; i < sz; ++i) {
        ( (void (*)())arr[i])();
    }
}



/* destructors */
void executeFinishesArray(Elf32_Exec *ex)
{
    if(!ex->dyn[DT_FINI_ARRAY]) return;

    size_t sz = ex->dyn[DT_FINI_ARRAYSZ] / sizeof (void*);
    void ** arr = (void**)(ex->body + ex->dyn[DT_FINI_ARRAY] - ex->v_addr);

    for(int i=0; i < sz; ++i) {
        ( (void (*)())arr[i])();
    }
}

