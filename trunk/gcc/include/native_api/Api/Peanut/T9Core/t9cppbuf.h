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
;**     FileName: t9cppbuf.h                                                  **
;**                                                                           **
;**  Description: PTI phrase buffer read/save module header file.             **
;**               Conforming to the development version of PTI.				  **
;**                                                                           **
;*******************************************************************************
;******************************************************************************/

#ifndef T9CPPBUF_H
#define T9CPPBUF_H 1

/* don't mangle the function name if compile under C++ */
#if defined(__cplusplus)
extern "C" {
#endif

#define T9CP_MAXDUPSUPNUM (128 + T9CPMAXPAGESIZE)  /* maximum number of phrases for duplicate suppression */
#define T9CP_FREQ_MASK_EXACT    ((T9U16)0x8000)
#define T9CP_FREQ_MASK_CONTEXT  ((T9U16)0x4000)
#define T9CP_FREQ_MASK_UDB      ((T9U16)0x2000)
#define T9CP_FREQ_MASK_NONMOHU  ((T9U16)0x1000)
#define T9CP_FREQ_MASK_ALL      ((T9U16)(T9CP_FREQ_MASK_EXACT | T9CP_FREQ_MASK_CONTEXT | T9CP_FREQ_MASK_UDB | T9CP_FREQ_MASK_NONMOHU))

#define T9CP_UEDITDEFLENFREQ    (0x0FFFFFFF)

#define T9CP_MAX_SPELL_FREQ     ((T9U16)(0x1000))
/* this is for encoding spell to a stream of bits used in spell buffer */
#define T9CP_NUM_BITS_PER_LETTER 3  

#define T9CP_IsSpellBufEmpty(pT9CPFieldInfo) ((pT9CPFieldInfo)->CommonInfo.sSpellBuf.bTestClear || !(pT9CPFieldInfo)->CommonInfo.sSpellBuf.bNumSpells)
#define T9CP_IsPhraseBufEmpty(pT9CPFieldInfo) ((pT9CPFieldInfo)->CommonInfo.sPhraseBuf.bTestClear || !(pT9CPFieldInfo)->CommonInfo.sPhraseBuf.wTotal)
#define T9CP_GetSpellCount(pT9CPFieldInfo)   (T9U8)((pT9CPFieldInfo)->CommonInfo.sSpellBuf.bTestClear? 0: (pT9CPFieldInfo)->CommonInfo.sSpellBuf.bNumSpells)
/*----------------------------------------------------------------------------
 *  Define the internal spell buffer save and read function prototypes.
 *----------------------------------------------------------------------------*/
void T9FARCALL T9CP_ClearSpellBuf(T9CPFieldInfo *pT9CPFieldInfo);
void T9FARCALL T9CP_RestoreSpellBuf(T9CPFieldInfo *pT9CPFieldInfo, T9UINT fSpellBufRestorable, T9UINT fPhraseBufRestorable);
/* This function is going to return the specified spell in the buffer, the index is 1 based 
 * 
 * parameters:  nIndex          1-based index of the spell in the spell buffer
 *              psSpellInfo     pointing to the structure where the return spell will be written
 *
 * return:  T9STATNONE if successful, T9CPSTAT_SPELL_NOTFOUND if not.
 */
T9STATUS T9FARCALL T9CP_GetSpellFromBuf(T9CPFieldInfo *pT9CPFieldInfo, T9CPSpellInfo *psSpellInfo, T9UINT nIndex);

/* set the active spell to the default one according to the following priority:
   Pinyin/BPMF/Stroke
   Jianpin
   Num
   AW/Sym
   Note: This relies on the ordering of spells in spell buffer, so that the last
   visited type has higher priority to be the default active spell.
*/
void T9FARCALL T9CP_SetDefaultActiveSpell(T9CPFieldInfo *pT9CPFieldInfo);

/* Function : T9CP_GetNextSpellInAlphabeticOrder
 *            Get the next spelling from spell buffer according to alphabetic
 *            order of each syllable.
 * Input    : pT9CPFieldInfo = PTI field info
 *            pSpell = current spelling
 *              Note : call sets pSpell->bSpellLen to 0 to get first spelling
 * Output   : pSpell = next spelling if found
 * Return   : T9STATNONE if successful, T9CPSTAT_SPELL_NOTFOUND if not.
 */
T9STATUS T9FARCALL T9CP_GetNextSpellInAlphabeticOrder(T9CPFieldInfo *pT9CPFieldInfo,
                                             T9CPSpellInfo *pSpell);

/* 
 * this function should be called for LDB spells, context spells, UDB spells and mohu spells.  The new 
 * added spells will be checked for duplicates against all the similarly encoded entries.
 *
 * pass:
 *      pT9CPFieldInfo  the pointer to the structure
 *      pSpellInfo      pointing to the spell info.  It should be NULL if it is an LDB spell added 
 *                          from UDB or LDB without context
 *      dwFreq          The frequency if it is from UDB.  Otherwise, it is ignored.
 *      bLdbIndex       0 if this is not an LDB spell, otherwise, 1-based LDB instruction index.  Invalid for mohu pinyin
 *      bIsExact        1 if an exact match, 0 if not.
 *      bIsFromContext  1 if it is from context, 0 if not.
 *      bIsFromUdb      0 if it is not from RUDB, 1 if it is from RUDB.
 *      bIsMohu         1 if it is a mohu pinyin, 0 if not.
 *      bCombineFreq    1 to combine new frequency with duplicate's frequency, 0 otherwise.
 *      
 * return           0 - successful
 *                  1 - buffer is not enough, conflicting with phrase buffer
 * Note: the matching spells should be added to the buffer in the following order for duplicate suppression purpose:
 *      1, context spells, mohu or not, exact or not, from LDB and UDB
 *      2, LDB spells that are not from context.  LDB spells are coverted to full spell for duplication check
 *      3, UDB spells that are not from context.  No duplicate check
 * 
 */
T9UINT T9FARCALL T9CP_AddSpellToBuf(T9CPFieldInfo *pT9CPFieldInfo, T9CPSpellInfo *pSpellInfo, T9U32 dwFreq, T9U8 bLdbIndex, T9U8 bIsExact, T9U8 bIsFromContext, T9U8 bIsFromUdb, T9U8 bIsMohu, T9U8 bCombineFreq);


/*----------------------------------------------------------------------------
 *  Define the internal phrase buffer save and read function prototypes.                                         
 *----------------------------------------------------------------------------*/

/* 
    This function fills up the phrase buffer based on the PID ranges that are set in
    T9CPFieldInfo.  The phrases include context predictions.
 */
void T9FARCALL T9CP_FillPhraseBufOnRanges(T9CPFieldInfo *pT9CPFieldInfo, T9U8 bActIsJianpin, T9U8 *pbTones, T9U8 *pbValidate);
T9UINT T9FARCALL T9CP_ExpandDelimiter(T9CPFieldInfo *pT9CPFieldInfo);
T9STATUS T9FARCALL T9CP_PhoneticFillPhraseBuffer(T9CPFieldInfo *pT9CPFieldInfo);
void T9FARCALL T9CP_ClearPhraseBuf(T9CPFieldInfo *pT9CPFieldInfo);
void T9FARCALL T9CP_RestorePhraseBuf(T9CPFieldInfo *pT9CPFieldInfo);
T9STATUS T9FARCALL T9CP_AdjustPointerFillPhraseBuf(T9CPFieldInfo *pT9CPFieldInfo, T9CPGETTYPE eGetType, T9STATUS T9FARCALL (*FctFill)(T9CPFieldInfo *pT9CPFieldInfo));
T9STATUS T9FARCALL T9CP_ConvertPhraseToUnicode(T9CPFieldInfo *pT9CPFieldInfo, T9CPPhraseInfo *psPhrase, T9CP_IDEncode eEnc);

#define T9CP_PhraseBufPageIsFull(pT9CPFieldInfo) (0 == ((pT9CPFieldInfo)->CommonInfo.sPhraseBuf.wTotal % (pT9CPFieldInfo)->CommonInfo.sPhraseBuf.bPageSize))

#define T9CP_PhraseLastFreqInPage(psPhraseBuf) (((psPhraseBuf)->bTestClear || \
    !(psPhraseBuf)->wTotal || \
    ((psPhraseBuf)->wTotal == (psPhraseBuf)->wCurrent) || \
    ((psPhraseBuf)->wTotal % (psPhraseBuf)->bPageSize))? \
         0:((psPhraseBuf)->pwFreq[(psPhraseBuf)->bPageSize - 1]))
