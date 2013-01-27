/*******************************************************************************
********************************************************************************
**
**                    COPYRIGHT 2005 TEGIC COMMUNICATIONS
**
**                TEGIC COMMUNICATIONS PROPRIETARY INFORMATION
**
**     This software is supplied under the terms of a license agreement
**     or non-disclosure agreement with Tegic Communications and may not
**     be copied or disclosed except in accordance with the terms of that
**     agreement.
**
********************************************************************************
**
**     File Name:   t9awruuudb.h
**
**     Description: T9 Event handler for Japanese language
**
********************************************************************************
********************************************************************************/

#ifndef _T9AWRUUDB_H

#define _T9AWRUUDB_H 1

#ifndef  T9AWRECENCYCOUNT
/* Number of yomis to reprioritize in selection list.
 * Can be customized in xxt9oem.h file.  If not customized, the
 * default is defined here. */
#define  T9AWRECENCYCOUNT 3
#endif
#include "t9awudb.h"


static void T9NEARCALL RUT9UpdateUDBUsageCount(T9AWFieldInfo* pAWFieldInfo,
                                               UdbBodyPtr     pbUdbSrc,
											   T9AuxType*     paKeySrc, 
											   T9UINT         nWordLen);

static T9STATUS T9NEARCALL RUAddRdbObject(T9AWFieldInfo* pAWFieldInfo, 
                                         T9UINT nWordLen,
                                         T9UINT nObjNumRaw, 
                                         T9AuxType* paAuxSrc);

static T9STATUS T9NEARCALL RUAddUdbObject(T9AWFieldInfo *pAWFieldInfo,  
                                         T9SYMB *psTxtSrc,
                                         T9AuxType *paAuxSrc, 
                                         T9UINT nWordLen);

static T9STATUS T9NEARCALL RUAddMdbObject(T9AWFieldInfo *pAWFieldInfo,  
                                         T9SYMB *psTxtSrc,
                                         T9AuxType *paAuxSrc, 
                                         T9UINT nWordLen);

static T9U16 T9NEARCALL RUAgeUdbCount(T9AWFieldInfo *pAWFieldInfo);

static void T9NEARCALL RUdbGarbageCollection(T9AWFieldInfo *pAWFieldInfo,
                                     T9AWUdbInfo T9FARUDBPOINTER *pUdb,
                                     T9UINT nNewWordSize);

static T9STATUS T9NEARCALL AddRUObjectStart(T9AWFieldInfo *pAWFieldInfo, T9UINT nWordLen,
                                            UdbRecTypes eType, T9U16 wInitFreq,
                                            T9UINT nRecordLen, T9AuxType *paAuxSrc, NibbleWrite* pN,
                                            T9U16       * pwCheckSum, T9U8 bAsMDBWord);

#ifndef UDB_LENMASK8
#error "Die : for AWRUUDB, we need to see UDB_LENMASK8 has been defined before include this file."
#endif

#undef  UDB_LENMASK8
#define UDB_LENMASK8 ((T9U8) 0x1F) /* 5 LSBs of byte */

#ifndef T9UDBAGGINGFACTOR
#error "Die : for AWRUUDB, we need to include t9awudb.h before this file"
#endif

#undef  T9UDBAGGINGFACTOR
#define T9UDBAGGINGFACTOR 2


#ifndef T9UDBMAXUPDATE
#error "Die : for AWRUUDB, we need to include t9awudb.h before this file"
#endif
#undef  T9UDBMAXUPDATE
#define T9UDBMAXUPDATE ((T9U16)(0xFFFF - T9RD_WORD_INIT_FREQ))
#endif
