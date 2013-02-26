



#ifdef _USE_MZ80
#include "mz80/mz80.c"

#elif _USE_CZ80
#include "cz80/cz80.c"

#elif _USE_DRZ80
#warning include drz80 asm file

#else
#error You must define some of this z80 cpus!
#endif


