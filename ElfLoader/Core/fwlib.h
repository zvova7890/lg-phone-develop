#ifndef __FWLIB_H__
#define __FWLIB_H__

#define FILE_OPEN_WRITE         0x01
#define FILE_OPEN_READ          0x02
#define FILE_OPEN_CREATE        0x04
#define FILE_OPEN_TRUNCATE      0x08
#define FILE_OPEN_APPEND        0x10

#define FILE_SEEK_SET      0x00
#define FILE_SEEK_CUR      0x01
#define FILE_SEEK_END      0x02

#define FILE_PATH_SYS     "/sys" // ROOT Disc  
#define FILE_PATH_CUS     "/cus" // CUST Disc  
#define FILE_PATH_USR     "/usr" // USER Disc   
#define FILE_PATH_MMC     "/mmc" // MMC (SD/MicroSD) Disc 

typedef struct {
  int   (*open)(const char *file_path, unsigned int mode);
  int   (*read)(int handle, const void *buffer, int size);
  int   (*write)(int handle, const void *buffer, int size);
  int   (*seek)(int handle, unsigned char mode, int offset);
  int   (*close)(int handle);
  int   (*unlink)(const char *file_path);
  
  void *(*malloc)(unsigned int size);
  void  (*free)(void *ptr);
} FWLIB;

extern FWLIB *fwlib;

#endif // __FWLIB_H__
