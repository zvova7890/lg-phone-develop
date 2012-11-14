#ifndef __EJAPI_H__
#define __EJAPI_H__

#define EJAPI_NULL          0
#define EJAPI_ERROR         -1
#define EJAPI_SUCCESS       1
#define EJAPI_TRUE          "true"


#define EJAPI_HANDLE        400000
#define EJAPI_BASE_SIZE     100000

typedef struct {
  char *(*handler)(char *);
  void   *base;
}EJAPI_ITEM;


#pragma diag_suppress=Ta035


#pragma swi_number=0x4
__swi __arm int ejapi_addapi(char *path);

#pragma swi_number=0x5
__swi __arm int ejapi_removeapi(int handle);

#pragma swi_number=0x6
__swi __arm EJAPI_ITEM *ejapi_getbase();

#pragma swi_number=0x7
__swi __arm int ejapi_getbasesize();


#endif // __EJAPI_H__
