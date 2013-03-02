
#include <Api/ApiLinkLib/ApiLink.h>


#include <math.h>
#include <unistd.h>
#include <fcntl.h>
#include <fs.h>
#include <loader.h>

#include "FileViewWidget.h"
#include "FileViewWidgetListEngine.h"
#include "FileViewWidgetIconEngine.h"
#include "FileViewWidgetAbstractItem.h"
#include "FSEntryInfo.h"
#include "LocalFSProtocol.h"
#include "ThreadWorker.h"


FSEntryInfo __fs_entryinfo_null_entry;


FileViewWidget::FileViewWidget(UActiveArea *parent, EffectManager *em, const Rect &r) :
    ActiveList(parent, r),
    m_itemSelectMode(false),
    m_mainViewEngine(0),
    __null_fs_entry(FSEntryInfo("=Invalid=", 0, 0)),
    m_firstHeight(r.h()),
    m_fsEntryMenu(parent, Rect(10, 60, 240-20, 280), parent->eventManager()),
    global_yes_no_question(0),
    m_needCd(false),
    global_menu(parent, Rect(0, 0, 240, 310), parent->eventManager()),
    global_menu_button(parent, Rect(0, 0, 240, 39), false),
    global_menu_showing(false),
    effect_manager(em)
{
    memset(&cd_prev_screen_image, 0, sizeof(cd_prev_screen_image));


    // TODO: restoring last dir
    m_currentWorkspaceId = 0;
    m_workspaces.push_back( Workspace(0, "local", "/") );
    m_workspaces.push_back( Workspace(1, "local", "/") );


    if(workspace().viewEngine)
        m_mainViewEngine = new FileViewWidgetIconEngine(this);
    else
        m_mainViewEngine = new FileViewWidgetListEngine(this);

    border_img = resourceManager().image("border");
    folder_icon = resourceManager().image("folder-icon");
    file_icon = resourceManager().image("file-icon");
    back_action_icon = resourceManager().image("arrow-back-icon");
    checkedbox_icon = resourceManager().image("checkedbox");
    checkbox_icon = resourceManager().image("checkbox");

    initGlobalMenu();

    global_menu_button.setHeight(border_img.h);
    global_menu_button.setWidth(border_img.w);
    global_menu_button.setBackround(&border_img);
    global_menu_button.setFullScreenBlock(false);
    global_menu_button.setBlockable(true);

    this->parent()->pushFront(&global_menu_button);


    auto event = [this](Timer *t) {

        int new_y = 0;

        if(global_menu_way == 2) {
            new_y = global_menu.rect().y()+global_menu_speed;

            if(new_y > 0) {
                t->stop();
                global_menu.move( global_menu.rect().x(), 1);
                global_menu_button.move( 0, global_menu.rect().y2() );
                eventManager()->updateAfterEvent();
                return;
            }

        } else if(global_menu_way == 1) {
            new_y = global_menu.rect().y()-global_menu_speed;

            if(new_y+global_menu.rect().h() < 0) {

                global_menu.hide();

                t->stop();
                global_menu_button.move( 0, 0 );
                global_menu.setFullScreenBlock(false);
                eventManager()->updateAfterEvent();
                return;
            }
        }

        global_menu_speed += (global_menu_speed*30)/100;
        global_menu.move( global_menu.rect().x(), new_y);
        global_menu_button.move( 0, global_menu.rect().y2() );
        eventManager()->updateAfterEvent();
    };

    m_menuTimer.timerEventSignal().connect( event );


    global_menu_button.touchActionSignal().connect( [this](GlobalMenuButton *mm, int action, int x, int y) {

        switch(action)
        {
            case TOUCH_ACTION_PRESS:

                if(mm->isOffRectTouch()) {
                    return;
                }

                if(isSelectionMode()) {
                    mark_start_stop->setText("Закончить выделение");
                } else {
                    mark_start_stop->setText("Начать выделение");
                }

                if(!global_menu_showing)
                   global_menu_first_move = true;
                else
                   global_menu_first_move = false;


                global_menu_fix_y = y - global_menu_button.rect().y();
                global_menu_last_x = x;
                global_menu_last_y = y;
                global_menu_speed = 25;

                break;

            case TOUCH_ACTION_RELEASE:
                if(!global_menu_first_move && !mm->isOffRectTouch())
                    m_menuTimer.start(5);

                if(mm->isOffRectTouch() && !mm->isMoved()) {
                    global_menu.hide();
                    return;
                }


                break;

            case TOUCH_ACTION_MOVE:
                if(!mm->isTouched() || mm->isOffRectTouch())
                    return;

                if(global_menu_first_move) {
                    stopScroll();
                    global_menu.resetViewListPosition();
                    global_menu.show();
                    global_menu.setFullScreenBlock(false);
                    global_menu_button.setFullScreenBlock(true);
                    global_menu_showing = true;

                    fixScrollPosition();
                    global_menu_first_move = false;


                }

                if(global_menu_last_y > y) { // UP
                    global_menu_way = 1;
                } else {    // Down
                    global_menu_way = 2;
                }

                global_menu_last_x = x;
                global_menu_last_y = y;



                global_menu.move( global_menu.rect().x(), (y-global_menu_fix_y)-global_menu.rect().h() );
                if(global_menu.rect().y() > 0)
                    global_menu.moveY(1);

                global_menu_button.move( 0, global_menu.rect().y2() );
                eventManager()->updateAfterEvent();
                break;
        }

    });


    global_menu.onHideSignal().connect( [this](ListMenu *) {
        m_menuTimer.stop();

        global_menu_button.setFullScreenBlock(false);
        global_menu_button.move( 0, 0 );

        global_menu_showing = false;
        eventManager()->updateAfterEvent();
    });


}


