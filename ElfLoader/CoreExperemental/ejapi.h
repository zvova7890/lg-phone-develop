#ifndef __EJAPI_H__
#define __EJAPI_H__


#define EJAPI_PREFIX_LEN    6
#define EJAPI_HEAD          "ejapi."
#define EJAPI_AVAIL         "ejapi.avail"
#define EJAPI_VER           "ejapi.ver"

#define EJAPI_OPEN          "ejapi.open."
#define EJAPI_OPEN_LEN      11
#define EJAPI_CLOSE         "ejapi.close."
#define EJAPI_CLOSE_LEN     12

#define EJAPI_RUN           "ejapi.run."
#define EJAPI_RUN_LEN       10

#define EJAPI_TRUE          "true"
#define EJAPI_PERCD         "%d"
#define EJAPI_PERSS         "%s/%s"
#define EJAPI_NULL          0
#define EJAPI_ERROR         -1
#define EJAPI_SUCCESS       1

#define EJAPI_HANDLE        400000
#define EJAPI_BASE_SIZE     100000

#define SWINUM_EJAPIADD     0x04
#define SWINUM_EJAPIREM     0x05
#define SWINUM_EJAPIGET     0x06
#define SWINUM_EJAPIGSZ     0x07


typedef struct {
  char *(*handler)(char *);
  void *base;
}EJAPI_ITEM;

char *__ejapi_handler(char *key);
void __ejapi_init(char *ejapi_folder);

int __ejapi_addapi(char *path);
int __ejapi_removeapi(int handle);
EJAPI_ITEM *__ejapi_getbase();
int __ejapi_getbasesize();

extern void __ejapi_patch();


#endif // __EJAPI_H__
