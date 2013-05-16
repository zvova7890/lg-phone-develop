
#include <gl.h>
#include "Keyboard.h"
#include <wchar.h>
#include <Widget/Button.h>
#include "KeyboardEN.h"
#include "KeyboardRU.h"
#include "KeyboardEnum.h"
#include "main.h"
#include <compatible.h>



KeyboardHelper::KeyboardHelper(const Rect &r, Keyboard *p, bool) :
    Widget(r, (Widget*)p),
    m_parent(p),
    m_poputButton(0)
{
    setMovable(false);
}


KeyboardHelper::~KeyboardHelper()
{
    clear();
}


void KeyboardHelper::clear()
{
    std::list<Widget*> chl = directChilds();
    for(Widget *w : chl) {
        delete w;
    }
}


void KeyboardHelper::createKeyboard(const std::vector<std::vector<const char *> > &kbd_layout)
{
    caseTypeSwitcher = 0;
    m_unsignedButtons.clear();
    m_charset = kbd_layout;

    Image *kbd_c = &resourceManager().image("kbd_c");
    Image *kbd_up = &resourceManager().image("kbd_up");

    int hstep = 5;
    int i = 0;
    for(const std::vector<const char *> &vec : kbd_layout) {

        float xstep = 0;
        float width = float(rect().w() - 2) / vec.size();
        float xpos = 1;
        Button *b = 0;

        if(i == 2) {
            width = float(rect().w() - 2 - (35+35)) / vec.size();

            b = new Button(Rect(xpos, hstep, 35, 30), this, "up");
            caseTypeSwitcher = b;
            b->setIcon(kbd_up);
            b->setActive(false);
            b->setTextVisible(false);
            b->setMovable(false);
            b->pressedSignal().connect(this, &KeyboardHelper::kbdAction, std::placeholders::_1);

            add(b);
            xpos += 35 + xstep;
        }

        for(const char *ch : vec) {

            b = new Button(Rect(xpos, hstep, width, 30), this, ch);
            b->releasedSignal().connect(this, &KeyboardHelper::kbdAction, std::placeholders::_1);
            b->setMovable(false);
            b->pressedSignal().connect(this, &KeyboardHelper::kbdShowChar, std::placeholders::_1);
            b->movedSignal().connect(this, &KeyboardHelper::kbdShowChar, std::placeholders::_1);

            add(b);
            xpos += width + xstep;
            m_unsignedButtons.push_back(b);
        }

        if(i == 2) {
            b = new Button(Rect(xpos, hstep, 35, 30), this, "clean");
            b->setIcon(kbd_c);
            b->setTextVisible(false);
            //b->setMovable(false);


            m_repeat.timerEventSignal().connect( [this, b](Timer *) {
                m_actionSignal.trigger((Keyboard*)parent(), 1, b->constText().c_str());
            });


            b->touchAction().connect( [this](Button *b, int action) {

                if(action == TOUCH_ACTION_LONGPRESS)
                    m_repeat.start(100);

                else if(action == TOUCH_ACTION_RELEASE) {
                    if(m_repeat.isActive())
                        m_repeat.stop();
                    else
                       m_actionSignal.trigger((Keyboard*)parent(), 1, b->constText().c_str());
                }

            });

            add(b);
        }

        hstep += 30 + 4;
        ++i;
    }


    int whitespace = rect().w()*30 / 100;
    float width = float((rect().w()-2)-whitespace) / 6.0f;
    int xstep = 0;
    float xpos = 1;

    class Ololo
    {
    public:
        bool textVisible;
        const char *ch;
        Image *icon;
    };

    Ololo ks[] = {
        {true, "123", 0},
        {false, "lang", &resourceManager().image("kbd_lang")}
    };

    for(int i=0; i<2; ++i) {
        Button *b = new Button(Rect(xpos, hstep, width, 30), this, ks[i].ch);
        b->setTextVisible(ks[i].textVisible);
        b->pressedSignal().connect(this, &KeyboardHelper::kbdAction, std::placeholders::_1);
        b->setIcon(ks[i].icon);
        b->setMovable(false);
        add(b);

        xpos += width+xstep;
    }

    Button *b = new Button(Rect(xpos, hstep, whitespace, 30), this, " ");
    b->setTextVisible(true);
    b->setMovable(false);
    b->setTextRender( [](Button *b) {
        Rect rc = b->realRect();
        int xyoff = 0;

        if(b->isTouched())  {
            xyoff = 1;
        }

        glSetPen(0xFFFFFFFF);
        glDrawVLine(rc.y2()-4-8+xyoff, rc.y2()-4+xyoff, rc.x()+6+xyoff);
        glDrawVLine(rc.y2()-4-8+xyoff, rc.y2()-4+xyoff, rc.x2()-6+xyoff);
        glDrawHLine(rc.x()+6+xyoff, rc.x2()-6+xyoff, rc.y2()-4+xyoff);
    });

    b->releasedSignal().connect(this, &KeyboardHelper::kbdAction, std::placeholders::_1);
    add(b);

    xpos += whitespace+xstep;

    Ololo ks2[] = {
        {true, ".", 0},
        {true, ",", 0},
        {false, "ok", &resourceManager().image("kbd_ok")},
        {false, "hide", &resourceManager().image("kbd_hide")}
    };

    for(int i=0; i<4; ++i) {
        Button *b = new Button(Rect(xpos, hstep, width, 30), this, ks2[i].ch);
        b->setTextVisible(ks2[i].textVisible);
        b->setIcon(ks2[i].icon);
        b->setMovable(false);
        b->style().setFontFlags( FT_TEXT_W_CENTER | FT_TEXT_H_DOWN );
        b->pressedSignal().connect(this, &KeyboardHelper::kbdAction, std::placeholders::_1);
        add(b);

        xpos += width+xstep;
    }
}


