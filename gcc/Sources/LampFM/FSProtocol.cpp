#include "FSProtocol.h"
#include <errno.h>

#define UNUSED(x) ((void)x);

FSProtocol::FSProtocol()
{

}


FSProtocol::~FSProtocol()
{

}


void *FSProtocol::open(const char *f, int mode)
{
    UNUSED(f);
    UNUSED(mode);

    _err = -ENOTSUP;
    return 0;
}


int FSProtocol::read(void *, char *, int )
{
    _err = -ENOTSUP;
    return -1;
}


int FSProtocol::write(void *, const char *, int )
{
    _err = -ENOTSUP;
    return -1;
}


long FSProtocol::fsize(void *)
{
    _err = -ENOTSUP;
    return -1;
}


int FSProtocol::seek(void *, off_t , int )
{
    _err = -ENOTSUP;
    return -1;
}


int FSProtocol::close(void *)
{
    _err = -ENOTSUP;
    return -1;
}


int FSProtocol::unlink(const char *)
{
    _err = -ENOTSUP;
    return -1;
}


int FSProtocol::mkdir(const char *)
{
    _err = -ENOTSUP;
    return -1;
}


int FSProtocol::rmdir(const char *)
{
    _err = -ENOTSUP;
    return -1;
}


void *FSProtocol::opendir(const char *, const char *)
{
    printf("opendir not implemented\n");
    _err = -ENOTSUP;
    return 0;
}


int FSProtocol::readdir(void *, FSProtocol::FSEntry *)
{
    _err = -ENOTSUP;
    return -1;
}


int FSProtocol::closedir(void *)
{
    _err = -ENOTSUP;
    return -1;
}
