#ifndef MYMAINWINDOW_H
#define MYMAINWINDOW_H


#include <Widget/MainWindow.h>
#include <Widget/HTextScroller.h>
#include <Widget/Button.h>
#include <Widget/TabBox.h>
#include <Widget/ListMenu.h>
#include <Widget/Separator.h>
#include "Positioner.h"
#include "MediaPlayer.h"



class MyMainWindow : public MainWindow
{
public:
    MyMainWindow(EventManager *event_manager, MediaPlayer *p);
    virtual ~MyMainWindow();

    void scanFolder();
    void setupMediaButtons();
    void tabBoxChanged(TabBox *, int last_idx, int idx);
    void playByIndex(int);
    void playNext();
    void playPrev();

    void paintEvent();
    void initEvent();
    void releaseEvent();
    void suspendEvent();
    void resumeEvent();
    void keyEvent(int type, int key);
    void touchEvent(int action, int x, int y);
    bool eventFilter(unsigned long, unsigned long, unsigned long);


private:
    std::string m_workFolder;
    std::string m_playFile;
    HTextScroller m_headText;
    std::vector<Button*> m_buttons;
    std::vector<Separator*> m_separators;
    ButtonStyle m_style;
    Positioner m_playPos;
    Timer m_timer;
    Button *m_lastTouchedButton;
    Rect m_tabButtonSizes;
    TabBox m_functionalTab;
    Button m_stopButton;
    Button m_prevButton;
    Button m_playButton;
    Button m_nextButton;
    ListMenu m_mediaList;
    Image m_musicImage;

    Image *m_playImg,
          *m_stopImg,
          *m_pauseImg,
          *m_prevImg,
          *m_nextImg;

    int setup_handle;
    MediaPlayer *m_player;
    Timer volumeTimer;
    ListMenuItem *m_currentPlayedItem;
};

#endif // MYMAINWINDOW_H
