/*******************************************************************************
;*******************************************************************************
;**                                                                           **
;**                    COPYRIGHT 2004-2007 TEGIC COMMUNICATIONS               **
;**                                                                           **
;**                TEGIC COMMUNICATIONS PROPRIETARY INFORMATION               **
;**                                                                           **
;**     This software is supplied under the terms of a license agreement      **
;**     or non-disclosure agreement with Tegic Communications and may not     **
;**     be copied or disclosed except in accordance with the terms of that    **
;**     agreement.                                                            **
;**                                                                           **
;**                                                                           **
;*******************************************************************************
;**                                                                           **
;**     FileName: t9cpkey.h                                                   **
;**                                                                           **
;**  Description: Chinese Phrase Text Input  key module header file.          **
;**               Conforming to the development version of PTI.				  **
;**                                                                           **
;*******************************************************************************
;******************************************************************************/

#ifndef T9CPKEY_H
#define T9CPKEY_H 1

/* don't mangle the function name if compile under C++ */
#if defined(__cplusplus)
extern "C" {
#endif

#define T9CP_PHONETICKEYMASK      0x1F    /* mask for phonetic key in the key buffer. 
                                             For the 9-key, 4 bits are enough. For    
                                             explicit input, we need 5 bits.
                                           */
#define T9CP_DELIMIETRKEYMASK     0xE0    /* mask for phonetic delimiter in 
                                             the key buffer.
                                           */
#define T9CP_TONEDELMASKSHIFT       5     /* number of shift in the key encoding
                                             to get the tone or delimilter 
                                           */
#define T9CP_PINYINKEYCOUNT         (T9KEYAMBIG9 - T9KEYAMBIG2 + 1)       /* number of ambiguous keys used in Pinyin */

#define T9CP_BPMFKEYCOUNT           10      /* number of ambiguous keys used in BPMF */

#define T9CP_JIANPINMINKEY          2       /* Min key count to trigger Jianpin search */
#define T9CP_JIANPINMAXKEY          T9CPMAXPHRASESIZE /* Max key count for Jianpin */

/*----------------------------------------------------------------------------
 *  Define the ambiguous key function prototypes.                                         
 *----------------------------------------------------------------------------*/
T9STATUS T9FARCALL T9CP_PhoneticAddKey(T9CPFieldInfo * pT9CPFieldInfo,
									   T9U8            bKey);
T9STATUS T9FARCALL T9CP_PhoneticDelLastKey(T9CPFieldInfo * pT9CPFieldInfo);

T9STATUS T9FARCALL T9CP_AddAWKeys(T9CPFieldInfo *pT9CPFieldInfo,
                                  T9U8 *pbKeyBuf,
                                  T9U8 bKeyCount);
void T9FARCALL T9CP_RestoreAWTextBuf(T9CPFieldInfo *pT9CPFieldInfo, T9UINT nTextLen);

/* End don't mangle the function name if compile under C++ */
#if defined(__cplusplus)
    }
#endif

#endif	/* #ifndef T9CPKEY_H */

/* ----------------------------------< eof >--------------------------------- */

