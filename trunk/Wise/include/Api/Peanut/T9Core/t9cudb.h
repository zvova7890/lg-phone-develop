/*******************************************************************************
********************************************************************************

                    COPYRIGHT 1999-2003 TEGIC COMMUNICATIONS

                TEGIC COMMUNICATIONS PROPRIETARY INFORMATION

     This software is supplied under the terms of a license agreement
     or non-disclosure agreement with Tegic Communications and may not
     be copied or disclosed except in accordance with the terms of that
     agreement.

********************************************************************************

     File Name:   t9cudb.h

     Description: Header file for Chinese User Database module


********************************************************************************
********************************************************************************/

#ifndef T9CUDB_H
#define T9CUDB_H

/* don't mangle the function name if compile under C++ */
#if defined(__cplusplus)
extern "C" {
#endif

/* Maximum bytes that a CUDB entry occupies, including overheads */
#define CUDB_ENTRY_MAXSIZE  (4 + (T9CCUDBPHRASEMAXSIZE << (T9SYMBOLWIDTH - 1)) + T9CCUDBACRONYMMAXSIZE)

/* towards older/newer entries */
#define CUDB_SEARCH_OLDER       ((T9U8)0x00)
#define CUDB_SEARCH_NEWER       ((T9U8)0x80)

/* do partial/exact match */
#define CUDB_MATCH_EXACT        ((T9U8)0x00)
#define CUDB_MATCH_PARTIAL      ((T9U8)0x40)

/* get which part of the CUDB entry */
#define CUDB_GET_SIZE           ((T9U8)0x00)
#define CUDB_GET_PHRASE         ((T9U8)0x20)
#define CUDB_GET_ACRONYM        ((T9U8)0x10)

#define CUDB_NO_ADD_TEXT        ((T9U8)0x00)
#define CUDB_ADD_TEXT           ((T9U8)0x01)

/* length of default CUDB acronym */
#define CUDB_ACRONYM_DEFAULTSIZE          5

#define T9MIN(x,y)  (((x) < (y)) ? (x) : (y))

/* The following definitions relate to the T9CCUdbInfo structure
 * defined in the t9ccapi.h file. */

/* Macro to get cudb data area pointer */
#define T9CudbData(cudb) ((T9U8 T9FARUDBPOINTER*)(cudb)->sDataArea)

/* Macro to get pointer to the end of cudb */
#define T9CudbEnd(cudb) ((T9U8 T9FARUDBPOINTER*)(cudb) + (cudb)->wDataSize)

/* Macro to get size in bytes of the cudb header area */
#define T9CudbHeaderBytes(cudb)    \
            ((T9U16)(T9CudbData(cudb) - (T9U8 T9FARUDBPOINTER*)(cudb)))

/* Macro to get size in bytes of the cudb data area */
#define T9CudbDataAreaBytes(cudb)    \
            ((T9U16)((cudb)->wDataSize - T9CudbHeaderBytes(cudb)))


/* Helper functions exposed to other parts of T9 Core */

/*-----------------------------------------------------------------------------
 *
 *  Function name   : T9CC_IsUdbSpell
 *
 *  Description     : Judge if the current selected spell is from CUdb
 *
 *  Pass            : pCCFieldInfo = Pointer to chinese data info structure.
 *
 *  Return          : 1: if selected spell is from cudb
 *                    0: otherwise (implies from ldb)
 *
 *---------------------------------------------------------------------------*/
T9U8 T9FARCALL T9CC_IsUdbSpell(T9CCFieldInfo *pCCFieldInfo);


/*---------------------------------------------------------------------------
 *
 *  Function name   : T9CC_UdbGetEntryContent
 *
 *  Description     : Copy the content of the target entry into an object.
 *
 *  Pass            : pCudb = Pointer to CUDB
 *                    wTargetIndex = entry index ranging from 0 to entry count - 1
 *                    bOption = CUDB_GET_SIZE: copy the phrase and acronym sizes only
 *                              CUDB_GET_PHRASE: copy phrase and phrase size only
 *                              CUDB_GET_ACRONYM: copy acronym and acronym size only
 *                              (CUDB_GET_PHRASE | CUDB_GET_ACRONYM) copy everything.
 *                    pResultObj = Pointer to the object for storing entry contents.
 *
 *  Return          : void
 *
 *---------------------------------------------------------------------------*/
void T9FARCALL T9CC_UdbGetEntryContent(T9CCUdbInfo T9FARUDBPOINTER *pCudb,
                                 T9U16                     wTargetIndex,
                                 T9U8                      bOption,
                                 T9CCUdbObj                *pResultObj);


/*---------------------------------------------------------------------------
 *
 *   Function: T9CC_FindUdbContext
 *
 *   Synopsis: Find from CUDB any phrase that match the current context, which is the several
 *             character before the cursor, and return the next character from the phrase.
 *
 *   Input:    pCCFieldInfo    - pointer to field information structure
 *             bDepth        - number of character to look back from cursor for context.
 *                             valid range is 0 to T9CCDYNCTXTSEARCHMAXDEPTH - 1
 *             wStartIndex   - index to start the CUDB search.
 *                             valid range is 1 to CUDB entry count.
 *             pwMatchIndex  - OUTPUT: Index of the matching phrase.
 *                             valid range is 1 to CUDB entry count
 *                             NOMATCH if no match found or
 *                                     the matching phrase has no more character for context
 *             pbMatchSize   - OUTPUT: Size of matching phrase.
 *             pwMatchChar   - I/O: if 0, no context character is returned.
 *                             otherwise, return context character if found.
 *
 *   Return:   T9STATNONE       if successful
 *             T9STATNOWRD      if no matching phrase is found.
 *             T9STATEND        if wStartIndex > CUDB entry count.
 *             T9STAT_NO_UDB    if CUDB is absent.
 *             T9STAT_BAD_PARAM if inputs are invalid
 *
 *---------------------------------------------------------------------------*/
T9STATUS T9FARCALL T9CC_FindUdbContext(T9CCFieldInfo *pCCFieldInfo,
                                 T9U8         bDepth,
                                 T9U16        wStartIndex,
                                 T9U16       *pwMatchIndex,
                                 T9U8        *pbMatchSize,
                                 T9U16       *pwMatchChar);


/*-----------------------------------------------------------------------------
 *
 *  Function name   : T9CC_UdbFillSpell
 *
 *  Description     : Fills the spell buff with all message shortcuts that match the
 *                    current key sequence. There are two cases:
 *                    1, In Pin Yin mode, the spell buffer is filled with spell
 *                      from ldb first, if there is no match from ldb, match from udb is shifted to
 *                       the first place.
 *                    2, In cudblist mode, the spell buffer is only filled with spell from udb
 *
 *  Pass            : pCCFieldInfo = Pointer to field information structure.
 *
 *  PRE             : spell buffer has been filled with LDB spells (including FuzzyPinyin) if there's any.
 *                    LDB spells has been counted.
 *
 *  POST            : CUDB acronyms that match the original key buffer will be appended to spell buffer.
 *
 *  Return          : T9STATNONE: found match or other right conditions
 *                    T9STATNOWRD: not found
 *
 *---------------------------------------------------------------------------*/
T9STATUS T9FARCALL T9CC_UdbFillSpell(T9CCFieldInfo *pCCFieldInfo);


/*-----------------------------------------------------------------------------
 *
 *  Function name   : T9CC_UdbFillSelectMessage
 *
 *  Description     : fill the Phonetic Chinese Selection Window with phrase from UDB
 *                     (Only used when the current selected spell is from udb
 *  Pass            : pCCFieldInfo = Pointer to field information structure.
 *                    mPageDirection = 1 for User hit Prev, 2 for Next, 0 other
 *
 *  Return          : pCCFieldInfo->nSelectPageLen
 *
 *---------------------------------------------------------------------------*/
T9STATUS T9FARCALL T9CC_UdbFillSelectMessage(T9CCFieldInfo *pCCFieledInfo,
                                         T9MINOR mPageDirection);


/*-----------------------------------------------------------------------------
 *
 *  Function name   : T9CC_CountLdbSpell
 *
 *  Description     : Count the number of spells from ldb
 *
 *  Pass            : pCCFieldInfo = Pointer to chinese data info structure.
 *
 *  Return          : void   (pCCFieldInfo->bSpellMatchFromLdb record the result)
 *
 *---------------------------------------------------------------------------*/
void T9FARCALL T9CC_CountLdbSpell(T9CCFieldInfo *pCCFieldInfo);


/*---------------------------------------------------------------------------
 *
 *   Function: T9CC_UdbGetMatchedObj
 *
 *   Synopsis: Starting from the target obj, find the next entry, according
 *             to the search direction, that matches the given criteria.
 *
 *   Input:    pCCFieldInfo    - pointer to field information structure
 *             pTargetObj    - pointer to obj where we start the search
 *                             if 0 or not found, start from top of CUDB
 *             pResultObj    - pointer to obj storing the search result
 *             pbCriteria    - pointer to the string of search criteria
 *                             can be 0 in stroke search.
 *            bCriteriaBytes - length of criteria in bytes
 *                             if 0, any entry is a match.
 *             bOption       - specifies search direction, search method, and
 *                             which part of the search result to return.
 *                             [older/newer]|[exact/partial]|[get phrase and/or acronym]|[search by acronym/phrase/stroke]
 *
 *   Return:   T9STATNONE         if successful
 *             T9STATNOWRD        if couldn't find any matching entry for the given criteria.
 *                                content of pResultObj will not be changed.
 *             T9STAT_BAD_PARAM   if inputs are invalid
 *
 *---------------------------------------------------------------------------*/
T9STATUS T9FARCALL T9CC_UdbGetMatchedObj(T9CCFieldInfo *pCCFieldInfo,
                                     T9CCUdbObj   *pTargetObj,
                                     T9CCUdbObj   *pResultObj,
                                     const T9U8  *pbCriteria,
                                     T9U8         bCriteriaBytes,
                                     T9U8         bOption);


/*---------------------------------------------------------------------------
 *
 *   Function: T9CC_UdbUseObj
 *
 *   Synopsis: Find the target obj.
 *             Append its phrase part into text buffer if necessary.
 *             Reorder the target obj to the top of CUDB.
 *
 *   Input:    pCCFieldInfo  - pointer to field information structure
 *             pTargetObj    - pointer to obj to be used
 *             bOption       - whether to append phrase part into text buffer
 *
 *   Return:   T9STATNONE         if successful
 *             T9STATNOWRD        if couldn't find the target obj in the CUDB
 *             T9STATFULL         if can't copy the whole phrase into text buffer.
 *             T9STAT_BAD_PARAM   if inputs are invalid
 *
 *---------------------------------------------------------------------------*/
T9STATUS T9FARCALL T9CC_UdbUseObj(T9CCFieldInfo *pCCFieldInfo,
                              T9CCUdbObj   *pTargetObj,
                              T9U8         bOption);



#if defined(__cplusplus)
}
#endif

#endif /* T9CUDB_H */

/*---------------------------------- eof ---------------------------------*/
