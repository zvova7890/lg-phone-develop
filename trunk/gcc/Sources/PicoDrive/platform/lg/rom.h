
#ifndef __ROM_H__
#define __ROM_H__



int PicoDriveInit();
int PicoDriveLoadRom(const char *);
int PicoDriveDeinit();
void PicoDriveFrame(int skeep);


int PicoSaveLoadGame(int load, int sram, const char *file);



#endif

