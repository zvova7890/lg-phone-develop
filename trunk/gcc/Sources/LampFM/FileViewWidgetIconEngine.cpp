
#include <Core/compatible.h>
#include "FileViewWidgetIconEngine.h"
#include "FileViewWidget.h"
#include "FileViewWidgetAbstractItem.h"
#include <fs.h>





/**********************************************************************************************/
/********************************** FileViewWidgetIconItem ************************************/
/**********************************************************************************************/


FileViewWidgetIconItem::FileViewWidgetIconItem(FileViewWidget *parent, int w, int h, int num, const std::vector<FSEntryInfo> &entries) :
    Widget(Rect(0, 0, w, h), parent),
    m_maxView(num),
    m_widgetParent(parent)
{
    m_fsInfo = entries;

    int subitem_w = 5;
    int startx = 1;
    int max_width = (rect().w()-(startx*2)-(subitem_w*(num-1))) /num;


    for(unsigned int i=0; i<m_fsInfo.size(); ++i) {
        FsEntryItem *it = new FsEntryItem(this, 0, Rect(startx, 0, max_width, h));
        it->setFSEntryItem(&m_fsInfo[i]);
        add(it);
        startx += max_width+subitem_w;
    }
}


FileViewWidgetIconItem::~FileViewWidgetIconItem()
{
    // that provide a copy of childs list, because childs can do self-removing from tham
    auto c = childs();

    for(Widget *item : c) {
        delete ((FsEntryItem*)item);
    }

    m_childs.clear();
}



void FileViewWidgetIconItem::resizeEvent()
{
    Widget::resizeEvent();

    int num = m_maxView;
    int subitem_w = 5;
    int startx = 1;
    int max_width = (rect().w()-(startx*2)-(subitem_w*(num-1))) /num;

    for(Widget *w : directChilds())
    {
        w->setSize(Rect(startx, 0, max_width, rect().h()));
        startx += max_width+subitem_w;
    }
}


void FileViewWidgetIconItem::paintEvent()
{
    /*if(isTouched() && !isMoved()) {
        glSetPen(0x4FFF0000);
        glDrawFilledRectange(realRect().x(), realRect().y(), realRect().x()+realRect().w(), realRect().y() + realRect().x()+realRect().h());
    }*/

    Widget::paintEvent();
}


void FileViewWidgetIconItem::touchEvent(int action, int x, int y)
{
    Widget::touchEvent(action, x, y);
}


void FileViewWidgetIconItem::itemTouched(FSEntryInfo *fs_entry)
{
    //if(!fs_entry)
     //   return;

    if(fs_entry->attr & FSProtocol::FSEntryFlags::Dir) {

        if(fs_entry->name == ".." && fs_entry->action) {
            m_widgetParent->cdUpAfterAction(std::string());
        } else {
            m_widgetParent->cdUpAfterAction(fs_entry->name);
        }
    } else {
        extensionManager().run(m_widgetParent->directory() + fs_entry->name);
    }
}



