


#ifdef EMU_F68K // FAME 68000
#include "fame/famec.c"

#elif EMU_C68K // Cyclone 68000
//#include "Cyclone/Cyclone.S"

#elif EMU_M68K // MUSASHI 68000
#include "musashi/m68kcpu.c"
#include "musashi/m68kops.c"


#else
#error You must define some of this cpus!
#endif

