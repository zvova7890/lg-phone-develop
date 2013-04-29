#ifndef CLIPBOARD_H
#define CLIPBOARD_H

#include <string>
#include <map>
#include <unordered_map>
#include <FSProtocol.h>
#include <list>
#include <FSEntryInfo.h>




class FSListedEntry
{
public:
    FSListedEntry() {
        base_from = flags = 0;
    }

    bool operator ==(const FSListedEntry &f) {

        if(base_from == f.base_from &&
           flags == f.flags &&
           name == f.name &&
           dir == f.dir )
            return true;

        return false;
    }

    FSListedEntry(const std::string &dir, int base_from, const FSEntryInfo &info) {
        name = info.name;
        flags = info.attr;
        this->dir = dir;
        this->base_from = base_from;

        if(flags & FSProtocol::Dir && name[name.length()-1] == '/') {
            name.erase(name.length()-1, 1);
        }
    }

    FSListedEntry(const std::string &dir, int base_from, const FSProtocol::FSEntry &info) {
        name = info.name;
        flags = info.flags;
        this->dir = dir;
        this->base_from = base_from;
    }

    std::string dir;
    int base_from;
    std::string name;
    int flags;
};



struct ClipBoardFilesGroup
{
public:

    class File {
    public:
        File(const FSListedEntry &info, int action) {
            this->info = info;
            this->action = action;
        }

        FSListedEntry info;
        char action;
    };

    std::list<File> & filesList() {
        return _files;
    }

protected:
    std::list<File> _files;
};


class ClipBoardProtocolGroup
{
public:
    ClipBoardProtocolGroup();

    bool pushFile(const std::string &dir, const FSListedEntry &info, int action);
    bool popFile(const std::string &dir, const FSListedEntry &info, int *action = 0);
    int popDir(const std::string &dir);
    bool actions(const std::string &dir, int *cp, int *mv, int *del);

    void setProtocol(FSProtocol *p) {
        m_protocol = p;
    }


    std::map<std::string, ClipBoardFilesGroup> & files() {
        return m_files;
    }

private:
    std::map<std::string, ClipBoardFilesGroup> m_files;
    FSProtocol *m_protocol;
};



class ClipBoard
{
public:
    enum Action {
        Copy = (1 << 1),
        Move = (1 << 2),
        Delete = (1 << 3)
    };

public:
    ClipBoard();

    bool pushFile(const std::string &protocol, const std::string &dir, const FSListedEntry &info, int );
    bool popFile(const std::string &protocol, const std::string &dir, const FSListedEntry &info);
    bool popDir(const std::string &protocol, const std::string &dir);
    void clear();

    std::unordered_map <std::string, ClipBoardProtocolGroup> &protocols() {
        return m_clipProtocols;
    }

    unsigned int size() const {
        return m_filesCountForCopy+m_filesCountForMove+m_filesCountForDelete;
    }

    unsigned int size(int accepted_works);

    unsigned int filesForCopy() {
        return m_filesCountForCopy;
    }

    unsigned int filesForMove() {
        return m_filesCountForMove;
    }

    unsigned int filesForDelete() {
        return m_filesCountForDelete;
    }

private:
    unsigned int m_filesCountForCopy, m_filesCountForMove, m_filesCountForDelete;
    std::unordered_map <std::string, ClipBoardProtocolGroup> m_clipProtocols;
};


#endif // CLIPBOARD_H
