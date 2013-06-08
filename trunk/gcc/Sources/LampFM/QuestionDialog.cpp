
#include <Core/compatible.h>
#include "QuestionDialog.h"
#include "main.h"





QuestionDialog::QuestionDialog(Widget *parent, const std::string &question) :
    PopupWindow(parent),
    m_question(question),
    done(0),
    effect_type(0)
{
    framebuffer = new unsigned char[(rect().w()+2) * (rect().h()+2) * 2];
    context = glCreateContext(rect().w()+2, rect().h()+2, 16, framebuffer);

    int button_w = rect().w()/2-10;
    int button_h = 40;

    Button *button_yes = new Button(Rect(5, rect().h()-button_h-5, button_w, button_h), this, "Yes");
    Button *button_no = new Button(Rect(rect().w()-button_w-5, rect().h()-button_h-5, button_w, button_h), this, "No");


    button_yes->releasedSignal().connect ( [this](Button *self) {

        if(self->isTouched() && !self->isMoved()) {
            m_buttonPressed.trigger(this, 1);
            return;
        }
    } );

    button_no->releasedSignal().connect ( [this](Button *self) {

        if(self->isTouched() && !self->isMoved()) {
            m_buttonPressed.trigger(this, 0);
            return;
        }
    } );

    add(button_yes);
    add(button_no);

    animation.timerEventSignal().connect(this, &QuestionDialog::timerEvent, std::placeholders::_1);
}



QuestionDialog::~QuestionDialog()
{
    for(Widget *i: childs())
        delete i;

    directChilds().clear();

    glDestroyContext(context);
    delete framebuffer;
}



void QuestionDialog::resizeEvent()
{
    PopupWindow::resizeEvent();

    int button_w = rect().w()/2-10;
    int button_h = 35;


    auto it = directChilds().begin();

    Widget *w = *it;
    w->setSize(Rect(5, rect().h()-button_h-5, button_w, button_h));

    w = *(++it);
    w->setSize(Rect(rect().w()-button_w-5, rect().h()-button_h-5, button_w, button_h));
}


void QuestionDialog::touchEvent(int action, int x, int y)
{
    if(action == TOUCH_ACTION_RELEASE && isOffRectTouch() && !isMoved()) {
        hide();
        m_buttonPressed.trigger(this, 0);
        return;
    }

    Widget::touchEvent(action, x, y);
}


void ScaleAndPaint(GLContext *ctx, const unsigned short *bitmap, int w, int h, int xfrom, int yfrom,
                   int newWidth, int newHeight, unsigned char alpha);


void QuestionDialog::paintEvent()
{
    GLContext *last = 0;
    Rect r;
    if(done != 100 && !effect_type) {
        last = glActiveContext();
        glActivateContext(context);
        r = size();
        setRealRect(Rect(0, 0, r.w(), r.h()));
    }

    if(!effect_type) {
        glSetPen(0xF0000000);
        glDrawFilledRectange(realRect().x()+1, realRect().y()+1, realRect().x2()-1, realRect().y2()-1);
        glSetPen(0xFFFFFFFF);
        glDrawRectange(realRect().x(), realRect().y(), realRect().x2(), realRect().y2());

        glSetPen(0xFFFFFFFF);
        glDrawString(m_question.c_str(), realRect().x()+2, realRect().y()+4, realRect().x2()-4, realRect().y2()-60, 23,
                     FT_TEXT_W_CENTER | FT_TEXT_SENTENCEBREAK | FT_TEXT_H_CENTER, 0, 256);


        Widget::paintEvent();
    } else {

        if(effect_type == 1) {

            int new_w = context->width * done / 100;
            int new_h = context->height * done / 100;

            done += speed;
            speed += (speed*15 /100);
            if(done >= 100) {
                animation.stop();
                done = 100;
                effect_type = 0;
                eventManager()->updateAfterEvent();
            }


            int cx = context->width/2 - new_w/2;
            int cy = context->height/2 - new_h/2;

            ScaleAndPaint(glActiveContext(), (unsigned short*)framebuffer, context->width, context->height,
                          realRect().x()+cx, realRect().y()+cy, new_w, new_h, 255);
        }

    }

    if(done != 100 && !effect_type) {
        glActivateContext(last);
        setRealRect(r);
    }
}


void QuestionDialog::timerEvent(Timer *)
{
    eventManager()->updateAfterEvent();
}


bool QuestionDialog::show()
{
    paintEvent();

    done = 10;
    speed = 10;
    effect_type = 1;
    animation.start(1);

    return Widget::show();
}


bool QuestionDialog::hide()
{
    return Widget::hide();
}

