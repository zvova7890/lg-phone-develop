/*******************************************************************************
;*******************************************************************************
;**                                                                           **
;**                    COPYRIGHT 2004-2006 TEGIC COMMUNICATIONS               **
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
;**     FileName: t9cpudb.h                                                   **
;**                                                                           **
;**  Description: Chinese Phrase Text Input UDB module header file.           **
;**               Conforming to the development version of PTI.				  **
;**                                                                           **
;*******************************************************************************
;******************************************************************************/

#ifndef T9CPUDB_H
#define T9CPUDB_H 1

#ifndef T9CPNOUDB

/* don't mangle the function name if compile under C++ */
#if defined(__cplusplus)
extern "C" {
#endif


/*----------------------------------------------------------------------------
 *  Define the internal UDB function prototypes.                                         
 *----------------------------------------------------------------------------*/
void T9FARCALL T9CP_UdbSelectPhrase(T9CPFieldInfo *);
void T9FARCALL T9CP_BuildUdbEditorSpell(T9CPFieldInfo *);
void T9FARCALL T9CP_UdbUpdateClue(T9CPFieldInfo *pT9CPFieldInfo,
                                  T9CPPhraseInfo *psNewClue);
void T9FARCALL T9CP_SaveUdbPhraseClueAndExit(T9CPFieldInfo *pT9CPFieldInfo);

/* test if UDB spellings are fixed length */
#define T9CP_UdbIsFixedLen(pT9CPFieldInfo) ((pT9CPFieldInfo)->CommonInfo.bNumConsumedKeys != 0)

/* End don't mangle the function name if compile under C++ */
#if defined(__cplusplus)
    }
#endif

#endif /* end of T9CPNOUDB */

#endif	/* #ifndef T9CPUDB_H */

/* ----------------------------------< eof >--------------------------------- */

