#ifndef __FS_H__
#define __FS_H__

#include "swihelper.h"


#define FILE_OPEN_WRITE         0x01
#define FILE_OPEN_READ          0x02
#define FILE_OPEN_CREATE        0x04
#define FILE_OPEN_TRUNCATE      0x08
#define FILE_OPEN_APPEND        0x10

#define FILE_SEEK_SET           0x00
#define FILE_SEEK_CUR           0x01
#define FILE_SEEK_END           0x02

#define FILE_PATH_SYS           "/sys" // ROOT Disc  
#define FILE_PATH_CUS           "/cus" // CUST Disc  
#define FILE_PATH_USR           "/usr" // USER Disc   
#define FILE_PATH_MMC           "/mmc" // MMC (SD/MicroSD) Disc 

#define FS_ATTR_FILE            0x0000
#define FS_ATTR_FOLDER          0x0200
#define FS_ATTR_READONLY        0x0400
#define FS_ATTR_HIDE            0x0800


typedef struct {
   unsigned int size;
   unsigned int attr;
   unsigned int unk0;
   unsigned int unk1;
   unsigned int unk2;
   unsigned int unk3;
   unsigned int unk4;
   unsigned int unk5;
   char         name[260];
} FS_INFO;



__inl
int fs_open(const char *file_path, unsigned short mode)
__def( 0x10, int, file_path, mode)

__inl
int fs_read(int handle, const void *buffer, int size)
__def( 0x11, int, handle, buffer, size)

__inl
int fs_write(int handle, const void *buffer, int size)
__def( 0x12, int, handle, buffer, size)

__inl
int fs_seek(int handle, unsigned char mode, int offset)
__def( 0x13, int, handle, mode, offset)

__inl
int fs_close(int handle)
__def( 0x14, int, handle)

__inl
int fs_unlink(const char *file_path)
__def( 0x15, int, file_path)

__inl
int fs_mkdir(const char *dir_path)
__def( 0x16, int, dir_path)

__inl
int fs_rmdir(const char *dir_path)
__def( 0x17, int, dir_path)

__inl
int fs_opendir(const char *dir_path)
__def( 0x18, int, dir_path)

__inl
int fs_readdir(int handle, FS_INFO *entry)
__def( 0x19, int, handle, entry)

__inl
int fs_closedir(int handle)
__def( 0x1A, int, handle)

__inl
int fs_getinfo(const char *fs_path, FS_INFO *info)
__def( 0x1B, int, fs_path, info)



#endif // __FS_H__

 
