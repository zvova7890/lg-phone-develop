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
;**     FileName: t9cpspel.h                                                 **
;**                                                                           **
;**  Description: Chinese Phrase Text Input spelling module header file.      **
;**               Conforming to the development version of PTI.				  **
;**                                                                           **
;*******************************************************************************
;******************************************************************************/

#ifndef T9CPSPEL_H
#define T9CPSPEL_H 1

/* don't mangle the function name if compile under C++ */
#if defined(__cplusplus)
extern "C" {
#endif

#define T9CP_FILTERDELIMITER    1   /* filter delimiter only */
#define T9CP_FILTERTONE         2   /* filter both tone and delimiter */

/* Pinyin spelling related definitions */
#define T9CP_FIRSTUPLETTER      'A'
#define T9CP_LASTUPLETTER       'Z'
#define T9CP_FIRSTLOWERLETTER   'a'
#define T9CP_LASTLOWERLETTER    'z'
#define T9CP_PHLETTERLEN        5
#define T9CP_BINSHIFT           4

#define T9CP_IsPinyinUpperCase(bLetter) (T9CP_IsByte(bLetter) ? (((bLetter) >= T9CP_FIRSTUPLETTER) && ((bLetter) <= T9CP_LASTUPLETTER)) : 0)
#define T9CP_IsPinyinLowerCase(bLetter) (T9CP_IsByte(bLetter) ? (((bLetter) >= T9CP_FIRSTLOWERLETTER) && ((bLetter) <= T9CP_LASTLOWERLETTER)) : 0)
#define T9CP_IsPinyinLetter(bLetter)    (T9CP_IsPinyinUpperCase(bLetter) || T9CP_IsPinyinLowerCase(bLetter))
#define T9CP_IsUpperCase(pInfo, b) ((T9CPIsModePinyin(pInfo) && T9CP_IsPinyinUpperCase(b)) || (T9CPIsModeBpmf(pInfo) && T9CPIsBpmfUpperCase(b)))
#define T9CP_IsLowerCase(pInfo, b) ((T9CPIsModePinyin(pInfo) && T9CP_IsPinyinLowerCase(b)) || (T9CPIsModeBpmf(pInfo) && T9CPIsBpmfLowerCase(b)))

typedef T9U8 T9CP_VOWEL[4];

T9U8 T9FARCALL T9CP_CountSyl(T9CPSpellInfo *pSpell);
void T9FARCALL T9CP_ConvertSpellInfo(T9CPFieldInfo *pT9CPFieldInfo,
                                     T9CPSpellInfo *pSpellInfo);
void T9FARCALL T9CP_ConvertExplSpellInfo(T9CPFieldInfo *pT9CPFieldInfo,
                                         T9U8 *pbKeyBuf,
                                         T9CPSpellInfo *pSpellInfo,
                                         const T9U8 *pbSyl,
                                         const T9U8 bNumSyls);
void T9FARCALL T9CP_MakeSpellFromType(T9CPSpellType eType,
                                      /*out*/T9CPSpellInfo *pSpell);
#ifdef T9ALPHABETIC
/* setup shift state in AW core according to destination spell type */
void T9FARCALL T9CP_AWSetShfCap(T9CPFieldInfo *pT9CPFieldInfo,
                                T9CPSpellType eDstSpellType);
#endif

/*----------------------------------------------------------------------------
 *  Define the internal spelling function prototypes.                                         
 *----------------------------------------------------------------------------*/
T9STATUS T9FARCALL T9CP_FillSpellBuffer(T9CPFieldInfo *pT9CPFieldInfo, T9UINT fAddChineseSpell);
T9STATUS T9FARCALL T9CP_FillSpellBufferCPCount(T9CPFieldInfo *pT9CPFieldInfo, T9UINT fAddChineseSpell, T9U8 * pbCPSpellAdded);

T9INT T9FARCALL T9CP_AreAllPhoneticKeysValid(T9UINT fIsPinyin, T9U8 *pbKeyBuf, T9U8 bLen);

/* End don't mangle the function name if compile under C++ */
#if defined(__cplusplus)
    }
#endif

#endif	/* #ifndef T9CPSPEL_H */
