
#include "QuestionDialog.h"
#include "main.h"





QuestionDialog::QuestionDialog(Widget *parent, const Rect &r, const std::string &question) :
    Widget(r, parent),
    m_question(question)
{
    setFullScreenBlock(true);


    int button_w = rect().w()/2-10;
    int button_h = button_w/2-10;

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
}



QuestionDialog::~QuestionDialog()
{
    for(Widget *i: childs())
        delete i;

    directChilds().clear();
}


void QuestionDialog::parentHasDied()
{

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



void QuestionDialog::paintEvent()
{
    glSetPen(0xF0000000);
    glDrawFilledRectange(realRect().x()+1, realRect().y()+1, realRect().x2()-1, realRect().y2()-1);
    glSetPen(0xFFFFFFFF);
    glDrawRectange(realRect().x(), realRect().y(), realRect().x2(), realRect().y2());

    glSetPen(0xFFFFFFFF);
    glDrawString(m_question.c_str(), realRect().x()+2, realRect().y()+4, realRect().x2()-4, realRect().y2()-60, 23,
                 FT_TEXT_W_CENTER | FT_TEXT_SENTENCEBREAK | FT_TEXT_H_CENTER, 0, 256);


    Widget::paintEvent();
}


