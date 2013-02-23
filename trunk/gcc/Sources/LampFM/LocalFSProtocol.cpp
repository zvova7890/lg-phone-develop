#include "LocalFSProtocol.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <fs.h>



LocalFSProtocol::LocalFSProtocol()
{

}


void *LocalFSProtocol::open(const char *f, FSProtocol::OpenMode mode)
{
    char m[4] = {0};
    int at = 0;

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


int LocalFSProtocol::unlink(const char *f)
{
    return ::unlink(f);
}


int LocalFSProtocol::mkdir(const char *d, bool recursive)
{
    if(!recursive)
        return ::mkdir(d, 0777);

    return -1;
}


int LocalFSProtocol::rmdir(const char *d, bool recursive)
{
    if(!recursive)
        return ::rmdir(d);

    return -1;
}


void *LocalFSProtocol::opendir(const char *dir, const char *mask)
{
    ((void)mask);

    int d = fs_opendir(dir);

    printf("LocalFSProtocol::opendir: %d\n", d);

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
