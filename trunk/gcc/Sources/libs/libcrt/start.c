

#include <loader.h>


void *DefaultGLContext;

static int _destroyed = 0;

void executeInitializersArray(Elf32_Exec *ex);
void executeFinishesArray(Elf32_Exec *ex);
void __destroy_dtors_list(void *ex);


extern int main(int argc, char *argv[]);


int _start(int argc, char *argv[])
{
    extern void *__ex;
    Elf32_Exec *ex = (Elf32_Exec *)&__ex;

    executeInitializersArray(ex);

    return main(argc, argv);
}


void ElfDestroy()
{
    if(_destroyed)
        return;

    _destroyed = 1;

    extern void *__ex;
    Elf32_Exec *ex = (Elf32_Exec *)&__ex;

    __destroy_dtors_list((void*)ex);
    executeFinishesArray(ex);
    elfclose(ex);
}
