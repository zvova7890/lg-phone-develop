#ifndef POSITIONER_H
#define POSITIONER_H


#include <Widget/Widget.h>



class Positioner : public Widget
{
public:
    Positioner(const Rect &r, Widget *parent);

    void paintEvent();
    void touchEvent(int /*action*/, int /*x*/, int /*y*/);
    void setPosition(int p);
    void setLength(int l);


    signal_slot::multi_signal<int> & positionSelected() {
        return m_positionSelected;
    }

protected:
    Rect band;
    int m_lenght;
    int m_pos;

    signal_slot::multi_signal<int> m_positionSelected;
};

#endif // POSITIONER_H
