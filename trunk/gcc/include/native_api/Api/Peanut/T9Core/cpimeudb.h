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
;**     FileName: cpimeudb.h                                                  **
;**                                                                           **
;**  Description: Phrase Text Input UDB demo header file.					  **
;**               Conforming to the development version of PTI.				  **
;**                                                                           **
;*******************************************************************************
;******************************************************************************/
#ifndef CPIMEUDB_H
#define CPIMEUDB_H

#ifndef T9CPNOUDB

#include "t9cpapi.h"

/* don't mangle the function name if compile under C++ */
#if defined(__cplusplus)
extern "C" {
#endif

T9STATUS T9FARCALL PrepareCPUdbEdit();
T9STATUS T9FARCALL AppendConfirmedUdbSyl(T9U8);

int T9FARCALL IME_UdbOpMenuExit();
int T9FARCALL IME_UdbOpMenu();
int T9FARCALL IME_UdbPromptDeleteEntry();
int T9FARCALL IME_UdbDeleteEntry();

/* End don't mangle the function name if compile under C++ */
#if defined(__cplusplus)
    }
#endif

#endif /* UDB */
#endif /* CPIMEUDB_H */

