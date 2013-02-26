
#include "../Pico/PicoInt.h"
#include <pxeapi.h>
#include <taskapi.h>
#include "objectmap.h"
#include "button.h"
#include "ui.h"



#define global_key_state PicoPad[0]
#define push_key(x) { if(!(global_key_state & x)) global_key_state |= x; }
#define pop_key(x) { if(global_key_state & x) global_key_state &= ~x; }
#define STATIC_JOUSTICK




static Button bstart, bmode, bexit;
static Button navi_up, navi_down, navi_left, navi_right;
static Button navi_left_up, navi_left_down, navi_right_up, navi_right_down;



void startSelectButtonTouch(Button *btn, int action, int x, int y)
{
    if(action == TOUCH_ACTION_RELEASE) {
        pop_key(btn->code);
    } else {
        push_key(btn->code);
    }
}


void exitButton(Button *btn, int action, int x, int y)
{
    if(action == TOUCH_ACTION_RELEASE && btn->obj.have_touch && !btn->obj.have_move)
        TaskMngr_AppExit(0, 0, 0);
}

/*
	{ "UP     ", 0x001 },
	{ "DOWN   ", 0x002 },
	{ "LEFT   ", 0x004 },
	{ "RIGHT  ", 0x008 },
*/


/*
_USE_DRZ80
_ASM_DRAW_C
_ASM_MISC_C
_USE_YM2612_ASM_HELPER
*/


#ifndef STATIC_JOUSTICK
static const int accepted_interval = 25;

static int start_touch_x, start_touch_y;
static int last_touch_x, last_touch_y;
static int last_diff_x, last_diff_y;


void navigationTouch(int action, int x, int y)
{
    return;

    switch(action)
    {
    case TOUCH_ACTION_PRESS:
        start_touch_x = x;
        start_touch_y = y;
        last_touch_x = x;
        last_touch_y = y;
        last_diff_x = last_diff_y = 0;
        break;

    case TOUCH_ACTION_RELEASE:
        pop_key(0x001);
        pop_key(0x002);
        pop_key(0x004);
        pop_key(0x008);
        break;

    case TOUCH_ACTION_MOVE:

        pop_key(0x001);
        pop_key(0x002);
        pop_key(0x004);
        pop_key(0x008);

        int diff_x = start_touch_x - x;
        int diff_y = start_touch_y - y;
        int prio = 0;


        if(last_touch_x != x && ((last_touch_x > x && diff_x < 0) || (last_touch_x < x && diff_x > 0)))
            start_touch_x = x;

        if(last_touch_y != y && ((last_touch_y > y && diff_y < 0) || (last_touch_y < y && diff_y > 0)))
            start_touch_y = y;


        last_touch_x = x;
        last_touch_y = y;
        last_diff_x = diff_x;
        last_diff_y = diff_y;

#define abs(x) (x < 0? -x : x)

        /*if( abs(diff_x) - accepted_interval*2 > abs(diff_y) )
            prio |= 2;

        if( abs(diff_y) - accepted_interval*2 > abs(diff_x) )
            prio |= 4;*/


        if( prio & 2 || (!prio && abs(diff_x) > accepted_interval) ) {

            if(diff_x > 0)
                push_key(0x002); // DONW

            if(diff_x < 0)
                push_key(0x001); // UP
        }

        if( prio & 4 || (!prio && abs(diff_y) > accepted_interval) ) {

            if(diff_y > 0)
                push_key(0x004); // LEFT

            if(diff_y < 0)
                push_key(0x008); // RIGHT
        }

        break;
    }
}
#endif


void UIOnDraw()
{
    objectMapPaintEvent();
}



