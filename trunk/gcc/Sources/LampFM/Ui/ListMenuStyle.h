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
        _separator = b;
    }

    Brush & separator() {
        return _separator;
    }

    void setLine(const Brush & b) {
        _line = b;
    }

    Brush & line() {
        return _line;
    }


    void setLinePressed(const Brush & b) {
        _line_selected = b;
    }

    Brush &  linePressed() {
        return _line_selected;
    }


    void setLineLongPressed(const Brush & b) {
        _line_long_selected = b;
    }

    Brush &  lineLongPressed() {
        return _line_long_selected;
    }

    void setLineText(GLColor c) {
        _list_text = c;
    }

    GLColor lineText() {
        return _list_text;
    }


    void setLinePressedText(GLColor c) {
        _pressed_text = c;
    }

    GLColor linePressedText() {
        return _pressed_text;
    }


    void setLineLongPressedText(GLColor c) {
        _long_pressed_text = c;
    }

    GLColor lineLongPressedText() const {
        return _long_pressed_text;
    }



private:
    Brush _separator, _line, _line_selected, _line_long_selected;
    GLColor _list_text, _pressed_text, _long_pressed_text;
};


#endif // LISTMENUSTYLE_H
