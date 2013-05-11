#ifndef MESSAGEBOX_H
#define MESSAGEBOX_H


#include <Widget/Button.h>
#include "PopupWindow.h"



class MessageBox : public PopupWindow
{
public:
    MessageBox(Widget *parent, const std::string &text);
    virtual ~MessageBox();

    void touchEvent(int action, int x, int y);
    void paintEvent();
    void resizeEvent();

    typedef signal_slot::multi_signal <MessageBox *> signal;

    signal & closeAction() {
        return m_closeAction;
    }


private:
    std::string m_text;
    signal m_closeAction;
    Timer timer;
    Button m_okButton;
};

#endif // MESSAGEBOX_H
