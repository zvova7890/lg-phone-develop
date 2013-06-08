
#include <stdio.h>
#include <string.h>

#include "freetype_engine.h"
#include "gl.h"

#include <unistd.h>
#include <dlfcn.h>


//#include <loader.h>
#ifdef __SYSTEM_FONT__
#include <Api/ApiLinkLib/ApiLink.h>
#endif

//#define __linux


int newFontBaseEntry(const char *file, void *engine);
void deleteFontBaseEntry(int i);
void deleteFontBaseFile(const char *file);
int findFontBaseEntry(const char *file);
int getFontBaseEntrysCount();
void *getFontBaseEntryEngine(int i);
const char *getFontBaseEntryFile(int i);


static const char *accepted_libs[4] = {"libft.so", "libft-2.4.6-1.so", "libft-2.4.11-1.so", "libfreetype.so"};
static char _initialized = 0, _error_one_show = 1;



#ifdef __linux
#define loader_dlsym dlsym
#define loader_dlclose dlclose
static void *freetype_dlhandle = 0;
#else
static int freetype_dlhandle = -1;
#endif


FT_Error (*_FT_Init_FreeType)( FT_Library  *alibrary ) = 0;
FT_Error (*_FT_Done_Face)( FT_Face  face ) = 0;

FT_Error (*_FT_Set_Pixel_Sizes)( FT_Face  face,
                      FT_UInt  pixel_width,
                      FT_UInt  pixel_height ) = 0;

FT_Error (*_FT_Load_Char)( FT_Face   face,
                FT_ULong  char_code,
                FT_Int32  load_flags ) = 0;

FT_Error (*_FT_Done_FreeType)( FT_Library  library ) = 0;

FT_Error (*_FT_New_Face)( FT_Library   library,
               const char*  filepathname,
               FT_Long      face_index,
               FT_Face     *aface ) = 0;






