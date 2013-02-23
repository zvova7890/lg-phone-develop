#ifndef FSPROTOCOL_H
#define FSPROTOCOL_H

#include <map>
#include <string>


class FSProtocol
{
public:

    enum OpenMode {
        Read = (1 << 1),
        Write = (1 << 2),
        Create = (1 << 3),
        Trunc = (1 << 4)
    };


    enum FSEntryFlags {
        File = 0,
        Dir = (1 << 1),
        Hidden = (1 << 2),
        Readonly = (1 << 3),
        Archived = (1 << 4)
    };


    typedef struct {
        std::string name;
        int flags;
        unsigned int size;
    }FSEntry;


public:
    FSProtocol();
    virtual ~FSProtocol();

    virtual void *open(const char *f, OpenMode mode);
    virtual int read(void *, char *data, int size);
    virtual int write(void *, const char *data, int size);
    virtual int close(void *);

    virtual int unlink(const char *f);

    virtual int mkdir(const char *d, bool recursive = false);
    virtual int rmdir(const char *d, bool recursive = false);


    virtual void *opendir(const char *dir, const char *mask);
    virtual int readdir(void *hdir, FSEntry *);
    virtual int closedir(void *hdir);

    int error() {
        return _err;
    }

private:
    int _err;
};






class FSProtocolsContainer
{
public:

    ~FSProtocolsContainer() {
        for(auto c : _protocols)
        {
            delete c.second;
        }
    }

    void pushProtocol(const std::string &name, FSProtocol *p) {
        _protocols[name] = p;
    }


    FSProtocol & indexOf(const std::string &name) {
        auto p = _protocols[name];
        return p? *p : __null_protocol;
    }



private:
    FSProtocol __null_protocol;
    std::map <std::string, FSProtocol *> _protocols;
};


#endif // FSPROTOCOL_H
