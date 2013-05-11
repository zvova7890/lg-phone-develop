#ifndef FILEVIEWWIDGETICONENGINE_H
#define FILEVIEWWIDGETICONENGINE_H


#include <Widget.h>
#include "FileViewWidgetEngine.h"
#include "FileViewWidgetAbstractItem.h"
#include "FSEntryInfo.h"



class FileViewWidgetIconItem : public Widget
{
public:
    class FsEntryItem : public Widget, public FileViewWidgetAbstractItem
    {
    public:
        FsEntryItem(FileViewWidgetIconItem *parent, FSEntryInfo *fentry, const Rect &r) :
            Widget(r, parent),
            FileViewWidgetAbstractItem((FileViewWidget*)parent->parent()),
            m_isLongPress(false),
            m_fsEntryInfo(fentry),
            m_itemParent(parent)
        {
        }

        virtual ~FsEntryItem() {

        }

        const FSEntryInfo & getSelectedEntry() {
            return *m_fsEntryInfo;
        }

        void paintEvent();
        void touchEvent(int action, int x, int y);

        inline void setFSEntryItem(FSEntryInfo *fs_entry) {
            m_fsEntryInfo = fs_entry;
        }

    protected:
        bool m_isLongPress;
        FSEntryInfo *m_fsEntryInfo;
        FileViewWidgetIconItem *m_itemParent;
    };


public:
    FileViewWidgetIconItem(FileViewWidget *parent, int w, int h, int num, const std::vector<FSEntryInfo> &entries);
    virtual ~FileViewWidgetIconItem();

    void paintEvent();
    void touchEvent(int action, int x, int y);
    void resizeEvent();

protected:
    void itemTouched(FSEntryInfo *);
    /*FsEntryItem *entryItem(int at) {
        return (FsEntryItem*)m_touchArea.queueItem(at)->user;
    }*/

protected:
    std::vector<FSEntryInfo> m_fsInfo;
    int m_maxView;
    FileViewWidget *m_widgetParent;
};



class FileViewWidgetIconEngine : public FileViewWidgetEngine
{
public:
    FileViewWidgetIconEngine(FileViewWidget *parent);
    virtual ~FileViewWidgetIconEngine();

    Widget *getListItem(int index);
    int  itemBySystemEntryNumber(int n);
    int  fileSystemEntryByItem(int n);
    void resizeEvent();
    void clearItems();
    int itemsForViewList();
    int fsEntriesPerLine();
    int viewItemsCount();

    void setMarkedAll();
    void setUnMarkedAll();
    std::list<const FSEntryInfo *> getSelectedEntriesList();

    void block();
    void unblock();

protected:
    std::vector <FileViewWidgetIconItem*> m_items;
    bool m_isBlocked;
};

#endif // FILEVIEWWIDGETICONENGINE_H
