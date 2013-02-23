#ifndef LOCALFSPROROCOL_H
#define LOCALFSPROROCOL_H


#include "FSProtocol.h"


class LocalFSProtocol : public FSProtocol
{
public:

    LocalFSProtocol();

    void *open(const char *f, FSProtocol::OpenMode mode);
    int unlink(const char *f);
    int mkdir(const char *d, bool recursive = false);
    int rmdir(const char *d, bool recursive = false);

    void *opendir(const char *dir, const char *mask);
    int readdir(void *hdir, FSEntry *);
    int closedir(void *hdir);
};


#endif // LOCALFSPROROCOL_H
