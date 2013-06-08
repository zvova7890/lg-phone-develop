
#ifndef __WIDGET_H__
#define __WIDGET_H__

#include <Widget/EventManager.h>
#include <Core/Rect.h>
#include <Core/Point.h>
#include <vector>
#include <list>
#include <string>


class TimerCounter;


class Widget
{
    enum {
        ATTR_HIDDEN = (1 << 1),
        ATTR_TOUCHED = (1 << 2),
        ATTR_MOVED = (1 << 3),
        ATTR_MOVING = (1 << 4),
        ATTR_OFFRECT_TOUCH = (1 << 5),
        ATTR_FULLSCREEN_BLOCK = (1 << 6),
        ATTR_BLOCKABLE = (1 << 7),
        ATTR_HAVE_LONGPRESS = (1 << 8),
        ATTR_MOVABLE = (1 << 9),
        ATTR_FOCUSED = (1 << 10),
        ATTR_FOCUSEABLE = (1 << 11),

        ATTR_RESIZE_NO_CALC_W = (1 << 12),
        ATTR_RESIZE_NO_CALC_H = (1 << 13)
    };

    inline void set_attr(int a) {
        if(!(m_attrs & a))
            m_attrs |= a;
    }

    inline void erase_attr(int a) {
        if(m_attrs & a)
            m_attrs &= ~a;
    }

    inline bool test_attr(int a) const {
        return m_attrs & a;
    }

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
        friend class Widget;
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
    virtual bool show();

    /* map before widget (Widget::widgetId) */
    virtual bool showBefore(Widget::wid & id);

    /* mark as hidden */
    virtual bool hide();

    /* unmap widget */
    virtual bool close();

    virtual void addParentToQueue();

    void activateLongPressSupport(bool is);

    void setWidth(int w);
    void setHeight(int h);
    void setFullScreenBlock(bool is);
    void setBlockable(bool is);

    void move(const Point &pos);
    void move(int x, int y);
    void moveX(int x);
    void moveY(int y);
    void setSize(const Rect &r);
    Widget *rootParent();
    virtual void *providesExtraExtension(const std::string &);
    bool isTop();
    bool toTop();

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

    inline void setUserData(void *ud) {
        m_userData = ud;
    }

    inline void *userData() {
        return m_userData;
    }

    inline void setRealRect(const Rect &r) {
        m_realRect = r;
    }

    /* have touch? */
    inline bool isTouched() const {
        return test_attr(ATTR_TOUCHED);
    }

    /* have move? */
    inline bool isMoved() const {
        return test_attr(ATTR_MOVED);
    }

    /* now it's moving? */
    inline bool isMoving() const {
        return test_attr(ATTR_MOVING);
    }

    /* if widget full screen grab, it receive event always,
     * even if xy not in widget rect, that flag is tell, have in rect touch or offrect
    */
    inline bool isOffRectTouch() const {
        return test_attr(ATTR_OFFRECT_TOUCH);
    }

    inline bool isFullScreenBlocked() const {
        return test_attr(ATTR_FULLSCREEN_BLOCK);
    }

    inline bool isBlockable() const {
        return test_attr(ATTR_BLOCKABLE);
    }

    bool isHaveLongPress() const {
        return test_attr(ATTR_HAVE_LONGPRESS);
    }

    void setMovable(bool is = true) {
        if(is)
            set_attr(ATTR_MOVABLE);
        else
            erase_attr(ATTR_MOVABLE);
    }

    bool isMovable() const {
        return test_attr(ATTR_MOVABLE);
    }

    bool isFocused() const {
        return test_attr(ATTR_FOCUSED);
    }

    void setFocuseable(bool is) {
        if(is)
            set_attr(ATTR_FOCUSEABLE);
        else
            erase_attr(ATTR_FOCUSEABLE);
    }

    bool isFocuseable() const {
        return test_attr(ATTR_FOCUSEABLE);
    }

    bool isHidden() const {
        return test_attr(ATTR_HIDDEN);
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

    signal_slot::signal<Widget *> & handleResizeEvent() {
        return m_resizeHandler;
    }

    void setResizeNoCalcW(bool is = true) {
        if(is)
            set_attr(ATTR_RESIZE_NO_CALC_W);
        else
            erase_attr(ATTR_RESIZE_NO_CALC_W);
    }

    void setResizeNoCalcH(bool is = true) {
        if(is)
            set_attr(ATTR_RESIZE_NO_CALC_H);
        else
            erase_attr(ATTR_RESIZE_NO_CALC_H);
    }

    void paint();
    void touch(int action, int x, int y);
    
    void focus();
    void unfocus();

    virtual void motionSensorEvent(int pos);
    virtual void motionSensorEvent(int x, int y, int z);
    virtual void resizeEvent();

protected:
    virtual void paintEvent();
    virtual void touchEvent(int action, int x, int y);
    virtual void focusEvent();
    virtual void unfocusEvent();

    void init();
    static void updateCoordinates(Widget *);


protected:
    std::list<Widget*> m_childs;
    signal_slot::signal<Widget *> m_resizeHandler;

public:
    std::string __name;

private:
    class TouchedWidget
    {
    public:
        TouchedWidget(Widget *wi, bool block = false) {
            w = wi;
            blocked = block;
        }

        Widget *w;
        bool blocked;
    };

    Widget *m_parent;
    Widget *m_touched;
    Widget *m_focused;
    wid m_wid;
    EventManager *m_eventManager;
    Rect m_rect;
    Rect m_realRect;
    Rect m_lastRect;

    int m_id;
    int m_attrs;

    TimerCounter *m_longPressTimer;

    Point m_lastTouchCoord;
    char m_lastAction;

    void *m_userData;
};







#endif
