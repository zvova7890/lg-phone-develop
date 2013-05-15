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

private:
    std::vector< std::vector<const char *> > m_kbdL;
    std::vector< std::vector<const char *> > m_upKbd;
};

#endif // KEYBOARDENUM_H
