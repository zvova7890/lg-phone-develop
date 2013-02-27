#include "EffectManager.h"
#include <gl.h>



EffectManager::EffectManager(UActiveArea *parent) :
    UActiveAreaItem<ActiveAreaItem>(parent, Rect(0, 0, 240, 400), false),
    is_active(false)
{
    auto event = [](TimerWrap *timer, void *user){
        ((void)timer);
        EffectManager *self = (EffectManager*)user;
        self->timerEvent();
    };

    TimerCreate(&timer, 1, event, this);
    memset(&prev_img, 0, sizeof(prev_img));
    memset(&next_img, 0, sizeof(next_img));
}


EffectManager::~EffectManager()
{
    is_active = false;
    TimerDestroy(&timer);

    if(next_img.bitmap)
        free(next_img.bitmap);
    next_img.bitmap = 0;
}



void EffectManager::reset()
{
    if(is_active) {
        memset(&prev_img, 0, sizeof(prev_img));
        TimerStop(&timer);
        is_active = false;

        if(next_img.bitmap)
            free(next_img.bitmap);
        next_img.bitmap = 0;
    }
}


void EffectManager::stop()
{
    bool _a = is_active;

    reset();
    _parent->pop(this);

    if(_a) effectFinished.trigger(this);
}


void EffectManager::start(int effect, int delay)
{
    reset();

    _effect = effect;
    start_pos = 0;
    end_pos = prev_img.w;
    speed = 20;

    _parent->pushFront(this);

    TimerStart(&timer, delay);
    is_active = true;

    eventManager()->updateAfterEvent();
}



void ScaleAndPaint(unsigned short *bitmap, int w, int h, int xfrom, int yfrom, int newWidth, int newHeight)
{
    int width = w;
    int height = h;

    GLContext *ctx = glActiveContext();
    for(int y = 0; y < newHeight; y++)
    {
        int dy = (y * height) / newHeight;
        for(int x = 0; x < newWidth; x++)
        {
            int dx = (x * width) / newWidth;
            int nx = x+xfrom;
            int ny = y+yfrom;

            //if(nx >= ctx->clip_x1 && nx < ctx->clip_x2 &&  ny >= ctx->clip_y1 && ny < ctx->clip_y2)
                glPutPixel16c(ctx, nx, ny, *(bitmap + dy*w+dx));
        }
    }
}


void EffectManager::paintEvent()
{
    //printf("void EffectManager::paintEvent()\n");

    if(!is_active)
        return;

    if(!prev_img.bitmap) {

        GLContext *ctx = glActiveContext();
        int sz = ctx->width *ctx->height *(ctx->depth/8);

        if(prev_img.bitmap)
            free(prev_img.bitmap);

        prev_img.bitmap = malloc(sz);
        prev_img.w = ctx->width;
        prev_img.h = ctx->height;
        prev_img.bit = ctx->depth;
        memcpy(prev_img.bitmap, &glGetPixel16(ctx, 0, 0), sz);
    }

    if(_effect >= EFFECT_CENTER_SCALE && _effect <= EFFECT_RIGHT_SCALE)
        scaleEffect(_effect - EFFECT_CENTER_SCALE);

    else if(_effect >= EFFECT_LEFT_MOVE && _effect <= EFFECT_RIGHT_MOVE)
        moveEffect(_effect - EFFECT_LEFT_MOVE);

    else if(_effect >= EFFECT_SUB_ALPHA && _effect <= EFFECT_ADD_ALPHA)
        alphaEffect(_effect - EFFECT_SUB_ALPHA);

    else if(_effect >= EFFECT_SUB_DOMINO && _effect <= EFFECT_ADD_DOMINO)
        dominoEffect(_effect - EFFECT_SUB_DOMINO);

    else {

        stop();
        return;
    }


/*
    if(prev_img.bitmap) {
        //glDisable(GL_ALPHA_TEST);
        //glDrawBitmap(start_pos, 0, prev_img.w, prev_img.h, prev_img.bit, prev_img.bitmap);
        //glEnable(GL_ALPHA_TEST);

        if(start_pos > -1) {
            int w_sz = 240-start_pos;
            int h_sz = 400 - (400 *(start_pos*100/240) /100);
            ScaleAndPaint((unsigned short*)prev_img.bitmap, prev_img.w, prev_img.h, start_pos/2, 400*(start_pos*100/240)/100 /2, w_sz, h_sz);
        }
    }

    start_pos += speed;
    speed += speed * 10 / 100+1;

    if(start_pos-50 > (prev_img.w)) {
        stop();
        //printf("effectTimerHandler: cdEffectStop()\n");
    } else {

        //printf("effectTimerHandler: refresh()\n");
        event_mngr->refresh();
    }*/
}