FileViewWidget::~FileViewWidget()
{
    clearFSEntries();
    setViewList();
    clearItems();

    if(cd_prev_screen_image.bitmap)
        free(cd_prev_screen_image.bitmap);
    cd_prev_screen_image.bitmap = 0;


    for(ActiveListItem *i : *m_fsEntryMenu.itemList()) {
        delete i;
    }

    for(ActiveListItem *i : *global_menu.itemList()) {
        delete i;
    }
    global_menu.itemList()->clear();

    if(global_yes_no_question) {
        global_yes_no_question->hide();
        delete global_yes_no_question;
    }

    delete m_mainViewEngine;
}


void FileViewWidget::initGlobalMenu()
{
    /* init menu */
    ListMenuItem *mi;

    global_menu.setFullScreenBlock(true);
    global_menu.style().setShadow(Brush());


    global_menu.pushBack( mi = new ListMenuItem(&global_menu, global_menu.rect().w(), 40, "Назад..."));
    mi->onReleasedSignal().connect( [this](ListMenuItem *) {
        global_menu.hide();
        cdDown();
    } );

    global_menu.pushBack( mi = new ListMenuItem(&global_menu, global_menu.rect().w(), 40, "В начало"));
    mi->onReleasedSignal().connect( [this](ListMenuItem *) {
        global_menu.hide();
        resetViewListPosition();
        setViewListScrollCoordinateY(rect().x2());
        fixScrollPosition();
    } );

    global_menu.pushBack( mi = new ListMenuItem(&global_menu, global_menu.rect().w(), 40, "В конец"));
    mi->onReleasedSignal().connect( [this](ListMenuItem *) {
        global_menu.hide();
        resetViewListPosition();
        setLineItem(linesCount()-1);
        fixScrollPosition();
    } );


    global_menu.pushBack( mi = new ListMenuItem(&global_menu, global_menu.rect().w(), 40, "Обновить"));
    mi->onReleasedSignal().connect( [this](ListMenuItem *) {
        global_menu.hide();
        refreshDir();
        eventManager()->updateAfterEvent();
    } );

    global_menu.pushBack( mi = new ListMenuItem(&global_menu, global_menu.rect().w(), 40, "Вставить"));
    mi->onReleasedSignal().connect( [this](ListMenuItem *) {
        global_menu.hide();

        paste(directory());
        refreshDir();
        eventManager()->updateAfterEvent();
    } );

    global_menu.pushBack( mi = new ListMenuItem(&global_menu, global_menu.rect().w(), 40, "Сменить папку"));
    mi->onReleasedSignal().connect( [this](ListMenuItem *) {
        global_menu.hide();
        switchNextWorkSpace();
    } );

    global_menu.pushBack( mi = new ListMenuItem(&global_menu, global_menu.rect().w(), 40, "Сменить вид"));
    mi->onReleasedSignal().connect( [this](ListMenuItem *) {
        global_menu.hide();
        switchViewType();
    } );


    global_menu.pushBack( mark_start_stop = mi = new ListMenuItem(&global_menu, global_menu.rect().w(), 40, "Начать выделение"));
    mi->onReleasedSignal().connect( [this](ListMenuItem *) {
        setSelectMode(!isSelectionMode());

        if(isSelectionMode())
            unMarkAllFiles();

        global_menu.hide();
        eventManager()->updateAfterEvent();
    } );

    global_menu.pushBack( mi = new ListMenuItem(&global_menu, global_menu.rect().w(), 40, "Информация"));
    mi->style().setLineText(0xffa3a3a3);

    global_menu.pushBack( mi = new ListMenuItem(&global_menu, global_menu.rect().w(), 40, "Выход..."));
    mi->onReleasedSignal().connect( [this](ListMenuItem *) {
        m_exitSignal.trigger(this);
    } );


    global_menu.onHideSignal().connect( [this](ListMenu *){
        eventManager()->updateAfterEvent();
    });

    global_menu.setLinesCount(global_menu.itemList()->size());
}


