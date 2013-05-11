

#include <FileViewWidget.h>
#include <sstream>
#include <iostream>

#include "FileViewWidgetAbstractItem.h"
#include "FSEntryInfo.h"
#include "LocalFSProtocol.h"
#include "EInformationDialog.h"
#include "RenameDialog.h"
#include "MessageBox.h"



void FileViewWidget::showEntryInformationDialog()
{

}


void FileViewWidget::createFolder()
{
    RenameDialog *d = new RenameDialog(realRect(), this);
    d->show();
    d->handleResizeEvent().connect( [this](Widget *w) {
        w->setSize(realRect());
    });

    std::string mydir = directory();

    d->renameAction().connect( [this, mydir](RenameDialog *d, const std::string &t) {

        FSProtocol & p = protocolsContainer().indexOf(workspace().protocol);

        printf("mkdir: %s\n", (mydir+t).c_str());

        if(p.mkdir((mydir+t).c_str())) {
            MessageBox *msg = new MessageBox(this, "Ошибка!");
            msg->show();
        }


        d->deleteLater();

        refreshDir();
    });
}


void FileViewWidget::showRenameDialog(const std::string &name)
{
    RenameDialog *d = new RenameDialog(realRect(), this);
    d->setText(name);
    d->show();
    d->handleResizeEvent().connect( [this](Widget *w) {
        w->setSize(realRect());
    });

    std::string mydir = directory();

    d->renameAction().connect( [this, mydir, name](RenameDialog *d, const std::string &t) {

        FSProtocol & p = protocolsContainer().indexOf(workspace().protocol);

        printf("Rename: %s -> %s\n", (mydir+name).c_str(), (mydir+t).c_str());

        if(p.rename((mydir+name).c_str(), (mydir+t).c_str())) {
            MessageBox *msg = new MessageBox(this, "Ошибка!");
            msg->show();
        }


        d->deleteLater();

        refreshDir();
    });
}


