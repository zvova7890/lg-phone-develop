#include "FSProtocol.h"
#include <errno.h>

#define UNUSED(x) ((void)x);

FSProtocol FSProtocol::null;
FSEntryInfo FSEntryInfo::null;


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

    m_err = -ENOTSUP;
    return 0;
}


int FSProtocol::read(void *, char *, int )
{
    m_err = -ENOTSUP;
    return -1;
}


int FSProtocol::write(void *, const char *, int )
{
    m_err = -ENOTSUP;
    return -1;
}


long FSProtocol::fsize(void *)
{
    m_err = -ENOTSUP;
    return -1;
}


int FSProtocol::seek(void *, off_t , int )
{
    m_err = -ENOTSUP;
    return -1;
}


int FSProtocol::close(void *)
{
    m_err = -ENOTSUP;
    return -1;
}


int FSProtocol::unlink(const char *)
{
    m_err = -ENOTSUP;
    return -1;
}


int FSProtocol::mkdir(const char *)
{
    m_err = -ENOTSUP;
    return -1;
}


int FSProtocol::rmdir(const char *)
{
    m_err = -ENOTSUP;
    return -1;
}


void *FSProtocol::opendir(const char *, const char *)
{
    printf("opendir not implemented\n");
    m_err = -ENOTSUP;
    return 0;
}


int FSProtocol::readdir(void *, FSProtocol::FSEntry *)
{
    m_err = -ENOTSUP;
    return -1;
}


int FSProtocol::closedir(void *)
{
    m_err = -ENOTSUP;
    return -1;
}