ScrollAreaItem *FileViewWidget::getListItem(int index)
{
    return m_mainViewEngine->getListItem(index);
}


void FileViewWidget::pushBackFile(FSEntryInfo *info)
{
    pushBackFile(*info);
}


void FileViewWidget::pushBackFile(const FSEntryInfo &info)
{
    if(info.attr & FSProtocol::FSEntryFlags::Dir) {
        m_DirsList.push_back(info);
    } else {
        m_FilesList.push_back(info);
    }
}


void FileViewWidget::setViewList()
{
    setLinesCount(m_mainViewEngine->itemsForViewList());
}


void FileViewWidget::clearItems()
{
    m_mainViewEngine->clearItems();
}


std::list <const FSEntryInfo *> FileViewWidget::getSelectedEntriesList()
{
    return m_mainViewEngine->getSelectedEntriesList();
}


void FileViewWidget::clearScreen()
{
    //fullResetViewList();
    clearFSEntries();
    clearItems();
}


void FileViewWidget::paintEvent()
{
    glSetPen(0xFF0F0000);
    glDrawFilledRectange(0, /*border->h*/0, rect().w(), rect().y2());

    glSaveClipRegion();
    glSetClipRegion(0, 30, rect().w(), rect().y2());

    moveY( border_img.h );
    setHeight( m_firstHeight - border_img.h );

    ActiveList::paintEvent();
    glRestoreClipRegion();

    int cline = lineItem()+1;
    int entries = fsEntriesCount();
    int dirs = viewDirsCount();


    if(1) {
        cline = (cline-1)*m_mainViewEngine->fsEntriesPerLine();
        cline++;
    }

    if(dirs > 0) {
        if(m_DirsList[0].action) {
            --dirs;
            --entries;

            if(cline > 1)
                --cline;
        }
    }


    global_menu_button.setDirecory(directory());
    global_menu_button.setDirectoriesCount(dirs);
    global_menu_button.setFilesCount(viewFilesCount());
    global_menu_button.setCurrentLine(cline);
    global_menu_button.setViewLines(entries);
    global_menu_button.setWorkspace(workspace().id);

    global_menu_button.paintEvent();
}