void FileViewWidget::onItemMenu(const FSEntryInfo &f, FileViewWidgetAbstractItem *abstract_item)
{
    ((void)f);

    m_selectedList.clear();
    std::list <const FSEntryInfo *> & selected_list = m_selectedList;

    if(isSelectionMode()) {
        selected_list = getSelectedEntriesList();

        std::stringstream ss;
        ss << "Выбрано ";
        ss << selected_list.size();
        ss << " объектов";
        m_fsEntryMenu.setHeadText(ss.str());
    }
    else {
        const FSEntryInfo & l = abstract_item->getSelectedEntry();

        if(!l.name.empty())
            m_selectedList.push_back( &l );

        m_fsEntryMenu.setHeadText(l.name.c_str());
    }


    m_fsEntryMenu.setFullScreenBlock(true);
    m_fsEntryMenu.setBlockable(true);


    m_fsEntryMenu.style().setShadow(Brush());
    //m_fsEntryMenu.style().setBackground(Brush(&resourceManager().image("fs-menu")));
    //m_fsEntryMenu.style().setBackground(Brush(0xFF000000));

    m_fsEntryMenu.style().setShadow(Brush(0xFFFFFFFF));
    m_fsEntryMenu.style().setHeaderSize(Rect(0, 0, m_fsEntryMenu.rect().w(), 27));
    m_fsEntryMenu.style().setHeader( Brush( [](Brush &, const Rect &r){
         glSetPen(0xFFFFFFFF);
         glDrawHLine(r.x(), r.x2(), r.y2());
    }));

    m_fsEntryMenu.style().setListSize(Rect(0, 29, m_fsEntryMenu.rect().w(), m_fsEntryMenu.rect().h()-29));
    m_fsEntryMenu.setHeaderScrollable(true);

    //m_fsEntryMenu.__name = "m_fsEntryMenu";

    ListMenuItem *it = 0;

    if(!isSelectionMode()) {
        m_fsEntryMenu.scrollArea().addItem( (it = new ListMenuItem(&m_fsEntryMenu, m_fsEntryMenu.rect().w(), 40, "Открыть...")) );
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


    m_fsEntryMenu.scrollArea().addItem( (it = new ListMenuItem(&m_fsEntryMenu, m_fsEntryMenu.rect().w(), 40, "Удалить")) );
    it->onReleasedSignal().connect( [&selected_list, abstract_item, this](ListMenuItem *) {
        m_fsEntryMenu.hide();

        if(global_yes_no_question) {
            printf("Another question has view??\n");
        }

        global_yes_no_question = new QuestionDialog(this, "Удалить?");
        global_yes_no_question->show();
        global_yes_no_question->setBlockable(true);
        global_yes_no_question->setFullScreenBlock(true);

        global_yes_no_question->choisPressedSignal().connect( [&selected_list, abstract_item, this](QuestionDialog *self, int choise) {

            if(choise == 1) {

                if(isSelectionMode()) {
                    unlinkFiles(selected_list);
                    setSelectMode(false);
                }
                else {
                    std::list<const FSEntryInfo *> list;
                    list.push_back(&abstract_item->getSelectedEntry());
                    unlinkFiles(list);
                }
                refreshDir();
            }

            selected_list.clear();

            self->hide();

            self->deleteLater();

            eventManager()->updateAfterEvent();
            global_yes_no_question = 0;
        });


    } );

    if(!isSelectionMode()) {
        m_fsEntryMenu.scrollArea().addItem( it = new ListMenuItem(&m_fsEntryMenu, m_fsEntryMenu.rect().w(), 40, "Переименовать...") );
        it->onReleasedSignal().connect( [f, this](ListMenuItem *) {
            m_fsEntryMenu.hide();
            showRenameDialog(f.name);
        });
    }

    m_fsEntryMenu.scrollArea().addItem( it = new ListMenuItem(&m_fsEntryMenu, m_fsEntryMenu.rect().w(), 40, "Копировать...") );
    it->onReleasedSignal().connect( [abstract_item, this](ListMenuItem *i) {
        ((void)i);

        if(isSelectionMode()) {
            for(auto fs_entry : m_selectedList)
                copy(directory(), *fs_entry);

            setSelectMode(false);
        } else {
            copy(directory(), abstract_item->getSelectedEntry());
        }

        m_fsEntryMenu.hide();
        eventManager()->updateAfterEvent();
    });




    m_fsEntryMenu.scrollArea().addItem( it = new ListMenuItem(&m_fsEntryMenu, m_fsEntryMenu.rect().w(), 40, "Переместить...") );
    it->onReleasedSignal().connect( [abstract_item, this](ListMenuItem *i) {
        ((void)i);

        if(isSelectionMode()) {
            for(auto fs_entry : m_selectedList)
                move(directory(), *fs_entry);

            setSelectMode(false);
        } else {
            move(directory(), abstract_item->getSelectedEntry());
        }

        m_fsEntryMenu.hide();
        eventManager()->updateAfterEvent();
    });


    m_fsEntryMenu.scrollArea().addItem( it = new ListMenuItem(&m_fsEntryMenu, m_fsEntryMenu.rect().w(), 40, "Выделить/Снять") );
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
        m_fsEntryMenu.scrollArea().addItem( it = new ListMenuItem(&m_fsEntryMenu, m_fsEntryMenu.rect().w(), 40, "Выделить все") );
        it->onReleasedSignal().connect( [this](ListMenuItem *i) {
            ((void)i);
            m_fsEntryMenu.hide();

            markAllFiles();
            eventManager()->updateAfterEvent();
        });

        m_fsEntryMenu.scrollArea().addItem( it = new ListMenuItem(&m_fsEntryMenu, m_fsEntryMenu.rect().w(), 40, "Снять все") );
        it->onReleasedSignal().connect( [this](ListMenuItem *i) {
            ((void)i);
            m_fsEntryMenu.hide();

            unMarkAllFiles();
            eventManager()->updateAfterEvent();
        });
    }

    m_fsEntryMenu.scrollArea().addItem( it = new ListMenuItem(&m_fsEntryMenu, m_fsEntryMenu.rect().w(), 40, "Информация") );
    it->onReleasedSignal().connect( [abstract_item, this](ListMenuItem *i) {
        ((void)i);

        showEntryInformationDialog();
    });

    //it->setActive(false);


    printf("m_fsEntryMenu.scrollArea().items().size() = %d\n", m_fsEntryMenu.scrollArea().items().size());
    m_fsEntryMenu.scrollArea().setLinesCount(m_fsEntryMenu.scrollArea().items().size());

    m_onHideSlot = m_fsEntryMenu.onHideSignal().connect ( [this](ListMenu *m){

        m->eventManager()->notifyAfterEvent( [m](){
            ListMenu *fsm = m;

            for(Widget *i : fsm->scrollArea().items()) {
                delete i;
            }
            fsm->scrollArea().clear();
            fsm->scrollArea().resetViewPosition();

            fsm->scrollArea().setItem(0);
            fsm->scrollArea().setLinesCount(0);
            printf("Clear items!\n");
        });

        m->eventManager()->updateAfterEvent();
        m_fsEntryMenu.onHideSignal().disconnect(m_onHideSlot);
    });

    m_fsEntryMenu.show();
}
