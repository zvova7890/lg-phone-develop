
#include <stdio.h>
#include <string.h>
#include "../../Pico/PicoInt.h"



unsigned char *framebuff = NULL;
char romFileName[256] = "";
int initialized = 0;


void *getFrameBuffer();

int RomLoad(const char *RomName);
void RomFree();




static int EmuScan16(unsigned int num, void *sdata)
{
    DrawLineDest = (unsigned short *)framebuff + 400*(num+1)+(400-320-1);
    return 0;
}


void emu_write_sound()
{

}


int PicoDriveInit()
{
    framebuff = getFrameBuffer();

    PicoDrawSetColorFormat(1);
    PicoScan = EmuScan16;

    if(PicoInit())
        return -1;

    PicoWriteSound = emu_write_sound;
    return 0;
}



int PicoDriveLoadRom(const char *romfile)
{
    strcpy(romFileName, romfile);
    int ret;

    if(RomLoad(romFileName)) {
        printf("failed to load rom\n");
        return -1;
    }


    //Pico.m.frame_count = 0;
    initialized = 1;
    return 0;
}


int PicoDriveDeinit()
{
    PicoExit();
    RomFree();

    return 0;
}


void PicoDriveFrame(int skeep)
{
    if(initialized) {
        PicoSkipFrame = skeep;
        PicoFrame();
        PicoSkipFrame = 0;
    }
}



