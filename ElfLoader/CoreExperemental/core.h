#ifndef __CORE_H__
#define __CORE_H__

#define CORE_LOG "core.log"
#define CORE_LIB "core.lib"

#define SWINUM_LCLEAR  0x0D
#define SWINUM_LPRINTF 0x0E

const char *__core_getelffile();
const char *__core_getlibfile();
const char *__core_getfolder();
const char *__core_getcomfolder();
const char *__core_getversion();
const void *__core_getbase();

void __core_lclear();
void __core_lprintf(const char *format, ...);

#endif // __CORE_H__
