/*******************************************************************************
********************************************************************************

                    COPYRIGHT 2003-2005 TEGIC COMMUNICATIONS

                TEGIC COMMUNICATIONS PROPRIETARY INFORMATION

     This software is supplied under the terms of a license agreement
     or non-disclosure agreement with Tegic Communications and may not
     be copied or disclosed except in accordance with the terms of that
     agreement.

********************************************************************************

     File Name:   t9kcapi.h

     Description: Header file for T9 Korean character module

     Version:	  7.3                                                       
********************************************************************************
********************************************************************************/

#ifndef _T9KCAPI_H
#define _T9KCAPI_H    1

#include "t9.h"

/* don't mangle the function name if compile under C++ */
#if defined(__cplusplus)
extern "C" {
#endif

/*----------------------------------------------------------------------------
 *  Define T9 core version number
 *
 *  String format is defined as "T9KC VMM.mm.bf.qa"
 *  Where
 *      MM   = major version number
 *      mm   = minor version number
 *      bf   = bug fix version number
 *      qa   = QA release version number
 *  Update T9KCCOREVER defn. if any component version # goes beyond 2 digits.
 *----------------------------------------------------------------------------*/
#define T9KCMAJORVER   T9MAJORVER
#define T9KCMINORVER   T9MINORVER
#define T9KCPATCHVER   T9PATCHVER
#define T9KCCOREVER   "T9KC V0" T9KCMAJORVER ".0" T9KCMINORVER ".0" T9KCPATCHVER "   "

/*----------------------------------------------------------------------------
 *  Define alphabetic word T9 field information structure.
 *---------------------------------------------------------------------------*/
typedef struct T9KCFieldInfo_s {
    T9FieldInfo G; /* Generic data. */
} T9KCFieldInfo;

T9STATUS T9FARCALL T9KCDelJamo(T9KCFieldInfo *pKCFieldInfo);
T9STATUS T9FARCALL T9KCDelKey(T9KCFieldInfo *pKCFieldInfo);
T9STATUS T9FARCALL T9KCDelWord(T9KCFieldInfo *pKCFieldInfo);
T9STATUS T9FARCALL T9KCGetCodeVersion(T9U8 *pbCoreVerBuf, T9U16 wBufSize, T9U16 *pwCoreVerLen);
T9STATUS T9FARCALL T9KCInitialize(T9KCFieldInfo *pKCFieldInfo, T9SYMB *psTxtBuf, T9AuxType *paAuxBuf, T9UINT nBufLenMax, T9UINT nBufLen, T9HandleRequest_f T9HandleRequest, T9ReadLdbData_f T9ReadLdbData);
T9STATUS T9FARCALL T9KCSetLanguage(T9KCFieldInfo *pKCFieldInfo, T9UINT nLdbNum,
                                 T9FieldInfo *pPreviousFieldInfo);
#if defined(__cplusplus)
}
#endif

#endif /* _T9KCAPI_H */
/*-----------------------------------< eof >----------------------------------*/

