#ifndef __CORELIB_H__
#define __CORELIB_H__

#ifndef _NULL
#define _NULL 0
#endif

#ifndef NULL
#define NULL   _NULL
#endif /* NULL */

#define __int8  char
#define __int16 short
#define __int32 long

#include "swi.h"
#include "elf.h"
#include "ejapi.h"
#include "fs.h"
#include "mem.h"
#include "amem.h"
#include "log.h"
#include "const.h"
#include "nucleus.h"

#endif // __CORELIB_H__

