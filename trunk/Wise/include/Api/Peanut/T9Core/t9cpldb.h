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
;**     FileName: t9cpldb.h                                                   **
;**                                                                           **
;**  Description: Chinese PTI database access routines header file.           **
;**               Conforming to the development version of PTI.               **
;**                                                                           **
;*******************************************************************************
;******************************************************************************/

#ifndef T9CPLDB_H
#define T9CPLDB_H 1

/* don't mangle the function name if compile under C++ */
#if defined(__cplusplus)
extern "C" {
#endif

#define T9CP_PARTIDRANGENUM   3
#define T9CP_EXACTIDRANGENUM  2

/* set and reset the header offset to make alpha code reused for PTI */
#define T9CP_SET_ALPHA_HEADER(pT9CPFieldInfo)   ((pT9CPFieldInfo)->G.T9PrivateLdb[(pT9CPFieldInfo)->G.bActiveLangIndex].dwHeaderStart = (pT9CPFieldInfo)->Private.PPrivate.dwHeaderOffset)
#define T9CP_RESET_ALPHA_HEADER(pT9CPFieldInfo) ((pT9CPFieldInfo)->G.T9PrivateLdb[(pT9CPFieldInfo)->G.bActiveLangIndex].dwHeaderStart = 0)
enum T9CP_Lookup_e {
    T9CP_Lookup_PIDToSID = 0,
    T9CP_Lookup_SIDToPID
};
T9U8 T9FARCALL T9CP_FreqLookup(T9CPFieldInfo * pT9CPFieldInfo, T9U16 wPID);
#define T9CP_LookupTone(pT9CPFieldInfo, wPID) (T9_SetDataOffset(&pT9CPFieldInfo->G, (T9U32)(pT9CPFieldInfo->Private.PPrivate.dwToneOffset + (T9U32)wPID * 2 + 4), CACHE0), \
                                                T9CP_ReadByte(pT9CPFieldInfo, CACHE0))

/*----------------------------------------------------------------------------
 *  Define the LDB parameters and constants.
 *----------------------------------------------------------------------------*/
#define T9CP_PARTMATCHSILFOUND    2       /* partial matching spelling and phrase found */
#define T9CP_PARTMATCHINSTRFOUND  1       /* partial matching spelling found */
#define T9CP_PARTMATCHNOTFOUND    0       /* no partial matching spelling found */

#define T9CP_CONVTYPEMASK         0x08    /* bit mask for checking conversion type */
#define T9CP_TONETYPEMASK         0x06    /* bit mask for checking tone encoding type */
#define T9CP_FIRSTTONEMASK        0x07    /* bit mask for first tone */

#define T9CP_MAXBPMFSYLBLEN       3       /* maximum length of one BPMF syllable */
#define T9CP_MAXPINYINSYLBLEN     6       /* maximum length of one Pinyin syllable */
#define T9CP_MINSILLENGTH         1       /* minimum length of the SIL */

#define T9CP_ONECHARPBUFSIZE      3        /* number of bytes for one character in phrase buffer */
#define T9CP_STARTSEARCHNEXT      2        /* start searching the next partial match in the node, not child node */
#define T9CP_TEGICIDMASK          0x7FFF   /* bit mask for Tegic ID used in phonetic ID lookup table */
#define T9CP_CONTEXTDATASTART     12       /* nibble offset of the context data start */
#define T9CP_MULTI_BPMF_SYL_MARK  0x01C0   /* indicator for multi-mapped BPMF syllable to Pinyin syllable in LDB */
#define T9CP_MAX_NUM_MT_SYM       8        /* maximum number of multitap symbol */
/* Define T9 compatibility index for Chinese PTI core and databases.
   This number should be updated for each release. */
#define T9COMPATIDXBASECP         7
#define T9COMPATIDXOFFSETCP       0

#define T9CP_MAXALTSYLLABLE     8   /* max count of alt syllable/strokes including the most common one */

#define T9CP_MAXPARTIALSYL     37  /* max number of partial syllable */
#define T9CP_MAXPARTSYLFORKEY  79  /* max number of partial syllable for a key (key 7) */
/*----------------------------------------------------------------------------
 *  Define the LDB structure and variable types.
 *----------------------------------------------------------------------------*/