void UIOnInit()
{
    initObjectMap();

    buttonCreate(&bstart, 130, 240-25, 60, 25, 1, 0, startSelectButtonTouch);
    bstart.font = 14;
    bstart.text = "S";
    bstart.color = 0x4FFF000F;
    bstart.tcolor = 0x4F00FF00;
    bstart.code = 0x080;

    buttonCreate(&bmode, 130+65, 240-25, 60, 25, 1, 0, startSelectButtonTouch);
    bmode.font = 14;
    bmode.text = "M";
    bmode.color = 0x4FFF0000;
    bmode.tcolor = 0x4F00FF00;
    bmode.code = 0x800;

    buttonCreate(&bexit, 1, 1, 50, 25, 0, 0, exitButton);
    bexit.font = 14;
    bexit.text = "X";
    bexit.color = 0x4FFF0000;
    bexit.tcolor = 0x4F00FF00;
    bexit.code = 0;
 
    objectMapPush((UIObject*)&bstart);
    objectMapPush((UIObject*)&bmode);
    objectMapPush((UIObject*)&bexit);

    
    
#ifdef STATIC_JOUSTICK
    struct bmap {
        int x, y, w, h;
    };

#define button_s 35

    struct bmap buttons_map[9] = {

        {2+(button_s+1), 100,                   button_s, button_s}, // UP
        {2+(button_s+1), 100+(button_s+1)*2,    button_s, button_s}, // DOWN

        {2,  100+button_s+1,                    button_s, button_s}, // LEFT
        {2+(button_s+1)*2, 100+button_s+1,      button_s, button_s}, // RIGHT

        {2,  100,                               button_s, button_s}, // LEFT UP
        {2,  100+(button_s+1)*2,                button_s, button_s}, // LEFT DOWN

        {2+(button_s+1)*2, 100,                 button_s, button_s}, // RIGHT UP
        {2+(button_s+1)*2, 100+(button_s+1)*2,  button_s, button_s}  // RIGHT DOWN

    };

    buttonCreate(&navi_up, buttons_map[0].x, buttons_map[0].y, buttons_map[0].w, buttons_map[0].h, 1, 0, startSelectButtonTouch);
    navi_up.font = 14;
    navi_up.text = "U";
    navi_up.color = 0x4FFF0000;
    navi_up.tcolor = 0x4F00FF00;
    navi_up.code = 0x001;

    buttonCreate(&navi_down, buttons_map[1].x, buttons_map[1].y, buttons_map[1].w, buttons_map[1].h, 1, 0, startSelectButtonTouch);
    navi_down.font = 14;
    navi_down.text = "D";
    navi_down.color = 0x4FFF0000;
    navi_down.tcolor = 0x4F00FF00;
    navi_down.code = 0x002;


    buttonCreate(&navi_left, buttons_map[2].x, buttons_map[2].y, buttons_map[2].w, buttons_map[2].h, 1, 0, startSelectButtonTouch);
    navi_left.font = 14;
    navi_left.text = "L";
    navi_left.color = 0xFFFF0000;
    navi_left.tcolor = 0xFF00FF00;
    navi_left.code = 0x004;


    buttonCreate(&navi_right, buttons_map[3].x, buttons_map[3].y, buttons_map[3].w, buttons_map[3].h, 1, 0, startSelectButtonTouch);
    navi_right.font = 14;
    navi_right.text = "R";
    navi_right.color = 0x4FFF0000;
    navi_right.tcolor = 0x4F00FF00;
    navi_right.code = 0x008;


    /* ================================= combineed ======================= */

    buttonCreate(&navi_left_up, buttons_map[4].x, buttons_map[4].y, buttons_map[4].w, buttons_map[4].h, 1, 0, startSelectButtonTouch);
    navi_left_up.font = 14;
    navi_left_up.text = "";
    navi_left_up.color = 0xFFFF0000;
    navi_left_up.tcolor = 0xFF00FF00;
    navi_left_up.code = 0x004 | 0x001;


    buttonCreate(&navi_left_down, buttons_map[5].x, buttons_map[5].y, buttons_map[5].w, buttons_map[5].h, 1, 0, startSelectButtonTouch);
    navi_left_down.font = 14;
    navi_left_down.text = "";
    navi_left_down.color = 0xFFFF0000;
    navi_left_down.tcolor = 0xFF00FF00;
    navi_left_down.code = 0x004 | 0x002;


    buttonCreate(&navi_right_up, buttons_map[6].x, buttons_map[6].y, buttons_map[6].w, buttons_map[6].h, 1, 0, startSelectButtonTouch);
    navi_right_up.font = 14;
    navi_right_up.text = "";
    navi_right_up.color = 0x4FFF0000;
    navi_right_up.tcolor = 0x4F00FF00;
    navi_right_up.code = 0x008 | 0x001;


    buttonCreate(&navi_right_down, buttons_map[7].x, buttons_map[7].y, buttons_map[7].w, buttons_map[7].h, 1, 0, startSelectButtonTouch);
    navi_right_down.font = 14;
    navi_right_down.text = "";
    navi_right_down.color = 0x4FFF0000;
    navi_right_down.tcolor = 0x4F00FF00;
    navi_right_down.code = 0x008 | 0x002;

    
    objectMapPush((UIObject*)&navi_up);
    objectMapPush((UIObject*)&navi_down);

    objectMapPush((UIObject*)&navi_left);
    objectMapPush((UIObject*)&navi_right);

    objectMapPush((UIObject*)&navi_left_up);
    objectMapPush((UIObject*)&navi_left_down);

    objectMapPush((UIObject*)&navi_right_up);
    objectMapPush((UIObject*)&navi_right_down);
#endif
}



void UIOnDestroy()
{
    clearObjectMap();
}



void UIOnFocuse()
{

}



void UIOnUnFocus()
{

}




void UIOnKey(int type, int button)
{
    if(type != 1 && type != 2)
        return;

    //printf("UIOnKey: %d type, %d button\n", type, button);

    switch(button)
    {
    case KEY_SEND:
        if(type == 1) {
            push_key(0x040);
        }

        if(type == 2) {
            pop_key(0x040);
        }

        break;

    case KEY_MULTI:
        if(type == 1) {
            push_key(0x010);
        }

        if(type == 2) {
            pop_key(0x010);
        }

        break;

    case KEY_END:
        if(type == 1) {
            push_key(0x020);
        }

        if(type == 2) {
            pop_key(0x020);
        }
        break;
    }
}



void UIOnTouch(int action, int x, int y)
{
#ifndef STATIC_JOUSTICK
    if(!objectMapTouchEvent(action, x, y))
       navigationTouch(action, x, y);
#else
    objectMapTouchEvent(action, x, y);
#endif
}
























