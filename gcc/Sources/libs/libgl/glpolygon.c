
#include <gl.h>
#include <stdlib.h>


/* ported from GD library */


void glCtxDrawFilledPolygon (GLContext *ctx, GLPoint *p, int n)
{
    int i;
    int j;
    int index;
    int y;
    int miny, maxy;
    int x1, y1;
    int x2, y2;
    int ind1, ind2;
    int ints;
    if (!n) {
        return;
    }

    if(ctx->polyIntsCnt <= n) {
        ctx->polyInts = realloc (ctx->polyInts, sizeof (int) * (n+1));
        ctx->polyIntsCnt = n+1;
    }

    miny = p[0].y;
    maxy = p[0].y;
    for (i = 1; (i < n); i++)
    {
        if (p[i].y < miny)
        {
            miny = p[i].y;
        }
        if (p[i].y > maxy)
        {
            maxy = p[i].y;
        }
    }
    /* 2.0.16: Optimization by Ilia Chipitsine -- don't waste time offscreen */
    /* 2.0.26: clipping rectangle is even better */

    /* Fix in 1.3: count a vertex only once */
    for (y = miny; (y <= maxy); y++)
    {
        ints = 0;
        for (i = 0; (i < n); i++)
        {
            if (!i)
            {
                ind1 = n - 1;
                ind2 = 0;
            }
            else
            {
                ind1 = i - 1;
                ind2 = i;
            }
            y1 = p[ind1].y;
            y2 = p[ind2].y;
            if (y1 < y2)
            {
                x1 = p[ind1].x;
                x2 = p[ind2].x;
            }
            else if (y1 > y2)
            {
                y2 = p[ind1].y;
                y1 = p[ind2].y;
                x2 = p[ind1].x;
                x1 = p[ind2].x;
            }
            else
            {
                continue;
            }

            /* Do the following math as float intermediately, and round to ensure
             * that Polygon and FilledPolygon for the same set of points have the
             * same footprint. */

            if ((y >= y1) && (y < y2))
            {
                ctx->polyInts[ints++] = (int) ((float) ((y - y1) * (x2 - x1)) /
                                               (float) (y2 - y1) + 0.5 + x1);
            }
            else if ((y == maxy) && (y > y1) && (y <= y2))
            {
                ctx->polyInts[ints++] = (int) ((float) ((y - y1) * (x2 - x1)) /
                                               (float) (y2 - y1) + 0.5 + x1);
            }
        }
        /*
          2.0.26: polygons pretty much always have less than 100 points,
          and most of the time they have considerably less. For such trivial
          cases, insertion sort is a good choice. Also a good choice for
          future implementations that may wish to indirect through a table.
        */
        for (i = 1; (i < ints); i++)
        {
            index = ctx->polyInts[i];
            j = i;
            while ((j > 0) && (ctx->polyInts[j - 1] > index))
            {
                ctx->polyInts[j] = ctx->polyInts[j - 1];
                j--;
            }
            ctx->polyInts[j] = index;
        }
        for (i = 0; (i < (ints)); i += 2)
        {
#if 0
            int minx = polyInts[i];
            int maxx = polyInts[i + 1];
#endif
            /* 2.0.29: back to gdImageLine to prevent segfaults when
              performing a pattern fill */
            glCtxDrawLine (ctx, ctx->polyInts[i], y, ctx->polyInts[i + 1], y);
        }
    }

}


void glCtxDrawOpenPolygon (GLContext *ctx, GLPoint *p, int n)
{
    int i;
    int lx, ly;
    if (!n) {
        return;
    }


    lx = p->x;
    ly = p->y;
    for (i = 1; (i < n); i++)
    {
        p++;
        glCtxDrawLine (ctx, lx, ly, p->x, p->y);
        lx = p->x;
        ly = p->y;
    }

}


void glCtxDrawPolygon(GLContext *ctx, GLPoint *p, int n)
{
    if (!n)
        return;

    glCtxDrawLine(ctx, p->x, p->y, p[n - 1].x, p[n - 1].y);
    glCtxDrawOpenPolygon(ctx, p, n);
}
