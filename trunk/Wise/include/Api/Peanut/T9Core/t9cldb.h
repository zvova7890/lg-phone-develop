/*******************************************************************************
********************************************************************************

                    COPYRIGHT 2000-2005 TEGIC COMMUNICATIONS

                TEGIC COMMUNICATIONS PROPRIETARY INFORMATION

     This software is supplied under the terms of a license agreement
     or non-disclosure agreement with Tegic Communications and may not
     be copied or disclosed except in accordance with the terms of that
     agreement.

********************************************************************************

     File Name:   t9cldb.h

     Description: Function prototypes for T9 Chinese LDB functions


********************************************************************************
********************************************************************************/

#include "t9cmisc.h"

#ifndef _T9CLDB_H
#define _T9CLDB_H    1

/* don't mangle the function name if compile under C++ */
#if defined(__cplusplus)
extern "C" {
#endif

/*----------------------------------------------------------------------------
 *  Various database/search engine constants
 *----------------------------------------------------------------------------*/

/*  This is the code returned by search routines when no character found      */
#define     NOMATCH             0xFFFF

/*  This number defines the split point for keeping arrays of words < 16kb    */
#define     SPLITPOINT          0x1FC0

#define     STROKES_PER_RECORD  60
#define     STROKES_PER_WORD    5
#define     STROKES_ARR_SIZE    ((STROKES_PER_RECORD + STROKES_PER_WORD - 1) / STROKES_PER_WORD)
#define     BITSPERSTROKE       (16 / STROKES_PER_WORD)

#define     STROKEOFFSET        T9KEYAMBIG1
#define     WILDCARDSTROKE      T9KEYAMBIG6

#define     T9STROKEBITS        ((1 << BITSPERSTROKE) - 1)
#define     T9ALLVALID          077777
#define     T9ALLTONES          037

#define     T9MATCHBUFFSIZE     64                      /* Must be a power of two */
#define     T9PARTIALBUFFSIZE   16
#define     T9EXACTSTART        0

#define     T9RSBLOCKSHIFT      6                       /* Log 2 remaining strokes block size  */
#define     T9RSBLOCKSIZE       (1 << T9RSBLOCKSHIFT)   /* Actual remaining strokes block size */
#define     T9RSBLOCKMASK       (T9RSBLOCKSIZE - 1)     /* Remaining stroke block offset mask  */

#define     T9LETTERONKEYSIZE   40                      /* Phonetic letter on key table size   */

#define		SYLLABLE_MAX_LEN	6						/* maximum length for single spell	   */

/*  Character set mask bits in the upper bits of the StrokeCounts data byte */
#define     CSET_MASK       0xC0            /* Character set mask bits */
#define     CSET_SIMP       0x40            /* Simplified only */
#define     CSET_TRAD       0x80            /* Traditional only */
#define     CSET_COMB       0xC0            /* Combined -- both simplified and traditional */

#define     STROKECOUNTMASK (~CSET_MASK)    /* Mask to get stroke count only */

/* Defines for Unicode ranges of components for Simplified and Traditional Chinese */
#define T9SIMP_FIRSTCOMPONENT       0xEEB8
#define T9SIMP_LASTCOMPONENT        0xEF51
#define T9TRAD_FIRSTCOMPONENT       0xEF88
#define T9TRAD_LASTCOMPONENT        0xF120

/* Defines for the compressed components arrays */
#define NUM_REMAINING_BITS_PER_BYTE 4
#define NUM_REMAINING_CHUNKS_PER_BYTE (8 / NUM_REMAINING_BITS_PER_BYTE)

/* define checksum ID (2 bytes)'s location at Chinese database */
#define CHECKSUM_ID_LOCATION		(T9CC_HeaderOffsetCheckSum)
/* define the starting location of the array of data block sizes at Chinese database */
#define BLOCK_SIZE_START_LOCATION	(T9CC_HeaderOffsetBlockSize)
/* define the starting location of the module flag inside the version string */
#define T9CDBMODULEFLAGSTART        20

/*----------------------------------------------------------------------------
 *  Define the format of the Phonetic database data bins
 *----------------------------------------------------------------------------*/
typedef struct  T9PhoneticBin_s {

    T9U16   wStrokeData;    /* One word of packed phonetic stroke data       */
    T9U16   wListStart;     /* Index of first phonetic data char list entry  */
    T9U16   wSpellings;     /* Index to start of spellings list for this bin */

} T9PhoneticBin;

/*	Macro to step to the next structure as it sits in the database --
	some compilers will pad structure to a 4 byte offset, but the table as
	it sits in the database is just a string of words
*/

#define	T9PhoneticBinAddr(pBin, cnt)    ((T9PhoneticBin const T9FARDATA *)((T9U16 const T9FARDATA *)(pBin) + (3 * (cnt))))
#define	T9NextPhoneticBin(pBin)         ((pBin) = T9PhoneticBinAddr((pBin), 1))

/*----------------------------------------------------------------------------
 *  Define the format of the Phonetic character to key mapping table
 *----------------------------------------------------------------------------*/
typedef struct  T9PhoneticCharMap_s {

    T9U8    bChar;          /* Ascii character code */
    T9U8    bKey;           /* T9 ambiguous key code */

} T9PhoneticCharMap;

/*	Macro to step to the next structure as it sits in the database --
	some compilers will pad structure to a 4 byte offset, but the table as
	it sits in the database is just a string of bytes
*/

#define T9NextCharMap(pMap) ((pMap) = (T9PhoneticCharMap const T9FARDATA *)((T9U8 const T9FARDATA *)(pMap) + 2))


/*----------------------------------------------------------------------------
 *  Define T9 Chinese stroke header block
 *----------------------------------------------------------------------------*/
typedef struct  T9ChineseStrokeHeader_s {

    const   T9U16   wDataValid;         /*  Start of header flag              */

    /*      These two values are different for the 5 and 8 stroke systems     */
    /*      5 strokes uses keys 1..5 while eight stroke uses 2..9             */
    const   T9U16   wWildCardStroke;    /*  Wildcard stroke value             */
    const   T9U16   wStrokeOffset;      /*  Offset strokes keys to db strokes */

    /*      Offset to stroke counts to words of stroke data translate table   */
    const   T9U16   wStrokeWordsTable;

    const   T9U16   wRemStrokeTable;    /*  Offset to remaining strokes table */
    const   T9U16   wRemStrokeEntries;  /*  Number of rem stroke entries      */

    const   T9U16   w1StrokeEntries;    /*  Number of 1 stroke entries        */
    const   T9U16   w2StrokeEntries;    /*  Number of 2 stroke entries        */
    const   T9U16   w3StrokeEntries;    /*  Number of 3 stroke entries        */
    const   T9U16   w4StrokeEntries;    /*  Number of 4 stroke entries        */

    const   T9U16   w1StrokeTable;      /*  Offset to 1 stroke entry table    */
    const   T9U16   w2StrokeTable;      /*  Offset to 2 stroke entry table    */
    const   T9U16   w3StrokeTable;      /*  Offset to 3 stroke entry table    */
    const   T9U16   w4StrokeTable;      /*  Offset to 4 stroke entry table    */

    /*      The rest of this header block is filled with the actual tables    */
    /*      referenced by the above wXxxxTable data elements                  */
    const   T9U16   wDataStart[1];      /*  Start of variable length data     */

} T9ChineseStrokeHeader;

/*----------------------------------------------------------------------------
 *  Define T9 Chinese context data block
 *----------------------------------------------------------------------------*/
typedef struct  T9ChineseContextData_s {

    const   T9U16   wDataValid;         /*  Start of header flag              */
    const   T9U16   wContextEntries;    /*  Context entries in this block     */
    const   T9U16   wContextCodesTable; /*  Offset to context codes table     */
    const   T9U16   wDataOffsetsTable;  /*  Offset to data offsets table      */

    /*      The rest of the context data block contains the context data,     */
    /*      and the context codes table and corresponding context data        */
    /*      offsets table.                                                    */
    const   T9U16   wDataStart[1];      /*  Start of variable length data     */

} T9ChineseContextData;

/*----------------------------------------------------------------------------
 *  Define T9 CompressedChinese components data block
 *----------------------------------------------------------------------------*/
typedef struct  T9CompressedChineseComponentsData_s {

    const   T9U16   wDataValid;         /*  Start of header flag              */
    const   T9U16   wNumCompTableWords;	/*  # of comp table words             */
    const   T9U16   wCompTable;			/*  Offset to comp table              */
    const   T9U16   wDataStart[1];      /*  Start of variable length data     */

} T9CompressedChineseComponentsData;

/*----------------------------------------------------------------------------
 *  Define T9 Chinese phonetic header block
 *----------------------------------------------------------------------------*/
typedef struct  T9ChinesePhoneticHeader_s {

    const   T9U16   wDataValid;         /*  Start of header flag              */
    const   T9U16   wTotalBins;         /*  Number of phonetic bins           */
    const   T9U16   wLetterOnKeyTable;  /*  Offset to letter on key table     */
    const   T9U16   wSpellingsList;     /*  Offset to spellings pointer list  */
    const   T9U16   wSpellingsText;     /*  Offset to phonetic spellings text */
    const   T9U16   wEndOfData;         /*  Offset to end of spellings text   */

    /*      The rest of this header block is filled with the actual tables    */
    /*      referenced by the above wXxxxTable data elements                  */
    const   T9U16   wDataStart[1];      /*  Start of variable length data     */

} T9ChinesePhoneticHeader;

/*----------------------------------------------------------------------------
 *  Define T9 Chinese phonetic data block
 *----------------------------------------------------------------------------*/
typedef struct  T9ChinesePhoneticData_s {

    const   T9U16   wDataValid;         /*  Start of header flag              */
    const   T9U16   wNumberOfBins;      /*  Number of bins in this block      */
    const   T9U16   wTone5Table;        /*  Tone 5 flags table offset         */
	const	T9U16	wTone2BitsTable;	/*  Tone lower 2 bit table offset	  */
    const   T9U16   wSpellMCFTable;     /*  Spell / Most Common Flag offset   */
    const   T9U16   wCharIdxTable;      /*  Character index table offset      */
    const   T9U16   wBinTable;          /*  Start of phonetic bin data        */

    /*      The rest of this header block is filled with the actual tables    */
    /*      referenced by the above wXxxxTable data elements                  */
    const   T9U16   wDataStart[1];      /*  Start of variable length data     */

} T9ChinesePhoneticData;


/* ***********************     Important ***************************
 *
 * When adding any blocks to this structure, make sure to update the define
 * T9CCLDBBLOCKCOUNT in T9API.h to match the number indicated here!
 *
 ********************************************************************/

/*----------------------------------------------------------------------------
 *  Define T9 Chinese database pointer set
 *----------------------------------------------------------------------------*/
#define T9MAXCHNCONTEXTBLOCKS		5
#define T9MAXCHNPHONETICBLOCKS		12
#define T9MAXCHNCOMPONENTBLOCKS		1

typedef struct  T9CC_LdbDataBlockPointers_s {
    const T9U8 bHeader[T9CCLdbHeaderSize];

    /* Display code Module -- up to 8 blocks, used by all modules. */
    const   T9U16                   T9FARDATA * const pwDisplayCodes[8];

    /* Stroke Module -- up to 33 blocks */
    /* stroke header */
    const   T9ChineseStrokeHeader     T9FARDATA * const pStrokeHeader;
    /* stroke data */
    const   T9U16                   T9FARDATA * const pwFirstStrokes[8];
    const   T9U16                   T9FARDATA * const pwSecondStrokes[8];
    const   T9U16                   T9FARDATA * const pwRemainingStrokes[12];
    const   T9U8                    T9FARDATA * const pbStrokeCounts[4];

    /* Context Module -- up to 5 x 16kb gives up to 80kb context */
    const   T9ChineseContextData    T9FARDATA * const pContext[T9MAXCHNCONTEXTBLOCKS];

    /* Phonetic Module -- up to 13 blocks */
    const   T9ChinesePhoneticHeader T9FARDATA * const pPhoneticHeader;
    const   T9ChinesePhoneticData   T9FARDATA * const pPhoneticData[T9MAXCHNPHONETICBLOCKS];

    /* Component Module -- 7 data blocks */
    const   T9CompressedChineseComponentsData    T9FARDATA * const pCompressedComponents[T9MAXCHNCOMPONENTBLOCKS];
    const   T9U8                    T9FARDATA * const pbCompressedCharComponents[4];
    const   T9U8                    T9FARDATA * const pbCompressedCharRemainders[2];
} T9ChineseDataPointers;

#define gpLdbCoreView       ((T9ChineseDataPointers const T9FARDATA *)(&pCCFieldInfo->T9CPrivate.T9CC_LdbUserView))

/*----------------------------------------------------------------------------
 *  Define some handy structure access macros
 *----------------------------------------------------------------------------*/

/* Macro to get the number of elements in an array */
#define     Elements(a)         (sizeof(a) / sizeof((a)[0]))

/* Macro to get actual number of words before the variable length data area   */
#define T9ChineseHeaderWords(pStruct)           ((T9UINT)((const T9U16 T9FARDATA *)((pStruct)->wDataStart) - (const T9U16 T9FARDATA *)(pStruct)))

/* Macro to get pointer to start of a table data data words                   */
#define T9ChineseTableStart(pStruct, wTable)   ((const T9U16 T9FARDATA *)(pStruct) + T9CC_ReadFarWord(&((pStruct)->wTable)))

/* Macro to get pointer to start of a table data data bytes                   */
#define T9ChineseByteTableStart(pStruct, wTable)   ((const T9U8 T9FARDATA *)(pStruct) + T9CC_ReadFarWord(&((pStruct)->wTable)))

/* Macro to get an entry from the stroke counts array */
#define T9ChineseStrokeCounts(pData, nIndex, mBlock)    (T9CC_ReadFarByte((const T9U8 T9FARDATA *)T9CC_ReadFarPointer(&((pData)->pbStrokeCounts[mBlock])) +  ((nIndex) - (mBlock) * SPLITPOINT * 2)))

/* Macro to get an entry from correct word based array */
#define T9ChineseTableEntry(pData, nIndex, mBlock, pwTable)     (T9CC_ReadFarWord((const T9U16 T9FARDATA *)T9CC_ReadFarPointer(&((pData)->pwTable[mBlock])) + ((nIndex) - (mBlock) * SPLITPOINT)))

/*--------------------- for dynamic context and new GB standard--------*/

#define DEPTMASK  0X1F                  /* how many character are there before this dynamic
                                         * context. like there is a phrase "abcdef", you chose
                                         * d, then depth is 4
                                         * also, this field also indicate if this character
                                         * is from cudb or not. 0 means not. */
#define CUDBMASK  0X20                  /* if this dymaic context is from cudb then 1,
                                         * from phone book 0 */
#define OCUPMASK  0X40                  /* if there is a character be placed in this slot, s
                                         * set it to 1. if no character, 0 */
#define CAUDBMASK 0X80                  /* if this character is from CAUDB,
                                         * 0, it's not; 1 it is */

#define FIRST_CHINESE_UNICODE  0x3400	/* new GB 18030 standard has character staring from 0x3400 */
#define LAST_CHINESE_UNICODE   0xF7EE   /* This is the range of Unicodes found inside our TegicID-Unicode
                                         * look-up table in Chinese LDBs.  */

/*----------------------- for Magic string -----------------------------*/


#define CHINESE_MAGIC_CHARACTER 0x770B          /* unicode for the magic character */
#define CHINESE_MAGIC_CHARACTER_STROKE_LENGTH 9 /* the ordinary stroke length for the magic character  */
#define CHINESE_MAGIC_STRING_LENGTH 32          /* the stroke magic string length */
#define CHINESE_MAGIC_SPELL_BPMF_LENGTH       3 /* the BPMF magic spell length */
#define CHINESE_MAGIC_SPELL_PINYIN_LENGTH     6 /* the PINYIN magic spell length */

/*------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 *  Function prototypes
 *----------------------------------------------------------------------------*/

extern T9UINT    T9FARCALL T9CC_UpdateSelectionPage(T9CCFieldInfo *pCCFieldInfo, T9MINOR mExpl);
extern void     T9FARCALL T9CC_ResetDynamicContext(T9CCFieldInfo *pCCFieldInfo);
extern void     T9FARCALL T9CC_ResetStrokes(T9CCFieldInfo *pCCFieldInfo);
extern void     T9FARCALL T9CC_ResetSearch(T9CCFieldInfo *pCCFieldInfo);
extern T9U8     T9FARCALL T9CC_PhoneticCharToKey(T9CCFieldInfo *pCCFieldInfo, T9U8 bChar);

extern T9STATUS T9FARCALL T9CC_GetStrokes(T9CCFieldInfo *pCCFieldInfo, T9U16 wDisplay, T9MINOR mAltIdx);
extern T9STATUS T9FARCALL T9CC_GetSpelling(T9CCFieldInfo *pCCFieldInfo, T9U16 wDisplay, T9MINOR mAltIdx);
extern T9STATUS T9FARCALL T9CC_GetSpellOptions(T9CCFieldInfo *pCCFieldInfo);
extern T9UINT    T9FARCALL T9CC_GetToneOptions(T9CCFieldInfo *pCCFieldInfo);
extern T9STATUS T9FARCALL T9CC_MultitapKey(T9CCFieldInfo *pCCFieldInfo,
                                           T9KEY eKeyID);

extern T9STATUS T9FARCALL T9CC_ValidateLdb(T9CCFieldInfo *pCCFieldInfo);
extern T9U8     T9FARCALL T9CC_StrokeMatch(T9CCFieldInfo *pCCFieldInfo, T9SYMB T9FARDATA *psPhrase);
extern T9STATUS T9FARCALL T9CC_GetDynamicContextString(T9CCFieldInfo *pCCFieldInfo, T9SYMB** psString, T9UINT nStringNum, T9U8 *bStringLen);

T9UINT T9FARCALL T9CC_DisplayCodeLookup(T9CCFieldInfo *pCCFieldInfo,
                                        T9U16          wDisplay,
                                        T9MINOR        mAltIdx);
T9UINT T9FARCALL T9CC_DisplayCode(
    const T9ChineseDataPointers T9FARDATA *pData,
    T9UINT nIndex, T9UINT nBlock);

T9UINT T9FARCALL T9CC_GetStrokeBlkNum(T9UINT nIndex,
                                    T9UINT nTotalBlocks);
/*---------------------------------------------------------------------------
 * The following are a set of data access routines required for supporting
 * the OEM specific C166 CPU environment.  They do not allow direct access to
 * ROM data (anything with 'const'), so it must be accessed via these
 * access functions.
 *
 * In the Latin T9 core, this isn't much of an issue, only the SymbolToKey
 * tables are const ROM data.  However, in the T9Cldb.c module, these
 * access routines are heavily used.
 *
 * Some OEMs also has their own multiply routine.
 *---------------------------------------------------------------------------*/

#ifndef OEM_C166_FARDATA

#define T9CC_ReadFarByte(addr)       (*(addr))
#define T9CC_ReadFarWord(addr)       ((T9U16)(*((T9U8 T9FARDATA*)(addr)) | (((T9U16)(*((T9U8 T9FARDATA*)(addr) + 1))) << 8)))
#define T9CC_ReadFarPointer(addr)    (*(addr))

#else
/*---------------------------------------------------------------------------
 * Note: If the functions are used for Chinese ldb, please keep in mind that
 *          all the Chinese ldbs are now in little endian starting from v6.1
 *          (See the macro-definitions above)
 *---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------
 *  Function: T9CC_ReadFarByte
 *  Synopsis: Read a single byte from far ROM data
 *
 *     Input: pData    - Pointer to data byte to read
 *
 *    Return: Data byte from ROM
 *---------------------------------------------------------------------------*/
extern T9U8 T9FARCALL T9CC_ReadFarByte(const T9U8 T9FARDATA *pData);

/*---------------------------------------------------------------------------
 *  Function: T9CC_ReadFarWord
 *  Synopsis: Read a single word from far ROM data
 *
 *     Input: pData    - Pointer to data word to read
 *
 *    Return: Data word from ROM
 *---------------------------------------------------------------------------*/
extern T9U16 T9FARCALL T9CC_ReadFarWord(const T9U16 T9FARDATA *pData);

/*---------------------------------------------------------------------------
 *  Function: T9CC_ReadFarPointer
 *  Synopsis: Read a single pointer value from far ROM data
 *
 *     Input: pData    - Pointer to data pointer value to read
 *
 *    Return: Data pointer read from ROM
 *---------------------------------------------------------------------------*/
extern const void T9FARDATA* T9FARCALL T9CC_ReadFarPointer(const void T9FARDATA * const T9FARDATA *pData);


#endif  /*  End of special OEM_C166 T9FARDATA data access routine headers */

#if defined(__cplusplus)
}
#endif

#endif

/*-----------------------------------< eof >----------------------------------*/
