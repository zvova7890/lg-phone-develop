/*******************************************************************************
;*******************************************************************************
;**                                                                           **
;**                  COPYRIGHT 1997-2003 TEGIC COMMUNICATIONS                 **
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
;**     FileName: T9awmdb.h                                                   **
;**                                                                           **
;**  Description: Manufacture database (MDB) access header File.              **
;**               Conforming to version 5.2                                   **
;**                                                                           **
;*******************************************************************************
;******************************************************************************/

#ifndef T9AWMDB_H

#define T9AWMDB_H

#if defined(__cplusplus)
extern "C" {
#endif

extern T9UINT T9FARCALL T9AW_GetMdbObject( T9AWFieldInfo  *pAWFieldInfo,
                                   T9U8         bObjectType,
                                   T9UINT        nMdbObjNum,
                                   T9INT       nTraverseNext,
                                   T9UINT        nWordLen,
                                   T9UINT        nCursor,
                                   T9U8          bLead,
                                   T9U32        *pdwMdbDataIdx,
                                   T9U8         bRightMost,
                                   T9SYMB       *psBuildTxtBuf,
                                   T9UINT        nBuildTxtBufSize,
                                   T9UINT        *pnComplLen,
                                   T9UINT        *pnNumTermWords,
                                   T9UINT        *pnFullObjCnt);


#if defined(__cplusplus)
}
#endif

#endif /* #ifndef T9AWMDBB_H */



