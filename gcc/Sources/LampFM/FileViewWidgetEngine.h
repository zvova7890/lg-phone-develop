#ifndef FILEVIEWWIDGETENGINE_H
#define FILEVIEWWIDGETENGINE_H


#include "EventManager.h"
#include "ActiveList.h"


class FileViewWidget;

class FileViewWidgetEngine
{
public:
    FileViewWidgetEngine(FileViewWidget *parent);
    virtual ~FileViewWidgetEngine();

    /* must return a ScrollAreaItem for SrollArea engine */
    virtual ScrollAreaItem *getListItem(int /*index*/) {
        return 0;
    }

    /* calling when need too clear all items */
    virtual void clearItems() {

    }

    /* n - is nummber of fs entry in list, function must return when the fs entry is placed(item number) */
    virtual int  itemBySystemEntryNumber(int /*n*/) {
        return 0;
    }

    /* ^ reverse */
    virtual int  fileSystemEntryByItem(int /*n*/) {
        return 0;
    }

    /* must return how much items need to be viewed with curent fs entries */
    virtual int  itemsForViewList() {
        return 0;
    }

    /* must return is number of fs entries, there can be view per item line */
    virtual int fsEntriesPerLine() {
        return 0;
    }

    /* must return how much all items needs to be, for view of current fs entries */
    virtual int viewItemsCount() {
        return 0;
    }


    /* ATENTION: KEP in thread! ;) */

    /* return fs enrties count */
    int fileSystemEntriesCount();

    /* parent widget */
    inline FileViewWidget *fileViewParent() {
        return _fparent;
    }


protected:


protected:
    FileViewWidget *_fparent;
    EventManager *event_mngr;
};



#endif // FILEVIEWWIDGETENGINE_H
