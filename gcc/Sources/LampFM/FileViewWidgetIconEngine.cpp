#include "FileViewWidgetIconEngine.h"
#include "FileViewWidget.h"
#include "FileViewWidgetAbstractItem.h"
#include <fs.h>





/**********************************************************************************************/
/********************************** FileViewWidgetIconItem ************************************/
/**********************************************************************************************/


FileViewWidgetIconItem::FileViewWidgetIconItem(FileViewWidget *parent, int w, int h, int num, const std::vector<FSEntryInfo> &entries) :
    ActiveListItem(parent, w, h),
    _fvparent(parent),
   _touch_area(parent->eventManager(), Rect(0, 0, w, h))
{
    _fsinfo = entries;

    int subitem_w = 5;
    int startx = 1;
    int max_width = (rect().w()-(startx*2)-(subitem_w*(num-1))) /num;


    for(unsigned int i=0; i<_fsinfo.size(); ++i) {
        FsEntryItem *it = new FsEntryItem(this, 0, Rect(startx, 0, max_width, h));
        it->setFSEntryItem(&_fsinfo[i]);
        _touch_area.push(it);
        startx += max_width+subitem_w;
    }
}


FileViewWidgetIconItem::~FileViewWidgetIconItem()
{
    /*GLQueueList *q = _touch_area.itemsQueue();
    GLQueueListItem *item;
    for(item = q->first; item; item = (GLQueueListItem*)item->next)
    {
        ActiveAreaItem *titem = *glQueueListItemBody(item, ActiveAreaItem **);
        auto aai = (FsEntryItem*)titem->user;
        delete aai;
    }*/

    /* iterator style for items queue */
    for(auto item : _touch_area)
    {
        auto fei = (FsEntryItem*)item->user;
        delete fei;
    }
}


void FileViewWidgetIconItem::paintEvent()
{
    _touch_area.move(rect().x(), rect().y());

    /*if(isTouched() && !isMoved()) {
        glSetPen(0x4FFF0000);
        glDrawFilledRectange(rect().x(), rect().y(), rect().x()+rect().w(), rect().y() + rect().x()+rect().h());
    }*/

    _touch_area.paintEvent();
}


void FileViewWidgetIconItem::touchEvent(int action, int x, int y)
{
    _touch_area.move(rect().x(), rect().y());
    _touch_area.touchEvent(action, x, y);
}


void FileViewWidgetIconItem::itemTouched(FSEntryInfo *fs_entry)
{
    //if(!fs_entry)
     //   return;

    if(fs_entry->attr & FSProtocol::FSEntryFlags::Dir) {

        if(fs_entry->name == ".." && fs_entry->action) {
            _fvparent->cdUpAfterAction(std::string());
        } else {
            _fvparent->cdUpAfterAction(fs_entry->name);
        }
    } else {
        extensionManager().run(_fvparent->directory() + fs_entry->name);
    }
}



