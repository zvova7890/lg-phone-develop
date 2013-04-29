#ifndef ASYNCPROGRESSIVELYWORK_H
#define ASYNCPROGRESSIVELYWORK_H

#include <Thread.h>
#include <Timer.h>
#include <signals/signal.h>
#include <Widget.h>
#include <string>


class Image;

class AsyncProgressivelyWork : protected Thread, public Widget
{
public:
    typedef signal_slot::signal <AsyncProgressivelyWork *> signal;

    AsyncProgressivelyWork(Widget *parent);
    virtual ~AsyncProgressivelyWork();


    virtual bool start();
    virtual bool tryCancel();

    void setPercentDone(int p);
    void setWorkName(const std::string &work);
    void setProgressInfo(const std::string &i);



    void setMaxFullProgress(unsigned int c) {
        m_maxFullProgress = c;
    }

    void setMaxProgress(unsigned int c) {
        m_maxProgress = c;
    }

    void setFullProgress(unsigned int c) {
        m_fullProgress = c;
    }

    unsigned int fullProgress() {
        return m_fullProgress;
    }

    void setProgress(unsigned int c) {
        m_progress = c;
    }

    unsigned int progress() {
        return m_progress;
    }

    bool needToCancel() const {
        return m_cancelFlag;
    }

    signal &worker() {
        return m_worker;
    }

    signal & workFinished() {
        return m_workFinished;
    }


protected:
    void run();
    void paintEvent();
    void touchEvent(int action, int x, int y);

protected:
    signal m_worker;
    signal m_workFinished;

    std::string m_workName;
    std::string m_progressInfo;

    Timer m_timer;
    Image *m_background;

    bool m_cancelFlag;
    int m_progress, m_fullProgress, m_maxFullProgress, m_maxProgress;
};

#endif // ASYNCPROGRESSIVELYWORK_H
