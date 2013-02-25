#ifndef GLOBALMENUBUTTON_H
#define GLOBALMENUBUTTON_H

#include "UButton.h"
#include "png_ops.h"
#include <TimerWrap.h>
#include <signals/signal.h>



class GlobalMenuButton : public UButton
{
public:
    typedef signal_slot::signal <void(GlobalMenuButton *, int, int, int)> MoveSignal;

    GlobalMenuButton(UActiveArea *parent, const Rect &r, bool blockable = true);
    void paintEvent();
    void touchEvent(int action, int x, int y);

    inline MoveSignal & touchActionSignal() {
        return _move;
    }

    inline void setFilesCount(int c) {
        _files_cnt = c;
    }

    inline void setDirectoriesCount(int c) {
        _dirs_cnt = c;
    }

    inline void setCurrentLine(int c) {
        _line = c;
    }

    inline void setViewLines(int c) {
        _entries = c;
    }

    inline void setDirecory(const std::string & d) {
        _directory = d;
    }

    inline void setBackround(const image_t *img) {
        _border_img = img;
    }

private:
    MoveSignal _move;
    const image_t *_border_img;
    int _files_cnt, _dirs_cnt, _line, _entries;
    std::string _directory;

};

#endif // GLOBALMENUBUTTON_H
