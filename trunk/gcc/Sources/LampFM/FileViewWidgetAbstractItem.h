#ifndef FILEVIEWWIDGETABSTRACTITEM_H
#define FILEVIEWWIDGETABSTRACTITEM_H



#include "FSEntryInfo.h"
#include "FileViewWidget.h"



class FileViewWidgetAbstractItem
{
public:

    FileViewWidgetAbstractItem(FileViewWidget *parent) :
        m_widgetParent(parent),
        m_isMarked(false),
        m_notFile(false)
    {
    }

    virtual ~FileViewWidgetAbstractItem() {

    }

    virtual const FSEntryInfo & getSelectedEntry() {
        return FSEntryInfo::null;
    }


    bool isMarked() const {
        return m_isMarked;
    }

    void setMarked(bool is = true) {

        if(m_isMarked != is) {
            if(!m_notFile) {
                /*if(is)
                    _fvparent->marked_files++;
                else
                    _fvparent->marked_files--;*/
            }
            m_isMarked = is;
        }
    }

    FileViewWidget *parentWidget() {
        return m_widgetParent;
    }

protected:
    FileViewWidget *m_widgetParent;
    bool m_isMarked;
    bool m_notFile;

};



#endif // FILEVIEWWIDGETABSTRACTITEM_H
