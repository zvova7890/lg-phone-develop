
#include <gl.h>




void glCtxFillRegion(GLContext *ctx, int x1, int y1, int x2, int y2, GLColor color)
{
    int x, y;

#ifndef __NO_ASM_OPTIMIZE
    switch(ctx->depth)
    {
        case 16:
        {
            GLColor depth_dep_color = rgb32ToRgb16(color);
            unsigned int double_color = (depth_dep_color << 16) | depth_dep_color;

            // if we fill all buffer, fill it with memset, it fastest then
            /*if(x1 == 0 && x2 == ctx->width) {
                memset((unsigned short *)&glGetPixel16(ctx, 0, y1), double_color, x2*(y2-y1)*2);
                return;
            }*/

#define copy_per_takt 16

            int xdiff = x2-x1;
            int max_aligned = __ALIGN_MASK(xdiff, copy_per_takt-1);

            while(max_aligned > xdiff)
                max_aligned -= copy_per_takt;

            // store of $copy_per_takt byte by instruction
            if(max_aligned < 1)
                max_aligned = 0;

            //printf("max_aligned: %d\n", max_aligned);

            for(y = y1; y < y2; ++y) {

                unsigned short *start_s = (unsigned short *)&glGetPixel16(ctx, x1, y);
                unsigned short *end_ss = ((unsigned short*)start_s) + (xdiff);

                if(!max_aligned) {
                    while(start_s < end_ss)
                        *start_s++ = depth_dep_color;
                    continue;
                }


                unsigned short *aligned_start_s = (unsigned short *)__ALIGN_MASK((unsigned long)start_s, copy_per_takt-1);
                unsigned short *end_s = aligned_start_s + max_aligned;

                while(end_s > end_ss) {
                    max_aligned -= copy_per_takt;
                    end_s = aligned_start_s + max_aligned;
                }

                while(start_s < aligned_start_s/* && start_s < end_ss*/)
                    *start_s++ = depth_dep_color;

                //if(aligned_start_s < end_s)
                {
                    asm volatile
                    (
#if copy_per_takt == 16
                        "mov   r4, %2 \n"
                        "mov   r5, %2 \n"
                        "mov   r6, %2 \n"
                        "lock: \n"
                        "stmia %0!, {%2,r4-r6}\n"
                        "cmp   %0, %1\n"
                        "bcc   lock\n"
                        ::"r"(aligned_start_s), "r"(end_s), "r"(double_color)
                        :"r4", "r5", "r6"
#elif copy_per_takt == 8
                        "mov   r4, %2 \n"
                        "lock: \n"
                        "stmia %0!, {%2, r4}\n"
                        "cmp   %0, %1\n"
                        "bcc   lock\n"
                        ::"r"(aligned_start_s), "r"(end_s), "r"(double_color)
                        :"r4"
#else
#error not supported
#endif

                    );
                }


                while(end_s < end_ss)
                    *end_s++ = depth_dep_color;
            }

            break;
        }

        case 32:
            for(y = y1; y < y2; ++y)
                for(x = x1; x < x2; ++x)
                    glPutPixel32c(ctx, x, y, color);
            break;
    }
#else

    switch(ctx->depth)
    {
        case 16:
	{
	    GLColor depth_dep_color = rgb32ToRgb16(color);
            for(y = y1; y < y2; ++y)
                for(x = x1; x < x2; ++x)
                    glPutPixel16c(ctx, x, y, depth_dep_color);
            break;
	}

        case 32:
            for(y = y1; y < y2; ++y)
                for(x = x1; x < x2; ++x)
                    glPutPixel32c(ctx, x, y, color);
            break;
    }

#endif
}