int utf8_to_ucs2 (const unsigned char * input, const unsigned char ** end_ptr)
{
    if(end_ptr) *end_ptr = input;
    if (input[0] == 0)
        return -1;
    if (input[0] < 0x80) {
        if(end_ptr) * end_ptr = input + 1;
        return input[0];
    }
    if ((input[0] & 0xE0) == 0xE0) {
        if (input[1] == 0 || input[2] == 0)
            return -1;
        if(end_ptr) * end_ptr = input + 3;
        return
            (input[0] & 0x0F)<<12 |
            (input[1] & 0x3F)<<6  |
            (input[2] & 0x3F);
    }
    if ((input[0] & 0xC0) == 0xC0) {
        if (input[1] == 0)
            return -1;
        if(end_ptr) * end_ptr = input + 2;
        return
            (input[0] & 0x1F)<<6  |
            (input[1] & 0x3F);
    }
    return -1;
}


int ucs2_to_utf8 (int ucs2, unsigned char * utf8)
{
    if (ucs2 < 0x80) {
        utf8[0] = ucs2;
        utf8[1] = '\0';
        return 1;
    }
    if (ucs2 >= 0x80  && ucs2 < 0x800) {
        utf8[0] = (ucs2 >> 6)   | 0xC0;
        utf8[1] = (ucs2 & 0x3F) | 0x80;
        utf8[2] = '\0';
        return 2;
    }
    if (ucs2 >= 0x800 && ucs2 < 0xFFFF) {
        utf8[0] = ((ucs2 >> 12)       ) | 0xE0;
        utf8[1] = ((ucs2 >> 6 ) & 0x3F) | 0x80;
        utf8[2] = ((ucs2      ) & 0x3F) | 0x80;
        utf8[3] = '\0';
        return 3;
    }
    return -1;
}


void KeyboardHelper::setCharSizeType(bool up)
{
    for(Button *b : m_unsignedButtons)
    {
        const char *ch = b->text().c_str();
        wchar_t ucs2 = utf8_to_ucs2((unsigned char*)ch, 0);

        if(up)
            ucs2 += L'A' - L'a';
        else
            ucs2 -= L'A' - L'a';

        char ch2[4] = {0};
        ucs2_to_utf8(ucs2, (unsigned char*)ch2);

        b->setText(ch2);
    }
}


