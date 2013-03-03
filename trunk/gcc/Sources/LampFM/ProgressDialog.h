#ifndef PROGRESSDIALOG_H
#define PROGRESSDIALOG_H


#include <Ui/UActiveArea.h>
#include <Ui/UButton.h>
#include <Graph/Image.h>
#include <string>
#include <png_ops.h>


class ProgressDialog : public UActiveAreaItem<ActiveAreaItem>
{
public:
    ProgressDialog(UActiveArea *parent, const Rect &r, bool blockable = true);


    void paintEvent();
    void touchEvent(int action, int x, int y);
    void show();
    void hide();

    void setProgressName(const std::string &n) {
        m_progressName = n;
    }

    void setCurrentWorkStatus(const std::string &s) {
        m_whatDoing = s;
    }


    void setMaxFullProgress(unsigned int c) {
        m_maxFullProgress = c;
    }

    void setMaxProgress(unsigned int c) {
        m_maxProgress = c;
    }

    void setFullProgress(unsigned int c) {
        m_fullProgress = c;
    }

    unsigned int fullProgress() {
        return m_fullProgress;
    }

    void setProgress(unsigned int c) {
        m_progress = c;
    }

    unsigned int progress() {
        return m_progress;
    }


    UButton::signal & onCancelPressedSignal() {
        return m_onCancelPressed;
    }


private:
    std::string m_progressName;
    std::string m_whatDoing;
    UButton m_cancelButton;
    Image *m_background;
    UButton::signal m_onCancelPressed;
    UActiveArea m_activeArea;

    unsigned int m_fullProgress, m_progress, m_maxFullProgress, m_maxProgress;
};

#endif // PROGRESSDIALOG_H
