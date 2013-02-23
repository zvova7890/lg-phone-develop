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


int FSProtocol::mkdir(const char *, bool )
{
    _err = -ENOTSUP;
    return -1;
}


int FSProtocol::rmdir(const char *, bool )
{
    _err = -ENOTSUP;
    return -1;
}
