#ifndef FSPROTOCOL_H
#define FSPROTOCOL_H

#include <map>
#include <string>
#include <FSEntryInfo.h>


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


    struct FSEntry{
    public:

        FSEntry() :
            flags(0),
            size(0),
            ctime(0) {
        }

        FSEntry(const FSEntryInfo &info) {
            name = info.name;
            flags = info.attr;
            size = info.size;
            ctime = 0;

            if(flags & Dir && name[name.length()-1] == '/') {
                name.erase(name.length()-1, 1);
            }
        }

        std::string name;
        int flags;
        unsigned int size;
        unsigned ctime;
    };


public:
    FSProtocol();
    virtual ~FSProtocol();

    virtual void *open(const char *f, int mode);
    virtual int read(void *, char *data, int size);
    virtual int write(void *, const char *data, int size);
    virtual long fsize(void *);
    virtual int seek(void *, off_t offset, int mode);
    virtual int close(void *);

    virtual int unlink(const char *f);

    virtual int mkdir(const char *d);
    virtual int rmdir(const char *d);


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
