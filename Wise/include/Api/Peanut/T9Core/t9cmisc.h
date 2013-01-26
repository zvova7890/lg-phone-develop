/*******************************************************************************
;*******************************************************************************
;**                                                                           **
;**                  COPYRIGHT 1997-2003 TEGIC COMMUNICATIONS                 **
;**                                                                           **
;**                TEGIC COMMUNICATIONS PROPRIETARY INFORMATION               **
;**                                                                           **
;**     This software is supplied under the terms of a license agreement      **
;**     or non-disclosure agreement with Tegic Communications and may not     **
;**     be copied or disclosed except in accordance with the terms of that    **
;**     agreement.                                                            **
;**                                                                           **
;**     T9 Export Control Classification Number ECCN: EAR99                   **
;**                                                                           **
;*******************************************************************************
;**                                                                           **
;**     FileName: t9chksum.h                                                    **
;**                                                                           **
;**  Description: Checksum calculation for Chinese T9.                                 **
;**                                                                           **
;*******************************************************************************
;******************************************************************************/

#ifndef T9CHKSUM_H
#define T9CHKSUM_H 1

/* don't mangle the function name if compile under C++ */
#if defined(__cplusplus)
extern "C" {
#endif

/*------------------------------------------------------------------
 * Functions
 *------------------------------------------------------------------*/
extern T9U32 T9FARCALL T9CC_Checksum(T9U8 bType, const T9U8 T9FARDATA *str, const T9U32 len, const T9U32 dwStartValue);

#if defined(__cplusplus)
}
#endif

#endif





/* ----------------------------------< eof >--------------------------------- */

