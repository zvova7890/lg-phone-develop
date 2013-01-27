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
;**     FileName: T9compat.h                                                  **
;**                                                                           **
;**  Description: Event-api compatibility declarations.                       **
;**                                                                           **
;**  Version:	  7.3                                                         **
;*******************************************************************************
;******************************************************************************/

#ifndef T9COMPAT_H
#define T9COMPAT_H    1

#include "t9ccapi.h" /* To be just like old, need Chinese */

/* don't mangle the function name if compile under C++ */
#if defined(__cplusplus)
extern "C" {
#endif

/*----------------------------------------------------------------------------
 *  Define T9 valid event types for T9HandleEvent.
 *----------------------------------------------------------------------------*/
typedef enum T9EVT_e {
    T9EVTNONE,                  /*  0 - No real event.                      */
    T9EVTINIT,                  /*  1 - Initialize T9 system                */
    T9EVTTERM,                  /*  2 - Terminate  T9 system                */
    T9EVTKEY,                   /*  3 - T9 Key event                        */
    T9EVTEXPL,                  /*  4 - T9 Explicit event.                  */
    T9EVTCTRL,                  /*  5 - T9 Control event.                   */
    T9EVTTIMEOUT,               /*  6 - T9 Timer experation event           */
    T9EVTTEXTKEY,               /*  7 - T9 Keystroke from text, process key */
    T9EVTSYMTOKEY,              /*  8 - Get ambiguous key for text symbol   */
    T9EVTUDBFENCE,              /*  9 - UDB selection list insertion point  */
    T9EVTSETLANG,               /* 10 - T9 Set new language number          */
    T9EVTCURSOR,                /* 11 - T9 Adjust cursor event              */
    T9EVT12,                    /* 12 - Reserved                            */
    T9EVT13,                    /* 13 - Reserved                            */
    T9EVT14,                    /* 14 - Reserved                            */
    T9EVTUDB,                   /* 15 - T9 UDB event.                       */
    T9EVTVALIDLDB,              /* 16 - Validate the downloaded LDB data    */
    T9EVTLDB,                   /* 17 - T9 LDB event                        */
    T9EVTMDB,                   /* 18 - T9 MDB event                        */
    T9EVTWORDCHECK,             /* 19 - Check if the word matches to the    */
                                /*      keystrokes.                         */
    T9EVTGETCORECOMPATID,       /* 20 - Get the complete compatibility ID of*/
                                /*      T9 core.                            */
    T9EVTGETSLCOUNT,            /* 21 - Word counts in the selection list   */
                                /*      that excluding the duplicates       */
    T9EVTRESETBUFFER,           /* 22 - Purge current T9 text buffer.       */
    T9EVTNOTEWORDDONE,          /* 23 - T9 Event to mark the use of a word  */
    T9EVTADDLANG,               /* 24 - T9 Event to add a language for bilingual T9         */
    T9EVTREMOVELANG,            /* 25 - T9 Event to add a language for bilingual T9         */
    T9EVTSWITCHLEADLANG,        /* 26 - T9 Event to switch leading language in bilingual T9 */
    T9EVTSETLANGFENCES,         /* 27 - T9 Event to change language fences in bilingual T9  */
    T9EVTSETMINLDBCOMPLCHARS,   /*28 - T9 Event to set the min. active chars required for RDB completions. */
	T9EVTFLUSHNOMARKUSE,		/* 29 - T9 Event to flush the active word without marking use */
    /* Language extension event types -- Chinese Range from 64-128          */
    T9EVTSTROKES           = 64,/* 64 - Retrieve strokes for character      */
    T9EVTSPELLING,              /* 65 - Retrieve spelling for character     */
    T9EVTSETTONE,               /* 66 - Set tone code filter (phonetic only)*/
    T9EVTSETSPELL,              /* 67 - Set spell code filter(phonetic only)*/
    T9EVT68,                    /* 68 - Reserved                            */
    T9EVT69,                    /* 69 - Reserved                            */
    T9EVT70,                    /* 70 - Reserved                            */
    T9EVT71,                    /* 71 - Reserved                            */
    T9EVT72,                    /* 72 - Reserved                            */
    T9EVT73,                    /* 73 - Reserved                            */
    T9EVT74,                    /* 74 - Reserved                            */
    T9EVT75,                    /* 75 - Reserved                            */
    T9EVTDYMCTXTFENCE,          /* 76 - T9 set Chinese Dynamic context Fence*/
    T9EVTCAUDBFENCE,            /* 77 - T9 set Chinese CAUDB Fence          */
    T9EVTDYMCTXTSEARCHDEPTH,    /* 78 - Set Chinese Dynamic Context search  */
                                /*      depth                               */
    T9EVTCAUDB,                 /* 79 - T9 CAUDB event                      */
    T9EVTPHRASECOMPFENCE,       /* 80 - T9 set Chinese Phrase completion    */
                                /*      Fence                               */
    T9EVTACCEPTPHRASECOMP,      /* 81 - T9 accept Phrase completion part    */
    T9EVTREJECTPHRASECOMP,      /* 82 - T9 reject Phrase completion part    */
    T9EVTMATCHSTROKEXTDYNCTXT,  /* 83 - T9 stroke match external dynamic    */
                                /*      context                             */
    T9EVTEXPLICITKEY,           /* 84 - T9 explicit key event               */
    T9EVTCUDB,                  /* 85 - T9 CUDB event                       */

#ifdef T9CDB_IN_BUILD
    T9EVTCDB,                   /* 86 - T9 CDB event                       */
    T9EVTCLEARBUFFER,           /* 87 - T9 clear buffer without brreaking context */
#endif
    /* Language extension event types -- Japanese Range from 125 - 191      */
    T9EVT_JUDB_DELETE = 125,    /* 125 - delete an entry from JUDB      */
                                        /* nValue param says which entry
                                           should be deleted              */
    T9EVT_JUDB_GET_NTH_ENTRY,   /* 126 - Get information stored in
                                             * the nth entry. Uses T9GetJUDB
                                             * struct                     */
    T9EVT_JUDB_GET_COUNT,       /* 127 - get total number of entries in
                                             the Japanese UDB. return value
                                             is stored in nValue param    */
    T9EVT_JUDB_DELETE_ALL,      /* 128 - delete all entries from JUDB */
    T9EVT_JUDB_ADD,             /* 129 - add the entry to the Japanese UDB.
                                             Provide data in the structure
                                             used for GET_NTH_ENTRY. */
    T9EVT_JUDB_CHECK_SPACE,     /* 130 */
    /* check whether the Japanese UDB has space for a new entry.  Use
      this event before adding a UDB entry if garbage collection has
      been disabled. The result is indicated by the status - T9STATNONE
      on success, T9STATFULL if no additional entries will fit. */
    T9EVTSYMTOKEYSEQ_REMOVE,    /* 131 - T9 Get key sequence for text symbol */
    T9EVTJTEXTKEY,              /* 132 - Similar to T9EVTTEXTKEY, but also supply
                                    * key info.  */
    T9EVT_JUDB_CHECKSUM_UDB1,   /* 133 - Check for UDB 1 */
    T9EVT_JUDB_CHECKSUM_UDB2,   /* 134 - Check for UDB 2 */
    T9EVT_JUDB_CHECKSUM_YRDB,   /* 135 - Check for Yomi RO DB */
    T9EVT_JUDB_UPDATE,          /* 136 - Add an entry to the Japanese UDB2 */
    T9EVT_JUDB_UPDATECOMPWORD,  /* 137 */
    T9EVT_JUDB_GETCOMPWORD,     /* 138 */
    T9EVT_JUDB_CHECKSUM_ACDB,   /* 139 - Check for Complete DB */
    
    T9EVT_JUDB_ADD_AUTOUDB,     /* 140 */
    T9EVT_GET_JMT_TABLE,        /* 141 */
    T9EVT_CURSOR_RIGHT_FOR_RESPELL,/* 142 */
    T9EVT_CURSOR_LEFT_FOR_RESPELL,/* 143 */
    T9EVT_EXPLICIFY_CURRENT_CHAR_AT_CURSOR,/* 144 */
    T9EVT_EXPLICIFY_NEW_CHAR_AT_CURSOR,/* 145 */
    T9EVT_JGET_OBJECT,          /* 146 */
    T9EVT_JMDB,                 /* 147 - Japanese Manufacturer DB (JMDB) event */
    T9EVT_JWORDCHECK            /* 148 - Check if yomi matches to key sequence */

    /* Language extension event types -- Korean Range from 192-255                */

} T9EVT;


/*----------------------------------------------------------------------------
 *  Define T9 control event types for T9HandleEvent.
 *----------------------------------------------------------------------------*/

typedef enum T9CTRL_e {
    T9CTRLNONE,                      /*  0: No real event.                    */
    T9CTRLAMBIG,                     /*  1: Set T9 smart mode.                */
    T9CTRLSPELL,                     /*  2: Set spell multi-tap mode.         */
    T9CTRL3,                         /*  3: Reserved                          */
    T9CTRL4,                         /*  4: Reserved                          */
    T9CTRL5,                         /*  5: Reserved                          */
    T9CTRL6,                         /*  6: Reserved                          */
    T9CTRLSETSHF,                    /*  7: Set shift state.                  */
    T9CTRLCLRSHF,                    /*  8: Clear shift state.                */
    T9CTRLSETCAP,                    /*  9: Set capitalization lock.          */
    T9CTRLCLRCAP,                    /* 10: Clear capitalization lock.        */
    T9CTRLBEGIN,                     /* 11: Set cursor to beginning of buffer.*/
    T9CTRLEND,                       /* 12: Set cursor to end of buffer.      */
    T9CTRLWRDLFB,                    /* 13: Move cursor left to front of word.*/
    T9CTRLWRDRTE,                    /* 14: Move cursor right to end of word. */
    T9CTRLWRDDEL,                    /* 15: Delete current word.              */
    T9CTRLIMPLEFT,                   /* 16: Import T9 word left of the cursor.*/
    T9CTRLIMPRIGHT,                  /* 17: Import T9 word right of the cursor*/
    T9CTRLWRDRTB,                    /* 18: Move cursor right to beg of word. */
    T9CTRLWRDLFE,                    /* 19: Move cursor left to end of word.  */
    T9CTRLSETEXTSPELL,               /* 20: Set ext spell symb acquisition    */
    T9CTRLCLREXTSPELL,               /* 21: Clear ext spell symb acquisition  */
    T9CTRLCODEVER,                   /* 22: Get the revision of the code      */
    T9CTRLDBVER,                     /* 23: Get the rev. of the current DB    */
    T9CTRLSETUDBWRITEBYOEM,          /* 24: Set writing to UDB done by OEM    */
    T9CTRLCLRUDBWRITEBYOEM,          /* 25: Clear writing to UDB done by OEM  */
    T9CTRL26,                        /* 26: Reserved                          */
    T9CTRL27,                        /* 27: Reserved                          */
    T9CTRLSETUDBCOMPLETION,         /* 28: turn on word completion           */
    T9CTRLCLRUDBCOMPLETION,         /* 29: turn off word completion          */
    T9CTRLSETREORDERWORD,            /* 30: turn on word reordering           */
    T9CTRLCLRREORDERWORD,            /* 31: turn off word reordering           */
    /*
     * Host-Implemented Character Converter callback control, these events
     * allow translation from Unicode to GSM character sets (On-The-Fly
     * mapping)
     */
    T9CTRLSETCHARCONVERT,            /* 32: enable Character Converter        */
                                     /*     callback                          */
    T9CTRLCLRCHARCONVERT,            /* 33: disable Character Converter       */
                                     /*     callack                           */
    T9CTRLSETLDBCOMPLETION,          /* 34: turn on ldb word completion       */
    T9CTRLCLRLDBCOMPLETION,          /* 35: turn of ldb word completion       */
    T9CTRLSETAUTOSWITCHLANG,         /* 36: turn on language autoswitch      */
    T9CTRLCLRAUTOSWITCHLANG,         /* 37: turn off language autoswitch      */
#ifdef T9CDB_IN_BUILD
    T9CTRLSETCDBWRITEBYOEM,          /* 38: Set writing to CDB done by OEM    */
    T9CTRLCLRCDBWRITEBYOEM,          /* 39: Clear writing to CDB done by OEM  */
    T9CTRLCDBRESET,                  /* 40: Reset the CDB                     */
    T9CTRLCDBBREAKCONTEXT,           /* 41: break context                     */
    T9CTRLCDBFILLCONTEXTBUFFER,      /* 42: fill context buffer               */
    T9CTRLCDBGETWORDPREDICTION,      /* 43: get CDB word prediction           */
    T9CTRLSETCDBCOMPLETION,          /* 44: turn on cdb word completion       */
    T9CTRLCLRCDBCOMPLETION,          /* 45: turn off cdb word completion       */
    T9CTRLSETCDBPREDICTION,          /* 46: turn on cdb word prediction       */
    T9CTRLCLRCDBPREDICTION,          /* 47: turn off cdb word prediction       */
#endif
    T9CTRLSETNEXTLOCKING,            /* 48: turn on stem locking              */
    T9CTRLCLRNEXTLOCKING,            /* 49: turn off stem locking             */
    T9CTRLSETLOCKONCURRENTCHARS,     /* 50: set a lock on current character   */
    T9CTRLCLRLOCKONCURRENTCHARS,     /* 51: clear lock on current character   */

    /*
     *  Define T9 control event types for T9EVTUDB.
     */
    T9CTRLUDBANDRDBRESET       = 55, /* 55: Set UDB and RDB to empty.         */
    /*
     * UDB callback event control, these event allow OEM to disable
     * UDB callback - core will always add word to the UDB, or to
     * enable UDB callback - core will always inquires host wether or
     * not to add a word to the UDB.  The default is disable UDB callback.
     */
    T9CTRLSETUDBCALLBACK,            /* 56: Enable UDB callback               */
    T9CTRLCLRUDBCALLBACK,            /* 57: Disable UDB callack               */
    T9CTRLUDBADDWORD,                /* 58: Add a word in UDB.                */
    T9CTRLUDBSCANFORWORDS,           /* 59: Scan text buffer and add words to */
                                     /*     UDB.                              */
    T9CTRLUDBGETFIRSTWORD,           /* 60: Get the first UDB word.           */
    T9CTRLUDBGETNEXTWORD,            /* 61: Get the next UDB word.            */
    T9CTRLUDBGETPREVWORD,            /* 62: Get the previous UDB word.        */
    T9CTRLUDBDELETEWORD,             /* 63: Delete a UDB word.                */
    T9CTRLUDBGETCOUNT,               /* 64: Get the number of the UDB words.  */
    T9CTRL60,                        /* 65: Reserved                          */
    T9CTRL61,                        /* 66: Reserved                          */
    T9CTRLTUDBGETSIZE,               /* 67: Get size of TUDB                  */
    T9CTRLTUDBEXPORT,                /* 68: Export TUDB                       */
    T9CTRLTUDBIMPORT,                /* 69: Import TUDB                       */
    /*
     *  Define T9 control event types for T9EVTLDB.
     */
    T9CTRLRESETSMARTPUNCTTABLE = 70, /* 70: reset the smart punct table with  */
                                     /*     table from the LDB                */
    T9CTRLSETSMARTPUNCTTABLE,        /* 71: set the smart punct table with    */
                                     /*     the table provided with this event*/
    T9CTRLSETEMBEDDEDSMARTPUNCT,     /* 72: set the default embedded smart    */
                                     /*     punct with the one provided with  */
                                     /*     this event                        */
    T9CTRLRESETEMBEDDEDSMARTPUNCT,   /* 73: reset the default embedded smart  */
                                     /*     punct with the one in the LDB     */
    T9CTRLGETMULTITAPTABLE,          /* 74: control event for getting the     */
                                     /*     multi-tap table                   */
    T9CTRLGETLANGID,                 /* 75: Get the language ID from the LDB  */
    /*
     *  Define T9 control event types for T9EVTMDB.
     */
    T9CTRLREGISTERMDB          = 80, /* 80: Register a new MDB                */
    T9CTRLUNREGISTMDB,               /* 81: Remove a MDB                      */
    /*
     *  Define T9 control event types for Chinese.
     */
    T9CTRLKEYDEL               = 90, /* 90: Delete all strokes                */
    T9CTRLSTROKE,                    /* 91: Enter stroke input mode           */
    T9CTRLPHAMBIG,                   /* 92: Enter ambiguous phonetic input    */
                                     /*     mode                              */
    T9CTRLPHMULTI,                   /* 93: Enter multitap phonetic input     */
                                     /*     mode                              */
    T9CTRLSPELLOPT,                  /* 94: Fill spell buff from current keys */
    T9CTRLSETAUTOSPELL,              /* 95: Set auto-spell mode               */
    T9CTRLCLRAUTOSPELL,              /* 96: Clear auto-spell mode             */
    T9CTRLSETPHMTUPDATE,             /* 97: Set multi-tap update always       */
    T9CTRLCLRPHMTUPDATE,             /* 98: Clear multi-tap update always     */
    T9CTRLSETCOMPONENTS,             /* 99: Set enable components             */
    T9CTRLCLRCOMPONENTS,             /* 100: Clear enable components          */
    T9CTRLPHEXPL,                    /* 101: Enter explicit keyboard input    */
                                     /*      mode                             */
    T9CTRL102,                       /* 102: Reserved                         */
    T9CTRLSETFUZZYPINYIN,            /* 103: Set enable fuzzy Pinyin          */
    T9CTRLCLRFUZZYPINYIN,            /* 104: Clear enable fuzzy Pinyin        */
    /* Define T9 control event types for T9EVTCAUDB                           */
    T9CTRLADDCAUDBOBJ         = 110, /* 110: Add one cuadb object             */
    T9CTRLGETCAUDBOBJ,               /* 111: Get one cuadb object             */
    T9CTRL112,                       /* 112: Reserved                         */
    T9CTRL113,                       /* 113: Reserved                         */
    T9CTRLTONEOPT,                   /* 114: Get valid tones 4 current state  */
    T9CTRL115,                       /* 115: Reserved                         */
    T9CTRLSETCUDBSEARCHONLY,         /* 116: in cudblist mode, only search    */
                                     /*      spell from udb                   */
    T9CTRLCLRCUDBSEARCHONLY,         /* 117: clear cudbonly mode              */
    /* Define T9 control event types for T9EVTCAUDB                           */
    T9CTRLSETCAUDBPARAM,             /* 118: set CAUDB ThreshHold parameters  */
    T9CTRLGETCAUDBPARAM,             /* 119: get CAUDB ThreshHold parameters  */
    T9CTRLCAUDBRESET,                /* 120: Set CAUDB to empty               */
    /* Define T9 control event types for T9EVTCUDB                            */
    T9CTRLCUDBPOPULATE,              /* 121: Pre-populate CUDB                */
    T9CTRLCUDBGETDEFAULTACRONYM,     /* 122: Get default CUDB acronym         */
    T9CTRLCUDBGETNEXTOBJ,            /* 123: Get next matching CUDB object    */
    T9CTRLCUDBGETPREVOBJ,            /* 124: Get previous matching CUDB object*/
    T9CTRLCUDBADDOBJ,                /* 125: Add a new CUDB object            */
    T9CTRLCUDBEDITOBJ,               /* 126: Edit an existing CUDB object     */
    T9CTRLCUDBDELOBJ,                /* 127: Delete an existing CUDB object   */
    T9CTRLCUDBUSEOBJ,                /* 128: Use an existing CUDB object      */
    T9CTRLCUDBRESET,                 /* 129: Set CUDB to empty                */

    /* Language extension control events -- Japanese                          */
    T9CTRLSET_JUDB_GC = 165,         /* 165: Enable JUDB garbage collection.  */
    T9CTRLCLR_JUDB_GC,               /* 166: Disable JUDB garbage collection  */
                                     /*      JUDB garbage collection is       */
                                     /*      enabled by default.              */
    T9CTRLREGISTER_JMDB,             /* 167: Register a JMDB */
    T9CTRLUNREGISTER_JMDB,           /* 168: Unregister a JMDB */

    T9CTRLSETREORDERPRNAMES,         /* 169: Enable Person Names Reordering */
    T9CTRLCLRREORDERPRNAMES,         /* 170: Disable Person Names Reordering */
    T9CTRLSET_CONV_SPEC_CHARS,       /* 171: Enable convert special chars. */
    T9CTRLCLR_CONV_SPEC_CHARS,       /* 172: Disable convert special chars. */
     /* Convert special characters that cannot be viewed in Hankaku mode.
        They are converted to the closest character that can be viewed */

    /* Language extension control events -- Korean                                */
    T9CTRLKKEYDEL             = 192, /* 192: Delete all keystrokes            */
    T9CTRLKOREANCHUN,                /* 193: Enter Korean ChunJiIn input mode */
    T9CTRLJAMODEL                    /* 194: Delete ONE LETTER                */


} T9CTRL;


/*----------------------------------------------------------------------------
 *  Define T9 structures used in calls to T9HandleEvent.
 *----------------------------------------------------------------------------*/
typedef struct T9GetCUDB_s {
    T9CTRL      mCtrlID;     /* T9 control value for T9EVTCUDB     */
    T9CCUdbObj  *pTargetObj;  /* Target CUDB object                 */
    T9CCUdbObj  *pResultObj;  /* Object storing the result          */
    const T9U8 *pbBuf;       /* Byte buffer of search criteria     */
    T9U8        bBufBytes;   /* Length of search criteria in bytes */
    T9U8        bOption;     /* CUDB event option                  */
    T9SYMB     *psBuf;       /* CUDB word buffer                   */
} T9CCUdbGet;

#ifdef T9JAPANESE
/* Structure used to fetch info about an entry from the Japanese UDB.
 * If the buffers are too small for the entire yomi or midashigo, the
 * item will be truncated to fit in the buffer.  The buffer lengths
 * will be adjusted to match the length of the contents stored in the
 * buffers. */
typedef struct T9JWUdbGet_s {
    T9UINT   nIndex;         /* 1-based index of entry number */
    T9UINT   nYomiBufLen;    /* length of yomi buffer */
    T9UINT   nMidaBufLen;    /* length of midashigo buffer */
    T9SYMB  *psYomi;        /* buffer to fill with SJIS chars for Yomi */
    T9SYMB  *psMida;        /* buffer to fill with SJIS chars for midashigo */
} T9GetJUDB;

typedef struct T9GetAutoCompJUDB_s {
    T9U8    nIndex;         /* 1-based index of entry number */
    T9U8    uMatchChar;
    T9U8    uKeyMatchCount;
    T9U8    uMatchCount;
    T9U8    uTargetLen;
    T9SYMB* psTarget;
    T9U8     uCandidateNum;
    T9SYMB** psList;
    T9U8**   uListLen;
    T9SYMB** psYomiList;
    T9U8**   uYomiListLen;
} T9GetAutoCompJUDB;

typedef struct T9UpdateAutoCompJUDB_s {
    T9UINT  nYomiBufLen;    /* length of yomi buffer */
    T9UINT  nMidaBufLen;    /* length of midashigo buffer */
    T9SYMB  *psYomi;        /* buffer to fill with SJIS chars for Yomi */
    T9SYMB  *psMida;        /* buffer to fill with SJIS chars for midashigo */
} T9UpdateAutoCompJUDB;

typedef struct T9JMdbInfo_s {
    T9MINOR         mCtrlId;        /* JMDB control value */
    T9JWMDBCALLBACK  T9ReadJMdbData; /* Pointer to JMDB callback function */
} T9JMdbInfo;

#endif

typedef struct T9AdjCursorData_s {
    T9UINT   nCount;         /* Move count                                   */
    T9CA    mType;          /* T9CA_FROMBEG/MOVERIGHT/FROMEND/MOVELEFT      */
} T9AdjCursorData;

typedef struct T9SETLANG_s
{
    T9UINT                      nLdbNum;    /* language number.      */
    T9CCAudbInfo T9FARUDBPOINTER *pCAUdbInfo; /* Chinese CAudb pointer */
} T9SETLANG;

/*
 * Structure used by LDB Event, such as setting the smart punct table,
 * resetting smart punct table, setting embedded smart punct
 * and resetting embedded smart punct
 */
typedef struct T9LDB_s
{
    T9CTRL      mCtrlID;            /* event control ID         */
    T9U8        *pbDataBuf;         /* LDB data buffer          */
    T9SYMB      *psBuf;             /* symbol buffer            */
    T9MINOR     mBufLen;            /* buffer length            */
} T9LDB;

typedef struct T9UDB_s {
    T9CTRL   mCtrlID;       /* UDB control value                            */
    T9UINT   nIndex;         /* 1-based index of entry number                */
    T9UINT   nBufLen;        /* UDB word length                              */
    T9SYMB  *psBuf;         /* UDB word buffer                              */
} T9UDB;

typedef struct T9TUDB_s {
    T9CTRL        mCtrlID;         /* UDB control value                             */
    T9U32         dwTUdbSize;      /* Size of TUDB                                  */
    T9U32         dwExportSize;    /* Size of TUDB                                  */
    T9FARPOINTER  pTUdb;           /* Pointer to TUDB                               */
    T9ReadTUdb_f  T9ReadTUdb;      /* Pointer to function to read from TUDB         */
    T9WriteTUdb_f T9WriteTUdb;     /* Pointer to function to write to TUDB          */
    T9U16         wNextRecord;     /* Next exporting record                         */
    T9U32         dwTotalRecords;  /* Total records exported or imported            */
    T9U32         dwTotalRejected; /* Total rejected records                        */
} T9TUDB;

#ifdef T9CDB_IN_BUILD
typedef struct T9CDB_s {
    T9CTRL   mCtrlID;       /* CDB control value                            */
   T9UINT   nBufLen;        /* CDB word length                              */
    T9SYMB  *psBuf;         /* CDB word buffer                              */
} T9CDB;
#endif

typedef struct T9MDB_s {
    T9CTRL          mCtrlId;        /* MDB control value                        */
    T9UINT           nMdbFence;      /* Selection list start point for MDB words */
    T9U8            bWordComplt;    /* Word completion switch                   */
    T9AWMDBCALLBACK   T9ReadMdbData;  /* Pointer to MDB callback function         */
} T9MDB;

typedef struct T9ChkWord_s {
    T9UINT          nWordLen;     /* Word length     */
    T9SYMB T9FARDATA *psWordBuf;   /* Word to check   */
    T9AuxType T9FARDATA *paKeyBuf;    /* Key buffer      */
} T9ChkWord;

/*
 * structure used to do search on external context
 * nStart:      the 1-based index where the search starts
 * nMatches:    how many matches will be returned.  The host has to allocate
 *              enough memory (at least nMatches + 1) in the response array
 */
typedef struct T9Match_s {
    T9UINT           nStart;
    T9UINT           nMatches;
} T9Match;


typedef struct T9LangFence_s {
    T9U8           bLeadLangFence;
    T9U8           bTrailLangFence;
} T9LangFence;
/*
 * struct for getting multi-tap symbols from the T9 LDB for a given key
 */
typedef struct T9MultiTapTable_s {
    T9CTRL   mCtrlID;       /* T9 control value                               */
    T9KEY    mKey;          /* T9 key                                         */
    T9SYMB  *psPage;        /* To hold a page of symbols                      */
    T9U16   wPage;          /* which page to get, (page start at 1, 2, 3,...) */
    T9U16   wPageSize;      /* the page size                                  */
    T9UINT  nDiacriticLevel;
} T9MultiTapTable;

typedef struct T9Event_s {

    T9EVT mType;               /* T9EventType                                 */

    union {

        T9U8        bChar;     /* T9 char value                               */
        T9KEY       mKeyID;    /* T9 key value                                */
        T9SYMB      sSymID;    /* T9 symbol value                             */
        T9CTRL      mCtrlID;   /* T9 control value                            */
        T9MINOR     mTimerID;  /* T9 timer number                             */
        T9UINT       nValue;    /* T9 function input value                     */
        T9U32       dwLong;    /* T9 function long input value                */
        T9SETLANG   sSetLang;  /* Parameters for switching to another language*/
        T9CCUdbGet   sCUDBData; /* Parameters for CUDB Access                  */
#ifdef T9JAPANESE
        T9GetJUDB   sJUDBData; /* Parameters for JUDB Access                  */
#endif
        T9LDB sLDBData;  /* Parameters for LDB Access                   */
        T9UDB       sUDBData;  /* Parameters for UDB Access                   */
        T9TUDB      sTUdbData;  /* Parameters for UDB Access                   */
#ifdef T9CDB_IN_BUILD
        T9CDB       sCDBData;  /* Parameters for CDB Access                   */
#endif
        T9MDB       sMdbData;  /* Parameters for MDB Access                   */
        T9ChkWord   sChkWord;  /* Parameters for word checking                */
        T9AdjCursorData sAdjData;    /* Parameters to adjust cursor position  */
        T9MultiTapTable sMultiTapTable;
        T9Match     sMatchData;
        T9LangFence sLangFenceData;
#ifdef T9JAPANESE
        T9GetAutoCompJUDB    sGetAutoCompJUDB;
        T9UpdateAutoCompJUDB sUpdateAutoCompJUDB;
        T9JMdbInfo  sJMdbData; /* Parameters for JMDB Access                  */
#endif
    } data;

    union {
        T9SYMB  *pSymbol;  /* Host provided pointers to location for response */
        T9UINT  *pNum;
        T9U8    *pChar;
        T9U16   *pShort;
        T9MINOR *pMinor;
        T9U32   *pLong;
    } response;

} T9Event;

extern T9STATUS T9FARCALL T9HandleEvent(T9AWFieldInfo *pAWFieldInfo, T9Event *pEvent);

#include "t9names2.h"

#if defined(__cplusplus)
}
#endif

#endif

/* ----------------------------------< eof >--------------------------------- */
