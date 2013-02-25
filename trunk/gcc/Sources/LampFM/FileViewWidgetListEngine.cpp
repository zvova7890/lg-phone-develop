
#include "FileViewWidget.h"
#include "FileViewWidgetListEngine.h"
#include "main.h"
#include <fs.h>



/**********************************************************************************************/
/********************************** FileViewWidgetListItem ************************************/
/**********************************************************************************************/


FileViewWidgetListItem::FileViewWidgetListItem(FileViewWidget *parent, int w, int h, const FSEntryInfo & entry) :
    FileViewWidgetAbstractItem(parent),
    ActiveListItem(parent, w, h),
    _is_longpress(false),
    _fsinfo(entry)
{
    _not_file = _fsinfo.action;
}


FileViewWidgetListItem::~FileViewWidgetListItem()
{

}


const FSEntryInfo &FileViewWidgetListItem::getSelectedEntry()
{
    return _fsinfo;
}


void FileViewWidgetListItem::paintEvent()
{
    if(!_fvparent->isSelectionMode())
        setMarked(false);

    int x = rect().x();
    int y = rect().y();

    if(isTouched() && !isMoved()) {

        if(_is_longpress) {
            glSetPen(0x4FFF00FF);
        } else
            glSetPen(0x4FFF0000);
        glDrawFilledRectange(x, y, x+rect().w(), y + x+rect().h());
    }

    glSetPen(0xFF332828);
    glDrawHLine(x, x+rect().w(), y);

    if(currentLineDisplayID() == (int)_fvparent->viewItemsCount()-1)
        glDrawHLine(x, x+rect().w(), y + x+rect().h());


    int x_offset = 4;

    if(!_fsinfo.action) {

        if(_fsinfo.attr & FSProtocol::FSEntryFlags::Dir) {

            image_t *img = &_fvparent->folder_icon;

            if(img->bitmap) {
                drawImage(x+1, y+2, img);
                x_offset += img->w;
            }
        } else {
            image_t *img = &_fvparent->file_icon;

            if(img->bitmap) {
                drawImage(x+1, y+2, img);
                x_offset += img->w;
            }
        }
    } else {
        //image_t *img = &_fvparent->back_action_icon;

        /*if(img->bitmap) {
            drawImage(x+1, y+2, img);
            x_offset += img->w;
        }*/
    }


    if(_fvparent->isSelectionMode() && !_fsinfo.action && _fsinfo.name != "..") {
        if( !isMarked() && _fvparent->checkbox_icon.bitmap)
        {
            drawImage(x+1, rect().y2()-_fvparent->checkbox_icon.h, &_fvparent->checkbox_icon);
            if(x_offset < _fvparent->checkbox_icon.w)
                x_offset = _fvparent->checkbox_icon.w+2;
        }

        if( isMarked() && _fvparent->checkedbox_icon.bitmap )
        {
            drawImage(x+1, rect().y2()-_fvparent->checkedbox_icon.h, &_fvparent->checkedbox_icon);
            if(x_offset < _fvparent->checkedbox_icon.w)
                x_offset = _fvparent->checkedbox_icon.w+2;
        }

    }


    if(!_fsinfo.name.empty()) {

        if(_fsinfo.attr & FSProtocol::FSEntryFlags::Hidden) {
            if(_fsinfo.attr & FSProtocol::FSEntryFlags::Readonly)
                glSetPen(0xFF925252);
            else
                glSetPen(0xFF525252);
        } else if(_fsinfo.attr & FSProtocol::FSEntryFlags::Readonly)
            glSetPen(0xFF520000);
        else
            glSetPen(0xFFFFFFFF);

        glDrawString(_fsinfo.name.c_str(), x_offset+x, y+4, x_offset+x+rect().w(), y+(rect().h()/2 + 14/2 ), 20, FT_TEXT_H_CENTER, 0, 56);


        char ext[128];
        if(_fsinfo.attr & FSProtocol::FSEntryFlags::Dir) {

            if(!_fsinfo.action)
                sprintf(ext, "folder");
            else if(_fsinfo.name == ".."){
                sprintf(ext, "back");
            }

        } else {
            sprintf(ext, "%s, 0", _fvparent->sizeToString(_fsinfo.size).c_str());
        }

        glDrawString(ext, x_offset+x+2, y, x_offset+x+rect().w(), y+rect().h()-2, 14, FT_TEXT_H_DOWN, 0, 56);
    }
}


