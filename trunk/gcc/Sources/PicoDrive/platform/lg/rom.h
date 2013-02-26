
#ifndef __ROM_H__
#define __ROM_H__



int PicoDriveInit();
int PicoDriveLoadRom(const char *);
int PicoDriveDeinit();
void PicoDriveFrame(int skeep);




#endif

