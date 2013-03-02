
#include <Api/ApiLinkLib/ApiLink.h>
#include <FileViewWidget.h>
#include <ThreadWorker.h>
#include <Timer.h>
#include <unistd.h>
#include <fcntl.h>




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
        m_clipboard.pushFile(workspace().protocol, e.dir, e, (ClipBoard::Action)action);
    }
}


void FileViewWidget::copy(const std::string &dir, const FSEntryInfo &info)
{
    if(info.action)
        return;

    if(!(info.attr & FSProtocol::Dir))
    {
        pushFileToClipBoard(dir, FSListedEntry(dir, dir.length(), info), ClipBoard::Copy);
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
        pushFileToClipBoard(dir, FSListedEntry(dir, dir.length(), info), ClipBoard::Move);
        return;
    }

    set_clipboard_files(dir, info, ClipBoard::Move);
}


void FileViewWidget::paste(const std::string &dir)
{
    do_clipboard_work(dir, ClipBoard::Action::Copy | ClipBoard::Action::Move);
}


void FileViewWidget::do_clipboard_work(const std::string &to_dir, int accepted_work)
{
    if(!m_clipboard.size())
        return;

    ThreadWorker *worker = new ThreadWorker;
    ProgressDialog *progress = new ProgressDialog(parent(), Rect(10, 70, 220, 150));
    Timer *timer = new Timer();

    worker->to_dir = to_dir;


    worker->slot = this->onExitSignal().connect( [this, timer, worker, progress](FileViewWidget *){
        progress->hide();
        timer->stop();

        delete worker;
        delete timer;
        delete progress;
        m_clipboard.clear();
    });


    progress->setFullScreenBlock(true);
    progress->setMaxFullProgress(m_clipboard.size(accepted_work));


    worker->thread.onRunSignal().connect( [accepted_work, worker, this](Thread *) {

        for(auto proto : m_clipboard.protocols())
        {

            struct Remover {
                Remover(const std::string *_dir, const FSListedEntry *_e) {
                    dir = _dir;
                    info = _e;
                }

                const std::string *dir;
                const FSListedEntry *info;
            };

            /* удалять файл из итерирующего спика опастно, лучьше делать это потом */
            std::list <Remover> remover_list;

            /* пост удаление папок */
            std::list<std::string> last_dir;

            if(!(accepted_work & ClipBoard::Action::Copy || accepted_work & ClipBoard::Action::Move))
                goto __next1;

            for(auto files = proto.second.files().begin(); files != proto.second.files().end(); ++files)
            {
                const std::string &dir = files->first;
                std::string base_dir;
                ClipBoardFilesGroup &group = files->second;

                for(auto file = group.filesList().begin(); file != group.filesList().end(); ++file)
                {
                    base_dir.clear();

                    if(dir.length() > (unsigned int)group.filesList().front().info.base_from)
                        base_dir.assign(dir, group.filesList().front().info.base_from, dir.length()-group.filesList().front().info.base_from);

                    if(file->info.flags & FSProtocol::FSEntryFlags::Dir) {


                        if((file->action == ClipBoard::Action::Copy || file->action == ClipBoard::Action::Move) &&
                                (accepted_work & ClipBoard::Action::Copy || accepted_work & ClipBoard::Action::Move))
                        {
                            worker->work_name = "Creating...";
                            worker->cur_file = file->info.name.c_str();
                            worker->full_size = 1;
                            worker->done = 0;

                            std::string ndir = worker->to_dir+base_dir+file->info.name+"/";
                            mkdir(ndir.c_str(), 0777);

                            if( file->action & ClipBoard::Action::Move &&
                                dir.compare(dir.length()-(file->info.name.length()+1), file->info.name.length(), file->info.name+"/") ) {
                                last_dir.push_back(dir + file->info.name+"/");
                            }

                            worker->done = 1;
                            worker->file++;

                            remover_list.push_back(Remover(&dir, &file->info)); 
                        }

                    } else {

                        if((file->action == ClipBoard::Action::Copy || file->action == ClipBoard::Action::Move) &&
                                (accepted_work & ClipBoard::Action::Copy || accepted_work & ClipBoard::Action::Move))
                        {

                            worker->work_name = file->action == ClipBoard::Action::Copy? "Copying..." : "Moving...";
                            worker->cur_file = file->info.name.c_str(); // Avoid CoW?
                            worker->done = 0;


                            if(file->action & ClipBoard::Action::Move && !strncmp(worker->to_dir.c_str(), dir.c_str(), 4)) {
                                U_CHAR old[256], nw[256];

                                UniLib_UTF8ToUCS2((char*)(dir+file->info.name).c_str(), old);
                                UniLib_UTF8ToUCS2((char*)(worker->to_dir+base_dir+file->info.name).c_str(), nw);

                                if(!FileSys_MoveFile(old, nw))
                                    goto try_copy;

                            } else {

                                try_copy:
                                int err = copy_file((dir+file->info.name).c_str(), (worker->to_dir+base_dir+file->info.name).c_str(),
                                                    &worker->full_size, &worker->done, &worker->canceled);
                                if(err)
                                    worker->cur_file = "Ошибка";

                                else if(file->action == ClipBoard::Action::Move)
                                    unlink((dir+file->info.name).c_str());
                            }

                            worker->file++;

                            remover_list.push_back(Remover(&dir, &file->info));
                        }
                    }

                    if(worker->canceled)
                        break;
                }

                for(const auto rl : remover_list) {
                    m_clipboard.popFile( workspace().protocol, *rl.dir, *rl.info);
                }

                remover_list.clear();

                if(worker->canceled)
                    break;
            }

            if(!last_dir.empty() && accepted_work & ClipBoard::Action::Move) {
                for(auto it = last_dir.rbegin(); it != last_dir.rend(); ++it) {
                    rmdir(it->c_str());
                    printf("REMOVEDIR: %s\n", it->c_str());
                }

                last_dir.clear();
            }




            __next1:

            if(!(accepted_work & ClipBoard::Action::Delete))
                goto __end;

            remover_list.clear();
            for(auto files = proto.second.files().rbegin(); files != proto.second.files().rend(); ++files)
            {
                const std::string &dir = files->first;
                std::string base_dir;
                ClipBoardFilesGroup &group = files->second;

                base_dir.assign(dir, group.filesList().front().info.base_from, dir.length()-group.filesList().front().info.base_from);

                for(auto file = group.filesList().rbegin(); file != group.filesList().rend(); ++file)
                {
                    if(file->info.flags & FSProtocol::FSEntryFlags::Dir) {

                        if(file->action == ClipBoard::Action::Delete && accepted_work & ClipBoard::Action::Delete) {

                            worker->work_name = "Deleting dir...";
                            worker->cur_file = file->info.name.c_str();
                            worker->full_size = 1;
                            worker->done = 0;

                            //printf("rmdir(%s)\n", (worker->to_dir+base_dir+file->info.name+"/").c_str());
                            rmdir((worker->to_dir+base_dir+file->info.name+"/").c_str());

                            worker->done = 1;
                            worker->file++;

                            remover_list.push_back(Remover(&dir, &file->info));
                        }

                    } else {

                        if(file->action == ClipBoard::Action::Delete && (accepted_work & ClipBoard::Action::Delete)) {

                            worker->work_name = "Deleting...";
                            worker->cur_file = file->info.name.c_str();
                            worker->full_size = 1;
                            worker->done = 0;

                            unlink((dir+file->info.name).c_str());

                            worker->done = 1;
                            worker->file++;

                            remover_list.push_back(Remover(&dir, &file->info));
                        }
                    }

                    if(worker->canceled)
                        break;
                }

                for(const Remover & rl : remover_list) {
                    m_clipboard.popFile(workspace().protocol, *rl.dir, *rl.info);
                }

                remover_list.clear();

                if(worker->canceled)
                    break;
            }


__end:;
        }


        onExitSignal().disconnect(worker->slot);
        worker->work_finished = 1;
    });


    timer->timerEventSignal().connect([worker, progress, this](Timer *t) {

        if(worker->work_finished > 10) {

            progress->hide();
            t->stop();

            delete worker;
            delete progress;

            eventManager()->notifyAfterEvent( EventManager::EventManagerAction( [](void *c){
                Timer *t = (Timer *)c;
                delete t;
            }, t));

            eventManager()->updateAfterEvent();
            refreshDir();
            return;
        }

        if(worker->work_finished)
            worker->work_finished++;

        progress->setCurrentWorkStatus(worker->cur_file);

        progress->setProgressName(worker->work_name);

        progress->setFullProgress(worker->file);
        progress->setMaxProgress(worker->full_size);
        progress->setProgress(worker->done);

        eventManager()->updateAfterEvent();
    });


    timer->start(80);
    progress->show();
    worker->start();
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
            int r = p.unlink((directory() + entry->name).c_str());
            if(!r) unlinked ++;
        }

        else if(entry->attr & FSProtocol::FSEntryFlags::Dir && !entry->action) {

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
                //printf("Push %s\n", (e.dir+e.name+(e.flags & FSProtocol::Dir? "/" : "")).c_str());
                m_clipboard.pushFile(workspace().protocol, e.dir, e, ClipBoard::Delete);
            }
        }
    }

    /* если мы запланировали какую-то работу, то выполняем её */
    do_clipboard_work(directory(), ClipBoard::Delete);

    return unlinked;
}



int FileViewWidget::copy_file(const std::string &from, const std::string &to, unsigned int *full, unsigned int *done, bool *cancel_flag)
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

        if(full)
            *full = p.fsize(h);

        bool err = false;

        while(1) {

            char data[4*1024+1];

            int r = p.read(h, data, 4*1024);
            if(r < 1)
                break;

            int w = p.write(h_to, data, r);

            if(done)
                *done += w;
            if(w != r) {
                printf("error: file '%s' writed not correctly\n", to.c_str());
                err = true;
                break;
            }

            if(cancel_flag && *cancel_flag)
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
