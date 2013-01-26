/*******************************************************************************
;*******************************************************************************
;**                                                                           **
;**                  COPYRIGHT 1997-2004 TEGIC COMMUNICATIONS                 **
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
;**     FileName: T9buffer.h                                                    **
;**                                                                           **
;**  Description: Miscellaneous tools for T9.                                 **
;**                                                                           **
;*******************************************************************************
;******************************************************************************/

#ifndef T9BUFFER_H
#define T9BUFFER_H 1

/* don't mangle the function name if compile under C++ */
#if defined(__cplusplus)
extern "C" {
#endif

T9STATUS T9FARCALL T9_MoveBufferRight(T9FieldInfo *pFieldInfo,
                                 const T9SYMB *psSymbol,
                                 T9AuxType *paKey,
                                 T9UINT      nNumMoves);
T9STATUS T9FARCALL T9_MoveBufferLeft(T9FieldInfo *pFieldInfo, T9UINT nNumMoves);
void T9FARCALL T9_OverWriteBuf(T9FieldInfo *pFieldInfo, T9UINT nClearLength);

#if defined(__cplusplus)
}
#endif

#endif /* T9BUFFER_H */






/* ----------------------------------< eof >--------------------------------- */

