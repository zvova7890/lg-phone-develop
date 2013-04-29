#ifndef RENAMEDIALOG_H
#define RENAMEDIALOG_H



#include <Widget.h>
#include <string>
#include <Timer.h>
#include <Button.h>
#include "Keyboard/Keyboard.h"


class EditLine : public Widget
{
public:
    EditLine(const Rect &r, Widget *parent = 0);
    ~EditLine();

    void paintEvent();
    void touchEvent(int action, int x, int y);
    void focusEvent();
    void unfocusEvent();

    void setText(const std::string &text) {
        m_text = text;
    }

    std::string text() const {
        return m_text;
    }


protected:
    void keyAction(Keyboard *, int type, const char *k);

private:
    std::string m_text;
    Timer m_timer;
    bool m_cursorVisible;

    Keyboard::sig::slot m_kbd_hideAction;
    bool m_kbdDisconnected;
    bool m_dontHideKbd;
};


class RenameDialog : public Widget
{
public:
    RenameDialog(const Rect &r, Widget *parent = 0);


    void setText(const std::string &text);

    void paintEvent();
    void touchEvent(int action, int x, int y);

protected:
    EditLine m_editor;
    Button m_doneButton;
};

#endif // RENAMEDIALOG_H
