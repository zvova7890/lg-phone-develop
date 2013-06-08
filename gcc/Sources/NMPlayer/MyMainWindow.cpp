
#include <Core/compatible.h>
#include <Core/Rect.h>
#include <Core/Thread.h>
#include <fs.h>
#include <pxeapi_misc.h>
#include "ResourceManager.h"
#include "MyMainWindow.h"
#include "taskapi.h"


extern "C" void __timer_notifier(int);
extern ResourceManager *resource_manager;
extern Application *application;



std::string path2name(const std::string &s)
{
    std::string r;

    auto pos = s.find_last_of('/');
    if(pos != std::string::npos) {

        pos += 1;
        r.assign(s, pos, s.length()-pos);
    }

    return r;
}


std::string path2dir(const std::string &s)
{
    std::string r;

    auto pos = s.find_last_of('/');
    if(pos != std::string::npos) {

        pos += 1;
        r.assign(s, 0, pos);
    }

    return r;
}


MyMainWindow::MyMainWindow(EventManager *event_manager, MediaPlayer *p) :
    MainWindow(0, Rect(0, 0, GRSYS_WIDTH, GRSYS_HEIGHT), event_manager),
    m_headText(event_manager, Rect(rect().x(), rect().y(), rect().w(), 24)),
    m_playPos(Rect(), this),
    m_lastTouchedButton(0),
    m_functionalTab(Rect(0, rect().h()-48, rect().w(), 48), this, TabBox::Horizontal),
    m_stopButton(Rect(), this, ""),
    m_prevButton(Rect(), this, ""),
    m_playButton(Rect(), this, ""),
    m_nextButton(Rect(), this, ""),
    m_mediaList(Rect(4, 0, rect().w()-8, 0), this),
    m_musicImage(resource_manager->image("music")),
    setup_handle(-1),
    m_player(p),
    m_currentPlayedItem(0)
{
    setup_handle = SetUP_GetHandle();

    m_playImg  = &resource_manager->image("play");
    m_stopImg  = &resource_manager->image("stop");
    m_pauseImg = &resource_manager->image("pause");
    m_prevImg  = &resource_manager->image("prev");
    m_nextImg  = &resource_manager->image("next");

    m_headText.setText( path2name(m_player->file()) );
    m_headText.start(200);
    m_headText.setTextSize(18);
    m_headText.setTextAttrs(FT_TEXT_H_CENTER);

    m_playPos.setSize( Rect(9, rect().h()-78, rect().w()-18, 16) );
    m_playPos.show();

    m_playPos.positionSelected().connect( [this](int pos) {
        //printf("Percent: %d\n", pos);

        unsigned int ms = m_player->length()*pos / 100;
        m_player->seek(ms);
    });

    //m_timer.start(1000);
    m_timer.timerEventSignal().connect( [this](Timer *) {
        eventManager()->updateAfterEvent();
    });


    m_functionalTab.show();
    m_functionalTab.addTab("List");
    m_functionalTab.addTab("Play");
    m_functionalTab.addTab("Info");
    m_functionalTab.addTab("Exit");

    m_functionalTab.setFocusTab(1);

    m_functionalTab.onTabChanged().connect( this, &MyMainWindow::tabBoxChanged,
                                            std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);

    setupMediaButtons();


    ListMenuStyle menu_style = m_mediaList.style();

    menu_style.setShadow( Brush() );
    menu_style.setBackground( Brush() );

    m_mediaList.setStyle(menu_style);

    Rect rc =  m_mediaList.rect();
    rc.setY(m_headText.size().h() + m_prevButton.rect().h()+10);
    rc.setH( rect().h() - (m_mediaList.rect().y() + (rect().h() - m_playPos.rect().y()) + 90 ));

    m_mediaList.setSize(rc);


    m_mediaList.resizeEvent();

    scanFolder();

    m_player->endAction().connect( [this](MediaPlayer *){
        playNext();
    });
}


MyMainWindow::~MyMainWindow() {

    std::vector<Widget*> ll = m_mediaList.scrollArea().items();
    for(Widget *w : ll)
        delete w;

    m_mediaList.scrollArea().clear();

    m_headText.stop();

    SetUP_CloseHandle(setup_handle);
}



