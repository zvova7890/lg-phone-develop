#include "QuestionDialog.h"
#include "main.h"





QuestionDialog::QuestionDialog(UActiveArea *parent, const Rect &r, const std::string &question) :
    UActiveAreaItem<ActiveAreaItem>(parent, r),
    _question(question),
    buttons_area(parent->eventManager(), r)
{
    setFullScreenBlock(true);


    int button_w = rect().w()/2-10;
    int button_h = button_w/2-10;

    buttons.push_back( new UActiveAreaItem<ActiveAreaItem>(parent, Rect(rect().x()+5, rect().h()-button_h-5, button_w, button_h)) );
    buttons.push_back( new UActiveAreaItem<ActiveAreaItem>(parent, Rect(rect().x2()-button_w-5, rect().h()-button_h-5, button_w, button_h)) );


    buttons[0]->paintSignal().connect ( [this](UActiveAreaItem<ActiveAreaItem> *_i) {

        if(_i->isTouched())
            glSetPen(0xF0FFFFFF);
        else
            glSetPen(0xF0370700);

        int x = _i->rect().x();
        int y = rect().y()+_i->rect().y();

        glDrawFilledRectange(x+1, y+1, x+_i->rect().w()-1, y+_i->rect().h()-1);

        glSetPen(0xFF001800);
        glDrawRectange(x, y, x+_i->rect().w(), y+_i->rect().h());

        if(_i->isTouched())
            glSetPen(0xFF000000);
        else
            glSetPen(0xFFFFFFFF);

        glDrawString("Да", x, y, x+_i->rect().w(), y+_i->rect().h(), 14, FT_TEXT_H_CENTER | FT_TEXT_W_CENTER, 0, 128);

    } );


    buttons[1]->paintSignal().connect( [this](UActiveAreaItem<ActiveAreaItem> *_i) {

        if(_i->isTouched())
            glSetPen(0xF0FFFFFF);
        else
            glSetPen(0xF0370700);

        int x = _i->rect().x();
        int y = rect().y()+_i->rect().y();

        glDrawFilledRectange(x+1, y+1, x+_i->rect().w()-1, y+_i->rect().h()-1);

        glSetPen(0xFF001800);
        glDrawRectange(x, y, x+_i->rect().w(), y+_i->rect().h());

        if(_i->isTouched())
            glSetPen(0xFF000000);
        else
            glSetPen(0xFFFFFFFF);

        glDrawString("Нет", x, y, x+_i->rect().w(), y+_i->rect().h(), 14, FT_TEXT_H_CENTER | FT_TEXT_W_CENTER, 0, 128);
    } );


    buttons[0]->touchSignal().connect ( [this](UActiveAreaItem<ActiveAreaItem> *self, int action, int /*x*/, int /*y*/) {


        if(action == TOUCH_ACTION_RELEASE && self->isTouched() && !self->isMoved()) {
            __button_pressed.trigger(this, 1);
            return;
        }
        eventManager()->updateAfterEvent();
    } );

    buttons[1]->touchSignal().connect ( [this](UActiveAreaItem<ActiveAreaItem> *self, int action, int /*x*/, int /*y*/) {

        if(action == TOUCH_ACTION_RELEASE && self->isTouched() && !self->isMoved()) {
            printf("No pressed O_O\n");
            __button_pressed.trigger(this, 0);
            return;
        }
        eventManager()->updateAfterEvent();
    } );

    buttons_area.push(buttons[0]);
    buttons_area.push(buttons[1]);
}



QuestionDialog::~QuestionDialog()
{
    for(UActiveAreaItem<ActiveAreaItem> *i: buttons)
        delete i;

    buttons.clear();
}


void QuestionDialog::parentHasDied()
{

}


void QuestionDialog::touchEvent(int action, int x, int y)
{
    if(action == TOUCH_ACTION_RELEASE && isOffRectTouch() && !isMoved()) {
        hide();
        __button_pressed.trigger(this, 0);
        return;
    }

    buttons_area.touchEvent(action, x, y);
}



void QuestionDialog::paintEvent()
{
    glSetPen(0xF0000000);
    glDrawFilledRectange(rect().x()+1, rect().y()+1, rect().x2()-1, rect().y2()-1);
    glSetPen(0xFFFFFFFF);
    glDrawRectange(rect().x(), rect().y(), rect().x2(), rect().y2());

    glSetPen(0xFFFFFFFF);
    glDrawString(_question.c_str(), rect().x()+2, rect().y()+4, rect().x2()-4, rect().y2()-60, 23,
                 FT_TEXT_W_CENTER | FT_TEXT_SENTENCEBREAK | FT_TEXT_H_CENTER, 0, 256);

    buttons_area.paintEvent();
}



void QuestionDialog::show()
{
    mainActiveArea().pushFront(this);
}


void QuestionDialog::hide()
{
    mainActiveArea().pop(this);
}

