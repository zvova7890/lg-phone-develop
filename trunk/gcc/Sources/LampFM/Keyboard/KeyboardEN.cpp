
#include <Button.h>
#include "KeyboardEN.h"
#include "main.h"


KeyboardEN::KeyboardEN(const Rect &r, Keyboard *p) :
    KeyboardHelper(r, p)
{
    std::vector< std::vector<const char *> > kbd_layout = {
        std::vector<const char *>{
            "q","w","e","r","t","y","u","i","o","p"
        },

        std::vector<const char *>{
            "a","s","d","f","g","h","j","k","l"
        },

        std::vector<const char *>{
            "z","x","c","v","b","n","m"
        }
    };


    createKeyboard(kbd_layout);
}


KeyboardEN::~KeyboardEN()
{

}




std::string KeyboardEN::name() const
{
    return "en_US";
}
