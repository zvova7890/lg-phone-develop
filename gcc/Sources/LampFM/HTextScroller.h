#ifndef HTEXTSCROLLER_H
#define HTEXTSCROLLER_H

#include <Graph/Rect.h>
#include <EventManager.h>
#include <Core/Timer.h>
#include <string>



class HTextScroller : private Timer
{
public:

    typedef signal_slot::multi_signal<HTextScroller*> signal;

    HTextScroller(EventManager *em, const Rect &r = Rect() );
    ~HTextScroller();

    void start(int speed);
    void stop();
    void reset();

    void pause();
    void resume();

    void paintEvent();
    void setRect(const Rect &);
    void setText(const std::string &, bool reset = true);

    inline void setTextSize(int s) {
        m_textSize = s;
        recalcTextWidth();
    }

    inline void setTextAttrs(int attrs) {
        m_textAttrs = attrs;
        recalcTextWidth();
    }

    inline bool isActive() {
        return m_isActive;
    }

    signal & onTextSmallerSignal() {
        return m_textSmallerThan;
    }


protected:
    void timerEvent();
    void recalcTextWidth();

private:
    Rect m_rect;
    std::string m_text;
    int m_speed, m_pos, m_textAttrs;
    signed char m_moveSign;
    char m_textSize;
    bool m_leftScroll, m_isActive, m_update;
    EventManager *m_eventMngr;

    int m_textWidth;
    signal m_textSmallerThan;
};

#endif // HTEXTSCROLLER_H
