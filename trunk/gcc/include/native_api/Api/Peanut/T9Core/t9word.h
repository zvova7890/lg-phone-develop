/*******************************************************************************
;*******************************************************************************
;**                                                                           **
;**                    COPYRIGHT 1997-2006 TEGIC COMMUNICATIONS               **
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
;**     FileName: T9word.h                                                    **
;**                                                                           **
;**  Description: Header definitions for t9word generic routines.             **
;**                                                                           **
;*******************************************************************************
;******************************************************************************/

#ifndef T9WORD_H
#define T9WORD_H    1

/* don't mangle the function name if compile under C++ */
#if defined(__cplusplus)
extern "C" {
#endif

#define NUM_MAGIC_STRING_SEQUENCES 2
#define SHOW_DB_VERSION            1
#define SHOW_CORE_VERSION          2

T9UINT T9FARCALL T9_IsMagicStringInBuffer(T9FieldInfo *pFieldInfo, T9UINT nWordLen);
T9STATUS T9FARCALL T9_InsertMagicString(T9FieldInfo *pFieldInfo, T9UINT bVersion,
                                           T9SYMB *psBuildTxtBuf);
void T9FARCALL T9_PutWordTagOnKey(T9FieldInfo *pFieldInfo, T9UINT nPosition);
T9STATUS T9FARCALL T9_WordMoveBufferRight(T9FieldInfo *pFieldInfo, const T9SYMB *psSymbol,
                                 T9AuxType *paKey,
                                 T9UINT      nNumMoves,
                                 T9U8       bWordCompletion);
T9STATUS T9FARCALL T9_WordMoveBufferLeft(T9FieldInfo *pFieldInfo, T9UINT nNumMoves, T9U8 bWordCompletion);
#if defined(__cplusplus)
}
#endif

#endif

/* ----------------------------------< eof >--------------------------------- */
