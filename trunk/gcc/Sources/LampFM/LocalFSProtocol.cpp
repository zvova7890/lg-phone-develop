#include "LocalFSProtocol.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>





void *LocalFSProtocol::open(const char *f, int mode)
{
    char m[4] = {0};
    int at = 0;

    if(mode & FSProtocol::Mode::READ)
        m[at++] = 'r';

    if(mode & FSProtocol::Mode::WRITE)
        m[at++] = 'w';

    if(mode & FSProtocol::Mode::CREATE)
        m[at++] = '+';

    if(mode & FSProtocol::Mode::TRUNC) {
        m[0] = 'w';
        m[1] = '+';
        m[3] = 0;
    }


    FILE *fp = fopen(f, m);
    return fp;
}


int LocalFSProtocol::unlink(const char *f)
{
    return ::unlink(f);
}


int LocalFSProtocol::mkdir(const char *d, bool recursive)
{
    return ::mkdir(d, 0777);
}


int LocalFSProtocol::rmdir(const char *d, bool recursive)
{
    return ::rmdir(d);
}
