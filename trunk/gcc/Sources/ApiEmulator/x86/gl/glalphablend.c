
#include <gl.h>

#if 0

GLColor _glAlphaBlend(GLColor color, GLColor background, unsigned char alpha)
{
    /*if(alpha == 0xFF)
        return color;*/

    unsigned char a = glColorAlpha(background);
    unsigned char alpha2 = 0xff - alpha;
    unsigned int r = (glColorRed(color) * alpha + (glColorRed(background) * alpha2) ) >> 8;
    unsigned int g = (glColorGreen(color) * alpha + (glColorGreen(background) * alpha2) ) >> 8;
    unsigned int b = (glColorBlue(color) * alpha + (glColorBlue(background) * alpha2) ) >> 8;

    return glRgb32(r, g, b, a);
}



unsigned short _glAlphaBlend16(GLColor color, unsigned short background, unsigned char alpha)
{
    /*if(alpha == 0xFF)
        return rgb32ToRgb16(color);*/

    unsigned char alpha2 = 0xff - alpha;

    unsigned char r = (glColorRed(color) * alpha + (glColorRed16(background) * alpha2) ) >> 8;
    unsigned char g = (glColorGreen(color) * alpha + (glColorGreen16(background) * alpha2) ) >> 8;
    unsigned char b = (glColorBlue(color) * alpha + (glColorBlue16(background) * alpha2) ) >> 8;

    return glRgb16(r, g, b);
}


unsigned short _glAlphaBlend16c(unsigned short color, unsigned short background, unsigned char alpha)
{
    /*if(alpha == 0xFF)
        return color;*/

    unsigned char alpha2 = 0xff - alpha;

    unsigned char r = (glColorRed16(color) * alpha + (glColorRed16(background) * alpha2) ) >> 8;
    unsigned char g = (glColorGreen16(color) * alpha + (glColorGreen16(background) * alpha2) ) >> 8;
    unsigned char b = (glColorBlue16(color) * alpha + (glColorBlue16(background) * alpha2) ) >> 8;

    return glRgb16(r, g, b);
}

#endif

