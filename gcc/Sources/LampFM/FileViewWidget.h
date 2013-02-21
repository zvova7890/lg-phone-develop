#ifndef FILEVIEWWIDGET_H
#define FILEVIEWWIDGET_H

#include <ActiveList.h>
#include <string>
#include <vector>
#include <png_ops.h>
#include "GlobalMenuButton.h"
#include "FSEntryMenu.h"
#include "FSEntryInfo.h"
#include "main.h"
#include <Timer.h>

#include <signals/signal.h>

#include "FileViewWidgetEngine.h"
#include "QuestionDialog.h"



class  FileViewWidgetAbstractItem;




class FileViewWidget : public ActiveList
{
public:
    typedef signal_slot::multi_signal <void(FileViewWidget*)> signal;

    FileViewWidget(UActiveArea *parent, EffectManager *em, const Rect &r, EventManager *e);
    ~FileViewWidget();

    void pushBackFile(FSEntryInfo *info);
    void pushBackFile(const FSEntryInfo &info);
    void setViewList();
    void clearItems();
    void clearScreen();
    void setViewEngine(FileViewWidgetEngine *engine);

    void unMarkAllFiles();
    void markAllFiles();

    std::list <const FSEntryInfo *> getSelectedEntriesList();
    int unlinkFiles(const std::list<const FSEntryInfo *> & list);

    int refreshDir();
    int cdUp(const std::string &dir, bool effect = true);
    int cdDown();
    int cdUpAfterAction(const std::string &dir);

    int fillEntries();

    void cdEffectPrepare(bool paint_fresh_screen = true);
    void cdEffectStart(int effect, int delay = 3);
    void cdEffectStop();

    void switchViewType();

    const std::string sizeToString(unsigned long bytes) const;

    void paintEvent();
    void touchEvent(int action, int x, int y);

    inline const std::string & directory() {
        return __current_dir;
    }

    void setDirectory(const std::string &dir) {
        __current_dir = dir;
    }

    inline FSEntryInfo & getFSEntry(int i) {

        if((int)_dir_fs_entrys.size() > i)
            return _dir_fs_entrys[i];

        i -= _dir_fs_entrys.size();
        if((int)_file_fs_entrys.size() > i)
            return _file_fs_entrys[i];

        return __null_fs_entry;
    }

    inline int fsEntriesCount() const {
        return _file_fs_entrys.size() + _dir_fs_entrys.size();
    }

    inline int viewFilesCount() {
        return _file_fs_entrys.size();
    }

    inline int viewDirsCount() {
        return _dir_fs_entrys.size();
    }

    inline void clearFSEntries() {
        _file_fs_entrys.clear();
        _dir_fs_entrys.clear();
    }


    inline signal & onExitSignal() {
        return __exit_signal;
    }

    inline bool isSelectionMode() {
        return _item_select_mode;
    }

    inline void setSelectMode(bool is = true) {
        _item_select_mode = is;
    }

    inline int viewItemsCount() {
        return _main_view_engine->viewItemsCount();
    }


protected:
    void initGlobalMenu();
    ScrollAreaItem *getListItem(int index);

protected:
    bool _item_select_mode;

private:
    int curent_engine;
    FileViewWidgetEngine *_main_view_engine;
    FSEntryInfo __null_fs_entry;
    std::vector<FSEntryInfo> _file_fs_entrys, _dir_fs_entrys;
    int _first_height;
    signal __exit_signal;
    FSEntryMenu _fsentry_menu;
    QuestionDialog *global_yes_no_question;
    FSEntryMenu::signal::slot _on_hide_it;
    Timer global_menu_timer;

private:
    std::string __current_dir;

    bool need_cd;
    std::string __cd_to;

public:
    image_t border_img, folder_icon, file_icon, back_action_icon,
            checkedbox_icon, checkbox_icon;
    EffectManager *effect_manager;
    image_t cd_prev_screen_image;
    UActiveArea *_parent_area;

    /* глобальное меню */
    GlobalMenu global_menu;
    GlobalMenuButton global_menu_button;
    GlobalMenuItem *mark_start_stop;

    bool global_menu_first_move, global_menu_showing;
    int global_menu_last_x, global_menu_last_y, global_menu_fix_y;
    int global_menu_way;
    int global_menu_speed;

    //int marked_files;

public:

    void onItemMenu(const FSEntryInfo & f,  FileViewWidgetAbstractItem *abstract_item);

};

#endif // FILEVIEWWIDGET_H
