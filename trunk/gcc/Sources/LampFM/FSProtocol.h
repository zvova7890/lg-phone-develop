#ifndef FSPROTOCOL_H
#define FSPROTOCOL_H

#include <map>
#include <string>


class FSProtocol
{
public:

    typedef enum {
        READ = (1 << 1),
        WRITE = (1 << 2),
        CREATE = (1 << 3),
        TRUNC = (1 << 4)
    }Mode;

public:
    FSProtocol();
    virtual ~FSProtocol();

    virtual void *open(const char *f, int mode);
    virtual int read(void *, char *data, int size);
    virtual int write(void *, const char *data, int size);
    virtual int close(void *);

    virtual int unlink(const char *f);

    virtual int mkdir(const char *d, bool recursive = false);
    virtual int rmdir(const char *d, bool recursive = false);

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


    FSProtocol *indexOf(const std::string &name) {
        return _protocols[name];
    }

private:
    std::map <std::string, FSProtocol *> _protocols;
};


#endif // FSPROTOCOL_H