typedef struct T9CP_SubInstruct_s {     /* structure for sub-instruction */
    T9SYMB  sChar;  /* if bTyep == 0, sChar is the most common tone; else, it is index in the root node SILs */
    T9U8    bType;  /* 0: character conversion; 1: phrase conversion */
    T9U8    bData;  /* if bType == 0, bData is tone bit mask; else, it is the syllable length */
    T9U16   wObj;   /* previous conversion object number (SI's index) */
    T9U8    bEOW;   /* end of word flag. single character is considered as EOW */
} T9CP_SubInstruct;

typedef enum {
    T9CP_GETBOTH = 0,   /* both partial and exact matches */
    T9CP_GETPARTIAL,    /* partial match only */
    T9CP_GETEXACT       /* exact match only */
} T9CP_PIDRANGE_TYPE;

typedef struct T9CP_PIDRange_s {
    T9U16               wPIDStart;  /* starting PID, inclusive */
    T9U16               wPIDEnd;    /* ending PID, exclusive */
    T9U16               wSylEndIndex;   /* syllabl entry index of the ending PID */
    T9U8                bNumKeys;       /* number of keys for this range */
    T9CP_PIDRANGE_TYPE  eGetType;       /* get type */
} T9CP_PIDRange;

enum T9CP_MOHU_RULES_e {
    T9CP_MOHU_NO_RULE = 0,
    T9CP_MOHU_Appendh,
    T9CP_MOHU_Appendg,
    T9CP_MOHU_Droph,
    T9CP_MOHU_Dropg,
    T9CP_MOHU_ChangeToR,
    T9CP_MOHU_ChangeToL,
    T9CP_MOHU_ChangeToN,
    T9CP_MOHU_ChangeToF,
    T9CP_MOHU_ChangeToH,
    T9CP_MOHU_NUMRULES
};

#define T9CP_MOHU_AppendhMask   (1 << (T9CP_MOHU_Appendh - 1))
#define T9CP_MOHU_AppendgMask   (1 << (T9CP_MOHU_Appendg - 1))
#define T9CP_MOHU_DrophMask     (1 << (T9CP_MOHU_Droph - 1))
#define T9CP_MOHU_DropgMask     (1 << (T9CP_MOHU_Dropg - 1))
#define T9CP_MOHU_ChangeToRMask (1 << (T9CP_MOHU_ChangeToR - 1))
#define T9CP_MOHU_ChangeToLMask (1 << (T9CP_MOHU_ChangeToL - 1))
#define T9CP_MOHU_ChangeToNMask (1 << (T9CP_MOHU_ChangeToN - 1))
#define T9CP_MOHU_ChangeToFMask (1 << (T9CP_MOHU_ChangeToF - 1))
#define T9CP_MOHU_ChangeToHMask (1 << (T9CP_MOHU_ChangeToH - 1))

typedef struct T9CP_MOHU_KEYS_s {
    T9U8 bKeyN;
    T9U8 bKeyL;
    T9U8 bKeyR;
    T9U8 bKeyF;
    T9U8 bKeyH;
    T9U8 bKeyg;
} T9CP_MOHU_KEYS;

#define T9CP_SetDataOffset(pInfo, offset) T9_SetDataOffset(pInfo, offset, CACHE1)
#define T9CP_GetDataOffset(pInfo) T9_GetDataOffset(pInfo, CACHE1)
#ifndef T9_CACHE_COUNT
#define T9_CACHE_COUNT(pFieldInfo, cacheIndex) ((pFieldInfo)->T9PrivateLdb[(pFieldInfo)->bActiveLangIndex].CacheInfo[cacheIndex].dwNibbleCount)
#endif

/* Macros to verify LDB content */
#define T9CP_IsLdbPinyinOnly(pT9CPFieldInfo)    ((pT9CPFieldInfo) && ((pT9CPFieldInfo)->CommonInfo.sOffsets.dwPinyinLDBOffset) \
                                                                  && !((pT9CPFieldInfo)->CommonInfo.sOffsets.dwBpmfLDBOffset))
