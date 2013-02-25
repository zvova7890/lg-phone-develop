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
        protocol = p;
    }


    std::map<std::string, ClipBoardFilesGroup> & files() {
        return _files;
    }

private:
    std::map<std::string, ClipBoardFilesGroup> _files;
    FSProtocol *protocol;
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

    bool pushFile(const std::string &protocol, const std::string &dir, const FSListedEntry &info, Action );
    bool popFile(const std::string &protocol, const std::string &dir, const FSListedEntry &info);
    bool popDir(const std::string &protocol, const std::string &dir);
    void clear();

    std::map <std::string, ClipBoardProtocolGroup> &protocols() {
        return _clip_protocols;
    }

    unsigned int size() {
        return files_count_for_copy+files_count_for_move+files_count_for_delete;
    }

    unsigned int size(int accepted_works);

    unsigned int filesForCopy() {
        return files_count_for_copy;
    }

    unsigned int filesForMove() {
        return files_count_for_move;
    }

    unsigned int filesForDelete() {
        return files_count_for_delete;
    }

private:
    unsigned int files_count_for_copy, files_count_for_move, files_count_for_delete;
    std::map <std::string, ClipBoardProtocolGroup> _clip_protocols;
};

#endif // CLIPBOARD_H
