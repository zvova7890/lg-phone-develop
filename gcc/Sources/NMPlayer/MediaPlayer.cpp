
#include <Api/ApiLinkLib/ApiLink.h>
#include "MediaPlayer.h"
#include "MSOEM_Player.h"
#include <Core/Application.h>
#include <Widget/MainWindow.h>
#include <MyMainWindow.h>


extern Application application;
extern MyMainWindow *main_window;
static MediaPlayer *player = 0;

static H_TIMERCORE timer = 0;

void MediaPlayer::cb_timer(T_HANDLE, H_TIMERCORE hTimerCore, int )
{
    player->m_endAction.trigger(player);

    TimerCore_KillTimer(timer);
    timer = 0;
}


void startTimer(int duration)
{
    if(timer)
        TimerCore_KillTimer(timer);
    timer = TimerCore_SetTimer(application.process(), duration, 0, 0, MediaPlayer::cb_timer);
}


void stopTimer()
{
    if(timer)
        TimerCore_KillTimer(timer);
    timer = 0;
}


MediaPlayer::MediaPlayer() :
    m_volume(10),
    m_isPlaying(false),
    m_isPause(true),
    m_delayAfterEnd(400)
{
    player = this;

    /*m_end.timerEventSignal().connect( [this](Timer *t){
        m_endAction.trigger(this);
        t->stop();
    });*/
}


MediaPlayer::~MediaPlayer()
{
    stopTimer();
    stop();
}


bool MediaPlayer::play(const std::string &resource, int from_ms)
{
    if(m_isPlaying)
        stop();

    if(resource.empty() && m_resource.empty())
        return false;

    if(!resource.empty())
        m_resource = resource;

    U_CHAR lol[512] = {0};
    UniLib_UTF8ToUCS2((char *)m_resource.c_str(), lol);


    T_MSFPLAYER_MEDIA_SPEC info;
    memset(&info, 0, sizeof(info));
    m_img.clear();


    if(!MSOEM_Player_GetMediaSpec(lol, 0, &info, 0)) {
        m_msec = info.dwDuration;

        if( info.ExtendedInfo.StdSpec.pbAlbumImg ) {

            //printf("pImgBuf %X\n", info.ExtendedInfo.StdSpec.pbAlbumImg);
                //m_img = Image(minfo.unAPicWidth, minfo.unAPicHeight, 16, (char*)minfo.pAttachedPic, true);
        }

        /*FILE *fp = fopen("/zbin/dump.bin", "w+");
        if(fp) {

            fwrite(&minfo, sizeof(minfo), 1, fp);
            fclose(fp);
        }*/

        printf("Length: %d\n", info.dwDuration / 1000);
    } else {
        printf("Ololoev vam\n");
    }


    int r = MSOEM_Player_Init(lol, 0);

    if(!r)
        MSOEM_Player_Start(from_ms);

    setVolume(volume());

    m_isPlaying = (r == 0);
    m_isPause = !m_isPlaying;

    startTimer(m_msec - from_ms+m_delayAfterEnd);
    //m_end.start(m_msec - from_ms+m_delayAfterEnd);

    printf("ret: %d\n", r);
    return r == 0;
}


bool MediaPlayer::stop()
{
    if(m_isPlaying)
    {
        m_isPlaying = false;
        m_isPause = true;
        m_msec = 0;
        m_pausedPos = 0;
        //m_end.stop();
        stopTimer();
        return MSOEM_Player_Stop() == 0;
    }

    return false;
}


bool MediaPlayer::pause()
{
    m_isPause = true;
    //m_end.stop();
    stopTimer();
    m_pausedPos = position();
    return MSOEM_Player_Pause( 0 ) == 0;
}


bool MediaPlayer::resume()
{
    m_isPause = false;
    //return MSOEM_Player_Resume( 0 ) == 0;

    //m_end.start(m_msec - m_pausedPos +m_delayAfterEnd);
    startTimer(m_msec - m_pausedPos+m_delayAfterEnd);
    return MSOEM_Player_Start(m_pausedPos) == 0;
}


bool MediaPlayer::seek(unsigned long ms)
{
    MSOEM_Player_Pause( 0 );
    bool r = MSOEM_Player_Start(ms) == 0;
    m_pausedPos = position();
    //m_end.start(m_msec - m_pausedPos +m_delayAfterEnd);
    startTimer(m_msec - m_pausedPos+m_delayAfterEnd);
    return r;
}


void MediaPlayer::setVolume(int vol)
{
    if(vol < 0 || vol > 30)
        return;

    m_volume = vol;
    MSOEM_Player_SetParam(MSFPLAYER_PARAM_SET_VOLUME, m_volume, 0);
}


int MediaPlayer::volume() const
{
    return m_volume;
}


void MediaPlayer::incrementVolume()
{
    setVolume(volume()+1);
}


void MediaPlayer::decrementVolume()
{
    setVolume(volume()-1);
}


unsigned int MediaPlayer::position()
{
    int pos, lol;

    MSOEM_Player_GetParam(10308, &pos, &lol);

    //printf("GetPlayPos: %d - %d\n", pos, m_msec);
    return pos;
}


unsigned int MediaPlayer::length() const
{
    return m_msec;
}
