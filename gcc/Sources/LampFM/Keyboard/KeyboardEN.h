#ifndef KEYBOARDEN_H
#define KEYBOARDEN_H

#include "Keyboard.h"

class Image;

class KeyboardEN : public KeyboardHelper
{
public:
    KeyboardEN(const Rect &r, Keyboard *p = 0);
    virtual ~KeyboardEN();

    String name() const;
    int rows() const;
    int rowMaxHeight() const;

protected:
    void kbdAction(Button *);

private:
    std::vector< std::vector <Button *> > m_buttons;
    Image *kbd_c;
    Image *kbd_up;
};



#endif // KEYBOARDEN_H
