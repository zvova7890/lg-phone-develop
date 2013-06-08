#include <QPainter>
#include <QApplication>
#include <QDebug>
#include "x86_mainwindow.h"
#include "ui_mainwindow.h"
#include "freetype_engine.h"
#include <signals/signal.h>
#include <stdarg.h>
#include <functional>

#include <pxeapi.h>
#include <Api/ApiLinkLib/ApiLink.h>


extern "C" void initGLStringFont();
extern "C" void finiGLStringFont();
extern "C" void fte_cleanMap();

extern "C" void lgmain(int, char **);



GLContext *DefaultGLContext = 0;

int max_fps = 0;
EmuMainWindow *cur_window = 0;


class MsgHandlerData
{
public:
    MsgHandlerData() {
        cb = 0;
    }

    MsgHandlerData(MsgHandler_Callback c) {
        cb = c;
    }

    MsgHandler_Callback cb;
    QMap<int, unsigned long> params;
};

QMap <T_ID, MsgHandlerData> msg_handlers;
std::list<int> msg_handler_active_pid;

MsgHandler_Callback _current_cb_process = 0;


void MsgHandler_SendMessageToActiveID(unsigned long event, unsigned long p1, unsigned long p2);

void EvHandler_SendMessageToActivePID(unsigned long event, unsigned long p1, unsigned long p2)
{
    if(_current_cb_process) {
        _current_cb_process(event, p1, p2);
    }
}


EmuMainWindow::EmuMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    repaintReq(0),
    fps(0), fps_cnt(40),
    rotated(false)
{
    cur_window = this;
    ui->setupUi(this);

    connect(ui->orientationAction, SIGNAL(triggered()), this, SLOT(orientationChange()));
    connect(this, SIGNAL(_doLater(void*)), SLOT(doLaterSlot(void*)), Qt::QueuedConnection);

    memset(m_timers, 0, sizeof(m_timers));
    initGLStringFont();

    if(rotated)
        img = new QImage(400, 240, QImage::Format_RGB16);
    else
        img = new QImage(240, 400, QImage::Format_RGB16);


    EmuMainWindow::resize(img->width()+20, img->height()+30);


    img->fill(0xFFFFFFFF);

    off_x = 40;
    off_y = 40;


    lgmain(QApplication::argc(), QApplication::argv());

    EvHandler_SendMessageToActivePID(BNS_EVENT_START, 0, 0);
}



EmuMainWindow::~EmuMainWindow()
{
    EvHandler_SendMessageToActivePID(BNS_EVENT_TERMINATE, 0, 0);


    finiGLStringFont();
    fte_cleanMap();

    printf("MAX fps: %d\n", max_fps);
    delete img;
    delete ui;
}



void EmuMainWindow::doLaterSlot(void *_f)
{
    std::function<void ()> *f = (std::function<void ()>*)_f;
    (*f)();

    delete f;
}


void EmuMainWindow::doLater(std::function<void ()> f)
{
    emit _doLater(new std::function<void ()>(f));
}


void EmuMainWindow::paintEvent(QPaintEvent *)
{
    QPainter p(this);

    if(repaintReq > 0) {
        EvHandler_SendMessageToActivePID(BNS_EVENT_PAINT, 0, 0);
        repaintReq --;
    }


    if(rotated) {
        QPainter l(img);
        l.rotate(90);
    }

    p.drawImage(10, 30, *img);
}


void EmuMainWindow::update_()
{
    //repaint(10, 10, img->width(), img->height());
    update(10, 30, img->width(), img->height());
}


void EmuMainWindow::update_(int x , int y, int w, int h)
{
    update(10+x, 30+y, w, h);
}


void EmuMainWindow::mouseMoveEvent(QMouseEvent *e)
{
    int x = e->x() - 10;
    int y = e->y() - 30;

    if(x < 0)
        x = 0;

    //qWarning() << "GRSYS_WIDTH: " << GRSYS_WIDTH;

    if(x > GRSYS_WIDTH)
        x = GRSYS_WIDTH;

    if(y < 0)
        y = 0;

    if(y > GRSYS_HEIGHT)
        y = GRSYS_HEIGHT;

    //qWarning() << "mouseMoveEvent: " << x << " " << y;
    EvHandler_SendMessageToActivePID(BNS_EVENT_POINTING, TOUCH_ACTION_MOVE, (y << 16) | (x & 0xFFFF));
}


