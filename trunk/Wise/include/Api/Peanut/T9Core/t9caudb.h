/*******************************************************************************
********************************************************************************

                    COPYRIGHT 1999-2004 TEGIC COMMUNICATIONS

                TEGIC COMMUNICATIONS PROPRIETARY INFORMATION

     This software is supplied under the terms of a license agreement
     or non-disclosure agreement with Tegic Communications and may not
     be copied or disclosed except in accordance with the terms of that
     agreement.

********************************************************************************

     File Name:   t9caudb.h

     Description: Header file for Chinese Auto User Database module


********************************************************************************
********************************************************************************/

#ifndef T9CAUDB_H
#define T9CAUDB_H

/* don't mangle the function name if compile under C++ */
#if defined(__cplusplus)
extern "C" {
#endif

#define T9MINCAUDBSIZE              20      /* THE minimun size fo the audb */
#define CAUDBCACHEMAX               10      /* size of cache for CAUDB matches during NEXT/PREV */

#define T9CAUDBIDMASK               0X0003  /* tegic ID or unicode */
#define T9CAUDBLCMASK               0X0004  /* by location or ID */

#define T9CHINSIMP                  0X0000  /* MASK FOR SIMPLE */
#define T9CHINTRAD                  0X4000  /* MASK FOR TRADITIONAL */

#define T9CAUDBLANGMASK             0XC000  /* */

/*------------------------------------------------------------------------
 *
 *                  API for accessing the Chinese auto user database (AUDB).
 *
 *------------------------------------------------------------------------*/
extern T9STATUS T9FARCALL T9CC_AudbAddObject(T9CCFieldInfo *pCCFieldInfo,
                              T9SYMB sChar_ID, T9SYMB sChar_Tegic_ID, T9U8 bOptions);

extern T9U16 T9FARCALL T9CC_AudbSearchObject(T9CCFieldInfo *pCCFieldInfo, T9SYMB sChar_ID);

extern T9STATUS T9FARCALL T9CC_AudbGetObject(T9CCFieldInfo *pCCFieldInfo,
                              T9SYMB* psChar_ID, T9U16 wPosition, T9U8 Options);

#if defined(__cplusplus)
}
#endif

#endif

/*----------------------------- eof ------------------------------------*/
