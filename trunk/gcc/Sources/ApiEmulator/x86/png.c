

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <stdint.h>
#include <png.h>
#include <fs.h>
#include "png_ops.h"



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
    return -1;
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


 //png_failure:
 png_create_info_struct_failed:
    png_destroy_write_struct (&png_ptr, &info_ptr);

 png_create_write_struct_failed:
    fclose (fp);

    return status;
}




/*********************************************************************/


#define PNG_8 1
#define PNG_16 2
#define PNG_24 3

#define PNG_1 0xFF

#define number 8


void* xmalloc(int x,int n)
{
    ((void)x);
    return malloc(n);
}

void xmfree(int x,void* ptr)
{
    ((void)x);
    free(ptr);
}


void read_data_fn(png_structp png_ptr, png_bytep data, png_size_t length)
{
    int f;
    f=(int)png_get_io_ptr(png_ptr);
    fs_read(f, data, length);
}


image_t* load_png(const char *fname, int type)
{
    int f;
    char buf[number];

    struct PP
    {
        unsigned char *row;
        unsigned char *img;
        image_t * img_h;
    } pp;

    image_t * img_hc;
    png_structp png_ptr=NULL;
    png_infop info_ptr=NULL;
    png_uint_32 rowbytes;

    if ((f=fs_open(fname, FILE_OPEN_READ)) < 0)
        return 0;

    pp.row=NULL;
    pp.img=NULL;
    pp.img_h=NULL;

    if (fs_read(f, &buf, number)!=number)
        goto L_CLOSE_FILE;

    if  (!png_check_sig((png_bytep)buf,number))
        goto  L_CLOSE_FILE;

    png_ptr = png_create_read_struct_2(PNG_LIBPNG_VER_STRING, (png_voidp)0, 0, 0, (png_voidp)0,(png_malloc_ptr)xmalloc,(png_free_ptr)xmfree);
    if (!png_ptr) goto L_CLOSE_FILE;

    info_ptr = (png_infop)png_create_info_struct(png_ptr);
    if (!info_ptr)
    {
        png_destroy_read_struct(&png_ptr, (png_infopp)NULL, (png_infopp)NULL);
        goto L_CLOSE_FILE;
    }

    /*  if (setjmp(png_jmpbuf(png_ptr)))
      {
        png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp)NULL);
        goto L_CLOSE_FILE;
      }
    */

    png_set_read_fn(png_ptr, (void *)f, read_data_fn);

    png_set_sig_bytes(png_ptr, number);

    png_read_info(png_ptr, info_ptr);

    png_uint_32 width, height;
    int bit_depth, color_type;

    png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth, &color_type, 0, 0, 0);

    if (type==0)
    {
        if (color_type == PNG_COLOR_TYPE_GRAY)
            type=PNG_1;
        else type = PNG_24;
    }

    if (bit_depth < 8) png_set_gray_1_2_4_to_8(png_ptr);

    if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS))
        png_set_tRNS_to_alpha(png_ptr);

    if (bit_depth == 16) png_set_strip_16(png_ptr);

    if (bit_depth < 8) png_set_packing(png_ptr);

    if (color_type == PNG_COLOR_TYPE_PALETTE)
        png_set_palette_to_rgb(png_ptr);

    if (color_type == PNG_COLOR_TYPE_GRAY_ALPHA || color_type == PNG_COLOR_TYPE_GRAY)
        png_set_gray_to_rgb(png_ptr);

    png_set_filler(png_ptr,0xFF,PNG_FILLER_AFTER);
    png_read_update_info(png_ptr, info_ptr);

    rowbytes = png_get_rowbytes(png_ptr, info_ptr);

    pp.row = (unsigned char *)malloc(rowbytes);
    pp.img_h = img_hc = (image_t*)malloc(sizeof(image_t));

    if (type == PNG_1)
    {
        int rowc_w=(width+7)>>3;
        int size=height*rowc_w;
        unsigned char *iimg=(unsigned char *)(pp.img = (unsigned char *)malloc(size));
        memset(iimg, 0, size);

        for (unsigned int y = 0; y<height; ++y)
        {
            png_read_row(png_ptr, (png_bytep)pp.row, NULL);
            for (unsigned int x = 0; x<width; x++)
            {
                if (!pp.row[x*4+0] && !pp.row[x*4+1] && !pp.row[x*4+2])
                    iimg[x>>3]|=(0x80>>(x&7));
            }
            iimg+=rowc_w;
        }
        pp.img_h->bit = 1;
    }
    else
    {
        switch (type)
        {
        case PNG_8:
        {
            unsigned char *iimg=(unsigned char *)(pp.img = (unsigned char *)malloc(width*height));
            for (unsigned int y = 0; y<height; ++y)
            {
                png_read_row(png_ptr, (png_bytep)pp.row, NULL);
                for (unsigned int x = 0; x<width; ++x)
                {
                    if (pp.row[x*4+3] < 255)
                        *iimg++=0xC0;
                    else
                    {
                        unsigned char c=(pp.row[x*4+0] & 0xE0);
                        c|=((pp.row[x*4+1]>>3)&0x1C);
                        c|=((pp.row[x*4+2]>>6)&0x3);
                        *iimg++=c;
                    }
                }
            }
            pp.img_h->bit = 8;
            break;
        }
        case PNG_16:
        {
            unsigned short *iimg=(unsigned short *)(pp.img = (unsigned char*)malloc(width*height*2));
            for (unsigned int y = 0; y<height; ++y)
            {
                png_read_row(png_ptr, (png_bytep)pp.row, NULL);
                for (unsigned int x = 0; x<width; ++x)
                {
                    if (pp.row[x*4+3] < 255)
                        *iimg++=0xE000;
                    else
                    {
                        unsigned int c=((pp.row[x*4+0]<<8)&0xF800);
                        c|=((pp.row[x*4+1]<<3)&0x7E0);
                        c|=((pp.row[x*4+2]>>3)&0x1F);
                        *iimg++=c;
                    }
                }
            }
            pp.img_h->bit = 16;
            break;
        }
//#if NEWSGOLD || X75
        case PNG_24:
        {
            unsigned char *iimg=(unsigned char *)(pp.img = (unsigned char *)malloc((width*height)<<2));
            for (unsigned int y = 0; y<height; ++y)
            {
                png_read_row(png_ptr, (png_bytep)pp.row, NULL);
                for (unsigned int x = 0; x<width; ++x)
                {
                    unsigned int c;
                    *iimg++=pp.row[x*4+2];
                    *iimg++=pp.row[x*4+1];
                    *iimg++=pp.row[x*4+0];
                    c=pp.row[x*4+3];
//	    if (c>=128) c++;
//	    c*=100;
//	    c>>=8;
                    *iimg++=c;//(pp.row[x*4+3]*100)/0xFF;
                }
            }
            pp.img_h->bit = 32;
            break;
        }
//#endif
        }
    }
    pp.img_h->w=width;
    pp.img_h->h=height;
    //pp->img_h->zero=0;
    pp.img_h->bitmap=pp.img;

    png_read_end(png_ptr, info_ptr);
    png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp)NULL);
    if (!pp.img)
    {
L_CLOSE_FILE:
        free(pp.row);
        free(pp.img);
        free(pp.img_h);
        fs_close(f);
        return NULL;
    }

    free(pp.row);
    fs_close(f);
    return (img_hc);
}
