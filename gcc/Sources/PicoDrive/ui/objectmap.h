
#ifndef __OBJECTMAP_H__
#define __OBJECTMAP_H__




typedef struct
{
    short x, y, w, h;
    char have_touch, have_move, no_mem_touch;
    void (*touchEvent)(void *obj, int action, int x, int y);
    void (*paintEvent)(void *obj);
}UIObject;



void objectMapPush(UIObject *obj);


void initObjectMap();
void clearObjectMap();
void objectMapPaintEvent();
int objectMapTouchEvent(int action, int x, int y);



#endif /*__OBJECTMAP_H__*/


