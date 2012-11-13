#ifndef __PXEAPI_H__
#define __PXEAPI_H__

#define SWINUM_GETPXEAPI       0x30

#define PXEAPI_SIZE            0x4000
#define PXEAPI_BASE            0x00400000


unsigned int **__pxeapi_getlib();

int __pxeapi_init();


#endif // __PXEAPI_H__
