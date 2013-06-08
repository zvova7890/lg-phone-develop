#ifndef TABBOX_H
#define TABBOX_H

#include <Widget/Widget.h>
#include <Widget/Button.h>


class TabBox : public Widget
{
public:
    enum {
        Horizontal = 0,
        Vertiacal
    };

public:
    TabBox(const Rect &r, Widget *parent, int type = Horizontal);
    ~TabBox();


    void addTab(const std::string &text);
    int tabsCount() const;
    void setFocusTab(int idx, bool no_trigger = false);

    signal_slot::multi_signal<TabBox*, int, int> & onTabChanged() {
        return m_tabChanged;
    }

protected:
    void buttonHandler(Button *);
    void rebaseTabs();
    void paintEvent();
    void touchEvent(int action, int x, int y);

private:
    std::vector <Button *> m_tabsButton;
    char m_type;

    ButtonStyle m_style;
    signal_slot::multi_signal<TabBox *, int, int> m_tabChanged;
    Button *m_lastTouchedButton;
};

#endif // TABBOX_H
