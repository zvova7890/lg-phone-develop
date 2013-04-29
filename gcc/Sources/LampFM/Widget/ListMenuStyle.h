#ifndef LISTMENUSTYLE_H
#define LISTMENUSTYLE_H


#include <Graph/Brush.h>



class ListMenuStyle
{
public:
    ListMenuStyle();

    ListMenuStyle &operator =(const ListMenuStyle &s);


    void setBackground(const Brush & b) {
        _background = b;
    }

    Brush & background() {
        return _background;
    }


    void setShadow(const Brush & b) {
        _shadow = b;
    }

    Brush & shadow() {
        return _shadow;
    }


    void setHeaderSize(const Rect &r) {
        _header_r = r;
    }

    const Rect & headerSize() {
        return _header_r;
    }


    void setListSize(const Rect &r) {
        _list_r = r;
    }

    const Rect & listSize() {
        return _list_r;
    }


    void setSize(const Rect &r) {
        _size = r;
    }

    const Rect & size() {
        return _size;
    }


    void setHeaderText(GLColor c) {
        _header_text = c;
    }

    GLColor headerText() {
        return _header_text;
    }


    bool isPaintLastLine() const {
        return _paint_last_line;
    }

    bool isPaintFirstLine() const {
        return _paint_first_line;
    }

private:
    Brush _background, _shadow;
    GLColor _header_text;
    bool _paint_first_line, _paint_last_line;

    Rect _header_r, _list_r;
    Rect _size;
};



class ListMenuItemStyle
{
public:
    ListMenuItemStyle();

    ListMenuItemStyle &operator =(const ListMenuItemStyle &s);

    void setSeparator(const Brush &b) {
        m_separator = b;
    }

    Brush & separator() {
        return m_separator;
    }

    void setLine(const Brush & b) {
        m_line = b;
    }

    Brush & line() {
        return m_line;
    }


    void setLinePressed(const Brush & b) {
        m_lineSelected = b;
    }

    Brush &  linePressed() {
        return m_lineSelected;
    }


    void setLineLongPressed(const Brush & b) {
        m_lineLongSelected = b;
    }

    Brush &  lineLongPressed() {
        return m_lineLongSelected;
    }

    void setLineText(GLColor c) {
        m_listText = c;
    }

    GLColor lineText() {
        return m_listText;
    }


    void setLinePressedText(GLColor c) {
        m_pressedText = c;
    }

    GLColor linePressedText() {
        return m_pressedText;
    }


    void setLineLongPressedText(GLColor c) {
        m_longPressedText = c;
    }

    GLColor lineLongPressedText() const {
        return m_longPressedText;
    }



    void setLineInactiveText(GLColor c) {
        m_inactiveText = c;
    }

    GLColor lineInactiveText() {
        return m_inactiveText;
    }


    void setLineInactivePressedText(GLColor c) {
        m_inactivePressedText = c;
    }

    GLColor lineInactivePressedText() {
        return m_inactivePressedText;
    }


    void setLineInactiveLongPressedText(GLColor c) {
        m_inactiveLongPresedText = c;
    }

    GLColor lineInactiveLongPressedText() const {
        return m_inactiveLongPresedText;
    }


private:
    Brush m_separator, m_line, m_lineSelected, m_lineLongSelected;
    GLColor m_listText, m_pressedText, m_longPressedText,
            m_inactiveText, m_inactivePressedText, m_inactiveLongPresedText;
};


#endif // LISTMENUSTYLE_H
