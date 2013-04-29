
#include <Button.h>
#include "KeyboardEN.h"
#include "main.h"


KeyboardEN::KeyboardEN(const Rect &r, Keyboard *p) :
    KeyboardHelper(r, p)
{

    kbd_c = &resourceManager().image("kbd_c");
    kbd_up = &resourceManager().image("kbd_up");


    m_buttons.push_back( std::vector<Button *> {

        new Button(Rect(0, 0, 22, 30), this, "q"),
        new Button(Rect(0, 0, 22, 30), this, "w"),
        new Button(Rect(0, 0, 22, 30), this, "e"),
        new Button(Rect(0, 0, 22, 30), this, "r"),
        new Button(Rect(0, 0, 22, 30), this, "t"),
        new Button(Rect(0, 0, 22, 30), this, "y"),
        new Button(Rect(0, 0, 22, 30), this, "u"),
        new Button(Rect(0, 0, 22, 30), this, "i"),
        new Button(Rect(0, 0, 22, 30), this, "o"),
        new Button(Rect(0, 0, 22, 30), this, "p")

    } );


    m_buttons.push_back( std::vector<Button *> {
        new Button(Rect(0, 0, 22, 30), this, "a"),
        new Button(Rect(0, 0, 22, 30), this, "s"),
        new Button(Rect(0, 0, 20, 30), this, "d"),
        new Button(Rect(0, 0, 22, 30), this, "f"),
        new Button(Rect(0, 0, 22, 30), this, "g"),
        new Button(Rect(0, 0, 22, 30), this, "h"),
        new Button(Rect(0, 0, 22, 30), this, "j"),
        new Button(Rect(0, 0, 22, 30), this, "k"),
        new Button(Rect(0, 0, 22, 30), this, "l")
    } );


    auto kdb_up_render_handle = [this](Button *b) {

        int center_x = b->rect().w()/2 - kbd_up->width()/2;
        int center_y = b->rect().h()/2 - kbd_up->height()/2;

        if(b->isTouched()) {
            center_x ++;
            center_y ++;
        }

        drawImage(b->realRect().x()+center_x, b->realRect().y()+center_y, kbd_up);
    };

    auto kdb_c_render_handle = [this](Button *b) {

        int center_x = b->rect().w()/2 - kbd_c->width()/2;
        int center_y = b->rect().h()/2 - kbd_c->height()/2;

        if(b->isTouched()) {
            center_x ++;
            center_y ++;
        }

        drawImage(b->realRect().x()+center_x, b->realRect().y()+center_y, kbd_c);
    };


    m_buttons.push_back( std::vector<Button *> {
        ((new Button(Rect(0, 0, 35, 30), this, "up"))->setTextRender(kdb_up_render_handle)),
        new Button(Rect(0, 0, 22, 30), this, "z"),
        new Button(Rect(0, 0, 22, 30), this, "x"),
        new Button(Rect(0, 0, 22, 30), this, "c"),
        new Button(Rect(0, 0, 22, 30), this, "v"),
        new Button(Rect(0, 0, 22, 30), this, "b"),
        new Button(Rect(0, 0, 22, 30), this, "n"),
        new Button(Rect(0, 0, 22, 30), this, "m"),
        ((new Button(Rect(0, 0, 35, 30), this, "clean"))->setTextRender(kdb_c_render_handle))
    } );




    auto kdb_lang_handle = [this](Button *) {

    };

    m_buttons.push_back( std::vector<Button *> {
        (new Button(Rect(0, 0, 35, 30), this, "lang"))->setTextRender(kdb_lang_handle),
        (new Button(Rect(0, 0, 60, 30), this, " "))->setTextRender(kdb_lang_handle),
        (new Button(Rect(0, 0, 22, 30), this, "hide"))->setTextRender(kdb_lang_handle),
        new Button(Rect(0, 0, 35, 30), this, "OK")
    } );



    int hstep = 5;
    for(std::vector<Button *> &vec : m_buttons) {
        float xstep = 2;
        int width = 0;

        for(Button *b : vec)
            width += b->rect().w();

        float xp = (rect().w() - width - vec.size()*xstep) / 2 + xstep/2;

        for(Button *b : vec) {
            b->move(xp, hstep);
            b->pressedSignal().connect(this, &KeyboardEN::kbdAction, std::placeholders::_1);

            add(b);
            xp += (float)b->rect().w() + xstep;
        }

        hstep += 30 + 5;
    }

}


KeyboardEN::~KeyboardEN()
{
    for(std::vector<Button *> &v : m_buttons) {
        for(Button *b : v) {
            delete b;
        }
    }
}



void KeyboardEN::kbdAction(Button *b)
{
    std::string s = b->text();
    printf("kbdAction: %s\n", b->text().c_str());


    if(s == "clean") {
        m_actionSignal.trigger((Keyboard*)parent(), 1, s.c_str());

    } else if(s == "up") {
        m_actionSignal.trigger((Keyboard*)parent(), 2, s.c_str());

    } else if(s == "lang") {
        // handle

    } else if(s == "hide") {
        parent()->hide();

    } else if(s == "OK") {
        // handle

    } else {
        m_actionSignal.trigger((Keyboard*)parent(), 0, s.c_str());
    }
}


String KeyboardEN::name() const
{
    return "en_US";
}


int KeyboardEN::rows() const
{
    return 3;
}


int KeyboardEN::rowMaxHeight() const
{
    return 30;
}
