
#include <gl.h>
#include <math.h>



void glCtxDrawFilledCircle(GLContext *ctx, int circlePosX, int circlePosY, int radius)
{
    glPixelSetProc setPixel = ctx->setPixel;
    const int FULL = (1 << 2);
    const int HALF = (FULL >> 1);

    int circleDiameter = radius*2;
    int size = (circleDiameter << 2);// fixed point value for size
    int ray = (size >> 1);
    int dY2;
    int ray2 = ray * ray;
    int posmin,posmax;
    int Y,X;
    int x = ((circleDiameter&1)==1) ? ray : ray - HALF;
    int y = HALF;
    circlePosX -= (circleDiameter>>1);
    circlePosY -= (circleDiameter>>1);

    for (;; y+=FULL)
    {
        dY2 = (ray - y) * (ray - y);

        for (;; x-=FULL)
        {
            if (dY2 + (ray - x) * (ray - x) <= ray2) continue;

            if (x < y)
            {
                Y = (y >> 2);
                posmin = Y;
                posmax = circleDiameter - Y + 1;

                // Draw inside square and leave
                while (Y < posmax)
                {
                    for (X = posmin; X < posmax; X++)
                        setPixel(ctx, circlePosX+X, circlePosY+Y);
                    Y++;
                }

                return;
            }

            // Draw the 4 borders
            X = (x >> 2);
            Y = (y >> 2);
            posmax = circleDiameter - X;
            int mirrorY = circleDiameter - Y;

            while (X < posmax)
            {
                setPixel(ctx, circlePosX+X, circlePosY+Y);
                setPixel(ctx, circlePosX+X, circlePosY+mirrorY);
                setPixel(ctx, circlePosX+Y, circlePosY+X);
                setPixel(ctx, circlePosX+mirrorY, circlePosY+X);
                X++;
            }

            break;
        }
    }
}



void glCtxDrawCircle(GLContext *ctx, int x, int y, int r)
{
    int f = 1 - r;
    int ddfx = 1;
    int ddfy = -2 * r;
    int xp = 0;
    int yp = r;

    glPixelSetProc pixel = ctx->setPixel;

    /* Draw outer points. */

    pixel(ctx, x, y + r);
    pixel(ctx, x, y - r);
    pixel(ctx, x + r, y);
    pixel(ctx, x - r, y);

    /* Calculate coordinates of points in one octant. */

    while(xp < yp)
    {
        /* ddfx == 2 * xp + 1;
           ddfy == -2 * yp;
           f == xp*xp + yp*yp - r*r + 2*xp - yp + 1; */
        if(f >= 0)
        {
            yp--;
            ddfy += 2;
            f += ddfy;
        }

        xp++;
        ddfx += 2;
        f += ddfx;



        /* Draw pixels in all octants. */
        pixel(ctx, x + xp, y + yp);
        pixel(ctx, x + xp, y - yp);
        pixel(ctx, x - xp, y + yp);
        pixel(ctx, x - xp, y - yp);
        pixel(ctx, x + yp, y + xp);
        pixel(ctx, x + yp, y - xp);
        pixel(ctx, x - yp, y + xp);
        pixel(ctx, x - yp, y - xp);
    }
}
