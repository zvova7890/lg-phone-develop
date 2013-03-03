#ifndef GLOBALMENUBUTTON_H
#define GLOBALMENUBUTTON_H

#include <Ui/UButton.h>
#include <Graph/Image.h>
#include "png_ops.h"
#include <TimerWrap.h>
#include <signals/signal.h>



class GlobalMenuButton : public UActiveAreaItem<ActiveAreaItem>
{
public:
    typedef signal_slot::signal <void(GlobalMenuButton *, int, int, int)> MoveSignal;

    GlobalMenuButton(UActiveArea *parent, const Rect &r, bool blockable = true);
    void paintEvent();
    void touchEvent(int action, int x, int y);

    inline MoveSignal & touchActionSignal() {
        return m_move;
    }

    inline void setFilesCount(int c) {
        m_filesCount = c;
    }

    inline void setDirectoriesCount(int c) {
        m_dirsCount = c;
    }

    inline void setCurrentLine(int c) {
        m_line = c;
    }

    inline void setViewLines(int c) {
        m_entries = c;
    }

    inline void setDirecory(const std::string & d) {
        m_directory = d;
    }

    inline void setBackround(const Image *img) {
        m_borderImg = img;
    }

    inline void setWorkspace(int id) {
        m_workpace = id;
    }

private:
    MoveSignal m_move;
    const Image *m_borderImg;
    int m_filesCount, m_dirsCount, m_line, m_entries, m_workpace;
    std::string m_directory;


};

#endif // GLOBALMENUBUTTON_H
