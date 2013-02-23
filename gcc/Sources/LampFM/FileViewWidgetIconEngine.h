#ifndef FILEVIEWWIDGETICONENGINE_H
#define FILEVIEWWIDGETICONENGINE_H

#include "FileViewWidgetEngine.h"
#include "FileViewWidgetAbstractItem.h"
#include "ActiveList.h"
#include "FSEntryInfo.h"



class FileViewWidgetIconItem : public ActiveListItem
{
public:
    class FsEntryItem : public UActiveAreaItem<ActiveAreaItem>, public FileViewWidgetAbstractItem
    {
    public:
        FsEntryItem(FileViewWidgetIconItem *parent, FSEntryInfo *fentry, const Rect &r) :
            UActiveAreaItem<ActiveAreaItem>(r, false),
            FileViewWidgetAbstractItem((FileViewWidget*)parent->parent()),
            _is_longpress(false),
            _fs_entry_info(fentry),
            _item_parent(parent)
        {
        }

        virtual ~FsEntryItem() {

        }

        const FSEntryInfo & getSelectedEntry() {
            return *_fs_entry_info;
        }

        void paintEvent();
        void touchEvent(int action, int x, int y);

        inline void setFSEntryItem(FSEntryInfo *fs_entry) {
            _fs_entry_info = fs_entry;
        }

    protected:
        bool _is_longpress;
        FSEntryInfo *_fs_entry_info;
        FileViewWidgetIconItem *_item_parent;
    };


public:
    FileViewWidgetIconItem(FileViewWidget *parent, int w, int h, int num, const std::vector<FSEntryInfo> &entries);
    virtual ~FileViewWidgetIconItem();

    void paintEvent();
    void touchEvent(int action, int x, int y);

    UActiveArea *itemsUActiveArea() {
        return &_touch_area;
    }

protected:
    void itemTouched(FSEntryInfo *);
    FsEntryItem *entryItem(int at) {
        return (FsEntryItem*)_touch_area.queueItem(at)->user;
    }

protected:
    std::vector<FSEntryInfo> _fsinfo;
    int max_view;
    FileViewWidget *_fvparent;
    UActiveArea _touch_area;
};



class FileViewWidgetIconEngine : public FileViewWidgetEngine
{
public:
    FileViewWidgetIconEngine(FileViewWidget *parent);
    virtual ~FileViewWidgetIconEngine();

    ScrollAreaItem *getListItem(int index);
    int  itemBySystemEntryNumber(int n);
    int  fileSystemEntryByItem(int n);
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
    std::vector <FileViewWidgetIconItem*> _items;
    bool _is_blocked;
};

#endif // FILEVIEWWIDGETICONENGINE_H
