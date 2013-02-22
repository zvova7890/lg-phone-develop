#ifndef LISTMENUSTYLE_H
#define LISTMENUSTYLE_H


#include "Brush.h"



class ListMenuStyle
{
public:
    ListMenuStyle();
    ~ListMenuStyle();

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


    void setSeparator(GLColor c) {
        _separator = c;
    }

    GLColor separator() {
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

    GLColor lineLongPressedText() {
        return _long_pressed_text;
    }


    void setHeaderText(GLColor c) {
        _header_text = c;
    }

    GLColor headerText() {
        return _header_text;
    }

private:
    Brush _background, _shadow,
          _line, _line_selected, _line_long_selected;

    GLColor _separator, _list_text, _pressed_text, _long_pressed_text, _header_text;

    Rect _header_r, _list_r;
    Rect _size;
};

#endif // LISTMENUSTYLE_H
