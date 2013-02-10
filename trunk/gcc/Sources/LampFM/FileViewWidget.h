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

#include "FileViewWidgetEngine.h"
#include "FileViewWidgetAbstractItem.h"



class FileViewWidget;





class FileViewWidget : public ActiveList
{
public:
    FileViewWidget(UActiveArea *parent, EffectManager *em, const Rect &r, EventManager *e);
    ~FileViewWidget();

    void pushBackFile(FSEntryInfo *info);
    void pushBackFile(const FSEntryInfo &info);
    void setViewList();
    void clearItems();
    void clearScreen();
    void setViewEngine(FileViewWidgetEngine *engine);


    int cdUp(const std::string &dir, bool effect = true);
    int cdDown();
    int cdUpAfterAction(const std::string &dir);

    int fillEntrys();

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

    inline image_t & getBorderImage() {
        return resourceManager().image("border");
    }

    inline image_t & getFolderIcon() {
        return resourceManager().image("folder-icon");
    }

    inline image_t & getFileIcon() {
        return resourceManager().image("file-icon");
    }

    inline image_t & getBackActionIcon() {
        return resourceManager().image("arrow-back-icon");
    }

    template <class T>
    inline void connectDestroySignal(T slot_) {
        __exit_signal.connect(slot_);
    }

    inline bool isSelectionMode() {
        return _item_select_mode;
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
    sigc::signal <void, FileViewWidget*> __exit_signal;
    FSEntryMenu _fsentry_menu;
    sigc::signal <void, ListMenu *>::iterator _on_hide_it;
    TimerWrap global_menu_timer;

private:
    std::string __current_dir;

    bool need_cd;
    std::string __cd_to;

public:
    image_t border_img, folder_icon, file_icon, back_action_icon;
    EffectManager *effect_manager;
    image_t cd_prev_screen_image;
    UActiveArea *_parent_area;

    GlobalMenu global_menu;
    GlobalMenuButton global_menu_button;
    bool global_menu_first_move;
    int global_menu_last_x, global_menu_last_y;
    int global_menu_way;
    int global_menu_speed;

public:
    void onItemMenu(const FSEntryInfo & f, UActiveAreaItem<ActiveAreaItem> *);

};

#endif // FILEVIEWWIDGET_H
