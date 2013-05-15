
#include <Core/compatible.h>
#include <pxeapi_graphics.h>
#include <gl.h>
#include "MainWindow.h"


int MainWindow::event_listener(unsigned long event, unsigned long p1, unsigned long p2)
{
    MainWindow *that = (MainWindow *)MsgHandler_GetParam(0);

    if(!that->eventFilter(event, p1, p2)) {
        return 1;
    }

    //printf("event: %d\n", event);

    /*auto rebaseGlContext = []() {
        glSetContextProp(glActiveContext(), GRSYS_WIDTH, GRSYS_HEIGHT, 16, Graphics_GetScreenBuffer());
    };*/

    switch(event)
    {
        case MSG_INIT:
            that->initEvent();
            break;

        case MSG_EXIT:
            that->releaseEvent();
            break;

        case /*MSG_AWAKE: case*/ MSG_RESUME:

            if( that->test_attr(CONTROL_GDI_STATE) )
                Graphics_ChangeGDI(that->m_orientationType);

            that->resumeEvent();
            break;

        case MSG_SLEEP:
            that->suspendEvent();
            break;

        case MSG_KEYDOWN:
            that->keyEvent(KEY_DOWN, p1);
            break;

        case MSG_KEYUP:
            that->keyEvent(KEY_UP, p1);
            break;

        case MSG_LONGKEY:
            that->keyEvent(KEY_LONG_PRESS, p1);
            break;

        case MSG_REPEATKEY:
            that->keyEvent(KEY_REPEAT, p1);
            break;

        case MSG_DRAW:
            that->paintEvent();
            break;

        case MSG_POINTING:
        {
            int action = p1;
            int x, y;

            x = p2 & 0xFFFF;
            y = (p2 >> 16) & 0xFFFF;

            if( that->test_attr(TRANSLATE_COORDS_WITH_GDI_STATE) && GrSys_GetGDIID() == 1 ) {
                int t = x;
                x = y;
                y = 240-t;
            }


            if( that->test_attr(TOUCHPAD_ADAPTIVE_SENSITIVITY) ) {
                static int last_action;

                if(action == TOUCH_ACTION_MOVE && last_action != 1) {
                    last_action = 1;
                    //Thread::sleep(2);
                    SetUP_SetTouchpadSensitivity(that->m_settingsHandler, TOUCHPAD_SENSITIVITY_SET, 1);

                } else if(action != TOUCH_ACTION_MOVE && last_action != 2) {
                    last_action = 2;
                    //Thread::sleep(2);
                    SetUP_SetTouchpadSensitivity(that->m_settingsHandler, TOUCHPAD_SENSITIVITY_SET, that->m_touchpadSensitivity);
                }
            }


            that->touchEvent(p1, x, y);
            break;
        }
    }



    that->lastOrientation = GrSys_GetGDIID();
    return 1;
}



MainWindow::MainWindow(int id, const Rect &r, EventManager *e) :
    Widget(r, e),
    m_id(id),
    m_touchpadSensitivity(9)
{
    MsgHandler_RegisterProcessor(m_id, event_listener);
    MsgHandler_SetActivePID(m_id);

    MsgHandler_SetParam(0, (unsigned long)this);
    //that = this;

    lastOrientation = m_orientationType = GrSys_GetGDIID();

    m_fixTmr.timerEventSignal().connect( [this](Timer *t) {

        if(GrSys_GetGDIID() != m_orientationType)
            Graphics_ChangeGDI(m_orientationType);
        else
            t->stop();
    });

    m_settingsHandler = SetUP_GetHandle();
    m_flags = CONTROL_GDI_STATE | TRANSLATE_COORDS_WITH_GDI_STATE | TOUCHPAD_ADAPTIVE_SENSITIVITY;
}


MainWindow::~MainWindow()
{
    SetUP_CloseHandle(m_settingsHandler);
    MsgHandler_Terminate();
}


void MainWindow::setTouchpadSensitivity(int v)
{
    m_touchpadSensitivity = v;
}


void MainWindow::initEvent()
{

}


void MainWindow::releaseEvent()
{

}



void MainWindow::keyEvent(int , int )
{

}



void MainWindow::suspendEvent()
{

}


void MainWindow::resumeEvent()
{

}


bool MainWindow::eventFilter(unsigned long, unsigned long, unsigned long)
{
    return true;
}


void MainWindow::applicationEvent(unsigned long event, unsigned long p1, unsigned long p2)
{
    switch (event)
    {
        case BNS_EVENT_SUSPEND:
            printf("BNS_EVENT_SUSPEND\n");
            MsgHandler_SendMessage(m_id, MSG_SLEEP, 0, 0);
            break;

        case BNS_EVENT_RESUME:
            printf("BNS_EVENT_RESUME\n");
            MsgHandler_SendMessage(m_id, MSG_RESUME, 0, 0);
            break;

        default:

            MsgHandler_Translate(event, p1, p2);
            break;
    }

    MsgHandler_FlushMessage(m_id);
}

