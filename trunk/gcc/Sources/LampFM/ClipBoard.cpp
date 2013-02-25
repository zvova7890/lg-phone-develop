#include "ClipBoard.h"
#include "main.h"


ClipBoardProtocolGroup::ClipBoardProtocolGroup() :
    protocol(0)
{
}


bool ClipBoardProtocolGroup::pushFile(const std::string &dir, const FSListedEntry &info, int action)
{
    ClipBoardFilesGroup & f = _files[dir];

    // exist?
    for(const ClipBoardFilesGroup::File & file : f.filesList()) {
        if(file.info.name == info.name)
            return false;
    }

    f.filesList().push_back(ClipBoardFilesGroup::File(info, action));

    return true;
}


bool ClipBoardProtocolGroup::popFile(const std::string &dir, const FSListedEntry &info, int *action)
{
    if(action)
        *action = 0;

    auto iter = _files.find(dir);

    if(iter == _files.end())
        return false;

    ClipBoardFilesGroup & f = iter->second;


    if(!f.filesList().empty())
    for(auto it = f.filesList().begin(); it != f.filesList().end(); ++it) {
        if(it->info.name == info.name) {

            if(action)
                *action = it->action;

            f.filesList().erase(it);
            return true;
        }
    }

    if(f.filesList().empty()) {
        _files.erase(iter);
    }


    return false;
}


int ClipBoardProtocolGroup::popDir(const std::string &dir)
{
    auto it = _files.find(dir);

    if(it == _files.end())
        return 0;

    int r = it->second.filesList().size();
    _files.erase(it);
    return r;
}


bool ClipBoardProtocolGroup::actions(const std::string &dir, int *cp, int *mv, int *del)
{
    ClipBoardFilesGroup & f = _files[dir];


    if(cp)
        *cp = 0;

    if(mv)
        *mv = 0;

    if(del)
        *del = 0;

    for(const ClipBoardFilesGroup::File & file : f.filesList()) {
        if(file.info.flags & ClipBoard::Copy && cp)
            ++*cp;

        if(file.info.flags & ClipBoard::Move && mv)
            ++*mv;

        if(file.info.flags & ClipBoard::Delete && del)
            ++*del;
    }

    return true;
}


ClipBoard::ClipBoard()
{
    files_count_for_copy = files_count_for_move = files_count_for_delete = 0;
}


bool ClipBoard::pushFile(const std::string &protocol, const std::string &dir, const FSListedEntry &info, ClipBoard::Action action)
{
    FSProtocol &p = protocolsContainer().indexOf(protocol);
    ClipBoardProtocolGroup &pgroup = _clip_protocols[protocol];

    pgroup.setProtocol(&p);
    bool r = pgroup.pushFile(dir, info, action);

    if(r) {
        if(action & Copy)
            ++files_count_for_copy;

        if(action & Move)
            ++files_count_for_move;

        if(action & Delete)
            ++files_count_for_move;
    }
    return r;
}


bool ClipBoard::popFile(const std::string &protocol, const std::string &dir, const FSListedEntry &info)
{
    ClipBoardProtocolGroup &pgroup = _clip_protocols[protocol];

    int action;
    bool r = pgroup.popFile(dir, info, &action);

    if(r) {
        if(action & Copy)
            --files_count_for_copy;

        if(action & Move)
            --files_count_for_move;

        if(action & Delete)
            --files_count_for_move;
    }

    if(!size())
        clear();

    return r;
}


bool ClipBoard::popDir(const std::string &protocol, const std::string &dir)
{
    ClipBoardProtocolGroup &pgroup = _clip_protocols[protocol];

    int mv, cp, del;

    pgroup.actions(dir, &cp, &mv, &del);

    files_count_for_copy -= cp;
    files_count_for_move -= mv;
    files_count_for_delete -= del;

    int r = pgroup.popDir(dir);

    return r != 0;
}


unsigned int ClipBoard::size(int accepted_works)
{
    unsigned int r = 0;
    if(accepted_works & Copy)
        r += files_count_for_copy;

    if(accepted_works & Move)
        r += files_count_for_move;

    if(accepted_works & Delete)
        r += files_count_for_move;

    return r;
}


void ClipBoard::clear()
{
    files_count_for_copy = files_count_for_move = files_count_for_delete = 0;
    _clip_protocols.clear();
}

