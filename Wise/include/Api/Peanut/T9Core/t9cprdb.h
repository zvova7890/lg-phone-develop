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
;**     FileName: t9cprdb.h                                                   **
;**                                                                           **
;**  Description: Chinese PTI RDB header file.                                **
;**               Conforming to the development version of PTI.               **
;**                                                                           **
;*******************************************************************************
;******************************************************************************/

#ifndef T9CPRDB_H
#define T9CPRDB_H 1

#ifndef T9CPNORDB /* use RDB */

/* don't mangle the function name if compile under C++ */
#if defined(__cplusplus)
extern "C" {
#endif

/*----------------------------------------------------------------------------
 *  Define the RDB parameters and constants.
 *----------------------------------------------------------------------------*/

/* constants related to an entry */
#define NONFREETYPEMASK         (0x80)  /* whether the obj is non-free type */
#define RDBTYPEMASK             (0x40)  /* whether the obj is RDB type */
#define LANGMASK                (0x20)  /* indicate the obj's language */
#define MINWORDSIZE             1       /* min word size of an entry */
#define WORDSIZEMASK            (0x1F)  /* mask for word size */
#define FREESIZEFLAG            (0x40)  /* whether the free obj uses 2 bytes for entry size */
#define MAXFREESIZE             (0x3FFF)/* max size of a free entry */
#define FREESIZEUPPERMASK       (FREESIZEFLAG - 1) /* mask for upper byte of a free entry's size */
/* bit masks for get entry operation */
#define GETTYPE         0x01
#define GETENTRYSIZE    0x02
#define GETFREQ         0x04
#define GETID           0x08
#define GETCHECKSUM     0x10

#define MAXUPDATECOUNT          ((T9U16)500)    /* max update count before rescale */
#define MAXFREQ                 ((T9U16)64000)  /* max frequency */
#define MINFREQ                 ((T9U16)1)      /* min frequency */
#define RDB_INITFREQ            ((T9U16)64)     /* initial freq for RDB words */
#define UDB_INITFREQ            ((T9U16)400)    /* initial freq for UDB words */
#define FREQ_RISE               ((T9U16)88)     /* freq rise for one usage */
#define T9CP_UDBRESCALEFACTOR   32              /* freq rescale factor */
#define T9CP_UDBCUTOFFLEVELS    5               /* number of estimated cutoff freq levels */
#define T9CP_UDBMINCUTOFF       ((T9U16)10)     /* min cutoff freq */
#define T9CP_UDBMINFREEFACTOR   20      /* min factor (1/20) of free space before overcrowded */
#define T9CP_UDBMINCLEANUPFACTOR    20  /* min factor (1/20) to clean during clean up */

/* Given a == hi byte, b == lo byte; compose a word integral (T9U16). */
#ifndef T9MAKEWORD
#define T9MAKEWORD(a, b) ((T9U16)((T9U8)(b) | ((T9U16)((T9U8)(a)) << 8)))
#endif
#ifndef T9LOBYTE
#define T9LOBYTE(w)      ((T9U8)(w))
#endif
#ifndef T9HIBYTE
#define T9HIBYTE(w)      ((T9U8)((T9U16)(w) >> 8))
#endif
/* entry size = 3 + 2 * (word size) */
#define WordSizeToEntrySize(bWordSize) ((T9U8)(3 + ((bWordSize) << 1)))
/* word size  = ((entry size) - 3) / 2 */
#define EntrySizeToWordSize(wEntrySize) ((T9U8)(((wEntrySize) - 3) >> 1))

/* next zone */
#define NextZone(b) ((b + 1) % T9CP_UDBZONEMAX)

/* Macros related to the T9CPUdbInfo structure in the t9cpapi.h */

/* The pointer to UDB data area */
#define T9UdbData(udb) ((T9U8 T9FARUDBPOINTER*)((udb)->bDataArea))

/* The pointer to the byte following the end of UDB */
#define T9UdbEnd(udb) ((T9U8 T9FARUDBPOINTER*)(udb) + (udb)->wDataSize)

/* The actual number of bytes in the UDB header area */
#define T9UdbHeaderBytes(udb)    \
            ((T9UINT)(T9UdbData(udb) - (T9U8 T9FARUDBPOINTER*)(udb)))

/* The actual number of bytes in the UDB data area */
#define T9UdbDataAreaBytes(udb)    \
            ((T9UINT)((udb)->wDataSize - T9UdbHeaderBytes(udb)))

#define UdbPtrToOffset(udb, ptr) ((T9U16)((ptr) - T9UdbData(udb)))

#define UdbOffsetToPtr(udb, offset) (T9UdbData(udb) + (offset))

/*----------------------------------------------------------------------------
 *  Define the RDB structure and variable types.
 *----------------------------------------------------------------------------*/

typedef enum EntryType_e {
    FREE = 0,
    RDBPHONETIC = 1,
    RDBSTROKE = 2,
    UDBPHONETIC = 3,
    UDBSTROKE = 4
} EntryType;

typedef struct RUdbObj_s {
    EntryType   eType;  /* Entry type */
    /* T9U8        bLang;   reserved for future use */
    T9U16       wEntrySize; /* bytes occupied by the entry == 3 + 2w (where w == word length) */
    T9U16       wFreq;  /* word frequency (FREE entry: undefined) */
    T9U16       pwID[T9CPMAXPHRASESIZE]; /* Phonetic entry: Phonetic ID,
                                            Stroke entry: Stroke ID,
                                            FREE entry: undefined */
} RUdbObj;

/*----------------------------------------------------------------------------
 *  Declare prototypes for RDB functions internal to the core
 *----------------------------------------------------------------------------*/

#if defined(T9_DEBUG)
/* The following functions are exposed only for debug config */
/*------------------------------------------------------------------------
 *  Function    : T9CP_MoveUdbPR
 *
 *  Synopsis    : Move a UDB pointer to the right by the given amount.
 *                Wrap around at UDB end.
 *
 *     Input:   : pUdb = pointer to UDB
 *                pbThis = pointer to start of the move
 *                wNumMoves = number of bytes of the move amount
 *
 *    Output    : none
 *
 *    Return    : result pointer after the move
 *-----------------------------------------------------------------------*/
T9FARPOINTER T9FARCALL T9CP_MoveUdbPR(T9CPUdbInfo T9FARUDBPOINTER *pUdb,
                                      T9FARPOINTER pbThis,
                                      T9U16 wNumMoves);

/*------------------------------------------------------------------------
 *  Function    : T9CP_GetEntryInfo
 *
 *  Synopsis    : Get requested info of an entry into the result obj.
 *
 *     Input:   : pUdb = pointer to the UDB
 *                pbData = pointer to the start of the entry
 *                bOption = specify which field(s) of the entry is needed
 *
 * Input/Output : pObj = obj containing info of the entry.
 *
 *    Return    : checksum of the entry if requested, 0 otherwise.
 *-----------------------------------------------------------------------*/
T9U16 T9FARCALL T9CP_GetEntryInfo(T9CPUdbInfo T9FARUDBPOINTER *pUdb,
                                  T9FARPOINTER pbData,
                                  RUdbObj *pObj,
                                  T9U8 bOption);
#endif /* END T9_DEBUG */

/* Test this thread's cached update ID against the update ID from UDB header
 * return : 1 = match or no UDB; caller doesn't need to do anything
 *          0 = mismatch (Note: caller should return T9CPSTAT_RESETKEYS to integration layer */
T9U8 T9FARCALL T9CP_UdbTestUpdateID(T9CPFieldInfo *pT9CPFieldInfo);

/* Description : Check if the UDB is compatible with the LDB.
 * Return      : T9STAT_NO_UDB if has a UDB and the UDB is incompatible with LDB.
 */
T9STATUS T9FARCALL T9CP_CheckUdbCompat(T9CPFieldInfo *pT9CPFieldInfo);

/*------------------------------------------------------------------------
 *  Function    : T9CP_UdbUsePhrase
 *
 *  Synopsis    : Update the UDB in respond to the use of a phrase.
 *
 *     Input:   : pT9CPFieldInfo = pointer to PTI field info
 *                pPhrase = pointer to the phrase that was used.
 *                eEncode = ID encoding (either PID or SID)
 *                wFreq = (> 0): to use this frequency for the phrase
 *                              (overwrite frequency for existing phrase)
 *                        0: to use default frequency.
 *                bIsUObj = 1: to create a UDB phrase
 *                          0: otherwise
 *    Return    : none
 *-----------------------------------------------------------------------*/
void T9FARCALL T9CP_UdbUsePhrase(T9CPFieldInfo *pT9CPFieldInfo,
                                 T9CPPhraseInfo *pPhrase,
                                 T9CP_IDEncode eEncode,
                                 T9U16 wFreq,
                                 T9U8 bIsUObj);

/*---------------------------------------------------------------------------
 *
 *   Function: T9CP_GetUdbPhrases
 *
 *   Synopsis: This function searches the UDB to find any phrases that
 *             match the given context prefix and the current keys, which is
 *             in a form of ID ranges in pT9CPFieldInfo. Then add the matching
 *             phrases into the phrase buffer.
 *
 *      Input: pT9CPFieldInfo = Pointer to PTI field info structure.
 *             pwPrefix       = the context prefix in PID/SID
 *             bPrefixLen     = the context prefix length.
 *             bIsSID         = 0 - ID is encoded in PID;
 *                              1 - ID is encoded in SID;
 *             bGetToneOption = 0 - do not get tone options and phrases are added
 *                                  into phrase buffer.
 *                              1 - get tone options and phrases are not added into
 *                                  phrase buffer.
 *             pbTones        = array of 32 Tones (32 bytes) in phonetic mode.
 *                              NULL if in stroke mode.
 *     In/Out: pbValidate     = if NULL, the function will search the UDB,
 *                              find matching phrases and add them into the phrase buffer.
 *                              else, *pbValidate = 1 if found any matching phrases (return at once)
 *                                    *pbValidate = 0 if not found.
 *     Output: pbToneOptions  = if bGetToneOption is 1, it stores the retrieved tone options. 
 *                              Its format is one byte and bit arrangement is: 000xxxxx.
 *                              Least significant bit is for tone 1.
 *                              2nd least significant bit is for tone 2, etc.
 *
 *     Return: none
 *
 *---------------------------------------------------------------------------*/
void T9FARCALL T9CP_GetUdbPhrases(
                    T9CPFieldInfo *pT9CPFieldInfo,
                    T9U16 *pwPrefix,
                    T9U8 bPrefixLen,
                    T9U8 *pbValidate,
                    T9U8 bIsSID,
                    T9U8 bGetToneOption,
                    T9U8 *pbToneOptions,
                    T9U8 *pbTones,
                    T9U8 bValidateCntxPrefix);

/* 
 * Function: T9CP_UdbFindDelUIDMatch
 * Synopsis: Find 1st or Delete all phrases that exactly match the given Unicode
 * Input:    psPhrase = given Unicode
 *           eEncode = encoding of pwAltID (PID/BID/SID)
 *           pwAltID = array of all alt ID of 1st Unicode
 *           bAltCount = number of alt ID in pwAltID
 * In/Out:   psIDPhrase = 0: delete all phrases that match the given Unicode
 *                        non-zero: store PID/SID of the 1st match found
 *                        
 * Return : non-zero if at least one phrase is found/deleted;
 *          0 otherwise.
 */
T9UINT T9FARCALL T9CP_UdbFindDelUIDMatch(T9CPFieldInfo *pT9CPFieldInfo,
                                         T9CPPhraseInfo *psPhrase,
                                         T9CPPhraseInfo *psIDPhrase,
                                         T9CP_IDEncode eEncode,
                                         T9U16 *pwAltID,
                                         T9U8 bAltCount);
#ifndef T9CP_DISABLE_PHONETIC

void T9FARCALL T9CP_AddUdbSpells(T9CPFieldInfo *pT9CPFieldInfo);

#endif /* END use phonetic */

/* End don't mangle the function name if compile under C++ */
#if defined(__cplusplus)
    }
#endif

#endif /* END use RDB */

#endif  /* #ifndef T9CPRDB_H */

/* ----------------------------------< eof >--------------------------------- */
