
#include <Button.h>
#include "KeyboardRU.h"
#include "main.h"


KeyboardRU::KeyboardRU(const Rect &r, Keyboard *p) :
    KeyboardHelper(r, p)
{
    std::vector< std::vector<const char *> > kbd_layout = {
        std::vector<const char *>{
            "й","ц","у","к","е","н","г","ш","щ","з","х","ъ"
        },

        std::vector<const char *>{
            "ф","ы","в","а","п","р","о","л","д","ж","э"
        },

        std::vector<const char *>{
            "я","ч","с","м","и","т","ь","б","ю"
        }
    };


    createKeyboard(kbd_layout);
}


KeyboardRU::~KeyboardRU()
{

}


std::string KeyboardRU::name() const
{
    return "ru_RU";
}


