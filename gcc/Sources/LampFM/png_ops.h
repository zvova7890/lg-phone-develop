

#ifndef __PNG_H__
#define __PNG_H__

#include <gl.h>


typedef struct
{

    unsigned short w, h, bit;
    void *bitmap;
}image_t;

#ifdef __cplusplus
extern "C" {
#endif


static inline void drawImage(int x, int y, const image_t *image)
{
    if(image)
        glDrawBitmap(x, y, image->w, image->h, image->bit, image->bitmap);
}



int save_png_to_file (image_t *bitmap, const char *path);
image_t* load_png(const char *fname, int type);


#ifdef __cplusplus
}
#endif

#endif
