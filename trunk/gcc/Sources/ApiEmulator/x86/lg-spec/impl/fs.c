
#define _BSD_SOURCE
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <fs.h>
#include <stdio.h>



typedef struct
{
    DIR *d;
    char dir_name[256];
}MY_DIR;

static MY_DIR dirs[128];



__attribute__((constructor))
static void dirst_init()
{
    memset(&dirs, 0, sizeof(dirs));
}


static int findEmpty()
{
    for(int i=1; i<128; ++i) {

        if(!dirs[i].d)
            return i;
    }

    return -1;
}



static int newEntry(DIR *d, const char *name)
{
    int id = findEmpty();
    if(id > -1) {
        dirs[id].d = d;
        strcpy(dirs[id].dir_name, name);
    }

    return id;
}


static MY_DIR *getDir(int i) {

    if(i< 0 || i>=128)
        return 0;

    return &dirs[i];
}



int fs_open(const char *file_path, unsigned short mode)
{
    int md = 0;

    if(mode & FILE_OPEN_CREATE)
        md |= O_CREAT;

    if(mode & FILE_OPEN_APPEND)
        md |= O_APPEND;

    //if(mode & FILE_OPEN_READ && !(mode & FILE_OPEN_WRITE))
        //md |= O_RDONLY;

    //if(mode & FILE_OPEN_WRITE && !(mode & FILE_OPEN_READ))
      //  md |= O_RDONLY;

    if(mode & FILE_OPEN_READ && mode & FILE_OPEN_WRITE)
        md |= O_RDWR;

    if(mode & FILE_OPEN_CREATE && (!(md & O_WRONLY) || !(md & O_RDWR)))
        md |= O_WRONLY;

    if(mode & FILE_OPEN_TRUNCATE)
        md |= O_TRUNC;

    return open(file_path, md);
}


int fs_read(int handle, void *buffer, int size)
{
    return read(handle, buffer, size);
}


int fs_write(int handle, const void *buffer, int size)
{
    return write(handle, buffer, size);
}

int fs_seek(int handle, unsigned char mode, int offset)
{
    return lseek(handle, offset, mode) < 0;
}

int fs_close(int handle)
{
    return close(handle);
}


int fs_getinfo(const char *fs_path, FS_INFO *info)
{
    struct stat s;
    if(!stat(fs_path, &s)) {
        info->size = s.st_size;
        info->attr = s.st_mode &S_IFDIR? FS_ATTR_FOLDER : FS_ATTR_FILE;

        return 0;
    }

    return -1;
}


int fs_unlink(const char *file_path)
{
    return unlink(file_path) == 0;
}


int fs_mkdir(const char *dir_path)
{
    return mkdir(dir_path, 777) == 0;
}


int fs_rmdir(const char *dir_path)
{
    return rmdir(dir_path) == 0;
}


int fs_opendir(const char *dir_path)
{
    DIR *d = opendir(dir_path);
    if(!d)
        return -1;

    int i = newEntry(d, dir_path);
    if(i < 0) {
        closedir(d);
    }

    return i;
}


int fs_readdir(int handle, FS_INFO *entry)
{
    MY_DIR *d = getDir(handle);
    if(!d)
        return -1;

    struct dirent *di = readdir(d->d);
    if(entry && di) {

        strcpy(entry->name, di->d_name);

        char filename[512];
        sprintf(filename, "%s/%s", d->dir_name, entry->name);

        struct stat st;
        stat(filename, &st);
        entry->size = st.st_size;

        if(di->d_type & DT_DIR)
            entry->attr = FS_ATTR_FOLDER;
        else
            entry->attr = FS_ATTR_FILE;

        return 0;
    }

    return 1;
}


int fs_closedir(int handle)
{
    MY_DIR *d = getDir(handle);
    if(!d)
        return -1;


    return 0;
}



