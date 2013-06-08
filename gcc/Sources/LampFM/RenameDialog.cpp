
#include <pxeapi.h>
#include <gl.h>
#include <Timer.h>
#include "RenameDialog.h"
#include "main.h"


EditLine::EditLine(const Rect &r, Widget *parent) :
    Widget(r, parent),
    m_cursorVisible(false),
    mark_start(0),
    mark_end(0),
    xtest_offset(0),
    kbd( (Keyboard*)parent->rootParent()->providesExtraExtension("keyboard") ),
    m_kbdDisconnected(true),
    m_dontHideKbd(false)
{
    setMovable(true);

    m_timer.timerEventSignal().connect( [this](Timer *) {
        m_cursorVisible = !m_cursorVisible;
        eventManager()->updateAfterEvent();
    });

    pos_fixup.timerEventSignal().connect(this, &EditLine::timerEvent, std::placeholders::_1);
}


EditLine::~EditLine()
{
    if(!m_kbdDisconnected) {
        if(kbd)
            kbd->hideAction().disconnect(m_kbd_hideAction);
        m_kbdDisconnected = true;
    }
}


void EditLine::timerEvent(Timer *)
{
    switch(fixup_way)
    {
        case 0:
            if(mark_end > 0)
                setCursorPosition(mark_end-1, true);
            break;

        case 1:
            setCursorPosition(mark_end+1, true);
            break;
    }


    eventManager()->updateAfterEvent();
}


void EditLine::paintEvent()
{
    if(isFocused()) {
        glSetPen(0xFFFFFFFF);
    } else {
        glSetPen(0xFFe8d5d5);
    }

    glDrawFilledRectange(realRect().x(), realRect().y(), realRect().x2(), realRect().y2());


    glSaveClipRegion();
    glSetClipRegion(realRect().x(), realRect().y(), realRect().x2()+1, realRect().y2()+1);


    int cursor_pos = 0;
    if(!chars.empty()) {
        cursor_pos = realCursorPosition(mark_end);

        //if(pos+3 >= realRect().w()) {
          //  xtest_offset = ((pos - realRect().w()) + 4);
        //}
    }

    glSetPen(0xFF000000);
    glDrawString(m_text.c_str(), realRect().x()-xtest_offset, realRect().y(), realRect().x2(), realRect().y2(),
                 15, FT_TEXT_H_CENTER | FT_TEXT_NOCALC_HCENTER, 0, 1024);

    if(isFocused())
    {
        if(!m_timer.isActive())
            m_timer.start(1000);


        if(mark_start != mark_end) {

            glSetPen(0x6FFF0000);

            int x1 = realCursorPosition(mark_start);
            int x2 = realCursorPosition(mark_end);

            glDrawFilledRectange(realRect().x() + x1 - xtest_offset, realRect().y()+1,
                                 realRect().x() + x2 - xtest_offset, realRect().y2()-1);
        }

        if(m_cursorVisible) {

            int w = /*glStringMetrics(15, m_text.c_str(), 0, 0, 1024)+xoffset*/ cursor_pos-xtest_offset;
            glSetPen(0xAF000000);
            glDrawVLine(realRect().y()+3, realRect().y2()-3, realRect().x()+w);
        }

    } else {

        if(m_timer.isActive())
            m_timer.stop();

        m_cursorVisible = false;
    }

    glRestoreClipRegion();
}



int EditLine::realCursorPosition(int cpos)
{
    if(!chars.empty()) {
        int pos = 0;

        if((unsigned)cpos == chars.size()) {
            Character &chr = chars.at(cpos-1);
            pos = chr.pos+chr.width;
        } else {
            Character &chr = chars.at(cpos);
            pos = chr.pos;
        }

        return pos;
    }

    return 0;
}


void EditLine::setCursorPosition(unsigned int pos, bool mark)
{
    mark_end = pos;
    if(mark_end > chars.size())
        mark_end = chars.size();

    if(!mark)
        mark_start = mark_end;

    int xpos = realCursorPosition(mark_end);

    if(xpos+3 - xtest_offset >= realRect().w()) {
        xtest_offset = ((xpos - realRect().w()) + 4);
    }

    if(xpos - xtest_offset <= 0 && xtest_offset > 0) {
        xtest_offset -= xtest_offset-xpos +1;
    }

}


