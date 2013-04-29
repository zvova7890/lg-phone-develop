#ifndef KEYBOARD_H
#define KEYBOARD_H


#include <Widget.h>
#include <signals/signal.h>
#include <String.h>
#include <Timer.h>


class Button;
class Keyboard;


class KeyboardHelper : public Widget
{
public:
    typedef signal_slot::signal <Keyboard *, int, const char *> sig;

    KeyboardHelper(const Rect &r, Keyboard *p = 0) :
        Widget(r, (Widget*)p),
        m_parent(p)
    {}

    virtual ~KeyboardHelper() {}


    virtual String name() const {
        return "HuiZnaet";
    }

    virtual int rows() const {
        return 0;
    }

    virtual int rowMaxHeight() const {
        return 0;
    }

    Keyboard *parent() {
        return m_parent;
    }

    void setParent(Keyboard *p) {
        m_parent = p;
    }

    sig & actionSignal() {
        return m_actionSignal;
    }

protected:
    sig m_actionSignal;
    Keyboard *m_parent;

    friend class Keyboard;
};



class Keyboard : public Widget
{
public:
    typedef signal_slot::multi_signal<Keyboard *> sig;

    Keyboard(const Rect &, Widget *parent = 0, KeyboardHelper *kbd = 0);
    virtual ~Keyboard();


    void paintEvent();
    void touchEvent(int action, int x, int y);

    void show();
    void hide();


    KeyboardHelper::sig & keyActionSignal() {
        return m_kbd->m_actionSignal;
    }

    sig & showAction() {
        return m_showAction;
    }

    sig & hideAction() {
        return m_hideAction;
    }


protected:
    void effectHandler(Timer *);

private:
    sig m_showAction;
    sig m_hideAction;
    std::vector<std::vector<const char *> > m_keyCodes;

    KeyboardHelper *m_kbd;
    bool m_kbdCleanup;
    char m_animation_type;

    Rect m_lastRect;
    Timer m_timer;
};

#endif // KEYBOARD_H
