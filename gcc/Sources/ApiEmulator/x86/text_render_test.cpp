




#include <gl.h>







void render_test()
{
    glClear(0xFF000000);

    glSetPen(0xFFFFFF00);
    glDrawString("Hello Ololo\nТрололо сам такой\nВтф, воркает о_О", 0, 1, 240, 400, 20,
                 FT_TEXT_H_UP | FT_TEXT_W_RIGHT | FT_TEXT_CRBREAK | FT_TEXT_SENTENCEBREAK, 0, 128);
}


