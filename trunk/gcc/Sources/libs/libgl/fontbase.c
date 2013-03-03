
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int findFontBaseEntry(const char *file);

typedef struct
{
    char *file;
    void *engine;
    unsigned int hash;
}FontBase;



struct {
    FontBase **base;
    int cnt;
    int empty_entries;
    int allocated;
}fbase;


void initFontBase()
{
    memset(&fbase, 0, sizeof(fbase));
}


unsigned int name_hash(const char* name)
{
    unsigned int hash = 0;
    unsigned int hi;
    register unsigned char c = *name++;

    while (c != '\0')
    {
        hash = (hash << 4) + c;
        hi = hash & 0xf0000000;
        hash ^= hi;
        hash ^= hi >> 24;

        c = *name++;
    }
    return hash;
}


int fbase_pushback(FontBase *f)
{
    if(fbase.allocated <= fbase.cnt) {
        fbase.allocated += 24;
        fbase.base = realloc(fbase.base, fbase.allocated * sizeof(void *));
    }


    int i = fbase.cnt++;
    fbase.base[i] = f;
    return i;
}


int newFontBaseEntry(const char *file, void *engine)
{
    if(findFontBaseEntry(file) > -1) {
        printf("Fontbase: font '%s' already exist\n", file);
        return -1;
    }

    FontBase *n = 0;
    int i;
    for(i=0; fbase.empty_entries && i<fbase.cnt; ++i)
    {
        if(!fbase.base[i]) {
            n = fbase.base[i];
            fbase.empty_entries --;
            break;
        }
    }

    if(!n) {
        n = calloc(1, sizeof *n);
        i = fbase_pushback(n);
    }

    n->engine = engine;
    n->file = strdup(file);
    n->hash = name_hash(file);

    return i;
}



void deleteFontBaseEntry(int i)
{
    if(i < 0 || i >= fbase.cnt)
        return;

    FontBase *n = fbase.base[i];

    if(n) {
        fbase.base[i] = 0;
        free(n->file);
        free(n);
        fbase.cnt --;
    }

    if(fbase.cnt < 1 && fbase.base) {
        free(fbase.base);
        fbase.base = 0;
    }
}



int findFontBaseEntry(const char *file)
{
    unsigned int hash = name_hash(file);
    int i;

    for(i=0; i<fbase.cnt; ++i) {
        if(fbase.base[i] && fbase.base[i]->hash == hash && !strcmp(fbase.base[i]->file, file)) {
            return i;
        }
    }

    return -1;
}


void deleteFontBaseFile(const char *file)
{
    int i = findFontBaseEntry(file);
    if(i > -1)
        deleteFontBaseEntry(i);
}


int getFontBaseEntrysCount()
{
    return fbase.cnt;
}


void *getFontBaseEntryEngine(int i)
{
    if(i < 0 || i >= fbase.cnt)
        return 0;

    return fbase.base[i]->engine;
}


const char *getFontBaseEntryFile(int i)
{
    if(i < 0 || i >= fbase.cnt)
        return 0;

    return fbase.base[i]->file;
}

