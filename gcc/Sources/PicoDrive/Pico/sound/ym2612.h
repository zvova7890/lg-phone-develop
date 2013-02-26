/*
  header file for software emulation for FM sound generator

*/
#ifndef _H_FM_FM_
#define _H_FM_FM_

/* compiler dependence */
#ifndef UINT8
typedef unsigned char	UINT8;   /* unsigned  8bit */
typedef unsigned short	UINT16;  /* unsigned 16bit */
typedef unsigned int	UINT32;  /* unsigned 32bit */
#endif
#ifndef INT8
typedef signed char		INT8;    /* signed  8bit   */
typedef signed short	INT16;   /* signed 16bit   */
typedef signed int		INT32;   /* signed 32bit   */
#endif

#if 1
/* struct describing a single operator (SLOT) */
typedef struct
{
	INT32	*DT;		/* #0x00 detune          :dt_tab[DT] */
	UINT8	ar;			/* #0x04 attack rate  */
	UINT8	d1r;		/* #0x05 decay rate   */
	UINT8	d2r;		/* #0x06 sustain rate */
	UINT8	rr;			/* #0x07 release rate */
	UINT32	mul;		/* #0x08 multiple        :ML_TABLE[ML] */

	/* Phase Generator */
	UINT32	phase;		/* #0x0c phase counter */
	UINT32	Incr;		/* #0x10 phase step */

	UINT8	KSR;		/* #0x14 key scale rate  :3-KSR */
	UINT8	ksr;		/* #0x15 key scale rate  :kcode>>(3-KSR) */

	UINT8	key;		/* #0x16 0=last key was KEY OFF, 1=KEY ON */

	/* Envelope Generator */
	UINT8	state;		/* #0x17 phase type: EG_OFF=0, EG_REL, EG_SUS, EG_DEC, EG_ATT */
	UINT16	tl;			/* #0x18 total level: TL << 3 */
	INT16	volume;		/* #0x1a envelope counter */
	UINT32	sl;			/* #0x1c sustain level:sl_table[SL] */

	UINT32	eg_pack_ar;		/* #0x20 (attack state) */
	UINT32	eg_pack_d1r;	/* #0x24 (decay state) */
	UINT32	eg_pack_d2r;	/* #0x28 (sustain state) */
	UINT32	eg_pack_rr;		/* #0x2c (release state) */
} FM_SLOT;


typedef struct
{
	FM_SLOT	SLOT[4];	/* four SLOTs (operators) */

	UINT8	ALGO;		/* algorithm */
	UINT8	FB;			/* feedback shift */
	INT32	op1_out;	/* op1 output for feedback */

	INT32	mem_value;	/* delayed sample (MEM) value */

	INT32	pms;		/* channel PMS */
	UINT8	ams;		/* channel AMS */

	UINT8	kcode;		/* key code:                        */
	UINT32	fc;			/* fnum,blk:adjusted to sample rate */
	UINT32	block_fnum;	/* current blk/fnum value for this slot (can be different betweeen slots of one channel in 3slot mode) */

	/* LFO */
	UINT8	AMmasks;	/* AM enable flag */

} FM_CH;

typedef struct
{
	int		clock;		/* master clock  (Hz)   */
	int		rate;		/* sampling rate (Hz)   */
	double	freqbase;	/* frequency base       */
	UINT8	address;	/* address register     */
	UINT8	status;		/* status flag          */
	UINT8	mode;		/* mode  CSM / 3SLOT    */
	UINT8	fn_h;		/* freq latch           */
	int		TA;			/* timer a              */
	int		TAC;		/* timer a maxval       */
	int		TAT;		/* timer a ticker       */
	UINT8	TB;			/* timer b              */
	int		TBC;		/* timer b maxval       */
	int		TBT;		/* timer b ticker       */
	/* local time tables */
	INT32	dt_tab[8][32];/* DeTune table       */
} FM_ST;

/***********************************************************/
/* OPN unit                                                */
/***********************************************************/

/* OPN 3slot struct */
typedef struct
{
	UINT32  fc[3];			/* fnum3,blk3: calculated */
	UINT8	fn_h;			/* freq3 latch */
	UINT8	kcode[3];		/* key code */
	UINT32	block_fnum[3];	/* current fnum value for this slot (can be different betweeen slots of one channel in 3slot mode) */
} FM_3SLOT;

/* OPN/A/B common state */
typedef struct
{
	FM_ST	ST;				/* general state */
	FM_3SLOT SL3;			/* 3 slot mode state */
	UINT32  pan;			/* fm channels output mask (bit 1 = enable) */

	UINT32	eg_cnt;			/* #0xb38 global envelope generator counter */
	UINT32	eg_timer;		/* #0xb3c global envelope generator counter works at frequency = chipclock/64/3 */
	UINT32	eg_timer_add;	/* #0xb40 step of eg_timer */

	/* LFO */
	UINT32	lfo_cnt;
	UINT32	lfo_inc;

	UINT32	lfo_freq[8];	/* LFO FREQ table */
} FM_OPN;

/* here's the virtual YM2612 */
typedef struct
{
	UINT8		REGS[0x200];		/* registers (for save states)       */
	INT32		addr_A1;			/* address line A1      */

	FM_CH		CH[6];				/* channel state (0x168 bytes each)? */

	/* dac output (YM2612) */
	int			dacen;
	INT32		dacout;

	FM_OPN		OPN;				/* OPN state            */
} YM2612;
#endif



void YM2612Init_(int baseclock, int rate);
void YM2612ResetChip_(void);
void YM2612UpdateOne_(short *buffer, int length, int stereo);

int  YM2612Write_(unsigned int a, unsigned int v);
unsigned char YM2612Read_(void);

int  YM2612PicoTick_(int n);
void YM2612PicoStateLoad_(void);

void *YM2612GetRegs(void);

#ifndef __GP2X__
#define YM2612Init          YM2612Init_
#define YM2612ResetChip     YM2612ResetChip_
#define YM2612UpdateOne     YM2612UpdateOne_
#define YM2612Write         YM2612Write_
#define YM2612Read          YM2612Read_
#define YM2612PicoTick      YM2612PicoTick_
#define YM2612PicoStateLoad YM2612PicoStateLoad_
#else
/* GP2X specific */
#include "../../platform/gp2x/940ctl_ym2612.h"
extern int PicoOpt;
#define YM2612Init(baseclock,rate) { \
	if (PicoOpt&0x200) YM2612Init_940(baseclock, rate); \
	else               YM2612Init_(baseclock, rate); \
}
#define YM2612ResetChip() { \
	if (PicoOpt&0x200) YM2612ResetChip_940(); \
	else               YM2612ResetChip_(); \
}
#define YM2612UpdateOne(buffer,length,stereo) { \
	if (PicoOpt&0x200) YM2612UpdateOne_940(buffer, length, stereo); \
	else               YM2612UpdateOne_(buffer, length, stereo); \
}
#define YM2612Write(a,v) \
	(PicoOpt&0x200) ?  YM2612Write_940(a, v) : YM2612Write_(a, v)
#define YM2612Read() \
	(PicoOpt&0x200) ?  YM2612Read_940()      : YM2612Read_()
#define YM2612PicoTick(n) \
	(PicoOpt&0x200) ?  YM2612PicoTick_940(n) : YM2612PicoTick_(n)
#define YM2612PicoStateLoad() { \
	if (PicoOpt&0x200) YM2612PicoStateLoad_940(); \
	else               YM2612PicoStateLoad_(); \
}
#endif /* __GP2X__ */


#endif /* _H_FM_FM_ */