void EffectManager::timerEvent()
{
    if(timer.period != 3){
        TimerResetPeriod(&timer, 3);
    }
    eventManager()->updateAfterEvent();
}


void EffectManager::scaleEffect(int t)
{
    if(prev_img.bitmap) {
        if(start_pos > -1) {
            int w_sz = 0;
            int h_sz = 0;

            int xpos = 0;
            int ypos = 0;

            switch(t)
            {
                case 0:
                    w_sz = 240-start_pos;
                    h_sz = 400 - (400 *(start_pos*100/240) /100);
                    xpos = start_pos/2;
                    ypos = ((400 *(start_pos*100/240) /100))/2;
                    break;

                case 1:
                    w_sz = 240-start_pos;
                    h_sz = prev_img.h;
                    xpos = 0;
                    ypos = 0;
                    break;

                case 2:
                    w_sz = 240-start_pos;
                    h_sz = prev_img.h;
                    xpos = start_pos;
                    ypos = 0;
                    break;
            }

            //drawImage(0, 0, &prev_img);
            ScaleAndPaint((unsigned short*)prev_img.bitmap, 240, 400, xpos, ypos, w_sz, h_sz);
        }
    }

    if(start_pos > (prev_img.w)) {
        stop();
        eventManager()->updateAfterEvent();
        eventManager()->refresh();
    } else {
        eventManager()->refresh();
    }

    start_pos += speed;
    speed += speed * 10 / 100+1;
}


void EffectManager::moveEffect(int t)
{
    if(prev_img.bitmap) {
        if(start_pos > -1) {
            int xpos = 0;

            switch(t)
            {
                case 0:
                    xpos = -start_pos;
                    break;

                case 1:
                    xpos = start_pos;
                    break;
            }

            glDrawBitmap(xpos, 0, prev_img.w, prev_img.h, prev_img.bit, prev_img.bitmap);
        }
    }

    if(start_pos > (prev_img.w)) {
        stop();
        eventManager()->updateAfterEvent();
        //event_mngr->refresh();
    } else {
        eventManager()->refresh();
    }

    start_pos += speed;
    speed += speed * 10 / 100+1;
}


void EffectManager::alphaEffect(int t)
{
    if(prev_img.bitmap) {
        if(start_pos > -1) {
            int alpha = 0;

            switch(t)
            {
                case 0:
                    alpha = 0xff - (0xff * (start_pos*100/240) / 100);
                    if(!next_img.bitmap) {
                        next_img.bitmap = malloc(240*400*2);
                    }
                    memcpy(next_img.bitmap, GetScreenBuffer(), 240*400*2);

                    glDrawBitmap(0, 0, prev_img.w, prev_img.h, prev_img.bit, prev_img.bitmap);

                    glDrawAlphaBitmap(0, 0, alpha, prev_img.w, prev_img.h, prev_img.bit, next_img.bitmap);
                    break;

                case 1:
                    alpha = (0xff * (start_pos*100/240) / 100);
                    glDrawAlphaBitmap(0, 0, alpha, prev_img.w, prev_img.h, prev_img.bit, prev_img.bitmap);
                    break;
            }
        }
    }

    if(start_pos > (prev_img.w)-speed) {
        stop();
        eventManager()->updateAfterEvent();

    } else {
        eventManager()->refresh();
    }

    start_pos += speed;
    speed += speed * 8 / 100+1;
}



void EffectManager::dominoEffect(int t)
{
    if(prev_img.bitmap) {
        if(start_pos > -1) {

            switch(t)
            {
                case 0:

                    glDrawOptionalBitmap(start_pos, 0, start_pos, 0, prev_img.w, prev_img.h, 0, prev_img.w, prev_img.h, prev_img.bit, prev_img.bitmap);
                    break;

                case 1:

                    glDrawOptionalBitmap(0, 0, 0, 0, prev_img.w-start_pos, prev_img.h, 0, prev_img.w, prev_img.h, prev_img.bit, prev_img.bitmap);
                    break;
            }
        }
    }

    if(start_pos > (prev_img.w)) {
        stop();
        eventManager()->updateAfterEvent();

    } else {
        eventManager()->refresh();
    }

    start_pos += speed;
    speed += speed * 10 / 100+1;
}