void MyMainWindow::scanFolder() {

    const std::string &m_file = m_player->file();
    const char *f = strrchr(m_file.c_str(), '/');

    if(!f)
        return;

    ++f;

    m_playFile = m_file;

    char folder[128];
    memcpy(folder, m_file.c_str(), f-m_file.c_str());
    folder[f-m_file.c_str()] = 0;

    m_workFolder = folder;

    int h = fs_opendir(folder);

    printf("open %s - %d\n", folder, h);

    std::string fname = path2name(m_playFile);

    if(h > 0) {
        FS_INFO info;
        while(!fs_readdir(h, &info)) {

            if(!(info.attr & FS_ATTR_FOLDER)) {

                ListMenuItem *mi = 0;
                m_mediaList.scrollArea().addItem(
                           (mi = new ListMenuItem(&m_mediaList, m_mediaList.rect().w(), 40, info.name)) );

                if(info.name == fname) {
                    mi->setIcon( &resource_manager->image("played") );
                    m_currentPlayedItem = mi;

                } else
                    mi->setIcon( &resource_manager->image("music_small") );

                mi->onReleasedSignal().connect( [this](ListMenuItem *i) {
                    m_playFile = m_workFolder + i->text();
                    m_player->play(m_playFile);
                    m_headText.setText(i->text());
                    m_headText.start(200);

                    m_currentPlayedItem->setIcon( &resource_manager->image("music_small") );
                    i->setIcon( &resource_manager->image("played") );

                    m_currentPlayedItem = i;
                    eventManager()->updateAfterEvent();
                });
            }
        }

        fs_closedir(h);
    }



    m_mediaList.scrollArea().setLinesCount(m_mediaList.scrollArea().items().size());
}


void MyMainWindow::setupMediaButtons()
{

    auto paintBackground = [](const Rect &r, GLColor begin, GLColor ) {
        /*GLGradient g;
        glAllocateGradient(&g, 2);

        g.colors[0].color  = begin; //0xFF2a0708;
        g.colors[0].pixels = r.h();

        g.colors[1].color  = end; //0xFF8f0f0f;

        glDrawGradient(r.x(), r.y(), r.w(), r.h(), 2, &g);
        glDestroyGradient(&g);*/

        glSetPen(begin);
        glDrawFilledRectange(r.x(), r.y(), r.x2(), r.y2());
    };

    ButtonStyle bstyle;

    //bstyle.setBorder(Brush(0xFFFFFFFF, false));
    //bstyle.setPressedBorder(Brush(0xFFFFFFFF, false));
    bstyle.setBorder(Brush());
    bstyle.setPressedBorder(Brush());

    bstyle.setRoundedRect(false);
    bstyle.setShadowAfterBackground(true);
    bstyle.setFontFlags( bstyle.fontFlags() | FT_TEXT_NOCALC_HCENTER );

    bstyle.setBackground( Brush( [&paintBackground](Brush &, const Rect &r) {
         paintBackground(r, 0xFF000000, 0xFF000000);
    } ));


    bstyle.setPressedBackground( Brush( [&paintBackground](Brush &, const Rect &r) {
         paintBackground(r, 0xFF000000, 0xFF000000);
    } ));




    int width = (rect().w()) / 4;
    int xpos = 0;

    m_stopButton.setSize(Rect(xpos, m_headText.size().y2()+2, width, 40));
    m_stopButton.setStyle(bstyle);
    m_stopButton.setIcon(m_stopImg);
    xpos += m_stopButton.rect().w();
    m_stopButton.releasedSignal().connect( [this](Button *) {
        m_player->stop();
        m_playButton.setIcon(m_playImg);
    });

    m_prevButton.setSize(Rect(xpos, m_headText.size().y2()+2, width, 40));
    m_prevButton.setStyle(bstyle);
    m_prevButton.setIcon(m_prevImg);
    xpos += m_prevButton.rect().w();
    m_prevButton.releasedSignal().connect( [this](Button *) {
        playPrev();
    });


    m_playButton.setSize(Rect(xpos, m_headText.size().y2()+2, width, 40));
    m_playButton.setStyle(bstyle);
    m_playButton.setIcon( m_player->isPlaying()? m_pauseImg : m_playImg );

    xpos += m_playButton.rect().w();

    m_playButton.releasedSignal().connect( [this](Button *b) {

        if(m_player->isPlaying()) {
            if(!m_player->isPause()) {
                m_player->pause();
                b->setIcon(m_playImg);

            } else {
                m_player->resume();
                b->setIcon(m_pauseImg);
            }

        } else {
            m_player->play(m_playFile);
            b->setIcon(m_pauseImg);
        }

        b->eventManager()->updateAfterEvent();
    } );


    m_nextButton.setSize(Rect(xpos, m_headText.size().y2()+2, width, 40));
    m_nextButton.setStyle(bstyle);
    m_nextButton.setIcon(m_nextImg);
    m_nextButton.releasedSignal().connect( [this](Button *) {
        playNext();
    });


    m_prevButton.show();
    m_stopButton.show();
    m_playButton.show();
    m_nextButton.show();


}


void MyMainWindow::playByIndex(int idx)
{
    if((unsigned)idx >= (unsigned)m_mediaList.scrollArea().count())
        return;

    ListMenuItem *itm = (ListMenuItem*)m_mediaList.scrollArea().widgetItem(idx);

    m_currentPlayedItem->setIcon( &resource_manager->image("music_small") );
    itm->setIcon( &resource_manager->image("played") );
    m_currentPlayedItem = itm;


    m_mediaList.scrollArea().setItem(idx);
    //m_mediaList.scrollArea().fixupViewPosition();

    m_player->play( path2dir(m_playFile) + itm->text() );
    m_headText.setText(itm->text());
}