void KeyboardHelper::paintEvent()
{
    Widget::paintEvent();

    if(m_poputButton) {
        glSetPen(0xFF0000FF);
        glDrawRectange(m_infoPopup.x(), m_infoPopup.y(), m_infoPopup.x2(), m_infoPopup.y2());

        glSetPen(0xAF000000);
        glDrawFilledRectange(m_infoPopup.x()+1, m_infoPopup.y()+1, m_infoPopup.x2(), m_infoPopup.y2());

        glSetPen(0xFFFFFFFF);
        glDrawString(m_poputButton->text().c_str(), m_infoPopup.x(), m_infoPopup.y(), m_infoPopup.x2(), m_infoPopup.y2(), 25, FT_TEXT_H_CENTER | FT_TEXT_W_CENTER, 0, 128);
    }
}


void KeyboardHelper::kbdShowChar(Button *b)
{
    int xpos = b->realRect().x() + (b->realRect().w()/2 - 40/2);

    if(xpos + 40 > parent()->realRect().x2()) {
        xpos = parent()->realRect().x2()-40-2;

    } else if(xpos < parent()->realRect().x()) {
        xpos = parent()->realRect().x()+1;
    }

    m_infoPopup = Rect(xpos, b->realRect().y()-65, 40, 50);
    m_poputButton = b;
}


void KeyboardHelper::kbdAction(Button *b)
{
    // Если выключен режим привязки при нажатии isMovable(нажали на объекти и ему идут все ивенты пока не отпустим)
    // то при выходе из зоны объекта приходит RELEASE сигнал, с пометкой что это OffRect сигнал
    if(b->isOffRectTouch()) {
        m_poputButton = 0;
        return;
    }

    m_poputButton = 0;
    std::string s = b->text();
    //printf("kbdAction: %s\n", b->text().c_str());

    /*if(s == "clean") {

        m_actionSignal.trigger((Keyboard*)parent(), 1, s.c_str());

    } else*/ if(s == "up") {
        b->setActive( !b->isActive() );
        bool up = ((Keyboard*)parent())->m_upper = b->isActive();

        setCharSizeType(up);
        m_actionSignal.trigger((Keyboard*)parent(), 2, s.c_str());

    } else if(s == "lang") {
        m_langSwitch.trigger((Keyboard*)parent());

    } else if(s == "hide") {
        parent()->hide();

    } else if(s == "ok") {
        m_actionSignal.trigger((Keyboard*)parent(), 10, s.c_str());

    } else if(s == "123") {
        m_enumSwitch.trigger((Keyboard*)parent());

    } else {
        m_actionSignal.trigger((Keyboard*)parent(), 0, s.c_str());
    }
}




Keyboard::Keyboard(const Rect &r, Widget *parent) :
    Widget(r, parent),
    m_upper(false),
    m_animation_type(0)
{
    setBlockable(true);
    setFocuseable(false);
    setMovable(false);


    m_kbdLayouts["enum"] = newKeyboard("enum");
    m_kbdLayouts["ru_RU"] = newKeyboard("ru_RU");
    m_kbdLayouts["en_US"] = m_kbd = newKeyboard("en_US");

    //kbd->show();
    addParentToQueue();

    m_timer.timerEventSignal().connect(this, &Keyboard::effectHandler, std::placeholders::_1);
    m_lastRect = rect();
}


Keyboard::~Keyboard()
{
    for(auto kbd : m_kbdLayouts) {
        delete kbd.second;
    }
}



void Keyboard::switchKeyboard(const std::string &type)
{
    eventManager()->notifyAfterEvent( [this, type]() {
        KeyboardHelper *kbd = m_kbdLayouts[type];
        if(!kbd)
            return;

        if(type == "enum") {
            kbd->setUserData( (void*)m_kbd );
        }

        m_kbd = kbd;
    });
}


