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

    template <class Tp>
    inline void connectChoisPressed(Tp slot_) {
        __button_pressed.connect(slot_);
    }

private:
    std::string _question;
    std::vector< UActiveAreaItem<ActiveAreaItem>* > buttons;
    sigc::signal <void, QuestionDialog *, int> __button_pressed;
    UActiveArea buttons_area;
};

#endif // QUESTIONDIALOG_H