void EmuMainWindow::mousePressEvent(QMouseEvent *e)
{
    int x = e->x() - 10;
    int y = e->y() - 30;

    if(x < 0)
        x = 0;

    if(x > GRSYS_WIDTH)
        x = GRSYS_WIDTH;

    if(y < 0)
        y = 0;

    if(y > GRSYS_HEIGHT)
        y = GRSYS_HEIGHT;

    EvHandler_SendMessageToActivePID(BNS_EVENT_POINTING, TOUCH_ACTION_PRESS, (y << 16) | (x & 0xFFFF));
}


void EmuMainWindow::mouseReleaseEvent(QMouseEvent *e)
{
    int x = e->x() - 10;
    int y = e->y() - 30;

    if(x < 0)
        x = 0;

    if(x > GRSYS_WIDTH)
        x = GRSYS_WIDTH;

    if(y < 0)
        y = 0;

    if(y > GRSYS_HEIGHT)
        y = GRSYS_HEIGHT;

    EvHandler_SendMessageToActivePID(BNS_EVENT_POINTING, TOUCH_ACTION_RELEASE, (y << 16) | (x & 0xFFFF));
}


void EmuMainWindow::timer_timeout()
{
    QQTimer *t = (QQTimer *)sender();
    long id = reinterpret_cast<long>(t->user);

    //printf("timer_timeout: %d\n", id);

    if(id > -1 && id < 128 && cur_window->m_timers[id]) {

        //printf("timer_timeout: %d\n", id);
        EvHandler_SendMessageToActivePID(BNS_EVENT_TIMER, id, 0);
    }
}


void EmuMainWindow::orientationChange()
{
    //lg_general_motion_sensor_event(rotated? 2 : 1);
    //MsgHandler_SendMessageToActivePID(MSG_, id, 0);
}


QImage *GetScreenQImage() {
    return cur_window? cur_window->img : 0;
}


extern "C" void TaskMngr_AppExit(int, int, int)
{
    cur_window->close();
}


extern "C" void *Graphics_GetScreenBuffer()
{
    return (void*)cur_window->img->bits();
}


extern "C" unsigned short Graphics_GetScreenWidth()
{
    return cur_window->img->width();
}


extern "C" unsigned short Graphics_GetScreenHeight()
{
    return cur_window->img->height();
}


extern "C" unsigned char Graphics_GetScreenDepth()
{
    return cur_window->img->depth();
}


extern "C" void Graphics_Repaint()
{
    cur_window->repaintReq ++;
    cur_window->repaint(10, 10, cur_window->img->width(), cur_window->img->height());
}


extern "C" void GrSys_Refresh()
{
    cur_window->update_();
}


extern "C" int Timer_CreateEvent(int id, int msec, int start_msec)
{
    ((void)start_msec);

    if(cur_window->m_timers[id]) {
        //delete cur_window->m_timers[id];
        //cur_window->m_timers[id] = 0;

        printf("Timer already created!\n");
        return 0;
    }

    //printf("Create timer %d\n", id);

    QQTimer *t = new QQTimer();
    cur_window->m_timers[id] = t;
    t->user = (void*)((long)id);
    cur_window->connect(t, SIGNAL(timeout()), cur_window, SLOT(timer_timeout()));

    t->start(msec);
    return 1;
}


extern "C" int Timer_KillEvent(int id)
{
    if(!cur_window->m_timers[id]) {
        return 0;
    }

    //printf("Kill timer %d\n", id);

    QQTimer *t = cur_window->m_timers[id];
    t->user = (void*)100500;

    cur_window->disconnect(t, SIGNAL(timeout()));
    delete t;

    cur_window->m_timers[id] = 0;
    return 1;
}


extern "C" int Graphics_ChangeGDI(int id)
{
    cur_window->rotated = id == 0? false : true;


    delete cur_window->img;

    if(cur_window->rotated)
        cur_window->img = new QImage(400, 240, QImage::Format_RGB16);
    else
        cur_window->img = new QImage(240, 400, QImage::Format_RGB16);

    cur_window->EmuMainWindow::resize(cur_window->img->width()+20, cur_window->img->height()+30);

    return 0;
}


extern "C" int GrSys_GetGDIID()
{
    if(cur_window->rotated)
        return 1;

    else
        return 2;
}


extern "C" void GrSys_SelectGDI(int id)
{
    // FIXME
}





extern "C" int RegisterApplicationEventListener( ELF_PARASITE_INFO *pi,
                                      int (*handler)(unsigned long event_id, unsigned long wparam, unsigned long lparam),
                                      const wchar_t *name )
{
    _current_cb_process = handler;
    return 1;
}


extern "C" BOOL	EvHandler_PostEvent(T_HANDLE hDst, T_EVENT EventType, T_PARAM wParam, T_PARAM lParam)
{
    return 1;
}