KeyboardHelper *Keyboard::newKeyboard(const std::string &type)
{
    Rect r = rect();
    KeyboardHelper *kbd = 0;

    if(type == "enum") {
        kbd = new KeyboardEnum(Rect(0, 0, r.w(), r.h()), this);
        kbd->langSwitchAction().connect( [this](Keyboard *) {
            switchKeyboard("en_US");
        });

        kbd->enumSwitchAction().connect( [this, kbd](Keyboard *) {
            KeyboardHelper *last_kbd = (KeyboardHelper*)kbd->userData();
            switchKeyboard(last_kbd->name());
        });

        kbd->actionSignal().connect( this, &Keyboard::kbdKeyAction,
                                       std::placeholders::_1,
                                       std::placeholders::_2,
                                       std::placeholders::_3);

    }
    ////////////////

    if(type == "ru_RU") {
        kbd = new KeyboardRU(Rect(0, 0, r.w(), r.h()), this);
        kbd->langSwitchAction().connect( [this](Keyboard *) {
            switchKeyboard("en_US");
        });

        kbd->actionSignal().connect( this, &Keyboard::kbdKeyAction,
                                       std::placeholders::_1,
                                       std::placeholders::_2,
                                       std::placeholders::_3);
        kbd->enumSwitchAction().connect( [this](Keyboard *) {
            switchKeyboard("enum");
        });
    }

    //////////////////

    if(type == "en_US") {
        kbd = new KeyboardEN(Rect(0, 0, r.w(), r.h()), this);
        kbd->langSwitchAction().connect( [this](Keyboard *) {
            switchKeyboard("ru_RU");
        });
        kbd->actionSignal().connect( this, &Keyboard::kbdKeyAction,
                                       std::placeholders::_1,
                                       std::placeholders::_2,
                                       std::placeholders::_3);

        kbd->enumSwitchAction().connect( [this](Keyboard *) {
            switchKeyboard("enum");
        });
    }

    if(m_upper && kbd) {
        kbd->setCharSizeType(true);
        kbd->caseTypeSwitcher->setActive(true);
    }

    return kbd;
}


void Keyboard::paintEvent()
{
    GLGradient gr;
    GLGradient *g = glAllocateGradient(&gr, 2);

    g->colors[0].pixels = 6;
    g->colors[0].color = 0xFF000000;

    g->colors[1].pixels = 0;
    g->colors[1].color = 0x50FFFFFF;


    glCtxDrawGradient(glActiveContext(), realRect().x(), realRect().y()-6, realRect().w(), 6, 3, g);

    glDestroyGradient(g);


    glSetPen(0xFF000000);
    glDrawFilledRectange(realRect().x(), realRect().y(), realRect().x2(), realRect().y2());

    /*glSetPen(0xFFFFFFFF);
    glDrawRectange(realRect().x(), realRect().y(), realRect().x2(), realRect().y2());*/

    updateCoordinates(m_kbd);
    if(m_kbd)
        m_kbd->paint();

    Widget::paintEvent();
}


void Keyboard::touchEvent(int action, int x, int y)
{
    updateCoordinates(m_kbd);

    bool dirty = m_kbd->m_poputButton != 0;

    if(action == TOUCH_ACTION_RELEASE)
        m_kbd->m_poputButton = 0;

    if(m_kbd)
        m_kbd->touch(action, x, y);

    if(dirty && !m_kbd->m_poputButton)
        eventManager()->updateAfterEvent();

    Widget::touchEvent(action, x, y);
}



void Keyboard::resizeEvent()
{
    Widget::resizeEvent();

    m_lastRect = rect();


    std::string l = m_kbd->name();
    delete m_kbd;

    m_kbdLayouts["enum"] = newKeyboard("enum");
    m_kbdLayouts["ru_RU"] = newKeyboard("ru_RU");
    m_kbdLayouts["en_US"] = newKeyboard("en_US");

    m_kbd = m_kbdLayouts[l];
}


void Keyboard::show()
{
    if(!isHidden())
        return;

    m_timer.start(30);
    m_animation_type = 1;

    toTop();
    move(parent()->rect().x(), parent()->rect().y2());
    Widget::show();

    m_showAction.trigger(this);
}


void Keyboard::hide()
{
    if(isHidden())
        return;

    m_timer.start(30);
    m_animation_type = 2;

    m_hideAction.trigger(this);
}



void Keyboard::effectHandler(Timer *)
{
    if(m_animation_type == 1) {
        move(parent()->rect().x(), rect().y()-18);

        if(m_lastRect.y() >= rect().y()) {
            m_timer.stop();
            m_animation_type = 0;
        }

    } else if(m_animation_type == 2) {
        move(parent()->rect().x(), rect().y()+18);

        if(m_lastRect.y2() <= rect().y()) {
            Widget::hide();
            m_timer.stop();
            m_animation_type = 0;
        }
    }

    eventManager()->updateAfterEvent();
}



void Keyboard::kbdKeyAction(Keyboard *, int c, const char *ch)
{
    if(m_kbd) {
        m_actionSignal.trigger(this, c, ch);
    }
}
