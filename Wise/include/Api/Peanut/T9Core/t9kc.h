/*******************************************************************************
;*******************************************************************************
;**                                                                           **
;**                    COPYRIGHT 2001-2003 TEGIC COMMUNICATIONS               **
;**                                                                           **
;**                TEGIC COMMUNICATIONS PROPRIETARY INFORMATION               **
;**                                                                           **
;**     This software is supplied under the terms of a license agreement      **
;**     or non-disclosure agreement with Tegic Communications and may not     **
;**     be copied or disclosed except in accordance with the terms of that    **
;**     agreement.                                                            **
;**                                                                           **
;*******************************************************************************
;**                                                                           **
;**     FileName: T9KCAPI.H                                                   **
;**                                                                           **
;**  Description: T9 Korean Chun-Ji-In non-API Header File                    **
;**                                                                           **
;**                                                                           **
;*******************************************************************************
;******* 10 ****** 20 ****** 30 ****** 40 ****** 50 ****** 60 ****** 70 *******/

#ifndef T9KCAPI_H
#define T9KCAPI_H

#include "t9kcapi.h"

/* don't mangle the function name if compile under C++ */
#if defined(__cplusplus)
extern "C" {
#endif

/* ----------------------------------------------------------
    Korean Hangul Types
  ----------------------------------------------------------- */
#define  HANGUL_NONE		0
#define  HANGUL_VOWEL		1
#define  HANGUL_SUB_VOWEL	2
#define  HANGUL_LEAD		3
#define  HANGUL_LEAD_MULTAP	4
#define  HANGUL_UNI			5
#define  HANGUL_UNI_MULTAP	6
#define  HANGUL_EXPL_UNI	7
#define  HANGUL_EXPL_VOWEL	8
#define  HANGUL_EXPL_SUB_VOWEL	9
#define  HANGUL_EXPL_LEAD	10

#define VOWEL_DECOMP_FLAG   5
#define DECOMP_MASK			(T9U8)(1 << VOWEL_DECOMP_FLAG)
#define INVALID_IDX			(T9U8)30 /* bigger than LEAD_COUNT or VOWEL_COUNT but less than DECOMP_MASK value*/
#define INVALID_S			(T9U16)0xF430

/* ----------------------------------------------------------
    Unicode composition/decomposition Constants
  ----------------------------------------------------------- */
static const T9U16 KOR_UNI_BASE = 0xAC00;
static const T9U16 LEAD_UNI_BASE = 0x1100;
static const T9U16 VOWEL_UNI_BASE = 0x1161;
static const T9U16 VOWEL_UNI_MAX  = 0x1177;
static const T9U16 TAIL_UNI_BASE = 0x11A7;
static const T9U16 LEAD_COUNT = 19;
static const T9U16 VOWEL_COUNT = 21;
static const T9U16 TAIL_COUNT = 28;
static const T9U16 VOWEL_TAIL_COUNT = 588; /* VOWEL_COUNT * TAIL_COUNT = 588 */
static const T9U16 HANGUL_COUNT = 11172; /* LEAD_COUNT * VOWEL_TAIL_COUNT = 11172 */

/*  the following table has information on how to build a Jamo Vowel ( or Jungsung)
    from the Chun-Ji-In components.  Indexes start at Unicode Jamo code 1161 and the
	three data items contain how many rows to add (depending on Chun, Ji, or In) to
	get to the next Vowel (dot and double dor are included as 0x1176 and 0x1177 */
static const T9U8 VowelTable[23][3] = {
	{1,	DECOMP_MASK | 2,	INVALID_IDX}, /*  offset from 0x1161 Unicode when adding Chun, Ji, or In */
	{DECOMP_MASK | INVALID_IDX,	INVALID_IDX,	INVALID_IDX}, /*  offset from 0x1162 */
	{3,	DECOMP_MASK | INVALID_IDX,	INVALID_IDX}, /*  offset from 0x1163 */
	{DECOMP_MASK | INVALID_IDX,	INVALID_IDX,	INVALID_IDX}, /*  offset from 0x1164 */
	{DECOMP_MASK | 5,	INVALID_IDX,	INVALID_IDX}, /*  offset from 0x1165 */
	{DECOMP_MASK | INVALID_IDX,	INVALID_IDX,	INVALID_IDX}, /*  offset from 0x1166 */
	{DECOMP_MASK | 7,	INVALID_IDX,	INVALID_IDX}, /*  offset from 0x1167 */
	{DECOMP_MASK | INVALID_IDX,	INVALID_IDX,	INVALID_IDX}, /*  offset from 0x1168 */
	{11,	INVALID_IDX,	DECOMP_MASK | INVALID_IDX}, /*  offset from 0x1169 */
	{10,	DECOMP_MASK | INVALID_IDX,	INVALID_IDX}, /*  offset from 0x116A */
	{DECOMP_MASK | INVALID_IDX,	INVALID_IDX,	INVALID_IDX}, /*  offset from 0x116B */
	{DECOMP_MASK | INVALID_IDX,	9,	INVALID_IDX}, /*  offset from 0x116C */
	{INVALID_IDX,	INVALID_IDX,	DECOMP_MASK | INVALID_IDX}, /*  offset from 0x116D */
	{16,	DECOMP_MASK | 17,	INVALID_IDX}, /*  offset from 0x116E */
	{DECOMP_MASK | 15,	INVALID_IDX,	INVALID_IDX}, /*  offset from 0x116F */
	{DECOMP_MASK | INVALID_IDX,	INVALID_IDX,	INVALID_IDX}, /*  offset from 0x1170 */
	{DECOMP_MASK | INVALID_IDX,	INVALID_IDX,	INVALID_IDX}, /*  offset from 0x1171 */
	{14,DECOMP_MASK | INVALID_IDX,	INVALID_IDX}, /*  offset from 0x1172 */
	{19, 13,	INVALID_IDX}, /*  offset from 0x1173 */
	{DECOMP_MASK | INVALID_IDX,	INVALID_IDX,	INVALID_IDX}, /*  offset from 0x1174 */
	{INVALID_IDX, 0, INVALID_IDX}, /*  offset from 0x1175 */
	{4, 22, 8}, /*  offset from 0x1176 = dot */
	{6, DECOMP_MASK | 21, 12} /*  offset from 0x1177 = double dot */
};

/*  the following table holds the component single jamos for the compound jamos
    in the Jongsung (final consonant), so they can be broken up
	FIRST column in Jonsung encoding (terminal), SECOND column in Chosung encoding (Leading)*/
static const T9FARDATA T9SYMB BreakTailTable[28][2] = {
	{0x0000,	0x0000}, /*  wont ever get this 0x11A7 Unicode Jongsung (empty jongsung) */
	{0x0000,	0x1100}, /*  two components for 0x11A8 Unicode Jongsung*/
	{0x0000,	0x1101}, /*  two components for 0x11A9 Unicode Jongsung*/
	{0x11A8,	0x1109}, /*  two components for 0x11AA Unicode Jongsung*/
	{0x0000,	0x1102}, /*  two components for 0x11AB Unicode Jongsung*/
	{0x11AB,	0x110C}, /*  two components for 0x11AC Unicode Jongsung*/
	{0x11AB,	0x1112}, /*  two components for 0x11AD Unicode Jongsung*/
	{0x0000,	0x1103}, /*  two components for 0x11AE Unicode Jongsung*/
	{0x0000,	0x1105}, /*  two components for 0x11AF Unicode Jongsung*/
	{0x11AF,	0x1100},
	{0x11AF,	0x1106},
	{0x11AF,	0x1107},
	{0x11AF,	0x1109},
	{0x11AF,	0x1110},
	{0x11AF,	0x1111},
	{0x11AF,	0x1112},
	{0x0000,	0x1106},
	{0x0000,	0x1107},
	{0x11B8,	0x1109},
	{0x0000,	0x1109},
	{0x0000,	0x110A},
	{0x0000,	0x110B},
	{0x0000,	0x110C},
	{0x0000,	0x110E},
	{0x0000,	0x110F},
	{0x0000,	0x1110},
	{0x0000,	0x1111},
	{0x0000,	0x1112} /*  two components for 0x11C2 Unicode Jongsung*/
};

/*----------------------------------------------------------------------------
 *  Function prototypes for non-API routines
 *----------------------------------------------------------------------------*/
extern T9STATUS T9FARCALL T9KC_TakeApartVowel(T9U8* pucVIndex, T9U8* pucChunIndex);

#if defined(__cplusplus)
}
#endif

#endif
