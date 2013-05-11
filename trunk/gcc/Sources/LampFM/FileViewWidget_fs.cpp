
#include <Api/ApiLinkLib/ApiLink.h>
#include <Timer.h>
#include <FileViewWidget.h>
#include <ThreadWorker.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <AsyncProgressivelyWork.h>

//2.7.81


void FileViewWidget::recursive_flush(FSProtocol & proto, int base_dir, const std::string &dir, void *handle, std::list<FSListedEntry> & list)
{
    if(!handle)
        return;

    FSProtocol::FSEntry entry;
    int f_count = 0;
    while(!proto.readdir(handle, &entry))
    {
        if(f_count == 0 && entry.name == ".") {
            ++f_count;
            continue;
        }

        if(f_count == 1 && entry.name == "..") {
            ++f_count;
            continue;
        }

        list.push_back(FSListedEntry(dir, base_dir, entry));

        if(entry.flags & FSProtocol::Dir)
        {
            void *h = proto.opendir((dir+entry.name+"/").c_str(), "*.*");
            if(h) {
                recursive_flush(proto, base_dir, dir+entry.name+"/", h, list);
                proto.closedir(h);
            }
        }
    }
}


void FileViewWidget::set_clipboard_files(const std::string &dir, const FSEntryInfo &info, int action)
{
    FSProtocol & proto = protocolsContainer().indexOf( workspace().protocol );
    std::list<FSListedEntry> list;

    void *h = proto.opendir((dir+info.name).c_str(), "*.*");
    if(h)
    {
        list.push_back(FSListedEntry(dir, dir.length(), info));
        recursive_flush(proto, dir.length(), dir+info.name, h, list);
        proto.closedir(h);
    }


    printf(" -> Copy '%s' files....\n", info.name.c_str());
    for(FSListedEntry &e : list)
    {
        //printf("entry: %s%s\n", (e.dir + e.name).c_str(), e.flags & FSProtocol::Dir? "/" : "");
        m_copyMoveClipboard.pushFile(workspace().protocol, e.dir, e, (ClipBoard::Action)action);
    }
}


void FileViewWidget::copy(const std::string &dir, const FSEntryInfo &info)
{
    if(info.action)
        return;

    if(!(info.attr & FSProtocol::Dir))
    {
        m_copyMoveClipboard.pushFile(workspace().protocol, dir, FSListedEntry(dir, dir.length(), info), ClipBoard::Copy);
        return;
    }


    set_clipboard_files(dir, info, ClipBoard::Copy);
}


void FileViewWidget::move(const std::string &dir, const FSEntryInfo &info)
{
    if(info.action)
        return;

    if(!(info.attr & FSProtocol::Dir))
    {
        m_copyMoveClipboard.pushFile(workspace().protocol, dir, FSListedEntry(dir, dir.length(), info), ClipBoard::Move);
        return;
    }

    set_clipboard_files(dir, info, ClipBoard::Move);
}


void FileViewWidget::paste(const std::string &dir)
{
    if(!m_copyMoveClipboard.size())
        return;

    auto work = new AsyncProgressivelyWork(this);

    work->setMaxFullProgress(m_copyMoveClipboard.size());
    work->setMaxProgress(1);
    work->setWorkName("");
    std::string to_dir = dir;

    work->worker().connect( [this, to_dir](AsyncProgressivelyWork *w){

        for(auto proto : m_copyMoveClipboard.protocols())
        {
            if(w->needToCancel())
                break;


            /* пост удаление папок */
            std::list<std::string> last_dir;

            for(auto files = proto.second.files().begin(); files != proto.second.files().end(); ++files)
            {
                const std::string &dir = files->first;
                std::string base_dir;
                ClipBoardFilesGroup &group = files->second;

                base_dir.assign(dir, group.filesList().front().info.base_from, dir.length()-group.filesList().front().info.base_from);


                for(auto file = group.filesList().begin(); file != group.filesList().end(); ++file)
                {
                    base_dir.clear();

                    if(dir.length() > (unsigned int)group.filesList().front().info.base_from)
                        base_dir.assign(dir, group.filesList().front().info.base_from, dir.length()-group.filesList().front().info.base_from);

                    if(file->info.flags & FSProtocol::FSEntryFlags::Dir) {

                            w->setWorkName("Creating...");
                            w->setProgressInfo(file->info.name.c_str());
                            w->setMaxProgress(1);
                            w->setProgress(0);

                            std::string ndir = to_dir+base_dir+file->info.name+"/";
                            mkdir(ndir.c_str(), 0777);
                            //printf("Mkdir %s\n", ndir.c_str());

                            if( file->action & ClipBoard::Action::Move &&
                                dir.compare(dir.length()-(file->info.name.length()+1), file->info.name.length(), file->info.name+"/") ) {
                                last_dir.push_back(dir + file->info.name+"/");
                            }

                            w->setProgress(1);
                            w->setFullProgress(w->fullProgress()+1);


                    } else {

                            w->setWorkName(file->action == ClipBoard::Action::Copy? "Copying..." : "Moving...");
                            w->setProgressInfo(file->info.name.c_str()); // Avoid CoW?
                            w->setProgress(0);


                            if(file->action & ClipBoard::Action::Move && !strncmp(to_dir.c_str(), dir.c_str(), 4)) {
                                U_CHAR old[256], nw[256];

                                UniLib_UTF8ToUCS2((char*)(dir+file->info.name).c_str(), old);
                                UniLib_UTF8ToUCS2((char*)(to_dir+base_dir+file->info.name).c_str(), nw);

                                if(!FileSys_MoveFile(old, nw))
                                    goto try_copy;

                            } else {

                                try_copy:
                                int err = copy_file((dir+file->info.name).c_str(), (to_dir+base_dir+file->info.name).c_str(),
                                                    [w](int p) { w->setMaxProgress(p); },
                                                    [w](int p) { w->setProgress(p); },
                                                    [w]()      { return w->needToCancel(); });

                                if(err)
                                    w->setProgressInfo("Ошибка");

                                else if(file->action == ClipBoard::Action::Move)
                                    unlink((dir+file->info.name).c_str());
                            }

                            w->setFullProgress(w->fullProgress()+1);
                    }

                    if(w->needToCancel())
                        break;
                }

            }

            if(!last_dir.empty()) {
                for(auto it = last_dir.rbegin(); it != last_dir.rend(); ++it) {
                    rmdir(it->c_str());
                    //printf("REMOVEDIR: %s\n", it->c_str());
                }

                last_dir.clear();
            }
        }

        m_copyMoveClipboard.clear();
        w->setWorkName("Done!");

        eventManager()->notifyAfterEvent([this, w](){
            ::Timer::oneShoot(eventManager(), 1000, [this, w](){
                w->close();
                delete w;

                refreshDir();
                eventManager()->updateAfterEvent();
            });
        });
    });

    work->show();
    work->start();


    //do_clipboard_work(dir, ClipBoard::Action::Copy | ClipBoard::Action::Move);
}


