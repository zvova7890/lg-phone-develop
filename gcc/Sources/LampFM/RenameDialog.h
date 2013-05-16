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

    void setText(const std::string &text);
    void appendText(const std::string &text);

    std::string text() const {
        return m_text;
    }


    signal_slot::multi_signal<EditLine *> &editFinishedAction() {
        return m_editFinishedSignal;
    }

protected:
    int newCharPosition(const char *s, int l, int font);
    void keyAction(Keyboard *, int type, const char *k);

private:

    struct Character {

        Character(int _size, int _pos) {
            size = _size;
            pos = _pos;
        }

        char size;
        int pos;
    };

    std::string m_text;
    std::vector<Character> chars;
    Timer m_timer;
    bool m_cursorVisible;
    int cursor_position;


    Keyboard *kbd;
    Keyboard::sig::slot m_kbd_hideAction;
    bool m_kbdDisconnected;
    bool m_dontHideKbd;

    signal_slot::multi_signal<EditLine *> m_editFinishedSignal;
};


class RenameDialog : public Widget
{
public:
    RenameDialog(const Rect &r, Widget *parent = 0);


    void setText(const std::string &text);
    void paintEvent();
    void touchEvent(int action, int x, int y);
    void resizeEvent();

    signal_slot::multi_signal<RenameDialog *, const std::string> & renameAction() {
        return m_renameAction;
    }

protected:
    EditLine m_editor;
    Button m_cancel;

    signal_slot::multi_signal<RenameDialog *, const std::string> m_renameAction;
};

#endif // RENAMEDIALOG_H
