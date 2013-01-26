/*******************************************************************************
********************************************************************************

                    COPYRIGHT 2000-2003 TEGIC COMMUNICATIONS

                TEGIC COMMUNICATIONS PROPRIETARY INFORMATION

     This software is supplied under the terms of a license agreement
     or non-disclosure agreement with Tegic Communications and may not
     be copied or disclosed except in accordance with the terms of that
     agreement.

********************************************************************************

     File Name:   t9japi.h

     Description: External entry points for Japanese T9 Core.


********************************************************************************
********************************************************************************/

#ifndef T9JAPI_H
#define T9JAPI_H

/*----------------------------------------------------------------------------
 *  Function prototypes for API routines
 *----------------------------------------------------------------------------*/

extern T9STATUS T9FARCALL T9HandleJEvent(T9JWFieldInfo *pJWFieldInfo, T9Event *pEvent);

#endif /* T9JAPI_H */

/*---------------------------------- eof ---------------------------------*/
