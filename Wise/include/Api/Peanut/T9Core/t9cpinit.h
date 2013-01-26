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
;**     FileName: t9cpinit.h                                                  **
;**                                                                           **
;**  Description: Chinese Phrase Text Input initialization module header file.**
;**               Conforming to the development version of PTI.				  **
;**                                                                           **
;*******************************************************************************
;******************************************************************************/

#ifndef T9CPINIT_H
#define T9CPINIT_H 1

/* don't mangle the function name if compile under C++ */
#if defined(__cplusplus)
extern "C" {
#endif

typedef enum {
    T9CP_FULLZERO = 1,                 /* zero all variables */
    T9CP_PBUFZERO,                     /* zero phrase buffer variables */
    T9CP_KEYSEARCHZERO,                /* zero key search variables for */
    T9CP_ACTINSTSEARCHZERO             /* zero active instruction search variables */
} T9CP_ZEROTYPE;


/*----------------------------------------------------------------------------
 *  Define the internal initialization function prototypes.                                         
 *----------------------------------------------------------------------------*/

void T9FARCALL T9CP_ZeroT9FieldInfo(T9FieldInfo *);
void T9FARCALL T9CP_ZeroPTIFieldInfo(T9CPFieldInfo *);

/* End don't mangle the function name if compile under C++ */
#if defined(__cplusplus)
    }
#endif

#endif	/* #ifndef T9CPINIT_H */

/* ----------------------------------< eof >--------------------------------- */


