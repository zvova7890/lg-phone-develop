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
;**     FileName: t9cpsldb.h                                                  **
;**                                                                           **
;**  Description: PTI stroke ldb access functions.                            **
;**                                                                           **
;*******************************************************************************
;******************************************************************************/

#ifndef T9CPSLDB_H
#define T9CPSLDB_H 1

/* don't mangle the function name if compile under C++ */
#if defined(__cplusplus)
extern "C" {
#endif
#ifndef T9CP_DISABLE_STROKE

typedef enum {
    T9CP_SID_NO_MATCH = 0,
    T9CP_SID_EXACT_MATCH,
    T9CP_SID_PARTIAL_MATCH,
    T9CP_SID_UNKNOWN_MATCH
} T9CP_SIDMatch;

void T9CP_StrokeKeysChangeInit(T9CPFieldInfo *pT9CPFieldInfo);
T9STATUS T9FARCALL T9CP_StrokeSelectPhrase(T9CPFieldInfo *pT9CPFieldInfo, T9CPPhraseInfo *psPhrase);
T9STATUS T9FARCALL T9CP_StrokeFillPhraseBuffer(T9CPFieldInfo *pT9CPFieldInfo);
T9STATUS T9FARCALL T9CP_StrokeGetPhrase(T9CPFieldInfo *pT9CPFieldInfo, T9CPGETTYPE eGetType, T9CPPhraseInfo *psPhrase);
T9U8 T9FARCALL T9CP_StrokeLookup(T9CPFieldInfo *pT9CPFieldInfo, T9U16 wSID, T9U8 *pbBuf, T9U8 bLen);
void T9CP_StrokeSetupKey(T9CPFieldInfo *pT9CPFieldInfo, T9U8 bKey);
T9STATUS T9FARCALL T9CP_StrokeAddKey(T9CPFieldInfo *pT9CPFieldInfo, T9U8 bKey);
T9STATUS T9FARCALL T9CP_StrokeDelLastKey(T9CPFieldInfo *pT9CPFieldInfo);
T9U16 T9FARCALL T9CP_SIDToTID(T9CPFieldInfo *pT9CPFieldInfo, T9U16 wSID);
T9U16 T9FARCALL T9CP_TIDToSID(T9CPFieldInfo *pT9CPFieldInfo, T9U16 wTID, T9U16 wStart, T9U16 wEnd);
void T9FARCALL T9CP_StrokeAddValidKeys(T9CPFieldInfo *pT9CPFieldInfo, T9U8 * pbKeySeq, T9U8 bKeySeqLen);
T9UINT T9FARCALL T9CP_IsLastStrokeValidForChar(T9CPFieldInfo *pT9CPFieldInfo);

#endif
/* End don't mangle the function name if compile under C++ */
#if defined(__cplusplus)
    }
#endif

#endif	/* #ifndef T9CPSLDB_H */
