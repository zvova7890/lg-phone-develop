

#include <FileViewWidget.h>
#include <sstream>
#include <iostream>

#include "FileViewWidgetAbstractItem.h"
#include "FSEntryInfo.h"
#include "LocalFSProtocol.h"




void FileViewWidget::onItemMenu(const FSEntryInfo &f, FileViewWidgetAbstractItem *abstract_item)
{
    ((void)f);

    _selected_list.clear();
    std::list <const FSEntryInfo *> & selected_list = _selected_list;

    if(isSelectionMode()) {
        selected_list = getSelectedEntriesList();

        std::stringstream ss;
        ss << "Выбрано ";
        ss << selected_list.size();
        ss << " объектов";
        m_fsEntryMenu.setHeadText(ss.str());
    }
    else {
        auto l = abstract_item->getSelectedEntry();

        m_fsEntryMenu.setHeadText(l.name.c_str());
    }


    m_fsEntryMenu.setUserData(abstract_item);
    m_fsEntryMenu.setFullScreenBlock(true);

    m_fsEntryMenu.style().setShadow(Brush());
    m_fsEntryMenu.style().setBackground(Brush(&resourceManager().image("fs-menu")));
    m_fsEntryMenu.style().setHeaderSize(Rect(0, 0, m_fsEntryMenu.rect().w(), 27));
    m_fsEntryMenu.style().setListSize(Rect(0, 29, m_fsEntryMenu.rect().w(), m_fsEntryMenu.rect().h()-29));

    ListMenuItem *it = 0;

    if(!isSelectionMode()) {
        m_fsEntryMenu.pushBack( (it = new ListMenuItem(&m_fsEntryMenu, m_fsEntryMenu.rect().w(), 40, "Открыть...")) );
        it->onReleasedSignal().connect( [&f, this](ListMenuItem *i) {
            ((void)i);
            m_fsEntryMenu.hide();
            const FSEntryInfo & fs_entry = f;

            if(fs_entry.attr & FSProtocol::FSEntryFlags::Dir && !fs_entry.action) {
                cdUp(fs_entry.name, true);

            } else if(!fs_entry.action) {
                extensionManager().run(directory()+fs_entry.name);
            }

        } );
    }


    m_fsEntryMenu.pushBack( (it = new ListMenuItem(&m_fsEntryMenu, m_fsEntryMenu.rect().w(), 40, "Удалить")) );
    it->onReleasedSignal().connect( [&selected_list, this](ListMenuItem *i) {
        ListMenu *mi = (ListMenu *)i->parent();
        auto item = (FileViewWidgetAbstractItem*)mi->userData();
        m_fsEntryMenu.hide();

        if(global_yes_no_question) {
            printf("Another question has view??\n");
        }

        global_yes_no_question = new QuestionDialog(parent(), Rect(20, 80, 240-40, 400-160), "Удалить?");
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

            selected_list.clear();

            self->hide();

            /* delete it after event safetly */
            eventManager()->notifyAfterEvent( EventManager::EventManagerAction( [](void *_m) {
                auto self = (QuestionDialog*)_m;
                delete self;
            }, self));

            eventManager()->updateAfterEvent();
            global_yes_no_question = 0;
        });


    } );

    if(!isSelectionMode()) {
        m_fsEntryMenu.pushBack( it = new ListMenuItem(&m_fsEntryMenu, m_fsEntryMenu.rect().w(), 40, "Переименовать...") );
        it->style().setLineText(0xffa3a3a3);
    }

    m_fsEntryMenu.pushBack( it = new ListMenuItem(&m_fsEntryMenu, m_fsEntryMenu.rect().w(), 40, "Копировать...") );
    it->onReleasedSignal().connect( [abstract_item, this](ListMenuItem *i) {
        ((void)i);

        if(isSelectionMode()) {
            for(auto fs_entry : _selected_list)
                copy(directory(), *fs_entry);

            setSelectMode(false);
        } else {
            copy(directory(), abstract_item->getSelectedEntry());
        }

        m_fsEntryMenu.hide();
        eventManager()->updateAfterEvent();
    });




    m_fsEntryMenu.pushBack( it = new ListMenuItem(&m_fsEntryMenu, m_fsEntryMenu.rect().w(), 40, "Переместить...") );
    it->onReleasedSignal().connect( [abstract_item, this](ListMenuItem *i) {
        ((void)i);

        if(isSelectionMode()) {
            for(auto fs_entry : _selected_list)
                move(directory(), *fs_entry);

            setSelectMode(false);
        } else {
            move(directory(), abstract_item->getSelectedEntry());
        }

        m_fsEntryMenu.hide();
        eventManager()->updateAfterEvent();
    });


    m_fsEntryMenu.pushBack( it = new ListMenuItem(&m_fsEntryMenu, m_fsEntryMenu.rect().w(), 40, "Выделить/Снять") );
    it->onReleasedSignal().connect( [abstract_item, this](ListMenuItem *i) {
        ((void)i);


        if(!isSelectionMode()) {
            m_itemSelectMode = !m_itemSelectMode;
            abstract_item->setMarked(true);
        } else {
            abstract_item->setMarked(!abstract_item->isMarked());
        }

        m_fsEntryMenu.hide();
        eventManager()->updateAfterEvent();
    });

    if(isSelectionMode()) {
        m_fsEntryMenu.pushBack( it = new ListMenuItem(&m_fsEntryMenu, m_fsEntryMenu.rect().w(), 40, "Выделить все") );
        it->onReleasedSignal().connect( [this](ListMenuItem *i) {
            ((void)i);
            m_fsEntryMenu.hide();

            markAllFiles();
            eventManager()->updateAfterEvent();
        });

        m_fsEntryMenu.pushBack( it = new ListMenuItem(&m_fsEntryMenu, m_fsEntryMenu.rect().w(), 40, "Снять все") );
        it->onReleasedSignal().connect( [this](ListMenuItem *i) {
            ((void)i);
            m_fsEntryMenu.hide();

            unMarkAllFiles();
            eventManager()->updateAfterEvent();
        });
    }

    m_fsEntryMenu.pushBack( it = new ListMenuItem(&m_fsEntryMenu, m_fsEntryMenu.rect().w(), 40, "Информация") );
    it->style().setLineText(0xffa3a3a3);


    m_fsEntryMenu.setLinesCount(m_fsEntryMenu.itemList()->size());

    m_onHideSlot = m_fsEntryMenu.onHideSignal().connect ( [this](ListMenu *m){

        m->eventManager()->notifyAfterEvent( EventManager::EventManagerAction( [](void *_m){
            ListMenu *fsm = (ListMenu *)_m;

            for(ActiveListItem *i : *fsm->itemList()) {
                delete i;
            }
            fsm->itemList()->clear();
            fsm->resetViewListPosition();
            fsm->setLinesCount(0);
            fsm->setLineItem(0);
        }, m));

        m->eventManager()->updateAfterEvent();
        m_fsEntryMenu.onHideSignal().disconnect(m_onHideSlot);
    });

    m_fsEntryMenu.show();
}
