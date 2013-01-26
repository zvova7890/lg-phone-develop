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
;**     FileName: t9cpname.h                                                  **
;**                                                                           **
;**  Description: Chinese Phrase Text Input name input module header file.    **
;**               Conforming to the development version of PTI.               **
;**                                                                           **
;*******************************************************************************
;******************************************************************************/

#ifndef T9CPNAME_H
#define T9CPNAME_H 1

/* don't mangle the function name if compile under C++ */
#if defined(__cplusplus)
extern "C" {
#endif

#define T9CP_MAX_NAMETABLE_BOOKMARK     6

/* a structure to temporarily remember a reference point in name table */
typedef struct T9CP_NameTableBookmark_s {
    T9U16 wOffset;  /* the 0-based entry index as the bookmark location */
    T9U16 wID; /* entries starting from wOffset will have ID >= wID */
} T9CP_NameTableBookmark;

/*----------------------------------------------------------------------------
 *  Define function prototypes.
 *----------------------------------------------------------------------------*/
void T9FARCALL T9CP_InitNameTableBookmarks(T9CPFieldInfo *pT9CPFieldInfo,
                                           T9CP_NameTableBookmark *pBookmarks,
                                           T9UINT nCount,
                                           T9UINT fIsSID);
void T9FARCALL T9CP_AddNameSpells(T9CPFieldInfo *pT9CPFieldInfo);

void T9FARCALL T9CP_GetCommonNameChar(T9CPFieldInfo *pT9CPFieldInfo,
                                      T9UINT fIsSID);

T9U8 T9FARCALL T9CP_GetNameCharFreq(T9CPFieldInfo *pT9CPFieldInfo,
                                    T9UINT fIsSID,
                                    T9U16 wID);
T9U8 T9FARCALL T9CP_FindNameMatch(T9CPFieldInfo *pT9CPFieldInfo,
                                  T9UINT fIsSID,
                                  T9CP_NameTableBookmark *pBookmarks,
                                  T9U8 *pbTones,
                                  T9U8 *pbIsExact,
                                  T9U8 fFindPhrase);
/* End don't mangle the function name if compile under C++ */
#if defined(__cplusplus)
    }
#endif

#endif	/* #ifndef T9CPNAME_H */

/* ----------------------------------< eof >--------------------------------- */