void EditLine::touchEvent(int action, int x, int y)
{
    switch(action)
    {
        case TOUCH_ACTION_PRESS:
        {
            int pos = charCursorPosition(x-realRect().x() + xtest_offset, y);
            if(pos > -1) {
                setCursorPosition(pos);
            }

            break;
        }

        case TOUCH_ACTION_MOVE:
        {
            int least_x;
            int pos = charCursorPosition((x > realRect().x()? x-realRect().x() : 0) + xtest_offset, y, &least_x);

            if(x+15 >= realRect().x2()) {
                //setCursorPosition(pos+1, true);

                fixup_way = 1;
                pos_fixup.start(60);
                //printf("LEAST LOOOOOL: %d\n", least_x);
            }

            else if(x-15 <= realRect().x()) {
                fixup_way = 0;
                pos_fixup.start(60);

            } else if(pos > -1) {
                pos_fixup.stop();
                setCursorPosition(pos, true);
            }


            break;
        }


        case TOUCH_ACTION_RELEASE:
            pos_fixup.stop();
            break;
    }

    Widget::touchEvent(action, x, y);

    m_cursorVisible = true;
    eventManager()->updateAfterEvent();
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



int EditLine::charCursorPosition(int x, int y, int *least_x)
{
    if(x < 0)
        x = 0;

    if(least_x) *least_x = 0;

    int i = 0;
    for(auto it = chars.begin(); it != chars.end(); ++i)
    {
        auto cur = it++;
        if(it != chars.end()) {

             if( x >= (*cur).pos &&  x < (*it).pos)
                return i;
        } else {

            if( x >= (*cur).pos + (*cur).width) {
                if(least_x)
                    *least_x = x - ((*cur).pos + (*cur).width);
                return i+1;
            }
            else
                return i;
        }
    }

    return -1;
}



int EditLine::erase(int start, int end)
{
    if((unsigned)end > chars.size())
        end = chars.size();

    if((unsigned)start >= chars.size() || end-start < 1)
        return -1;

    if(end-start == chars.size()) {
        chars.clear();
        m_text.clear();
        setCursorPosition(0);
        return end-start;
    }

    int erase_bytes = chars.at(end-1).strpos + chars.at(end-1).size - chars.at(start).strpos;
    int erased = end-start;
    int text_start = chars.at(start).strpos;

    chars.erase( chars.begin()+start, chars.begin()+start+erased );

    int new_from = 0;
    int strpos = 0;
    if(start > 1) {
        auto it = chars.begin()+start-1;
        if(it != chars.end()) {
            new_from = (*it).pos + (*it).width;
            strpos = (*it).strpos + (*it).size;
        }
    }

    for(auto it = chars.begin()+start; it != chars.end(); ++it) {
        (*it).pos = new_from;
        (*it).strpos = strpos;
        new_from += (*it).width;
        strpos += (*it).size;
    }


    m_text.erase(m_text.begin() + text_start, m_text.begin() + text_start + erase_bytes);
    return erased;
}


int EditLine::erase()
{
    int erased = 0;
    if(mark_end == mark_start) {

        if((unsigned)mark_start == chars.size()) {
            erased = erase(mark_start-1, mark_start);
            setCursorPosition(chars.size());

        } else if(mark_start > 0) {
            erased = erase(mark_start-1, mark_start);
            setCursorPosition(mark_start-1);
        }
    } else {

        int begin = mark_start > mark_end? mark_end : mark_start;
        int end = mark_start < mark_end? mark_end : mark_start;

        erased = erase(begin, end);
        setCursorPosition(begin);
    }

    return erased;
}


int utf8_charset_size(const char *word)
{
    const char *s = word;

    /* Assumes correct input and no characters outside the BMP. */
/*
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
    }*/

    size_t res = 0;
    unsigned char _c = word[0];

    while(_c & 0x80){
        res ++;
        _c <<= 0x1;
    }

    return res == 0 ? 1 : res;
}



void EditLine::setText(const std::string &text)
{
    setCursorPosition(0);
    chars.clear();
    m_text = text;

    const char *s = m_text.c_str();

    do
    {
        int l = utf8_charset_size(s);

        if(l > 0) {

            int size = glStringMetrics(15, s, 0, 0, 1);
            int pos = 0;
            int strpos = 0;

            if(!chars.empty()) {
                pos = chars.back().pos + chars.back().width;
                strpos = chars.back().strpos + chars.back().size;
            }

            chars.push_back( Character(strpos, l, pos, size) );
        } else
            break;

        s += l;
    }while(*s);

    setCursorPosition(chars.size());
    m_cursorVisible = true;
}


void EditLine::insertText(const std::string &text)
{
    insert(mark_end, text);
}


int EditLine::insert(int start, const std::string &text)
{
    if((unsigned)start > chars.size())
        start = chars.size();

    int pos_from = 0;
    int strpos = 0;
    if(!chars.empty() && start > 0) {
        auto it = chars.begin()+start-1;
        pos_from = (*it).pos + (*it).width;
        strpos = (*it).strpos + (*it).size;
    }

    std::vector<Character> ins;
    const char *s = text.c_str();
    int strpos_cnt = strpos;

    while(1) {
        int l = utf8_charset_size(s);

        if(l > 0) {
            int width = glStringMetrics(15, s, 0, 0, 1);

            ins.push_back( Character(strpos_cnt, l, pos_from, width) );
            pos_from += width;
            strpos_cnt += l;
        } else
            break;

        s += l;
        if(!*s) {
            break;
        }
    }



    if(strpos == 0 && m_text.empty()) {
        m_text = text;
        chars = ins;
    } else {
        chars.insert(chars.begin()+start, ins.begin(), ins.end());
        m_text.insert(m_text.begin() + strpos, text.begin(), text.end());
    }

    /* recalc positions */
    for(auto it = chars.begin()+start+ins.size(); it != chars.end(); ++it) {
        (*it).pos = pos_from;
        (*it).strpos = strpos_cnt;
        pos_from += (*it).width;
        strpos_cnt += (*it).size;
    }

    setCursorPosition(start+ins.size());
    return 0;
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
        case Keyboard::KBD_CHAR:
            insertText(k);
            break;

        case Keyboard::KBD_ERASE:
            if(!m_text.empty())
                erase();

            break;

        case 2:
            break;

        case Keyboard::KBD_OK:
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



