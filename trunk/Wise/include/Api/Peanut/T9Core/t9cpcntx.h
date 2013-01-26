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
;**     FileName: t9cpcntx.h                                                  **
;**                                                                           **
;**  Description: PTI context prediction module header file.                  **
;**               Conforming to the development version of PTI.				  **
;**                                                                           **
;*******************************************************************************
;******************************************************************************/

#ifndef T9CPCNTX_H
#define T9CPCNTX_H 1

/* don't mangle the function name if compile under C++ */
#if defined(__cplusplus)
extern "C" {
#endif

/*----------------------------------------------------------------------------
 *  Define the context function prototypes.                                         
 *----------------------------------------------------------------------------*/

T9U8 T9FARCALL T9CP_GetContextPrefix(T9CPFieldInfo *pT9CPFieldInfo,
                                     T9U16 **ppwPrefix,
                                     T9U8 bNthPrefix);

void T9FARCALL T9CP_UpdateContextBuf(T9CPFieldInfo *pT9CPFieldInfo,
                                     T9CPPhraseInfo *psPhrase);

void T9FARCALL T9CP_ClrContextBuf(T9CPFieldInfo *pT9CPFieldInfo);

/* End don't mangle the function name if compile under C++ */
#if defined(__cplusplus)
    }
#endif

#endif	/* #ifndef T9CPCNTX_H */

/* ----------------------------------< eof >--------------------------------- */
