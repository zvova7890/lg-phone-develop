
#if 0
#include "freetype_engine.h"
#include <dlfcn.h>


ft_font *ft_open(const char *font, uint16_t size)
{
    ft_font *ftf = malloc(sizeof(ft_font));
    if( !ftf ) return 0;


    ftf->fte = fte_open(font);
    if(!ftf->fte){
        goto release;
    }

    ftf->fti = fte_open_cache_by_metrics(ftf->fte, size);
    if(!ftf->fti)
    {
        fte_close(ftf->fte, 0);
        goto release;
    }

    return ftf;
release:
    free(ftf);
    return 0;
}


void ft_close(ft_font *f)
{
    if(!f) return;
    if(!f->fte) return;
    if(!f->fti) return;

    fte_close_cache_metrics(f->fti);
    fte_close(f->fte, 0);
    free(f);
}
#endif

