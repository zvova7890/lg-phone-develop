#ifndef QUESTIONDIALOG_H
#define QUESTIONDIALOG_H

#include <Widget.h>
#include <Button.h>
#include <string>
#include <vector>


class QuestionDialog : public Widget
{
public:
    QuestionDialog(Widget *parent, const Rect &r, const std::string &question);
    virtual ~QuestionDialog();

    void touchEvent(int action, int x, int y);
    void paintEvent();

    void parentHasDied();

    typedef signal_slot::multi_signal <QuestionDialog *, int> signal;

    signal & choisPressedSignal() {
        return m_buttonPressed;
    }

private:
    std::string m_question;
    signal m_buttonPressed;
};

#endif // QUESTIONDIALOG_H
