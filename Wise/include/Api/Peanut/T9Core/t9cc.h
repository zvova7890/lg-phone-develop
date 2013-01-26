/*******************************************************************************
********************************************************************************

                    COPYRIGHT 1998-2003 TEGIC COMMUNICATIONS

                TEGIC COMMUNICATIONS PROPRIETARY INFORMATION

     This software is supplied under the terms of a license agreement
     or non-disclosure agreement with Tegic Communications and may not
     be copied or disclosed except in accordance with the terms of that
     agreement.

********************************************************************************

     File Name:   t9cc.h

     Description: Header file for T9 Chinese Character internals


********************************************************************************
********************************************************************************/

#ifndef _t9cc_H
#define _t9cc_H    1

#include "t9ccapi.h"

/* don't mangle the function name if compile under C++ */
#if defined(__cplusplus)
extern "C" {
#endif

/* Some of the API commands that T9CC treats special in post-processing. */
typedef enum {
    CCCMDOTHER,
    CCCMDKEY,
    CCCMDEXPL,
    CCCMDEXPLICITKEY,
    CCCMDSETTONE,
    CCCMDSETSPELL
} CCCMD;

/*----------------------------------------------------------------------------
 *  Function prototypes for non-API routines
 *----------------------------------------------------------------------------*/
extern T9STATUS	T9FARCALL T9CC_LdbInitialize(T9CCFieldInfo *pCCFieldInfo);
extern T9STATUS T9FARCALL T9CC_PreProcess(
    T9CCFieldInfo *pCCFieldInfo,
    T9MINOR mMagicString, /* Keep T9CPrivate.bCMagicStringOn? */
    T9MINOR mLeaveMultitapInsert, /* True if multitap insert is to be dropped */
    T9MINOR mDropPhraseComp /* True if phrase completion is to be dropped */
    );
extern T9STATUS T9FARCALL T9CC_PostProcess(T9CCFieldInfo *pCCFieldInfo,
                                  CCCMD     eCmd,
                                  T9MINOR     mPageDirection,
                                  T9MINOR     mAmbigKey,
                                  T9STATUS    mStatus);

/* Need these macros because they points to structs */
#define gpExactBin         (*((const T9PhoneticBin T9FARDATA**)&(pCCFieldInfo->T9CPrivate.pPrivatePTR[0])))    /* Exactly matching phonetic bin pointer for 1st bin set */
#define gpPartialBin       (*((const T9PhoneticBin T9FARDATA**)&(pCCFieldInfo->T9CPrivate.pPrivatePTR[1])))    /* First partially matching phonetic bin for 1st bin set */
#define gpExactBin2        (*((const T9PhoneticBin T9FARDATA**)&(pCCFieldInfo->T9CPrivate.pPrivatePTR[2])))    /* Exactly matching phonetic bin pointer for 2nd bin set */
#define gpPartialBin2      (*((const T9PhoneticBin T9FARDATA**)&(pCCFieldInfo->T9CPrivate.pPrivatePTR[3])))    /* First partially matching phonetic bin for 2nd bin set*/

#if defined(__cplusplus)
}
#endif

#endif /* _t9cc_H */
/*-----------------------------------< eof >----------------------------------*/

