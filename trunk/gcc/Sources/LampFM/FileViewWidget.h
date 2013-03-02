#ifndef FILEVIEWWIDGET_H
#define FILEVIEWWIDGET_H

#include <ActiveList.h>
#include <string>
#include <vector>
#include <png_ops.h>

#include <ListMenu.h>
#include "GlobalMenuButton.h"
#include "FSEntryInfo.h"
#include "ClipBoard.h"
#include "main.h"
#include <Timer.h>

#include <signals/signal.h>

#include "FileViewWidgetEngine.h"
#include "QuestionDialog.h"
#include "ProgressDialog.h"



class  FileViewWidgetAbstractItem;




class FileViewWidget : public ActiveList
{
public:

    class Workspace {
    public:

        Workspace (int id, const std::string &protocol, const std::string &dir) {
            this->id = id;
            this->protocol = protocol;
            this->dir = dir;
            viewEngine = 0;
        }

        Workspace & operator=(const Workspace &w) {
            id = w.id;
            dir = w.dir;
            protocol = w.protocol;
            scrollState = w.scrollState;
            return *this;
        }

        int id;
        int viewEngine;
        std::string protocol;
        std::string dir;
        ActiveList::ScrollState scrollState;
    };


public:
    typedef signal_slot::multi_signal <void(FileViewWidget*)> signal;

    FileViewWidget(UActiveArea *parent, EffectManager *em, const Rect &r);
    ~FileViewWidget();

    void pushBackFile(FSEntryInfo *info);
    void pushBackFile(const FSEntryInfo &info);
    void setViewList();
    void clearItems();
    void clearScreen();
    void setViewEngine(int id);

    void unMarkAllFiles();
    void markAllFiles();


    void pushFileToClipBoard(const std::string &dir, const FSListedEntry &info, ClipBoard::Action type);

    void copy(const std::string &dir, const FSEntryInfo &info);
    void move(const std::string &dir, const FSEntryInfo &info);

    void paste(const std::string &dir);

    std::list <const FSEntryInfo *> getSelectedEntriesList();
    int unlinkFiles(const std::list<const FSEntryInfo *> & list);

    int refreshDir(bool fix_scroll = true);
    int cdUp(const std::string &dir, bool effect = true);
    int cdDown();
    int cdUpAfterAction(const std::string &dir);

    int fillEntries();

    void cdEffectPrepare(bool paint_fresh_screen = true);
    void cdEffectStart(int effect, int delay = 3);
    void cdEffectStop();

    void switchViewType(); // deprecated
    bool switchWorkSpace(unsigned int id);
    void switchNextWorkSpace();

    const std::string sizeToString(unsigned long bytes) const;

    void paintEvent();
    void touchEvent(int action, int x, int y);

    inline const std::string & directory() {
        return workspace().dir;
    }

    void setDirectory(const std::string &dir) {
        workspace().dir = dir;
    }

    inline FSEntryInfo & getFSEntry(int i) {

        if((int)m_DirsList.size() > i)
            return m_DirsList[i];

        i -= m_DirsList.size();
        if((int)m_FilesList.size() > i)
            return m_FilesList[i];

        return __null_fs_entry;
    }

    inline int fsEntriesCount() const {
        return m_FilesList.size() + m_DirsList.size();
    }

    inline int viewFilesCount() {
        return m_FilesList.size();
    }

    inline int viewDirsCount() {
        return m_DirsList.size();
    }

    inline void clearFSEntries() {
        m_FilesList.clear();
        m_DirsList.clear();
    }


    inline signal & onExitSignal() {
        return m_exitSignal;
    }

    inline bool isSelectionMode() {
        return m_itemSelectMode;
    }

    inline void setSelectMode(bool is = true) {
        m_itemSelectMode = is;
    }

    inline int viewItemsCount() {
        return m_mainViewEngine->viewItemsCount();
    }

    inline std::vector<Workspace> & workspaces() {
        return m_workspaces;
    }

    inline Workspace & workspace() {
        return m_workspaces[m_currentWorkspaceId];
    }

protected:

    void do_clipboard_work(const std::string &to_dir, int accepted_work);
    void set_clipboard_files(const std::string &dir, const FSEntryInfo &info, int action);
    int copy_file(const std::string &from, const std::string &to, unsigned int *full, unsigned int *done, bool *cancel_flag);
    void recursive_flush(FSProtocol &, int base_dir, const std::string &dir, void *handle, std::list<FSListedEntry> & list);
    void initGlobalMenu();
    ScrollAreaItem *getListItem(int index);

protected:
    bool m_itemSelectMode;

private:
    FileViewWidgetEngine *m_mainViewEngine;
    FSEntryInfo __null_fs_entry;
    std::vector<FSEntryInfo> m_FilesList, m_DirsList;
    int m_firstHeight;
    signal m_exitSignal;
    ListMenu m_fsEntryMenu;
    QuestionDialog *global_yes_no_question;
    ListMenu::signal::slot m_onHideSlot;
    Timer m_menuTimer;


    std::vector<Workspace> m_workspaces;
    unsigned int m_currentWorkspaceId;

    //std::vector <std::string> _current_protocol;
    std::list <const FSEntryInfo *> _selected_list;

    ClipBoard m_clipboard;

    bool m_needCd;
    std::string m_cdLaterTo;

    /* глобальное меню */
    ListMenu global_menu;
    GlobalMenuButton global_menu_button;
    ListMenuItem *mark_start_stop;

    bool global_menu_first_move, global_menu_showing;
    int global_menu_last_x, global_menu_last_y, global_menu_fix_y;
    int global_menu_way;
    int global_menu_speed;


public:
    image_t border_img, folder_icon, file_icon, back_action_icon,
            checkedbox_icon, checkbox_icon;
    EffectManager *effect_manager;
    image_t cd_prev_screen_image;

public:
    void onItemMenu(const FSEntryInfo & f,  FileViewWidgetAbstractItem *abstract_item);

};

#endif // FILEVIEWWIDGET_H
