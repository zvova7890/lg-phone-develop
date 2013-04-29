#ifndef FILEVIEWWIDGETLISTENGINE_H
#define FILEVIEWWIDGETLISTENGINE_H


#include <Widget.h>
#include "FileViewWidgetEngine.h"
#include "FileViewWidgetAbstractItem.h"
#include "FSEntryInfo.h"


class FileViewWidget;


class FileViewWidgetListItem : public FileViewWidgetAbstractItem, public Widget
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

    Widget *getListItem(int index);
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
    int fullListHeight() const;

protected:
    std::vector <FileViewWidgetListItem*> m_items;
    bool m_isBlocked;
    int m_fullHeight;
};



#endif // FILEVIEWWIDGETLISTENGINE_H
