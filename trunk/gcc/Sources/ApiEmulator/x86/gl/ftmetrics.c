
#include <gl.h>



uint32_t ftStringMetrics(fte_info *fti, const void *str, ft_metrics *metr, int32_t max_width, int32_t max_leter_cnt,
                         int flags, wchar_t (*conv)(const void **))
{
    static wchar_t breakers[] = {L' ', L',', L'.', L'='};

    int32_t w = 0, h = 0;
    int t = 0;
    int chars = 0;
    int chars_last_break = 0;
    const void *str_last_break = 0;
    int errs = 0;
    wchar_t smb = conv(&str);
    //w -= fte_get_symbol(ftf->fti, smb)->left;

    while(smb && max_leter_cnt > 0)
    {
        if(flags & FT_TEXT_CRBREAK && smb == '\n')
            break;

        if(flags & FT_TEXT_SENTENCEBREAK) {

            for(int i=0; i < (sizeof(breakers)/sizeof(breakers[0])); ++i)
            {
                if(smb == breakers[i]) {
                    str_last_break = str;
                    chars_last_break = chars;
                }
            }
        }

        fte_symbol *fte = fte_get_symbol(fti, smb);
        if(!fte) {
            ++errs;
            continue;
        }

        if(max_width > 0 && w+fte->xadvance >= max_width)
            break; // CHECKME

        w += fte->xadvance;

        if(t < fte->height - fte->top) {
            t = fte->height - fte->top;
        }

        if((int)h < fte->height)
            h = fte->height;
        smb = conv(&str);
        --max_leter_cnt;

        ++chars;
    }

    if(metr) {
        metr->str = str;
        metr->height = h;
        metr->width = w;
        metr->top = t;
        metr->strend = smb == 0;
        metr->charscount = chars;
        metr->last_breaked_char_pos = str_last_break;
        metr->last_breaked_char = chars_last_break;
    }

    return w == 0 && errs? -1 : w;
}



