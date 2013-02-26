/* faked 940 code just uses local copy of ym2612 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <errno.h>

#include "../../Pico/sound/ym2612.h"
#include "../../Pico/PicoInt.h"



/***********************************************************/


int YM2612Write_940(unsigned int a, unsigned int v)
{


	return 0; // cause the engine to do updates once per frame only
}


void YM2612PicoStateLoad_940(void)
{

}


void sharedmem_init(void)
{

}

void sharedmem_deinit(void)
{

}

void YM2612Init_940(int baseclock, int rate)
{

}


void YM2612ResetChip_940(void)
{

}




int YM2612UpdateOne_940(int *buffer, int length, int stereo, int is_buf_empty)
{
    return 0;
}


void mp3_update(int *buffer, int length, int stereo)
{
	// nothing..
}


/***********************************************************/


int mp3_get_bitrate(FILE *f, int len)
{
    return 0;
}


void mp3_start_play(FILE *f, int pos) // pos is 0-1023
{

}


int mp3_get_offset(void)
{
	return 0;
}


