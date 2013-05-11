#include "KeyboardEnum.h"





KeyboardEnum::KeyboardEnum(const Rect &r, Keyboard *p) :
    KeyboardHelper(r, p)
{
    std::vector< std::vector<const char *> > kbd_layout = {
        std::vector<const char *>{
            "1","2","3","4","5","6","7","8","9","0"
        },

        std::vector<const char *>{
            "@","#","$","%","&","*","-","+","(",")"
        },

        std::vector<const char *>{
            "!","\"","'",":",";","/","?"
        }
    };

    createKeyboard(kbd_layout);
}



KeyboardEnum::~KeyboardEnum()
{

}


void KeyboardEnum::setCharSizeType(bool )
{
  // FIXME
}


std::string KeyboardEnum::name() const {
    return "enum";
}