void FileViewWidget::touchEvent(int action, int x, int y)
{
    ActiveList::touchEvent(action, x, y);

    if(m_needCd) {

        if(m_cdLaterTo.empty()) {
            cdDown();

        } else {
            cdUp(m_cdLaterTo);
            m_cdLaterTo.clear();
        }

        eventManager()->updateAfterEvent();
    }
}


int FileViewWidget::refreshDir(bool fix_scroll)
{
    int linei = lineItem();
    clearScreen();
    fillEntries();
    setViewList();

    if(linei >= linesCount())
        linei = linesCount()-1;

    setLineItem(linei);

    if(fix_scroll)
        fixScrollPosition();
    return 0;
}


int FileViewWidget::cdUp(const std::string &dir, bool effect)
{
    if(isSelectionMode()) {
        setSelectMode(false);
    }

    m_needCd = false;
    if(effect)
        cdEffectPrepare();

    setDirectory(dir == "/"? dir : directory()+dir);
    refreshDir();

    if(effect)
        cdEffectStart(EFFECT_SUB_ALPHA);
    return 0;
}


int FileViewWidget::cdDown()
{
    if(isSelectionMode()) {
        setSelectMode(false);
    }

    m_needCd = false;
    if(directory() == "/")
        return -1;

    cdEffectPrepare();

    std::string new_dir = directory();

    auto p = new_dir.find_last_of('/', new_dir.length()-2);
    new_dir = new_dir.assign(new_dir.begin(), new_dir.begin()+p+1);

    setDirectory(new_dir);
    refreshDir();

    cdEffectStart(EFFECT_ADD_ALPHA);
    return 0;
}


int FileViewWidget::cdUpAfterAction(const std::string &dir)
{
    m_needCd = true;
    m_cdLaterTo = dir;
    return 0;
}


int FileViewWidget::fillEntries()
{
    auto push_item = [this](const std::string & name, int attr, unsigned long size, bool action) {
        pushBackFile(FSEntryInfo(name, attr, size, action));
    };

    FSProtocol & proto = protocolsContainer().indexOf( workspace().protocol );

    const std::string & path = directory();

    if(path == "/") {

        const char *names[4] = {"usr/", "sys/", "mmc/", "cus/"};

        for(int i=0; i<4; ++i) {
            push_item(names[i], FSProtocol::FSEntryFlags::Dir, 0, false);
        }
        return 0;
    } else {

        void *h = proto.opendir(path.c_str(), "*.*");

        if(h) {
            FSProtocol::FSEntry entry;
            int i = 0;

            while(!proto.readdir(h, &entry)) {

                if(i == 0 && entry.name ==  ".") {
                    continue;
                }

                if(i == 0 && entry.name !=  "..") {
                    push_item("..", FSProtocol::FSEntryFlags::Dir, 0, true);
                    ++i;
                }

                if(entry.name ==  "..") {
                    push_item(entry.name, entry.flags, 0, true);

                } else {
                    if(entry.flags & FSProtocol::FSEntryFlags::Dir) {
                        push_item(entry.name + "/", entry.flags, 0, false);
                    } else {
                        push_item(entry.name, entry.flags, entry.size, false);
                    }
                }

                ++i;

                if(i > 10000) {
                    printf("That is fucking bug in firmware?\n");
                    break;
                }

            }

            if(!i) {
                push_item("..", FSProtocol::FSEntryFlags::Dir, 0, true);
            }

            proto.closedir(h);
        } else {
            push_item("..", FSProtocol::FSEntryFlags::Dir, 0, true);
        }
    }

    return 0;
}


