#ifndef KEYBOARDENUM_H
#define KEYBOARDENUM_H

#include "Keyboard.h"



class KeyboardEnum : public KeyboardHelper
{
public:
    KeyboardEnum(const Rect &r, Keyboard *p = 0);
    virtual ~KeyboardEnum();

    std::string name() const;
    void setCharSizeType(bool up);
};

#endif // KEYBOARDENUM_H
