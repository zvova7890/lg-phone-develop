
#ifndef __BUTTON_H__
#define __BUTTON_H__


#include "objectmap.h"
#include <gl.h>



typedef struct
{
    UIObject obj;
    void (*touchEvent)(void *obj, int action, int x, int y);
    void (*paintEvent)(void *obj);
    const char *text;
    int font;
    GLColor color, tcolor;
    unsigned int code;
    //image_t background;
}Button;



void buttonCreate(Button *button, int x, int y, int w, int h, int no_mem_touch,
                  void (*paint)(Button *),
                  void (*touch)(Button *, int, int, int));




#endif /*__BUTTON_H__*/
