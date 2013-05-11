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

    virtual int rename(const char *old, const char *nw);
    virtual int unlink(const char *f);
    virtual int mkdir(const char *d);
    virtual int rmdir(const char *d);


    virtual void *opendir(const char *dir, const char *mask);
    virtual int readdir(void *hdir, FSEntry *);
    virtual int closedir(void *hdir);

    int error() {
        return m_err;
    }

private:
    int m_err;
    
public:
    static FSProtocol null;
};






class FSProtocolsContainer
{
public:

    ~FSProtocolsContainer() {
        for(auto c : m_protocols)
        {
            delete c.second;
        }
    }

    void pushProtocol(const std::string &name, FSProtocol *p) {
        m_protocols[name] = p;
    }


    FSProtocol & indexOf(const std::string &name) {
        auto p = m_protocols[name];
        return p? *p : FSProtocol::null;
    }



private:
    std::map <std::string, FSProtocol *> m_protocols;
};


#endif // FSPROTOCOL_H
