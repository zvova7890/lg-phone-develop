/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	PEANUT POINTING PROCESS RETURN VALUE DEFINITION

	Copyright(c) 1997-2003 BNSoft Corp.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT_PEANUT_PPRDEF_H_
#define		_BNSOFT_PEANUT_PPRDEF_H_

#define		PPRET_NONE				0x00000000	
#define		PPRET_DONE				0x00000001
#define		PPRET_UP				0x00000002
#define		PPRET_DOWN				0x00000004
#define		PPRET_MOVE				0x00000008
#define		PPRET_SB_UP				0x00000010
#define		PPRET_SB_DOWN				0x00000020
#define		PPRET_SB_LEFT				0x00000030
#define		PPRET_SB_RIGHT				0x00000040
#define		PPRET_SB_PAGEUP				0x00000050
#define		PPRET_SB_PAGEDOWN			0x00000060
#define		PPRET_SB_PAGELEFT			0x00000070	
#define		PPRET_SB_PAGERIGHT			0x00000080
#define		PPRET_SB_HBAR				0x00000090
#define		PPRET_SB_VBAR				0x000000A0
#define		PPRET_SB_MASK				0x000000F0
#define		PPRET_OUT_OF_RANGE			0x00000100
#define		PPRET_SM_1				0x00000200
#define		PPRET_SM_2				0x00000400
#define		PPRET_SM_3				0x00000800	
#define		PPRET_SM_MASK				0x00000E00	
#define		PPRET_LONG				0x00001000
#define		PPRET_FLICK_PROCESSED		        0x00002000
#define		PPRET_MOVE_FAKE				0X00004000

#endif	//	_BNSOFT_PEANUT_PPRDEF_H_