int init_freetype()
{
#ifdef __linux
    void *hd = 0;
#else
    int hd = -1;
#endif

    for(unsigned int i=0; i<sizeof(accepted_libs)/sizeof(void*); ++i) {
#ifdef __linux
        printf("try open: %s\n", accepted_libs[i]);
        hd = dlopen(accepted_libs[i], RTLD_NOW);
        if(hd)
            break;
#else
        hd = loader_dlopen(accepted_libs[i]);
        if(hd > -1)
            break;
#endif

    }

#ifndef __linux
    if(hd < 0) {
#else
    if(!hd) {
#endif
        if(_error_one_show) {
            printf("Can`t initialize freetype library. Fonts be invisible\n");
            _error_one_show = 0;
        }
        return -1;
    }



    _FT_Init_FreeType = (void*)loader_dlsym(hd, "FT_Init_FreeType");
    _FT_New_Face = (void*)loader_dlsym(hd, "FT_New_Face");
    _FT_Set_Pixel_Sizes = (void*)loader_dlsym(hd, "FT_Set_Pixel_Sizes");
    _FT_Load_Char = (void*)loader_dlsym(hd, "FT_Load_Char");
    _FT_Done_Face = (void*)loader_dlsym(hd, "FT_Done_Face");
    _FT_Done_FreeType = (void*)loader_dlsym(hd, "FT_Done_FreeType");


    if( !_FT_Init_FreeType ||
        !_FT_New_Face ||
        !_FT_Set_Pixel_Sizes ||
        !_FT_Load_Char ||
        !_FT_Done_Face ||
        !_FT_Done_FreeType )
    {
        printf("Freetype opened, but can`t resolve some symbols. May be incorrect version?\n");
        loader_dlclose(hd);
        return -1;
    }

    freetype_dlhandle = hd;
    _initialized = 1;
    return 0;
}


void fini_freetype()
{
    loader_dlclose(freetype_dlhandle);
#ifdef __linux
    freetype_dlhandle = 0;
#else
    freetype_dlhandle = -1;
#endif
    _initialized = 0;
}


__attribute__((visibility ("hidden")))
void fte_cleanMap()
{
    int i, s = getFontBaseEntrysCount();
    for(i = 0; i<s; ++i)
    {
        ft_engine * fte = (ft_engine *)getFontBaseEntryEngine(i);
        if(fte)
            fte_close(fte, 1);

        //deleteFontBaseEntry(i);
    }
}



__attribute__((visibility ("hidden")))
char fte_isexist(const char *name)
{
    const char *env = getenv("FONTS");
    if(!env)
        return 0;

    char str[512];
    sprintf(str, "%s%s", env, name);

    FILE *f = fopen(str, "r");
    if(!f) return 0;
    fclose(f);
    return 1;
}


ft_engine * fte_open(const char *file)
{
    if(_initialized == 0 && init_freetype())
        return 0;

    ft_engine *cfte = 0;
    int i = findFontBaseEntry(file);
    if(i > -1)
        cfte = (ft_engine *)getFontBaseEntryEngine(i);

    if(cfte) {
        cfte->clients++;
        return cfte;
    }

    if(!fte_isexist(file)) return 0;

    const char *env = getenv("FONTS");
    if(!env)
        return 0;

    char path[512];
    sprintf(path, "%s%s", env, file);

    ft_engine * fte = (ft_engine *)calloc(1, sizeof(ft_engine));
    if(!fte) {
        printf("calloc failed\n");
        return 0;
    }

    fte->clients = 1;
    fte->flags = FT_LOAD_RENDER | FT_LOAD_FORCE_AUTOHINT/* FT_FACE_FLAG_HINTER */| FT_RENDER_MODE_LCD_V;
    fte->error = _FT_Init_FreeType(&fte->library);
    fte->font_cnt = 0;
    if(fte->error) {
        printf("Can`t init freetype library\n");
        goto err;
    }

    fte->error = _FT_New_Face(fte->library, path, 0, &fte->face);
    if ( fte->error == FT_Err_Unknown_File_Format )
    {
        printf("Unknown font format!\n");
        goto err;
    }
    else if ( fte->error )
    {
        printf("Can`t open font! err code: %d\n", fte->error);
        goto err;
    }

    i = newFontBaseEntry(file, fte);
    fte->file = getFontBaseEntryFile(i);

    return fte;
err:
    _FT_Done_Face(fte->face);
    _FT_Done_FreeType(fte->library);
    free(fte);
    printf("fuck(\n");
    return 0;
}


void fte_close(ft_engine *fte, int clean_now)
{
    if(!_initialized)
        return;

    if(!fte)
        return;

    if(fte->clients > 1) {
        fte->clients--;
        return;
    }

    if(!clean_now)
        return;

    fte_clear_cache(fte);

    _FT_Done_Face(fte->face);
    _FT_Done_FreeType(fte->library);

    deleteFontBaseFile(fte->file);
    free(fte);
}



int fte_cache_symbol(fte_info *fti, unsigned int letter)
{
    if(!_initialized)
        return -3;

    if( fti ) {
        if( fti->symbols_cnt > letter && fti->symbols[letter] ) {
            return 1;
        }
    }
    else
        return -1;

    ft_engine *fte = (ft_engine*)fti->fte;
    _FT_Set_Pixel_Sizes( fte->face, fti->w, fti->h );
    fte->error = _FT_Load_Char( fte->face, letter, fte->flags );
    if(fte->error) {
        return -3;
    }

    if(fti->symbols_cnt <= letter)
        fti->symbols = (fte_symbol **)realloc(fti->symbols, (letter+1)*sizeof(void*));

    for(; fti->symbols_cnt < letter+1; fti->symbols_cnt++)
        fti->symbols[fti->symbols_cnt] = 0;

    fti->symbols[letter] = (fte_symbol *)malloc(sizeof(fte_symbol));
    if(!fti->symbols[letter])
        return -1;

    fte_symbol *symb = fti->symbols[letter];
/*
    TGlyphInfo glyph_info;
    GrFont_GetGlyphInfo(fti->h, letter, &glyph_info);

    symb->width = glyph_info.Width;
    symb->height = glyph_info.Height;
    symb->top = glyph_info.Top;
    symb->left = glyph_info.Left;
    symb->xadvance = glyph_info.xAdvance;
    symb->yadvance = glyph_info.yAdvance;
    uint32_t bmlen = symb->width * symb->height;

    printf("width: %d\n", symb->width);
    printf("height: %d\n", symb->height);
    printf("top: %d\n", symb->top);
    printf("left: %d\n", symb->left);
    printf("xadvance: %d\n", symb->xadvance);
    printf("yadvance: %d\n", symb->yadvance);
    printf("bmlen: %d\n", bmlen);
    printf("pBuffer: %X\n", glyph_info.pBuffer);

    if(bmlen > 0) {
        symb->bitmap = glyph_info.pBuffer;
        //symb->bitmap = (uint8_t*)malloc(bmlen);
        //memcpy(symb->bitmap, glyph_info.pBuffer, bmlen);
    } else {
        symb->bitmap = 0;
    }
*/
    fte->slot = fte->face->glyph;

    symb->width = fte->slot->bitmap.width;
    symb->height = fte->slot->bitmap.rows;
    symb->top = fte->slot->bitmap_top;
    symb->left = fte->slot->bitmap_left;

    symb->xadvance = fte->slot->advance.x >> 6;
    symb->yadvance = fte->slot->advance.y >> 6;
    uint32_t bmlen = symb->width * symb->height;

    if(bmlen > 0) {
        symb->bitmap = (uint8_t*)malloc(bmlen);
        if(!symb->bitmap)
            return -1;

        memcpy(symb->bitmap, fte->slot->bitmap.buffer, bmlen);
    } else {
        symb->bitmap = 0;
    }

    return 0;
}


fte_symbol *fte_get_symbol(fte_info *fti, unsigned long letter)
{
    if(!_initialized)
        return 0;

    if( !fti ) return 0;
    if(fte_cache_symbol(fti, letter) < 0) return 0;
    return fti->symbols[letter];
}



const char *fte_get_name(ft_engine *fte)
{
    if(!_initialized)
        return 0;

    if( !fte ) return 0;
    return fte->file;
}


int fte_clear_cache_by_metrics(fte_info *fti)
{
    if(!_initialized)
        return -3;

    if(!fti) return -1;

    fte_info *fi = fti;

    if(fi->clients > 0)
        return -2;

    int clened = 0;
    int inf_size = fi->symbols_cnt;
    int c;
    for(c = 0; c < inf_size; ++c)
    {
        fte_symbol *symb = fi->symbols[c];
        if(!symb) continue;
        clened += symb->width*symb->height;

        if(symb->bitmap)
            free( symb->bitmap );

        free( symb );
    }

    if(fi->symbols_cnt > 0)
        free(fi->symbols);
    fi->symbols = 0;
    fi->symbols_cnt = 0;

    ft_engine *fte = (ft_engine*)fti->fte;
    fte->font_map[fti->w] = 0;
    free(fi);
    return clened;
}


int fte_clear_cache(ft_engine *fte)
{
    if(!_initialized)
        return -3;

    char no_clen_map = 0;
    int size = fte->font_cnt;
    int i;
    for(i = 0; i <size; ++i) {

        if(fte->font_map[i] && fte_clear_cache_by_metrics(fte->font_map[i]) == -2 ) {
            no_clen_map = 1;
        }
    }

    if(!no_clen_map) {
        free(fte->font_map);
        fte->font_map = 0;
        fte->font_cnt = 0;
    }
    return 0;
}


fte_info *fte_open_cache_by_metrics(ft_engine *fte, unsigned int size)
{
    if(!_initialized)
        return 0;

    if( !fte )
        return 0;

    if( fte->font_cnt <= size || !fte->font_map[size] )
    {
        printf("fte_open_cache_by_metrics: %d\n", size);

        if(fte->font_cnt <= size)
            fte->font_map = (fte_info **)realloc(fte->font_map, (size+1)*sizeof(void*));

        for(; fte->font_cnt < size+1; fte->font_cnt++)
            fte->font_map[fte->font_cnt] = 0;

        fte->font_map[size] = (fte_info *)calloc(1, sizeof(fte_info));
        if(!fte->font_map[size])
            return 0;

        fte->font_map[size]->clients = 0;
        fte->font_map[size]->h = size;
        fte->font_map[size]->w = size;
        fte->font_map[size]->fte = (void*)fte;
    }

    fte->font_map[size]->clients++;
    return fte->font_map[size];
}


int fte_close_cache_metrics(fte_info *fti)
{
    if(!_initialized)
        return -3;

    if( !fti ) return -1;
    fti->clients--;
    return 0;
}


FT_Library fte_library_handler(ft_engine *fte)
{
    return fte->library;
}


FT_Face fte_face_handler(ft_engine *fte)
{
    return fte->face;
}


void fte_set_flags(ft_engine *fte, FT_Int32 flag)
{
    fte->flags = flag;
}


FT_Int32 fte_flags(ft_engine *fte)
{
    return fte->flags;
}

