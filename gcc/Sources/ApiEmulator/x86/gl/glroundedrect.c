
#include <gl.h>




void glCtxDrawRoundedRect(GLContext *ctx, int x1, int y1, int w, int h, int round_x, int round_y)
{
    GLPoint  _pts[1024];
    GLPoints pts = {1024, 0, 0, _pts};

    int r1 = 0;

    int rc_x1 = 0;
    int rc_y1 = 0;
    int rc_x2 = 0;
    int rc_y2 = 0;

    if(w < round_x)
        round_x = w;

    if(h < round_y)
        round_y = h;


    glArc(ctx, &pts, x1+(round_x/2), y1+(round_y/2), round_x, round_y, 180, 270, 0);
    r1 = pts.at;

    int l_diff_x = abs(pts.pts[r1-1].x - pts.pts[0].x)*2;
    int l_diff_y = /*abs(pts.pts[r1-1].y - pts.pts[0].y)*/0;

    rc_x1 = pts.pts[0].x;
    rc_x2 = pts.pts[r1-1].x+w+(pts.pts[r1-1].x - pts.pts[0].x)-l_diff_x;

    rc_y1 = pts.pts[0].y+l_diff_y+1;
    rc_y2 = pts.pts[r1-1].y+h+(pts.pts[r1-1].y - pts.pts[0].y)+l_diff_y-1;


    for(int i=0; i<r1; ++i) {
        int _y2, _x2;
        int diffx = abs(pts.pts[r1-1].x - pts.pts[i].x);
        int diffy = abs(pts.pts[r1-1].y - pts.pts[i].y);

        _x2 = pts.pts[i].x+w+(diffx*2);
        _y2 = pts.pts[i].y+h-(diffy*2);


        int x = pts.pts[i].x, y = pts.pts[i].y+l_diff_y;

        if(glTestRange(ctx, x, y))
           glDrawPixel16(ctx, x, y);


        x = _x2-l_diff_x;
        y = _y2+l_diff_y-1;

        if(glTestRange(ctx, x, y))
            glDrawPixel16(ctx, x, y);


        x = pts.pts[i].x;
        y = _y2+l_diff_y-1;

        if(glTestRange(ctx, x, y))
            glDrawPixel16(ctx, pts.pts[i].x, _y2+l_diff_y-1);


        x = _x2-l_diff_x;
        y = pts.pts[i].y+l_diff_y;

        if(glTestRange(ctx, x, y))
            glDrawPixel16(ctx, _x2-l_diff_x, pts.pts[i].y+l_diff_y);
    }


    glCtxDrawVLine(ctx, rc_y1, rc_y2, rc_x1);
    glCtxDrawVLine(ctx, rc_y1, rc_y2, rc_x2);

    glCtxDrawHLine(ctx, pts.pts[r1-1].x, pts.pts[0].x+w+(pts.pts[r1-1].x - pts.pts[0].x)-l_diff_x, pts.pts[r1-1].y+l_diff_y);
    glCtxDrawHLine(ctx, pts.pts[r1-1].x, pts.pts[0].x+w+(pts.pts[r1-1].x - pts.pts[0].x)-l_diff_x, pts.pts[r1-1].y+h+l_diff_y);
}




void glCtxFillRoundedRect(GLContext *ctx, int x1, int y1, int w, int h, int round_x, int round_y)
{
    GLPoint  _pts[1024];
    GLPoints pts = {1024, 0, 0, _pts};

    int r1 = 0;

    int rc_x1 = 0;
    int rc_y1 = 0;
    int rc_x2 = 0;
    int rc_y2 = 0;

    if(w < round_x)
        round_x = w;

    if(h < round_y)
        round_y = h;

    glArc(ctx, &pts, x1+(round_x/2), y1+(round_y/2), round_x, round_y, 180, 270, 0);
    r1 = pts.at;


    int l_diff_x = abs(pts.pts[r1-1].x - pts.pts[0].x)*2;
    int l_diff_y = /*abs(pts.pts[r1-1].y - pts.pts[0].y)*/0;

    rc_x1 = pts.pts[0].x;
    rc_x2 = pts.pts[r1-1].x+w+(pts.pts[r1-1].x - pts.pts[0].x)-l_diff_x;

    rc_y1 = pts.pts[0].y+l_diff_y+1;
    rc_y2 = pts.pts[r1-1].y+h+(pts.pts[r1-1].y - pts.pts[0].y)+l_diff_y-1;

    int last_y = 0, dlast_y = 0;
    for(int i=0; i<r1; ++i) {
        int _y2, _x2;
        int diffx = abs(pts.pts[r1-1].x - pts.pts[i].x);
        int diffy = abs(pts.pts[r1-1].y - pts.pts[i].y);

        _x2 = pts.pts[i].x+w+(diffx*2);
        _y2 = pts.pts[i].y+h-(diffy*2);

        if(last_y != pts.pts[i].y || i == 0)
            glCtxDrawHLine(ctx, pts.pts[i].x, _x2-l_diff_x, pts.pts[i].y+l_diff_y);
        last_y = pts.pts[i].y;


        if(dlast_y != _y2 || i == 0)
           glCtxDrawHLine(ctx, pts.pts[i].x, _x2-l_diff_x, _y2+l_diff_y-1);
        dlast_y = _y2;
    }


    glCtxDrawFilledRectange(ctx, rc_x1, rc_y1, rc_x2, rc_y2);
}

