#ifndef UBUTTON_H
#define UBUTTON_H

#include <string>
#include <Widget/EventManager.h>
#include <Widget/Widget.h>
#include <ButtonStyle.h>
#include <signals/signal.h>

/* Simple button */


class Button : public Widget
{
public:
    Button(const Rect & rc, Widget *parent, const std::string &text);


    void paintEvent();
    void touchEvent(int action, int x, int y);


    Button *setTextRender(std::function<void(Button*)> f);
    void setDefaultTextRender();
    static int roundRect(int w);

    bool isActive() const {
        return m_isActive;
    }


    void setActive(bool is = true) {
        m_isActive = is;
    }


    typedef signal_slot::multi_signal <Button *> signal;
    static typename signal_slot::multi_signal <Button *> &_sig;

    signal & releasedSignal() {
        return m_released;
    }

    signal & pressedSignal() {
        return m_pressed;
    }


    ButtonStyle & style() {
        return m_style;
    }

    void setStyle(const ButtonStyle & style) {
        m_style = style;
    }

    void setText(const std::string &text) {
        m_text = text;
    }

    std::string text() const {
        return m_text;
    }

protected:
    static void defaultTextRender(Button *);

private:

    signal m_pressed, m_released;
    std::string m_text;
    bool m_isActive;

    ButtonStyle m_style;

    std::function<void(Button *)> m_textRender;
};



#endif // UBUTTON_H