#define T9CP_IsLdbBpmfOnly(pT9CPFielfInfo)      ((pT9CPFieldInfo) && ((pT9CPFieldInfo)->CommonInfo.sOffsets.dwBpmfLDBOffset) \
                                                                  && !((pT9CPFieldInfo)->CommonInfo.sOffsets.dwPinyinLDBOffset))
#define T9CP_IsLdbDualPhonetic(pT9CPFieldInfo)  ((pT9CPFieldInfo) && ((pT9CPFieldInfo)->CommonInfo.sOffsets.dwBpmfLDBOffset) \
                                                                  && ((pT9CPFieldInfo)->CommonInfo.sOffsets.dwPinyinLDBOffset))
#define T9CP_LdbHasStroke(pT9CPFieldInfo)       ((pT9CPFieldInfo) && ((pT9CPFieldInfo)->CommonInfo.sOffsets.dwStrokeLDBOffset))

#define T9CP_LdbHasPinyin(pT9CPFieldInfo)       ((pT9CPFieldInfo) && ((pT9CPFieldInfo)->CommonInfo.sOffsets.dwPinyinLDBOffset))

#define T9CP_LdbHasBpmf(pT9CPFieldInfo)         ((pT9CPFieldInfo) && ((pT9CPFieldInfo)->CommonInfo.sOffsets.dwBpmfLDBOffset))

#define T9CP_LdbHasPhonetic(pT9CPFieldInfo)     ((pT9CPFieldInfo) && (((pT9CPFieldInfo)->CommonInfo.sOffsets.dwPinyinLDBOffset) \
                                                                      || ((pT9CPFieldInfo)->CommonInfo.sOffsets.dwBpmfLDBOffset)))

/*----------------------------------------------------------------------------
 *  Define the LDB function prototypes.
 *----------------------------------------------------------------------------*/
T9STATUS T9FARCALL T9CP_CheckLdb(T9CPFieldInfo *);
T9U16 T9FARCALL T9CP_UnicodeToPID(T9CPFieldInfo *, T9U16, T9U8);
T9SYMB T9FARCALL T9CP_LookupUnicode(T9CPFieldInfo * pT9CPFieldInfo, T9U16 wPID);
T9U8 T9FARCALL T9CP_LookupID(T9CPFieldInfo *pT9CPFieldInfo, T9U16 *pwIDBuf, T9U16 wID, T9U8 bBufSize, T9U8 bType);
T9STATUS T9FARCALL T9CP_PidBidToSyllable(T9CPFieldInfo * pT9CPFieldInfo, T9U16 wPID, T9U8 *pbSpell, T9U8 *pbSpellLen, T9U8 bOutFormat);
T9STATUS T9FARCALL T9CP_CheckPhoneticLdb(T9CPFieldInfo *);
T9U32 T9FARCALL T9CP_PinyinSyllableToBIN(T9U8 *pbSpell, T9U8 bSpellLen, T9U32 *pdwBIN, T9U8 bDualPhnLdb);
/*------------------------------------------------------------------------
 *
 *  Function    : T9CP_GetSyllablePIDRange
 *
 *  Synopsis    : It gets the phonetic ID range for the specified syllable.
 *
 *     Input    : pT9CPFieldInfo = Pointer to PTI field info structure.
 *                pbSpell        = Character's spelling.
 *                bSpellLen      = Character's spelling length.
 *                bPartial       = 0 - the syllable is complete;
 *                                 1 - the syllabel can be partial or complete
 *
 *    Output    : pwStartPID     = First phonetic ID.
 *                pwPartStartPID = First phonetic ID for partial syllable.
 *                pwPartEndPID   = Last phonetic ID for partial syllable.
 *
 *    Return    : 0 - success; 1 - the specified syllable is not found.
 *
 *    NOTE:       *pwStartPID <= exact match < *pwPartStartPID
 *                *pwPartStartPID <= partial match < *pwPartEndPID
 *-----------------------------------------------------------------------*/
T9U8 T9FARCALL T9CP_GetSyllablePIDRange(T9CPFieldInfo * pT9CPFieldInfo,
                                      T9U8 *          pbSpell,
                                      T9U8            bSpellLen,
                                      T9U8            bPartial,
                                      T9U16 *         pwStartPID,
                                      T9U16 *         pwPartStartPID,
                                      T9U16 *         pwPartEndPID);
