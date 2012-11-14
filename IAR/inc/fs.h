#ifndef __FS_H__
#define __FS_H__

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



#pragma diag_suppress=Ta035


#pragma swi_number=0x10
__swi __arm int fs_open(const char *file_path, unsigned short mode);

#pragma swi_number=0x11
__swi __arm int fs_read(int handle, const void *buffer, int size);

#pragma swi_number=0x12
__swi __arm int fs_write(int handle, const void *buffer, int size);

#pragma swi_number=0x13
__swi __arm int fs_seek(int handle, unsigned char mode, int offset);

#pragma swi_number=0x14
__swi __arm int fs_close(int handle);

#pragma swi_number=0x15
__swi __arm int fs_unlink(const char *file_path);

#pragma swi_number=0x16
__swi __arm int fs_mkdir(const char *dir_path);

#pragma swi_number=0x17
__swi __arm int fs_rmdir(const char *dir_path);

#pragma swi_number=0x18
__swi __arm int fs_opendir(const char *dir_path);

#pragma swi_number=0x19
__swi __arm int fs_readdir(int handle, FS_INFO *entry);

#pragma swi_number=0x1A
__swi __arm int fs_closedir(int handle);

#pragma swi_number=0x1B
__swi __arm int fs_getinfo(const char *fs_path, FS_INFO *info);

#pragma swi_number=0x1C
__swi __arm int fs_rename(const char *fs_path, const char *newname);

#endif // __FS_H__

