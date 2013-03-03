
#include <gl.h>
#include <math.h>
#include <stdio.h>



extern int gdCosT[];
extern int gdSinT[];




void glCtxDrawFilledArc (GLContext *ctx, int cx, int cy, int w, int h, int s, int e, int style)
{
  GLPoint pts[3];
  int i;
  int lx = 0, ly = 0;
  int fx = 0, fy = 0;
  while (e < s)
  {
      e += 360;
  }

  for (i = s; (i <= e); i++)
  {
      int x, y;
      x = ((long) gdCosT[i % 360] * (long) w / (2 * 1024)) + cx;
      y = ((long) gdSinT[i % 360] * (long) h / (2 * 1024)) + cy;
      if (i != s)
      {
        if (!(style & GL_CHORD))
        {
          if (style & GL_NO_FILL)
          {
            glCtxDrawLine(ctx, lx, ly, x, y);
          }
          else
          {
              /* This is expensive! */
              pts[0].x = lx;
              pts[0].y = ly;
              pts[1].x = x;
              pts[1].y = y;
              pts[2].x = cx;
              pts[2].y = cy;
              glCtxDrawFilledPolygon (ctx, pts, 3);
          }
        }
      }
      else
      {
          fx = x;
          fy = y;
      }
      lx = x;
      ly = y;
  }

  if (style & GL_CHORD)
    {
      if (style & GL_NO_FILL)
    {
      if (style & GL_EDGED)
        {
          glCtxDrawLine (ctx, cx, cy, lx, ly);
          glCtxDrawLine (ctx, cx, cy, fx, fy);
        }
      glCtxDrawLine (ctx, fx, fy, lx, ly);
    }
      else
    {
      pts[0].x = fx;
      pts[0].y = fy;
      pts[1].x = lx;
      pts[1].y = ly;
      pts[2].x = cx;
      pts[2].y = cy;
      glCtxDrawFilledPolygon(ctx, pts, 3);
    }
    }
  else
    {
      if (style & GL_NO_FILL)
    {
      if (style & GL_EDGED)
        {
          glCtxDrawLine (ctx, cx, cy, lx, ly);
          glCtxDrawLine (ctx, cx, cy, fx, fy);
        }
    }
    }
}




void glCtxDrawArc (GLContext *ctx, int cx, int cy, int w, int h, int s, int e)
{
    glCtxDrawFilledArc(ctx, cx, cy, w, h, s, e, GL_NO_FILL);
}

