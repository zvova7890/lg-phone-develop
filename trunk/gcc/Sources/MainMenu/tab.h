#ifndef TAB_H
#define TAB_H

#include <Widget/Widget.h>
#include <Graph/Image.h>
#include <string>
#include <Core/Timer.h>

class Button;

class Tab : public Widget
{
public:
    Tab(const Rect &r, Widget *parent);
    ~Tab();

    void addButton(Image *icon, const std::string &text,
                   std::function<void(Tab *, Button *)> f = [](Tab *, Button *) {});
    bool show();


    void setName(const std::string &n) {
        m_name = n;
    }

    const std::string &name() const {
        return m_name;
    }

private:
    Timer m_animation;
    int buttons;
    Rect m_rat;
    std::string m_name;
};

#endif // TAB_H