/* testing if a syllable is valid */
T9U8 T9FARCALL T9CP_ValidateSyl(T9CPFieldInfo * pT9CPFieldInfo,
                               T9U8 *          pbSpell,
                               T9U8            bSpellLen,
                               T9U8            bPartial);
T9U8 T9FARCALL T9CP_SearchSylbFromTable(T9CPFieldInfo *pT9CPFieldInfo, T9U8 bBpmfType, T9U8 bPartial,
                                         T9U32 dwCharBIN, T9U32 dwMask, T9U16 *pwStartIndex, T9U16 *pwEndIndex);
T9STATUS T9FARCALL T9CP_BuildPhrase(T9CPFieldInfo *, T9CPPhraseInfo *, T9CPSpellInfo *, T9U8, T9U8, T9U8);
T9U8 T9FARCALL T9CP_PIDSearchLdb(T9CPFieldInfo *, T9U16 *, T9U8);
void T9FARCALL T9CP_AddMohuSpells(T9CPFieldInfo * pT9CPFieldInfo,
                                  T9U8 bNumContext,
                                  T9U8 bSingleSyl
#ifndef T9CPNOUDB
                                  , T9U32 dwUdbFreq
#endif
                                  );
/****************************************************************************************************
 * function description:
 *      This function test if the given spelling matches the key sequence based on the mohu flags in T9CPFieldInfo
 *      *psSpell will be modified to the spelling that matches the key sequence if the spelling matches, otherwise,
 *      *psSpell is not defined.  This function also calculate the tone information for the spelling.
 *
 * in:  psSpell - pointing to the spelling
 *      pbKeyBuf - the key buffer to be compared with
 *      bLen -  the key buffer length
 *      pbTones - the tone buffer
 *
 * out: pbTones - the tone information if pbTones is not null.
 *      pT9CPFieldInfo->CommonInfo.bNumCharacters - the number of syllables in the output spelling if pbTones
 *          is not 0.
 *
 * return T9U8 1 - match, 0 - mismatch.
 *
 ***************************************************************************************************/
T9U8 T9FARCALL T9CP_DoesSpellMatchKeySeq(T9CPFieldInfo *pT9CPFieldInfo,
                                         T9CPSpellInfo *psSpell,
                                         T9U8 *pbKeyBuf,
                                         T9U8 bLen,
                                         T9U8 *pbTones);
#ifndef T9CPNOUDB
/*------------------------------------------------------------------------
 *
 *  Function    : T9CP_PhoneticRestore
 *
 *  Synopsis    : It restore the phonetic core to the saved states. Then set the active spell.
 *
 *     Input    :   pT9CPFieldInfo = Pointer to PTI field info structure.
 *                  pbKey          = Character's spelling.
 *                  bKeyLen        = Character's spelling length.
 *                  pbActSpell     = pointing to active spell
 *                  bStemLen       = saved stem spell length.
 *
 *    Return    : T9STATNONE for success
 *
 *-----------------------------------------------------------------------*/
T9STATUS T9FARCALL T9CP_PhoneticRestore(T9CPFieldInfo * pT9CPFieldInfo,
                                        T9U8 *pbKey,
                                        T9U8 bKeyLen,
                                        T9CPSpellInfo *pbActSpell,
                                        T9U8 bStemLen);
#endif
/*------------------------------------------------------------------------
 *
 *  Function    : T9CP_SetupPIDRanges
 *
 *  Synopsis    : This function calculate the PID ranges for the spell and save it in the FieldInfo
 *                  The spelling has to match the key sequence
 *
 *     Input    : pT9CPFieldInfo = Pointer to PTI field info structure.
 *                pbInKeyBuf     = key buffer corresponding to pbSpell.
 *                pbSpell        = the spelling buffer. Assuming the spell length is the key buffer length
 *                pbTones        = the tone buffer.  It points to continuous T9CPMAXPHRASESIZE bytes.
 *                bLen           = the length of the spelling buffer
 *
 *    Return    :
 *                  pbTones     tone information on each key.  It is in bit mask format.  For example:
 *                              a tone 4 is represented in a byte of 0000 1000
 *                  T9U8        number of syllables
 *
 *-----------------------------------------------------------------------*/
