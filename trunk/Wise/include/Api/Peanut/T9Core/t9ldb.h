/*******************************************************************************
;*******************************************************************************
;**                                                                           **
;**                    COPYRIGHT 1997-2005 TEGIC COMMUNICATIONS               **
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
;**     FileName: T9LDB.H                                                     **
;**                                                                           **
;**  Description: Linguistics data base access routines header file.          **
;**                                                                           **
;*******************************************************************************
;******************************************************************************/

#ifndef T9LDB_H
#define T9LDB_H    1

/* don't mangle the function name if compile under C++ */
#if defined(__cplusplus)
extern "C" {
#endif

/*----------------------------------------------------------------------------
 *  Define T9 database types and bit masks.
 *----------------------------------------------------------------------------*/
#define T9MAXDBTYPE		9
typedef enum {
    T9LdbAlphabetic            = 0,
    T9LdbKoreanChunJiIn        = 1,
    T9LdbJapaneseKanaNoInflect = 4,
    T9LdbJapaneseFullNoInflect = 5,
    T9LdbJapaneseKanaInflected = 6,
    T9LdbJapaneseFullInflected = 7,
    T9LdbChinese               = 8,
    T9LdbChinesePTI            = 9
} T9LdbTypes;

typedef enum {
	T9LdbAlphMask			  = (1 << T9LdbAlphabetic),
    T9LdbKorChunJiInMask      = (1 << T9LdbKoreanChunJiIn),
    T9LdbJpnKanaNoInflectMask = (1 << T9LdbJapaneseKanaNoInflect),
    T9LdbJpnFullNoInflectMask = (1 << T9LdbJapaneseFullNoInflect),
    T9LdbJpnKanaInflectedMask = (1 << T9LdbJapaneseKanaInflected),
    T9LdbJpnFullInflectedMask = (1 << T9LdbJapaneseFullInflected),
    T9LdbChnMask              = (1 << T9LdbChinese),
    T9LdbChnPTIMask           = (1 << T9LdbChinesePTI)
} T9LdbTypeMasks;


/*----------------------------------------------------------------------------
 *  Define T9 character encoding and endianess.
 *----------------------------------------------------------------------------*/
typedef enum {
	T9Ldb1Byte				= 1,
	T9Ldb2ByteLittleEndian	= 2,
	T9Ldb2ByteBigEndian		= 3
} T9CharEncodingEndian;

/*---------------------------------------------------------------------------
 *
 *   Synopsis: Define smart punctuation rules.
 *   -----------------------------------------------------------------------
 *   PRE_RULE00: No smart punctuation.
 *   -----------------------------------------------------------------------
 *   PRE_RULE01: All smart-punct except "French rule"
 *   -----------------------------------------------------------------------
 *   PRE_RULE02: Allows "French rule", i.e. breaking to an LDB object
 *               which includes the punctuation such as "l'".
 *---------------------------------------------------------------------------*/
#define PRE_RULE00 0
#define PRE_RULE01 1
#define PRE_RULE02 2

/*---------------------------------------------------------------------------
 *      DATABASE CONTROL BIT FLAGS
 *---------------------------------------------------------------------------*/
/* Eliminated: #define ENCRYPT_FLAG               (1 << 0) */
#define NO_SHIFT_FLAG              (1 << 1)
/* Eliminated: #define BIDI_FLAG                  (1 << 2) */
#define HAS_EOW_FLAG               (1 << 4)
/* Eliminated:  #define ENCODE_VALIDKEYS_FLAG      (1 << 5) */
#define ENCODE_DEFAULT_CHILD_FLAG  (1 << 6)
#define ENCODE_DEFAULT_INSTRUCT_FLAG  (1 << 7)

/*----------------------------------------------------------------------------
 *  Define Alpha LDB field offsets
 *----------------------------------------------------------------------------*/
typedef enum {
	T9VERSION_OFFSET    	  = 0x20, /* Offsets into LDB header              */
	T9DBTYPE_OFFSET			  = 0x21, /* Offset of database type              */
	T9CONTROLBITS_OFFSET 	  = 0x22, /* Flag bits for SpellMap size, other   */
	                                  /* future stuff                         */
	T9NUMAMBIGKEYS_OFFSET     = 0x25, /* Offset to number of ambiguous keys   */
	T9COLLATINGSEQN_OFFSET	  = 0x2C, /* Collating sequences                  */
	T9COMPATIDX_OFFSET		  = 0x30, /* Offset to compatibility index        */
	T9CONTENTS_VERSION_OFFSET = 0x32, /* Offset to start of contents version  */
	T9LANGUAGEID_OFFSET 	  = 0x36, /* Offset to primary language ID        */
	T9SYMBOLBYTES_OFFSET 	  = 0x38, /* Offset to symbol bytes               */
	T9SYMBOLCLASS_OFFSET	  = 0x39, /* Offset to symbol class               */
	T9SMARTPUNCTRULE_OFFSET	  = 0x3A, /* Offset to SmartPunct rule            */
	T9OEMIDHI_OFFSET		  = 0x3B, /* Offset to high byte of the OEM ID    */
	T9EMBEDDEDPUNCT_OFFSET	  = 0x3D, /* Offset to EmbeddedPunct              */
	T9SMARTPUNCTKEYS_OFFSET	  = 0x3F, /* Offset to SmartPunctKeys             */
	T9INTEGID_OFFSET		  = 0x41, /* Offset to checksum                   */
	T9CHARMAPADDR_OFFSET	  = 0x45, /* Offset to Character Map address      */
	T9TAPTBLADDR_OFFSET		  = 0x47, /* Offset to multitap table address     */
	T9PUNCTBLADDR_OFFSET	  = 0x52, /* Offset to SmartPunctTable address    */
	T9OEMIDLO_OFFSET		  = 0x54  /* Offset to low byte of the OEM ID     */
} T9LdbFieldOffsets;

/* ------------------------------------------------------------------------ */

#define NO_MULTITAP_SYMBOL     (T9SYMB) 0x1B   /* Error retrieving multitap map symbol */
#define MULTITAP_START_CHAR    (T9SYMB) 0x1B   /* Start char for multitap mode. */

#define MAX_SEL_INSTRS          256      /* 8-bit selection list index */
#define MAX_KEY_SYMS    		16		 /* maximum symbols per key */

typedef struct T9Instruct_s {
    T9U8    bObj;
    T9U8    bSym;
    T9U8    bEOW;
    T9U8    bHalt;
} T9Instruct;

/* Structure for storing version info. */
typedef struct T9VersionInfo_s {
    T9U8    bLDBVer;            /* database version */
    T9U8    bLDBType;           /* database type */
    T9U8    bPrimID;            /* primary language id */
    T9U8    bSecID;             /* secondary language id */
    T9U8    bSymClass;          /* symbol class */
    T9U8    bContMajVer;        /* content major version */
    T9U8    bContMinVer;        /* content minor version */
    T9U8    bConvDev;           /* content deviation */
    T9U8    bHdrDev;            /* header deviation */
} T9VersionInfo;

/*---------------------------------------------------------------------------
 *      Cache control
 *---------------------------------------------------------------------------*/
/* CACHE0 is the cache for the LDB header fields when read in isolated bytes
   in normal operation. */
#define CACHE0 0 /* Mostly just for parallelism w/ CACHE1 */

/* CACHE1 is the cache for contiguous reads, either from the body in normal
   operations or the header on LDB init.  It can be the same as CACHE0 if the
   there's only one cache. */
#if T9NUMCACHE > 1
#define CACHE1 1
#else
#define CACHE1 0
#endif

/* CACHEN(n) is intended to be the cache for the (1-based) nth key pressed,
   i.e. CACHEN(1) would cache the root node, CACHEN(2) would cache the child
   node for the 2nd key, etc.  This is not yet implemented. */
#if T9NUMCACHE > 2
#define CACHEN(n) ((n) >= T9NUMCACHE ? T9NUMCACHE - 1 : n)
#else
#define CACHEN(n) CACHE1
#endif
/*----------------------------------------------------------------------------
 *  Function prototypes
 *----------------------------------------------------------------------------*/
void  T9FARCALL T9_SetDataOffset(T9FieldInfo *pFieldInfo, T9U32 dwOffset, T9MINOR mCacheIndex);
T9U32 T9FARCALL T9_GetDataOffset(T9FieldInfo *pFieldInfo, T9MINOR mCacheIndex);
T9U8  T9FARCALL T9_ReadNibble(T9FieldInfo *pFieldInfo);
T9U8  T9FARCALL T9_ReadByte(T9FieldInfo *pFieldInfo);
T9U16 T9FARCALL T9_ReadWord(T9FieldInfo *pFieldInfo);
T9U32 T9FARCALL T9_ReadDWord(T9FieldInfo *pFieldInfo);
T9U16 T9FARCALL T9_GetBytes(T9FieldInfo *pFieldInfo, T9MINOR mNumBytes,
                            T9UINT nOffset, T9MINOR mEndian);
T9U32 T9FARCALL T9_GetLong(T9FieldInfo *pFieldInfo, T9UINT nOffset);
T9U32 T9FARCALL T9_GetPointer(T9FieldInfo *pFieldInfo,
                         T9UINT        nTree,
                         T9U8         bReadTable);
T9U8 T9FARCALL T9_GetInstruction(T9FieldInfo *pFieldInfo,
                                    T9Instruct  *pInstruct,
                                    T9U32       *pdwMarkOff1,
                                    T9U32       *pdwMarkOff2,
                                    T9U8        bMaxLdbObjects);
void T9FARCALL T9_DecodeOneOrTwoNibbleInstIndex(
    T9FieldInfo *pFieldInfo,
    T9U16 wInstIndex,
    T9Instruct *pInstruct,
    T9U32 *pdwMarkOff1, T9U32 *pdwMarkOff2);
void T9FARCALL T9_SkipToInstrListEnd(T9FieldInfo *pFieldInfo);
T9U16 T9FARCALL T9_GetValidKeys(T9FieldInfo *pFieldInfo);
T9MINOR T9FARCALL T9_IsPunctKey(T9FieldInfo *pFieldInfo,
                                 T9AuxType aKey, T9U8 bLangIndex);
T9U8 T9FARCALL T9_RelSymbolToSymbol(
    T9FieldInfo *pFieldInfo,
    T9AuxType aKey,      T9U8 bRelSymbolNumber,
    T9AuxType aPrevKey,  T9U8 bPrevSymbolNumber);
void T9FARCALL T9_FindLegalListLength(T9FieldInfo *pFieldInfo,
                                 T9UINT       *pnMaxListLength,
                                 T9U8           bMaxLdbObjects);
T9STATUS T9FARCALL T9_InitializeLdb(T9FieldInfo *pFieldInfo,
                                      T9U16 wCoreCompatBase,
                                      T9U16 wCoreCompatOffsetMask);
T9SYMB   T9FARCALL T9_GetMultitapSymbol(T9FieldInfo *pFieldInfo);
T9STATUS T9FARCALL T9_ValidateLDB(T9FieldInfo *pFieldInfo);
T9STATUS T9FARCALL T9_GetLdbVersion(T9FieldInfo *pFieldInfo, T9U8 *pbResponse);
T9MINOR  T9FARCALL T9_GetCharSyntax(T9FieldInfo *pFieldInfo, T9SYMB sSym,
                                    T9U8 *pbSyntaxByte, T9U8 *pbMapShiftOffset,
                                    T9U8 *pbLangIndex);
T9S16    T9FARCALL T9_GetShiftValue(T9FieldInfo *pFieldInfo, T9MINOR mOffset,
                                    T9U8 bLdbInd);

/*---------------------------------------------------------------------------
 * The following are a set of stack empty/fill routines required for
 * supporting the OEM specific C166 CPU environment.  They have very limited stack
 * depth and provide and empty/fill stack routines to create more room.
 *
 * Also, they have a custom multiplication routine required instead of
 * whatever that standard C compiler uses.
 *---------------------------------------------------------------------------*/

#ifdef  OEM_C166

void  T9FARCALL empty_stack(void);
void  T9FARCALL fill_stack(void);
T9U16 T9FARCALL multiplication(T9U16 a, T9U16 b);

#else

#define empty_stack()
#define fill_stack()
#define multiplication(a,b)     ((a)*(b))

#endif

#if defined(__cplusplus)
}
#endif

#endif

/* ----------------------------------< eof >--------------------------------- */
