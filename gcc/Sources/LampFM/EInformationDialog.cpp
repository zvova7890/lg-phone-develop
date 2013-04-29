
#include "EInformationDialog.h"
#include <gl.h>





// FIXME


EInformationDialog::EInformationDialog(Widget *parent, const Rect &r) :
    VScrollArea(r, parent)
{

}



EInformationDialog::~EInformationDialog()
{
    /*for(auto item : *itemList())
    {
        ActiveListItem *it = item;
        delete item;
    }*/
    printf("EntryInformationDialog destroyed\n");
    hide();
}



void EInformationDialog::paintEvent()
{
    glSaveClipRegion();
    glSetClipRegion(rect().x(), rect().y(), rect().x2(), rect().y2());

    glSetPen(0xFF000000);
    glDrawFilledRectange(rect().x(), rect().y(), rect().x2(), rect().y2());

    //ActiveList::paintEvent();

    glRestoreClipRegion();
}


void EInformationDialog::touchEvent(int action, int x, int y)
{
    (void) action;
    (void) x;
    (void) y;

    //ActiveList::touchEvent(action, x, y);
}




void EInformationDialog::show()
{
    //_parent->pushFront(this);
    m_stateChanget.trigger(this, 1);
}


void EInformationDialog::hide()
{
    //_parent->pop(this);
    m_stateChanget.trigger(this, 2);
}
