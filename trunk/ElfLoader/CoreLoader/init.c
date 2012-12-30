#include "fwlib.h"
#include "init.h"
#include "elf.h"


__thumb void init_main()
{
 elfload(CORE_PATH, (void *)&fw, 0, 0);
}

