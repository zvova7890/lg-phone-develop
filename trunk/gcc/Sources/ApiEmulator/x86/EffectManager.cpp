
#include <Core/compatible.h>
#include <pxeapi.h>
#include "EffectManager.h"
#include <gl.h>



EffectManager::EffectManager(Widget *parent) :
    Widget(Rect(0, 0, GRSYS_WIDTH, GRSYS_HEIGHT), parent),
    be_updated(0),
    m_isActive(false)
{
    setFullScreenBlock(false);
    setBlockable(false);

    timer.setUserData(this);
    timer.timerEventSignal().connect( this, &EffectManager::timerEvent, std::placeholders::_1 );


    addEffect( "alpha", std::bind(&EffectManager::alphaEffect, this, std::placeholders::_1) );
    addEffect( "alphazoom", std::bind(&EffectManager::alphaZoomEffect, this, std::placeholders::_1) );
    addEffect( "zoom", std::bind(&EffectManager::zoomEffect, this, std::placeholders::_1) );
    addEffect( "conveyor", std::bind(&EffectManager::conveyorEffect, this, std::placeholders::_1) );
}


EffectManager::~EffectManager()
{
    m_isActive = false;
}



void EffectManager::resizeEvent()
{
    Widget::resizeEvent();
    setSize(Rect(0, 0, GRSYS_WIDTH, GRSYS_HEIGHT));

    next_img.clear();
    prev_img.clear();
}



void EffectManager::reset()
{
    if(m_isActive) {
        timer.stop();
        m_isActive = false;

        next_img.clear();
        prev_img.clear();
    }
}


void EffectManager::stop()
{
    bool _a = m_isActive;

    if(m_isActive) {
        reset();
        hide();
    }


    if(_a) m_effectFinished.trigger(this);
}



void EffectManager::addEffect(const std::string &effect, std::function<void(EffectManager *)> f)
{
    m_effects[effect] = f;
}


void EffectManager::start(const std::string &effect, int flags, int state, int speed, int delay)
{
    reset();

    m_currentEffect = m_effects.find(effect);
    if(m_currentEffect == m_effects.end())
        return;

    m_state = state;
    m_speed = speed;
    m_flags = flags;

    show();
    toTop();

    timer.start(delay);
    m_isActive = true;

    eventManager()->updateAfterEvent();
}



void ScaleAndPaint(const unsigned short *bitmap, int w, int h, int xfrom, int yfrom,
                   int newWidth, int newHeight, unsigned char alpha)
{
    int width = w;
    int height = h;

    GLContext *ctx = glActiveContext();

    int y2 = yfrom + newHeight;
    int x2 = xfrom + newWidth;
    int xfrom_range = xfrom;
    int yfrom_range = yfrom;


    if(yfrom_range < ctx->clip_y1)
        yfrom_range = ctx->clip_y1;

    if(xfrom_range < ctx->clip_x1)
        xfrom_range = ctx->clip_x1;


    if(y2 > ctx->clip_y2)
        y2 = ctx->clip_y2;

    if(x2 > ctx->clip_x2)
        x2 = ctx->clip_x2;


    if(alpha != 0xff) {
        for(int y = yfrom_range; y < y2; y++)
        {
            int dy = ((y-yfrom) * height) / newHeight;
            for(int x = xfrom_range; x < x2; x++)
            {
                int dx = ((x-xfrom) * width) / newWidth;
                int nx = x;
                int ny = y;

                //if(nx >= ctx->clip_x1 && nx < ctx->clip_x2 &&  ny >= ctx->clip_y1 && ny < ctx->clip_y2) {
                    //glPutPixel16c(ctx, nx, ny, *(bitmap + dy*w+dx));
                    glDrawPixel16ca(ctx, nx, ny, *(bitmap + dy*w+dx), alpha);
                /*} else {

                    printf("lol: nx %d, ny: %d\n", nx, ny);
                }*/
            }
        }
    } else {
        for(int y = yfrom_range; y < y2; y++)
        {
            int dy = ((y-yfrom) * height) / newHeight;
            for(int x = xfrom_range; x < x2; x++)
            {
                int dx = ((x-xfrom) * width) / newWidth;
                int nx = x;
                int ny = y;

                //if(nx >= ctx->clip_x1 && nx < ctx->clip_x2 &&  ny >= ctx->clip_y1 && ny < ctx->clip_y2) {
                    glPutPixel16c(ctx, nx, ny, *(bitmap + dy*w+dx));
                    //glDrawPixel16ca(ctx, nx, ny, *(bitmap + dy*w+dx), alpha);
                /*} else {

                    printf("lol: nx %d, ny: %d\n", nx, ny);
                }*/
            }
        }
    }
}


