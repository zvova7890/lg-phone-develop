#ifndef MEDIAPLAYER_H
#define MEDIAPLAYER_H

#include <signals/signal.h>
#include <Graph/Image.h>
#include <Core/Timer.h>
#include <string>

class MediaPlayer
{
public:

    typedef signal_slot::multi_signal<MediaPlayer *> signal;

    MediaPlayer();
    ~MediaPlayer();



    bool play(const std::string &m_resource = "", int from_ms = 0);
    bool stop();
    bool pause();
    bool resume();
    bool seek(unsigned long ms);


    void setVolume(int vol);
    int volume() const;

    void incrementVolume();
    void decrementVolume();

    unsigned int length() const;
    unsigned int position();

    bool isPlaying() const {
        return m_isPlaying;
    }

    bool isPause() const {
        return m_isPause;
    }

    const Image & albymImage() {
        return m_img;
    }

    bool isHaveAlbymImage() const {
        return !m_img.isEmpty();
    }

    const std::string & file() const {
        return m_resource;
    }


    signal & endAction() {
        return m_endAction;
    }

    static void cb_timer(T_HANDLE, H_TIMERCORE hTimerCore, int );

private:
    signal m_endAction;
    std::string m_resource;
    int m_volume;
    unsigned long m_pausedPos;
    unsigned long m_msec;
    bool m_isPlaying;
    bool m_isPause;
    Image m_img;
    //Timer m_end;
    int m_delayAfterEnd;
};

#endif // MEDIAPLAYER_H
