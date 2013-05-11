#ifndef LOCALFSPROROCOL_H
#define LOCALFSPROROCOL_H


#include "FSProtocol.h"


class LocalFSProtocol : public FSProtocol
{
public:

    LocalFSProtocol();

    void *open(const char *f, int mode);
    int read(void *, char *data, int size);
    int write(void *, const char *data, int size);
    int close(void *);
    long fsize(void *);

    int rename(const char *old, const char *nw);
    int unlink(const char *f);
    int mkdir(const char *d);
    int rmdir(const char *d);

    void *opendir(const char *dir, const char *mask);
    int readdir(void *hdir, FSEntry *);
    int closedir(void *hdir);
};


#endif // LOCALFSPROROCOL_H
