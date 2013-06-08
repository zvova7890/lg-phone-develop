 
#ifndef __GRSYS_H__
#define __GRSYS_H__

#ifdef __cplusplus
extern "C" {
#endif


void *Graphics_GetScreenBuffer();
unsigned short Graphics_GetScreenWidth();
unsigned short Graphics_GetScreenHeight();
unsigned char Graphics_GetScreenDepth();


static inline void *GrSys_GetGrBuf() {
  return Graphics_GetScreenBuffer();
}



int GrSys_GetGDIID();
void GrSys_SelectGDI(int);
void GrSys_Refresh();



#define GRSYS_WIDTH Graphics_GetScreenWidth()
#define GRSYS_HEIGHT Graphics_GetScreenHeight()



#ifdef __cplusplus
}
#endif

#endif
