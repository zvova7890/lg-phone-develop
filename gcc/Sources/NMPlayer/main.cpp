
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


#include <Api/ApiLinkLib/ApiLink.h>
#include <gl.h>
#include <taskapi.h>
#include <loader.h>

#include <Widget/Widget.h>
#include <Widget/HTextScroller.h>
#include <Widget/Button.h>
#include <Widget/Separator.h>
#include <Widget/TabBox.h>
#include <Widget/ListMenu.h>
#include <Core/Timer.h>
#include <Core/Application.h>
#include <Widget/MainWindow.h>

#include "MediaPlayer.h"
#include "ResourceManager.h"
#include "MyMainWindow.h"


/*===================================================================*/
/*============================ GUI ==================================*/
/*===================================================================*/

char file[256];

ResourceManager *resource_manager = 0;
EventManager *event_manager;
MyMainWindow *main_window = 0;


class MyApplication : public Application
{
public:

    MyApplication()
    {
        glActivateContext( glCreateContext(GRSYS_WIDTH, GRSYS_HEIGHT, 16, GrSys_GetGrBuf()) );
        glEnable(GL_ALPHA_TEST);
    }

    ~MyApplication()
    {
        delete resource_manager;
        delete event_manager;
        delete player;

        glDestroyContext(glActiveContext());
    }

    void constructEvent(int argc, char *argv[])
    {
        if(argc > 1)
            strcpy(file, argv[1]);
        else
            file[0] = 0;

        resource_manager = new ResourceManager(applicationDir());
        event_manager = new EventManager();
        player = new MediaPlayer();

    }

    void initEvent()
    {
        player->play(file);
        main_window = new MyMainWindow(event_manager, player);

    }

    void releaseEvent()
    {
        delete main_window;
    }

    bool eventFilter(unsigned long event, unsigned long p1, unsigned long p2)
    {
        if(main_window)
            main_window->applicationEvent(event, p1, p2);
        return true;
    }


private:
    MediaPlayer *player;
};




MyApplication application;



int main(int argc, char *argv[])
{
    GL_UNUSED(argc);
    GL_UNUSED(argv);

    file[0] = 0;
    if(argc > 1) {
        if(!memcmp(argv[1], "/usr/", 5))
            strcpy(file, argv[1]+4);
        else
            strcpy(file, argv[1]);
    }


    application.construct(argc, argv, "NMPlayer");
    return 0;
}


