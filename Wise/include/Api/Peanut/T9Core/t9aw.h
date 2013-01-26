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
;**     FileName: T9aw.h                                                      **
;**                                                                           **
;**  Description: General declarations private to the Alpha Word edition.     **
;**                                                                           **
;*******************************************************************************
;******************************************************************************/

#ifndef T9AW_H
#define T9AW_H    1

#include "t9awapi.h"

/* don't mangle the function name if compile under C++ */
#if defined(__cplusplus)
extern "C" {
#endif

/*----------------------------------------------------------------------------
 *  The type of fully built word, as significant to selection-list building.
 *----------------------------------------------------------------------------*/
enum {
    CDBTERM, /* A completely specified CDB object. */
    REORDERWORD, /* A completely specified reorder or high-freq custom UDB entry. */
    UDBTERM, /* A completely specified low-freq. UDB entry. */
    MDBTERM, /* A completely specified MDB entry. */
    LDBWORD, /* A completely specified MDB entry. */
    TERMINAL_WORD = LDBWORD, /* Marker for highest index of terminal word. */
    RUDBSTEM, /* A UDB (custom or reorder) word whose start matches keys. */
    MDBSTEM,  /* An MDB word whose start matches keys. */
    CDBSTEM,  /* A CDB word whose start matches keys. */
    NOWHERE /* Build-around word.
               Corresponds to all entries but FULLMATCH in the enum with FULLMATCH.  */
};
/* Note that NOWHERE must equal T9AW_NUMSUBCOUNTS - 1. */

/*---------------------------------------------------------------------------
 *      enum for indexing wbSubCounts array
 *---------------------------------------------------------------------------*/
enum {
    LDB_TOTAL,  /* total number of words found in the ldb */
    LDB_TERM,   /* number of words found in the ldb that are known to be terminal */
    UDB_TOTAL, /* total number of matches: stems and terms, custom and ldb. */
    UDB_TERM,  /* number of terminal custom words whose frequency is such 
                that they don't make it to the reorder section of the list.*/
    MDB_TOTAL,
    MDB_TERM,
    CDB_TOTAL,
    CDB_TERM,
    RUDB_HIFREQ    /* number of ldb and custom words that are reordered to the top. */
};
/* Note that RDB must equal T9AW_NUMSUBCOUNTS - 1. */

/*----------------------------------------------------------------------------
 *  Misc control constants for word building.
 *----------------------------------------------------------------------------*/
#define NO_TERM_REQUESTED 0
#define TERM_REQUESTED    1
#define JUSTCOUNT                  0

/*----------------------------------------------------------------------------
 *  Build-around regions.
 *----------------------------------------------------------------------------*/
enum {
    FULLMATCH, /* The word is fully specified.  The pwSelListSubCnts array for
                  this includes the AUTOPUNCT count.
                  This corresponds to all entries but NOWHERE in the enum
                  with NOWHERE. */
    TRAILPUNCT, /* Build-around: LLLLP LLLL, e.g. "l'homme" */
    LEADPUNCT,  /* Build-around: LLLL PLLLL, e.g. "aol.com" */
    EMBPUNCT,   /* Build-around: LLLL P LLLL, e.g. "peut-etre" */
    AUTOPUNCT   /* Word from DB + default trailing punct.  No entry in pwSelListSubCnts */
};

/* Note that EMBPUNCT must equal T9AW_NUMSELLISTSUBCNTS - 1. */

#define CDB_COMPLETION_ON(info) (info->G.dwStateBits & T9STATECDBCOMPLETIONMASK)
#define CDB_PREDICTION_ON(info) (info->G.dwStateBits & T9STATECDBPREDICTIONMASK)

#define T9_AWFULLCHECKINFO(pAWFieldInfo)                                                        \
    if (! pAWFieldInfo) return(T9STATABORT);                                                    \
    if (pAWFieldInfo->G.T9Private.wInitOK != T9_GOODSETUP) return T9STATNOINIT;                 \
    if ((pAWFieldInfo->G.nLdbNum & T9PIDMASK) == T9PIDKorean)                                    \
        return T9STAT_NODATAMODULE;                                                             \
    if ((pAWFieldInfo->G.T9PrivateLdb[pAWFieldInfo->G.bActiveLangIndex].wLangOK != T9_GOODSETUP) ||  \
        (pAWFieldInfo->G.T9PrivateLdb[0].wLangOK != T9_GOODSETUP))   \
        return (T9STATNOLANG);

/*----------------------------------------------------------------------------
 *  Defines and Functions shared between files in T9Alpha.
 *----------------------------------------------------------------------------*/
#define MULTITAP_ON(statebits)  (statebits & T9STATEMULTITAPMASK)

T9STATUS T9FARCALL T9AW_MultitapFlushKey(T9AWFieldInfo *pAWFieldInfo);
T9UINT T9FARCALL T9AW_WordIsTermPunct(T9AWFieldInfo *pAWFieldInfo, T9UINT nCursor,
                               T9UINT nComplLen, T9UINT nObjNumRaw, T9UINT nWordLen);
T9STATUS T9FARCALL T9AW_FlushWord(T9AWFieldInfo *pAWFieldInfo, T9MINOR mFlushType);
T9STATUS T9FARCALL T9AW_StartFresh(T9AWFieldInfo *pAWFieldInfo);
T9UINT   T9FARCALL T9AW_BuildLdbObject(T9AWFieldInfo *pAWFieldInfo, T9UINT nLdbObjNum,
                                       T9UINT nWordLen, T9UINT nCursor,
                                       T9U8   bLead,
                                       T9U8 *pbTerminal, T9U8 *pbPrevIndex,
                                       T9SYMB *psBuildTxtBuf,
                                       T9UINT *pnLdbObjCnt);
T9UINT T9FARCALL T9AW_BuildLdbObjectFromKeys(T9AWFieldInfo *pAWFieldInfo,
                                             T9UINT nLdbObjNum,
                                             T9UINT nFullWordLen,
                                             T9UINT nWordLen,

                                             T9U8  *pbTerminal,
                                             T9U8  *pbPrevIndex,
                                             T9SYMB *psBuildTxtBuf,
                                             T9UINT *pnLdbObjCnt,
                                             T9AuxType *paAuxBuf,
                                             T9UINT nBuildTxtBufSize);
T9UINT T9FARCALL T9AW_FindFirstLdbObject(T9AWFieldInfo *pAWFieldInfo,
                                 T9SYMB      *psObjectToFind,
                                 T9AuxType     *paKeySrc,
                                 T9UINT        nWordLen,
                                 T9UINT       *pnObjNumRaw);
T9STATUS T9FARCALL T9AW_HandleMultitapKey(T9AWFieldInfo *pAWFieldInfo, T9KEY eKeyID);
T9STATUS T9FARCALL T9AW_SelectWord(T9AWFieldInfo *pAWFieldInfo);
T9STATUS T9FARCALL T9AW_GetConstrainedSelectWord(T9AWFieldInfo *pAWFieldInfo);
T9MINOR T9FARCALL T9AW_IsPunctKey(T9AWFieldInfo *pAWFieldInfo,
                                   T9AuxType aKey);
T9AuxType T9FARCALL T9AW_AddShiftState(T9AWFieldInfo *pAWFieldInfo, T9AuxType aKey);
T9STATUS T9FARCALL T9AW_AddExplicitKey(T9AWFieldInfo *pAWFieldInfo,
                                              T9SYMB         sSymbol, 
                                              T9AuxType      aKey, 
                                              T9UINT nInternalSource);
T9STATUS T9FARCALL T9AW_SubAmbiguousKey(T9AWFieldInfo *pAWFieldInfo);
T9STATUS T9FARCALL T9AW_AddAmbiguousKey(T9AWFieldInfo *pAWFieldInfo, 
                                               T9AuxType      aKey);
T9STATUS T9FARCALL T9AW_DoSpaceProcessing(T9AWFieldInfo *pAWFieldInfo);
void T9FARCALL T9AW_ForgetBuildInfo(T9AWFieldInfo *pAWFieldInfo);
T9STATUS T9FARCALL T9AW_InitFromLDBHeader(T9AWFieldInfo *pAWFieldInfo,
                                                 T9U32         *pdwCSUnsupportVal);
T9STATUS T9FARCALL T9AW_GetNextFilteredObject(T9AWFieldInfo *pAWFieldInfo,
                                                     T9INT nTraverseNext,
                                                     T9UINT nContextMatchAllowed);

T9STATUS T9FARCALL T9AW_SetActiveLang(T9AWFieldInfo *pAWFieldInfo, T9U8 bIndex);

T9STATUS T9FARCALL T9AW_SetPrincLang(T9AWFieldInfo *pAWFieldInfo, T9U8 bIndex);

#if defined(__cplusplus)
}
#endif

#endif

/* ----------------------------------< eof >--------------------------------- */
