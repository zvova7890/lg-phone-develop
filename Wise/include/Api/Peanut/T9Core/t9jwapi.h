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
;**     FileName: t9jwapi.h                                                     **
;**                                                                           **
;**  Description: T9 Japanese API Interface Header File.                      **
;**                                                                           **
;*******************************************************************************
;******************************************************************************/

#ifndef T9JWAPI_H
#define T9JWAPI_H 1

/* don't mangle the function name if compile under C++ */
#if defined(__cplusplus)
extern "C" {
#endif

#include "t9.h"

/* Language extension define constants - Japanese */
#define NUM_CLASS_NIBBLE_RANGES     (4)
#ifndef T9MAXMDBWORDSIZE
#define T9MAXMDBWORDSIZE T9_MAXLDBWORDSIZE
#endif
#ifndef T9JWMAXMDBWORDSIZE
#define T9JWMAXMDBWORDSIZE T9_MAXLDBWORDSIZE
#endif
#if (T9JWMAXMDBWORDSIZE > T9_MAXLDBWORDSIZE)
#define T9JWMAXWORDSIZE   T9_MAXLDBWORDSIZE
#else
#define T9JWMAXWORDSIZE   T9_MAXLDBWORDSIZE
#endif

/* All the memory the JT9 core code has to play with. */
#ifndef T9JW_MEMBLOCKSIZE
#define T9JW_MEMBLOCKSIZE  (1024 * 48)
#endif
#if T9JW_MEMBLOCKSIZE % 4 != 0
#error T9JW_MEMBLOCKSIZE must be a multiple of four.
#endif

#ifndef T9JWYOMIREORDERCOUNT
/* Number of yomis to reprioritize in selection list.
 * Can be customized in xxt9oem.h file.  If not customized, the
 * default is defined here. */
#define T9JWYOMIREORDERCOUNT         3
#endif

/* Japanese UDBs. */
typedef struct T9JWUdbInfo_s {

    T9U16 wDataSize;        /* Total size in bytes of this struct (minimum is 1024) */
    T9U16 wDataCheck;       /* Additive checksum of database */
    T9U16 wUpdateCounter;   /* Count incremented each time user database modified */
    T9U16 wSymbolClass;     /* T9 enum value indicating symbol table mapping for this UDB */
    T9U16 wUdbWordCount;        /* Number of valid words currently in user database */
    T9U16 wAddDataAreaLen;      /* Length in symbol bytes of the used data area */

    T9U16 wWordCount;       /* For Japanese Core */

    /* new in 6.0 - for word reordering */
    T9U16 wRdbWordCount;    /* Number of reorder-word count */
    T9U16 wLastDelCutOffFreq;   /* Last deletion freq. cut-off by garbage collection */
    T9U16 wReorderDataAreaLen;  /* Number of bytes used by word reordering */
//@ T9SYMB sDataArea[1];          /* Really a variable size data array */
	T9SYMB sDataArea[JUDB_MAX_SIZE - 20];

} T9JWUdbInfo;

enum {
    T9JWNODIACRITIC,
    T9JWDAKUTEN,
    T9JWHANDAKUTEN
};

/*--------------------------------------------------------------------------- */
/* Additional key definitions to access special Japanese language processing  */
/* NOTE: T9KEYAMBIGA is used for number 0                                     */
#define T9JWDIACRITICADDER   10
#define T9JWKEYDIACRITIC     T9KEYAMBIGB
#define T9JWKEYSELECTNEXT    T9KEYAMBIGC
#define T9JWKEYSELECTPREV    T9KEYAMBIGD
#define T9JWEXPLICITMASK     ((T9AuxType)0x40)
#define T9JWKEYVALMASK       ((T9AuxType)0x1F)
#define T9JWKEYRAWVAL(x)     ((x) & T9JWKEYVALMASK)
#define T9JWKEYVAL(x)        (((T9JWKEYRAWVAL(x) - 1)  % T9JWDIACRITICADDER) + 1)
#define T9JWKEYGETDIACRITICLEVEL(x)   (((T9JWKEYRAWVAL(x) - 1) / T9KEYAMBIGA) == 2) ? T9JWHANDAKUTEN : ((((T9JWKEYRAWVAL(x) - 1) / T9KEYAMBIGA) == 1) ? T9JWDAKUTEN : T9JWNODIACRITIC)
#define T9JWHASDIACRITIC(x)  ((T9JWKEYGETDIACRITICLEVEL(x) == T9JWDAKUTEN) || (T9JWKEYGETDIACRITICLEVEL(x) == T9JWHANDAKUTEN))

/* Japanese MDB */

/*----------------------------------------------------------------------------
 *  Define T9 MDB request types
 *----------------------------------------------------------------------------*/
typedef enum T9JWREQMDB_e {
    T9JWMDBGETEXACTWORD = 1,   /* 1 */
    T9JWMDBGETSTEMWORD         /* 2 */
} T9JWREQMDB;

typedef struct T9JWFieldInfo_s T9JWFieldInfo;
typedef T9STATUS (T9FARCALL *T9JWMDBCALLBACK)(
    T9JWFieldInfo* pJWFieldInfo,             /* I   - T9 Field Info structure */
    T9U8                    bMdbRequestType, /* I   - MDB request type. Should be one of */
                                             /*       the values defined above.          */
    T9AuxType*              paAuxBuf,        /* I   - Pointer to T9 Aux buffer */
    T9UINT                  nWordLen,        /* I   - Word length */
    T9SYMB*                 psBuildTxtBuf,   /* O   - Word to return */
    T9UINT*                 pnMdbWordLen,    /* O   - Length of the returned MDB word */
    T9U32*                  pdwWordListIdx,  /* I/O - MDB word list index */
    T9U16*                  pwClass,         /* O   - Yomi absolute in class number */
    T9U8*                   pbFreq           /* O   - Yomi in-class frequency (betweem 0 - 15) */
    );

/*============================================================================
 * NOTE:
 *   The following definitions are private to AOL Mobile and are subject
 *   to change without notice.
 *============================================================================*/

#ifdef T9JW_DEBUGON
#include "assert.h"
#define T9JW_DEBUGFILTER(x)    x
#else
#define T9JW_DEBUGFILTER(x)
#endif

#define T9JW_MAXSYMSPERKEY    16  /* 4-bit char-on-key index */

/* Size of hash table.  Hash value must be less than this value. */
#define T9JW_HASHTABLESIZE     32  /* same as T9JWMAXWORDSIZE, by coincidence? */

/*--------------------------------------
 * Memory Manager And Heap Definitions
 *--------------------------------------*/

/* All memory allocated is referred to by this type.  Memory must be
 * dereferenced before use to get a valid address pointer. */
#define T9JW_HANDLE     T9U16

/* Results of sorting 2 elements */
typedef enum {
    T9JW_SREQUAL,
    T9JW_SRLOWER,              /* item 1 is lower priority than item 2 */
    T9JW_SRHIGHER              /* item 1 is higher priority than item 2 */
} T9JW_SortResult;

/* Result of comparing 2 elements */
typedef enum {
    T9JW_CRSAME,
    T9JW_CRDIFFERENT
} T9JW_CmpResult;

/*
 * Structure of elements in the heap.  Keep element dword-aligned.
 */
typedef struct {
    T9U16   wWhen;          /* timestamp when element was added to heap */
    T9JW_HANDLE hData;          /* data stored in the heap element */

    T9JW_HANDLE hHash;          /* handle to corresponding hash element */
    T9U16   wHshIndx;       /* index of element in hash table */
        /* Heap uses this info to locate the hash element corresponding to
         * this heap element.  The handle provides direct access to
         * update the heap index stored in the hash element when the
         * element moves in the heap.  The hash index narrows the search
         * for the hash element to remove it from the hash table when
         * the element is removed from the heap. */
} T9JW_HeapElt;


/*
 * Bookkeeping data for the heap.
 *
 * The heap contains the largest element at the top.  There is no limit
 * on the number of elements which may be added to the heap.
 *
 * The heap must be initialized with callback functions for sorting
 * 2 elements based on priority and for comparing 2 elements to see if
 * their contents are identical.
 */
struct T9JW_memmgr_s;                /* forward declaration of structure */
typedef struct {
        T9JW_SortResult (*sortCB)(struct T9JW_memmgr_s *memMgr, T9JW_HANDLE hObj1, T9JW_HANDLE hObj2);
                                /* Callback routine to sort 2 elements.
                                   If both elements are equal, the heap manager
                                   will break the tie using the timestamp. */

        T9JW_CmpResult  (*cmpCB)(struct T9JW_memmgr_s *memMgr, T9JW_HANDLE hOrig, T9JW_HANDLE hNew);
                                /* Callback routine to compare if 2
                                    elements are duplicates of each other.
                                    If elements are the same, the original
                                    object should be updated as needed.
                                    It will be reprioritized within the heap. */

        T9JW_HeapElt *theHeap;       /* the actual heap */
                                /* a reverse array - element N is at address 0,
                                    element 1 is at address N-1, etc. */

        T9JW_HANDLE hashTbl[T9JW_HASHTABLESIZE];
                                /* Hash table containing all heap elements.
                                 * Each table contains a list of elements
                                 * that hashed to the same value. */

        T9U16   wTimer;         /* counter for timestamping elements as they
                                are added to the heap */
        T9U16   wElts;          /* number of elements in the heap */

} T9JW_HeapMgr;

typedef struct T9JW_memmgr_s {

    T9U8     pbMemBase[T9JW_MEMBLOCKSIZE]; /* Our dynamic memory area */
    T9U8    *pbMemEnd;         /* end of memory allocation area marks
                                  the bottom of the heap */

    T9JW_HeapMgr hpMgr;             /* heap manager data */

    T9JW_HANDLE hFree;             /* first free memory blob */
    T9JW_HANDLE hLastfree;         /* last blob of free memory */

    T9JW_DEBUGFILTER(T9U16   wMemSize;)   /* total size of memory block, including heap */
    T9JW_DEBUGFILTER(T9U16   wMaxUsed;)   /* max allocated from memory block */
    T9JW_DEBUGFILTER(T9U16   wMaxHpSz;)   /* maximum heap size */
    T9JW_DEBUGFILTER(T9U16   wAllocCnt;)  /* number of currently allocated blocks */
} T9JW_MemMgr;

/*--------------------------------------
 * End Memory Manager And Heap Definitions
 *--------------------------------------*/


/*
 * Japanese database header information cache.
 */

typedef struct {

    T9U16   wFreqOffset;        /* Added to the frequency code when this
                                    class is made. */
    T9U16   wFClass;            /* Inflection class of word component
                                    following, or 0 if end of word */

} T9JW_FCTE;                         /* Follow-Class Table Entry */

typedef struct {
    /* For decoding encoded class numbers. */
    T9U16 pwNumClassNibbles[(T9MAXTREES + 1) * NUM_CLASS_NIBBLE_RANGES];

    /* For the sake of run-time at the expense of memory, we have a copy
       of the character map. */
    T9U8    bNumCharsOnKey[T9MAXDBKEYS];


    /* For diacriticizing kana. */
    T9U8    bNCCTable[T9MAXDBKEYS];
                /* number of characters per cycle (NCC) table. */
    /*
     * Additional header information for inflection.
     *
     * No need to store mem handles for variable sized tables as
     * memory manager is initialized before these tables are created,
     * effectively freeing all the tables.
     */
    T9U8    bNumTrees;       /* number of trees in addition to
                                 the main tree. */

    T9U16   wNumIC;          /* number of inflection classes, not
                                 counting class 0. */

    T9U8    *pbTrFlags;      /* Per-tree flags table.  Indexes start at 0.
                              * Zeroth entry is for the main tree. */

    T9U16   *pwTrClassCnts;  /* Per-tree class count sum.  Total number of
                              * classes defined by each tree and all previous
                              * trees. Indexes start at 0; zeroth entry is for
                              * the main tree. */

    T9U8    *pbNumCInTr;     /* Total number of classes defined in each tree. */

    T9U16   *pwIC2Tr;        /* Inflection Class to Tree table.  For each
                              * class, which aux. tree is it stored in?
                              * Tree indexes start at 1. */

    T9U8    *pbICFlags;      /* Per-Class Flags table. */

    T9U16   *pwIC2TrIndx;    /* Inflection Class to Tree Index table. For each
                              * class, what is the index within its tree? */

    T9U16   *pwTrIndx2IC;    /* Tree Index to Inflection Class table.  Entries
                              * at indexes from (pbTrClassCnts[bTree - 1] + 1)
                              * through (pbTrClassCnts[bTree]) give the
                              * inflection class corresponding to the in-tree
                              * index. */

    T9U16   *pwYomiFreqSc;   /* Yomi frequency scales.  Multiplies the
                              * frequencies given in the instructions for this
                              * inflection class. */

    T9U16   *pwFCE;          /* Follow-Class Ends table.  Number in the
                              * Follow-Class Table of the last following class
                              * which applies to this class.  The first entry
                              * (index 0) in the table gives the starting
                              * classes and their frequencies. */

    T9JW_FCTE    *pFCTE;          /* Dereferencd address of Follow-Class Table  */

} T9JW_DBInfo;


typedef struct {
    T9JW_HANDLE     hGrp;       /* handle to group of paths */
    T9U16       wGrpSz;     /* number of paths in the group */
} T9JW_PathGroup;

/*------------------------------------------------------------------------
 *
 *                  Linked List Utility
 *
 * A generic linked list implementation so insertion, deletion code
 * can be all in one place.  The linked list has no knowledge of the
 * type of the list node structure or the data in each list node.
 *
 * The next pointer in a list node must be the first field of the
 * structure so the generic list code can always find it.  The next
 * pointer is the handle of the next node and must be named hNext;
 *
 *------------------------------------------------------------------------*/

/* A queue header to provide quick access to the tail of the list when
 * a list is acting as a queue. */
typedef struct {
    T9JW_HANDLE hHead;       /* first element in queue */
    T9JW_HANDLE hTail;       /* last element in queue */
} T9JW_Queue;


/* Define structure for T9 Private persistent data */
struct T9JW_Private_s {
   /*********************/
   /* API level globals */
   /*********************/

    /* Spell (multi-tap) mode key tracking */
    T9SYMB  sSpellPrevKey;        /* previous spell key */

    /* UDB addition mode tracking.  If there was an active yomi prior to
     * entering UDB addition mode, that yomi is captured as the default
     * yomi being added to the UDB.  */
    T9U8    bYomiSize;       /* size of captured yomi, 0 if none */
    T9U8    bEditSize;       /* size of word to be edited when UDB add
                                 word mode is finished */
    T9UINT   nUDBEditPos;     /* cursor position when yomi was captured,
                                 0 if text buffer should NOT be edited
                                 after UDB add word mode is finished */

    /* After a word fails to have any matches from the database, additional
     * ambiguous keys are represented by '?' in the display.  This variable
     * tracks the number of ambiguous keys beyond the end of valid database
     * words. */
    T9UINT   nSurplusKeys;

   /**********************************/
   /* UDB processing related globals */
   /**********************************/

    T9U8    bUdbFound[T9JWMAXWORDSIZE + 1];  /* Counts number of UDB matches
                                               of each length */
    T9U8    bAutoUdbFound[T9JWMAXWORDSIZE + 1];  /* Counts number of Automatic UDB
                                                  matches of each length */
    /* Used for reordering the selection list using info in reorder DB. */
    T9UINT   nLdbEntryFound;                /* Non-zero if UDB yomi is also
                                               found in the Japanese LDB */
   /*****************************/
   /* Auto-help related globals */
   /*****************************/
    T9U8    bNextPresses;               /* consecutive presses on "Select Next" */
    T9U8    bNextingOffenses;           /* number of times "excessive nexting" offense
                                         *  has been detected */

    T9U8    bParticles;                 /* particle entries */
    T9U8    bParticleOffenses;          /* number of times "particle entry" offense
                                         *  has been detected */

   /*********************/
   /* JDB level globals */
   /*********************/
    T9JW_DBInfo jdbInfo;                /* header info in the LDB file */

    T9SYMB  sJCharMap[T9MAXDBKEYS * T9JW_MAXSYMSPERKEY];    /* CharMap table */

    /* Information for processing and building objects. */
    T9UINT    nKeyCnt;                /* number of processed keys */
    T9AuxType bLastKey;               /* value of last processed key */

    T9JW_DEBUGFILTER(T9U16   wNumPaths;)       /* count of spawned paths */
    T9JW_DEBUGFILTER(T9U16   wMaxPaths;)       /* max spawned paths */

    T9JW_PathGroup pathMgr[T9JWMAXWORDSIZE]; /* structure for all the path information
                                         belonging to the current key sequence */

    T9JW_HANDLE hObjTable;              /* handle to completed objects table -
                                        may contain either selection
                                        objects.  JNULL if
                                        no objects have been built. */

    T9U8    bRebuildSelObjs;        /* Selection ojects in table have been
                                     * invalidated and require rebuilding -
                                     *  JRebuildReasons */

    T9U8    bHaveK;                 /* database has katakana for this word */
    T9U8    bShift;                 /* current shift state */
    T9U8    bMagicString;           /* in magic string mode */

    /* Globals needed for inflecting UDB words. */
    T9U32   dwUdbMatches;           /* mask of lengths with UDB matches */
                                    /* bit set if UDB has a yomi of that
                                           length for current key sequence */

    T9JW_Queue  *pUdbStemsQ;            /* queue for storing UDB stems */
    T9U8    bBuildableYomi;         /* 1 if yomi can be created from the LDB, UDB1, or
                                       UDB2 (its buildable), otherwise 0 */
    T9U32   dwMaxReorderClassFreqCode; /* Maximum reorder class frequency */

    /* Globals needed for inflecting JMDB words. */
    T9U32   dwMdbDataIdx;           /* JMDB data index */
    T9JW_Queue  *pMdbStemsQ;            /* queue for storing JMDB stems */
    T9U32   dwMdbMatches;           /* mask of lengths with JMDB matches */
                                    /* bit set if JMDB has a yomi of that
                                           length for current key sequence */
    T9U32   dwClasses[T9JWMAXMDBWORDSIZE]; /* mask of JMDB matched classes */
    T9U8    bMdbFound[T9JWMAXMDBWORDSIZE + 1];  /* Counts number of UDB matches
                                               of each length */
    T9JW_MemMgr memmgr;         /* the almighty memory manager */
};
/*============================================================================
 * END OF PRIVATE:
 *============================================================================*/

/* Define Japanese Flags for the dwJFlags field. */
#define T9JWUDBNOGCMASK                 0x0001  /* no JUDB garbage collection */
#define T9JWCONVERTSPECIALCHARSMASK     0x0002  /* convert special chars */
/* Define Japanese Reorder Flags for dwJReorderFlags field */
#define T9JWPRNAMEREORDERMASK           0x0004  /* On bit for person names class */
/* Person Name Reordering macro */
#define T9JWPRNAMEREORDERMODE(flag)     ((flag & T9JWPRNAMEREORDERMASK) == T9JWPRNAMEREORDERMASK)
/*
 * Define values/macros for parsing key information in pbJAuxBuf field
 * in T9JWFieldInfo structure.  Use these defines rather than access
 * the values directly as the formatting within the buffer may change.
 */
#define T9JWKEYISEXPLICIT(key)          (T9JWEXPLICITMASK &(key))    /* check if key is explicit */
#define T9JWKEYISAMBIG(key)             (!T9JWKEYISEXPLICIT(key))  /* check if key is ambiguous */
        /* T9KEYAMBIG1, T9KEYAMBIG2,... T9KEYAMBIGA is key zero */
#define T9JW_AUTOWORDOFFSETS 0x0A

typedef struct T9JWWordCompleteInfo_s {
    T9U16   wDataSize;    /* Total size in bytes of this struct (minimum is 256) */
    T9U16   wDataCheck;   /* Additive checksum of database */
    T9U16   wOffset     [T9JW_AUTOWORDOFFSETS];
    T9U16   wWorkOffset [T9JW_AUTOWORDOFFSETS];
//@ T9U8    aData[1];     /* Part 1 reserve fixed size */
	T9U8	aData[JACDB_MAX_SIZE - 8];
} T9JWWordCompleteInfo;

struct T9JWFieldInfo_s {
    T9FieldInfo G; /* Generic data. */

    T9JWUdbInfo T9FARUDBPOINTER *pYomiReorderInfo;
    T9JWWordCompleteInfo T9FARUDBPOINTER *pWordCompleteInfo;
    T9U32   dwJFlags;         /* Bitfield of miscellaneous information. */
                              /* T9JWUDBNOGCMASK - indicates no UDB garbage collection when set */
                              /*               Default is no garbage collection. */
    T9UINT   nBuildableWordLen;

    void    *pOEMJPrivate;    /* pointer for OEM use for callbacks             */
    T9JWUdbInfo T9FARUDBPOINTER *pUdbInfo; /* Pointer to manual UDB (UDB1) information */
    T9JWUdbInfo T9FARUDBPOINTER *pAutoUdbInfo;
                              /* Pointer to Automatic UDB (UDB2) information */
    T9U32   dwJReorderFlags;  /* Bitfield to reorder an LDB class to the front of the Selection List */
                              /*    T9JWPRNAMEREORDERMASK : "Person Names Reordering" is enabled */
    T9JWMDBCALLBACK  T9ReadJMdbData; /* Pointer to JMDB callback function */

    struct T9JW_Private_s JWPrivate; /* Our private data */

};

/*********** Public Functions *******************************/
T9STATUS T9FARCALL T9JWInitialize(T9JWFieldInfo *pJWFieldInfo,
    T9SYMB *psTxtBuf,
    T9AuxType *paAuxBuf,
    T9UINT   nBufLenMax,
    T9UINT   nBufLen,
    T9HandleRequest_f T9HandleRequest,
    T9ReadLdbData_f T9ReadLdbData);

T9STATUS T9FARCALL T9JWSetLanguage   (T9JWFieldInfo *pJWFieldInfo,
                                      T9UINT   nLdbNum,
                                      T9FieldInfo *pPreviousFieldInfo);

T9STATUS T9FARCALL T9JWBuildWordWithCurrentText(T9JWFieldInfo *pJWFieldInfo);

T9STATUS T9FARCALL T9JWDelWord       (T9JWFieldInfo *pJWFieldInfo);
T9STATUS T9FARCALL T9JWUdbActivate   (T9JWFieldInfo *pJWFieldInfo, T9JWUdbInfo T9FARUDBPOINTER *pUdbInfo,  T9U16 wDataSize);
T9STATUS T9FARCALL T9JWAudbActivate  (T9JWFieldInfo *pJWFieldInfo, T9JWUdbInfo T9FARUDBPOINTER *pUdbInfo,  T9U16 wDataSize);
T9STATUS T9FARCALL T9JWYrdbActivate  (T9JWFieldInfo *pJWFieldInfo, T9JWUdbInfo T9FARUDBPOINTER *pUdbInfo,  T9U16 wDataSize);
T9STATUS T9FARCALL T9JWAcdbActivate  (T9JWFieldInfo *pJWFieldInfo, T9JWWordCompleteInfo* pWordCompleteInfo, T9U16 wDataSize);

T9STATUS T9FARCALL T9JWUdbAddWord    (T9JWFieldInfo *pJWFieldInfo,  const T9SYMB *psBuf, const T9MINOR mBufLen);
T9STATUS T9FARCALL T9JWUdbDeleteWord (T9JWFieldInfo *pJWFieldInfo,  const T9SYMB *psBuf, const T9MINOR mBufLen);
T9STATUS T9FARCALL T9JWUdbReset      (T9JWFieldInfo *pJWFieldInfo);
T9UINT   T9FARCALL T9JWUdbGetCount   (T9JWFieldInfo *pJWFieldInfo, T9UINT* nCount);
T9STATUS T9FARCALL T9JWUdbGetNthWord (T9JWFieldInfo *pJWFieldInfo,  T9UINT nIndex, T9SYMB* psBuf, T9MINOR* mBufLen);

T9STATUS T9FARCALL T9JWAcdbGetWordList(T9JWFieldInfo *pJWFieldInfo,
                                       T9SYMB* psTarget, T9U8 bTargetLen,
                                       T9SYMB** psYomiList, T9U8** bYomiListLen,
                                       T9SYMB** psList,     T9U8** bListLen,
                                       T9U8     bCandidateCount,
                                       T9U8     bMatchChar, T9U8*  pbCharMatchCount, T9U8* pbKeyMatchCount,
                                       T9U8     bIndex);

T9STATUS T9FARCALL T9JWAudbAddWord(T9JWFieldInfo *pJWFieldInfo, T9SYMB* psYomi, T9U8 bYomiLen);

T9STATUS T9FARCALL T9JWAcdbUpdateWord(T9JWFieldInfo *pJWFieldInfo,
                                      const T9SYMB* psYomi, T9U8 bYomiLen,
                                      const T9SYMB* psMida, T9U8 bMidaLen);

T9STATUS T9FARCALL T9JWUdbCheckSpace(T9JWFieldInfo *pJWFieldInfo, T9UINT *pnResponse);
T9STATUS T9FARCALL T9JWUdbIsValid   (T9JWFieldInfo *pJWFieldInfo);
T9STATUS T9FARCALL T9JWAudbIsValid  (T9JWFieldInfo *pJWFieldInfo);
T9STATUS T9FARCALL T9JWYrdbIsValid  (T9JWFieldInfo *pJWFieldInfo);
T9STATUS T9FARCALL T9JWAcdbIsValid  (T9JWFieldInfo *pJWFieldInfo);
T9STATUS T9FARCALL T9JWNoteWordDone (T9JWFieldInfo *pJWFieldInfo);

T9STATUS T9FARCALL T9JWGetMultitapTable(T9JWFieldInfo *pJWFieldInfo,
                                        T9KEY   eKey,
                                        T9UINT  nDiacriticLevel,
                                        T9SYMB  *pSymb,
                                        T9U16   wPage,
                                        T9U16   wSymbolPerPage,
                                        T9MINOR *pmNumTapRetrieved);

T9STATUS T9FARCALL T9JWDelWord(T9JWFieldInfo *pJWFieldInfo);
T9STATUS T9FARCALL T9JWMoveRightRespellCursor(T9JWFieldInfo *pJWFieldInfo);
T9STATUS T9FARCALL T9JWMoveLeftRespellCursor(T9JWFieldInfo *pJWFieldInfo);
T9STATUS T9FARCALL T9JWExplicifyCharAtCursor(T9JWFieldInfo *pJWFieldInfo);
T9STATUS T9FARCALL T9JWExplicifyCharAsNew(T9JWFieldInfo *pJWFieldInfo, T9SYMB sSymID);
T9STATUS T9FARCALL T9JWGetNthCandidate(T9JWFieldInfo *pJWFieldInfo, T9UINT nTh);

T9STATUS T9FARCALL T9JWMdbCheckWord(T9JWFieldInfo *pJWFieldInfo,
                                    T9SYMB* psWord,
                                    T9U8    bWordLen,
                                    T9AuxType* paKeyBuf);

T9STATUS T9FARCALL T9JWRegisterMdb(T9JWFieldInfo *pJWFieldInfo, T9JWMDBCALLBACK T9ReadMdbData);
T9STATUS T9FARCALL T9JWUnregisterMdb(T9JWFieldInfo *pJWFieldInfo);

T9STATUS T9FARCALL T9JWClrMultitapMode(T9JWFieldInfo *pJWFieldInfo);
T9STATUS T9FARCALL T9JWSetMultitapMode(T9JWFieldInfo *pJWFieldInfo);
T9STATUS T9FARCALL T9JWUdbEnableGC(T9JWFieldInfo *pJWFieldInfo);
T9STATUS T9FARCALL T9JWUdbDisableGC(T9JWFieldInfo *pJWFieldInfo);
T9STATUS T9FARCALL T9JWEnableConvertSpecialChars(T9JWFieldInfo *pJWFieldInfo);
T9STATUS T9FARCALL T9JWDisableConvertSpecialChars(T9JWFieldInfo *pJWFieldInfo);
T9STATUS T9FARCALL T9JWEnablePersonNameReorder(T9JWFieldInfo *pJWFieldInfo);
T9STATUS T9FARCALL T9JWDisablePersonNameReorder(T9JWFieldInfo *pJWFieldInfo);

/*------------------------------------------------------------------------
 *
 *                  Hex Character Values
 *
 * The Japanese T9 Core is using the Shift-JIS character set, with ASCII
 * for latin characters and numbers.
 *
 *------------------------------------------------------------------------*/

#define T9JWC_NUM_0       ((T9SYMB)0x824F)
#define T9JWC_NUM_1       ((T9SYMB)0x8250)
#define T9JWC_NUM_2       ((T9SYMB)0x8251)
#define T9JWC_NUM_3       ((T9SYMB)0x8252)
#define T9JWC_NUM_4       ((T9SYMB)0x8253)
#define T9JWC_NUM_5       ((T9SYMB)0x8254)
#define T9JWC_NUM_6       ((T9SYMB)0x8255)
#define T9JWC_NUM_7       ((T9SYMB)0x8256)
#define T9JWC_NUM_8       ((T9SYMB)0x8257)
#define T9JWC_NUM_9       ((T9SYMB)0x8258)
/* some common symbols */
#define T9JWC_SPACE          ((T9SYMB)0x8140)
#define T9JWC_PERIOD         ((T9SYMB)0x8144)
/*  as 7F is never used in low byte of S-JIS */
/* Hiragana values */
#define T9JWC_A           ((T9SYMB)0x82A0)
#define T9JWC_I           ((T9SYMB)0x82A2)
#define T9JWC_U           ((T9SYMB)0x82A4)
#define T9JWC_E           ((T9SYMB)0x82A6)
#define T9JWC_O           ((T9SYMB)0x82A8)
#define T9JWC_a           ((T9SYMB)0x829F)
#define T9JWC_i           ((T9SYMB)0x82A1)
#define T9JWC_u           ((T9SYMB)0x82A3)
#define T9JWC_e           ((T9SYMB)0x82A5)
#define T9JWC_o           ((T9SYMB)0x82A7)
#define T9JWC_OLD_I       ((T9SYMB)0x82EE)
#define T9JWC_OLD_E       ((T9SYMB)0x82EF)
#define T9JWC_VU          ((T9SYMB)0x8394)
#define T9JWC_KA          ((T9SYMB)0x82A9)
#define T9JWC_KI          ((T9SYMB)0x82AB)
#define T9JWC_KU          ((T9SYMB)0x82AD)
#define T9JWC_KE          ((T9SYMB)0x82AF)
#define T9JWC_KO          ((T9SYMB)0x82B1)
#define T9JWC_GA          ((T9SYMB)0x82AA)
#define T9JWC_GI          ((T9SYMB)0x82AC)
#define T9JWC_GU          ((T9SYMB)0x82AE)
#define T9JWC_GE          ((T9SYMB)0x82B0)
#define T9JWC_GO          ((T9SYMB)0x82B2)
#define T9JWC_SA          ((T9SYMB)0x82B3)
#define T9JWC_SHI         ((T9SYMB)0x82B5)
#define T9JWC_SU          ((T9SYMB)0x82B7)
#define T9JWC_SE          ((T9SYMB)0x82B9)
#define T9JWC_SO          ((T9SYMB)0x82BB)
#define T9JWC_ZA          ((T9SYMB)0x82B4)
#define T9JWC_JI          ((T9SYMB)0x82B6)
#define T9JWC_ZU          ((T9SYMB)0x82B8)
#define T9JWC_ZE          ((T9SYMB)0x82BA)
#define T9JWC_ZO          ((T9SYMB)0x82BC)
#define T9JWC_TA          ((T9SYMB)0x82BD)
#define T9JWC_CHI         ((T9SYMB)0x82BF)
#define T9JWC_TSU         ((T9SYMB)0x82C2)
#define T9JWC_TE          ((T9SYMB)0x82C4)
#define T9JWC_TO          ((T9SYMB)0x82C6)
#define T9JWC_tsu         ((T9SYMB)0x82C1)
#define T9JWC_DA          ((T9SYMB)0x82BE)
#define T9JWC_DI          ((T9SYMB)0x82C0)
#define T9JWC_DU          ((T9SYMB)0x82C3)
#define T9JWC_DE          ((T9SYMB)0x82C5)
#define T9JWC_DO          ((T9SYMB)0x82C7)
#define T9JWC_NA          ((T9SYMB)0x82C8)
#define T9JWC_NI          ((T9SYMB)0x82C9)
#define T9JWC_NU          ((T9SYMB)0x82CA)
#define T9JWC_NE          ((T9SYMB)0x82CB)
#define T9JWC_NO          ((T9SYMB)0x82CC)
#define T9JWC_HA          ((T9SYMB)0x82CD)
#define T9JWC_HI          ((T9SYMB)0x82D0)
#define T9JWC_FU          ((T9SYMB)0x82D3)
#define T9JWC_HE          ((T9SYMB)0x82D6)
#define T9JWC_HO          ((T9SYMB)0x82D9)
#define T9JWC_BA          ((T9SYMB)0x82CE)
#define T9JWC_BI          ((T9SYMB)0x82D1)
#define T9JWC_BU          ((T9SYMB)0x82D4)
#define T9JWC_BE          ((T9SYMB)0x82D7)
#define T9JWC_BO          ((T9SYMB)0x82DA)
#define T9JWC_PA          ((T9SYMB)0x82CF)
#define T9JWC_PI          ((T9SYMB)0x82D2)
#define T9JWC_PU          ((T9SYMB)0x82D5)
#define T9JWC_PE          ((T9SYMB)0x82D8)
#define T9JWC_PO          ((T9SYMB)0x82DB)
#define T9JWC_MA          ((T9SYMB)0x82DC)
#define T9JWC_MI          ((T9SYMB)0x82DD)
#define T9JWC_MU          ((T9SYMB)0x82DE)
#define T9JWC_ME          ((T9SYMB)0x82DF)
#define T9JWC_MO          ((T9SYMB)0x82E0)
#define T9JWC_YA          ((T9SYMB)0x82E2)
#define T9JWC_YU          ((T9SYMB)0x82E4)
#define T9JWC_YO          ((T9SYMB)0x82E6)
#define T9JWC_ya          ((T9SYMB)0x82E1)
#define T9JWC_yu          ((T9SYMB)0x82E3)
#define T9JWC_yo          ((T9SYMB)0x82E5)
#define T9JWC_RA          ((T9SYMB)0x82E7)
#define T9JWC_RI          ((T9SYMB)0x82E8)
#define T9JWC_RU          ((T9SYMB)0x82E9)
#define T9JWC_RE          ((T9SYMB)0x82EA)
#define T9JWC_RO          ((T9SYMB)0x82EB)
#define T9JWC_wa          ((T9SYMB)0x82EC)
#define T9JWC_WA          ((T9SYMB)0x82ED)
#define T9JWC_WO          ((T9SYMB)0x82F0)
#define T9JWC_STICK       ((T9SYMB)0x815B)
#define T9JWC_N           ((T9SYMB)0x82F1)
#define T9JWC_U           ((T9SYMB)0x82A4)
#define T9JWC_a           ((T9SYMB)0x829F)
#define T9JWC_i           ((T9SYMB)0x82A1)
#define T9JWC_u           ((T9SYMB)0x82A3)
#define T9JWC_e           ((T9SYMB)0x82A5)
#define T9JWC_o           ((T9SYMB)0x82A7)
#define T9JWC_tsu         ((T9SYMB)0x82C1)

#define T9JWC_SMALL_KA    ((T9SYMB)0x8395)
#define T9JWC_SMALL_KE    ((T9SYMB)0x8396)

/* Amount to add to lowercase ascii to get SJIS latin char */
#define T9JWC_LATIN_ASCII_TO_SJIS_FACTOR (0x8220)

#define T9JWC_HIRAGANA_START          ((T9SYMB)0x829F)
#define T9JWC_HIRAGANA_END            ((T9SYMB)0x82F1)
#define T9JWC_KATAKANA_END            ((T9SYMB)0x8340)
#define T9JWC_KANJI_START             ((T9SYMB)0x889E)
#define T9JWC_KATAKANA_ADJUSTMENT     ((T9SYMB)0x00A1)/* if low byte is < 0xDE */
#define T9JWC_KATAKANA_CHNG           ((T9SYMB)0x82DE)/* codes after this are adjusted by 1 byte */
#define T9JWC_SJIS_DIGIT_START        ((T9SYMB)0x824F)
#define T9JWC_SJIS_DIGIT_END          ((T9SYMB)0x8258)
#define T9JWC_SJIS_CAP_ALPHA_START    ((T9SYMB)0x8260)
#define T9JWC_SJIS_CAP_ALPHA_END      ((T9SYMB)0x8279)
#define T9JWC_SJIS_LOWER_ALPHA_START  ((T9SYMB)0x8281)
#define T9JWC_SJIS_LOWER_ALPHA_END    ((T9SYMB)0x829a)

/* End don't mangle the function name if compile under C++ */
#if defined(__cplusplus)
    }
#endif

#endif /* #ifndef T9JWAPI_H */

/* ----------------------------------< eof >--------------------------------- */
