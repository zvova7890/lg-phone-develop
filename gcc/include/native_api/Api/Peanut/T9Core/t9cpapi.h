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
;**     FileName: t9cpapi.h                                                   **
;**                                                                           **
;**  Description: Chinese Phrase Text Input API Interface Header File.        **
;**               Conforming to the development version of T9 PTI.            **
;**                                                                           **
;*******************************************************************************
;******************************************************************************/

#ifndef T9CPAPI_H
#define T9CPAPI_H 1

#include "t9.h"

/* don't mangle the function name if compile under C++ */
#if defined(__cplusplus)
extern "C" {
#endif

#ifdef T9ALPHABETIC
#include "t9awapi.h"
#endif

#if T9SYMBOLWIDTH != 2
#error T9SYMBOLWIDTH has to be 2 in PTI
#endif

#if defined(T9CP_DISABLE_PHONETIC)&&defined(T9CP_DISABLE_STROKE)
#error Can not disable both phonetic and stroke inputs.
#endif

/*----------------------------------------------------------------------------
 *  Define Chinese PTI core version number
 *
 *    String format is defined as "T9CP VMM.mm.bf.qa"
 *    Where
 *      MM   = major version number
 *      mm   = minor version number
 *      bf   = bug fix version number
 *      qa   = QA release version number
 *----------------------------------------------------------------------------*/
#define T9CPCOREVER	"T9CP V04.00.00   "

/* UDB requires RDB */
#if (!defined(T9CPNOUDB) && defined(T9CPNORDB))
#undef T9CPNORDB
#endif

/*----------------------------------------------------------------------------
 *  Define some basic PTI constants.                                          
 *----------------------------------------------------------------------------*/
#define T9CPMAXLDBOBJECTS          32   /* max number of instructions in the phonetic tree */
#define T9CPMAXLDBPHRASESIZE        6   /* Max the phrase length supported by T9 Chinese PTI system */
#define T9CPMAXSINGLESYLSIZE        7   /* max number of letters per syllable including tone */
#define T9CP_PHRASEBUFSIZE        1024  /* phrase buffer size for PTI use */
#ifndef T9CPMAXPAGESIZE
#define T9CPMAXPAGESIZE             9   /* max number of character that can be displayed on a selection page */
#endif
#define T9CPSYLLABLEDELIMITER     ' '   /* delimiter symbol in the spelling in the core */
#define T9CPMAXUDBPHRASESIZE       32   /* Max the UDB phrase length supported by T9 Chinese PTI system */
#define T9CPMAXCONTEXTHISTORY       2   /* max selection history that can be remembered */

#if (T9CPMAXUDBPHRASESIZE > T9CPMAXLDBPHRASESIZE)
#define T9CPMAXPHRASESIZE T9CPMAXUDBPHRASESIZE
#else
#define T9CPMAXPHRASESIZE T9CPMAXLDBPHRASESIZE
#endif

#define T9CPMAXSPELLSIZE (T9CPMAXPHRASESIZE * T9CPMAXSINGLESYLSIZE)   /* Max spelling length supported by T9 Chinese PTI system */
#define T9CP_MAXIDRANGESIZE          144
#define T9CPMAXPHONETICKEY          (T9CPMAXLDBPHRASESIZE * T9CPMAXSINGLESYLSIZE)  /* Max phonetic key length supported by T9 Chinese PTI system */
#define T9CP_STROKE_MAX_NUM  55     /* the maximum number of strokes per character */

typedef enum {
    T9CPGETFIRST = 0,                   /* get the first one */
    T9CPGETCURRENT,                     /* get current one */
    T9CPGETNEXT,                        /* get next one */
    T9CPGETPREVIOUS                     /* get previous one */
} T9CPGETTYPE;

typedef enum {
    T9CPTONE1 = 1,                 /* tone 1 */
    T9CPTONE2,                     /* tone 2 */
    T9CPTONE3,                     /* tone 3 */
    T9CPTONE4,                     /* tone 4 */
    T9CPTONE5                      /* tone 5 */
} T9CPTONE;


/* Define max key length */
#if (defined(T9CPMAXPHONETICKEY) && defined(T9CP_STROKE_MAX_NUM))
#if (T9CPMAXPHONETICKEY > T9CP_STROKE_MAX_NUM)
#define T9CPMAXKEY T9CPMAXPHONETICKEY
#else
#define T9CPMAXKEY T9CP_STROKE_MAX_NUM
#endif
#elif defined(T9CPMAXPHONETICKEY)
#define T9CPMAXKEY T9CPMAXPHONETICKEY
#elif defined(T9CP_STROKE_MAX_NUM)
#define T9CPMAXKEY T9CP_STROKE_MAX_NUM
#else
#error cannot determine T9CPMAXKEY
#endif

/*----------------------------------------------------------------------------
 *  Define some T9 Chinese PTI data and information structures.                                          
 *----------------------------------------------------------------------------*/
typedef struct T9CPSpellInfo_s {
    T9U8    bSpell[T9CPMAXSPELLSIZE];   /* Pinyin spelling */
    T9U8    bSpellLen;                  /* length of spelling */    
} T9CPSpellInfo;

typedef struct T9CPPhraseInfo_s {
    T9SYMB  sPhrase[T9CPMAXPHRASESIZE];     /* character's Unicodes */  
    T9U8    bPhraseLen;                     /* length of phrase */
} T9CPPhraseInfo;

/* Define structure for Chinese PTI Private persistent data */
#ifndef T9CP_DISABLE_PHONETIC

typedef struct T9CPPPrivate_s {
    T9U32       dwHeaderOffset;                             /* start of the pinyin tree header */
    T9U32       dwSyllableOffset;                           /* offset to syllable information table */
    T9U32       dwToneOffset;                               /* offset to PID to tone lookup table */
    T9U32       dwBpmfSylEncodeOffset;                      /* offset to BPMF syllable encoding table */
    T9U32       dwBpmfSylDecodeOffset;                      /* offset to BPMF syllable decoding table */
    T9CPSpellInfo sStemSpell;
    T9U8        pbSaveKeysLeft[T9CPMAXPHONETICKEY];         /* save for tree node decoding */

#ifndef T9CPNOUDB
    T9U8        bSavedActSpellBuf[T9CPMAXKEY];              /* current active spelling including partial expanded spelling */
    T9U8        sSavedStemSpellLen;                         /* save stem spell length for restoration later */
#endif
} T9CPPPrivate;
#endif /* END #ifndef T9CP_DISABLE_PHONETIC */

#ifndef T9KEYZERO
#define T9KEYZERO               T9KEYAMBIGA /* the T9KEY for entering digit '0' */
#endif

/*****************************************
 * for stroke
 ***************************************/

#ifndef T9KEY_STROKE_WILDCARD
#define T9KEY_STROKE_WILDCARD   T9KEYAMBIG6
#endif

#ifndef T9KEY_COMPONENT
#define T9KEY_COMPONENT (T9KEY_STROKE_WILDCARD + 1)
#endif

#ifndef T9CP_DISABLE_STROKE

#define T9CP_STROKE_NUMOFSTROKE 5   /* number of stroke, Tegic has only 5 stroke system */
#define T9CP_STROKE_MAXNODES 4      /* in the current design, the informationa of the first 4 nodes are in tree structure */
#define T9CP_STROKE_MAX_MASK  (((T9CP_STROKE_MAX_NUM - T9CP_STROKE_MAXNODES) * 3 + 9) / 8)   /* number of member for the array nStrokeMask, need at least one more byte */

#define T9CP_NUM_SMALLNUMBER_NIBBLE_RANGES 3
#define T9CP_NUM_LARGENUMBER_NIBBLE_RANGES 3

typedef struct T9CPSPrivate_s {
    T9U16       wNumNumberNibbles[T9CP_NUM_SMALLNUMBER_NIBBLE_RANGES];      /* the parameter used for decoding numbers like number of exact matches and stroke counts */
    T9U16       wNumLargeNibbles[T9CP_NUM_LARGENUMBER_NIBBLE_RANGES];       /* the parameters for decoding total number of nibbles of a child node */
    T9U8        bStrokeMask0[T9CP_STROKE_MAX_MASK];  /* the 1st character's bit mask for the remaining stroke comparison */
    T9U8        bStrokePack0[T9CP_STROKE_MAX_MASK];  /* the 1st character's packed remaining strokes, the first stroke is in the byte of (T9U8*)nStrokePack */
    T9U8        bStrokeMask[T9CP_STROKE_MAX_MASK];  /* last character's bit mask for the remaining stroke comparison */
    T9U8        bStrokePack[T9CP_STROKE_MAX_MASK];  /* last character's packed remaining strokes, the first stroke is in the byte of (T9U8*)nStrokePack */
    T9U8        bActStrokes[T9CP_STROKE_MAXNODES];   /* the stroke sequence for internal use, mainly for parital match and wild card */
    T9U32       dwNodeOffsets[T9CP_STROKE_MAXNODES + 1];        /* offsets of the nodes */
    T9U16       wCurNodeSIDBase[T9CP_STROKE_MAXNODES + 1];      /* stroke ID bases of exact and partial matches for the nodes */
    T9U16       wCurTotalMatch[T9CP_STROKE_MAXNODES + 1];       /* number of total matches of the current node */
    T9U8        bLastDelimiterPos;                  /* last entered delimiter position in key sequence 1 based */
    T9U8        bAllowCompWildCard;                 /* a flag that indicates if component and wild cards are allowed for the current char */
    T9U8        bIsRangeExact;                      /* indicating if all the characters in the range are matches */

    /* component related fields */
    T9U32       dwOffsetComponent;                  /* the offset of component module */
    T9U32       dwOffsetMissingComponent;           /* the offset of missing component */
    T9U32       dwOffsetCompAddress;                /* the offset of the component addresses */
    T9U32       dwOffsetCompChars;                  /* the data offset of the related characters and components */
    T9U16       wCompUnicode;                       /* selected component unicode, 0 means no component */
    T9U16       wCompStdSID;                        /* the standard SID for the selected component */
    T9U8        bCompNumStrokes;                    /* the number of strokes of the component */

    /* UDB search related fields */
#ifndef T9CPNORDB
    T9U16       wUdbLastOffset;                     /* stop offset of last Udb search */
    T9U16       wUdbLastWordCount;                  /* remaining word count of last Udb search */
    T9U16       wUdbLastRangeEnd;                   /* range end of last Udb search; init to 0xFFFF */
#endif
} T9CPSPrivate;
#endif /* END of #ifdef T9CP_DISABLE_STROKE */

/***************** end of stroke ***************/

typedef struct T9CP_SpellBuf_s {
    T9U8        bTestClear;
    T9U8        *pbSpellBuf;                                /* pointer to the spell buffer */
    T9U8        bSpellIndex;                                /* the index of the current spelling */
    T9U8        bActiveSpell;                               /* the index of the active spell */
    T9U8        bNumSpells;                                 /* the total number of spells in the buffer */
    T9U16       wSpellBufLen;                               /* the length of the spell buffer */
    T9U8        pbIndexAlphSort[T9CPMAXLDBOBJECTS];         /* the buffer to sort ldb spells */
} T9CP_SpellBuf;

struct T9CP_PhraseBuf {
    T9U8        bTestClear;                                 /* if this is set to true, the buffer is empty */
    T9U8        bIsDelimiterExpansion;                      /* this is set to 1 when setting active spelling, adding delimiter or deleting keys. 
                                                                    it is set to 0 when expansion fails */
    T9U16       wPhraseBufLen;                              /* the number of bytes used by phrase buffer */
    T9U16       wPhraseBufMaxLen;
    T9U16       wCurrent;                                   /* the current phrase index in the buffer, 1-based */
    T9U16       wTotal;                                     /* total number of phrases in the phrase buffer */
    T9U16       wPrevFreq;                                  /* the max freqency in the current sorting page */
    T9U16       wPrevPos;                                   /* the position of the last entry in the previous page.  It should be the address for UDB and the leading PID for LDB */
    T9U16       pwFreq[T9CPMAXPAGESIZE];                    /* the frequency information for the current page */
    T9U16       wCurrentPageStart;                          /* the byte offset of the start of the current page */
    T9U8        bPageSize;                                  /* the current page size T9CPMAXPAGESIZE/#of characters per phrase */
    T9U8        pbPhraseBuf[T9CP_PHRASEBUFSIZE];
};

typedef enum T9CP_IDEncode_e {
    T9CP_IDEncode_PID,    /*  0 */
    T9CP_IDEncode_SID,    /*  1 */
    T9CP_IDEncode_BID,    /*  2 */
    T9CP_IDEncode_UNI     /*  3 */
} T9CP_IDEncode;

typedef enum T9CPMohuPair_e {
    T9CPMOHU_PAIR_Z_ZH = 0,
    T9CPMOHU_PAIR_C_CH,
    T9CPMOHU_PAIR_S_SH,
    T9CPMOHU_PAIR_N_L,
    T9CPMOHU_PAIR_R_L,
    T9CPMOHU_PAIR_F_H,
    T9CPMOHU_PAIR_AN_ANG,
    T9CPMOHU_PAIR_EN_ENG,
    T9CPMOHU_PAIR_IN_ING,
    T9CPMOHU_PAIR_TOTAL
} T9CPMOHU_PAIR;
#define T9CPMOHU_PAIR_Z_ZH_MASK ((T9U16)(1 << T9CPMOHU_PAIR_Z_ZH))
#define T9CPMOHU_PAIR_C_CH_MASK ((T9U16)(1 << T9CPMOHU_PAIR_C_CH))
#define T9CPMOHU_PAIR_S_SH_MASK ((T9U16)(1 << T9CPMOHU_PAIR_S_SH))
#define T9CPMOHU_PAIR_N_L_MASK ((T9U16)(1 << T9CPMOHU_PAIR_N_L))
#define T9CPMOHU_PAIR_R_L_MASK ((T9U16)(1 << T9CPMOHU_PAIR_R_L))
#define T9CPMOHU_PAIR_F_H_MASK ((T9U16)(1 << T9CPMOHU_PAIR_F_H))
#define T9CPMOHU_PAIR_AN_ANG_MASK ((T9U16)(1 << T9CPMOHU_PAIR_AN_ANG))
#define T9CPMOHU_PAIR_EN_ENG_MASK ((T9U16)(1 << T9CPMOHU_PAIR_EN_ENG))
#define T9CPMOHU_PAIR_IN_ING_MASK ((T9U16)(1 << T9CPMOHU_PAIR_IN_ING))

typedef enum {
    T9CPSpellType_Unknown = 0, /* 0, unknown type for error handling, This has to be the first item */
	T9CPSpellType_Bpmf,   /* 1, from T9CP as it is in PTI v3.1 */
	T9CPSpellType_Pinyin, /* 2, from T9CP as it is in PTI v3.1 */
	T9CPSpellType_Jianpin,/* 3, from T9CP store {T9KEYNONE, T9CPSpellType_Jianpin} in spellInfo.bSpell */
	T9CPSpellType_Stroke, /* 4, from T9CP store {T9KEYNONE, T9CPSpellType_Stroke} in spellInfo.bSpell */
	T9CPSpellType_Num,    /* 5, from T9CP store digits in spellInfo.bSpell eg. {0x31,...} */
	T9CPSpellType_abc,    /* 6, from T9AW store {T9KEYNONE, T9CPSpellType_abc} in spellInfo.bSpell */
	T9CPSpellType_Abc,    /* 7, from T9AW store {T9KEYNONE, T9CPSpellType_Abc} in spellInfo.bSpell */
	T9CPSpellType_ABC,    /* 8, from T9AW store {T9KEYNONE, T9CPSpellType_ABC} in spellInfo.bSpell */
	T9CPSpellType_Sym,    /* 9, from T9CP store {T9KEYNONE, T9CPSpellType_Sym} in spellInfo.bSpell */
    T9CPSpellType_MAX     /* This has to be the last item */
} T9CPSpellType;
/* Note: core can support up to 15 spell types */

#define T9CPSpellType_Bpmf_MASK     ((T9U16)((T9U16)1 << T9CPSpellType_Bpmf))
#define T9CPSpellType_Pinyin_MASK   ((T9U16)((T9U16)1 << T9CPSpellType_Pinyin))
#define T9CPSpellType_Jianpin_MASK  ((T9U16)((T9U16)1 << T9CPSpellType_Jianpin))
#define T9CPSpellType_Stroke_MASK   ((T9U16)((T9U16)1 << T9CPSpellType_Stroke))
#define T9CPSpellType_Num_MASK      ((T9U16)((T9U16)1 << T9CPSpellType_Num))
#define T9CPSpellType_abc_MASK      ((T9U16)((T9U16)1 << T9CPSpellType_abc))
#define T9CPSpellType_Abc_MASK      ((T9U16)((T9U16)1 << T9CPSpellType_Abc))
#define T9CPSpellType_ABC_MASK      ((T9U16)((T9U16)1 << T9CPSpellType_ABC))
#define T9CPSpellType_Sym_MASK      ((T9U16)((T9U16)1 << T9CPSpellType_Sym))

#define T9CPSpellType_AW_MASK       ((T9U16)(T9CPSpellType_abc_MASK | T9CPSpellType_Abc_MASK | T9CPSpellType_ABC_MASK))

/* useful macros related to spell types */
#define T9CP_IsValidSpellType(eType)    ((T9CPSpellType_Unknown < (eType)) && ((eType) < T9CPSpellType_MAX))
#define T9CPSpellType_IsAW(eType)       (T9CP_IsValidSpellType(eType) && ((T9CPSpellType_abc == (eType)) || (T9CPSpellType_Abc == (eType)) || (T9CPSpellType_ABC == (eType))))
#define T9CPSpellType_IsPhonetic(eType) (T9CP_IsValidSpellType(eType) && ((T9CPSpellType_Pinyin == (eType)) || (T9CPSpellType_Bpmf == (eType))))

struct T9CP_LdbOffsets {
    T9U32       dwBpmfLDBOffset;            /* BPMF LDB module offset */
    T9U32       dwPinyinLDBOffset;          /* pinyin LDB module offset */
    T9U32       dwWordLDBOffset;            /* word module offset */
    T9U32       dwStrokeLDBOffset;          /* stroke LDB module offset */
    T9U32       dwUnicodeOffset;            /* PID to Unicode lookup table offset */
    T9U32       dwFrequencyOffset;          /* PID to frequency lookup table offset */
    T9U32       dwPIDToSIDOffset;           /* PID to SID lookup table */
    T9U32       dwSIDToPIDOffset;           /* SID to PID lookup table */
    T9U32       dwCommonCharOffset;         /* Common character lookup table */
    T9U32       dwFirstPIDWordOffset;       /* first PID offset lookup table */
    T9U32       dwWordListDataOffset;       /* word list starting offset */
    T9U32       dwSyllableBIDOffset;        /* syllable - BPMF ID range lookup table offset */
    T9U32       dwSyllablePIDOffset;        /* syllable - Pinyin ID range lookup table offset */
    T9U32       dwNameTableOffset;          /* name character table offset */
};

typedef struct T9CPCommon_s {               /* common data fields between stroke and pheontic modules */
    T9U16       wTotalNumBpmfSybl;          /* total number of BPMF spelling syllables */
    T9U16       wTotalNumPinyinSybl;        /* total number of Pinyin spelling syllables */
    T9U16       wMohuFlags;                 /* the mohu pinyin flags, see, for example T9CPMOHU_PAIR_Z_ZH_MASK */
    T9U16       wSavedMohuFlags;            /* Mohu Flags are preserved here to prevent information lost due to language switched */
    T9U16       wTotalNumCharIDs;           /* total number of PIDs for CHAR if phonetic module exist, otherwise number of SIDs */
    T9U16       wTotalPIDs;                 /* total number of PIDs exclude components. Currently, SYM_Count + wTotalNumCharIDs = wTotalPIDs */
    T9U16       wComponentFirst;            /* unicode of the first component */
    T9U16       wComponentLast;             /* unicode of the last component */
    T9U16       wSpellTypeFlags;            /* bit mask to indicate which spell types are enabled */
    T9U16       pwRange[T9CP_MAXIDRANGESIZE];            /* the ID range for both SID and PID */
    T9U8        pbRangeStart[T9CPMAXPHRASESIZE];        /* the starting index in wRange for the character */
    T9U16       pwContextBuf[T9CPMAXPHRASESIZE - 1];    /* the context buffer in PID/SID.  We save up to (T9CPMAXPHRASESIZE - 1) characters or T9CPMAXCONTEXTHISTORY phrases, whichever has fewer characters */
    T9U8        pbContextLen[T9CPMAXCONTEXTHISTORY + 1];    /* the lengths of the context units in pwContextBuf. 0-terminated */
    T9U8        bExtContext;                            /* context was set externally */
    T9U8        bNumCharacters;                         /* number of characters in the entered key sequence */
    T9U8        bNumWordBlocks;                         /* number of word list blocks */
    T9U8        bKeyBuf[T9CPMAXKEY + 1];        /* key input buffer, padding one more for explicit input */
    T9U8        bKeyBufTotalLen;            /* the length of the keys for all input modes */
    T9U8        bKeyBufLen;                 /* length of ambiguous key sequence for stroke and phonetic */
    T9U8        bAWKeyCount;                /* count of valid keys for the AW core */
#ifndef T9CPNOUDB
    T9U8        bSavedKeyBuf[T9CPMAXKEY + 1];   /* keys when UDB edit starts.  padding one more for explicit input*/
    T9U8        bSavedKeyBufLen;            /* > 0 : single char mode, == 0 : phrasal mode */
    T9U8        bSavedKeysChanged;          /* 0 : restore keys when UDB edit exit, 1 : don't restore */
    T9U8        bCurrUdbSpellPos;           /* current working spelling positions for UDB creation */
    T9U8        bFlagInsertKey;             /* boolean type indicating we are insert a key in the middle of the key buffer */
    T9U8        bNumUdbCarryInKey;          /* number of key carried in when UDB editor is invoked */
    T9U8        bNumConsumedKeys;           /* the number of keys that will be consumed in bSavedKeyBuf */
    T9U8        bCarryInToneDelimiter;      /* the tone/delimiter at the end of carried in keys */
    T9U8        bLastCarryInTonePos;        /* index of the tone position in key buffer + 1. This is set to 0 
                                                  after bCurrUdbSpellPos passes the point.  This is for tone stem locking in inline editor */
    T9CPPhraseInfo sUIDOriginal;            /* Unicode of the phrase to be edited */
    T9CPPhraseInfo sPIDSIDClue;             /* PID/BID/SID as clue for forming the new phrase */
#endif
    T9CP_SpellBuf sSpellBuf;                /* the spell buffer structure */
    struct T9CP_PhraseBuf sPhraseBuf;       /* the phrase buffer */
    struct T9CP_LdbOffsets sOffsets;        /* the data modules' offsets in the LDB */
} T9CPCommonInfo;

typedef enum T9CP_MODE_e {
    T9CPMODE_INVALID = -1,      /* -1 */
    T9CPMODE_PINYIN = 0,        /* 0 */
    T9CPMODE_BPMF,              /* 1 */
    T9CPMODE_STROKE             /* 2 */
} T9CPMode;

#define T9CPIsMode(pT9CPFieldInfo, eModeIn) ((pT9CPFieldInfo) && ((pT9CPFieldInfo)->eMode == (eModeIn)))
#define T9CPIsModePinyin(pT9CPFieldInfo)    T9CPIsMode(pT9CPFieldInfo, T9CPMODE_PINYIN)
#define T9CPIsModeBpmf(pT9CPFieldInfo)      T9CPIsMode(pT9CPFieldInfo, T9CPMODE_BPMF)
#define T9CPIsModeStroke(pT9CPFieldInfo)    T9CPIsMode(pT9CPFieldInfo, T9CPMODE_STROKE)

typedef enum {
    T9CPSTATE_COMPONENT,        /* 0 */
    T9CPSTATE_UDBEDIT,          /* 1 */
    T9CPSTATE_EXPL_INPUT,       /* 2 */
    T9CPSTATE_NAME_INPUT        /* 3 */
} T9CPState;

#define T9CPSTATE_COMPONENT_MASK        (1L << T9CPSTATE_COMPONENT) /* component is on when it is set */
#define T9CPSTATE_UDBEDIT_MASK              (1L << T9CPSTATE_UDBEDIT)
#define T9CPSTATE_EXPL_INPUT_MASK       (1L << T9CPSTATE_EXPL_INPUT)
#define T9CPSTATE_NAME_INPUT_MASK       (1L << T9CPSTATE_NAME_INPUT)
#define T9CPIsStateActive(pT9CPFieldInfo, eState) ((pT9CPFieldInfo) && ((pT9CPFieldInfo)->bState & (T9U8)(1 << (eState))))
#define T9CPIsComponentActive(pT9CPFieldInfo) T9CPIsStateActive(pT9CPFieldInfo, T9CPSTATE_COMPONENT)
#define T9CPIsUDBEditActive(pT9CPFieldInfo) T9CPIsStateActive(pT9CPFieldInfo, T9CPSTATE_UDBEDIT)
#define T9CPIsExplInputActive(pT9CPFieldInfo) T9CPIsStateActive(pT9CPFieldInfo, T9CPSTATE_EXPL_INPUT)
#define T9CPIsNameInputActive(pT9CPFieldInfo) T9CPIsStateActive(pT9CPFieldInfo, T9CPSTATE_NAME_INPUT)

#define T9CPGetChineseLdbNum(pT9CPFieldInfo) ((pT9CPFieldInfo)? ((pT9CPFieldInfo)->G.nLdbNum) : 0)

/* test if UDB is active and it is in insert mode */
#define T9CPIsUdbInsertKey(pT9CPFieldInfo) (T9CPIsUDBEditActive(pT9CPFieldInfo) && (pT9CPFieldInfo)->CommonInfo.bNumUdbCarryInKey && (pT9CPFieldInfo)->CommonInfo.bFlagInsertKey)
/* test if UDB is active and it is in append mode */
#define T9CPIsUdbAppendKey(pT9CPFieldInfo) (T9CPIsUDBEditActive(pT9CPFieldInfo) && (pT9CPFieldInfo)->CommonInfo.bNumUdbCarryInKey && !(pT9CPFieldInfo)->CommonInfo.bFlagInsertKey)

#define T9CPIsAWActive(pT9CPFieldInfo)  ((pT9CPFieldInfo) && (pT9CPFieldInfo)->pAWG)

#define T9CP_TONEDELKEYMASK       0xE0    /* mask for phonetic tone or delimiter in 
                                             the key buffer. 0010 - 1010 for 
                                             tones 1 - 5. 1110 for delimiter.
                                           */
#define T9CPSymToCPTone(bSym) ((T9U8)((((bSym) >= '0' + T9CPTONE1) && ((bSym) <= '0' + T9CPTONE5))?((bSym) - '1' + T9CPTONE1):0))

#define T9CPGetFirstComponent(pT9CPFieldInfo) ((pT9CPFieldInfo)? ((pT9CPFieldInfo)->CommonInfo.wComponentFirst) : 0)
#define T9CPGetLastComponent(pT9CPFieldInfo) ((pT9CPFieldInfo)? ((pT9CPFieldInfo)->CommonInfo.wComponentLast) : 0)

typedef struct {
#ifndef T9CP_DISABLE_STROKE
    T9CPSPrivate SPrivate;
#endif
#ifndef T9CP_DISABLE_PHONETIC
    T9CPPPrivate PPrivate;
#endif
} T9CPPrivate;

/* Optional features */

/* use RDB */
#ifndef T9CPNORDB

#define T9CPUDBMINSIZE              8192
#define T9CP_UDBBPMFZONES           37      /* based on BPMF letter */
#define T9CP_UDBPINYINZONES         26      /* based on Pinyin letter */
#define T9CP_UDBPHONETICZONES       T9CP_UDBBPMFZONES
#define T9CP_UDBSTROKEZONES         7       /* based on SID even distribution. Also allow the worst case: 8-byte struct alignment. */
#define T9CP_UDBZONEMAX             (T9CP_UDBPHONETICZONES + T9CP_UDBSTROKEZONES)

/* Define structure for Chinese PTI UDB */
typedef struct T9CPUdbInfo_s {
    const T9U16 wDataSize;        /* Total size in bytes of the database */
    const T9U16 wDataCheck;       /* Additive checksum of database */
    const T9U32 dwUpdateID;       /* Update ID for the last write. (multi-thread support) */
    const T9U16 wUpdateCount;     /* Count incremented when UDB is updated */
    const T9U16 wFreeBytes;       /* Total number of free bytes in the UDB */
    const T9U16 wCutOffFreq;      /* Freqency for cleaning up UDB entries when overcrowded */
    const T9U16 wLdbCompatibility;/* Store LDB compatibility info */
    const T9U16 wZoneOffset[T9CP_UDBZONEMAX];   /* Offsets to beginning of each zone. */
    const T9U16 wZoneWordCount[T9CP_UDBZONEMAX];/* Word counts in each zone. */
    const T9U8  bDataArea[CPUDB_MAX_SIZE];     /* Beginning of data area */
} T9CPUdbInfo;
#endif /* END use RDB */

typedef struct T9CPFieldInfo_s {
    T9FieldInfo     G;                  /* T9 Generic data structure */
    T9CPPrivate     Private;            /* persistent memory for PTI use */
    T9CPCommonInfo  CommonInfo;         /* phonetic and stroke common data structure */      
    T9CPMode        eMode;              /* Chinese mode */
    T9U8            bState;             /* Chinese state bit mask */
    T9FieldInfo     *pAWG;              /* point to the G struct within AW field info */
#ifndef T9CPNORDB
    T9CPUdbInfo     T9FARUDBPOINTER *pUdb;/* Pointer to the active UDB */
    T9U32           dwUdbUpdateID;      /* update ID in the Udb during my last read (multi-thread support) */
#endif

} T9CPFieldInfo;

/* BPMF spelling definitions */
/*
 * One byte BPMF spelling format:
 *  [ BBPMF bit (bit 7) ][ Uppercase bit (bit 6) ][ BPMF Letter ranging from 0 to 36 (bit 5 - 0) ]
 */
#define T9CPBPMFSPELLBIT            0x80
#define T9CPBPMFUPPERCASEBIT        0x40
#define T9CPBPMFFIRSTLOWERLETTER    0x80
#define T9CPBPMFLASTLOWERLETTER     0xA4
#define T9CPBPMFFIRSTUPPERLETTER    0xC0
#define T9CPBPMFLASTUPPERLETTER     0xE4
#define T9CPBpmfFirstUnicode        0x3105  /* unicode for letter Bo */

#define T9CP_IsByte(b)                  ((sizeof(b) == 1) || ((T9U8)(b) == (b))) /* private macro to chk if b's unsigned value <= 0xFF */

/* Macros for checking BPMF letter
 * Can accept any input as long as the unsigned value <= 0xFF.
 * Otherwise, 0 is returned.
 */
#define T9CPIsBpmfLetter(bLetter)       (T9CP_IsByte(bLetter) ? ((((T9U8)(bLetter) & ~T9CPBPMFUPPERCASEBIT) >= T9CPBPMFFIRSTLOWERLETTER) && (((T9U8)(bLetter) & ~T9CPBPMFUPPERCASEBIT) <= T9CPBPMFLASTLOWERLETTER)) : 0)
#define T9CPIsBpmfUpperCase(bLetter)    (T9CP_IsByte(bLetter) ? ((((bLetter) & (T9CPBPMFSPELLBIT | T9CPBPMFUPPERCASEBIT)) == (T9CPBPMFSPELLBIT | T9CPBPMFUPPERCASEBIT)) && ((T9U8)(bLetter) <= T9CPBPMFLASTUPPERLETTER)) : 0)
#define T9CPIsBpmfLowerCase(bLetter)    (T9CP_IsByte(bLetter) ? ((((bLetter) & (T9CPBPMFSPELLBIT | T9CPBPMFUPPERCASEBIT)) == T9CPBPMFSPELLBIT) && ((T9U8)(bLetter) <= T9CPBPMFLASTLOWERLETTER)) : 0)

#define T9CPIsStrokeLetter(bLetter)     ((((bLetter) >= T9KEYAMBIG1) && ((bLetter) <= T9KEYAMBIG5)) || ((bLetter) == T9KEY_COMPONENT) || ((bLetter) == T9KEY_STROKE_WILDCARD))

/* Convert a BPMF letter to its Unicode value
 * If the input is not a BPMF letter, 0 is returned. */
#define T9CPBpmfLetterToUnicode(bLetter) (T9U16)(T9CPIsBpmfLetter(bLetter) ? (((T9U8)(bLetter) & ~(T9CPBPMFSPELLBIT | T9CPBPMFUPPERCASEBIT)) + T9CPBpmfFirstUnicode) : 0)

/*----------------------------------------------------------------------------
 *
 *  Define T9 Chinese PTI API function prototypes      
 *
 *----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 *  T9 Chinese PTI system function prototypes
 *----------------------------------------------------------------------------*/
T9STATUS T9FARCALL T9CPInitialize(T9CPFieldInfo *pT9CPFieldInfo,
                                  T9ReadLdbData_f T9ReadLdbData, 
                                  T9HandleRequest_f T9HandleRequest);
T9STATUS T9FARCALL T9CPSetLanguage(T9CPFieldInfo *pT9CPFieldInfo, T9UINT nLdbNum);
T9STATUS T9FARCALL T9CPGetLdbVersion(T9FieldInfo *pFieldInfo, T9U8 *pbResponse);
T9STATUS T9FARCALL T9CPValidateLdb(T9FieldInfo *pFieldInfo, T9UINT nLdbNum);
T9STATUS T9FARCALL T9CPGetCodeVersion(T9U8 *pbCoreVerBuf, T9U16 wBufSize, T9U16 *pwCoreVerLen);
T9STATUS T9FARCALL T9CPSetInputMode(T9CPFieldInfo *pT9CPFieldInfo, T9CPMode eMode);

#ifdef T9ALPHABETIC
T9STATUS T9FARCALL T9CPSetAW(T9CPFieldInfo *pT9CPFieldInfo, T9AWFieldInfo *pAWFieldInfo);
#endif

/*----------------------------------------------------------------------------
 *  T9 Chinese PTI ambiguous key function prototypes
 *----------------------------------------------------------------------------*/
T9STATUS T9FARCALL T9CPAddAmbiguousKey(T9CPFieldInfo *pT9CPFieldInfo, T9U8 bKey);
T9STATUS T9FARCALL T9CPDelLastKey(T9CPFieldInfo *pT9CPFieldInfo);
T9STATUS T9FARCALL T9CPDelAllKeys(T9CPFieldInfo *pT9CPFieldInfo);
T9STATUS T9FARCALL T9CPGetKeySequence(T9CPFieldInfo *pT9CPFieldInfo, T9U8 *pbKeyBuf, T9U8 wBufSize, T9U8 *pbKeyLen);

/*----------------------------------------------------------------------------
 *  T9 Chinese PTI delimiter function prototypes
 *----------------------------------------------------------------------------*/
T9STATUS T9FARCALL T9CPAddDelimiter(T9CPFieldInfo *pT9CPFieldInfo);

/*----------------------------------------------------------------------------
 *  T9 Chinese PTI character and phrase function prototypes
 *----------------------------------------------------------------------------*/
T9STATUS T9FARCALL T9CPGetPhrase(T9CPFieldInfo *pT9CPFieldInfo, T9CPGETTYPE eGetType, T9CPPhraseInfo *psPhrase);
T9STATUS T9FARCALL T9CPSelectPhrase(/*IN, OUT*/T9CPFieldInfo *pT9CPFieldInfo, /*IN*/T9CPPhraseInfo *psPhrase, /*OUT*/T9CPSpellInfo *psSpell);

/*----------------------------------------------------------------------------
 *  T9 Chinese PTI context prediction function prototypes
 *----------------------------------------------------------------------------*/
T9STATUS T9FARCALL T9CPSetContext(T9CPFieldInfo *pT9CPFieldInfo, T9SYMB *psContext, T9UINT nContextLength);
T9STATUS T9FARCALL T9CPFlushContext(T9CPFieldInfo *pT9CPFieldInfo);

/* Spelling related APIs */
T9STATUS T9FARCALL T9CPSetSpellType(T9CPFieldInfo *pT9CPFieldInfo, T9CPSpellType eType);
T9STATUS T9FARCALL T9CPClrSpellType(T9CPFieldInfo *pT9CPFieldInfo, T9CPSpellType eType);
T9STATUS T9FARCALL T9CPChkSpellType(T9CPFieldInfo *pT9CPFieldInfo, T9CPSpellType eType);
T9CPSpellType T9FARCALL T9CPGetSpellType(const T9CPSpellInfo* const pSpell);
T9STATUS T9FARCALL T9CPGetSpell(T9CPFieldInfo *pT9CPFieldInfo, T9CPGETTYPE eGetType, T9CPSpellInfo *psSpell);
T9STATUS T9FARCALL T9CPSetActiveSpell(T9CPFieldInfo *pT9CPFieldInfo, T9CPSpellInfo *psSpell);
T9STATUS T9FARCALL T9CPGetActiveSpell(T9CPFieldInfo *pT9CPFieldInfo, T9CPSpellInfo *psSpell);

#ifndef T9CP_DISABLE_STROKE
/* APIs for Stroke input only */
/*---------------------------------------------------------------------------------
 * Description: This function disables or enables component in Chinese stroke input mode.
 *
 *      input:  pT9CPFieldInfo - pointing to the PTI structure
 *              fEnable - component will be enabled if true, disabled if false
 *      return: T9STAT_INVALID_STATE - the current mode is stroke and there 
 *                  is any stroke sequence.
 *              T9STATNOINIT - pT9CPFieldInfo is null or PTI is not initialized successfully
 *              T9STATNONE - successful.
 *---------------------------------------------------------------------------------*/
T9STATUS T9FARCALL T9CPEnableComponent(T9CPFieldInfo *pT9CPFieldInfo, T9U8 fEnable);
T9STATUS T9FARCALL T9CPGetSelectedComponent(T9CPFieldInfo *pT9CPFieldInfo, T9SYMB *psComp);

/*---------------------------------------------------------------------------------
 * Description: This function returns the stroke sequence for a given character
 *
 *      input:  pT9CPFieldInfo - pointing to the PTI structure
 *              sChar          - the unicode of a character
 *              pbBuf          - pointing to a stroke buffer
 *              pbLen          - *pbLen is the max number of strokes that are allowed in the buffer.
 *                               it can't be 0.  The value becomes the actual number of strokes returned 
 *                               exiting the call.
 *              bAltIndex      - alternate stroke index.  0-based.  0 to get most popular stroke sequence
 *                               1 to get second most popular sequence etc.
 *      return: T9STATNONE means a successful return, otherwise an error has occurred: either the 
 *                  character is not supported or the PTI core is not in the right status
 *---------------------------------------------------------------------------------*/
T9STATUS T9FARCALL T9CPGetCharStrokes(T9CPFieldInfo *pT9CPFieldInfo, T9SYMB sChar, T9U8 *pbBuf, T9U8 *pbLen, T9U8 bAltIndex);

#endif /* END APIs for Stroke input only */

#ifndef T9CP_DISABLE_PHONETIC
/* APIs for Phonetic input only */
/*----------------------------------------------------------------------------
 *  T9 Chinese PTI phonetic spelling function prototypes
 *----------------------------------------------------------------------------*/
T9STATUS T9FARCALL T9CPSetMohuPairs(T9CPFieldInfo *pT9CPFieldInfo, T9U16 wMohuPairBitMask);
T9STATUS T9FARCALL T9CPIsMohuPairEnabled(T9CPFieldInfo *pT9CPFieldInfo, T9CPMOHU_PAIR eMohuPair);
T9STATUS T9FARCALL T9CPGetCharSpell(T9CPFieldInfo * pT9CPFieldInfo, T9SYMB sCharacter, T9U8 bAlternateNum, T9U8 bGetTone, T9CPSpellInfo * pSpellInfo);
T9STATUS T9FARCALL T9CPAddExplPhoneticSym(T9CPFieldInfo *pT9CPFieldInfo, T9U8 bSym);

/*----------------------------------------------------------------------------
 *  T9 Chinese PTI phonetic tone function prototypes
 *----------------------------------------------------------------------------*/
T9STATUS T9FARCALL T9CPAddTone(T9CPFieldInfo *pT9CPFieldInfo, T9CPTONE bTone);
T9STATUS T9FARCALL T9CPGetToneOptions(T9CPFieldInfo *pT9CPFieldInfo, T9U8 *pbToneBitMask);

/*----------------------------------------------------------------------------
 *  T9 Chinese PTI Jianpin-related function prototypes [deprecated]
 *----------------------------------------------------------------------------*/
T9STATUS T9FARCALL T9CPSetJianpin(T9CPFieldInfo *pT9CPFieldInfo);
T9STATUS T9FARCALL T9CPClrJianpin(T9CPFieldInfo *pT9CPFieldInfo);
T9STATUS T9FARCALL T9CPChkSpellJianpin(T9CPFieldInfo *pT9CPFieldInfo, T9CPSpellInfo *pSpell);

#endif /* END APIs for Phonetic input only */

#ifndef T9CPNOUDB
/*----------------------------------------------------------------------------
 *  T9 Chinese PTI UDB edit function prototypes
 *----------------------------------------------------------------------------*/
T9STATUS T9FARCALL T9CPUdbEditStart(T9CPFieldInfo *pT9CPFieldInfo);
T9STATUS T9FARCALL T9CPUdbEditExit(T9CPFieldInfo *pT9CPFieldInfo, T9CPPhraseInfo *psPhrase, T9U8 * pbSpell, T9U8 bSpellLen, T9U8 bOKCancel);

/*---------------------------------------------------------------------------
 *
 *   Function: T9CPUdbSetInsertKey
 *
 *   Synopsis: This API sets the insert key mode in inline UDB editor.
 *              In insert key mode, the user's inputs(adding a key, deleting a
 *              key, adding a tone or a delimiter) will be at the end of 
 *              the current active spelling in phonetic input or key sequence
 *              in stroke input mode.
 *             
 *     Input: pT9CPFieldInfo = Pointer to Chinese PTI field info structure.
 *
 *       Output: none
 *
 *     Return: T9STATNONE on success, otherwise return T9 error code.
 *
 *---------------------------------------------------------------------------*/
T9STATUS T9FARCALL T9CPUdbSetInsertKey(T9CPFieldInfo *pT9CPFieldInfo);

/*---------------------------------------------------------------------------
 *
 *   Function: T9CPUdbSetAppendKey
 *
 *   Synopsis: This API sets the append key mode in inline UDB editor.
 *              In append key mode, the user's inputs(adding a key, deleting a
 *              key, adding a tone or a delimiter) will be at the end of 
 *              the key sequence.
 *             
 *     Input: pT9CPFieldInfo = Pointer to Chinese PTI field info structure.
 *
 *       Output: none
 *
 *     Return: T9STATNONE on success, otherwise return T9 error code.
 *
 *---------------------------------------------------------------------------*/
T9STATUS T9FARCALL T9CPUdbSetAppendKey(T9CPFieldInfo *pT9CPFieldInfo);

/*---------------------------------------------------------------------------
 *
 *   Function: T9CPUdbSetPhraseToEdit
 *
 *   Synopsis: Allow specifying the UDB phrase to be edited.
 *             Can only be called immediately after the UDB edit starts.
 *             
 *     Input: pT9CPFieldInfo = Pointer to Chinese PTI field info structure.
 *            psPhraseToEdit = phrase to be edited (in Unicode).
 *
 *       Output: none
 *
 *     Return: T9STATNONE on success, otherwise return T9 error code.
 *
 *---------------------------------------------------------------------------*/
T9STATUS T9FARCALL T9CPUdbSetPhraseToEdit(T9CPFieldInfo *pT9CPFieldInfo, T9CPPhraseInfo *psPhraseToEdit);
#endif

#ifndef T9CPNORDB
/*----------------------------------------------------------------------------
 *  T9 Chinese PTI UDB setup function prototypes
 *----------------------------------------------------------------------------*/
T9STATUS T9FARCALL T9CPUdbActivate(T9CPFieldInfo *pT9CPFieldInfo, T9CPUdbInfo T9FARUDBPOINTER *pUdb, T9U16 wDataSize);
T9STATUS T9FARCALL T9CPUdbReset(T9CPFieldInfo *pT9CPFieldInfo);

/*------------------------------------------------------------------------
 *  Function    : T9CPUdbDeletePhrase
 *  Description : Delete all entries in the UDB that exactly match the given
 *                Unicode.
 *     Input:   : pT9CPFieldInfo = pointer to PTI field info
 *              : pPhrase = phrase to delete (in Unicode)
 *    Output    : none
 *    Return    : T9STATNONE if successful, error otherwise.
 *-----------------------------------------------------------------------*/
T9STATUS T9FARCALL T9CPUdbDeletePhrase(T9CPFieldInfo *pT9CPFieldInfo, T9CPPhraseInfo *psPhrase);
#endif

/*----------------------------------------------------------------------------
 *  T9 Chinese PTI name-input-related function prototypes
 *----------------------------------------------------------------------------*/
T9STATUS T9FARCALL T9CPSetNameInput(T9CPFieldInfo *pT9CPFieldInfo);
T9STATUS T9FARCALL T9CPClrNameInput(T9CPFieldInfo *pT9CPFieldInfo);

#ifdef T9CHECKCOMPILE
enum {
    T9CPWRONGVALUE_SELECTPAGEMAXSIZE = T9CHECKCOMPILE_NEXT,
    T9CPWRONGVALUE_STROKE_WILDCARD
};

T9U32 T9FARCALL T9CPCheckCompileParameters(T9CPFieldInfo *pCPFieldInfo,
                                           T9U16  *pwT9CPFieldInfoSize, 
                                           T9U8   *pbyT9U8,
                                           T9U8   *pbyT9U16,
                                           T9U8   *pbyT9U32,
                                           T9U8   *pbyT9SYMB,
                                           T9U8   *pbyT9UINT,
                                           T9U8   *pbyT9INT,
                                           T9U8   *pbyT9MINOR,
                                           T9U8   *pbyT9FARDATA,
                                           T9U8   *pbyT9NEARDATA,
                                           T9U8   *pbyVoidPtr,
                                           T9U8   *pbCoreVer,
                                           T9U8   *pbT9MAXDBKEYS,
                                           T9U8   *pbT9MAXTAPKEYS,
                                           T9U8   *pbT9MAXTREES,
                                           T9U8   *pbT9CACHESIZE,
                                           T9U8   *pbT9CPMAXPAGESIZE,
#ifndef T9CP_DISABLE_STROKE
                                           T9U8   *pbT9KEYSTROKEWILDCARD,
#endif
                                           T9U32  *pdwInitOK);
#endif

/* End don't mangle the function name if compile under C++ */
#if defined(__cplusplus)
    }
#endif

#endif     /* #ifndef T9CPAPI_H */
    
/* ----------------------------------< eof >--------------------------------- */
