
#include "QuestionDialog.h"
#include "main.h"





QuestionDialog::QuestionDialog(UActiveArea *parent, const Rect &r, const std::string &question) :
    UActiveAreaItem<ActiveAreaItem>(parent, r),
    m_question(question),
    m_buttonsArea(parent->eventManager(), r)
{
    setFullScreenBlock(true);


    int button_w = rect().w()/2-10;
    int button_h = button_w/2-10;

    m_buttons.push_back( new UButton(parent, Rect(5, rect().h()-button_h-5, button_w, button_h), "Yes") );
    m_buttons.push_back( new UButton(parent, Rect(rect().w()-button_w-5, rect().h()-button_h-5, button_w, button_h), "No") );


    m_buttons[0]->releasedSignal().connect ( [this](UButton *self) {

        if(self->isTouched() && !self->isMoved()) {
            m_buttonPressed.trigger(this, 1);
            return;
        }
    } );

    m_buttons[1]->releasedSignal().connect ( [this](UButton *self) {

        if(self->isTouched() && !self->isMoved()) {
            m_buttonPressed.trigger(this, 0);
            return;
        }
    } );


    m_buttonsArea.push(m_buttons[0]);
    m_buttonsArea.push(m_buttons[1]);
}



QuestionDialog::~QuestionDialog()
{
    for(UActiveAreaItem<ActiveAreaItem> *i: m_buttons)
        delete i;

    m_buttons.clear();
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


    m_buttonsArea.move(rect().x(), rect().y());
    m_buttonsArea.touchEvent(action, x, y);
}



void QuestionDialog::paintEvent()
{
    glSetPen(0xF0000000);
    glDrawFilledRectange(rect().x()+1, rect().y()+1, rect().x2()-1, rect().y2()-1);
    glSetPen(0xFFFFFFFF);
    glDrawRectange(rect().x(), rect().y(), rect().x2(), rect().y2());

    glSetPen(0xFFFFFFFF);
    glDrawString(m_question.c_str(), rect().x()+2, rect().y()+4, rect().x2()-4, rect().y2()-60, 23,
                 FT_TEXT_W_CENTER | FT_TEXT_SENTENCEBREAK | FT_TEXT_H_CENTER, 0, 256);


    m_buttonsArea.move(rect().x(), rect().y());
    m_buttonsArea.paintEvent();
}



void QuestionDialog::show()
{
    mainActiveArea().pushFront(this);
}


void QuestionDialog::hide()
{
    mainActiveArea().pop(this);
}