T9U8 T9FARCALL T9CP_SetupPIDRanges(T9CPFieldInfo * pT9CPFieldInfo,
                                   T9U8 *pbKeyBuf, T9U8 *pbSpell,
                                   T9U8 *pbTones, T9U8 bLen);

/*------------------------------------------------------------------------
 *
 *  Function    : T9CP_SetupPIDRangesFromKeys
 *
 *  Synopsis    : This function populates the PID ranges from keys.
 *                Note: Ranges are set as exact ranges.
 *                      No ranges if beyond key count limits.
 *
 *     Input    : pT9CPFieldInfo = Pointer to PTI field info structure.
 *
 *    Return    : none
 *
 *-----------------------------------------------------------------------*/
void T9FARCALL T9CP_SetupPIDRangesFromKeys(T9CPFieldInfo * pT9CPFieldInfo);

/* BPMF mode LDB function prototypes */
void T9FARCALL T9CP_BINToBpmfSyllable(T9CPFieldInfo *pT9CPFieldInfo, T9U32 dwBIN, T9U8 *pbSpell, T9U8 *pbSpellLen);
T9U32 T9FARCALL T9CP_BpmfSyllableToBIN(T9CPFieldInfo *pT9CPFieldInfo, T9U8 *pbSpell, T9U8 bSpellLen, T9U32 *pdwBIN);
T9U32 T9FARCALL T9CP_BpmfSylbIndexToBIN(T9CPFieldInfo *pT9CPFieldInfo, T9U16 wIndex);
void T9FARCALL T9CP_SylbIndxToBIDRange(T9CPFieldInfo *pT9CPFieldInfo, T9U16 wSylbIndx, T9U8 bSylbIndxRng,
                                       T9U16 *pwStartPID, T9U16 *pwEndPID);
T9U8 T9FARCALL T9CP_GetSyllableIndex(T9CPFieldInfo *pT9CPFieldInfo,
                                     T9U8          *pbSpell,
                                     T9U8           bSpellLen,
                                     T9U8           bPartial,
                                     T9U16         *pwExactSylIndex,
                                     T9U8          *pbExactSylIndexRange, 
                                     T9U16         *pwPartSylIndex,
                                     T9U8          *pbPartSylIndexRange);
T9UINT T9FARCALL T9CP_SylbToBIDRanges(T9CPFieldInfo * pT9CPFieldInfo, T9U8 *pbSpell, T9U8 bNumLettr, T9U8 bPartial,
                                    T9U8 bLastSylb, T9U16 **ppwRange, T9U8 **ppbRangeStart);
T9U8 T9FARCALL T9CP_SetupBIDRangesFromKeys(T9CPFieldInfo * pT9CPFieldInfo);
/*---------------------------------------------------------------------------------------
 *  Define Chinese PTI internal return status codes (only used internally)
 *---------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------
 * Chinese Stroke PTI definitions
 *-----------------------------------------------------------------*/


/* The order of the enum is the same as that in database module flag.
 * Make sure 1 << enum & wModuleFlag is the flag for the corresponding module
 *     and dwOffset[enum] is the offset of the corresponding module.
 */
typedef enum {
    T9CP_ModuleList_TegicUnicodeLookup = 0,
    T9CP_ModuleList_StrokeTegicLookup,
    T9CP_ModuleList_SingleStroke,
    T9CP_ModuleList_Phonetic
    /*T9CP_ModuleList_Word */
} T9CP_MODULE_LIST;

/* definitions of module masks */
/*
#define T9CP_MODULEMASK_TEGICUNICODE    (1 << T9CP_ModuleList_TegicUnicodeLookup)
#define T9CP_MODULEMASK_STROKETEGIC     (1 << T9CP_ModuleList_StrokeTegicLookup)
#define T9CP_MODULEMASK_SINGLESTROKE    (1 << T9CP_ModuleList_SingleStroke)
#define T9CP_MODULEMASK_PHONETIC        (1 << T9CP_ModuleList_Phonetic)
*/

/*----------------------------------------------------------------------------
 *  Define PTI LDB header field offsets
 *----------------------------------------------------------------------------*/
