/*******************************************************************************
;*******************************************************************************
;**                                                                           **
;**                    COPYRIGHT 1999-2004 TEGIC COMMUNICATIONS               **
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
;**     FileName: T9SYM.H                                                     **
;**                                                                           **
;**  Description: T9 symbol key, class, key information                       **
;**                                                                           **
;******************************************************************************/

#ifndef T9SYM_H
#define T9SYM_H 1

/* don't mangle the function name if compile under C++ */
#if defined(__cplusplus)
extern "C" {
#endif

/*----------------------------------------------------------------------------
 * SymToKey table special codes
 *----------------------------------------------------------------------------*/
#define ST_WHITESPACE   0xF            /* White space */
#define ST_NUMERIC      0xE            /* Punctuation */
#define ST_UNKNOWN      0xD            /* Unknown characters */
#define ST_PUNCTUATION  0x0            /* Punctuation characters */

T9SYMB  T9FARCALL T9_SymToUpper( T9FieldInfo  *pFieldInfo, T9SYMB sSymb );
T9U8    T9FARCALL T9_SymbolToKeyTable(  T9FieldInfo  *pFieldInfo, T9SYMB sSymb );
T9UINT T9FARCALL T9_GetSymbolKeyAndClass(T9FieldInfo  *pFieldInfo,
                                  T9SYMB sSymb, T9AuxType *paKey,
                                  T9AuxType *paClass);
T9AuxType T9FARCALL T9_GetTxtClass(T9FieldInfo *pFieldInfo, T9UINT nPosition);
T9AuxType T9FARCALL T9_GetSymbolKey(T9FieldInfo *pFieldInfo, T9SYMB sSymID);
T9STATUS T9FARCALL T9_GetKeyForSym(T9FieldInfo *pFieldInfo, T9SYMB sSymID, T9AuxType *paKey);
T9MINOR T9FARCALL T9_HasAmbiguousKey(T9FieldInfo  *pFieldInfo, T9SYMB sSymb);
T9SYMB T9FARCALL T9_SymToLower(T9FieldInfo  *pFieldInfo, T9SYMB sSymb);

#define T9_IsNumeric(pFieldInfo, sSymb)    (T9GetSymbolClass(pFieldInfo, sSymb) == T9SYMNUMBRMASK)
#define T9_IsWhiteSpace(pFieldInfo, sSymb) (T9GetSymbolClass(pFieldInfo, sSymb) == T9SYMWHITEMASK)
#define T9_IsPunctChar(pFieldInfo, sSymb)  (T9GetSymbolClass(pFieldInfo, sSymb) == T9SYMPUNCTMASK)

T9U8 T9FARCALL T9_SymbToUtf8(T9FieldInfo *pFieldInfo, T9SYMB sIn, T9U8  *pbOut);
T9STATUS T9FARCALL T9_Utf8ToT9Symb(T9FieldInfo *pFieldInfo, T9U8 *pbIn, T9SYMB *psOut, T9U8 *pbUtf8SymbolSize);

#if defined(__cplusplus)
}
#endif

#endif
