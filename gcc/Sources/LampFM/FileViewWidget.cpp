
#include <Api/ApiLinkLib/ApiLink.h>


#include <math.h>
#include <unistd.h>
#include <fcntl.h>
#include <fs.h>
#include <loader.h>

#include <Core/compatible.h>
#include "FileViewWidget.h"
#include "FileViewWidgetListEngine.h"
#include "FileViewWidgetIconEngine.h"
#include "FileViewWidgetAbstractItem.h"
#include "FSEntryInfo.h"
#include "LocalFSProtocol.h"
#include "ThreadWorker.h"
#include "Keyboard/Keyboard.h"






FileViewWidget::FileScrollView::FileScrollView(const Rect &r, FileViewWidget *parent) :
    ScrollArea(r, ScrollArea::Vertical, parent)
{

}

FileViewWidget::FileScrollView::~FileScrollView()
{

}


void FileViewWidget::FileScrollView::paintEvent()
{
    glSaveClipRegion();
    glSetClipRegion(realRect().x(), realRect().y(), realRect().x2(), realRect().y2());
    ScrollArea::paintEvent();
    glRestoreClipRegion();
}


Widget *FileViewWidget::FileScrollView::widgetItem(int index)
{
    return parent()->m_mainViewEngine->getListItem(index);
}



