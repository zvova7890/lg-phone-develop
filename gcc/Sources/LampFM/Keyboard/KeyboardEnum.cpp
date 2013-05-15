
#include <Button.h>
#include "KeyboardEnum.h"




KeyboardEnum::KeyboardEnum(const Rect &r, Keyboard *p) :
    KeyboardHelper(r, p)
{
    KeyboardEnum::m_kbdL = std::vector< std::vector<const char *> > {
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


    KeyboardEnum::m_upKbd = std::vector< std::vector<const char *> > {
        std::vector<const char *>{
            "~","`","|","•","√","Π","÷","×","{","}"
        },

        std::vector<const char *>{
            ":)",":D",":P","Oo","oO","^","_","=","[","]"
        },

        std::vector<const char *>{
            "™","®","©","¶","\\","<",">"
        }
    };

    createKeyboard(KeyboardEnum::m_kbdL);
}



KeyboardEnum::~KeyboardEnum()
{

}


void KeyboardEnum::setCharSizeType(bool up)
{
    const std::vector< std::vector<const char *> > &kbd = up? m_upKbd : m_kbdL;

    unsigned int i = 0;
    unsigned int at = 0;
    for(Button *b : m_unsignedButtons)
    {
        if(i >= kbd.at(at).size()) {

            if(kbd.size() >= at+1)
                at++;
            else
                break;

            i = 0;
            //printf("\n");
        }

        //printf("%s ", kbd.at(at).at(i));

        b->setText(kbd.at(at).at(i));

        ++i;
    }

    //printf("\n\n");
}


std::string KeyboardEnum::name() const {
    return "enum";
}

