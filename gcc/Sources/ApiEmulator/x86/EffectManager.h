#ifndef EFFECTMANAGER_H
#define EFFECTMANAGER_H


#include <Widget/EventManager.h>
#include <Widget/Widget.h>
#include <signals/signal.h>
#include <Core/Timer.h>

#include <Graph/Image.h>
#include <map>


class EffectManager : public Widget
{
public:
    enum  {

        EFFEC_UP    = 0,
        EFFEC_DOWN  = (1 << 1),
        EFFEC_LEFT  = (1 << 2),
        EFFEC_RIGHT = (1 << 3),
        EFFECT_ALPHA_IN = (1 << 4),
        EFFECT_ALPHA_OUT = (1 << 5)

    }Flags;

public:


public:
    EffectManager(Widget *parent);
    virtual ~EffectManager();
    virtual void paintEvent();
    virtual void touchEvent(int action, int x, int y);
    void resizeEvent();

    void addEffect(const std::string &effect, std::function<void(EffectManager*)> f);

    void reset();
    void start(const std::string &effect, int flags, int state = 10, int speed = 8, int delay = 3);
    void stop();


    inline void pushPrevScreen(const Image &img) {
        prev_img = img;
    }

    inline void pushNextScreen(const Image &img) {
        next_img = img;
    }


    inline int flags() const {
        return m_flags;
    }

    inline int state() {
        return m_state;
    }

    inline void setState(int state) {
        m_state = state;
    }


    inline int speed() {
        return m_speed;
    }

    inline void setSpeed(int speed) {
        m_speed = speed;
    }


    typedef signal_slot::multi_signal <EffectManager *> signal;
    static typename signal_slot::multi_signal <EffectManager *> &_sig;

    signal & effectFinished() {
        return m_effectFinished;
    }

private:
    void timerEvent(Timer *);

    void scaleEffect(EffectManager *);
    void moveEffect(EffectManager *);
    void alphaEffect(EffectManager *);
    void alphaZoomEffect(EffectManager *);
    void zoomEffect(EffectManager *);
    void conveyorEffect(EffectManager *);

private:
    Widget::wid my_wid;
    std::map<std::string, std::function<void(EffectManager*)> > m_effects;
    std::map<std::string, std::function<void(EffectManager*)> >::iterator m_currentEffect;
    signal m_effectFinished;
    int m_speed, m_state;
    Image prev_img, next_img, tmp_img;
    Timer timer;
    int be_updated;
    bool m_isActive;
    int m_flags;
};

#endif // EFFECTMANAGER_H
