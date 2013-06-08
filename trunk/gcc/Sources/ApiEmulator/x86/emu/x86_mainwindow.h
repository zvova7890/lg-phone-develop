#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <QTimer>
#include <QTime>
#include <QMouseEvent>
#include <gl.h>



namespace Ui {
class MainWindow;
}


class TimerUserData : public QObjectUserData
{
public:

    TimerUserData(void *user) {
        data = user;
    }

    virtual ~TimerUserData() {

    }

    void *data;
};




class QQTimer : public QTimer
{
public:
    QQTimer(QObject *parent = 0) :
        QTimer(parent)
    {
    }

    virtual ~QQTimer() {

    }

    void *user;
};

class EmuMainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit EmuMainWindow(QWidget *parent = 0);
    ~EmuMainWindow();

    void ololo_test(int a, int b);
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);

public slots:
    void update_();
    void update_(int x , int y, int w, int h);
    void timer_timeout();
    void orientationChange();
    void doLaterSlot(void *);

signals:
    void _doLater(void *);

public:
    void doLater(std::function<void()> );

public:
    Ui::MainWindow *ui;
    QImage *img;
    GLContext *gl_context;

    int repaintReq;

    int fps, fps_cnt, last_time;
    int off_x, off_y;
    bool rotated;

    QQTimer *m_timers[128];
};

#endif // MAINWINDOW_H
