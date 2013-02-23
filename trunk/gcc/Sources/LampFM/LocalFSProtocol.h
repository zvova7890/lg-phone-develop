#ifndef LOCALFSPROROCOL_H
#define LOCALFSPROROCOL_H


#include "FSProtocol.h"


class LocalFSProtocol : public FSProtocol
{
public:

    void *open(const char *f, int mode);
    int unlink(const char *f);
    int mkdir(const char *d, bool recursive = false);
    int rmdir(const char *d, bool recursive = false);
};


#endif // LOCALFSPROROCOL_H
