#include "LocalFSProtocol.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <fs.h>



LocalFSProtocol::LocalFSProtocol()
{

}


void *LocalFSProtocol::open(const char *f, int mode)
{
    char m[4] = {0};
    int at = 0;

    // FIXME
    if(mode & FSProtocol::OpenMode::Read)
        m[at++] = 'r';

    if(mode & FSProtocol::OpenMode::Write)
        m[at++] = 'w';

    if(mode & FSProtocol::OpenMode::Create)
        m[at++] = '+';

    if(mode & FSProtocol::OpenMode::Trunc) {
        m[0] = 'w';
        m[1] = '+';
        m[3] = 0;
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