extern "C" BOOL	EvHandler_SendEvent(T_HANDLE hDst, T_EVENT EventType, T_PARAM wParam, T_PARAM lParam)
{
    return 1;
}


extern "C" void	EvHandler_FlushEvent(T_HANDLE hDst)
{

}


extern "C" int MsgHandler_RegisterProcessor(T_ID id, MsgHandler_Callback cb)
{
    msg_handlers[id] = MsgHandlerData(cb);
    return 0;
}


extern "C" int MsgHandler_SetActivePID(T_ID id)
{
    for(auto it = msg_handler_active_pid.rbegin(); it != msg_handler_active_pid.rend(); ++it) {
        MsgHandler_SendMessage((*it), MSG_EXIT, 0, 0);
    }

    msg_handler_active_pid.clear();
    msg_handler_active_pid.push_back(id);
    MsgHandler_SendMessageToActiveID(MSG_INIT, 0, 0);
    MsgHandler_SendMessageToActiveID(MSG_DRAW, 0, 0);
    return 0;
}


extern "C" int MsgHandler_InsertActivePID(T_ID id)
{
    MsgHandler_SendMessageToActiveID(MSG_SLEEP, 0, 0);

    msg_handler_active_pid.push_back(id);
    MsgHandler_SendMessageToActiveID(MSG_INIT, 0, 0);
    MsgHandler_SendMessageToActiveID(MSG_DRAW, 0, 0);
    return 0;
}


BOOL MsgHandler_RemoveActiveProcessor()
{
    if(msg_handler_active_pid.empty())
        return FALSE;

    MsgHandler_SendMessageToActiveID(MSG_EXIT, 0, 0);
    msg_handler_active_pid.erase( ( --msg_handler_active_pid.end()) );

    MsgHandler_SendMessageToActiveID(MSG_AWAKE, 0, 0);
    return true;
}


extern "C" int MsgHandler_Terminate()
{
    for(auto it = msg_handler_active_pid.rbegin(); it != msg_handler_active_pid.rend(); ++it) {
        MsgHandler_SendMessage((*it), MSG_EXIT, 0, 0);
    }

    msg_handlers.clear();
    return 0;
}


extern "C" int MsgHandler_SendMessage(T_ID id, unsigned long event, unsigned long p1, unsigned long p2)
{
    auto it = msg_handlers.find(id);
    if(it != msg_handlers.end()) {

        cur_window->doLater([=]() {
            (*it).cb(event, p1, p2);
        });
        return 0;
    }

    return -1;
}


void MsgHandler_SendMessageToActiveID(unsigned long event, unsigned long p1, unsigned long p2)
{
    if(!msg_handler_active_pid.empty()) {
        MsgHandler_SendMessage(msg_handler_active_pid.back(), event, p1, p2);
    }
}


extern "C" void MsgHandler_SetParam(int id, unsigned long p)
{
    if(!msg_handler_active_pid.empty()) {

        auto it = msg_handlers.find(id);
        if(it != msg_handlers.end()) {
            (*it).params[id] = p;
        }
    }
}


extern "C" unsigned long MsgHandler_GetParam(int id)
{
    if(!msg_handler_active_pid.empty()) {
        auto it = msg_handlers.find(id);
        if(it != msg_handlers.end()) {
            return (*it).params[id];
        }
    }

    return 0;
}


extern "C" int MsgHandler_Translate(unsigned long ev, unsigned long p1, unsigned long p2)
{

    if(ev <= BNS_EVENT_SUSPEND) {
        MsgHandler_SendMessageToActiveID(ev, p1, p2);

    } else if(ev >= BNS_EVENT_KEYDOWN && ev < BNS_EVENT_REPEATKEY) {
        MsgHandler_SendMessageToActiveID(ev-BNS_EVENT_KEYDOWN, p1, p2);

    } else if(ev >= BNS_EVENT_TIMER && ev <= BNS_EVENT_PAINT ) {
        MsgHandler_SendMessageToActiveID(ev != BNS_EVENT_PAINT? MSG_TIMER : MSG_DRAW, p1, p2);

    } else if(ev >= BNS_EVENT_POINTING && ev <= BNS_EVENT_INDICATOR ) {
        MsgHandler_SendMessageToActiveID(MSG_POINTING + (ev-BNS_EVENT_POINTING), p1, p2);
    }

    return 0;
}


extern "C" int MsgHandler_FlushMessage(T_ID )
{
    return 0;
}


extern "C" int SetUP_GetHandle()
{
    return 0;
}


extern "C" void SetUP_CloseHandle(int )
{
}


extern "C" int SetUP_SetTouchpadSensitivity(int , unsigned char , unsigned short )
{
    return -1;
}
