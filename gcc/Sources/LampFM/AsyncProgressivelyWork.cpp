#include "AsyncProgressivelyWork.h"
#include <gl.h>
#include <Graph/Image.h>
#include <main.h>


AsyncProgressivelyWork::AsyncProgressivelyWork(Widget *parent) :
    Widget(Rect(8, parent->rect().h()/3 - 100/2, parent->rect().w()-16, 150), parent),
    m_cancelFlag(false),
    m_progress(0),
    m_fullProgress(0),
    m_maxFullProgress(0),
    m_maxProgress(0)
{
    m_background = &resourceManager().image("progress");
    setFullScreenBlock(true);

    m_timer.timerEventSignal().connect([this](Timer *){
        eventManager()->updateAfterEvent();
    });
}


AsyncProgressivelyWork::~AsyncProgressivelyWork()
{

}


bool AsyncProgressivelyWork::start()
{
    m_timer.start(100);
    return Thread::start();
}


bool AsyncProgressivelyWork::tryCancel()
{
    m_cancelFlag = true;
    return true;
}


void AsyncProgressivelyWork::setPercentDone(int p)
{
    // FIXME?
    (void) p;
}


void AsyncProgressivelyWork::setProgressInfo(const std::string &i)
{
    m_progressInfo = i;
}


void AsyncProgressivelyWork::setWorkName(const std::string &work)
{
    m_workName = work;
}


void AsyncProgressivelyWork::run()
{
    m_worker.trigger(this);
}


void AsyncProgressivelyWork::paintEvent()
{
    if(!m_background->isEmpty()) {
        drawImage(realRect().x(), realRect().y(), m_background);

        int ws = (parent()->size().w() - m_background->width())/2;

        setSize(Rect(ws, parent()->realRect().h()/3 - 100/2, parent()->rect().w()-ws*2, m_background->height()));

    } else {
        glSetPen(0xFF000000);
        glDrawFilledRectange(realRect().x(), realRect().y(), realRect().x2(), realRect().y2());

        glSetPen(0xFFFFFFFF);
        glDrawRectange(realRect().x(), realRect().y(), realRect().x2(), realRect().y2());
    }


    glSetPen(0xFFFFFFFF);
    glDrawString(m_workName.c_str(), realRect().x()+2, realRect().y()+1, realRect().x2()-2, realRect().y()+20,
                 15, FT_TEXT_H_CENTER, 0, 128);


    char info[56];
    sprintf(info, "%d/%d", m_fullProgress, m_maxFullProgress);

    glDrawString(info, realRect().x()+2, realRect().y()+1, realRect().x2()-2, realRect().y()+20,
                 15, FT_TEXT_H_CENTER | FT_TEXT_W_RIGHT, 0, 128);

    //glDrawHLine(realRect().x()+2, realRect().x2()-2, realRect().y()+24);


    glSetPen(0xFFFFFFFF);
    glDrawString(m_progressInfo.c_str(), realRect().x()+2, realRect().y()+23, realRect().x2()-2, realRect().y()+23+22,
                 15, FT_TEXT_W_CENTER | FT_TEXT_H_DOWN | FT_TEXT_CENTER_BY_XSTART, 0, 128);

    int y = realRect().y()+60;

    int percent_full = m_fullProgress*100/m_maxFullProgress;
    int percent = m_progress && m_maxProgress? m_progress*100/m_maxProgress : 0;

    int max_w = realRect().w()-10;
    int full_x = max_w*percent_full/100;
    int cur_x = max_w*percent/100;


    glSetPen(0xFFFF0000);
    glDrawRectange(realRect().x()+4, y, realRect().x2()-6, y+4);

    if(full_x < 1)
        full_x = 0;
    if(full_x > max_w)
        full_x = max_w;

    glSetPen(0xFFFFFFFF);
    glDrawFilledRectange(realRect().x()+5, y+1, realRect().x()+5+full_x, y+4);


    y += 10;

    glSetPen(0xFFFF0000);
    glDrawRectange(realRect().x()+4, y, realRect().x2()-6, y+4);

    if(cur_x < 1)
        cur_x = 0;
    if(cur_x > max_w)
        cur_x = max_w;

    glSetPen(0xFFFFFFFF);
    glDrawFilledRectange(realRect().x()+5, y+1, realRect().x()+5-1+cur_x, y+4);

    Widget::paintEvent();
}


void AsyncProgressivelyWork::touchEvent(int action, int x, int y)
{
    Widget::touchEvent(action, x, y);
}
