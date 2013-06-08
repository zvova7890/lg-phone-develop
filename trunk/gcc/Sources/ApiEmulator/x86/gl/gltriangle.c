
#include <gl.h>




void glCtxDrawTriangle(GLContext *ctx, int x1, int y1,
                                  int x2, int y2,
                                  int x3, int y3)
{
    glCtxDrawLine(ctx, x1, y1, x2, y2);
    glCtxDrawLine(ctx, x2, y2, x3, y3);
    glCtxDrawLine(ctx, x1, y1, x3, y3);
}



/* Draw a filled triangle */
void glCtxDrawFilledTriangle(GLContext *ctx, int x1, int y1, int x2, int y2, int x3, int y3)
{
    int x, y;
    long fp_x1, fp_x2, fp_dx1, fp_dx2;

    /* sort vertices by increasing y value */
    if (y1 > y3)
    {
        if (y2 < y3)       /* y2 < y3 < y1 */
        {
            x = x1; x1 = x2; x2 = x3; x3 = x;
            y = y1; y1 = y2; y2 = y3; y3 = y;
        }
        else if (y2 > y1)  /* y3 < y1 < y2 */
        {
            x = x1; x1 = x3; x3 = x2; x2 = x;
            y = y1; y1 = y3; y3 = y2; y2 = y;
        }
        else               /* y3 <= y2 <= y1 */
        {
            x = x1; x1 = x3; x3 = x;
            y = y1; y1 = y3; y3 = y;
        }
    }
    else
    {
        if (y2 < y1)       /* y2 < y1 <= y3 */
        {
            x = x1; x1 = x2; x2 = x;
            y = y1; y1 = y2; y2 = y;
        }
        else if (y2 > y3)  /* y1 <= y3 < y2 */
        {
            x = x2; x2 = x3; x3 = x;
            y = y2; y2 = y3; y3 = y;
        }
        /* else already sorted */
    }

    if (y1 < y3)  /* draw */
    {
        fp_dx1 = ((x3 - x1) << 16) / (y3 - y1);
        fp_x1  = (x1 << 16) + (1<<15) + (fp_dx1 >> 1);

        if (y1 < y2)  /* first part */
        {
            fp_dx2 = ((x2 - x1) << 16) / (y2 - y1);
            fp_x2  = (x1 << 16) + (1<<15) + (fp_dx2 >> 1);
            for (y = y1; y < y2; y++)
            {
                glCtxDrawHLine(ctx, fp_x1 >> 16, fp_x2 >> 16, y);
                fp_x1 += fp_dx1;
                fp_x2 += fp_dx2;
            }
        }
        if (y2 < y3)  /* second part */
        {
            fp_dx2 = ((x3 - x2) << 16) / (y3 - y2);
            fp_x2 = (x2 << 16) + (1<<15) + (fp_dx2 >> 1);
            for (y = y2; y < y3; y++)
            {
                glCtxDrawHLine(ctx, fp_x1 >> 16, fp_x2 >> 16, y);
                fp_x1 += fp_dx1;
                fp_x2 += fp_dx2;
            }
        }
    }
}
