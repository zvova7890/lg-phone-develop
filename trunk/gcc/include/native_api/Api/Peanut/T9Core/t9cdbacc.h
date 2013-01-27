/*******************************************************************************
********************************************************************************

                    COPYRIGHT 2000-2004 TEGIC COMMUNICATIONS

                TEGIC COMMUNICATIONS PROPRIETARY INFORMATION

     This software is supplied under the terms of a license agreement
     or non-disclosure agreement with Tegic Communications and may not
     be copied or disclosed except in accordance with the terms of that
     agreement.

********************************************************************************

     File Name:   T9CDBAcc.h

     Description: Function prototypes T9 Chinese database access functions


********************************************************************************
********************************************************************************/

#ifndef _T9CDBACC_H
#define _T9CDBACC_H    1

/* don't mangle the function name if compile under C++ */
#if defined(__cplusplus)
extern "C" {
#endif

#define OUTPUT_FORMAT_0600  0x0600

extern T9STATUS T9FARCALL T9CC_LdbValidate(T9CCFieldInfo *pCCFieldInfo);
extern T9STATUS T9FARCALL T9CC_LdbCheck(T9CCFieldInfo *pCCFieldInfo);
extern T9U8  T9FARCALL T9CC_FindRelatedComponents(T9CCFieldInfo *pCCFieldInfo);
extern T9U16 T9FARCALL T9CC_CharHasComponent(T9U16 wCharCode, T9CCFieldInfo *pCCFieldInfo);

extern T9U8 T9FARCALL T9CC_db_HasModule(T9U8 bModule, T9CCFieldInfo *pCCFieldInfo);

#if defined(__cplusplus)
}
#endif

#endif

/*-----------------------------------< eof >----------------------------------*/

