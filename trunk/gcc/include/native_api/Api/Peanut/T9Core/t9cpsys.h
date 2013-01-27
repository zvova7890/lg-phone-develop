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
;**     FileName: t9cpsys.h                                                   **
;**                                                                           **
;**  Description: Chinese Phrase Text Input system header file.				  **
;**               Conforming to the development version of PTI.				  **
;**                                                                           **
;*******************************************************************************
;******************************************************************************/

#ifndef T9CPSYS_H
#define T9CPSYS_H 1

#include "t9cpapi.h"

/* don't mangle the function name if compile under C++ */
#if defined(__cplusplus)
extern "C" {
#endif

#define T9CP_CHECKFIELDINFO(pT9CPFieldInfo)	                    \
    if (!pT9CPFieldInfo ||                                      \
        (pT9CPFieldInfo->G.T9Private.wInitOK != T9_GOODSETUP) ||     \
        (pT9CPFieldInfo->G.T9PrivateLdb[pT9CPFieldInfo->G.bActiveLangIndex].wLangOK != T9_GOODSETUP))  \
    {                                                           \
        return(T9STATNOINIT);                                   \
    }                                                           \

typedef enum {
    T9CP_MISMATCH = 0,
    T9CP_TONEMISMATCH,
    T9CP_EXACTMATCH,
    T9CP_PARTIALMATCH
} T9CP_Match;

T9UINT T9FARCALL T9CP_PhraseIsAllChn(T9CPFieldInfo *pT9CPFieldInfo, T9SYMB *psPhrase, T9U8 bLen);
T9STATUS T9FARCALL T9CP_PhoneticAddDelimiter(T9CPFieldInfo * pT9CPFieldInfo);
T9STATUS T9FARCALL T9CP_PhoneticFlushContext(T9CPFieldInfo * pT9CPFieldInfo);
T9STATUS T9FARCALL T9CP_PhoneticGetPhrase(T9CPFieldInfo *   pT9CPFieldInfo,
                                        T9CPGETTYPE       eGetType,
                                        T9CPPhraseInfo *  pPhraseInfo);
T9STATUS T9FARCALL T9CP_PhoneticSelectPhrase(T9CPFieldInfo *    pT9CPFieldInfo,
                                           T9CPPhraseInfo *   pPhraseInfo,
                                           T9CPSpellInfo *    pSpellInfo);
T9STATUS T9FARCALL T9CP_StrokeAddDelimiter(T9CPFieldInfo * pT9CPFieldInfo);
#ifndef T9CP_DISABLE_STROKE
void T9FARCALL T9CP_InitStrokeMode(T9CPFieldInfo *pT9CPFieldInfo);
#endif

/*----------------------------------------------------------------------------
 *  Define the LDB function prototypes.                                         
 *----------------------------------------------------------------------------*/


/* End don't mangle the function name if compile under C++ */
#if defined(__cplusplus)
    }
#endif

#endif	/* #ifndef T9CPSYS_H */

/* ----------------------------------< eof >--------------------------------- */
