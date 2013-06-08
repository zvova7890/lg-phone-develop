

#ifndef __LOADER_H__
#define __LOADER_H__

#ifdef __cplusplus
extern "C" {
#endif



int execelf(const char *elfname, int argc, char *argv[], unsigned int *start, unsigned int *ret);
void ElfDestroy();

#ifdef __cplusplus
}
#endif


#endif

