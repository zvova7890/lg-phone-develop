/*******************************************************************************
********************************************************************************

                    COPYRIGHT 2003 TEGIC COMMUNICATIONS

                TEGIC COMMUNICATIONS PROPRIETARY INFORMATION

     This software is supplied under the terms of a license agreement
     or non-disclosure agreement with Tegic Communications and may not
     be copied or disclosed except in accordance with the terms of that
     agreement.

********************************************************************************

     File Name:   t9jw.h

     Description: Shared header file for Japanese edition of T9.


********************************************************************************
********************************************************************************/

#ifndef T9JW_H
#define T9JW_H

/*----------------------------------------------------------------------------
 * Japanese LDB class number
 *----------------------------------------------------------------------------*/

enum JT9LdbClass {
    JLC_UDBNoInflect        =1,     /* Word is not inflected */
    JLC_UDBInflect          =2,     /* Word is inflected */
    JLC_CmpWord             =3,
    JLC_VerbSahen           =4,
    JLC_VerbZahen           =5,
    JLC_VerbIchidan         =6,
    JLC_VerbKagyo           =7,
    JLC_VerbKagyoSoku       =8,
    JLC_VerbGagyo           =9,
    JLC_VerbSagyo           =10,
    JLC_VerbTagyo           =11,
    JLC_VerbNagyo           =12,
    JLC_VerbBagyo           =13,
    JLC_VerbMagyo           =14,
    JLC_VerbRagyo           =15,
    JLC_VerbRagyoSpe        =16,
    JLC_VerbWagyoSoku       =17,
    JLC_Adjective           =18,
    JLC_AdjNoun             =19,
    JLC_NounGeneral         =20,
    JLC_NounLName           =21,    /* Last names */
    JLC_NounFName           =22,    /* First names */
    JLC_NounGName           =23,    /* General names */
    JLC_NounPlace           =24,
    JLC_NounPronoun         =25,
    JLC_NounSahen           =26,
    JLC_NounNaiAdj          =27
};

/*----------------------------------------------------------------------------
 *
 *  Function prototypes for routines shared between modules
 *
 *----------------------------------------------------------------------------*/

/* Functions From t9jutils.c */
#include "t9jutils.h"
extern void       T9FARCALL T9JW_MInit(T9JW_MemMgr *pMemMgr, T9U16 wSize);
extern T9JW_HANDLE    T9FARCALL T9JW_MAlloc(T9JW_MemMgr *pMemMgr, T9U16 wSize);
extern void       T9FARCALL T9JW_MFree(T9JW_MemMgr *pMemMgr, T9JW_HANDLE hToFree);
extern HeapResult T9FARCALL T9JW_HInit(T9JW_MemMgr *pMemMgr,
                  T9JW_SortResult (*sfunc)(T9JW_MemMgr *memmgr, T9JW_HANDLE hObj1, T9JW_HANDLE hObj2),
                  T9JW_CmpResult  (*cfunc)(T9JW_MemMgr *memmgr, T9JW_HANDLE hOrig, T9JW_HANDLE hNew));
extern HeapResult T9FARCALL T9JW_HDestroy(T9JW_MemMgr *pMemMgr, void (*dfunc)(T9JW_MemMgr *memmgr, T9JW_HANDLE hObj));
extern HeapResult T9FARCALL T9JW_JHAdd(T9JW_MemMgr *pMemMgr, T9JW_HANDLE hItem, T9U16 wHash);
extern T9JW_HANDLE    T9FARCALL T9JW_HGet(T9JW_MemMgr *pMemMgr);
extern void       T9FARCALL T9JW_LDestroy(T9JW_MemMgr *pMemMgr, T9JW_HANDLE hLNode, void (*dfunc)(T9JW_MemMgr *memmgr, T9JW_HANDLE hObj));
extern void       T9FARCALL T9JW_Enqueue(T9JW_MemMgr *pMemMgr, T9JW_Queue *pQHdr, T9JW_HANDLE hNew);
extern T9JW_HANDLE    T9FARCALL T9JW_Dequeue(T9JW_MemMgr *pMemMgr, T9JW_Queue *pQHdr);

/* Functions From t9jldb.c */

extern T9STATUS T9FARCALL T9JW_InitializeLDB(T9JWFieldInfo *pJWFieldInfo);
extern void     T9FARCALL T9JW_InitBuilder(T9JWFieldInfo *pJWFieldInfo);
extern T9UINT   T9FARCALL T9JW_GetYomiReorderInfo(T9JWFieldInfo *pJWFieldInfo, T9U8 *pbSyms);
extern T9UINT   T9FARCALL T9JW_GetUdbSelMatchesCB(T9JWFieldInfo *pJWFieldInfo, T9SYMB *psYomi, T9UINT nMax, T9U8 bFlags);
extern T9U8     T9FARCALL T9JW_CharToSym(T9JWFieldInfo *pJWFieldInfo, T9SYMB sChar, T9SYMB sKey);
extern T9UINT   T9FARCALL T9JW_BuildMagicStringObj(T9JWFieldInfo *pJWFieldInfo, T9UINT nObjNum, T9UINT nMaxSize, T9SYMB *psObjBuf);
extern T9STATUS T9FARCALL T9JW_ReadKeyMTap(T9JWFieldInfo *pJWFieldInfo,
                              T9KEY eKey, T9UINT nDiacriticLevel,
                              T9SYMB *pSymb, T9U16 wPage,
                              T9U16 wSymbolPerPage, T9MINOR *pmNumTapRetrieved);