void EffectManager::paintEvent()
{
    //if(be_updated < 1)
    //    return;
    //be_updated --;

    if(!m_isActive)
        return;


    if(m_currentEffect != m_effects.end())
        m_currentEffect->second(this);
}



void EffectManager::touchEvent(int action, int x, int y)
{
    Widget::touchEvent(action, x, y);
}


void EffectManager::timerEvent(Timer *)
{
    if(timer.period() != 20){
        timer.resetPeriod(20);
    }

    be_updated ++;
    eventManager()->updateAfterEvent();
}




void EffectManager::alphaEffect(EffectManager *)
{
    unsigned char alpha = 0;

    if(flags() & EFFECT_ALPHA_IN) {
        alpha = 255 * m_state / 100;
        alpha = 255-alpha;
    }
    else if(flags() & EFFECT_ALPHA_OUT) {
        alpha = 255 * m_state / 100;
    } else {
        alpha = 255 * m_state / 100;
    }

    drawImage(0, 0, &prev_img);


    glDrawAlphaBitmap(0, 0, alpha, next_img.width(), next_img.height(),
                      next_img.depth(), next_img.constBitmap());

    if(be_updated > 0) {
        be_updated --;

        m_state += m_speed;
        m_speed += m_speed * 25 / 100;

        if(m_state >= 100) {
            stop();
            eventManager()->updateAfterEvent();
        }
    }
}



void EffectManager::alphaZoomEffect(EffectManager *)
{
    unsigned char alpha = 0;

    if(flags() & EFFECT_ALPHA_IN) {
        alpha = 255 * m_state / 100;
        alpha = 255-alpha;
    }
    else if(flags() & EFFECT_ALPHA_OUT) {
        alpha = 255 * m_state / 100;
    } else {
        alpha = 255 * m_state / 100;
    }

    drawImage(0, 0, &prev_img);

    int new_w = (next_img.width()*m_state/100),
        new_h = (next_img.height()*m_state/100);

    if(!new_w)
        new_w = 1;

    if(!new_h)
        new_h = 1;


    new_w = next_img.width() + (next_img.width() - new_w);
    new_h = next_img.height() + (next_img.height() - new_h);


    ScaleAndPaint((const unsigned short*)next_img.constBitmap(),
                  next_img.width(), next_img.height(),
                  next_img.width()/2 - new_w/2, next_img.height()/2 - new_h/2,
                  new_w, new_h, alpha);


    if(be_updated > 0) {
        be_updated --;

        m_state += m_speed;
        m_speed += m_speed * 25 / 100;

        if(m_state >= 100) {
            stop();
            eventManager()->updateAfterEvent();
        }
    }
}



