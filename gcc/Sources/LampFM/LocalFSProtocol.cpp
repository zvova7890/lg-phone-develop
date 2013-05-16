#include "LocalFSProtocol.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <fs.h>
#include <string.h>

#include <Api/ApiLinkLib/ApiLink.h>



typedef struct
{
    int fd;
    int pos;
    int size;
}File;

static File fds[128];


void init_fds()
{
    for(int i=0; i<128; ++i)
        fds[i].fd = -1;
}


int allocNewId(int sys_fd)
{
    for(int i=0; i<128; ++i) {
        if(fds[i].fd < 0) {
            fds[i].fd = sys_fd;
            fds[i].pos = 0;
            return i;
        }
    }

    return -1;
}


int freeId(int fd)
{
    if((unsigned int)fd >= 128)
        return -1;

    fds[fd].fd = -1;
    return 0;
}

#define get_fd(id) File *f = 0; if((unsigned)id > 128 || fds[id].fd < 0) return -1; f = &fds[id];


int file_open(const char *file, int mode)
{
    FS_INFO stat;
    memset(&stat, 0, sizeof(stat));
    fs_getinfo(file, &stat);

    int f = fs_open(file, mode);
    if(f < 1) {
        return -1;
    }

    int id = allocNewId(f);
    if(id < 0) {
        fs_close(f);
        return -1;
    }

    fds[id].size = stat.size;

    return id;
}


int file_close(int fd)
{
    get_fd(fd);

    int r = fs_close(f->fd);
    freeId(fd);

    return r;
}


int file_read(int fd, void *data, unsigned size)
{
    get_fd(fd);

    int rd = fs_read(f->fd, data, size);

    if(rd > 0)
        f->pos += rd;

    //printf("read: %d\n", rd);

    return rd;
}


int file_write(int fd, const void *data, unsigned size)
{
    get_fd(fd);

    int rd = fs_write(f->fd, data, size);

    if(rd > 0) {
        f->pos += rd;
        if(f->pos > f->size)
            f->size = f->pos;
    }

    //printf("write: %d\n", rd);

    return rd;
}



int file_seek(int fd, int pos, int type)
{
    get_fd(fd);

    switch(type)
    {
        case SEEK_SET:
            if(!fs_seek(f->fd, SEEK_SET, pos))
                f->pos = pos;
            break;

        case SEEK_CUR:
            if(!fs_seek(f->fd, SEEK_CUR, pos))
                f->pos += pos;
            break;

        case SEEK_END:
            if(!fs_seek(f->fd, SEEK_END, pos))
                f->pos = f->size + pos;
            break;

        default:
            return -1;
    }

    //printf("file_seek: %d\n", f->pos);

    return f->pos;
}


LocalFSProtocol::LocalFSProtocol()
{

}

/*
void *LocalFSProtocol::open(const char *f, int mode)
{
    char m[4] = {0};

    if(mode & FSProtocol::OpenMode::Create &&
       mode & FSProtocol::OpenMode::Trunc) {
        strcpy(m, "w+");

    } else if(mode & FSProtocol::OpenMode::Create) {
        strcpy(m, "ab+");

    } else if(mode & FSProtocol::OpenMode::Write) {
        strcpy(m, "w");
    } else {
        strcpy(m, "r");
    }

    ::FILE *fp = fopen(f, m);
    return fp;
}


int LocalFSProtocol::read(void *f, char *data, int size)
{
    ::FILE *fp = (FILE*)f;
    return fread(data, 1, size, fp);
}


int LocalFSProtocol::write(void *f, const char *data, int size)
{
    ::FILE *fp = (FILE*)f;
    return fwrite(data, 1, size, fp);
}


int LocalFSProtocol::close(void *f)
{
    ::FILE *fp = (FILE*)f;

    return fclose(fp);
}


long LocalFSProtocol::fsize(void *f)
{
    ::FILE *fp = (FILE*)f;

    long off = ftell(fp);

    fseek(fp, 0, SEEK_END);
    int sz = ftell(fp);
    fseek(fp, off, SEEK_SET);

    return sz;
}
*/


void *LocalFSProtocol::open(const char *f, int mode)
{
    int m;
    if(mode & FSProtocol::OpenMode::Create &&
       mode & FSProtocol::OpenMode::Trunc) {
        m = FILE_OPEN_WRITE | FILE_OPEN_CREATE | FILE_OPEN_TRUNCATE;

    } else if(mode & FSProtocol::OpenMode::Create) {
        m = FILE_OPEN_WRITE | FILE_OPEN_CREATE;

    } else if(mode & FSProtocol::OpenMode::Write) {
        m = FILE_OPEN_WRITE;
    } else {
        m = FILE_OPEN_READ;
    }

    printf("Open: %s\n", f);
    int fp = file_open(f, m);
    if(fp < 0)
        return 0;

    return (void*)(fp+1);
}


int LocalFSProtocol::read(void *f, char *data, int size)
{
    int fp = (int)f-1;
    return file_read(fp, data, size);
}


int LocalFSProtocol::write(void *f, const char *data, int size)
{
    int fp = (int)f-1;
    return file_write(fp, data, size);
}


int LocalFSProtocol::close(void *f)
{
    int fp = (int)f-1;
    return file_close(fp);
}


long LocalFSProtocol::fsize(void *f)
{
    int fp = (int)f-1;

    int pos = file_seek(fp, 0, SEEK_CUR);
    int sz = file_seek(fp, 0, SEEK_END);
    file_seek(fp, SEEK_SET, pos);

    return sz;
}


int LocalFSProtocol::rename(const char *old, const char *nw)
{
    return ::rename(old, nw);
}


int LocalFSProtocol::unlink(const char *f)
{
    return ::unlink(f);
}


int LocalFSProtocol::mkdir(const char *d)
{
    return ::mkdir(d, 0777);
}


int LocalFSProtocol::rmdir(const char *d)
{
    return ::rmdir(d);
}


void *LocalFSProtocol::opendir(const char *dir, const char *mask)
{
    ((void)mask);

    long d = fs_opendir(dir);

    if(d > 0) {
        void **r = (void **)malloc(sizeof(void*));
        *r = (void*)d;
        return (void*)r;
    }

    return 0;
}


int LocalFSProtocol::readdir(void *hdir, FSProtocol::FSEntry *entry)
{
    if(!hdir)
        return -1;

    int handle = *(int*)hdir;

    FS_INFO info;
    int r = fs_readdir(handle, &info);

    if(!r) {
        entry->flags = FSProtocol::FSEntryFlags::File;
        entry->name  = info.name;
        entry->size  = info.size;

        if(info.attr & FS_ATTR_FOLDER)
            entry->flags |= FSProtocol::FSEntryFlags::Dir;

        if(info.attr & FS_ATTR_HIDE)
            entry->flags |= FSProtocol::FSEntryFlags::Hidden;

        if(info.attr & FS_ATTR_READONLY) {
            entry->flags |= FSProtocol::FSEntryFlags::Readonly;
            printf("READONLY FUCK \n");
        }

        /*info.attr &= ~FS_ATTR_FOLDER;
        info.attr &= ~FS_ATTR_HIDE;
        info.attr &= ~FS_ATTR_READONLY;

        printf("info.attr(%s): %d\n", info.name, info.attr);*/

    }

    return r;
}


int LocalFSProtocol::closedir(void *hdir)
{
    if(!hdir)
        return -1;

    int handle = *(int*)hdir;
    free(hdir);

    return fs_closedir(handle);
}
