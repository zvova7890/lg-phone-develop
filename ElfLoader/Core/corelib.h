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

#pragma swi_number=0x0
__swi __arm unsigned int *swihook_getlib();

#pragma swi_number=0x1
__swi __arm int swihook_setfunc(unsigned short swinum, unsigned int address);

#pragma swi_number=0x2
__swi __arm unsigned int swihook_getfunc(unsigned short swinum);

#pragma swi_number=0x3
__swi __arm int swihook_clearfunc(unsigned short swinum);


/* NOTE: DEPRECATED */
/*
#pragma swi_number=0x4
__swi __arm int ejapi_addapi(char *path);

#pragma swi_number=0x5
__swi __arm int ejapi_removeapi(int handle);

#pragma swi_number=0x6
__swi __arm EJAPI_ITEM *ejapi_getbase();

#pragma swi_number=0x7
__swi __arm int ejapi_getbasesize();


#pragma swi_number=0x8
__swi __arm unsigned char  amem_setbyte(unsigned long address, unsigned char byte);

#pragma swi_number=0x9
__swi __arm unsigned short amem_sethwrd(unsigned long address, unsigned short hwrd);

#pragma swi_number=0xA
__swi __arm unsigned long  amem_setword(unsigned long address, unsigned long word);
*/

#pragma swi_number=0xB
__swi __arm int elf_load(char *filename, void *param1, void *param2, void *param3, unsigned int *start, unsigned int *ret);

#pragma swi_number=0xD
__swi __arm void lclear();

#pragma swi_number=0xE
__swi __arm void lprintf(const char *format, ...);

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

#pragma swi_number=0x20
__swi __arm void *mem_malloc(unsigned int size);

#pragma swi_number=0x21
__swi __arm void  mem_free(void *ptr);

#pragma swi_number=0x22
__swi __arm void *mem_realloc(void *ptr, unsigned int size);

#pragma swi_number=0x23
__swi __arm void *mem_calloc(unsigned int n, unsigned int size);

#pragma swi_number=0x24
__swi __arm void *mem_zmalloc(unsigned int size);

#pragma swi_number=0x25
__swi __arm unsigned int mem_totalsize();

#pragma swi_number=0x26
__swi __arm unsigned int mem_usedsize();

#pragma swi_number=0x27
__swi __arm unsigned int mem_freesize();

#pragma swi_number=0x28
__swi __arm void *mem_getbase();

#pragma swi_number=0x8030
__swi __arm unsigned int *drw_screenbuffer32();

#pragma swi_number=0x8031
__swi __arm unsigned short *drw_screenbuffer16();

#pragma swi_number=0x0060
__swi __arm int accel_sensor_activate();

#pragma swi_number=0x0061
__swi __arm int accel_sensor_is_active();

#pragma swi_number=0x0062
__swi __arm int accel_sensor_position(short *x, short *y, short *z);

#pragma swi_number=0x0063
__swi __arm int accel_sensor_state(short x, short y, short z);

#endif // __CORELIB_H__

