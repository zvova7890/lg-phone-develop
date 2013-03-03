#ifndef QUESTIONDIALOG_H
#define QUESTIONDIALOG_H

#include <Ui/UActiveArea.h>
#include <Ui/UButton.h>
#include <string>
#include <vector>


class QuestionDialog : public UActiveAreaItem<ActiveAreaItem>
{
public:
    QuestionDialog(UActiveArea *parent, const Rect &r, const std::string &question);
    ~QuestionDialog();

    void touchEvent(int action, int x, int y);
    void paintEvent();

    void parentHasDied();

    void show();
    void hide();


    signal_slot::multi_signal <void(QuestionDialog *, int)> & choisPressedSignal() {
        return m_buttonPressed;
    }

private:
    std::string m_question;
    std::vector< UButton* > m_buttons;
    signal_slot::multi_signal <void(QuestionDialog *, int)> m_buttonPressed;
    UActiveArea m_buttonsArea;
};

#endif // QUESTIONDIALOG_H
