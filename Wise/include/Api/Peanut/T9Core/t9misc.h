/*******************************************************************************
;*******************************************************************************
;**                                                                           **
;**                  COPYRIGHT 1997-2006 TEGIC COMMUNICATIONS                 **
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
;**     FileName: T9misc.h                                                    **
;**                                                                           **
;**  Description: Miscellaneous tools for T9.                                 **
;**                                                                           **
;*******************************************************************************
;******************************************************************************/

#ifndef T9MISC_H
#define T9MISC_H 1

/* don't mangle the function name if compile under C++ */
#if defined(__cplusplus)
extern "C" {
#endif

#define T9_FULLCHECKINFO(pFieldInfo)                                                    \
    if (! pFieldInfo) return(T9STATABORT);                                              \
    if (pFieldInfo->T9Private.wInitOK != T9_GOODSETUP) return T9STATNOINIT;             \
    if ((pFieldInfo->T9PrivateLdb[pFieldInfo->bActiveLangIndex].wLangOK != T9_GOODSETUP) ||  \
        (pFieldInfo->T9PrivateLdb[0].wLangOK != T9_GOODSETUP))   \
        return (T9STATNOLANG);

#define T9_CHECKSTATNONE(mStatus)   \
    if (mStatus != T9STATNONE) return mStatus;

/*------------------------------------------------------------------
 * Functions
 *------------------------------------------------------------------*/
extern T9U32 T9FARCALL T9_StringHash(const T9U8 T9FARDATA * str, const T9U32 len, const T9U32 dwStartValue);

/* will change to a single function once the ldb is build using the latest hash key value */
extern T9U32 T9FARCALL T9_StringHash2(const T9U8 T9FARDATA * str, const T9U32 len, const T9U32 dwStartValue);

T9U8* T9FARCALL T9_ByteCopy(void *des, const void T9FARUDBPOINTER *src, T9UINT size);
T9SYMB* T9FARCALL T9_SymbCopy(T9SYMB *des, const T9SYMB T9FARUDBPOINTER *src, T9UINT size);
T9U8* T9FARCALL T9_ByteSet(T9U8 *des, T9UINT size, T9U8 b);
T9U16* T9FARCALL T9U16Set(T9U16 *des, T9UINT size, T9U16 s);

void T9FARCALL T9_WriteUdbData(T9FieldInfo          *pFieldInfo,
                               void T9FARUDBPOINTER *pTo,
                               const void T9FARDATA *pFrom,
                               T9UINT                nSize);
T9STATUS T9FARCALL T9_RequestMultitapTimeout(T9FieldInfo *pFieldInfo, T9AuxType aKey);
T9UINT T9FARCALL T9_RequestAddWordToUDB(T9FieldInfo *pFieldInfo,
                                          T9UINT        nWordLen,
                                          T9SYMB      *psWordBuf);

T9STATUS T9FARCALL T9_ZeroOutWordVariables(T9FieldInfo *pFieldInfo);
T9STATUS T9FARCALL T9_EmptyNullFunc(T9FieldInfo *pFieldInfo);
T9STATUS T9FARCALL T9_EmptyMinorFunc(T9FieldInfo *pFieldInfo, T9MINOR mParam);
T9STATUS T9FARCALL T9_SetLanguage(T9FieldInfo *pFieldInfo, T9UINT nLdbNum,
                                T9FieldInfo *pPreviousFieldInfo);
T9STATUS T9FARCALL T9_Initialize(T9FieldInfo *pFieldInfo,
                         T9SYMB *psTxtBuf,
                         T9AuxType *paAuxBuf,
                         T9UINT   nBufLenMax,
                         T9UINT   nBufLen,
                         T9HandleRequest_f T9HandleRequest,
                         T9ReadLdbData_f T9ReadLdbData
                        );
T9U32 T9FARCALL T9_GetCollatingSequences(void);
T9STATUS T9FARCALL T9_CheckCompatOffset(T9U16 wLDBCompatID,
                                        T9U16 wCoreCompatBase,
                                        T9U16 wCoreCompatOffsetMask);

/* From t9ver.c: */
T9STATUS T9FARCALL T9_GetCodeVersion(T9U8 *pbCoreVerNum,
                                     T9U8 *pbResponse,
                                     T9U16 wBufSize,
                                     T9U16 *pwCoreVerLen,
                                     T9MINOR mYearDigits);
void T9FARCALL T9_ByteNumToHexStr(T9U8 bNumber, T9U8 *pbDest);

#ifdef T9CHECKCOMPILE
T9U32 T9FARCALL T9_CheckCompileParameters(T9FieldInfo *pFieldInfo,
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
                                          T9U32  *pdwInitOK);
#endif

/*
 * For debugging purpose only!
 */
#if defined(T9_DEBUG)
#include <assert.h>

#define T9Assert(e) assert(e)
#else
#define T9Assert(e)

#endif /* #if defined(T9_DEBUG) */


#if defined(__cplusplus)
}
#endif

#endif /* T9MISC_H */






/* ----------------------------------< eof >--------------------------------- */

