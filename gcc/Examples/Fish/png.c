

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <stdint.h>
#include <png.h>
#include "png.h"


static inline uint32_t rgb16ToRgb32(uint16_t c) {
    return 0xff000000
        | ((((c) << 3) & 0xf8) | (((c) >> 2) & 0x7))
        | ((((c) << 5) & 0xfc00) | (((c) >> 1) & 0x300))
        | ((((c) << 8) & 0xf80000) | (((c) << 3) & 0x70000));
}

unsigned int pixel32(image_t *img, int w, int h)
{
    if(w < 0 || h < 0 || w >= img->w || h >= img->h)
        return 0;

    switch(img->bit)
    {
        case 32:
        {
            unsigned int *bitmap = img->bitmap;
            return bitmap[img->w * h + w];
        }

        case 16:
        {
            unsigned short *bitmap = img->bitmap;
            return rgb16ToRgb32(bitmap[img->w * h + w]);
        }
    }
}


int save_png_to_file (image_t *bitmap, const char *path)
{
    FILE * fp;
    png_structp png_ptr = NULL;
    png_infop info_ptr = NULL;
    size_t x, y;
    png_byte ** row_pointers = NULL;
    /* "status" contains the return value of this function. At first
       it is set to a value which means 'failure'. When the routine
       has finished its work, it is set to a value which means
       'success'. */
    int status = -1;
    /* The following number is set by trial and error only. I cannot
       see where it it is documented in the libpng manual.
    */
    int pixel_size = 3;
    int depth = 8;

    fp = fopen (path, "w+");
    if (! fp) {
        return -1;
    }


    png_ptr = png_create_write_struct (PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (png_ptr == NULL) {
        status = -2;
        goto png_create_write_struct_failed;
    }


    info_ptr = png_create_info_struct (png_ptr);
    if (info_ptr == NULL) {
        status = -3;
        goto png_create_info_struct_failed;
    }

    /* Set up error handling. */

    /*if (setjmp (png_jmpbuf (png_ptr))) {
        goto png_failure;
    }*/

    /* Set image attributes. */


    png_set_IHDR (png_ptr,
                  info_ptr,
                  bitmap->w,
                  bitmap->h,
                  depth,
                  PNG_COLOR_TYPE_RGB,
                  PNG_INTERLACE_NONE,
                  PNG_COMPRESSION_TYPE_DEFAULT,
                  PNG_FILTER_TYPE_DEFAULT);

    /* Initialize rows of PNG. */


    row_pointers = png_malloc (png_ptr, bitmap->h * sizeof (png_byte *));
    for (y = 0; y < bitmap->h; ++y) {
        png_byte *row = png_malloc (png_ptr, sizeof (uint8_t) * bitmap->w * pixel_size);
        row_pointers[y] = row;
        for (x = 0; x < bitmap->w; ++x) {
            uint32_t pixel = pixel32 (bitmap, x, y);

            *row++ = pixel >> 16 & 0xff;
            *row++ = pixel >> 8 & 0xff;
            *row++ = pixel & 0xff;
        }
    }

    /* Write the image data to "fp". */

    png_init_io (png_ptr, fp);
    png_set_rows (png_ptr, info_ptr, row_pointers);
    png_write_png (png_ptr, info_ptr, PNG_TRANSFORM_IDENTITY, NULL);

    /* The routine has successfully written the file, so we set
       "status" to a value which indicates success. */

    status = 0;

    for (y = 0; y < bitmap->h; y++) {
        png_free (png_ptr, row_pointers[y]);
    }
    png_free (png_ptr, row_pointers);


 png_failure:
 png_create_info_struct_failed:
    png_destroy_write_struct (&png_ptr, &info_ptr);

 png_create_write_struct_failed:
    fclose (fp);

    return status;
}


