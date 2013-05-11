#ifndef KEYBOARDRU_H
#define KEYBOARDRU_H

#include "Keyboard.h"

class Image;

class KeyboardRU : public KeyboardHelper
{
public:
    KeyboardRU(const Rect &r, Keyboard *p);
    ~KeyboardRU();

    std::string name() const;

protected:


private:

};



#endif // KEYBOARDRU_H
