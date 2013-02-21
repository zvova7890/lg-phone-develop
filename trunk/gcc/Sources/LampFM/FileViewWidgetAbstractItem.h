#ifndef FILEVIEWWIDGETABSTRACTITEM_H
#define FILEVIEWWIDGETABSTRACTITEM_H


#include "ActiveList.h"
#include "FSEntryInfo.h"
#include "FileViewWidget.h"



class FileViewWidgetAbstractItem
{
public:

    FileViewWidgetAbstractItem(FileViewWidget *parent) :
        _fvparent(parent),
        _is_marked(false),
        _not_file(false)
    {
    }

    virtual ~FileViewWidgetAbstractItem() {

    }

    virtual const FSEntryInfo & getSelectedEntry() {
        extern FSEntryInfo __fs_entryinfo_null_entry;
        return __fs_entryinfo_null_entry;
    }


    bool isMarked() const {
        return _is_marked;
    }

    void setMarked(bool is = true) {

        if(_is_marked != is) {
            if(!_not_file) {
                /*if(is)
                    _fvparent->marked_files++;
                else
                    _fvparent->marked_files--;*/
            }
            _is_marked = is;
        }
    }

    FileViewWidget *parentWidget() {
        return _fvparent;
    }

protected:
    FileViewWidget *_fvparent;
    bool _is_marked;
    bool _not_file;

};



#endif // FILEVIEWWIDGETABSTRACTITEM_H
