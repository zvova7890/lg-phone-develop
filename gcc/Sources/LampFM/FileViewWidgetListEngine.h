#ifndef FILEVIEWWIDGETLISTENGINE_H
#define FILEVIEWWIDGETLISTENGINE_H


#include "FileViewWidgetEngine.h"
#include "FileViewWidgetAbstractItem.h"
#include "ActiveList.h"
#include "FSEntryInfo.h"


class FileViewWidget;


class FileViewWidgetListItem : public FileViewWidgetAbstractItem, public ActiveListItem
{
public:
    FileViewWidgetListItem(FileViewWidget *parent, int w, int h, const FSEntryInfo &entry);
    virtual ~FileViewWidgetListItem();

    void paintEvent();
    void touchEvent(int action, int x, int y);

    const FSEntryInfo & getSelectedEntry();


private:
    bool _is_longpress;
    const FSEntryInfo & _fsinfo;
};



class FileViewWidgetListEngine : public FileViewWidgetEngine
{
public:
    FileViewWidgetListEngine(FileViewWidget *parent);
    virtual ~FileViewWidgetListEngine();

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
    std::vector <FileViewWidgetListItem*> _items;
    bool _is_blocked;
};



#endif // FILEVIEWWIDGETLISTENGINE_H