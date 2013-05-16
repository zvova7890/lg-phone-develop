#ifndef UBUTTON_H
#define UBUTTON_H

#include <string>
#include <Widget/EventManager.h>
#include <Widget/Widget.h>
#include <Widget/ButtonStyle.h>
#include <Graph/Image.h>
#include <signals/signal.h>

/* Simple button */


class Button : public Widget
{
public:
    Button(const Rect & rc, Widget *parent, const std::string &text = "");


    void paintEvent();
    void touchEvent(int action, int x, int y);
    void resizeEvent();

    Button *setTextRender(std::function<void(Button*)> f);
    void setDefaultTextRender();
    static int roundRect(int w);

    bool isActive() const {
        return m_isActive;
    }

    void setActive(bool is = true) {
        m_isActive = is;
    }

    void setTextVisible(bool is) {
        m_textVisible = is;
    }

    typedef signal_slot::multi_signal <Button *> signal;
    static typename signal_slot::multi_signal <Button *> &_sig;

    signal & releasedSignal() {
        return m_released;
    }

    signal & pressedSignal() {
        return m_pressed;
    }

    signal & movedSignal() {
        return m_moved;
    }

    signal_slot::multi_signal <Button *, int> & touchAction() {
        return m_touchAction;
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

    const std::string & constText() const {
        return m_text;
    }

    void setIcon(const Image *i) {
        m_icon = i;
    }

protected:
    static void defaultTextRender(Button *);

private:

    signal m_pressed, m_released, m_moved;
    signal_slot::multi_signal <Button *, int> m_touchAction;
    std::string m_text;
    bool m_isActive;
    bool m_textVisible;

    ButtonStyle m_style;

    std::function<void(Button *)> m_textRender;
    const Image *m_icon;
};



#endif // UBUTTON_H
