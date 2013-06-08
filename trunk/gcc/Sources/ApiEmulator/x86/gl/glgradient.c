
#include <gl.h>




GLGradient *glAllocateGradient(GLGradient *g, int count)
{
    if(!g)
        g = malloc(sizeof *g);

    g->colors = calloc(1, count * sizeof(*g->colors));
    g->count  = count;
    return g;
}


void glDestroyGradient(GLGradient *g)
{
    if(g) {
        free(g->colors);
        g->colors = 0;
        g->count  = 0;
    }
}


void glCtxDrawGradient(GLContext *ctx, int x, int y, int w, int h, int type, GLGradient *g)
{
    if(type == 0) { // left -> right

        int pos_x = x;
        for(int i=0; i<g->count-1; ++i)
        {
            int pixels = g->colors[i].pixels;

            float a_start = glColorAlpha(g->colors[i].color);
            float a_end = glColorAlpha(g->colors[i+1].color);
            float a_diff = (a_end-a_start)/pixels;

            float r_start = glColorRed(g->colors[i].color);
            float r_end = glColorRed(g->colors[i+1].color);
            float r_diff = (r_end-r_start)/pixels;

            float g_start = glColorGreen(g->colors[i].color);
            float g_end = glColorGreen(g->colors[i+1].color);
            float g_diff = (g_end-g_start)/pixels;

            float b_start = glColorBlue(g->colors[i].color);
            float b_end = glColorBlue(g->colors[i+1].color);
            float b_diff = (b_end-b_start)/pixels;

            if(pos_x+pixels >= x+w) {
                pixels -= pos_x+pixels - (x+w);
            }

            for(int p = 0; p<pixels; ++p, ++pos_x) {

                GLColor c = (((unsigned char)a_start) << 24) | (((unsigned char)r_start) << 16) | (((unsigned char)g_start) << 8) | ((unsigned char)b_start);

                glSetPen(c);
                glCtxDrawVLine(ctx, y, y+h, pos_x);

                a_start += a_diff;
                r_start += r_diff;
                g_start += g_diff;
                b_start += b_diff;
            }

            if(pos_x >= x+w)
                break;
        }
    } else if(type == 1) { // right -> left

        int pos_x = x+w;
        for(int i=0; i<g->count-1; ++i)
        {
            int pixels = g->colors[i].pixels;

            float a_start = glColorAlpha(g->colors[i].color);
            float a_end = glColorAlpha(g->colors[i+1].color);
            float a_diff = (a_end-a_start)/pixels;

            float r_start = glColorRed(g->colors[i].color);
            float r_end = glColorRed(g->colors[i+1].color);
            float r_diff = (r_end-r_start)/pixels;

            float g_start = glColorGreen(g->colors[i].color);
            float g_end = glColorGreen(g->colors[i+1].color);
            float g_diff = (g_end-g_start)/pixels;

            float b_start = glColorBlue(g->colors[i].color);
            float b_end = glColorBlue(g->colors[i+1].color);
            float b_diff = (b_end-b_start)/pixels;

            if(pos_x-pixels <= x) {
                pixels -= x - (pos_x-pixels);
            }

            for(int p = 0; p<pixels; ++p, --pos_x) {

                GLColor c = (((unsigned char)a_start) << 24) | (((unsigned char)r_start) << 16) | (((unsigned char)g_start) << 8) | ((unsigned char)b_start);

                glSetPen(c);
                glCtxDrawVLine(ctx, y, y+h, pos_x);

                a_start += a_diff;
                r_start += r_diff;
                g_start += g_diff;
                b_start += b_diff;
            }

            if(pos_x <= x)
                break;
        }
    } else if(type == 2) { // up -> down

        int pos_y = y;
        for(int i=0; i<g->count-1; ++i)
        {
            int pixels = g->colors[i].pixels;

            float a_start = glColorAlpha(g->colors[i].color);
            float a_end = glColorAlpha(g->colors[i+1].color);
            float a_diff = (a_end-a_start)/pixels;

            float r_start = glColorRed(g->colors[i].color);
            float r_end = glColorRed(g->colors[i+1].color);
            float r_diff = (r_end-r_start)/pixels;

            float g_start = glColorGreen(g->colors[i].color);
            float g_end = glColorGreen(g->colors[i+1].color);
            float g_diff = (g_end-g_start)/pixels;

            float b_start = glColorBlue(g->colors[i].color);
            float b_end = glColorBlue(g->colors[i+1].color);
            float b_diff = (b_end-b_start)/pixels;

            if(pos_y+pixels >= y+h) {
                pixels -= pos_y+pixels - (y+h);
            }

            for(int p = 0; p<pixels; ++p, ++pos_y) {

                GLColor c = (((unsigned char)a_start) << 24) | (((unsigned char)r_start) << 16) | (((unsigned char)g_start) << 8) | ((unsigned char)b_start);

                glSetPen(c);
                glCtxDrawHLine(ctx, x, x+w, pos_y);

                a_start += a_diff;
                r_start += r_diff;
                g_start += g_diff;
                b_start += b_diff;
            }

            if(pos_y >= y+h)
                break;
        }
    } else if(type == 3) { // down -> up

        int pos_y = y+h;
        for(int i=0; i<g->count-1; ++i)
        {
            int pixels = g->colors[i].pixels;

            float a_start = glColorAlpha(g->colors[i].color);
            float a_end = glColorAlpha(g->colors[i+1].color);
            float a_diff = (a_end-a_start)/pixels;

            float r_start = glColorRed(g->colors[i].color);
            float r_end = glColorRed(g->colors[i+1].color);
            float r_diff = (r_end-r_start)/pixels;

            float g_start = glColorGreen(g->colors[i].color);
            float g_end = glColorGreen(g->colors[i+1].color);
            float g_diff = (g_end-g_start)/pixels;

            float b_start = glColorBlue(g->colors[i].color);
            float b_end = glColorBlue(g->colors[i+1].color);
            float b_diff = (b_end-b_start)/pixels;

            if(pos_y-pixels <= y) {
                pixels -= y - (pos_y-pixels);
            }

            for(int p = 0; p<pixels; ++p, --pos_y) {

                GLColor c = (((unsigned char)a_start) << 24) | (((unsigned char)r_start) << 16) | (((unsigned char)g_start) << 8) | ((unsigned char)b_start);

                glSetPen(c);
                glCtxDrawHLine(ctx, x, x+w, pos_y);

                a_start += a_diff;
                r_start += r_diff;
                g_start += g_diff;
                b_start += b_diff;
            }

            if(pos_y <= y)
                break;
        }
    }
}
