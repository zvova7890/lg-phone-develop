
#include <stdio.h>
#include <string.h>
#include "../../Pico/PicoInt.h"


void sync() {

}


typedef unsigned int (*STATE_SL_FUNC)(void *, unsigned int, unsigned int, void *);

int PicoSaveLoadGame(int load, int sram, const char *file)
{
	int ret = 0;
	char saveFname[256];

	strcpy(saveFname, file);

	printf("saveLoad (%i, %i): %s\n", load, sram, file);
	if(sram) {
		FILE *sramFile;
		int sram_size = SRam.end-SRam.start+1;
		if(SRam.reg_back & 4) sram_size=0x2000;
		if(!SRam.data) return 0; // SRam forcefully disabled for this game

		if(load) {
			sramFile = fopen(saveFname, "rb");
			if(!sramFile) {
                printf("Can`t open '%s' for read\n", saveFname);
                return -1;
			}

			fread(SRam.data, 1, sram_size, sramFile);
			fclose(sramFile);
		} else {
			// sram save needs some special processing
			// see if we have anything to save
			for(; sram_size > 0; sram_size--)
				if(SRam.data[sram_size-1]) break;

			if(sram_size) {
				sramFile = fopen(saveFname, "w+");
				if(!sramFile) {
                    printf("Can`t open '%s' for write\n", saveFname);
                    return -1;
				}
				ret = fwrite(SRam.data, 1, sram_size, sramFile);
				ret = (ret != sram_size) ? -1 : 0;
				fclose(sramFile);
				sync();
			}
		}

	} else {
		void *PmovFile = NULL;
		// try gzip first
		/*if(currentConfig.EmuOpt & 8) {
			strcat(saveFname, ".gz");
			if( (PmovFile = gzopen(saveFname, load ? "rb" : "wb")) ) {
				areaRead  = gzRead2;
				areaWrite = gzWrite2;
				if(!load) gzsetparams(PmovFile, 9, Z_DEFAULT_STRATEGY);
			} else
				saveFname[strlen(saveFname)-3] = 0;
		}*/
		if(!PmovFile) { // gzip failed or was disabled
			if( (PmovFile = fopen(saveFname, load ? "rb" : "w+")) ) {
				areaRead  = (STATE_SL_FUNC) fread;
				areaWrite = (STATE_SL_FUNC) fwrite;
			} else {
			    printf("Can`t open '%s' for %s\n", saveFname, load?"read" : "write");
			}
		}
		if(PmovFile) {
			PmovState(load ? 6 : 5, PmovFile);
			//if(areaRead == gzRead2)
				 //gzclose(PmovFile);
			//else
                fclose ((FILE *) PmovFile);
			PmovFile = 0;
			if (!load) sync();
			else Pico.m.dirtyPal=1;
		} else {

			ret = -1;
		}

	}

	return ret;
}
