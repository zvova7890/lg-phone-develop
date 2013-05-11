

#include <loader.h>

#include <Core/compatible.h>
#include "Application.h"



static Application *that = 0;


int Application::event_listener(unsigned long event_id, unsigned long wparam, unsigned long lparam)
{
    if(!that->eventFilter(event_id, wparam, lparam)) {
        return 1;
    }

    switch (event_id)
    {
        case BNS_EVENT_START:
            that->initEvent();
            break;

        case BNS_EVENT_TERMINATE:

            that->releaseEvent();
            ElfDestroy();
            break;

        case BNS_EVENT_SUSPEND:
            that->suspendEvent();
            break;

        case BNS_EVENT_RESUME:
            that->resumeEvent();
            break;

        case BNS_EVENT_MOTION_SENSOR:
            that->motionSensorEvent(wparam); // FIXME
            break;

        case BNS_EVENT_KEYUP:
            that->keyEvent(KEY_UP, wparam);
            break;

        case BNS_EVENT_KEYDOWN:
            that->keyEvent(KEY_DOWN, wparam);
            break;

        case BNS_EVENT_POINTING:
        {
            int x, y;
            x = lparam & 0xFFFF;
            y = (lparam >> 16) & 0xFFFF;

            if( GrSys_GetGDIID() == 1 ) {
                /* retranslate coordinates */
                int t = x;

                x = y;
                y = 240-t;
            }

            that->touchEvent(wparam, x, y);
            break;
        }
    }

    return 1;
}



Application::Application()
{
    that = this;
}


Application::~Application()
{

}


void Application::construct(int argc, char *argv[], const std::string &name)
{
    if(argc > 0) {
        const char *at = strrchr(argv[0], '/');
        if(at) {

            m_appDir.assign(argv[0], 0, at-argv[0]+1);
            m_appName = at;
        }
    }

    static ELF_PARASITE_INFO parasite;
    wchar_t wname[256];

    UniLib_UTF8ToUCS2((char*)name.c_str(), wname);

    m_applicationId = RegisterApplicationEventListener(&parasite, event_listener, wname);

    constructEvent(argc, argv);
}


std::string Application::applicationDir() const
{
    return m_appDir;
}


std::string Application::applicationName() const
{
    return m_appName;
}


void Application::constructEvent(int , char *[])
{

}


bool Application::eventFilter(unsigned long, unsigned long, unsigned long)
{
    return true;
}


void Application::paintEvent()
{

}


void Application::initEvent()
{

}


void Application::releaseEvent()
{

}


void Application::keyEvent(int , int )
{

}


void Application::touchEvent(int , int , int )
{

}


void Application::motionSensorEvent(int )
{

}


void Application::suspendEvent()
{

}


void Application::resumeEvent()
{

}