void EffectManager::zoomEffect(EffectManager *)
{
    unsigned char alpha = 255;
    drawImage(0, 0, &prev_img);


    if(flags() & EFFECT_ALPHA_IN) {
        alpha = 255 * m_state / 100;
        alpha = 255-alpha;
    }
    else if(flags() & EFFECT_ALPHA_OUT) {
        alpha = 255 * m_state / 100;
    }


    int new_w = (next_img.width()*m_state/100),
        new_h = (next_img.height()*m_state/100);

    if(!new_w)
        new_w = 1;

    if(!new_h)
        new_h = 1;


    if(flags() & EFFEC_DOWN) {
        new_w = next_img.width() + (next_img.width() - new_w);
        new_h = next_img.height() + (next_img.height() - new_h);

    } else {
    }

    ScaleAndPaint((const unsigned short*)next_img.constBitmap(),
                  next_img.width(), next_img.height(),
                  next_img.width()/2 - new_w/2, next_img.height()/2 - new_h/2,
                  new_w, new_h, alpha);


    if(be_updated > 0) {
        be_updated --;

        m_state += m_speed;
        m_speed += m_speed * 25 / 100;

        if(m_state >= 100) {
            stop();
            eventManager()->updateAfterEvent();
        }
    }
}


/*
void EffectManager::conveyorEffect(EffectManager *)
{
    int ypos = -(next_img.height()*m_state/100);


    if()

    drawImage(0, ypos, &prev_img);
    drawImage(0, ypos+prev_img.height(), &next_img);

    if(be_updated > 0) {
        be_updated --;

        m_state += m_speed;
        //m_speed += m_speed * 10 / 100;

        if(m_state >= 100) {
            stop();
            eventManager()->updateAfterEvent();
        }
    }
}
*/


void EffectManager::conveyorEffect(EffectManager *)
{
    auto val2perc = [](int full, int part){
        return part*100 / full;
    };


    auto perc2val = [](int full, int perc){
        return full * perc / 100;
    };


    int ypos = -(next_img.height()*m_state/100);
    int ctx_w = glActiveContext()->width;
    int ctx_h = glActiveContext()->height;

    glClear(0xFF000000);

    if(m_state < 33) {
        int percent = val2perc(32, m_state);
        int planed_w = ctx_w/4;
        int planed_h = ctx_h/4;

        int new_w = ctx_w - (perc2val(planed_w, percent)),
            new_h = ctx_h - (perc2val(planed_h, percent));

        if(!new_w)
            new_w = 1;

        if(!new_h)
            new_h = 1;

        prev_img = prev_img.scale(new_w, new_h);
        drawImage(ctx_w/2 - new_w/2, ctx_h/2 - new_h/2, &prev_img);
    }

    else if(m_state < 66) {

        if(next_img.width() != prev_img.width()) {
            tmp_img = next_img;
            next_img = next_img.scale(prev_img.width(), prev_img.height());
        }

        int state = m_state - 33;
        int percent = /*(state*100 / 33)*/ val2perc(33, state);


        int center_x = (ctx_w/2 - prev_img.width()/2);
        int center_y = (ctx_h/2 - prev_img.height()/2);
        int size = prev_img.width() + center_x;
        int xpos = (size *percent/100);

        drawImage(-(xpos-center_x), center_y, &prev_img);

        drawImage( (-(xpos-center_x)) + prev_img.width() + (ctx_w - (center_x+prev_img.width())),
                   center_y, &next_img);

    }

    else {

        int state = m_state - 66;

        int percent = 100-val2perc(34, state);
        int planed_w = ctx_w/4;
        int planed_h = ctx_h/4;

        int new_w = ctx_w - (perc2val(planed_w, percent)),
            new_h = ctx_h - (perc2val(planed_h, percent));

        if(!new_w)
            new_w = 1;

        if(!new_h)
            new_h = 1;

        next_img = tmp_img.scale(new_w, new_h);
        drawImage(ctx_w/2 - new_w/2, ctx_h/2 - new_h/2, &next_img);
    }


    //drawImage(0, ypos, &prev_img);
    //drawImage(0, ypos+prev_img.height(), &next_img);

    if(be_updated > 0) {
        be_updated --;

        m_state += m_speed;
        //m_speed += m_speed * 10 / 100;

        if(m_state >= 100) {
            stop();
            eventManager()->updateAfterEvent();
        }
    }
}
