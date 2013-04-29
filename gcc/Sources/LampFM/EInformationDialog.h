#ifndef EINFORMATIONDIALOG_H
#define EINFORMATIONDIALOG_H



#include <VScrollArea.h>
#include <signals/signal.h>



class EInformationDialog : public VScrollArea
{
public:
    typedef signal_slot::multi_signal <EInformationDialog *, int> state_signal;

public:

    EInformationDialog(Widget *parent, const Rect &r);
    ~EInformationDialog();


    void paintEvent();
    void touchEvent(int action, int x, int y);


    void show();
    void hide();


    state_signal & stateChangedSignal() {
        return m_stateChanget;
    }

protected:
    state_signal m_stateChanget;
};

#endif // EINFORMATIONDIALOG_H
