
// -------------------- Pico Library --------------------

// Pico Library - Header File

// (c) Copyright 2004 Dave, All rights reserved.
// (c) Copyright 2006 notaz, All rights reserved.
// Free for non-commercial use.

// For commercial use, separate licencing terms must be obtained.

#ifndef PICO_H
#define PICO_H

// port-specific compile-time settings
#include <port_config.h>

#ifdef __cplusplus
extern "C" {
#endif

// Pico.c
// PicoOpt bits LSb->MSb:
// enable_ym2612&dac, enable_sn76496, enable_z80, stereo_sound,
// alt_renderer, 6button_gamepad, accurate_timing, accurate_sprites,
// draw_no_32col_border, external_ym2612
extern int PicoOpt;
extern int PicoVer;
extern int PicoSkipFrame; // skip rendering frame, but still do sound (if enabled) and emulation stuff
extern int PicoRegionOverride; // override the region detection 0: auto, 1: Japan NTSC, 2: Japan PAL, 4: US, 8: Europe
int PicoInit();
void PicoExit();
int PicoReset(int hard);
int PicoFrame();
extern int PicoPad[2]; // Joypads, format is MXYZ SACB RLDU
extern int (*PicoCram)(int cram); // Callback to convert colour ram 0000bbb0 ggg0rrr0
extern void (*PicoWriteSound)(void); // called once per frame at the best time to send sound buffer (PsndOut) to hardware

// Area.c
typedef size_t (arearw)(void *p, size_t _size, size_t _n, void *file);
// Save or load the state from PmovFile:
int PmovState(int PmovAction, void *PmovFile); // &1=for reading &2=for writing &4=volatile &8=non-volatile
extern arearw *areaRead;  // read and write function pointers for
extern arearw *areaWrite; // gzip save state ability

// Cart.c
int PicoCartLoad(FILE *f,unsigned char **prom,unsigned int *psize);
int PicoCartInsert(unsigned char *rom,unsigned int romsize);
// notaz
int CartLoadZip(const char *fname, unsigned char **prom, unsigned int *psize);
void Byteswap(unsigned char *data,int len);
// anotherguest
int PicoUnloadCart(unsigned char* romdata);

// Draw.c
void PicoDrawSetColorFormat(int which); // 0=BGR444, 1=RGB555, 2=8bit(HighPal pal)
extern void *DrawLineDest;
extern int (*PicoScan)(unsigned int num, void *data);
// internals
extern unsigned short HighPal[0x100];
extern int rendstatus;
// utility
#ifdef _ASM_DRAW_C
void *blockcpy(void *dst, const void *src, size_t n);
#else
#define blockcpy memcpy
#endif

// Draw2.c
// stuff below is optional
extern unsigned short *PicoCramHigh; // pointer to CRAM buff (0x40 shorts), converted to native device color (works only with 16bit for now)
extern void (*PicoPrepareCram)();    // prepares PicoCramHigh for renderer to use

// sound.c
extern int PsndRate,PsndLen;
extern short *PsndOut;
void sound_reset();
void sound_rerate();
void z80_pack(unsigned char *data);
void z80_unpack(unsigned char *data);
void z80_reset();

// Utils.c
extern int PicuAnd;
int PicuQuick(unsigned short *dest,unsigned short *src);
int PicuShrink(unsigned short *dest,int destLen,unsigned short *src,int srcLen);
int PicuShrinkReverse(unsigned short *dest,int destLen,unsigned short *src,int srcLen);
int PicuMerge(unsigned short *dest,int destLen,unsigned short *src,int srcLen);

#ifdef __cplusplus
} // End of extern "C"
#endif

#endif // PICO_H