int FileViewWidget::unlinkFiles(const std::list<const FSEntryInfo *> & list)
{
    printf("unlinkFiles(%d)\n", list.size());
    int unlinked = 0;
    FSProtocol & p = protocolsContainer().indexOf(workspace().protocol);

    for(auto entry : list)
    {
        if((entry->attr == FSProtocol::FSEntryFlags::File) && !entry->action)
        {
            //int r = p.unlink((directory() + entry->name).c_str());
            //if(!r) unlinked ++;

            m_deleteClipboard.pushFile(workspace().protocol, directory(),
                                       FSListedEntry(directory(), directory().length(), *entry),
                                       ClipBoard::Delete);
        }

        if(entry->attr & FSProtocol::FSEntryFlags::Dir && !entry->action) {

            /* если выбрана папка, сгенерируем для неё полный поочерёдный "папка -> список -> папка -> список" список файлов */
            std::list<FSListedEntry> list;

            void *h = p.opendir((directory()+entry->name).c_str(), "*.*");
            if(h)
            {
                list.push_back(FSListedEntry(directory(), directory().length(), *entry));
                recursive_flush(p, directory().length(), directory()+entry->name, h, list);
                p.closedir(h);
            }

            /* запустим полученный список в буффер обмена, с пометкой операции "Delete" */
            for(FSListedEntry &e : list)
            {
                //FIXME
                m_deleteClipboard.pushFile(workspace().protocol, e.dir, e, ClipBoard::Delete);
            }
        }
    }

    /* если мы запланировали какую-то работу, то выполняем её */
    if(!m_deleteClipboard.size())
        return unlinked;


    startDeleteOperation();

    return unlinked;
}



int FileViewWidget::copy_file(const std::string &from, const std::string &to,
                              std::function<void(int)> setFullSize,
                              std::function<void(int)> setProcessedSize,
                              std::function<bool()> isCanceled)
{
    if(from == to) {
        printf("copy_file: From == to\n");
        return -1;
    }

    FSProtocol & p = protocolsContainer().indexOf(workspace().protocol);

    void *h = p.open(from.c_str(), FSProtocol::Read);
    if(h) {

        void *h_to = p.open(to.c_str(), FSProtocol::Create | FSProtocol::Trunc);
        if(!h_to) {

            printf("Can`t open '%s' for write\n", to.c_str());
            p.close(h);
            return -2;
        }

        int size = p.fsize(h);
        setFullSize(size);

        bool err = false;
        unsigned long processed = 0;

        while(1) {

            char data[4*1024+1];

            int r = p.read(h, data, 4*1024);
            if(r < 1)
                break;

            int w = p.write(h_to, data, r);

            processed += w;
            setProcessedSize(processed);

            if(w != r) {
                printf("error: file '%s' writed not correctly\n", to.c_str());
                err = true;
                break;
            }

            if(size <= processed)
                break;

            if(isCanceled())
                break;
        }


        p.close(h);
        p.close(h_to);

        if(err)
            return -4;

    } else {
        printf("Can`t open '%s' for read\n", from.c_str());
        return -3;
    }


    return 0;
}
