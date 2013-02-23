
#include <sstream>
#include <iostream>

#include <math.h>
#include <unistd.h>
#include <fs.h>
#include <loader.h>

#include "FileViewWidget.h"
#include "FileViewWidgetListEngine.h"
#include "FileViewWidgetIconEngine.h"
#include "FileViewWidgetAbstractItem.h"
#include "FSEntryInfo.h"


FSEntryInfo __fs_entryinfo_null_entry;


FileViewWidget::FileViewWidget(UActiveArea *parent, EffectManager *em, const Rect &r, EventManager *e) :
    ActiveList(r, e),
    _item_select_mode(false),
    curent_engine(0),
    _main_view_engine(0),
    __null_fs_entry(FSEntryInfo("=Invalid=", 0, 0)),
    _first_height(r.h()),
    _fsentry_menu(parent, Rect(10, 60, 240-20, 280), event_mngr),
    global_yes_no_question(0),
    __current_dir("/"),
    need_cd(false),
    effect_manager(em),
    _parent_area(parent),
    global_menu(parent, Rect(1, 0, 238, 310), e),
    global_menu_button(e, Rect(0, 0, 240, 39), false),
    global_menu_showing(false) /*,
    marked_files(0)*/
{
    memset(&cd_prev_screen_image, 0, sizeof(cd_prev_screen_image));

    _current_protocol.push_back("local");
    _current_protocol.push_back("local");

    if(curent_engine)
        _main_view_engine = new FileViewWidgetIconEngine(this);
    else
        _main_view_engine = new FileViewWidgetListEngine(this);

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
    _parent_area->pushFront(&global_menu_button);


    auto event = [this](Timer *t) {

        int new_y = 0;

        if(global_menu_way == 2) {
            new_y = global_menu.rect().y()+global_menu_speed;

            if(new_y > 0) {
                t->stop();
                global_menu.move( global_menu.rect().x(), 1);
                global_menu_button.move( 0, global_menu.rect().y2()+1 );
                event_mngr->updateAfterEvent();
                return;
            }

        } else if(global_menu_way == 1) {
            new_y = global_menu.rect().y()-global_menu_speed;

            if(new_y+global_menu.rect().h() < 0) {

                global_menu.hide();

                t->stop();
                global_menu_button.move( 0, 0 );
                global_menu.setFullScreenBlock(false);
                event_mngr->updateAfterEvent();
                return;
            }
        }

        global_menu_speed += (global_menu_speed*30)/100;
        global_menu.move( global_menu.rect().x(), new_y);
        global_menu_button.move( 0, global_menu.rect().y2() +1);
        event_mngr->updateAfterEvent();
    };

    global_menu_timer.timerEventSignal().connect( event );


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
                    global_menu_timer.start(5);

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
                global_menu_button.move( 0, global_menu.rect().y2()+1 );
                event_mngr->updateAfterEvent();
                break;
        }

    });


    global_menu.onHideSignal().connect( [this](ListMenu *) {
        global_menu_timer.stop();

        global_menu_button.setFullScreenBlock(false);
        global_menu_button.move( 0, 0 );

        global_menu_showing = false;
        event_mngr->updateAfterEvent();
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

    if(global_yes_no_question) {
        global_yes_no_question->hide();
        delete global_yes_no_question;
    }

    delete _main_view_engine;
}


void FileViewWidget::initGlobalMenu()
{
    /* init menu */
    ListMenuItem *mi;

    global_menu.setFullScreenBlock(true);


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
        event_mngr->updateAfterEvent();
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
        event_mngr->updateAfterEvent();
    } );

    global_menu.pushBack(new ListMenuItem(&global_menu, global_menu.rect().w(), 40, "Информация"));

    global_menu.pushBack( mi = new ListMenuItem(&global_menu, global_menu.rect().w(), 40, "Выход..."));
    mi->onReleasedSignal().connect( [this](ListMenuItem *) {
        __exit_signal.trigger(this);
    } );


    global_menu.onHideSignal().connect( [this](ListMenu *){
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


    global_menu_button.setDirecory(directory());
    global_menu_button.setDirectoriesCount(dirs);
    global_menu_button.setFilesCount(viewFilesCount());
    global_menu_button.setCurrentLine(cline);
    global_menu_button.setViewLines(entries);

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


int FileViewWidget::refreshDir()
{
    clearScreen();
    fillEntries();
    setViewList();
    return 0;
}


int FileViewWidget::cdUp(const std::string &dir, bool effect)
{
    if(isSelectionMode()) {
        setSelectMode(false);
    }

    need_cd = false;
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

    need_cd = false;
    if(directory() == "/")
        return -1;

    cdEffectPrepare();

    clearScreen();

    std::string new_dir = directory();

    auto p = new_dir.find_last_of('/', new_dir.length()-2);
    new_dir = new_dir.assign(new_dir.begin(), new_dir.begin()+p+1);

    setDirectory(new_dir);

    fillEntries();

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


int FileViewWidget::fillEntries()
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



void FileViewWidget::onItemMenu(const FSEntryInfo &f, FileViewWidgetAbstractItem *abstract_item)
{
    ((void)f);


    std::list <const FSEntryInfo *> selected_list;

    if(isSelectionMode()) {
        selected_list = getSelectedEntriesList();

        std::stringstream ss;
        ss << "Выбрано ";
        ss << selected_list.size();
        ss << " объектов";
        _fsentry_menu.setHeadText(ss.str());
    }
    else {
        auto l = abstract_item->getSelectedEntry();

        _fsentry_menu.setHeadText(l.name.c_str());
    }


    _fsentry_menu.setUserData(abstract_item);
    _fsentry_menu.setFullScreenBlock(true);

    _fsentry_menu.style().setShadow(Brush());
    _fsentry_menu.style().setBackground(Brush(&resourceManager().image("fs-menu")));
    _fsentry_menu.style().setHeaderSize(Rect(0, 0, _fsentry_menu.rect().w(), 27));
    _fsentry_menu.style().setListSize(Rect(0, 29, _fsentry_menu.rect().w(), _fsentry_menu.rect().h()-29));

    ListMenuItem *it = 0;

    if(!isSelectionMode()) {
        _fsentry_menu.pushBack( (it = new ListMenuItem(&_fsentry_menu, _fsentry_menu.rect().w(), 40, "Открыть...")) );
        it->onReleasedSignal().connect( [&f, this](ListMenuItem *i) {
            ((void)i);
            _fsentry_menu.hide();
            const FSEntryInfo & fs_entry = f;

            if(fs_entry.attr & FS_ATTR_FOLDER && !fs_entry.action) {
                cdUp(fs_entry.name, true);

            } else if(!fs_entry.action) {
                extensionManager().run(directory()+fs_entry.name);
            }


        } );
    }


    _fsentry_menu.pushBack( (it = new ListMenuItem(&_fsentry_menu, _fsentry_menu.rect().w(), 40, "Удалить")) );
    it->onReleasedSignal().connect( [&selected_list, this](ListMenuItem *i) {
        ListMenu *mi = (ListMenu *)i->parent();
        auto item = (FileViewWidgetAbstractItem*)mi->userData();
        _fsentry_menu.hide();

        if(global_yes_no_question) {
            printf("Another question has view??\n");
        }

        global_yes_no_question = new QuestionDialog(Rect(20, 80, 240-40, 400-160), "Удалить?");
        global_yes_no_question->show();

        global_yes_no_question->choisPressedSignal().connect( [&selected_list, item, this](QuestionDialog *self, int choise) {

            if(choise == 1) {

                if(isSelectionMode()) {
                    unlinkFiles(selected_list);
                    setSelectMode(false);
                }
                else {
                    std::list<const FSEntryInfo *> list;
                    list.push_back(&item->getSelectedEntry());
                    unlinkFiles(list);
                }
                refreshDir();
            }

            self->hide();

            /* delete it after event safetly */
            event_mngr->notifyAfterEvent( EventManager::EventManagerAction( [](void *_m) {
                auto self = (QuestionDialog*)_m;
                delete self;
            }, self));

            event_mngr->updateAfterEvent();
            global_yes_no_question = 0;
        });


    } );

    if(!isSelectionMode()) {
        _fsentry_menu.pushBack( new ListMenuItem(&_fsentry_menu, _fsentry_menu.rect().w(), 40, "Переименовать...") );
    }

    _fsentry_menu.pushBack( new ListMenuItem(&_fsentry_menu, _fsentry_menu.rect().w(), 40, "Копировать...") );
    _fsentry_menu.pushBack( new ListMenuItem(&_fsentry_menu, _fsentry_menu.rect().w(), 40, "Переместить...") );

    if(!isSelectionMode()) {
        _fsentry_menu.pushBack( new ListMenuItem(&_fsentry_menu, _fsentry_menu.rect().w(), 40, "Вставить...") );
    }

    _fsentry_menu.pushBack( it = new ListMenuItem(&_fsentry_menu, _fsentry_menu.rect().w(), 40, "Выделить/Снять") );
    it->onReleasedSignal().connect( [abstract_item, this](ListMenuItem *i) {
        ((void)i);
        _fsentry_menu.hide();

        if(!isSelectionMode()) {
            _item_select_mode = !_item_select_mode;
            abstract_item->setMarked(true);
        } else {
            abstract_item->setMarked(!abstract_item->isMarked());
        }

        event_mngr->updateAfterEvent();
    });

    if(isSelectionMode()) {
        _fsentry_menu.pushBack( it = new ListMenuItem(&_fsentry_menu, _fsentry_menu.rect().w(), 40, "Выделить все") );
        it->onReleasedSignal().connect( [this](ListMenuItem *i) {
            ((void)i);
            _fsentry_menu.hide();

            markAllFiles();
            event_mngr->updateAfterEvent();
        });

        _fsentry_menu.pushBack( it = new ListMenuItem(&_fsentry_menu, _fsentry_menu.rect().w(), 40, "Снять все") );
        it->onReleasedSignal().connect( [this](ListMenuItem *i) {
            ((void)i);
            _fsentry_menu.hide();

            unMarkAllFiles();
            event_mngr->updateAfterEvent();
        });

    }



    _fsentry_menu.setLinesCount(_fsentry_menu.itemList()->size());

    _on_hide_it = _fsentry_menu.onHideSignal().connect ( [this](ListMenu *m){

        m->event_mngr->notifyAfterEvent( EventManager::EventManagerAction( [](void *_m){
            ListMenu *fsm = (ListMenu *)_m;

            for(ActiveListItem *i : *fsm->itemList()) {
                delete i;
            }
            fsm->itemList()->clear();
            fsm->resetViewListPosition();
            fsm->setLinesCount(0);
            fsm->setLineItem(0);
        }, m));

        m->event_mngr->updateAfterEvent();
        _fsentry_menu.onHideSignal().disconnect(_on_hide_it);
    });

    _fsentry_menu.show();
}



void FileViewWidget::unMarkAllFiles()
{
    _main_view_engine->setUnMarkedAll();
}


void FileViewWidget::markAllFiles()
{
    _main_view_engine->setMarkedAll();
}


std::list <const FSEntryInfo *> FileViewWidget::getSelectedEntriesList()
{
    return _main_view_engine->getSelectedEntriesList();
}


int FileViewWidget::unlinkFiles(const std::list<const FSEntryInfo *> & list)
{
    printf("unlinkFiles(%d)\n", list.size());
    int unlinked = 0;

    for(auto entry : list)
    {
        if((entry->attr & FS_ATTR_FILE || entry->attr == FS_ATTR_FILE) && !entry->action)
        {
            printf("unlink %s action: %d file: %d\n", entry->name.c_str(), entry->action, entry->attr & FS_ATTR_FILE);
            unlink((directory() + entry->name).c_str());
            unlinked ++;
        }

        else if(entry->attr & FS_ATTR_FOLDER && !entry->action) {
            rmdir((directory() + entry->name).c_str());
            unlinked ++;
        }
    }

    return unlinked;
}


