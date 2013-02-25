#include "ThreadWorker.h"



ThreadWorker::ThreadWorker()
{
    file = 0;
    full_size = 0;
    done = 0;

    work_finished = 0;
}


ThreadWorker::~ThreadWorker()
{

}


void ThreadWorker::start()
{
    thread.start(120);
}
