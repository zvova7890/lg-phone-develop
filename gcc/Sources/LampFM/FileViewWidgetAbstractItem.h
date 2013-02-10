#ifndef FILEVIEWWIDGETABSTRACTITEM_H
#define FILEVIEWWIDGETABSTRACTITEM_H


#include "ActiveList.h"


class FileViewWidget;

class FileViewWidgetAbstractItem : public ActiveListItem
{
public:

    FileViewWidgetAbstractItem(FileViewWidget *parent, int w, int h) :
        ActiveListItem((ActiveList*)parent, w, h),
        _fvparent(parent)
    {
    }

    virtual ~FileViewWidgetAbstractItem() {

    }


    bool isMarked() const {
        return _is_marked;
    }

    FileViewWidget *parentWidget() {
        return _fvparent;
    }

protected:
    FileViewWidget *_fvparent;
    bool _is_marked;

};



#endif // FILEVIEWWIDGETABSTRACTITEM_H
