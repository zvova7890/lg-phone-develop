#include "ClipBoard.h"
#include "main.h"


ClipBoardProtocolGroup::ClipBoardProtocolGroup() :
    m_protocol(0)
{
}


bool ClipBoardProtocolGroup::pushFile(const std::string &dir, const FSListedEntry &info, int action)
{
    ClipBoardFilesGroup & f = m_files[dir];

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

    auto iter = m_files.find(dir);

    if(iter == m_files.end())
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
        m_files.erase(iter);
    }


    return false;
}


int ClipBoardProtocolGroup::popDir(const std::string &dir)
{
    auto it = m_files.find(dir);

    if(it == m_files.end())
        return 0;

    int r = it->second.filesList().size();
    m_files.erase(it);
    return r;
}


bool ClipBoardProtocolGroup::actions(const std::string &dir, int *cp, int *mv, int *del)
{
    ClipBoardFilesGroup & f = m_files[dir];


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
    m_filesCountForCopy = m_filesCountForMove = m_filesCountForDelete = 0;
}


bool ClipBoard::pushFile(const std::string &protocol, const std::string &dir, const FSListedEntry &info, ClipBoard::Action action)
{
    FSProtocol &p = protocolsContainer().indexOf(protocol);
    ClipBoardProtocolGroup &pgroup = m_clipProtocols[protocol];

    pgroup.setProtocol(&p);
    bool r = pgroup.pushFile(dir, info, action);

    if(r) {
        if(action & Copy)
            ++m_filesCountForCopy;

        if(action & Move)
            ++m_filesCountForMove;

        if(action & Delete)
            ++m_filesCountForMove;
    }
    return r;
}


bool ClipBoard::popFile(const std::string &protocol, const std::string &dir, const FSListedEntry &info)
{
    ClipBoardProtocolGroup &pgroup = m_clipProtocols[protocol];

    int action;
    bool r = pgroup.popFile(dir, info, &action);

    if(r) {
        if(action & Copy)
            --m_filesCountForCopy;

        if(action & Move)
            --m_filesCountForMove;

        if(action & Delete)
            --m_filesCountForMove;
    }

    if(!size())
        clear();

    return r;
}


bool ClipBoard::popDir(const std::string &protocol, const std::string &dir)
{
    ClipBoardProtocolGroup &pgroup = m_clipProtocols[protocol];

    int mv, cp, del;

    pgroup.actions(dir, &cp, &mv, &del);

    m_filesCountForCopy -= cp;
    m_filesCountForMove -= mv;
    m_filesCountForDelete -= del;

    int r = pgroup.popDir(dir);

    return r != 0;
}


unsigned int ClipBoard::size(int accepted_works)
{
    unsigned int r = 0;
    if(accepted_works & Copy)
        r += m_filesCountForCopy;

    if(accepted_works & Move)
        r += m_filesCountForMove;

    if(accepted_works & Delete)
        r += m_filesCountForMove;

    return r;
}


void ClipBoard::clear()
{
    m_filesCountForCopy = m_filesCountForMove = m_filesCountForDelete = 0;
    m_clipProtocols.clear();
}

