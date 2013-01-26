/*******************************************************************************
;*******************************************************************************
;**                                                                           **
;**                    COPYRIGHT 1998-2003 TEGIC COMMUNICATIONS               **
;**                                                                           **
;**                TEGIC COMMUNICATIONS PROPRIETARY INFORMATION               **
;**                                                                           **
;**     This software is supplied under the terms of a license agreement      **
;**     or non-disclosure agreement with Tegic Communications and may not     **
;**     be copied or disclosed except in accordance with the terms of that    **
;**     agreement.                                                            **
;**                                                                           **
;*******************************************************************************
;**                                                                           **
;**     FileName: T9rdb.h                                                     **
;**                                                                           **
;**  Description: reorder data base access routines source file.              **
;**               Conforms to Version 6.0                                     **
;**                                                                           **
;*******************************************************************************
;******************************************************************************/

#ifndef __T9RDB_H__
#define __T9RDB_H__

#if defined(__cplusplus)
extern "C" {
#endif

#define VT9RDB "T9RDB($Revision: 1.3 $) "
#include "t9api.h"
#include "t9key.h"
#include "t9ldb.h"
#include "t9udb.h"  /* include because we're sharing memory space with UDB */


#if defined(__cplusplus)
}
#endif

#endif /* __T9RDB_H__ */