#define T9CP_PhraseFreqGroupDiff(pT9CPFieldInfo) ((T9U16)(T9CP_IsPhraseBufEmpty(pT9CPFieldInfo)?0xffff: \
    ((pT9CPFieldInfo)->CommonInfo.sPhraseBuf.wPrevFreq & T9CP_FREQ_MASK_ALL) - \
    (T9CP_PhraseLastFreqInPage(&(pT9CPFieldInfo)->CommonInfo.sPhraseBuf) & T9CP_FREQ_MASK_ALL)))
/* use the following to decide if certain group of phrases need to be added to the phrase buffer */
/* need to search for a group if prev page & current page in diff group or in the same requested group */
#define T9CP_PhraseNeedExact(pT9CPFieldInfo) ((T9CP_PhraseFreqGroupDiff(pT9CPFieldInfo) >= T9CP_FREQ_MASK_EXACT) || \
    ((pT9CPFieldInfo)->CommonInfo.sPhraseBuf.wPrevFreq & T9CP_FREQ_MASK_EXACT))
#define T9CP_PhraseNeedPartial(pT9CPFieldInfo) ((T9CP_PhraseFreqGroupDiff(pT9CPFieldInfo) >= T9CP_FREQ_MASK_EXACT) || \
    (~(pT9CPFieldInfo)->CommonInfo.sPhraseBuf.wPrevFreq & T9CP_FREQ_MASK_EXACT))
