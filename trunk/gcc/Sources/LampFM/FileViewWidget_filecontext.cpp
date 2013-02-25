

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

            if(fs_entry.attr & FSProtocol::FSEntryFlags::Dir && !fs_entry.action) {
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
        _fsentry_menu.pushBack( new ListMenuItem(&_fsentry_menu, _fsentry_menu.rect().w(), 40, "Переименовать...") );
    }

    _fsentry_menu.pushBack( it = new ListMenuItem(&_fsentry_menu, _fsentry_menu.rect().w(), 40, "Копировать...") );
    it->onReleasedSignal().connect( [abstract_item, this](ListMenuItem *i) {
        ((void)i);

        if(isSelectionMode()) {
            for(auto fs_entry : _selected_list)
                copy(directory(), *fs_entry);

            setSelectMode(false);
        } else {
            copy(directory(), abstract_item->getSelectedEntry());
        }

        _fsentry_menu.hide();
        eventManager()->updateAfterEvent();
    });




    _fsentry_menu.pushBack( it = new ListMenuItem(&_fsentry_menu, _fsentry_menu.rect().w(), 40, "Переместить...") );
    it->onReleasedSignal().connect( [abstract_item, this](ListMenuItem *i) {
        ((void)i);

        if(isSelectionMode()) {
            for(auto fs_entry : _selected_list)
                move(directory(), *fs_entry);

            setSelectMode(false);
        } else {
            move(directory(), abstract_item->getSelectedEntry());
        }

        _fsentry_menu.hide();
        eventManager()->updateAfterEvent();
    });


    _fsentry_menu.pushBack( it = new ListMenuItem(&_fsentry_menu, _fsentry_menu.rect().w(), 40, "Выделить/Снять") );
    it->onReleasedSignal().connect( [abstract_item, this](ListMenuItem *i) {
        ((void)i);


        if(!isSelectionMode()) {
            _item_select_mode = !_item_select_mode;
            abstract_item->setMarked(true);
        } else {
            abstract_item->setMarked(!abstract_item->isMarked());
        }

        _fsentry_menu.hide();
        eventManager()->updateAfterEvent();
    });

    if(isSelectionMode()) {
        _fsentry_menu.pushBack( it = new ListMenuItem(&_fsentry_menu, _fsentry_menu.rect().w(), 40, "Выделить все") );
        it->onReleasedSignal().connect( [this](ListMenuItem *i) {
            ((void)i);
            _fsentry_menu.hide();

            markAllFiles();
            eventManager()->updateAfterEvent();
        });

        _fsentry_menu.pushBack( it = new ListMenuItem(&_fsentry_menu, _fsentry_menu.rect().w(), 40, "Снять все") );
        it->onReleasedSignal().connect( [this](ListMenuItem *i) {
            ((void)i);
            _fsentry_menu.hide();

            unMarkAllFiles();
            eventManager()->updateAfterEvent();
        });
    }

    _fsentry_menu.pushBack( it = new ListMenuItem(&_fsentry_menu, _fsentry_menu.rect().w(), 40, "Информация") );



    _fsentry_menu.setLinesCount(_fsentry_menu.itemList()->size());

    _on_hide_it = _fsentry_menu.onHideSignal().connect ( [this](ListMenu *m){

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
        _fsentry_menu.onHideSignal().disconnect(_on_hide_it);
    });

    _fsentry_menu.show();
}
