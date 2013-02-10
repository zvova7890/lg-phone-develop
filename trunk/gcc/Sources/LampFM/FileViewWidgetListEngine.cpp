
#include "FileViewWidget.h"
#include "FileViewWidgetListEngine.h"
#include "main.h"
#include <fs.h>



/**********************************************************************************************/
/********************************** FileViewWidgetListItem ************************************/
/**********************************************************************************************/


FileViewWidgetListItem::FileViewWidgetListItem(FileViewWidget *parent, int w, int h, const FSEntryInfo & entry) :
    FileViewWidgetAbstractItem(parent, w, h),
    _is_longpress(false),
    _fsinfo(entry)
{
}


FileViewWidgetListItem::~FileViewWidgetListItem()
{

}


void FileViewWidgetListItem::paintEvent()
{
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

    if(currentDisplayID() == (int)_fvparent->viewItemsCount()-1)
        glDrawHLine(x, x+rect().w(), y + x+rect().h());


    int x_offset = 4;

    if(!_fsinfo.action) {

        if(_fsinfo.attr & FS_ATTR_FOLDER) {

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

    if(!_fsinfo.name.empty()) {
        glSetPen(0xFFFFFFFF);
        glDrawString(_fsinfo.name.c_str(), x_offset+x, y+4, x_offset+x+rect().w(), y+(rect().h()/2 + 14/2 ), 20, FT_TEXT_H_CENTER, 0, 56);


        char ext[128];
        if(_fsinfo.attr & FS_ATTR_FOLDER) {

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

            if(_is_longpress && !_fsinfo.action && _fsinfo.name != "..") {
                _fvparent->onItemMenu(_fsinfo, (UActiveAreaItem<ActiveAreaItem>*)this);
                _is_longpress = false;
                return;
            }


            if(_fsinfo.attr & FS_ATTR_FOLDER) {

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
            _fvparent->event_mngr->updateAfterEvent();
            break;
    }
}





/**********************************************************************************************/
/********************************* FileViewWidgetListEngine ***********************************/
/**********************************************************************************************/



FileViewWidgetListEngine::FileViewWidgetListEngine(FileViewWidget *parent) :
    FileViewWidgetEngine(parent)
{
    event_mngr = &eventManager();
}



FileViewWidgetListEngine::~FileViewWidgetListEngine()
{
    clearItems();
}



ScrollAreaItem *FileViewWidgetListEngine::getListItem(int index)
{
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
