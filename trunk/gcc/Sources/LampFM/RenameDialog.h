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

    void setCursorPosition(unsigned int pos, bool mark = false);
    void setText(const std::string &text);
    void insertText(const std::string &text);

    std::string text() const {
        return m_text;
    }


    signal_slot::multi_signal<EditLine *> &editFinishedAction() {
        return m_editFinishedSignal;
    }

protected:
    void timerEvent(Timer *);
    int erase(int start, int end);
    int erase();
    int insert(int start, const std::string &text);
    int charCursorPosition(int x, int y, int *least_x = 0);
    int realCursorPosition(int cpos);
    int newCharPosition(const char *s, int l, int font);
    void keyAction(Keyboard *, int type, const char *k);

private:

    struct Character {

        Character(int _strpos, int _size, int _pos, int _width) {
            strpos = _strpos;
            size = _size;
            pos = _pos;
            width = _width;
        }

        char size;
        int pos;
        int width;
        int strpos;
    };

    std::string m_text;
    std::vector<Character> chars;
    Timer m_timer;
    bool m_cursorVisible;
    int mark_start, mark_end;
    int xtest_offset;

    Keyboard *kbd;
    Keyboard::sig::slot m_kbd_hideAction;
    bool m_kbdDisconnected;
    bool m_dontHideKbd;

    signal_slot::multi_signal<EditLine *> m_editFinishedSignal;

    Timer pos_fixup;
    int fixup_way;
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
