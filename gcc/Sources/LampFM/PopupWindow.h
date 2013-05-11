#ifndef POPUPWINDOW_H
#define POPUPWINDOW_H

#include <Widget/Widget.h>
#include <string>
#include <Core/Timer.h>



class PopupWindow : public Widget
{
public:
    PopupWindow(Widget *parent);
    virtual ~PopupWindow();

    virtual void touchEvent(int action, int x, int y);
    virtual void paintEvent();
    virtual void resizeEvent();

protected:
    void sizesNPositions();

private:
    Timer timer;
};



#endif // POPUPWINDOW_H