void FileViewWidgetListItem::touchEvent(int action, int x, int y)
{
    ((void)x);
    ((void)y);

    if(isMoved())
        return;


    switch(action)
    {
        case TOUCH_ACTION_PRESS:
            _is_longpress = false;
            break;

        case TOUCH_ACTION_RELEASE:

            if(!_fsinfo.action && _fsinfo.name != "..") {

                if(_fvparent->isSelectionMode() && !_is_longpress) {
                    setMarked(!isMarked());

                    _fvparent->eventManager()->updateAfterEvent();
                    return;

                } else if(_is_longpress) {
                    _fvparent->onItemMenu(_fsinfo, this);
                    _is_longpress = false;
                    return;
                }
            }


            if(_fsinfo.attr & FSProtocol::FSEntryFlags::Dir) {

                if(_fsinfo.name == ".." && _fsinfo.action) {
                    _fvparent->cdUpAfterAction(std::string());
                } else {
                    _fvparent->cdUpAfterAction(_fsinfo.name);
                }
            } else {
                extensionManager().run(parentWidget()->directory() + _fsinfo.name);

            }
            _is_longpress = false;
            break;

        case TOUCH_ACTION_LONG_PRESS:
            _is_longpress = true;
            _fvparent->eventManager()->updateAfterEvent();
            break;
    }
}





/**********************************************************************************************/
/********************************* FileViewWidgetListEngine ***********************************/
/**********************************************************************************************/



FileViewWidgetListEngine::FileViewWidgetListEngine(FileViewWidget *parent) :
    FileViewWidgetEngine(parent),
    _is_blocked(false)
{

}



FileViewWidgetListEngine::~FileViewWidgetListEngine()
{
    clearItems();
}



ScrollAreaItem *FileViewWidgetListEngine::getListItem(int index)
{
    if(_is_blocked)
        return 0;

    if(index < 0) {
        printf("Warning: index must be >= 0. item: %d, index: %d\n ", fileViewParent()->item()->item, index);
        return 0;
    }

    if(index >= (int)fileSystemEntriesCount()) {
        printf("Warning: index value is bigger than have items\n ");
        return 0;
    }

    FileViewWidgetListItem *fi = 0;
    if((int)_items.size() <= index || !_items[index]) {
        int old_size = _items.size();

        if((int)_items.size() <= index)
            _items.resize(index+1);

        for(unsigned int i = old_size; i<_items.size(); ++i)
            _items[i] = 0;


        if(!_items[index]) {
            _items[index] = new FileViewWidgetListItem(fileViewParent(), fileViewParent()->rect().w(), 45, fileViewParent()->getFSEntry(index));
        }

        fi = (FileViewWidgetListItem*)_items[index];

    } else
        fi = (FileViewWidgetListItem*)_items[index];


    return fi->item();
}


void FileViewWidgetListEngine::clearItems()
{
    for(FileViewWidgetListItem * i : _items)
    {
        if(i)
            delete i;
    }

    _items.clear();
}


int  FileViewWidgetListEngine::itemBySystemEntryNumber(int n)
{
    if(n < 0 && n >= (int)fileSystemEntriesCount()) {
        return 0;
    }

    return n;
}


int  FileViewWidgetListEngine::fileSystemEntryByItem(int n)
{
    if(n < 0 && n >= (int)_items.size()) {
        return 0;
    }

    return n;
}


int FileViewWidgetListEngine::itemsForViewList()
{
    return fileSystemEntriesCount();
}


int FileViewWidgetListEngine::fsEntriesPerLine()
{
    return 1;
}


int FileViewWidgetListEngine::viewItemsCount()
{
    return _items.size();
}


void FileViewWidgetListEngine::setMarkedAll()
{
    if(_items.size() < (unsigned int)itemsForViewList())
        _items.reserve(itemsForViewList());

    for(int i=0; i<itemsForViewList(); ++i)
    {
        FileViewWidgetListItem * item = 0;

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

        if(item)
            item->setMarked(true);
    }
}


void FileViewWidgetListEngine::setUnMarkedAll()
{
    for(FileViewWidgetListItem * i : _items)
    {
        if(i)
            i->setMarked(false);
    }
}


std::list<const FSEntryInfo *> FileViewWidgetListEngine::getSelectedEntriesList()
{
    std::list<const FSEntryInfo *> list;

    for(FileViewWidgetListItem * i : _items)
    {
        if(i && i->isMarked() && !i->getSelectedEntry().action) {
            list.push_back(&i->getSelectedEntry());
        }
    }

    return list;
}


void FileViewWidgetListEngine::block()
{
    _is_blocked = true;
}


void FileViewWidgetListEngine::unblock()
{
    _is_blocked = false;
}