FileViewWidget::FileViewWidget(Widget *parent, EffectManager *em, const Rect &r) :
    Widget(r, parent),
    m_itemSelectMode(false),
    m_fileViewList(Rect(Point(0, 0), r.wh()), this),
    m_mainViewEngine(0),
    m_firstHeight(r.h()),
    m_fsEntryMenu(Rect(10, 60, 200, rect().h()-60-10), this),
    global_yes_no_question(0),
    m_needCd(false),
    global_menu(Rect(0, 0, rect().w(), 60), this),
    m_headMenuButton(Rect(0, 0, rect().w(), 39), this),
    global_menu_showing(false),
    m_effectManager(em)
{
    memset(&m_prevScreenShoot, 0, sizeof(m_prevScreenShoot));

    if(rect().w() > 210) {
        int x = (rect().w()-210) / 2;
        int h = m_headMenuButton.rect().h()+10;
        m_fsEntryMenu.setSize( Rect(x, h, 210, rect().h()-h-10) );
    }

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

    m_headMenuButton.setHeight(39);
    m_headMenuButton.setBackround(&border_img);
    m_headMenuButton.setFullScreenBlock(false);
    m_headMenuButton.setBlockable(true);
    m_headMenuButton.setResizeNoCalcH(true);

    int off_h = m_headMenuButton.realRect().h();
    m_fileViewList.setSize( Rect(0, 0+off_h, rect().w(), rect().h()-off_h) );


    this->add(&m_fileViewList);
    this->add(&m_headMenuButton);
    this->add(&global_menu);

    global_menu.hide();
    global_menu.setResizeNoCalcH(true);


    auto event = [this](Timer *t) {

        if(!global_menu_showing)
            return;

        int new_y = 0;

        if(global_menu_way == 2) {
            new_y = global_menu.rect().y()+global_menu_speed;

            if(new_y > 0) {
                t->stop();
                global_menu.move( global_menu.rect().x(), 0);
                m_headMenuButton.move( 0, global_menu.rect().y2() );
                eventManager()->updateAfterEvent();
                return;
            }

        } else if(global_menu_way == 1) {
            new_y = global_menu.rect().y()-global_menu_speed;

            if(new_y+global_menu.rect().h() < 0) {

                global_menu.hide();

                t->stop();
                m_headMenuButton.move( 0, 0 );
                global_menu.setFullScreenBlock(false);
                eventManager()->updateAfterEvent();
                return;
            }
        }

        global_menu_speed += (global_menu_speed*30)/100;
        global_menu.move( global_menu.rect().x(), new_y);
        m_headMenuButton.move( 0, global_menu.rect().y2() );
        eventManager()->updateAfterEvent();
    };

    m_menuTimer.timerEventSignal().connect( event );


    m_headMenuButton.touchActionSignal().connect( [this](GlobalMenuButton *mm, int action, int x, int y) {

        switch(action)
        {
            case TOUCH_ACTION_PRESS:

                if(mm->isOffRectTouch()) {
                    return;
                }

                /*if(isSelectionMode()) {
                    //m_menuMarkOptionsItem->setText("Закончить выделение"); FIXME
                } else {
                    //m_menuMarkOptionsItem->setText("Начать выделение"); FIXME
                }*/

                if(!isClipboardsEmpty())
                    m_menuPasteItem->setActive();
                else
                    m_menuPasteItem->setActive(false);


                if(!global_menu_showing)
                   global_menu_first_move = true;
                else
                   global_menu_first_move = false;


                global_menu_fix_y = y - m_headMenuButton.rect().y();
                global_menu_last_x = x;
                global_menu_last_y = y;
                global_menu_speed = 25;

                break;

            case TOUCH_ACTION_RELEASE:
                if(!global_menu_first_move && !mm->isOffRectTouch())
                    m_menuTimer.start(40);

                if(mm->isOffRectTouch() && !mm->isMoved()) {
                    global_menu.hide();
                    return;
                }


                break;

            case TOUCH_ACTION_MOVE:
                if(!mm->isTouched() || mm->isOffRectTouch())
                    return;

                if(global_menu_first_move) {
                    fileViewArea().breakScrolling();
                    global_menu.show();
                    global_menu.setFullScreenBlock(false);
                    m_headMenuButton.setFullScreenBlock(true);
                    global_menu_showing = true;

                    fileViewArea().fixupViewPosition();
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

                m_headMenuButton.move( rect().x(), global_menu.rect().y2() );

                eventManager()->updateAfterEvent();
                break;
        }

    });


    global_menu.hideAction().connect( [this](GlobalIconMenu *) {
        m_menuTimer.stop();

        m_headMenuButton.setFullScreenBlock(false);
        m_headMenuButton.move( 0, 0 );

        global_menu_showing = false;
        eventManager()->updateAfterEvent();
    });


}


FileViewWidget::~FileViewWidget()
{
    m_exitSignal.trigger(this);

    clearFSEntries();
    setViewList();
    clearItems();

    if(m_prevScreenShoot.bitmap)
        free(m_prevScreenShoot.bitmap);
    m_prevScreenShoot.bitmap = 0;


    for(Widget *i : m_fsEntryMenu.scrollArea().items()) {
        delete i;
    }

    if(global_yes_no_question) {
        global_yes_no_question->hide();
        delete global_yes_no_question;
    }

    delete m_mainViewEngine;
}


void FileViewWidget::resizeEvent()
{
    //m_resizeHandler.trigger(this);
    Widget::resizeEvent();

    global_menu.setSize(Rect(0, 0, rect().w(), 60));

    int off_h = m_headMenuButton.rect().h();
    m_fileViewList.setSize( Rect(rect().x(), rect().y()+off_h, rect().w(), rect().h()-off_h) );

    if(!global_menu.isHidden())
        m_headMenuButton.setSize(Rect(rect().x(), global_menu.rect().y2(), rect().w(), off_h));
    else
        m_headMenuButton.setSize( Rect(m_headMenuButton.rect().xy(), Point(rect().w(), off_h)) );


    if(rect().w() > 210) {
        int x = (rect().w()-210) / 2;
        int h = m_headMenuButton.rect().h()+10;
        m_fsEntryMenu.setSize( Rect(x, h, 210, rect().h()-h-10) );
    } else {
        m_fsEntryMenu.setSize(Rect(10, 60, 200, rect().h()-60-10));
    }


    for(Widget *w : m_childs) {
        w->resizeEvent();
    }

    m_mainViewEngine->resizeEvent();
    //refreshDir();
}


void FileViewWidget::initGlobalMenu()
{
    global_menu.setFullScreenBlock(true);

#define check(b) if(!b->isTouched() || b->isMoved()) return;



    global_menu.addIcon(0, "Дом", &resourceManager().image("home"), [this](Button *b) {
        check(b);
        global_menu.hide();
        cdUp("/");
    });


    global_menu.addIcon(0, "Назад", &resourceManager().image("back"), [this](Button *b) {
        check(b);
        global_menu.hide();
        cdDown();
    });


    /*global_menu.addIcon(0, "Вперёд", &resourceManager().image("next"), [this](Button *b) {
        check(b);
        global_menu.hide();
        //cdDown();
    });*/


    global_menu.addIcon(0, "Обновить", &resourceManager().image("reload"), [this](Button *b) {
        check(b);
        global_menu.hide();
        refreshDir();
        eventManager()->updateAfterEvent();
    });


    global_menu.addIcon(0, "Вверх", &resourceManager().image("up"), [this](Button *b) {
        check(b);
        global_menu.hide();
        fileViewArea().toStart();
    });


    global_menu.addIcon(0, "Вниз", &resourceManager().image("down"), [this](Button *b) {
        check(b);
        global_menu.hide();
        fileViewArea().toEnd();
    });


    (m_menuPasteItem = global_menu.addIcon(0, "Вставить", &resourceManager().image("paste"), [this](Button *b) {
        check(b);
        if(b->isActive()) {
            global_menu.hide();
            paste(directory());
            refreshDir();
            eventManager()->updateAfterEvent();
        }
    }))->setActive(false);


    global_menu.addIcon(0, "Новый", &resourceManager().image("add"), [this](Button *b) {
        check(b);
        global_menu.hide();
        createFolder();
    });


    global_menu.addIcon(0, "Вид", &resourceManager().image("switch"), [this](Button *b) {
        check(b);
        global_menu.hide();
        switchViewType();
    });


    global_menu.addIcon(0, "Папка", &resourceManager().image("switch_workspace"), [this](Button *b) {
        check(b);
        global_menu.hide();
        switchNextWorkSpace();
    });


    global_menu.addIcon(0, "Выход", &resourceManager().image("exit"), [this](Button *b) {
        check(b);
        global_menu.hide();
        m_exitSignal.trigger(this);
    });

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
    fileViewArea().setLinesCount(m_mainViewEngine->itemsForViewList());
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
    glSetPen(0xFF000000);
    glDrawFilledRectange(realRect().x(), realRect().y(), rect().w(), rect().y2());

    int cline = fileViewArea().item()+1;
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


    m_headMenuButton.setDirecory(directory());
    m_headMenuButton.setDirectoriesCount(dirs);
    m_headMenuButton.setFilesCount(viewFilesCount());
    m_headMenuButton.setCurrentLine(cline);
    m_headMenuButton.setViewLines(entries);
    m_headMenuButton.setWorkspace(workspace().id);

    //m_headMenuButton.paintEvent();

    Widget::paintEvent();

#if 0
    //static int last_ololo = 0;

    bool haveOffRectItems = fileViewArea().listHeightInRect() > fileViewArea().rect().h();
    if(haveOffRectItems)
        last_ololo = fileViewArea().displayingItems();

    auto percent_to_real = [](float percent, int real) -> float {
        return real * percent / 100;
    };

    auto real_to_percent = [](int real, int part) -> float {
        return real? part * 100 / real : 0;
    };


    auto calc_percent_pos = [&real_to_percent, haveOffRectItems, this](int i) -> float {

        /*if(haveOffRectItems) {
            if(fileViewArea().displayingItems() < fileViewArea().count() &&
                    (fileViewArea().viewPageHeight() < fileViewArea().rect().h()))
                return 100.0f;
        } else
            return 100.0f;*/

        return real_to_percent(fileViewArea().count()-last_ololo-1, i);
    };

    auto calc_position = [&percent_to_real, this](int slider_h, float percent_pos) {
        return percent_to_real(percent_pos, fileViewArea().rect().h()-slider_h);
    };

    auto calc_step = [&percent_to_real, &real_to_percent, this]() -> float {
        return percent_to_real(real_to_percent(fileViewArea().count()-last_ololo, 1.0f), fileViewArea().rect().h());
    };


    auto calc_slider_h = [&calc_step, &haveOffRectItems, this]() -> int {


        auto slider_h = haveOffRectItems? calc_step() : fileViewArea().rect().h();

        if(slider_h < 10)
            slider_h = 10;
        return slider_h;
    };


    if(fileViewArea().listHeightInRect() > fileViewArea().rect().h()) {

    }

    Rect inrc = fileViewArea().size();

    auto percent_pos = calc_percent_pos(fileViewArea().item());
    int slider_h = calc_slider_h();
    int slider_pos = calc_position(slider_h, percent_pos);

    int diff_between_next = calc_position(slider_h,
                                          fileViewArea().item()+1 == fileViewArea().count()? 100 : calc_percent_pos(fileViewArea().item()+1) )
            - slider_pos;


    Widget *w = fileViewArea().widgetItem(fileViewArea().item()+fileViewArea().displayingItems());
    if(w) {

        int cpos = fileViewArea().itemCoord();

        if((!fileViewArea().item() && cpos > 0) || cpos == w->rect().h())
            cpos = 0;

        int p = cpos*100 / w->rect().h();
        int pos = diff_between_next * p / 100;

        slider_pos -= pos;
    }

    glSetPen(0xFF0000FF);


    //printf("slider_pos: %d\nslider_h: %d\nheight: %d\n\n", slider_pos, slider_h, fileViewArea().rect().h());

    glDrawVLine(inrc.y()+slider_pos, inrc.y()+slider_pos+slider_h, inrc.x2()-4);
#endif
}


void FileViewWidget::touchEvent(int action, int x, int y)
{
    //VScrollArea::touchEvent(action, x, y);
    Widget::touchEvent(action, x, y);

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
    int linei = fileViewArea().item();
    clearScreen();
    fillEntries();
    setViewList();

    if(linei >= fileViewArea().count())
        linei = fileViewArea().count()-1;

    fileViewArea().setItem(linei);

    if(fix_scroll)
        fileViewArea().fixupViewPosition();
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

    if(m_prevScreenShoot.bitmap)
        free(m_prevScreenShoot.bitmap);

    m_prevScreenShoot.bitmap = malloc(sz);
    m_prevScreenShoot.w = ctx->width;
    m_prevScreenShoot.h = ctx->height;
    m_prevScreenShoot.bit = ctx->depth;
    memcpy(m_prevScreenShoot.bitmap, &glGetPixel16(ctx, 0, 0), sz);

    /* толкаем в еффект менеджер */
    m_effectManager->pushPrevScreen(m_prevScreenShoot);
}


void FileViewWidget::cdEffectStart(int effect, int delay)
{
    m_effectManager->start(effect, delay);
}



void FileViewWidget::cdEffectStop()
{
    m_effectManager->stop();
}


void FileViewWidget::clearAndReset()
{
    fileViewArea().clear();
    fileViewArea().setLinesCount(0);
    fileViewArea().resetViewPosition();
}


void FileViewWidget::setViewEngine(int id)
{
    int fs_entry = m_mainViewEngine->fileSystemEntryByItem(fileViewArea().item());

    clearAndReset();
    clearItems();

    workspace().viewEngine = id;

    delete m_mainViewEngine;

    if(workspace().viewEngine) {
        m_mainViewEngine = new FileViewWidgetIconEngine(this);
    } else {
        m_mainViewEngine = new FileViewWidgetListEngine(this);
    }

    setViewList();
    fileViewArea().setItem( m_mainViewEngine->itemBySystemEntryNumber(fs_entry) );
}


void FileViewWidget::switchViewType()
{
    cdEffectPrepare();

    setViewEngine(!workspace().viewEngine);
    fileViewArea().fixupViewPosition();

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

    fileViewArea().breakScrolling();

    /* save scroll state */
    workspace().scrollState = fileViewArea().scrollState();

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
    fileViewArea().setScrollState( workspace().scrollState );
    fileViewArea().fixupViewPosition();

    if(bigger) {
        cdEffectStart(EFFECT_LEFT_MOVE);
    } else {
        cdEffectStart(EFFECT_RIGHT_MOVE);
    }

    return true;
}