void FileViewWidgetIconItem::FsEntryItem::paintEvent()
{
    if(_fs_entry_info) {
        int x = _item_parent->rect().x() + rect().x();
        int y = _item_parent->rect().y() + rect().y();

        int w = rect().w();
        int h = rect().h();

        glSaveClipRegion();
        glSetClipRegion(x, y, x+w, y+h);

        if(isTouched() && !isMoved()) {

            if(_is_longpress)
                glSetPen(0x4FFF00FF);
            else
                glSetPen(0x4FFF0000);
            glDrawFilledRectange(x, y, x+w, y+h);
        }


        image_t *img = 0;
        if(_fs_entry_info->action) {
            if(_fs_entry_info->name == "..") {
                img = &_item_parent->_fvparent->back_action_icon;

                if(img->bitmap)
                    drawImage(x + (rect().w()/2-img->w/2), y+2, img);
            }

        } else {
            if(_fs_entry_info->attr & FSProtocol::FSEntryFlags::Dir) {

                img = &_item_parent->_fvparent->folder_icon;

                if(img->bitmap)
                    drawImage(x + (rect().w()/2-img->w/2), y+2, img);
            } else {
                img = &_item_parent->_fvparent->file_icon;

                if(img->bitmap)
                    drawImage(x + (rect().w()/2-img->w/2), y+2, img);
            }
        }

        if(_fvparent->isSelectionMode() && !_fs_entry_info->action) {
            if(isMarked()) {
                drawImage(x, y, &_fvparent->checkedbox_icon);

            } else {
                drawImage(x, y, &_fvparent->checkbox_icon);
            }
        }

        //uint32_t font_h, font_top;
        int attr = FT_TEXT_H_CENTER | FT_TEXT_W_CENTER | FT_TEXT_CENTER_BY_XSTART;
        /*int font_w = glStringMetrics(13, _fs_entry_info->name.c_str(), &font_h, &font_top, 50);

        if(font_w < w) {
            attr |= FT_TEXT_W_CENTER;
        }*/

        int yc = y;

        if(img && img->bitmap) {
            yc += img->h;
        }


        if(_fs_entry_info->attr & FSProtocol::FSEntryFlags::Hidden) {
            if(_fs_entry_info->attr & FSProtocol::FSEntryFlags::Readonly)
                glSetPen(0xFF925252);
            else
                glSetPen(0xFF525252);
        } else if(_fs_entry_info->attr & FSProtocol::FSEntryFlags::Readonly)
            glSetPen(0xFF520000);
        else
            glSetPen(0xFFFFFFFF);

        glDrawString(_fs_entry_info->name.c_str(), x, yc, x+w, y+h, 13, attr, 0, 50);

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
            _is_longpress = false;
            break;

        case TOUCH_ACTION_RELEASE:

            if(_is_longpress && !_fs_entry_info->action && _fs_entry_info->name != "..") {
                _item_parent->_fvparent->onItemMenu(*_fs_entry_info, this);
                _is_longpress = false;
                return;
            }

            if(_fvparent->isSelectionMode() && !_fs_entry_info->action) {
                setMarked(!isMarked());
                _fvparent->eventManager()->updateAfterEvent();
                return;
            }

            _item_parent->itemTouched(_fs_entry_info);
            _is_longpress = false;
            break;

        case TOUCH_ACTION_LONG_PRESS:

            _is_longpress = true;
            _item_parent->_fvparent->eventManager()->updateAfterEvent();
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


ScrollAreaItem *FileViewWidgetIconEngine::getListItem(int index)
{
    int size = 0;
    if(fileSystemEntriesCount()) {
        size = (fileSystemEntriesCount())/3+1;
        if(!(fileSystemEntriesCount() % 3) && size > 0)
            size-=1;
    } else
        return 0;


    if(index < 0) {
        printf("Warning: index must be >= 0. item: %d, index: %d\n ", fileViewParent()->item()->item, index);
        return 0;
    }

    if(index >= size) {
        printf("Warning: index value is bigger than have items\n ");
        return 0;
    }

    FileViewWidgetIconItem *fi = 0;
    if((int)_items.size() <= index || !_items[index]) {
        int old_size = _items.size();

        if((int)_items.size() <= index)
            _items.resize(index+1);

        for(unsigned int i = old_size; i<_items.size(); ++i)
            _items[i] = 0;


        if(!_items[index]) {

            std::vector<FSEntryInfo> entries;
            entries.reserve(3);

            for(int i=0; i<3; ++i) {
                if((int)fileSystemEntriesCount() > index*3+i) {
                    entries.push_back(fileViewParent()->getFSEntry(index*3+i));
                }
            }

            _items[index] = new FileViewWidgetIconItem(fileViewParent(), fileViewParent()->rect().w(), 50, 3, entries);
        }

        fi = (FileViewWidgetIconItem*)_items[index];

    } else
        fi = (FileViewWidgetIconItem*)_items[index];

    return fi->item();
}


void FileViewWidgetIconEngine::clearItems()
{
    for(FileViewWidgetIconItem * i : _items)
    {
        if(i)
            delete i;
    }

    _items.clear();
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
    if(n < 0 && n >= (int)_items.size()) {
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
    return _items.size();
}


void FileViewWidgetIconEngine::setMarkedAll()
{
    for(int i=0; i<itemsForViewList(); ++i)
    {
        FileViewWidgetIconItem * item = 0;

        if((unsigned int)i >= _items.size())
        {
            getListItem(i);
            item = _items[i];
        }
        else
            item = _items[i];

        if(!item) {
            getListItem(i);
            item = _items[i];
        }

        if(item) {
            /* iterate items per line */
            for(auto items : *item->itemsUActiveArea())
            {
                auto fei = (FileViewWidgetIconItem::FsEntryItem*)items->user;
                fei->setMarked();
            }
        }
    }
}


void FileViewWidgetIconEngine::setUnMarkedAll()
{
    for(FileViewWidgetIconItem * i : _items)
    {
        if(i) {
            for(auto item : *i->itemsUActiveArea())
            {
                auto fei = (FileViewWidgetIconItem::FsEntryItem*)item->user;
                fei->setMarked(false);
            }
        }
    }
}


std::list<const FSEntryInfo *> FileViewWidgetIconEngine::getSelectedEntriesList()
{
    std::list<const FSEntryInfo *> list;

    for(FileViewWidgetIconItem * i : _items)
    {
        if(i) {
            for(auto item : *i->itemsUActiveArea())
            {
                auto fei = (FileViewWidgetIconItem::FsEntryItem*)item->user;
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
    _is_blocked = true;
}


void FileViewWidgetIconEngine::unblock()
{
    _is_blocked = false;
}
