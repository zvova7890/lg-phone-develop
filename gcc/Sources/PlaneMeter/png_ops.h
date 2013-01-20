

#ifndef __PNG_H__
#define __PNG_H__




typedef struct
{
    short w, h, bit;
    void *bitmap;
}image_t;




int save_png_to_file (image_t *bitmap, const char *path);
image_t* load_png(const char *fname, int type);


#endif
