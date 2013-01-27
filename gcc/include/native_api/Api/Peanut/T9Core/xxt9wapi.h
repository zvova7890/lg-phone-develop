/*******************************************************************************
;*******************************************************************************
;**                                                                           **
;**                  COPYRIGHT 1997-2005 TEGIC COMMUNICATIONS                 **
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
;**     FileName: T9wapi.h                                                    **
;**  Description: This header defines the word level interface to T9.         **
;**                                                                           **
*******************************************************************************/

#ifndef _T9WAPI_
#define _T9WAPI_

#include "t9api.h"
#include "t9names2.h"

/* don't mangle the function name if compile under C++ */
#if defined(__cplusplus)
extern "C" {
#endif

/*----------------------------------------------------------------------------
 *  Define WORD API core version number
 *
 *  String format is defined as "WORD API VMM.mm.bf.om.qa"
 *  Where
 *      MM   = major version number
 *      mm   = minor version number
 *      bf   = bug fix version number
 *      om   = OEM update version number
 *      qa   = QA release version number
 *----------------------------------------------------------------------------*/
#define T9OEMVER      "0"
#define WAPICOREVER "WORD API V0" T9_MAJORVER ".0" T9_MINORVER ".0" T9_PATCHVER ".0" T9OEMVER "   "

/* NOTE:
    THE FOLLOWING TWO DEFINITIONS HAVE BEEN CHANGED TO GET OUT OF THE
    WAY OF T9 KEY DEFINITIONS BUT STILL REMAIN WITHIN A BYTE.

    THIS MOVES US AWAY FROM THE SPEC AS RECEIVED FROM UNWIRED PLANET.
*/
#define T9KEYFLUSH     ((T9SYMB)0x7F)
#define T9FLAGSHIFT    ((T9SYMB)0x80)

#define T9WORDMARKMASK ((T9SYMB)0x20)

#define T9ERR_NONE     ((T9UINT)0x00)
#define T9ERR_DATABASE ((T9UINT)0x01)
#define T9ERR_NOTFOUND ((T9UINT)0x02)
#define T9ERR_FULL     ((T9UINT)0x04)
#define T9ERR_EMPTY    ((T9UINT)0x08)
#define T9ERR_BADKEY   ((T9UINT)0x10)
#define T9ERR_BADCOMMAND   ((T9UINT)0x20)
#define T9ERR_COMMAND  ((T9UINT)0x40)

/* To Set the char output mode */
#define T9WAPI_UCS2    ((T9UINT)0x01)
#define T9WAPI_UTF8    ((T9UINT)0x02)
#define T9WAPI_CONV_CALL ((T9UINT)0x03)

/* = UTF8 Conversion Stuff ========================================= */
typedef unsigned long   UCS4;
typedef unsigned short  UCS2;
typedef unsigned char   UTF8;

#if !defined(T9MAXWORDSIZE) && defined(T9AWMAXWORDSIZE)
#define T9MAXWORDSIZE T9AWMAXWORDSIZE
#endif
#ifdef T9CHINESE
#define T9WCCSPELLBUFMAXSIZE         T9CCSPELLBUFMAXSIZE     /* Size of Chinese spell buffer   */
#define T9WCCKEYBUFMAXSIZE           T9CCKEYBUFMAXSIZE       /* Size of Chinese key buffer     */
#define T9WCCSELECTPAGEMAXSIZE       T9CCSELECTPAGEMAXSIZE   /* Size of Chinese selection page */
#endif

typedef enum T9WMODES_e {
#ifdef T9CHINESE
    T9WCCSTROKE,
    T9WCCPHONETIC,
#endif /* T9CHINESE */
    T9WAWMULTITAP,
    T9WAWAMBIG
} T9WMODES;


typedef enum {
    T9FLUSH_ONLY = 0,         /* flush without saving or marking use */
    T9FLUSH_MARKUSE_ONLY,     /* flush and mark the use of this word without adding to UDB/CDB */
    T9FLUSH_MARKUSE_INTOUDB   /* flush and mark a use of this word and add to udb/cdb */
} T9FLUSHTYPE;

typedef enum {
    T9GETFIRST = 0,                   /* get the first one */
    T9GETCURRENT,                     /* get current one */
    T9GETNEXT,                        /* get next one */
    T9GETPREVIOUS,                    /* get previous one */
    T9GETPREDICTION                   /* get prediction */
} T9GETTYPE;

/* if there is an OEM defined character conversion */
#ifdef T9WAPI_OEM_CONV
extern  T9UINT    (T9FARCALL *pT9WAPIConvCallback)(T9SYMB*, T9UINT, unsigned char*);
extern  T9UINT    (T9FARCALL *pT9WAPIInvConvCallback)(unsigned char*, T9UINT, T9SYMB*);
#endif /* T9WAPI_OEM_CONV */

/*--------------------------------------------------------------------------
 *
 *   Function: T9Init
 *
 *   Synopsis: Word API routine for initialization.  Should FLUSH the buffer.
 *              for Chinese, use T9WInitWithChn()
 *
 *      Input: nDefaultLdb - Default LDB language to use based on T9LDB_***
 *                            values found in T9api.h
 *             pMemUdb     - pointer to RAM shadow copy of UDB (User Database)
 *             wSize       - size of RAM shadow UDB
 *
 *     Return: 1 if initialization successful; 0 otherwise
 *
 *---------------------------------------------------------------------------*/
T9UINT T9FARCALL T9Init(T9UINT                      nDefaultLdb, 
                        T9AWUdbInfo T9FARUDBPOINTER *pMemUdb,
                        T9U16                       wUdbSize);

/*----------------------------------------------------------------------------
 *
 *   Function: T9WAWBreakCdbContext
 *
 *   Synopsis: T9 WordAPI function to break the CDB word
 *              prediction context
 *
 *      Input: NONE
 *
 *     Return: T9STATNONE on success, T9STATERR on failure.
 *
 *------------------------------------------------------------------------------*/
T9STATUS T9FARCALL T9WAWBreakCdbContext(void);

/*----------------------------------------------------------------------------
 *
 *   Function: T9WAWFlushBuffer
 *
 *   Synopsis: T9 WordAPI function to flush the T9 buffer without
 *              saving the word in UDB or adding to the word prediction context
 *
 *      Input: nFlushType - Save the buffer contents to UDB/CDB/RDB?
 *
 *     Return: T9STATNONE on success, T9STATERR on failure.
 *
 *------------------------------------------------------------------------------*/
T9STATUS T9FARCALL T9WAWFlushBuffer(T9FLUSHTYPE nFlushType);

#ifdef T9CDB_IN_BUILD
/*---------------------------------------------------------------------------
 *
 *   Function: T9WAWActivateCdb
 *
 *   Synopsis: initialize CDB.
 *
 *      Input: pMemUdb     - Pointer to RAM copy of UDB (User Database)
 *             wSize       - Size of UDB
 *
 *     Return: T9STATNONE if successful, T9STATUS type otherwise.
 *
 *---------------------------------------------------------------------------*/
T9STATUS T9FARCALL T9WAWActivateCdb(T9AWCdbInfo T9FARUDBPOINTER *pMemCdb,
                                     T9U16                       wCdbSize);
#endif
/*---------------------------------------------------------------------------
 *
 *   Function: T9CharOutMode
 *
 *   Synopsis: Sets T9 WAPI output character mode.
 *
 *      Input: nCharOutputMode - Sets character output conversion mode for multi-byte
 *                        character sets (UCS2, UTF8, or CONV_CALL).
 *
 *     Return: 1 if successful; 0 otherwise
 *
 *---------------------------------------------------------------------------*/
T9UINT T9FARCALL T9CharOutMode(T9UINT nCharOutputMode);

/*---------------------------------------------------------------------------
 *
 *   Function: T9SetDatabase
 *
 *   Synopsis: Word API routine to change the current LDB.
 *             NOTE: Changing LDBs FLUSHES THE BUFFER
 *
 *      Input: nDatabase - New LDB language to use based on T9LDB_*
 *                          values found in T9api.h
 *
 *     Return: 1 if initialization successful; 0 otherwise
 *
 *---------------------------------------------------------------------------*/
T9UINT T9FARCALL T9SetDatabase(T9UINT nDatabase);

/*---------------------------------------------------------------------------
 *
 *   Function: T9AddKey
 *
 *   Synopsis: Word API routine to add a new ambiguous key to the current
 *                T9 word
 *
 *      Input: sKey = valid T9 key (T9KEYAMBIG1-9, T9KEYCLEAR, T9KEYFLUSH)
 *
 *     Return: Any of the T9ERR_* values:
 *             T9ERR_NONE if key added successfully
 *             T9ERR_DATABASE if LDB not initialized correctly
 *             T9ERR_NOTFOUND if added key does not produce an LDB/UDB word
 *             T9ERR_FULL if adding key causes the current word to exceed max
 *             T9ERR_EMPTY if CLEAR key sent when no current word
 *             T9ERR_BADKEY if invalid T9 key sent
 *
 *---------------------------------------------------------------------------*/
T9UINT T9FARCALL T9AddKey(T9SYMB sKey);

/*----------------------------------------------------------------------------
 *
 *   Function: T9WAWSetWordCompletion
 *
 *   Synopsis: turn on word completion
 *
 *      Input: NONE
 *
 *     Return: T9ERR_NONE on success, T9ERR_COMMAND on failure.
 *
 *------------------------------------------------------------------------------*/
T9UINT T9FARCALL T9WAWSetWordCompletion(void);

/*----------------------------------------------------------------------------
 *
 *   Function: T9WAWClrWordCompletion
 *
 *   Synopsis: turn off word completion
 *
 *      Input: NONE
 *
 *     Return: T9ERR_NONE on success, T9ERR_COMMAND on failure.
 *
 *------------------------------------------------------------------------------*/
T9UINT T9FARCALL T9WAWClrWordCompletion(void);

/*----------------------------------------------------------------------------
 *
 *   Function: T9WAWGetWordLen
 *
 *   Synopsis: Return word length in characters
 *
 *      Input: void
 *
 *     Return: word length in characters.
 *
 *------------------------------------------------------------------------------*/
T9UINT T9FARCALL T9WAWGetWordLen(void);

/*----------------------------------------------------------------------------
 *
 *   Function: T9WAWGetComplLen
 *
 *   Synopsis: Return completion length in characters
 *
 *      Input: void
 *
 *     Return: word completion in characters.
 *
 *------------------------------------------------------------------------------*/
T9UINT T9FARCALL T9WAWGetComplLen(void);

/*----------------------------------------------------------------------------
*   Function: T9WAWGetWordLenInBytes
*
*   Synopsis: Return word length in bytes
*
*      Input: void
*
*     Return: word length in bytes.
------------------------------------------------------------------------------*/
T9UINT T9FARCALL T9WAWGetWordLenInBytes(void);

/*----------------------------------------------------------------------------
*   Function: T9WAWGetComplLenInBytes
*
*   Synopsis: Return completion length in bytes
*
*      Input: void
*
*     Return: completion length in bytes.
------------------------------------------------------------------------------*/
T9UINT T9FARCALL T9WAWGetComplLenInBytes(void);


/*---------------------------------------------------------------------------
 *
 *   Function: T9WAWGetWord
 *
 *   Synopsis: Word API routine to get the word from the T9 selection
 *                list for the current key sequence
 *
 *      Input: eGetType - enum type of word to get (first, current, next, or previous)
 *             psDestBuf - pointer to buffer to copy the word into
 *             pnBytesWritten - pointer to Length of the destination buffer in bytes
 *
 *     Return: T9STATNONE if successful, T9STATERROR else
 *
 *---------------------------------------------------------------------------*/
T9STATUS T9FARCALL T9WAWGetWord(T9GETTYPE eGetType, T9SYMB *psDestBuf,
                                T9UINT *pnBytesWritten);

/*---------------------------------------------------------------------------
 *
 *   Function: T9GetFirstWord
 *
 *   Synopsis: Word API routine to get the first word from the T9 selection
 *                list for the current key sequence
 *
 *      Input: pDest - pointer to buffer to copy the word into
 *
 *     Return: 0 on failure (no LDB, no word found, no current word, etc)
 *              otherwise bytes in word returned or number of characters for UCS2
 *
 *---------------------------------------------------------------------------*/
T9UINT T9FARCALL T9GetFirstWord(T9SYMB *psDest);

/*****************************************************************
T9GetNextWord - gets the next relative word from the T9 selection list
Input: psDest - pointer to buffer to copy the word into
Output: 0 on failure (no LDB, no word found, no current word, etc)
        otherwise size of word returned
NOTE: This routine will also return 0 if called to get the NEXT
    word after the selection list is exhausted
*****************************************************************/
T9UINT T9FARCALL T9GetNextWord(T9SYMB *psDest);

/*---------------------------------------------------------------------------
 *
 *   Function: T9GetNextWord
 *
 *   Synopsis: Word API routine to get the next word from the T9 selection
 *                list for the current key sequence.
 *
 *      Input: pDest - pointer to buffer to copy the word into
 *
 *     Return: 0 on failure (no LDB, no word found, no current word, etc)
 *              otherwise size of word returned
 *              NOTE: This routine will also return 0 if called to get the     **
 *              NEXT word after the selection list is exhausted
 *
 *---------------------------------------------------------------------------*/
T9SYMB T9FARCALL T9GetAmbigKey(T9SYMB sChar);

/*---------------------------------------------------------------------------
 *
 *   Function: T9AddWords
 *
 *   Synopsis: Word API routine to processes an ascii text buffer for new
 *               words that need to be added to the User Database (UDB)
 *
 *      Input: psBuffer = pointer to text buffer to be processed
 *             nLength = length of passed buffer (to last valid character)
 *
 *     Return: 0 if no UDB, no buffer passed, DB not initialized or buffer
 *               length 0;
 *             1 otherwise (meaning buffer processed, whether words
 *              were actually added to the UDB or not)
 *
 *---------------------------------------------------------------------------*/
T9UINT T9FARCALL T9AddWords(T9SYMB *psBuffer, T9UINT nLength);

/*---------------------------------------------------------------------------
 *
 *   Function: T9Terminate
 *
 *   Synopsis: Word API routine to terminate T9
 *
 *      Input: NONE
 *
 *     Return: 1 if successful
 *
 *---------------------------------------------------------------------------*/
T9UINT T9FARCALL T9Terminate(void);

/*---------------------------------------------------------------------------
 *
 *   Function: T9ChangeSequence
 *
 *   Synopsis: Changes the switchover point in the selection list from which
 *             LDB words are listed before UDB words. If there is a current
 *             T9 word, it re-selects the word to update the object number
 *
 *      Input: value to set the udb fence
 *
 *     Return: 1 if successful
 *
 *---------------------------------------------------------------------------*/
T9UINT T9FARCALL T9ChangeSequence(T9UINT nValue);

/*---------------------------------------------------------------------------
 *
 *   Function: T9PresetWord
 *
 *   Synopsis: Word API routine to process a new word and try to bring it
 *             into context. The current context is flushed; the new text is
 *             traversed to ensure that the symbols correspond to ambiguous
 *             keys. The database is then checked to see if the word exists
 *
 *      Input: psBuffer = pointer to text buffer with word to be processed
 *             nLength = length of word  ( < than T9AWMAXWORDSIZE)
 *
 *     Return: Any of these T9ERR_* values:
 *             T9ERR_NONE if word pulled into context successfully
 *             T9ERR_DATABASE if LDB not initialized
 *             T9ERR_EMPTY if passed word length is 0
 *             T9ERR_NOTFOUND if input word not an LDB/UDB word
 *             T9ERR_FULL if word length too long
 *             T9ERR_BADKEY if nonambiguous symbol in text
 *
 *---------------------------------------------------------------------------*/
T9UINT T9FARCALL T9PresetWord(T9SYMB *psBuffer, T9UINT nLength);

/*---------------------------------------------------------------------------
 *
 *   Function: T9WAWAddLanguage
 *
 *   Synopsis: used to add a supplementary language to bilingual T9 (to 
 *             set the principal language, use T9SetDatabase()
 *
 *      Input: nLdbNum = Language number to add as supplementatry language
 *
 *     Return: T9STATNONE if successful, else a T9STATUS error
 *
 *---------------------------------------------------------------------------*/
T9STATUS T9FARCALL T9WAWAddLanguage(T9UINT nLdbNum);

/*---------------------------------------------------------------------------
 *
 *   Function: T9WAWRemoveLanguage
 *
 *   Synopsis: used to remove a supplementary language from bilingual T9
 *
 *      Input: nLdbNum = supplementary Language number to remove (0 removes default)
 *
 *     Return: T9STATNONE if successful, else a T9STATUS error
 *
 *---------------------------------------------------------------------------*/
T9STATUS T9FARCALL T9WAWRemoveLanguage(T9UINT nLdbNum);

/*---------------------------------------------------------------------------
 *
 *   Function: T9WAWSetLangFences
 *
 *   Synopsis: set the bilingual language fences.
 *
 *      Input: bLangFenceLead - how many Lead language words should appear
 *             in the selection list before Trailing language words are shown
 *             bLangFenceTrail - how many Trailing language words should appear
 *             in the selection list before the remaining Lead words are shown
 *
 *     Return: T9STATNONE if successful, else a T9STATUS error
 *
 *---------------------------------------------------------------------------*/
T9STATUS T9FARCALL T9WAWSetLangFences(T9U8 bLangFenceLead,
                                    T9U8 bLangFenceTrail);

/*---------------------------------------------------------------------------
 *
 *   Function: T9WAWSwitchLeadLang
 *
 *   Synopsis: switches the Lead and Trailing languages.
 *
 *      Input: nLdbNum - Ldb number to make the new Lead Language
 *             (0 sets Lead to the first supplementary language)
 *
 *     Return: T9STATNONE if successful, else a T9STATUS error
 *
 *---------------------------------------------------------------------------*/
T9STATUS T9FARCALL T9WAWSwitchLeadLang(T9UINT nLdbNum);

/*---------------------------------------------------------------------------
 *
 *   Function: T9WAWSetAutoswitchLang
 *
 *   Synopsis: turn on bilingual autoswitch feature.
 *
 *      Input: NONE
 *
 *     Return: T9STATNONE if successful, else a T9STATUS error
 *
 *---------------------------------------------------------------------------*/
T9STATUS T9FARCALL T9WAWSetAutoswitchLang(void);

/*---------------------------------------------------------------------------
 *
 *   Function: T9WAWClrAutoswitchLang
 *
 *   Synopsis: turn off bilingual autoswitch feature.
 *
 *      Input: NONE
 *
 *     Return: T9STATNONE if successful, else a T9STATUS error
 *
 *---------------------------------------------------------------------------*/
T9STATUS T9FARCALL T9WAWClrAutoswitchLang(void);

/*---------------------------------------------------------------------------
 *
 *   Function: T9WAWGetActiveLangIndex
 *
 *   Synopsis: return the active language index
 *
 *      Input: NONE
 *
 *     Return: Active language index
 *
 *---------------------------------------------------------------------------*/
T9U8 T9FARCALL T9WAWGetActiveLangIndex();

/*---------------------------------------------------------------------------
 *
 *   Function: T9WAWGetAutoswitchLangIndex
 *
 *   Synopsis: return the autoswitch language index
 *
 *      Input: NONE
 *
 *     Return: Autoswitch language index
 *
 *---------------------------------------------------------------------------*/
T9U8 T9FARCALL T9WAWGetAutoswitchLangIndex();

/*---------------------------------------------------------------------------
 *
 *   Function: T9WAWGetSupplLangID
 *
 *   Synopsis: Get supplementary language ID
 *
 *      Input: NONE
 *
 *     Return: Supplementary Language ID
 *
 *---------------------------------------------------------------------------*/
T9UINT T9FARCALL T9WAWGetSupplLangID();

/*----------------------------------------------------------------------------
 *
 *   Function: ConvertUCS2toUTF8
 *
 *   Synopsis: Converting Unicode to UTF8
 *
 *      Input: src  - Unicode buffer to convert
 *             len  - the length of the Unicode buffer
 *             dest - UTF8 receving buffer
 *
 *     Return: number of bytes in the dest buffer
 *
 *------------------------------------------------------------------------------*/
T9UINT T9FARCALL ConvertUCS2toUTF8(T9SYMB*          src, 
                                   int              len,
                                   unsigned char*   dest);

/*----------------------------------------------------------------------------
 *
 *   Function: ConvertUTF8toUCS2
 *
 *   Synopsis: Converting UTF8 to Unicode
 *
 *      Input: sourceStart  - UTF8 buffer to convert
 *             len  - the length of the UTF8 buffer
 *             targetStart - Unicode receiving buffer
 *
 *     Return: number of bytes written to target
 *
 *------------------------------------------------------------------------------*/
T9UINT T9FARCALL ConvertUTF8toUCS2(unsigned char*   src, 
                                   int              len,
                                   T9SYMB*          dest);

/*----------------------------------------------------------------------------
 *
 *   Function: T9WConvertUCS2toUTF8
 *
 *   Synopsis: Converting Unicode to UTF8
 *
 *      Input: psSourceStart  - Unicode buffer to convert
 *             nLen  - the number of characters in the Unicode buffer
 *             pucTargetStart - UTF8 receving buffer
 *             pnBytesWritten - pointer to the number of bytes that will be returned
 *
 *     Return: T9STATNONE if successful, error type if problems
 *
 *------------------------------------------------------------------------------*/
T9STATUS T9FARCALL T9WConvertUCS2toUTF8(T9SYMB*         psSourceStart, 
                                        int             nLen,
                                        unsigned char*  pucTargetStart, 
                                        T9UINT*         pnBytesWritten);

/*----------------------------------------------------------------------------
 *
 *   Function: T9WConvertUTF8toUCS2
 *
 *   Synopsis: Converting UTF8 to Unicode
 *
 *      Input: pucSourceStart  - UTF8 buffer to convert
 *             nLen  - the number of characters that are passed in
 *             psTargetStart - Unicode receiving buffer
 *
 *     Output: pnUTF8bytesRead - pointer to the number of bytes that are read
 *
 *     Return: T9STATNONE if successful, error type if problems
 *
 *------------------------------------------------------------------------------*/
T9STATUS T9FARCALL T9WConvertUTF8toUCS2(unsigned char*  pucSourceStart, 
                                        int             nLen,
                                        T9SYMB*         psTargetStart, 
                                        T9UINT*         pnUTF8bytesRead);

/*---------------------------------------------------------------------------
 *   Function: T9WSetMode
 *
 *   Synopsis: Word API routine to switch T9 input among different modes.
 *
 *      Input: Pass in one of the enum value ALPHAAMBIG, ALPHAEXPL, CHNSTROKE,
 *             or CHNPHONETIC.
 *
 *     Return: T9ERR_NONE (0) if sets mode successfully, otherwise returns
 *             non-zero value. 
 *---------------------------------------------------------------------------*/
T9UINT T9FARCALL T9WSetMode(T9WMODES eModeID);

/*---------------------------------------------------------------------------
 *
 *   Function: T9WGetLanguage
 *
 *   Synopsis: Get current active language
 *
 *      Input: NONE
 *
 *     Return: Language ID
 *
 *---------------------------------------------------------------------------*/
T9UINT T9FARCALL T9WGetLanguage(void);

/*---------------------------------------------------------------------------
 *
 *   Function: T9WAPITimeout
 *
 *   Synopsis: Send T9 a timeout event.
 *
 *      Input: int iTimerID - ID of timer that expired
 *
 *     Return: T9ERR_NONE (0) if successful, otherwise returns
 *             non-zero value.
 *
 *---------------------------------------------------------------------------*/
T9UINT  T9FARCALL T9WAPITimeout(int iTimerID);

/*------------------------------------------------------------------------
 *
 *  Function   : T9HandleRequest
 *  Synopsis   : How T9 asks for services, such as timers to expire. 
 *                    
 *
 *  Input      : pFieldInfo - T9 Fieldinfo structure
 *                    pRequest   - Type of request T9 is making
 *
 *  Return      : T9STATNONE if successful, otherwise a T9STATUS error
 *
 *-----------------------------------------------------------------------*/
extern T9STATUS T9FARCALL T9HandleRequest(T9FieldInfo *pFieldInfo, T9Request *pRequest);

/*---------------------------------------------------------------------------
 *
 *  Function: T9ReadLdbData
 *                                 
 *  Synopsis: Callback from T9Core to access language data base
 *                                           
 *     Input: T9FieldInfo *pFieldInfo -- Field info struct that holds database number
 *            T9U32 dwOffset - byte offset from LDB start to read from
 *            T9FARPOINTER *ppbDst - Ptr to a ptr to the data cache.
 *            T9U32 *pdwStart - Ptr to offset of start of data.
 *            T9NUM nSize    - number of bytes to read
 * 
 *    Return: Number of bytes transfered
 *                                                                            
 *---------------------------------------------------------------------------*/
extern T9U32 T9FARCALL T9ReadLdbData(T9FieldInfo *pFieldInfo, T9U32 dwOffset, T9FARPOINTER *ppbDst, T9U32 *pdwStart, T9UINT nSize, T9MINOR mCacheIndex);

#ifdef T9CHINESE 
/*---------------------------------------------------------------------------
 *   Function: T9WInitWithChn
 *
 *   Synopsis: Word API routine for initialization. This is used when Chinese
 *             T9 is compiled in.
 *
 *      Input: nDefaultLdb          - Default LDB language to use based on T9LDB_*
 *                                    values found in T9api.h
 *             pMemUdb              - pointer to RAM shadow copy of UDB (User Database)
 *             wSize                - size of RAM shadow UDB
 *             nSelectPageMax       - Maximum number of characters on each selection
 *                                    page
 *             pbCudbInfo           - Pointer to Chinese UDB buffer
 *             wCudbSize            - Chinese UDB buffer size in bytes
 *             pbSimpCaudbPointer   - Pointer to Simplified Chinese AUDB buffer
 *             wSimpCaudbSize       - Simplified Chinese AUDB buffer size in bytes
 *             pbTradCaudbPointer   - Pointer to Traditional Chinese AUDB buffer
 *             wTradCaudbSize       - Traditional Chinese AUDB buffer size in bytes
 *
 *     Return: 1 if initialization successful; 0 otherwise
 *---------------------------------------------------------------------------*/
T9UINT T9FARCALL T9WInitWithChn(T9UINT                      nDefaultLdb, 
                                T9AWUdbInfo T9FARUDBPOINTER *pMemUdb, 
                                T9U16                       wSize,
                                T9UINT                      nSelectPageMax,
                                T9U8                        *pbCudbInfo,
                                T9U16                       wCudbSize,
                                T9U8                        *pbSimpCaudbPointer,
                                T9U16                       wSimpCaudbSize,
                                T9U8                        *pbTradCaudbPointer,
                                T9U16                       wTradCaudbSize);
/*---------------------------------------------------------------------------
 *
 *   Function: T9WCCGetKeyBufLen
 *
 *   Synopsis: Get Chinese key buffer length
 *
 *      Input: NONE
 *
 *     Return: Key buffer length
 *
 *---------------------------------------------------------------------------*/
T9UINT T9FARCALL T9WCCGetKeyBufLen(void);

/*---------------------------------------------------------------------------
 *
 *   Function: T9WCCGetKeyBuf
 *
 *   Synopsis: Get Chinese key buffer
 *
 *      Input: NONE
 *
 *     Return: Pointer to key buffer.
 *
 *---------------------------------------------------------------------------*/
T9U8* T9FARCALL T9WCCGetKeyBuf(void);

/*---------------------------------------------------------------------------
 *
 *   Function: T9WCCGetSelectPage
 *
 *   Synopsis: Get Chinese selection page buffer
 *
 *      Input: NONE
 *
 *     Return: Pointer to selection page buffer.
 *
 *---------------------------------------------------------------------------*/
T9U16* T9FARCALL T9WCCGetSelectPage(void);

/*---------------------------------------------------------------------------
 *
 *   Function: T9WCCGetSelectPageNum
 *
 *   Synopsis: Get Chinese selection page number
 *
 *      Input: NONE
 *
 *     Return: Selection page number.
 *
 *---------------------------------------------------------------------------*/
T9UINT T9FARCALL T9WCCGetSelectPageNum(void);

/*---------------------------------------------------------------------------
 *
 *   Function: T9WCCGetSelectPageLen
 *
 *   Synopsis: Get length of the selection page
 *
 *      Input: NONE
 *
 *     Return: Selection page length.
 *
 *---------------------------------------------------------------------------*/
T9UINT T9FARCALL T9WCCGetSelectPageLen(void);

/*---------------------------------------------------------------------------
 *
 *   Function: T9WCCHasMoreSelectPage
 *
 *   Synopsis: Detect if there is more selection page
 *
 *      Input: None
 *
 *     Return: 1 if there is more page; 0 if not
 *
 *---------------------------------------------------------------------------*/
T9UINT T9FARCALL T9WCCHasMoreSelectPage(void);

/*---------------------------------------------------------------------------
 *
 *   Function: T9WCCGetSpellCode
 *
 *   Synopsis: Get Chinese spell code
 *
 *      Input: NONE
 *
 *     Return: Chinese spell code.
 *
 *---------------------------------------------------------------------------*/
T9U8 T9FARCALL T9WCCGetSpellCode(void);

/*---------------------------------------------------------------------------
 *
 *   Function: T9WCCGetSpellBuf
 *
 *   Synopsis: Get Chinese spell buffer
 *
 *      Input: NONE
 *
 *     Return: Pointer to Chinese spell buffer.
 *
 *---------------------------------------------------------------------------*/
T9U8* T9FARCALL T9WCCGetSpellBuf(void);

/*---------------------------------------------------------------------------
 *
 *   Function: T9WCCUpdateSpellBuffer
 *
 *   Synopsis: Re-generate phonetic spellings that correspond to
 *                    the current key buffer and update the spell buffer.
 *
 *      Input: NONE
 *
 *     Return: T9ERR_NONE (0) if successful, otherwise returns
 *                    non-zero value.
 *
 *---------------------------------------------------------------------------*/
T9UINT T9FARCALL T9WCCUpdateSpellBuffer(void);

/*---------------------------------------------------------------------------
 *
 *   Function: T9WCCSetSpell
 *
 *   Synopsis: Set Chinese phonetic spell code
 *
 *      Input: nSpellCode = Spell code.
 *
 *     Return: T9ERR_NONE (0) if successfully, otherwise returns
 *             non-zero value.
 *
 *---------------------------------------------------------------------------*/
T9UINT T9FARCALL T9WCCSetSpell(T9UINT nSpellCode);

/*---------------------------------------------------------------------------
 *
 *   Function: T9WCCGetSpellCount
 *
 *   Synopsis: Get total number of spells that matching to the keys.
 *
 *      Input: NONE
 *
 *     Return: Spell count
 *
 *---------------------------------------------------------------------------*/
T9UINT T9FARCALL T9WCCGetSpellCount(void);

/*---------------------------------------------------------------------------
 *
 *   Function: T9WCCGetLdbSpellCount
 *
 *   Synopsis: Get total number of LDB spells that matching to the keys.
 *
 *      Input: NONE
 *
 *     Return: LDB spell count.
 *
 *---------------------------------------------------------------------------*/
T9UINT T9FARCALL T9WCCGetLdbSpellCount(void);

/*------------------------------------------------------------------------
 *
 *  Function: T9WCCGetTone
 *
 *  Synopsis: Get Chinese tone
 *
 *  Pass    : NONE
 *
 *  Return  : Chinese tone
 *
 *-----------------------------------------------------------------------*/
T9U8 T9FARCALL T9WCCGetTone(void);

/*---------------------------------------------------------------------------
 *
 *   Function: T9WCCSetTone
 *
 *   Synopsis: Set Chinese phonetic tone
 *
 *      Input: mKeyID   = Tone code 1 - 5.
 *
 *     Return: T9ERR_NONE (0) if successfully, otherwise returns
 *             non-zero value.
 *
 *---------------------------------------------------------------------------*/
T9UINT T9FARCALL T9WCCSetTone(T9MINOR mKeyID);

/*---------------------------------------------------------------------------
 *
 *   Function: T9WCCGetToneOptions
 *
 *   Synopsis: Get Chinese phonetic valid tones for the current spell
 *
 *      Input: nValidTones = Return value on the valid tones
 *
 *     Return: T9ERR_NONE (0) if successfully, otherwise returns
 *             non-zero value.
 *
 *---------------------------------------------------------------------------*/
T9UINT T9FARCALL T9WCCGetToneOptions(T9UINT *pnValidTones);

/*---------------------------------------------------------------------------
 *
 *   Function: T9WCCFlushContext
 *
 *   Synopsis: Clears the current context
 *
 *      Input: NONE
 *
 *     Return: T9ERR_NONE (0) if successful, otherwise returns
 *             non-zero value.
 *
 *---------------------------------------------------------------------------*/
T9UINT T9FARCALL T9WCCFlushContext(void);

/*---------------------------------------------------------------------------
 *
 *   Function: T9WCCSetContext
 *
 *   Synopsis: Adds an explicit character (letter, symbol, or number) to
 *             the text buffer so that T9 generates the selection page based
 *             on context.
 *
 *      Input: sExplSym = Character-code value for the explicit character to
 *                        be added.
 *
 *     Return: T9ERR_NONE (0) if successful, otherwise returns
 *             non-zero value.
 *
 *---------------------------------------------------------------------------*/
T9UINT T9FARCALL T9WCCSetContext(T9SYMB sExplSym);

/*---------------------------------------------------------------------------
 *
 *   Function: T9WCCSetPhraseCompFence
 *
 *   Synopsis: Set Chinese phrase completion fence
 *
 *      Input: pCCFieldInfo   = Pointer to field information structure.
 *
 *     Return: T9ERR_NONE (0) if successfully, otherwise returns
 *             non-zero value.
 *
 *---------------------------------------------------------------------------*/
T9UINT T9FARCALL T9WCCSetPhraseCompFence(T9UINT nFence);

/*---------------------------------------------------------------------------
 *
 *   Function: T9WCCDeleteAllKeys
 *
 *   Synopsis: Delete all key strokes in the key buffer
 *
 *      Input: None
 *
 *     Return: T9ERR_NONE (0) if successful, otherwise returns
 *             non-zero value.
 *
 *---------------------------------------------------------------------------*/
T9UINT T9FARCALL T9WCCDeleteAllKeys(void);

/*---------------------------------------------------------------------------
 *   Function: T9WCCAddKey
 *
 *   Synopsis: Chinese word API routine to add a new ambiguous key
 *
 *      Input: sKey = valid T9 key (T9KEYAMBIG1-9, etc.)
 *
 *     Return: Any of the T9ERR_* values:
 *             T9ERR_NONE if key added successfully
 *             T9ERR_DATABASE if LDB not initialized correctly
 *             T9ERR_NOTFOUND if added key does not produce an LDB/UDB word
 *             T9ERR_FULL if adding key causes the current word to exceed max
 *             T9ERR_EMPTY if CLEAR key sent when no current word
 *             T9ERR_BADKEY if invalid T9 key sent
 *---------------------------------------------------------------------------*/
T9UINT T9FARCALL T9WCCAddKey(T9SYMB sKey);

/*---------------------------------------------------------------------------
 *
 *  Function: T9CCLoadLdb
 *
 *  Synopsis: Callback from T9Core to load the Chinese language database
 *
 *     Input: pCCFieldInfo   -- T9 Chinese Fieldinfo structure
 *            pT9CCLdbHeader -- Pointer to the buffer that the callback
 *                              function loads the LDB data to.
 *
 *    Return: T9STATNONE if the loading succeeds;
 *            T9STATLOADLDBFAIL if the language ID in the T9 FieldInfo
 *            structure is not valid.
 *
 *---------------------------------------------------------------------------*/
extern T9STATUS T9FARCALL T9CCLoadLdb(T9CCFieldInfo *pCCFieldInfo, T9ChineseData T9FARDATA *pT9CCLdbHeader);

#endif /* T9CHINESE */

#ifdef T9CDB_IN_BUILD
T9UINT T9FARCALL T9PresetContextBuffer(T9SYMB *psBuffer, T9UINT nLength);
#endif


/* End don't mangle the function name if compile under C++ */
#if defined(__cplusplus)
    }
#endif

#endif /* _T9WAPI_ */

/* ----------------------------------< eof >--------------------------------- */
