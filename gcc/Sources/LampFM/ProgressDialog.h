#ifndef PROGRESSDIALOG_H
#define PROGRESSDIALOG_H


#include <UActiveArea.h>
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
        _progress_name = n;
    }

    void setCurrentWorkStatus(const std::string &s) {
        _what_doing = s;
    }


    void setMaxFullProgress(unsigned int c) {
        _max_full_progress = c;
    }

    void setMaxProgress(unsigned int c) {
        _max_progress = c;
    }

    void setFullProgress(unsigned int c) {
        _full_progress = c;
    }

    unsigned int fullProgress() {
        return _full_progress;
    }

    void setProgress(unsigned int c) {
        _progress = c;
    }

    unsigned int progress() {
        return _progress;
    }


private:
    std::string _progress_name;
    std::string _what_doing;
    image_t *background;

    unsigned int _full_progress, _progress, _max_full_progress, _max_progress;
};

#endif // PROGRESSDIALOG_H
