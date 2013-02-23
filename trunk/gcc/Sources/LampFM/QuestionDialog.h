#ifndef QUESTIONDIALOG_H
#define QUESTIONDIALOG_H

#include <UActiveArea.h>
#include <string>
#include <vector>


class QuestionDialog : public UActiveAreaItem<ActiveAreaItem>
{
public:
    QuestionDialog(const Rect &r, const std::string &question);
    ~QuestionDialog();

    void touchEvent(int action, int x, int y);
    void paintEvent();

    void parentHasDied();

    void show();
    void hide();


    auto choisPressedSignal() -> signal_slot::multi_signal <void(QuestionDialog *, int)> {
        return __button_pressed;
    }

private:
    std::string _question;
    std::vector< UActiveAreaItem<ActiveAreaItem>* > buttons;
    signal_slot::multi_signal <void(QuestionDialog *, int)> __button_pressed;
    UActiveArea buttons_area;
};

#endif // QUESTIONDIALOG_H
