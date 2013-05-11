#ifndef KEYBOARD_H
#define KEYBOARD_H


#include <Widget.h>
#include <signals/signal.h>
#include <String.h>
#include <Timer.h>
#include <map>


class Button;
class Keyboard;


class KeyboardHelper : public Widget
{
public:
    typedef signal_slot::signal <Keyboard *, int, const char *> sig;

    KeyboardHelper(const Rect &r, Keyboard *p, bool = false) :
        Widget(r, (Widget*)p),
        m_parent(p)
    {}

    virtual ~KeyboardHelper();

    void createKeyboard( const std::vector< std::vector<const char *> > & kbd );
    virtual void clear();


    virtual std::string name() const {
        return "HuiZnaet";
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

    signal_slot::signal<Keyboard *> & langSwitchAction() {
        return m_langSwitch;
    }

    signal_slot::signal<Keyboard *> & enumSwitchAction() {
        return m_enumSwitch;
    }


protected:
    virtual void setCharSizeType(bool up);
    void kbdAction(Button *);

protected:
    std::vector<std::vector<const char *> > m_charset;
    std::vector<Button*> m_unsignedButtons;
    sig m_actionSignal;
    signal_slot::signal<Keyboard *> m_langSwitch;
    signal_slot::signal<Keyboard *> m_enumSwitch;
    Keyboard *m_parent;

    friend class Keyboard;
};



class Keyboard : public Widget
{
public:
    typedef signal_slot::multi_signal<Keyboard *> sig;

    Keyboard(const Rect &, Widget *parent = 0);
    virtual ~Keyboard();


    void paintEvent();
    void touchEvent(int action, int x, int y);
    void resizeEvent();

    void show();
    void hide();


    KeyboardHelper::sig & keyActionSignal() {
        return m_actionSignal;
    }

    sig & showAction() {
        return m_showAction;
    }

    sig & hideAction() {
        return m_hideAction;
    }


protected:
    void effectHandler(Timer *);
    void kbdKeyAction(Keyboard *, int, const char *);
    void switchKeyboard(const std::string &type);
    KeyboardHelper *newKeyboard(const std::string &type);

private:
    sig m_showAction;
    sig m_hideAction;
    KeyboardHelper::sig m_actionSignal;
    std::vector<std::vector<const char *> > m_keyCodes;
    bool m_upper;

    KeyboardHelper *m_kbd;
    bool m_dirtyKbd;
    char m_animation_type;

    Rect m_lastRect;
    Timer m_timer;

    std::map<std::string, KeyboardHelper*> m_kbdLayouts;

    friend class KeyboardHelper;
};

#endif // KEYBOARD_H