#define T9CP_PhraseNeedContext(pT9CPFieldInfo) ((T9CP_PhraseFreqGroupDiff(pT9CPFieldInfo) >= T9CP_FREQ_MASK_CONTEXT) || \
    ((pT9CPFieldInfo)->CommonInfo.sPhraseBuf.wPrevFreq & T9CP_FREQ_MASK_CONTEXT))
#define T9CP_PhraseNeedNonContext(pT9CPFieldInfo) ((T9CP_PhraseFreqGroupDiff(pT9CPFieldInfo) >= T9CP_FREQ_MASK_CONTEXT) || \
    (~(pT9CPFieldInfo)->CommonInfo.sPhraseBuf.wPrevFreq & T9CP_FREQ_MASK_CONTEXT))
#define T9CP_PhraseNeedUdb(pT9CPFieldInfo) ((T9CP_PhraseFreqGroupDiff(pT9CPFieldInfo) >= T9CP_FREQ_MASK_UDB) || \
    ((pT9CPFieldInfo)->CommonInfo.sPhraseBuf.wPrevFreq & T9CP_FREQ_MASK_UDB))
#define T9CP_PhraseNeedLdb(pT9CPFieldInfo) ((T9CP_PhraseFreqGroupDiff(pT9CPFieldInfo) >= T9CP_FREQ_MASK_UDB) || \
    (~(pT9CPFieldInfo)->CommonInfo.sPhraseBuf.wPrevFreq & T9CP_FREQ_MASK_UDB))

/* This function is to get a phrase from the specified position, the index is 0 based */
void T9FARCALL T9CP_GetPhraseFromBuf(T9CPFieldInfo *pT9CPFieldInfo, T9CPPhraseInfo *psPhraseInfo, T9UINT nIndex);
T9UINT T9FARCALL T9CP_AddPhraseToBuf(T9CPFieldInfo *pT9CPFieldInfo, struct T9CP_PhraseBuf *psPhraseBuf, T9SYMB *pwPhraseBuf, T9U8 bPhraseLen, T9CP_IDEncode eEnc, T9U16 wFreq, T9U8 bIsExact, T9U8 bIsFromContext, T9U8 bIsFromUdb);


void T9FARCALL T9CP_GetCommonChar(T9CPFieldInfo *   pT9CPFieldInfo);
T9UINT T9FARCALL T9CP_PhraseBufLookup(T9CPFieldInfo *pT9CPFieldInfo, T9CPPhraseInfo *pPhraseInfo, T9CPPhraseInfo *pPhraseInBuf);

/* End don't mangle the function name if compile under C++ */
#if defined(__cplusplus)
    }
#endif

#endif	/* #ifndef T9CPPBUF_H */

/* ----------------------------------< eof >--------------------------------- */
