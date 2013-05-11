#ifndef QUESTIONDIALOG_H
#define QUESTIONDIALOG_H

#include <Widget/Widget.h>
#include <PopupWindow.h>
#include <Widget/Button.h>
#include <string>
#include <vector>

// TODO class PopupWindow

class QuestionDialog : public PopupWindow
{
public:
    QuestionDialog(Widget *parent, const std::string &question);
    virtual ~QuestionDialog();

    void touchEvent(int action, int x, int y);
    void paintEvent();
    void resizeEvent();

    typedef signal_slot::multi_signal <QuestionDialog *, int> signal;

    signal & choisPressedSignal() {
        return m_buttonPressed;
    }

private:
    std::string m_question;
    signal m_buttonPressed;
};

#endif // QUESTIONDIALOG_H
