#ifndef EFFECTMANAGER_H
#define EFFECTMANAGER_H

#include "png_ops.h"
#include <TimerWrap.h>
#include "EventManager.h"
#include "UActiveArea.h"
#include <signals/signal.h>


enum Effects{
    EFFECT_CENTER_SCALE = 1,
    EFFECT_LEFT_SCALE,
    EFFECT_RIGHT_SCALE,
    EFFECT_LEFT_MOVE,
    EFFECT_RIGHT_MOVE,
    EFFECT_SUB_ALPHA,
    EFFECT_ADD_ALPHA,
    EFFECT_SUB_DOMINO,
    EFFECT_ADD_DOMINO
};


class EffectManager : public UActiveAreaItem<ActiveAreaItem>
{
public:
    EffectManager(UActiveArea *parent, EventManager *e);
    ~EffectManager();

    void reset();
    void start(int effect, int delay = 3);
    void stop();

    virtual void paintEvent();

    inline void pushPrevScreen(image_t & img) {
        prev_img = img;
    }

    inline void pushNewScreen(image_t & img) {
        next_img = img;
    }

    inline void setPaintManager(EventManager *e) {
        event_mngr = e;
    }


    typedef signal_slot::multi_signal <void(EffectManager *)> signal;
    static typename signal_slot::multi_signal <void(EffectManager *)> &_sig;


    auto effectFinishedSignal() -> decltype(_sig) {
        return effectFinished;
    }

private:
    void timerEvent();

    void scaleEffect(int t);
    void moveEffect(int t);
    void alphaEffect(int t);
    void dominoEffect(int t);

private:
    signal effectFinished;
    int speed, start_pos, end_pos;
    image_t prev_img, next_img;
    TimerWrap timer;
    bool is_active;
    EventManager *event_mngr;
    int _effect;

    UActiveArea *_parent;
};

#endif // EFFECTMANAGER_H
