
#include <gl.h>
#include <Timer.h>
#include "RenameDialog.h"
#include "main.h"


EditLine::EditLine(const Rect &r, Widget *parent) :
    Widget(r, parent),
    m_cursorVisible(false),
    cursor_position(0),
    kbd( (Keyboard*)parent->mainParent()->providesExtraWidget("keyboard") ),
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
        if(kbd)
            kbd->hideAction().disconnect(m_kbd_hideAction);
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


    int xoffset = 0;

    if(!chars.empty()) {
        Character &chr = chars.at(cursor_position-1);

        if(chr.pos+3 >= realRect().w()) {

            xoffset -= (chr.pos - realRect().w()) + 4;

        }
    }

    glSetPen(0xFF000000);
    glDrawString(m_text.c_str(), realRect().x()+xoffset, realRect().y(), realRect().x2(), realRect().y2(),
                 15, FT_TEXT_H_CENTER | FT_TEXT_NOCALC_HCENTER, 0, 1024);

    if(isFocused())
    {
        if(!m_timer.isActive())
            m_timer.start(1000);


        if(m_cursorVisible) {

            int w = glStringMetrics(15, m_text.c_str(), 0, 0, 1024)+xoffset;

            //printf("w: %d\n", w);

            glSetPen(0xFFFF0000);
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
    //printf("void EditLine::focus()\n");
    eventManager()->updateAfterEvent();

    Widget::focusEvent();
    if(kbd) {
        kbd->keyActionSignal().connect(this, &EditLine::keyAction,
                                              std::placeholders::_1,
                                              std::placeholders::_2,
                                              std::placeholders::_3);
        kbd->show();
    }

    if(m_kbdDisconnected) {
        m_kbdDisconnected = false;

        if(kbd) {
            m_kbd_hideAction = kbd->hideAction().connect( [this](Keyboard *) {
                m_dontHideKbd = true;
                unfocus();
                m_dontHideKbd = false;
            });
        }
    } else {
        assert(0);
    }


}


void EditLine::unfocusEvent()
{
    //printf("void EditLine::unfocus()\n");

    if(!m_kbdDisconnected) {
        printf("m_kbdDisconnected\n");
        if(kbd)
            kbd->hideAction().disconnect(m_kbd_hideAction);
        m_kbdDisconnected = true;
    }

    Widget::unfocusEvent();
    eventManager()->updateAfterEvent();

    if(!m_dontHideKbd && kbd)
        kbd->hide();
}



int utf8_charset_size(const char *word)
{
    const char *s = word;

    /* Assumes correct input and no characters outside the BMP. */

    if((s[0]&0x80)==0)
    {
        s++;
    }
    else if((s[0]&0x20)==0)
    {
        s+=2;
    }
    else if((s[0]&0x10)==0)
    {
        s+=3;
    }

    return s-word;
}



void EditLine::setText(const std::string &text)
{
    chars.clear();
    m_text = text;
    cursor_position = 0;


    const char *s = m_text.c_str();

    while(1) {
        int l = utf8_charset_size(s);

        if(l > 0) {
            chars.push_back( Character(l, newCharPosition(s, l, 15)) );
            cursor_position ++;
        } else
            break;

        s += l;
        if(!*s) {
            break;
        }
    }
}


void EditLine::appendText(const std::string &text)
{
    const char *s = text.c_str();
    while(1) {
        int l = utf8_charset_size(s);

        if(l > 0) {
            chars.push_back( Character(l, newCharPosition(s, l, 15)) );
            cursor_position ++;
        } else
            break;

        s += l;
        if(!*s) {
            break;
        }
    }

    m_text.append( text );
    m_cursorVisible = true;
}


int EditLine::newCharPosition(const char *s, int l, int font)
{
    int pos = 0;
    if(!chars.empty()) {
        pos = chars.back().pos;
    }

    char chr[4] = {0};
    memcpy(chr, s, l);

    pos += glStringMetrics(font, chr, 0, 0, 1);
    return pos;
}


void EditLine::keyAction(Keyboard *, int type, const char *k)
{
    switch(type)
    {
        case 0:
            appendText(k);
            break;

        case 1:
            if(!m_text.empty()) {

                if(m_text.length() == 1)
                    m_text.clear();

                else {


                    auto last = (--chars.end());
                    int rm_sz = (*last).size;
                    chars.erase( last );


                    if(rm_sz > 0) {
                        auto last = (m_text.end());

                        for(int i=0; i<rm_sz; ++i)
                            last--;

                        cursor_position --;
                        m_text.erase(last, m_text.end());
                    } else {
                        printf("That is happens!!! O_O\n");
                    }
                }
            }
            break;

        case 2:
            break;

        case 10:
            m_editFinishedSignal.trigger(this);
            break;
    }

    eventManager()->updateAfterEvent();
}


/**********************************************************************/


RenameDialog::RenameDialog(const Rect &r, Widget *parent) :
    Widget(r, parent),
    m_editor(Rect(), this),
    m_cancel(Rect(), this, "Cancel")
{
    resizeEvent();

    m_editor.editFinishedAction().connect( [this](EditLine *e) {
        m_editor.hide();
        m_renameAction.trigger(this, e->text());
    });


    m_editor.show();
    m_editor.focus();


    m_cancel.releasedSignal().connect( [this](Button *b) {
        if(b->isTouched() && !b->isMoved())
            deleteLater();
    });

    m_cancel.show();

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


void RenameDialog::resizeEvent()
{
    Widget::resizeEvent();

    if(rect().w() > rect().h()) {
        m_editor.setSize(Rect(4, 40, rect().w()-78, 35));
        m_cancel.setSize(Rect(rect().w()-65, 40, 60, 35));
    } else {
        m_editor.setSize(Rect(4, 40, rect().w()-8, 35));
        m_cancel.setSize(Rect(rect().w()-65, 80, 60, 35));
    }
}


void RenameDialog::setText(const std::string &text)
{
    m_editor.setText(text);
}
