/* Functions From t9jmdb.c */
extern T9U32    T9FARCALL T9JW_CountMdbSelMatches(T9JWFieldInfo *pJWFieldInfo, T9U8 bRequestType, T9UINT nLength);
extern T9UINT   T9FARCALL T9JW_GetMdbSelMatches(T9JWFieldInfo *pJWFieldInfo, T9UINT nWordLen, T9U8 bRequestType);
extern T9UINT   T9FARCALL T9JW_GetMdbSelMatchesCB(T9JWFieldInfo *pJWFieldInfo, T9SYMB *psYomi, T9UINT nMax, T9U16 wClass, T9U8 nFreq);
extern T9UINT   T9FARCALL T9JW_CmpWordToKey(T9JWFieldInfo *pJWFieldInfo, T9UINT nWordLen, T9SYMB T9FARDATA *psTxtSrc, T9AuxType T9FARDATA *paKeySrc);

/* From t9judb.c */
#define T9MINJUDBSIZE 512
typedef enum {UT_UDB1 = 1, UT_UDB2, UT_YRDB} UDBType;

extern T9UINT   T9FARCALL T9JW_IsYomiReordered(T9JWFieldInfo *pJWFieldInfo, T9U8 *pbSyms, T9U8 *pAsPerson);
extern T9UINT   T9FARCALL T9JW_GetUdbSelMatches(T9JWFieldInfo *pJWFieldInfo, T9UINT nWordLen, T9UINT nLenClass);
extern T9U32    T9FARCALL T9JW_CountUdbSelMatches(T9JWFieldInfo *pJWFieldInfo, T9UINT nLenClass);
extern T9STATUS T9FARCALL T9JW_JUdbActivate(T9JWFieldInfo *pJWFieldInfo,  T9JWUdbInfo T9FARUDBPOINTER *pUdbInfo, T9U16 wDataSize, T9U16 wMinSize);
extern T9STATUS T9FARCALL T9JW_AddJUdbObject(T9JWFieldInfo *pJWFieldInfo, const T9SYMB *psYomi, const T9U8 bYomiSize, const T9U8 bUdbType);
extern T9STATUS T9FARCALL T9JW_ForceUpdateYomiReorderDB (T9JWFieldInfo *pJWFieldInfo, const T9SYMB *psYomi, const T9U8 bYomiSize);
extern T9STATUS T9FARCALL T9JW_DeleteUdbWordByTargetWord(T9JWFieldInfo *pJWFieldInfo, const T9SYMB *psBuf,  const T9MINOR mBufLen);
extern T9STATUS T9FARCALL T9JW_UdbCheckSpace(T9JWFieldInfo *pJWFieldInfo, T9UINT *pnResponse);
extern T9U16    T9FARCALL T9JW_GetJUdbChecksum(const T9JWUdbInfo T9FARUDBPOINTER *pUdb);
extern T9STATUS T9FARCALL T9JW_UpdateYomiReorderDB(T9JWFieldInfo *pJWFieldInfo);
extern void     T9FARCALL T9JW_UpdateJUdbYomiTimestamp(T9JWFieldInfo *pJWFieldInfo);
extern T9STATUS T9FARCALL T9JW_UdbGetNthWord (T9JWFieldInfo *pJWFieldInfo, T9UINT nIndex, T9SYMB *psBuf, T9MINOR* mBufLen);

/* From t9jword.c */
extern T9STATUS T9FARCALL T9JW_GetAutoWordDBList(T9JWFieldInfo *pJWFieldInfo,
									 T9SYMB*  psTarget,   T9U8   bTargetLen,
									 T9SYMB** psYomiList, T9U8** bYomiListLen,
								     T9SYMB** psList,     T9U8** bListLen,
									 T9U8     bCandidateCount,
	                                 T9U8     bMatchChar, T9U8*  pbCharMatchCount, T9U8* pbKeyMatchCount,
									 T9U8     bIndex);

extern T9STATUS T9FARCALL T9JW_AddOdjToAutoWordDB(T9JWFieldInfo *pJWFieldInfo,
									const T9SYMB *psInYomi,
									T9U8   bYomiInSize,
                                    const T9SYMB *psInMida,
									T9U8   bMidaInSize);

extern T9STATUS T9FARCALL T9JW_CheckAutoCompleteDataSum(T9JWFieldInfo *pJWFieldInfo);
#endif /* T9JW_H */

/*---------------------------------- eof ---------------------------------*/