void FileViewWidget::cdEffectPrepare(bool paint_fresh_screen)
{
    /* останавливаем эффект */
    cdEffectStop();

    /* ресетим прорисовочный флаг */
    eventManager()->resetUpdate();

    /* прорисовываем чистый старый экран */
    if(paint_fresh_screen)
        eventManager()->paint();

    /* сохраняем в битмап */
    GLContext *ctx = glActiveContext();
    int sz = ctx->width *ctx->height *(ctx->depth/8);

    if(cd_prev_screen_image.bitmap)
        free(cd_prev_screen_image.bitmap);

    cd_prev_screen_image.bitmap = malloc(sz);
    cd_prev_screen_image.w = ctx->width;
    cd_prev_screen_image.h = ctx->height;
    cd_prev_screen_image.bit = ctx->depth;
    memcpy(cd_prev_screen_image.bitmap, &glGetPixel16(ctx, 0, 0), sz);

    /* толкаем в еффект менеджер */
    effect_manager->pushPrevScreen(cd_prev_screen_image);
}


void FileViewWidget::cdEffectStart(int effect, int delay)
{
    effect_manager->start(effect, delay);
}



void FileViewWidget::cdEffectStop()
{
    effect_manager->stop();
}


void FileViewWidget::setViewEngine(int id)
{
    int fs_entry = m_mainViewEngine->fileSystemEntryByItem(lineItem());

    fullResetViewList();
    clearItems();

    workspace().viewEngine = id;

    delete m_mainViewEngine;

    if(workspace().viewEngine) {
        m_mainViewEngine = new FileViewWidgetIconEngine(this);
    } else {
        m_mainViewEngine = new FileViewWidgetListEngine(this);
    }

    setViewList();
    setLineItem( m_mainViewEngine->itemBySystemEntryNumber(fs_entry) );
}


void FileViewWidget::switchViewType()
{
    cdEffectPrepare();

    setViewEngine(!workspace().viewEngine);
    fixScrollPosition();

    cdEffectStart(EFFECT_RIGHT_SCALE);
}


const std::string FileViewWidget::sizeToString(unsigned long bytes) const
{
    char size[128];

    /*if(bytes >= (1024*1024*1024*1024)) {
        sprintf(size, "%d Тиб", bytes / (1024 * 1024 * 1024 * 1024));

    } else */if(bytes >= (1024*1024*1024)) {
        sprintf(size, "%.02f Гиб", (float)bytes / (1024 * 1024 * 1024));

    } else if(bytes >= (1024*1024)) {
        sprintf(size, "%.02f Миб", (float)bytes / (1024 * 1024));

    } else if(bytes >= (1024)) {
        sprintf(size, "%.02f Киб", (float)bytes / (1024));

    } else {
        sprintf(size, "%lu Байт", bytes);
    }

    return size;
}


void FileViewWidget::unMarkAllFiles()
{
    m_mainViewEngine->setUnMarkedAll();
}


void FileViewWidget::markAllFiles()
{
    m_mainViewEngine->setMarkedAll();
}


void FileViewWidget::pushFileToClipBoard(const std::string &dir, const FSListedEntry &info, ClipBoard::Action type)
{
    m_clipboard.pushFile(workspace().protocol, dir, info, type);
}


void FileViewWidget::switchNextWorkSpace()
{
    unsigned int id = m_currentWorkspaceId+1;
    if(workspaces().size() <= id)
        id = 0;

    switchWorkSpace(id);
}


bool FileViewWidget::switchWorkSpace(unsigned int id)
{
    if(id >= workspaces().size())
        return false;

    bool bigger = false;

    stopScroll();

    /* save scroll state */
    workspace().scrollState = scrollState();

    cdEffectPrepare();

    if(m_currentWorkspaceId < id)
        bigger = true;

    m_currentWorkspaceId = id;

    /*  */
    clearScreen();
    fillEntries();
    setViewEngine( workspace().viewEngine );
    setViewList();

    /* restore scroll state */
    setScrollState( workspace().scrollState );

    if(bigger) {
        cdEffectStart(EFFECT_LEFT_MOVE);
    } else {
        cdEffectStart(EFFECT_RIGHT_MOVE);
    }

    return true;
}


/*
void FileViewWidget::paste(const std::string &to_dir)
*/


/*
int FileViewWidget::unlinkFiles(const std::list<const FSEntryInfo *> & list)
*/
