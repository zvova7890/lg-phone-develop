
#include <gl.h>
#include <Timer.h>
#include "RenameDialog.h"
#include "main.h"


EditLine::EditLine(const Rect &r, Widget *parent) :
    Widget(r, parent),
    m_cursorVisible(false),
    m_kbdDisconnected(true),
    m_dontHideKbd(false)
{
    m_timer.timerEventSignal().connect( [this](Timer *) {
        m_cursorVisible = !m_cursorVisible;
        eventManager()->updateAfterEvent();
    });
}


EditLine::~EditLine()
{
    if(!m_kbdDisconnected) {
        mainKeyboard()->hideAction().disconnect(m_kbd_hideAction);
        m_kbdDisconnected = true;
    }
}


void EditLine::paintEvent()
{
    if(isFocused()) {
        glSetPen(0xFFFFFFFF);
    } else {
        glSetPen(0xFFe8d5d5);
    }

    glDrawFilledRectange(realRect().x(), realRect().y(), realRect().x2(), realRect().y2());

    glSetPen(0xFF000000);
    glDrawString(m_text.c_str(), realRect().x(), realRect().y(), realRect().x2(), realRect().y2(),
                 15, FT_TEXT_H_CENTER | FT_TEXT_NOCALC_HCENTER, 0, 128);

    if(isFocused())
    {
        if(!m_timer.isActive())
            m_timer.start(1000);


        if(m_cursorVisible) {

            int w = glStringMetrics(15, m_text.c_str(), 0, 0, 128);
            glDrawVLine(realRect().y()+3, realRect().y2()-3, realRect().x()+w+1);
        }

    } else {

        if(m_timer.isActive())
            m_timer.stop();

        m_cursorVisible = false;
    }

}


void EditLine::touchEvent(int action, int x, int y)
{
    Widget::touchEvent(action, x, y);
}


void EditLine::focusEvent()
{
    printf("void EditLine::focus()\n");
    eventManager()->updateAfterEvent();

    Widget::focusEvent();
    mainKeyboard()->keyActionSignal().connect(this, &EditLine::keyAction,
                                              std::placeholders::_1,
                                              std::placeholders::_2,
                                              std::placeholders::_3);
    mainKeyboard()->show();

    if(m_kbdDisconnected) {
        m_kbdDisconnected = false;
        m_kbd_hideAction = mainKeyboard()->hideAction().connect( [this](Keyboard *) {
            m_dontHideKbd = true;
            unfocus();
            m_dontHideKbd = false;
        });
    } else {
        assert(0);
    }


}


void EditLine::unfocusEvent()
{
    printf("void EditLine::unfocus()\n");

    if(!m_kbdDisconnected) {
        printf("m_kbdDisconnected\n");
        mainKeyboard()->hideAction().disconnect(m_kbd_hideAction);
        m_kbdDisconnected = true;
    }

    Widget::unfocusEvent();
    eventManager()->updateAfterEvent();

    if(!m_dontHideKbd)
        mainKeyboard()->hide();
}


void EditLine::keyAction(Keyboard *, int type, const char *k)
{
    switch(type)
    {
        case 0:
            m_text.append(k);
            break;

        case 1:
            if(!m_text.empty()) {

                if(m_text.length() == 1)
                    m_text.clear();

                else {
                    auto last = (--m_text.end());
                    m_text.erase(last, m_text.end());
                }
            }
            break;

        case 2:
            break;
    }

    eventManager()->updateAfterEvent();
}


/**********************************************************************/


RenameDialog::RenameDialog(const Rect &r, Widget *parent) :
    Widget(r, parent),
    m_editor(Rect(4, 50, r.w()-8, 35), this),
    m_doneButton(Rect(4, 100, 70, 30), this, "Done")
{
    m_editor.show();
    m_editor.focus();

    m_doneButton.show();

    m_doneButton.releasedSignal().connect( [this](Button *b) {
        if(b->isTouched() && !b->isMoved()) {
            deleteLater();
        }
    });

    setFullScreenBlock(true);
    setBlockable(true);
}



void RenameDialog::paintEvent()
{
    glSetPen(0xFF000000);
    glDrawFilledRectange(realRect().x(), realRect().y(), realRect().x2(), realRect().y2());

    glSetPen(0xFFFFFFFF);
    glDrawHLine(realRect().x(), realRect().x2(), realRect().y()+30);

    glDrawString("Enter name", realRect().x()+4, realRect().y(), realRect().x2(), realRect().y()+30 ,
                 20, FT_TEXT_H_CENTER, 0, 128);


    Widget::paintEvent();
}


void RenameDialog::touchEvent(int action, int x, int y)
{
    Widget::touchEvent(action, x, y);
}


void RenameDialog::setText(const std::string &text)
{
    m_editor.setText(text);
}
