void FileViewWidgetIconItem::FsEntryItem::paintEvent()
{
    if(m_fsEntryInfo) {
        int x = realRect().x();
        int y = realRect().y();

        int w = realRect().w();
        int h = realRect().h();

        glSaveClipRegion();
        glSetClipRegion(x, y, x+w, y+h);

        if(isTouched() && !isMoved()) {

            if(m_isLongPress)
                glSetPen(0x4FFF00FF);
            else
                glSetPen(0x4FFF0000);
            glDrawFilledRectange(x, y, x+w, y+h);
        }


        Image *img = 0;
        if(m_fsEntryInfo->action) {
            if(m_fsEntryInfo->name == "..") {
                img = &m_itemParent->m_widgetParent->back_action_icon;

                if(!img->isEmpty())
                    drawImage(x + (rect().w()/2-img->width()/2), y+2, img);
            }

        } else {
            if(m_fsEntryInfo->attr & FSProtocol::FSEntryFlags::Dir) {

                img = &m_itemParent->m_widgetParent->folder_icon;

                if(!img->isEmpty())
                    drawImage(x + (rect().w()/2-img->width()/2), y+2, img);
            } else {
                img = &m_itemParent->m_widgetParent->file_icon;

                if(!img->isEmpty())
                    drawImage(x + (rect().w()/2-img->width()/2), y+2, img);
            }
        }

        if(m_widgetParent->isSelectionMode() && !m_fsEntryInfo->action) {
            if(isMarked()) {
                drawImage(x, y, &m_widgetParent->checkedbox_icon);

            } else {
                drawImage(x, y, &m_widgetParent->checkbox_icon);
            }
        }

        //uint32_t font_h, font_top;
        int attr = FT_TEXT_H_CENTER | FT_TEXT_W_CENTER | FT_TEXT_CENTER_BY_XSTART;
        /*int font_w = glStringMetrics(13, _fs_entry_info->name.c_str(), &font_h, &font_top, 50);

        if(font_w < w) {
            attr |= FT_TEXT_W_CENTER;
        }*/

        int yc = y;

        if(img && !img->isEmpty()) {
            yc += img->height();
        }


        if(m_fsEntryInfo->attr & FSProtocol::FSEntryFlags::Hidden) {
            if(m_fsEntryInfo->attr & FSProtocol::FSEntryFlags::Readonly)
                glSetPen(0xFF925252);
            else
                glSetPen(0xFF525252);
        } else if(m_fsEntryInfo->attr & FSProtocol::FSEntryFlags::Readonly)
            glSetPen(0xFF520000);
        else
            glSetPen(0xFFFFFFFF);

        glDrawString(m_fsEntryInfo->name.c_str(), x, yc, x+w, y+h, 13, attr, 0, 50);

        glRestoreClipRegion();
    }
}


void FileViewWidgetIconItem::FsEntryItem::touchEvent(int action, int x, int y)
{
    ((void)x);
    ((void)y);

    //printf("void FileViewWidgetIconItem::FsEntryItem::touchEvent() %d %dx%d\n", action, x, y);
    if(isMoved())
        return;

    switch(action)
    {
        case TOUCH_ACTION_PRESS:
            m_isLongPress = false;
            break;

        case TOUCH_ACTION_RELEASE:

            if(m_isLongPress && !m_fsEntryInfo->action && m_fsEntryInfo->name != "..") {
                m_itemParent->m_widgetParent->onItemMenu(*m_fsEntryInfo, this);
                m_isLongPress = false;
                return;
            }

            if(m_widgetParent->isSelectionMode() && !m_fsEntryInfo->action) {
                setMarked(!isMarked());
                m_widgetParent->eventManager()->updateAfterEvent();
                return;
            }

            m_itemParent->itemTouched(m_fsEntryInfo);
            m_isLongPress = false;
            break;

        case TOUCH_ACTION_LONGPRESS:

            m_isLongPress = true;
            m_itemParent->m_widgetParent->eventManager()->updateAfterEvent();
            break;
    }

    //_item_parent->_fvparent->event_mngr->updateAfterEvent();
}




/**********************************************************************************************/
/********************************* FileViewWidgetIconEngine ***********************************/
/**********************************************************************************************/


FileViewWidgetIconEngine::FileViewWidgetIconEngine(FileViewWidget *parent) :
    FileViewWidgetEngine(parent)
{
    //event_mngr = &eventManager();
}



FileViewWidgetIconEngine::~FileViewWidgetIconEngine()
{
    clearItems();
}


