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
;**     FileName: t9cpfcn.h                                                   **
;**                                                                           **
;**  Description: Some T9 generic function prototypes used in PTI.            **
;**               Conforming to the development version of PTI.				  **
;**                                                                           **
;*******************************************************************************
;******************************************************************************/

#include "t9cpapi.h"
#include "t9ldb.h"

#ifndef T9CPFCN_H
#define T9CPFCN_H 1

/* don't mangle the function name if compile under C++ */
#if defined(__cplusplus)
extern "C" {
#endif

#define     NOMATCH             0xFFFF
#define T9CP_MIN(x, y)     (((x) > (y))?(y):(x))

/*----------------------------------------------------------------------------
 *  Define the T9 generic function prototypes in the T9 core.                                         
 *----------------------------------------------------------------------------*/
T9STATUS T9FARCALL T9CP_GetLdbVersion(T9FieldInfo *, T9U8 *);
T9STATUS T9FARCALL T9CP_CheckCompatOffset(T9U16, T9U16, T9U16);
T9U8 T9FARCALL T9CP_LookupWordID(T9FieldInfo *   pFieldInfo, 
							    T9U32           dwStartOffset,
                                T9U16           wStart,
                                T9U16           wEnd,
                                T9U16           wID,
                                T9U16           *pwIDs);
void T9FARCALL T9CP_DoNibbleRangeAdjust(T9U16 *pwStartIndex,
                                         const T9U16 *pNibbleRanges,
                                         T9FieldInfo *pFieldInfo);
void T9FARCALL T9CP_WriteUdbData(T9FieldInfo *pFieldInfo,
                                 void T9FARUDBPOINTER *pTo,
                                 const void T9FARDATA *pFrom,
                                 T9UINT nSize);
T9STATUS T9FARCALL T9CP_ValidateLDB(T9FieldInfo *);
T9U16 T9FARCALL T9CP_ReadWord(T9CPFieldInfo *pT9CPFieldInfo, T9MINOR mCacheIndex);
T9U8 T9FARCALL T9CP_ReadByte(T9CPFieldInfo *pT9CPFieldInfo, T9MINOR mCacheIndex);

T9UINT T9FARCALL T9CP_IsComponent(T9CPFieldInfo *pT9CPFieldInfo, T9U16 wUnicode);

/* End don't mangle the function name if compile under C++ */
#if defined(__cplusplus)
    }
#endif

#endif	/* #ifndef T9CPFCN_H */

/* ----------------------------------< eof >--------------------------------- */

