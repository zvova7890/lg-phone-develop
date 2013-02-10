#ifndef FSENTRYINFO_H
#define FSENTRYINFO_H


#include <string>



struct FSEntryInfo
{
public:
    FSEntryInfo() :
        attr(0),
        size(0),
        action(false)
    {

    }

    FSEntryInfo(const std::string & _name, int _attr, int _size, bool _action = false) {
        name = _name;
        attr = _attr;
        size = _size;
        action = _action;
    }

    FSEntryInfo(const FSEntryInfo &f) {
        name = f.name;
        attr = f.attr;
        size = f.size;
        action = f.action;
    }

    FSEntryInfo & operator =(const FSEntryInfo &f) {
        name = f.name;
        attr = f.attr;
        size = f.size;
        action = f.action;
        return *this;
    }

    std::string name;
    int attr;
    int size;
    bool action;
};


#endif // FSENTRYINFO_H