void MyMainWindow::playNext()
{
    if(m_mediaList.scrollArea().count() < 1)
        return;

    int idx = m_currentPlayedItem->id() + 1;

    if(idx >= m_mediaList.scrollArea().count())
        idx = 0;


    playByIndex(idx);
}


void MyMainWindow::playPrev()
{
    if(m_mediaList.scrollArea().count() < 1)
        return;

    int idx = m_currentPlayedItem->id() - 1;

    if(idx < 0)
        idx = m_mediaList.scrollArea().count()-1;

    playByIndex(idx);
}


void MyMainWindow::tabBoxChanged(TabBox *, int last_idx, int idx)
{
    if(idx == 3)
        TaskMngr_AppExit(0, 0, 0);

    if(last_idx == 0)
        m_mediaList.hide();

    if(idx == 0)
        m_mediaList.show();
}




void MyMainWindow::paintEvent()
{
    Rect rc = realRect();

    glSetPen(0xFF1d1b1b);
    glDrawFilledRectange(rc.x(), rc.y(), rc.x2(), rc.y2());

    glSetPen(0xFFFFFFFF);
    glDrawHLine(rc.x(), rc.x2(), rc.y()+25);

    //glDrawString(filename, rect().x()+3, rect().y(), rect().x2(), rect().y()+25, 18, FT_TEXT_H_CENTER, 0, 128);
    m_headText.paintEvent();


    int mx, my;

    mx = rc.w() / 2 - m_musicImage.width()/2;
    my = m_mediaList.rect().h() / 2 - m_musicImage.height()/2;

    drawImage(rc.x()+mx, m_mediaList.rect().y()+my, &m_musicImage);

    if(!m_player->isPlaying()) {
        m_playPos.setPosition(0);
        m_playPos.setLength(0);

    } else {
        m_playPos.setPosition(m_player->position());
        m_playPos.setLength(m_player->length());


        if(m_player->isHaveAlbymImage())
            drawImage(rc.x(), m_playButton.realRect().y2(), &m_player->albymImage());
    }


    MainWindow::paintEvent();

    eventManager()->update();
}



void MyMainWindow::initEvent()
{
    eventManager()->setPaintFunc( [this](void*) {
        paintEvent();
    } );

    eventManager()->setRefreshFunc( [this](void*) {
        GrSys_Refresh();
    });
}


void MyMainWindow::releaseEvent()
{
    delete resource_manager;
}



void MyMainWindow::resumeEvent()
{
    GrSys_Refresh();
}



void MyMainWindow::suspendEvent()
{

}


void MyMainWindow::keyEvent(int type, int key)
{
    if(type == KEY_DOWN) {
        switch (key)
        {
            case KEY_CAMERA:
            {
                image_t img;

                img.bitmap = Graphics_GetScreenBuffer();
                img.w = GRSYS_WIDTH;
                img.h = GRSYS_HEIGHT;
                img.bit = 16;

                save_png_to_file (&img, "/usr/Zbin/shoot.png");
                break;
            }

            case KEY_SEND:
                break;

            case KEY_MULTI:
                TaskMngr_Show();
                break;

            case KEY_END:
                TaskMngr_AppExit(0, 0, 0);
                break;

            case BNS_VOLUP_K:
                m_player->incrementVolume();

                volumeTimer.timerEventSignal().clear();
                volumeTimer.timerEventSignal().connect( [this](Timer*) {

                    volumeTimer.stop();
                    eventManager()->notifyAfterEvent( [this]() {
                        volumeTimer.start(100);
                        volumeTimer.timerEventSignal().clear();
                        volumeTimer.timerEventSignal().connect( [this](Timer*) {
                            m_player->incrementVolume();
                        });
                    });
                });

                volumeTimer.start(800);
                break;

            case BNS_VOLDOWN_K:
                m_player->decrementVolume();

                volumeTimer.timerEventSignal().clear();
                volumeTimer.timerEventSignal().connect( [this](Timer*) {

                    volumeTimer.stop();

                    eventManager()->notifyAfterEvent( [this]() {
                        volumeTimer.start(100);
                        volumeTimer.timerEventSignal().clear();

                        volumeTimer.timerEventSignal().connect( [this](Timer*) {
                            m_player->decrementVolume();
                        });
                    });

                });

                volumeTimer.start(800);
                break;

        }
    }


    if(type == KEY_UP)
    {
        switch (key)
        {
            case BNS_VOLUP_K: case BNS_VOLDOWN_K:
                volumeTimer.stop();
                break;
        }
    }

    eventManager()->update();
}



bool MyMainWindow::eventFilter(unsigned long event, unsigned long p1, unsigned long )
{
    // Пока так, нужно для работы таймеров
    switch(event)
    {
        case MSG_TIMER:
        {
            __timer_notifier(p1);
            eventManager()->update();
            break;
        }
    }

    return true; // true - продолжить, false - пропустить
}



void MyMainWindow::touchEvent(int action, int x, int y)
{
    MainWindow::touchEvent(action, x, y);
    eventManager()->update();
}

