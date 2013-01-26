/*******************************************************************************
;*******************************************************************************
;**                                                                           **
;**                    COPYRIGHT 1998-2006 TEGIC COMMUNICATIONS               **
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
;**     FileName: t9awudb.h                                                     **
;**                                                                           **
;**  Description: User data base access routines header file.                 **
;**               Conforms to Version 3.0                                     **
;**                                                                           **
;*******************************************************************************
;******************************************************************************/

#ifndef T9AWUDB_H
#define T9AWUDB_H    1

/* don't mangle the function name if compile under C++ */
#if defined(__cplusplus)
extern "C" {
#endif

/*
 * Aging interval, roughtly 50 minutes use of T9 for
 * an average user which can type 20wpm using T9.
 */
#define T9UDBMAXUPDATE              ((T9U16)1000)
#define T9UDBAGGINGFACTOR           32
#define T9MAX_FREQ_COUNT            ((T9U16)(64000)) /* Max Freq. resolution */
#define T9FREQ_BUMP_COUNT           ((T9U16)(64))    /* Freq. bump amount */

/* initial freq. for non-first word (or first word of ldb word completion on) */
#define T9RD_WORD_INIT_FREQ         (54)

/* initial freq. for first-word */
#define T9RD_FIRST_WORD_INIT_FREQ   (150)

/* initial freq. for add word */
#define T9AW_WORD_INIT_FREQ         (160)

/* initial freq. for auto-scan udb word */
#define T9AT_WORD_INIT_FREQ         (5)

/* Minimum word length before LDB word completions. */
#define T9DEFAULTWORDLENFORRDBSTEMS 3

/* Minimum and maximum number of characters that can be required before RDB completions appear. */
#define T9MIN_CHARS_REQUIRED_FOR_RDB_COMPLETION 1
#define T9MAX_CHARS_REQUIRED_FOR_RDB_COMPLETION 3

#define T9LOBYTE(w)      ((T9U8)(w))
#define T9HIBYTE(w)      ((T9U8)(((T9U16)(w) >> 8)))

#define OVERWRITE 0
#define ONLYIFNEEDED 1

enum T9ProcessUdb {
    ONLYIFWORDCOMPOUNDED, /* Process word from ambig mode.      */
    SCANFORWORDS,         /* Process word fromT9AWUdbScanBufForCustWords. */
    IFDIRTYORNOTINLDB     /* Process word from multitap. */
/* Note that those three ways of processing UDB words check the LDB before */
/* adding any word in the UDB. */
};

typedef enum {UDB_CUSTOM_REC, UDB_CUSTOM_EXPLICIT_REC, UDB_REORDER_REC, UDB_FREE_REC}
    UdbRecTypes;


#define UDB_IS_CUSTOM(eType) ((eType) == UDB_CUSTOM_REC || (eType) == UDB_CUSTOM_EXPLICIT_REC)

typedef T9U8 T9FARUDBPOINTER * UdbBodyPtr;

typedef struct {
    T9U16 wFreq;    /* frequency of the word */
    T9U8  bLen;     /* length of the word */
    T9U8  bType;    /* UdbRecTypes, but compacted into 1 byte. */
    T9U8  bLdbId;   /* Language Id for Reorder word, 0 for Add word */
    T9U8  bLdbObj;  /* Ldb object number for Reorder word, 0 for Add word */

    /*
     * Add word store actual symbols in the UDB where as
     * Reorder word stores only keys where each byte store
     * two keys, one nibble per key.
     */
    UdbBodyPtr pbByte;
} T9RUdbWord;

extern T9UINT T9FARCALL T9AW_ProcessWordForUdb(T9AWFieldInfo *pAWFieldInfo,
                                       T9SYMB  *psTxtBuf,
                                       T9AuxType   *paAuxBuf,
                                       T9UINT   nTxtBufLen,
                                       T9UINT   nHowToProcess);

extern void T9FARCALL T9UdbUpdateCounter(T9AWFieldInfo *pAWFieldInfo, T9U8 value);

extern void T9FARCALL T9AW_MarkWordUse(T9AWFieldInfo *pAWFieldInfo, T9UINT nTestWordLen,
                                 T9UINT nTestCursor, T9UINT nTestComplLen,
                                 T9UINT ObjNum,
                                 T9U8  bHowBuilt);

extern T9UINT T9FARCALL T9AW_CompareSymbolWord(T9SYMB T9FARUDBPOINTER *psWordOne,
                                       T9SYMB T9FARUDBPOINTER *psWordTwo,
                                       T9UINT nWordLen);
extern T9UINT T9FARCALL T9AW_GetUdbObject(T9AWFieldInfo *pAWFieldInfo,
                           T9UINT nUdbObjNum,
                           T9UINT nWordLen,
                           T9UINT nCursor,
                           T9U8   bLead,
                           T9U8  bObjectType,
                           T9UINT *pnTerminal,
                           T9U8  bRightMost,
                           T9SYMB *psBuildTxtBuf,
                           T9UINT nBuildTxtBufSize,
                           T9UINT *pnComplLen,
                           T9UINT *pnUdbObjCnt,
                           T9UINT *pnUdbAddWordCutOffCount,
                           T9UINT *pnReorderWordCutOffCount,
                           T9U32 *pdwObjsFromRdbMask);

extern T9STATUS T9FARCALL T9AW_BuildKeysFromText(T9AWFieldInfo *pAWFieldInfo,
                                             T9AuxType *paKeys,
                                             T9SYMB *psTxt,
                                             T9UINT nNumKeys,
                                             T9UINT  nBuildType);

extern T9UINT T9FARCALL T9AW_FindSpacesAndUnknown(T9AWFieldInfo   *pAWFieldInfo,
                                            T9SYMB      *psTxtBuf,
                                            T9UINT        nBufLen);

extern T9STATUS T9FARCALL T9AW_CompWordToKey(T9AWFieldInfo    *pAWFieldInfo,
                                     T9UINT           nWordLen,
                                     T9SYMB T9FARDATA *psDbSrc,
                                     T9AuxType T9FARDATA *paKeySrc);

extern void T9FARCALL T9AW_ZeroOutUdbOffsetInfo(T9AWFieldInfo *pAWFieldInfo);

#ifdef _DEBUG
extern T9STATUS T9FARCALL T9AW_UdbGetRecord(T9AWFieldInfo *pAWFieldInfo,
                                     UdbRecTypes *peRecordType, T9UINT *pnWordLen,
                                     T9U16 *pnWordFreq, T9U16 *pwWordLangID,
                                     T9U8  *pbWordObjNum, T9AuxType *paWordKeys,
                                     T9SYMB *psWordSyms,
                                     UdbBodyPtr *pNextRecord);
#endif

/* The following definitions relate to the T9AWUdbInfo structure
** defined in the T9api.h file.
*/

/* The Udb data area pointer */
#define UDB_bCharOnKeySize(pUdb)   \
    ((pUdb)->pbFirstCharOnKey[T9MAXDBKEYS] * T9SYMBOLWIDTH)

/* The Udb data area pointer */
#define UDB_pbBodyPtr(pUdb)        \
    ((UdbBodyPtr)((pUdb)->bDataArea + UDB_bCharOnKeySize(pUdb)))

/* The pointer for one key section */
#define UDB_pbKeyPtr(pUdb, aKey)   \
    ((UdbBodyPtr)(UDB_pbBodyPtr(pUdb) + (pUdb)->wKeyOffset[aKey]))

/* The Udb KeyToSym table */
#define UDB_psCharsOnKey(pUdb)     \
    ((T9SYMB T9FARUDBPOINTER *)(pUdb)->bDataArea)

/* Macro to get actual number of bytes in the udb header area */
#define UDB_nHeaderSize(pUdb)      \
    ((T9UINT)((UdbBodyPtr) (pUdb)->bDataArea - (UdbBodyPtr) (pUdb)))

/* Macro to get actual number of bytes in the udb data area */
#define UDB_nBodySize(pUdb)        \
    ((T9UINT)((pUdb)->wDataSize - UDB_nHeaderSize(pUdb) - UDB_bCharOnKeySize(pUdb)))

/* Macro to get ptr to the end of udb data area */
#define UDB_pbEnd(pUdb)            \
    ((UdbBodyPtr) ((UdbBodyPtr) (pUdb) + (pUdb)->wDataSize))

#define T9NUMSORTEDUDB  0x0a


typedef enum {T9TUDB_INVALID_REC, T9TUDB_CUSTOMWORD_REC, T9TUDB_REORDERWORD_REC}
    T9TUdbRecTypes;

typedef enum {T9TUDB_REORDERWORD_INVALID, T9TUDB_REORDERWORD_LEN, T9TUDB_REORDERWORD_FREQ,
    T9TUDB_REORDERWORD_KEYS, T9TUDB_REORDERWORD_LDBNUM, T9TUDB_REORDERWORD_OBJNUM }
    T9TUdbReorderWordAttr;

typedef enum {T9TUDB_CUSTOMWORD_INVALID, T9TUDB_CUSTOMWORD_LEN, T9TUDB_CUSTOMWORD_FREQ,
    T9TUDB_CUSTOMWORD_KEYS, T9TUDB_CUSTOMWORD_SYMBOLS }
    T9TUdbCustomWordAttr;

#if defined(__cplusplus)
}
#endif

#endif /* T9UDB_H */


/* eof */
