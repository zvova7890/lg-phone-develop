
#include "FileViewWidget.h"
#include "FileViewWidgetListEngine.h"
#include "main.h"
#include <fs.h>



/**********************************************************************************************/
/********************************** FileViewWidgetListItem ************************************/
/**********************************************************************************************/


FileViewWidgetListItem::FileViewWidgetListItem(FileViewWidget *parent, int w, int h, const FSEntryInfo & entry) :
    FileViewWidgetAbstractItem(parent),
    Widget(Rect(Point(), Point(w, h)), parent),
    _is_longpress(false),
    _fsinfo(entry)
{
    m_notFile = _fsinfo.action;
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
    if(!m_widgetParent->isSelectionMode())
        setMarked(false);

    int x = realRect().x();
    int y = realRect().y();

    if(isTouched() && !isMoved()) {

        if(_is_longpress) {
            glSetPen(0x4FFF00FF);
        } else
            glSetPen(0x4FFF0000);
        glDrawFilledRectange(x, y, x+rect().w(), y + x+rect().h());
    }

    glSetPen(0xFF332828);
    glDrawHLine(x, x+rect().w(), y);

    if(Widget::id() == (int)m_widgetParent->viewItemsCount()-1)
        glDrawHLine(x, x+rect().w(), y + x+rect().h());


    int x_offset = 4;

    if(!_fsinfo.action) {

        if(_fsinfo.attr & FSProtocol::FSEntryFlags::Dir) {

            Image *img = &m_widgetParent->folder_icon;

            if(!img->isEmpty()) {
                drawImage(x+1, y+2, img);
                x_offset += img->width();
            }
        } else {
            Image *img = &m_widgetParent->file_icon;

            if(!img->isEmpty()) {
                drawImage(x+1, y+2, img);
                x_offset += img->width();
            }
        }
    } else {
        //image_t *img = &_fvparent->back_action_icon;

        /*if(img->bitmap) {
            drawImage(x+1, y+2, img);
            x_offset += img->w;
        }*/
    }


    if(m_widgetParent->isSelectionMode() && !_fsinfo.action && _fsinfo.name != "..") {
        if( !isMarked() && !m_widgetParent->checkbox_icon.isEmpty())
        {
            drawImage(x+1, realRect().y2()-m_widgetParent->checkbox_icon.height(), &m_widgetParent->checkbox_icon);
            if(x_offset < m_widgetParent->checkbox_icon.width())
                x_offset = m_widgetParent->checkbox_icon.width()+2;
        }

        if( isMarked() && !m_widgetParent->checkedbox_icon.isEmpty() )
        {
            drawImage(x+1, realRect().y2()-m_widgetParent->checkedbox_icon.height(), &m_widgetParent->checkedbox_icon);
            if(x_offset < m_widgetParent->checkedbox_icon.width())
                x_offset = m_widgetParent->checkedbox_icon.width()+2;
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
            sprintf(ext, "%s, 0", m_widgetParent->sizeToString(_fsinfo.size).c_str());
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

                if(m_widgetParent->isSelectionMode() && !_is_longpress) {
                    setMarked(!isMarked());

                    m_widgetParent->eventManager()->updateAfterEvent();
                    return;

                } else if(_is_longpress) {
                    m_widgetParent->onItemMenu(_fsinfo, this);
                    _is_longpress = false;
                    return;
                }
            }


            if(_fsinfo.attr & FSProtocol::FSEntryFlags::Dir) {

                if(_fsinfo.name == ".." && _fsinfo.action) {
                    m_widgetParent->cdUpAfterAction(std::string());
                } else {
                    m_widgetParent->cdUpAfterAction(_fsinfo.name);
                }
            } else {
                extensionManager().run(parentWidget()->directory() + _fsinfo.name);

            }
            _is_longpress = false;
            break;

        case TOUCH_ACTION_LONGPRESS:
            _is_longpress = true;
            m_widgetParent->eventManager()->updateAfterEvent();
            break;
    }
}





/**********************************************************************************************/
/********************************* FileViewWidgetListEngine ***********************************/
/**********************************************************************************************/



FileViewWidgetListEngine::FileViewWidgetListEngine(FileViewWidget *parent) :
    FileViewWidgetEngine(parent),
    m_isBlocked(false)
{

}



FileViewWidgetListEngine::~FileViewWidgetListEngine()
{
    clearItems();
}



Widget *FileViewWidgetListEngine::getListItem(int index)
{
    if(m_isBlocked)
        return 0;

    if(index < 0) {
        printf("Warning: index must be >= 0. item: %d, index: %d\n ", fileViewParent()->fileViewArea().item(), index);
        return 0;
    }

    if(index >= (int)fileSystemEntriesCount()) {
        printf("Warning: index value is bigger than have items\n ");
        return 0;
    }

    if(!m_fullHeight) {
        m_fullHeight = fileSystemEntriesCount() * 45;
    }

    FileViewWidgetListItem *fi = 0;
    if((int)m_items.size() <= index || !m_items[index]) {
        int old_size = m_items.size();

        if((int)m_items.size() <= index)
            m_items.resize(index+1);

        for(unsigned int i = old_size; i<m_items.size(); ++i)
            m_items[i] = 0;


        if(!m_items[index]) {
            m_items[index] = new FileViewWidgetListItem(fileViewParent(), fileViewParent()->rect().w(), 45, fileViewParent()->getFSEntry(index));
        }

        fi = (FileViewWidgetListItem*)m_items[index];

    } else
        fi = (FileViewWidgetListItem*)m_items[index];


    return fi;
}


void FileViewWidgetListEngine::clearItems()
{
    for(FileViewWidgetListItem * i : m_items)
    {
        if(i)
            delete i;
    }

    m_items.clear();
    m_fullHeight = 0;
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
    if(n < 0 && n >= (int)m_items.size()) {
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
    return m_items.size();
}


void FileViewWidgetListEngine::setMarkedAll()
{
    if(m_items.size() < (unsigned int)itemsForViewList())
        m_items.reserve(itemsForViewList());

    for(int i=0; i<itemsForViewList(); ++i)
    {
        FileViewWidgetListItem * item = 0;

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

        if(item)
            item->setMarked(true);
    }
}


void FileViewWidgetListEngine::setUnMarkedAll()
{
    for(FileViewWidgetListItem * i : m_items)
    {
        if(i)
            i->setMarked(false);
    }
}


std::list<const FSEntryInfo *> FileViewWidgetListEngine::getSelectedEntriesList()
{
    std::list<const FSEntryInfo *> list;

    for(FileViewWidgetListItem * i : m_items)
    {
        if(i && i->isMarked() && !i->getSelectedEntry().action) {
            list.push_back(&i->getSelectedEntry());
        }
    }

    return list;
}


void FileViewWidgetListEngine::block()
{
    m_isBlocked = true;
}


void FileViewWidgetListEngine::unblock()
{
    m_isBlocked = false;
}


int FileViewWidgetListEngine::fullListHeight() const
{
    return m_fullHeight;
}
