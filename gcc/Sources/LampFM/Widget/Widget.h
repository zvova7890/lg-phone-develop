
#ifndef __WIDGET_H__
#define __WIDGET_H__

#include <EventManager.h>
#include <include.h>
#include <Rect.h>
#include <vector>
#include <list>
#include <string>


class TimerCounter;


class Widget
{
public:
    
    class wid
    {
    public:
        wid() {
            m_w = 0;
        }

        wid(const std::list<Widget*>::iterator & it) :
            m_it(it)
        {
            m_w = *m_it;
        }

        wid(const wid & id) :
            m_it(id.m_it)
        {
            m_w = *m_it;
        }

        wid & operator =(const std::list<Widget*>::iterator & it)
        {
            m_it = it;
            m_w = *m_it;
            return *this;
        }

        wid & operator = (const wid & id) {
            m_it = id.m_it;

            m_w = *m_it;
            return *this;
        }

        void erase() {
            if(isValid()) {
                m_w->m_childs.erase(this->m_it);
                m_w = 0;
            }
        }

        bool isValid() const {
            return m_w != 0;
        }

        std::list<Widget*>::iterator iterator() {
            return m_it;
        }

        Widget *widget() {
            return m_w;
        }

    private:
        Widget *m_w;
        std::list<Widget*>::iterator m_it;
    };



    Widget(const Rect & rect, Widget *parent = 0);
    Widget(const Rect & rect, EventManager *event_manager);
    virtual ~Widget();


    /* add new widget on widget */
    virtual void add(Widget *);

    /* remove widget from widget list */
    virtual void remove(Widget::wid & id);

    /* insert */
    virtual void insert(Widget::wid & after, Widget *);

    /* swap widgets */
    virtual void swap(wid &id1, wid &id2);

    /* map on top or(if exist) mark as visible */
    virtual void show();

    /* map before widget (Widget::widgetId) */
    virtual void showBefore(Widget::wid & id);

    /* mark as hidden */
    virtual void hide();

    /* unmap widget */
    virtual void close();

    void activateLongPress(bool is);

    void setWidth(int w);
    void setHeight(int h);
    void setFullScreenBlock(bool is);
    void setBlockable(bool is);

    void move(const Point &pos);
    void move(int x, int y);
    void moveX(int x);
    void moveY(int y);
    void setSize(const Rect &r);

    /* aka realSize */
    Rect size() const;

    void deleteLater();
    void unfocusChild();

    inline EventManager *eventManager() {
        return m_eventManager;
    }

    /* virtual rect (relative to the parent) */
    inline Rect rect() const {
        return m_rect;
    }
    
    /* physical coordinates */
    inline Rect realRect() const {
        return m_realRect;
    }

    /* some id(as user needs, no have system character) */
    inline void setId(int i) {
        m_id = i;
    }

    inline int id() const {
        return m_id;
    }


    inline void setRealRect(const Rect &r) {
        m_realRect = r;
    }

    /* have touch? */
    inline bool isTouched() const {
        return m_isTouched;
    }

    /* have move? */
    inline bool isMoved() const {
        return m_isMoved;
    }

    /* now it's moving? */
    inline bool isMoving() const {
        return m_isMoving;
    }

    /* if widget full screen grab, it receive event always,
     * even if xy not in widget rect, that flag is tell, have in rect touch or offrect
    */
    inline bool isOffRectTouch() const {
        return m_isOffRectTouch;
    }

    inline bool isFullScreenBlocked() const {
        return m_isFullScreenBlocked;
    }

    inline bool isBlockable() const {
        return m_isBlockable;
    }

    bool isHaveLongPress() const {
        return m_isHaveLongPress;
    }

    void setMovable(bool is = true) {
        m_isMovable = is;
    }

    bool isMovable() const {
        return m_isMovable;
    }

    bool isFocused() const {
        return m_isFocused;
    }

    void setFocuseable(bool is) {
        m_isFocuseable = is;
    }

    bool isFocuseable() const {
        return m_isFocuseable;
    }

    bool isHidden() const {
        return m_hidden;
    }

    Widget *parent() {
        return m_parent;
    }

    wid & widgetId() {
        return m_wid;
    }

    std::list<Widget*> & directChilds() {
        return m_childs;
    }

    std::list<Widget*> childs() {
        return m_childs;
    }

    Point lastTouchedPosition() const {
        return m_lastTouchCoord;
    }

    void paint();
    void touch(int action, int x, int y);
    
    void focus();
    void unfocus();

protected:
    virtual void paintEvent();
    virtual void touchEvent(int action, int x, int y);
    virtual void focusEvent();
    virtual void unfocusEvent();

    void init();
    static void updateCoordinates(Widget *);


protected:
    std::list<Widget*> m_childs;

public:
    std::string __name;

private:
    Widget *m_parent;
    Widget *m_touched;
    Widget *m_focused;
    wid m_wid;
    EventManager *m_eventManager;
    Rect m_rect;
    Rect m_realRect;

    int m_id;

    bool m_hidden;
    bool m_isTouched;
    bool m_isMoved;
    bool m_isMoving;
    bool m_isOffRectTouch;
    bool m_isFullScreenBlocked, m_isBlockable;
    bool m_isHaveLongPress;
    bool m_isMovable;
    bool m_isFocused;
    bool m_isFocuseable;

    TimerCounter *m_longPressTimer;

    Point m_lastTouchCoord;
    char m_lastAction;
};







#endif
