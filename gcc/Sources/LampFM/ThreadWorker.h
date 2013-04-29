#ifndef THREADWORKER_H
#define THREADWORKER_H

#include <Core/Thread.h>
#include <string>


class FileViewWidget;

class ThreadWorker
{
public:
    ThreadWorker();
    ~ThreadWorker();

    void start();

    std::string to_dir;
    std::string cur_file;
    std::string work_name;
    unsigned int file;
    unsigned int full_size;
    unsigned int done;
    bool canceled;

    unsigned int work_finished;
    void *user;
    Thread thread;

    signal_slot::multi_signal <FileViewWidget*>::slot slot;
};

#endif // THREADWORKER_H