Widget *FileViewWidgetIconEngine::getListItem(int index)
{
    int size = 0;
    if(fileSystemEntriesCount()) {
        size = (fileSystemEntriesCount())/3+1;
        if(!(fileSystemEntriesCount() % 3) && size > 0)
            size-=1;
    } else
        return 0;


    if(index < 0) {
        printf("Warning: index must be >= 0. item: %d, index: %d\n ", fileViewParent()->fileViewArea().item(), index);
        return 0;
    }

    if(index >= size) {
        printf("Warning: index value is bigger than have items\n ");
        return 0;
    }

    FileViewWidgetIconItem *fi = 0;
    if((int)m_items.size() <= index || !m_items[index]) {
        int old_size = m_items.size();

        if((int)m_items.size() <= index)
            m_items.resize(index+1);

        for(unsigned int i = old_size; i<m_items.size(); ++i)
            m_items[i] = 0;


        if(!m_items[index]) {

            std::vector<FSEntryInfo> entries;
            entries.reserve(3);

            for(int i=0; i<3; ++i) {
                if((int)fileSystemEntriesCount() > index*3+i) {
                    entries.push_back(fileViewParent()->getFSEntry(index*3+i));
                }
            }

            m_items[index] = new FileViewWidgetIconItem(fileViewParent(), fileViewParent()->rect().w(), 50, 3, entries);

            m_items[index]->handleResizeEvent().connect( [](Widget *w) {
                w->setSize(Rect(0, 0, w->parent()->rect().w(), 50));
            });
        }

        fi = (FileViewWidgetIconItem*)m_items[index];

    } else
        fi = (FileViewWidgetIconItem*)m_items[index];

    return fi;
}


void FileViewWidgetIconEngine::resizeEvent()
{
    for(Widget *w : m_items) {
        if(w) {
            w->resizeEvent();
        }
    }
}


void FileViewWidgetIconEngine::clearItems()
{
    for(FileViewWidgetIconItem * i : m_items)
    {
        if(i)
            delete i;
    }

    m_items.clear();
}


int  FileViewWidgetIconEngine::itemBySystemEntryNumber(int n)
{
    if(n < 0 && n >= (int)fileSystemEntriesCount()) {
        return 0;
    }

    int line = (n)/3+1;
    if(!(n % 3) && line > 0)
        line-=1;

    return line;
}


int  FileViewWidgetIconEngine::fileSystemEntryByItem(int n)
{
    if(n < 0 && n >= (int)m_items.size()) {
        return 0;
    }

    return n*3;
}


int FileViewWidgetIconEngine::itemsForViewList()
{
    int size = 0;
    if(fileSystemEntriesCount()) {
        size = (fileSystemEntriesCount())/3+1;
        if(!(fileSystemEntriesCount() % 3) && size > 0)
            size-=1;
    }

    return size;
}


int FileViewWidgetIconEngine::fsEntriesPerLine()
{
    return 3;
}


int FileViewWidgetIconEngine::viewItemsCount()
{
    return m_items.size();
}


void FileViewWidgetIconEngine::setMarkedAll()
{
    for(int i=0; i<itemsForViewList(); ++i)
    {
        FileViewWidgetIconItem * item = 0;

        if((unsigned int)i >= m_items.size())
        {
            getListItem(i);
            item = m_items[i];
        }
        else
            item = m_items[i];

        if(!item) {
            getListItem(i);
            item = m_items[i];
        }

        if(item) {
            /* iterate items per line */

            for(auto items : item->directChilds())
            {
                auto fei = ((FileViewWidgetIconItem::FsEntryItem*)items);
                fei->setMarked();
            }
        }
    }
}


void FileViewWidgetIconEngine::setUnMarkedAll()
{
    for(FileViewWidgetIconItem * i : m_items)
    {
        if(i) {
            for(auto item : i->directChilds())
            {
                auto fei = (FileViewWidgetIconItem::FsEntryItem*)item;
                fei->setMarked(false);
            }
        }
    }
}


std::list<const FSEntryInfo *> FileViewWidgetIconEngine::getSelectedEntriesList()
{
    std::list<const FSEntryInfo *> list;

    for(FileViewWidgetIconItem * i : m_items)
    {
        if(i) {
            for(auto item : i->directChilds())
            {
                auto fei = (FileViewWidgetIconItem::FsEntryItem*)item;
                if(i && fei->isMarked() && !fei->getSelectedEntry().action) {
                    list.push_back(&fei->getSelectedEntry());
                }
            }
        }
    }

    return list;
}


void FileViewWidgetIconEngine::block()
{
    m_isBlocked = true;
}


void FileViewWidgetIconEngine::unblock()
{
    m_isBlocked = false;
}
