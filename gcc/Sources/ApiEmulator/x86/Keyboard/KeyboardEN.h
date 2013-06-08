#ifndef KEYBOARDEN_H
#define KEYBOARDEN_H

#include "Keyboard.h"

class Image;

class KeyboardEN : public KeyboardHelper
{
public:
    KeyboardEN(const Rect &r, Keyboard *p = 0);
    virtual ~KeyboardEN();

    std::string name() const;

protected:
    //void kbdAction(Button *);

private:

};



#endif // KEYBOARDEN_H
