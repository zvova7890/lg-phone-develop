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
;**     FileName: t9cpwdls.h                                                  **
;**                                                                           **
;**  Description: Chinese Phrase Text Input word list module header file.     **
;**               Conforming to the development version of PTI.				  **
;**                                                                           **
;*******************************************************************************
;******************************************************************************/

#ifndef T9CPWDLS_H
#define T9CPWDLS_H 1

#include "t9cpname.h"

/* don't mangle the function name if compile under C++ */
#if defined(__cplusplus)
extern "C" {
#endif

#define T9CP_WORDLISTPIDMASK  0x3FFF
#define T9CP_LDBWORDENDBIT    0x4000
#define T9CP_MORELDBWORDBIT   0x8000
#define T9CP_FIRSTPIDWORDOFF  0x04
#define T9CP_BLOCKFIRSTPIDOFF (0x09 * 2)

#define MISMATCH        0
#define EXACTMATCH      1
#define PARTIALMATCH    2
#define PARTIALSYLMATCH 3
#define MISMATCHTONEDEL 4
#define MISMATCHKEY     5

/*----------------------------------------------------------------------------
 *  Define the word list function prototypes.                                         
 *----------------------------------------------------------------------------*/
T9STATUS T9FARCALL T9CP_GetLdbPhrases(T9CPFieldInfo *, T9U8, T9U8 *, T9U8, T9U8 *, T9U8 *, T9U16 *, T9U8, T9U8, T9CP_NameTableBookmark *);
 
/* End don't mangle the function name if compile under C++ */
#if defined(__cplusplus)
    }
#endif

#endif	/* #ifndef T9CPWDLS_H */

/* ----------------------------------< eof >--------------------------------- */
