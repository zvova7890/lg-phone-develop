#include <Api/ApiLinkLib/ApiLink.h>
#include <Timer.h>
#include <FileViewWidget.h>
#include <ThreadWorker.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <AsyncProgressivelyWork.h>




void FileViewWidget::startDeleteOperation()
{
    auto work = new AsyncProgressivelyWork(this);

    work->setMaxFullProgress(m_deleteClipboard.size());
    work->setMaxProgress(1);
    work->setWorkName("Removing...");
    std::string to_dir = directory();

    work->worker().connect( [this, to_dir](AsyncProgressivelyWork *w){

        for(auto proto : m_deleteClipboard.protocols())
        {

            FSProtocol & p = protocolsContainer().indexOf(proto.first);

            if(w->needToCancel())
                break;

            for(auto files = proto.second.files().rbegin(); files != proto.second.files().rend(); ++files)
            {
                const std::string &dir = files->first;
                std::string base_dir;
                ClipBoardFilesGroup &group = files->second;

                base_dir.assign(dir, group.filesList().front().info.base_from, dir.length()-group.filesList().front().info.base_from);

                for(auto file = group.filesList().rbegin(); file != group.filesList().rend(); ++file)
                {
                    if(w->needToCancel())
                        break;

                    if(file->info.flags & FSProtocol::FSEntryFlags::Dir) {

                        w->setWorkName("Deleting dir...");
                        w->setProgressInfo(file->info.name.c_str());
                        w->setMaxProgress(1);
                        w->setProgress(0);

                        //printf("rmdir(%s)\n", (to_dir+base_dir+file->info.name+"/").c_str());
                        if(p.rmdir((to_dir+base_dir+file->info.name+"/").c_str())) {
                            w->setWorkName("Fail");
                            Thread::sleep(500);
                        }

                        w->setProgress(1);
                        w->setFullProgress(w->fullProgress()+1);

                    } else {

                        w->setWorkName("Deleting...");
                        w->setProgressInfo(file->info.name.c_str());
                        w->setMaxProgress(1);
                        w->setProgress(0);

                        if( p.unlink((dir+file->info.name).c_str()) ) {
                            w->setWorkName("Fail");
                            Thread::sleep(500);
                        }

                        Thread::sleep(1500);


                        w->setProgress(1);
                        w->setFullProgress(w->fullProgress()+1);

                        //usleep(500);
                    }

                    if(w->needToCancel())
                        break;
                }
            }
        }

        m_deleteClipboard.clear();
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
}
