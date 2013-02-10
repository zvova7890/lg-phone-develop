
#include <math.h>
#include <fs.h>
#include <loader.h>
#include "FileViewWidget.h"
#include "FileViewWidgetListEngine.h"
#include "FileViewWidgetIconEngine.h"




FileViewWidget::FileViewWidget(UActiveArea *parent, EffectManager *em, const Rect &r, EventManager *e) :
    ActiveList(r, e),
    _item_select_mode(false),
    curent_engine(0),
    _main_view_engine(0),
    __null_fs_entry(FSEntryInfo("=Invalid=", 0, 0)),
    _first_height(r.h()),
    _fsentry_menu(parent, Rect(20, 60, 200, 280), event_mngr),
    __current_dir("/"),
    need_cd(false),
    effect_manager(em),
    _parent_area(parent),
    global_menu(parent, Rect(10, 0, 240, 310), e),
    global_menu_button(e, Rect(0, 0, 36, 38))
{
    memset(&cd_prev_screen_image, 0, sizeof(cd_prev_screen_image));

    if(curent_engine)
        _main_view_engine = new FileViewWidgetIconEngine(this);
    else
        _main_view_engine = new FileViewWidgetListEngine(this);

    border_img = getBorderImage();
    folder_icon = getFolderIcon();
    file_icon = getFileIcon();
    back_action_icon = getBackActionIcon();

    initGlobalMenu();

    global_menu_button.setHeight(border_img.h);
    global_menu_button.setWidth(border_img.w);
    _parent_area->pushFront(&global_menu_button);


    auto event = [](TimerWrap *tt, void *u) {
        auto self = (FileViewWidget*)u;

        int new_y = 0;

        if(self->global_menu_way == 2) {
            new_y = self->global_menu.rect().y()+self->global_menu_speed;

            if(new_y > self->border_img.h) {
                TimerStop(tt);
                self->global_menu.move( self->border_img.w/2 - self->global_menu.rect().w()/2,
                                        self->border_img.h);
                self->event_mngr->updateAfterEvent();
                return;
            }

        } else if(self->global_menu_way == 1) {
            new_y = self->global_menu.rect().y()-self->global_menu_speed;

            if(new_y+self->global_menu.rect().h() < 0) {
                self->_parent_area->pop(&self->global_menu);
                TimerStop(tt);
                self->event_mngr->updateAfterEvent();
                return;
            }
        }

        self->global_menu_speed += (self->global_menu_speed*25)/100;
        self->global_menu.move( self->border_img.w/2 - self->global_menu.rect().w()/2, new_y);
        self->event_mngr->updateAfterEvent();
    };

    TimerCreate(&global_menu_timer, 1, event, this);



    global_menu_button.connectTouchAction( [this](GlobalMenuButton *, int action, int x, int y) {

        switch(action)
        {
            case TOUCH_ACTION_PRESS:
                global_menu_first_move = true;
                global_menu_last_x = x;
                global_menu_last_y = y;
                global_menu_speed = 15;
                break;

            case TOUCH_ACTION_RELEASE:

                TimerStart(&global_menu_timer, 5);

                break;

            case TOUCH_ACTION_MOVE:
                if(global_menu_first_move) {
                    stopScroll();
                    global_menu.resetViewListPosition();
                    _parent_area->pushFront(&global_menu);
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

                global_menu.move( border_img.w/2 - global_menu.rect().w()/2, y-global_menu.rect().h() );
                event_mngr->updateAfterEvent();
                break;
        }

    });

    /*global_menu_button.connectReleased( [this](UButton *) {
        stopScroll();
        _parent_area->pushFront(&global_menu);
        fixScrollPosition();
        event_mngr->updateAfterEvent();
    });*/
}


FileViewWidget::~FileViewWidget()
{
    TimerDestroy(&global_menu_timer);

    clearFSEntries();
    setViewList();
    clearItems();

    if(cd_prev_screen_image.bitmap)
        free(cd_prev_screen_image.bitmap);
    cd_prev_screen_image.bitmap = 0;


    for(ActiveListItem *i : *_fsentry_menu.itemList()) {
        delete i;
    }

    for(ActiveListItem *i : *global_menu.itemList()) {
        delete i;
    }
    global_menu.itemList()->clear();

    delete _main_view_engine;
}


void FileViewWidget::initGlobalMenu()
{
    /* init menu */
    GlobalMenuItem *mi;

    global_menu.setFullScreenBlock(true);


    global_menu.pushBack( mi = new GlobalMenuItem(&global_menu, global_menu.rect().w(), 40, "Назад..."));
    mi->connectReleasedSignal( [this](ListMenuItem *) {
        _parent_area->pop(&global_menu);
        cdDown();
    } );

    global_menu.pushBack( mi = new GlobalMenuItem(&global_menu, global_menu.rect().w(), 40, "В начало"));
    mi->connectReleasedSignal( [this](ListMenuItem *) {
        _parent_area->pop(&global_menu);
        resetViewListPosition();
        setViewListScrollCoordinateY(rect().x2());
        fixScrollPosition();
    } );

    global_menu.pushBack( mi = new GlobalMenuItem(&global_menu, global_menu.rect().w(), 40, "В конец"));
    mi->connectReleasedSignal( [this](ListMenuItem *) {
        _parent_area->pop(&global_menu);
        resetViewListPosition();
        setLineItem(linesCount()-1);
        fixScrollPosition();
    } );

    global_menu.pushBack( mi = new GlobalMenuItem(&global_menu, global_menu.rect().w(), 40, "Сменить вид"));
    mi->connectReleasedSignal( [this](ListMenuItem *) {
        _parent_area->pop(&global_menu);
        switchViewType();
    } );


    global_menu.pushBack(new GlobalMenuItem(&global_menu, global_menu.rect().w(), 40, "Удалить все..."));
    global_menu.pushBack(new GlobalMenuItem(&global_menu, global_menu.rect().w(), 40, "Выделить"));
    global_menu.pushBack(new GlobalMenuItem(&global_menu, global_menu.rect().w(), 40, "Информация..."));

    global_menu.pushBack( mi = new GlobalMenuItem(&global_menu, global_menu.rect().w(), 40, "Выход..."));
    mi->connectReleasedSignal( [this](ListMenuItem *) {
        __exit_signal.emit(this);
    } );


    global_menu.connectOnHideSignal( [this](ListMenu *){
        event_mngr->updateAfterEvent();
    });

    global_menu.setLinesCount(global_menu.itemList()->size());
}


ScrollAreaItem *FileViewWidget::getListItem(int index)
{
    return _main_view_engine->getListItem(index);
}


void FileViewWidget::pushBackFile(FSEntryInfo *info)
{
    pushBackFile(*info);
}


void FileViewWidget::pushBackFile(const FSEntryInfo &info)
{
    if(info.attr & FS_ATTR_FOLDER) {
        _dir_fs_entrys.push_back(info);
    } else {
        _file_fs_entrys.push_back(info);
    }
}


void FileViewWidget::setViewList()
{
    setLinesCount(_main_view_engine->itemsForViewList());
}


void FileViewWidget::clearItems()
{
    _main_view_engine->clearItems();
}


void FileViewWidget::clearScreen()
{
    fullResetViewList();
    clearFSEntries();
    clearItems();
}


void FileViewWidget::setViewEngine(FileViewWidgetEngine *engine)
{
    ((void)engine);
    /* WRITE ME */
}


void FileViewWidget::paintEvent()
{
    glSetPen(0xFF0F0000);
    glDrawFilledRectange(0, /*border->h*/0, rect().w(), rect().y2());

    glSaveClipRegion();
    glSetClipRegion(0, 30, rect().w(), rect().y2());

    moveY( border_img.h );
    setHeight( _first_height - border_img.h );

    ActiveList::paintEvent();
    glRestoreClipRegion();

    drawImage(0, 0, &border_img);

    glSetPen(0xFFFFFFFF);
    glDrawString(directory().c_str(), 2, 2, rect().w(), 35, 15, FT_TEXT_H_UP, 0, 100500);

    char extra_info[128];


    int cline = lineItem()+1;
    int entries = fsEntriesCount();
    int dirs = viewDirsCount();



    if(1) {
        cline = (cline-1)*_main_view_engine->fsEntriesPerLine();
        cline++;
    }

    if(dirs > 0) {
        if(_dir_fs_entrys[0].action) {
            --dirs;
            --entries;

            if(cline > 1)
                --cline;
        }
    }



    sprintf(extra_info, "Files: %d Dirs: %d", viewFilesCount(), dirs);
    glDrawString(extra_info, 2, 2, rect().w(), 35-2, 13, FT_TEXT_H_DOWN, 0, 100500);

    sprintf(extra_info, "%d/%d", cline, entries);
    glDrawString(extra_info, 2, 2, rect().w()-1, 35-2, 13, FT_TEXT_H_DOWN | FT_TEXT_W_RIGHT, 0, 100500);

    global_menu_button.paintEvent();
}


void FileViewWidget::touchEvent(int action, int x, int y)
{
    ActiveList::touchEvent(action, x, y);

    if(need_cd) {

        if(__cd_to.empty()) {
            cdDown();

        } else {
            cdUp(__cd_to);
            __cd_to.clear();
        }

        event_mngr->updateAfterEvent();
    }
}


int FileViewWidget::cdUp(const std::string &dir, bool effect)
{
    need_cd = false;
    if(effect)
        cdEffectPrepare();

    clearScreen();

    setDirectory(dir == "/"? dir : directory()+dir);

    fillEntrys();

    setViewList();

    if(effect)
        cdEffectStart(EFFECT_SUB_ALPHA);
    return 0;
}


int FileViewWidget::cdDown()
{
    need_cd = false;
    if(directory() == "/")
        return -1;

    cdEffectPrepare();

    clearScreen();

    std::string new_dir = directory();

    auto p = new_dir.find_last_of('/', new_dir.length()-2);
    new_dir = new_dir.assign(new_dir.begin(), new_dir.begin()+p+1);

    setDirectory(new_dir);

    fillEntrys();

    setViewList();

    cdEffectStart(EFFECT_ADD_ALPHA);
    return 0;
}


int FileViewWidget::cdUpAfterAction(const std::string &dir)
{
    need_cd = true;
    __cd_to = dir;
    return 0;
}


int FileViewWidget::fillEntrys()
{
    auto push_item = [this](const std::string & name, int attr, unsigned long size, bool action) {
        pushBackFile(FSEntryInfo(name, attr, size, action));
    };

    const std::string & path = __current_dir;

    if(path == "/") {

        const char *names[4] = {"usr/", "sys/", "mmc/", "cus/"};

        for(int i=0; i<4; ++i) {
            push_item(names[i], FS_ATTR_FOLDER, 0, false);
        }
        return 0;
    } else {

        auto h = fs_opendir(path.c_str());
        //printf("fs_opendir: %X - %s\n", h, path.c_str());

        if(h > 0) {
            FS_INFO entry;
            int i = 0;

            while(!fs_readdir(h, &entry)) {

                if(i == 0 && !strcmp(entry.name, ".")) {
                    continue;
                }

                if(i == 0 && strcmp(entry.name, "..")) {
                    push_item("..", FS_ATTR_FOLDER, 0, true);
                    ++i;
                }

                if(!strcmp(entry.name, "..")) {
                    push_item(entry.name, entry.attr, 0, true);

                } else {
                    if(entry.attr & FS_ATTR_FOLDER) {
                        push_item(std::string(entry.name) + "/", entry.attr, 0, false);
                    } else {
                        push_item(entry.name, entry.attr, entry.size, false);
                    }
                }

                ++i;

                if(i > 10000) {
                    printf("That is fucking bug in firmware?\n");
                    break;
                }

            }

            if(!i) {
                push_item("..", FS_ATTR_FOLDER, 0, true);
            }

            fs_closedir(h);
        } else {
            push_item("..", FS_ATTR_FOLDER, 0, true);
        }
    }

    return 0;
}


void FileViewWidget::cdEffectPrepare(bool paint_fresh_screen)
{
    /* останавливаем эффект */
    cdEffectStop();

    /* ресетим прорисовочный флаг */
    event_mngr->resetUpdate();

    /* прорисовываем чистый старый экран */
    if(paint_fresh_screen)
        event_mngr->paint();

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


void FileViewWidget::switchViewType()
{
    cdEffectPrepare();
    int fs_entry = _main_view_engine->fileSystemEntryByItem(lineItem());

    fullResetViewList();
    clearItems();

    curent_engine = !curent_engine;

    delete _main_view_engine;

    if(curent_engine) {
        _main_view_engine = new FileViewWidgetIconEngine(this);
    } else {
        _main_view_engine = new FileViewWidgetListEngine(this);
    }

    setViewList();
    setLineItem( _main_view_engine->itemBySystemEntryNumber(fs_entry) );

    fixScrollPosition();

    cdEffectStart(EFFECT_RIGHT_SCALE);
}


const std::string FileViewWidget::sizeToString(unsigned long bytes) const
{
    char ololo[128];

    /*if(bytes >= (1024*1024*1024*1024)) {
        sprintf(ololo, "%d Тиб", bytes / (1024 * 1024 * 1024 * 1024));

    } else */if(bytes >= (1024*1024*1024)) {
        sprintf(ololo, "%.02f Гиб", (float)bytes / (1024 * 1024 * 1024));

    } else if(bytes >= (1024*1024)) {
        sprintf(ololo, "%.02f Миб", (float)bytes / (1024 * 1024));

    } else if(bytes >= (1024)) {
        sprintf(ololo, "%.02f Киб", (float)bytes / (1024));

    } else {
        sprintf(ololo, "%lu Байт", bytes);
    }

    return ololo;
}



void FileViewWidget::onItemMenu(const FSEntryInfo &f, UActiveAreaItem<ActiveAreaItem> *l)
{
    ((void)l);

    /*
    for(ActiveListItem *i : *_fsentry_menu.itemList()) {
        delete i;
    }
    _fsentry_menu.itemList()->clear();
    _fsentry_menu.resetViewListPosition();
    _fsentry_menu.setLinesCount(0);*/

    _fsentry_menu.setFSEntryInfo(f);
    _fsentry_menu.setFullScreenBlock(true);
    _fsentry_menu.setBackgroundColor(0xBF900000);
    _fsentry_menu.setItemLineColor(0x4FFFFFFF);
    _fsentry_menu.setItemTextColor(0xFFFFFFFF);
    _fsentry_menu.setPressedLineColor(0x4F00FF00);

    FSEntryMenuItem *it = 0;
    _fsentry_menu.pushBack( (it = new FSEntryMenuItem(&_fsentry_menu, _fsentry_menu.rect().w(), 40, "Открыть...")) );
    it->connectReleasedSignal( [this](ListMenuItem *i) {

        FSEntryMenu *mi = (FSEntryMenu *)i->parent();
        _fsentry_menu.hide();

        if(mi->fsEntryInfo().attr & FS_ATTR_FOLDER && !mi->fsEntryInfo().action) {
            cdUp(mi->fsEntryInfo().name);
        } else if(!mi->fsEntryInfo().action) {
            extensionManager().run(directory()+mi->fsEntryInfo().name);
        }

    } );


    _fsentry_menu.pushBack( new FSEntryMenuItem(&_fsentry_menu, _fsentry_menu.rect().w(), 40, "Удалить нах") );
    _fsentry_menu.pushBack( new FSEntryMenuItem(&_fsentry_menu, _fsentry_menu.rect().w(), 40, "Переименовать...") );
    _fsentry_menu.pushBack( new FSEntryMenuItem(&_fsentry_menu, _fsentry_menu.rect().w(), 40, "Копировать...") );
    _fsentry_menu.pushBack( new FSEntryMenuItem(&_fsentry_menu, _fsentry_menu.rect().w(), 40, "Переместить...") );
    _fsentry_menu.pushBack( new FSEntryMenuItem(&_fsentry_menu, _fsentry_menu.rect().w(), 40, "Вставить...") );
    _fsentry_menu.pushBack( new FSEntryMenuItem(&_fsentry_menu, _fsentry_menu.rect().w(), 40, "Выделить") );
    _fsentry_menu.setLinesCount(_fsentry_menu.itemList()->size());

    _on_hide_it = _fsentry_menu.connectOnHideSignal( [this](ListMenu *m){

        m->event_mngr->notifyAfterEvent( EventManager::EventManagerAction( [](void *_m){
            FSEntryMenu *fsm = (FSEntryMenu *)_m;

            for(ActiveListItem *i : *fsm->itemList()) {
                delete i;
            }
            fsm->itemList()->clear();
            fsm->resetViewListPosition();
            fsm->setLinesCount(0);
            fsm->setLineItem(0);
        }, m));
        m->event_mngr->updateAfterEvent();
        _on_hide_it->disconnect();
    });

    _parent_area->pushFront(&_fsentry_menu);
}