typedef enum {
    T9CPVERSION_OFFSET        = 0x20, /* Offsets into LDB version             */
    T9CPDBTYPE_OFFSET         = 0x21, /* Offset of database type              */
    T9CPCORECOMP_OFFSET       = 0x22, /* Offset to Core compatible number     */
    T9CPOEMID_OFFSET          = 0x24, /* Offset to OEM ID                     */
    T9CPCHECKSUM_OFFSET       = 0x26, /* Offset to checksum                   */
    T9CPLANGUAGEID_OFFSET     = 0x28, /* Offset to primary language ID        */
    T9CPCONTENT_VER_OFFSET    = 0x2A, /* Offset to start of contents version  */
    T9CPMODULE_CHARSET_OFFSET = 0x2D, /* Offset to module and character set presence */
    T9CPSYMBOLBYTE_OFFSET     = 0x2E, /* Offset to symbol bytes               */
    T9CPBPMFLDB_OFFSET        = 0x30, /* Offset to BPMF LDB module            */
    T9CPPINYINLDB_OFFSET      = 0x34, /* Offset to pinyin LDB module          */
    T9CPWORDLDB_OFFSET        = 0x38, /* offset to the word module            */
    T9CPSTROKELDB_OFFSET      = 0x3C, /* Offset to stroke LDB module          */
    T9CPUNICODE_OFFSET        = 0x40, /* offset to the PID to Unicode lookup table */
    T9CPFREQUENCY_OFFSET      = 0x44, /* offset to the PID to frequency lookup table */
    T9CPPIDTOSID_OFFSET       = 0x48, /* offset to the PID to SID lookup table */
    T9CPSIDTOPID_OFFSET       = 0x4C, /* offset to the SID to PID lookup table */
    T9CPCOMMONCHAR_OFFSET     = 0x50, /* offset to the Common character table  */
    T9CPNAMETABLE_OFFSET      = 0x54, /* offset to the Name character table    */
    T9CPSYMCOUNT_OFFSET       = 0x58  /* offset to the Symbol character count  */
} T9CPLdbFieldOffsets;

typedef struct T9CP_Data_Component_s {
    T9U16   wLowerLimit;        /* the smallest Unicode of components */
    T9U16   wUpperLimit;        /* the biggest Unicode of components */
    T9U16   wTotal;             /* the total number of components */
    T9U32   dwDataOffset;       /* the offset of the start of component data */
} T9CP_DATA_COMPONENT;

typedef struct T9CP_Data_SingleStroke_s {
    /*T9U32   dwOffsetComponent;  don't need the field for component structure is included */
    T9U8    bInputVer;
    T9U8    bNumStroke;         /* total number of kinds of strokes.  The value is 5 in Tegic products */
    T9U8    bNumTreeLayers;     /* minimum number of tree layers */
    T9U32   dwDataOffset;       /* the offset of the start of data */
    T9CP_DATA_COMPONENT     sComp;  /* the component structure, wTotal = 0 means no component */
} T9CP_DATA_SINGLESTROKE;

T9U8 T9FARCALL  T9CP_GetSymbolCount(T9CPFieldInfo * pT9CPFieldInfo);
T9STATUS T9FARCALL T9CP_SymbolGetPhrase(T9CPFieldInfo *pT9CPFieldInfo, T9CPGETTYPE eGetType, T9CPPhraseInfo *pPhraseInfo);
T9STATUS T9FARCALL T9CP_NumGetPhrase(T9CPFieldInfo *pT9CPFieldInfo, T9CPGETTYPE eGetType, T9CPPhraseInfo *pPhraseInfo);
#ifdef T9ALPHABETIC
T9STATUS T9FARCALL T9CP_AWGetPhrase(T9CPFieldInfo *pT9CPFieldInfo, T9CPGETTYPE eGetType, T9CPPhraseInfo *pPhraseInfo);
T9STATUS T9FARCALL T9CP_AWSelectPhrase(T9CPFieldInfo *pT9CPFieldInfo, T9CPPhraseInfo *pPhrase);
#endif /*END T9ALPHABETIC */

/* End don't mangle the function name if compile under C++ */
#if defined(__cplusplus)
    }
#endif

#endif  /* #ifndef T9CPLDB_H */

/* ----------------------------------< eof >--------------------------------- */
