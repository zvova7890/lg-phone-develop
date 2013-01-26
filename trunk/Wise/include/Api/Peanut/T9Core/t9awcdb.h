/*******************************************************************************
;*******************************************************************************
;**                                                                           **
;**                    COPYRIGHT 1998-2004 TEGIC COMMUNICATIONS               **
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
;**     FileName: t9awcdb.h                                                     **
;**                                                                           **
;**  Description: Context data base access routines header file.                 **
;**               Conforms to Version 3.0                                     **
;**                                                                           **
;*******************************************************************************
;******************************************************************************/

#ifndef T9AWCDB_H
#define T9AWCDB_H    1

/* don't mangle the function name if compile under C++ */
#if defined(__cplusplus)
extern "C" {
#endif

extern T9UINT T9FARCALL T9AW_AddToContextBuffer(T9AWFieldInfo *pAWFieldInfo, T9UINT nTrailingSpace);
extern T9STATUS T9FARCALL T9AW_AddToContextDatabase(T9AWFieldInfo *pAWFieldInfo);
extern T9UINT T9FARCALL T9AW_GetCdbObject(T9AWFieldInfo *pAWFieldInfo,
                                         T9UINT nCdbObjNum,
                                         T9UINT nWordLen,
                                         T9UINT nCursor,
                                         T9U8   bLead,
                                         T9U8  bObjectType,
                                         T9UINT *pnTerminal,
                                         T9U8  bRightMost,
                                         T9SYMB *psBuildTxtBuf,
                                         T9UINT nBuildTxtBufSize,
                                         T9UINT *pnComplLen,
                                         T9UINT *pnCdbObjCnt,
                                         T9INT nTraverseNext);
extern T9STATUS T9FARCALL T9AW_DoCdbSpaceProcessing(T9AWFieldInfo *pAWFieldInfo);
extern void T9FARCALL T9AW_BreakCdbContext(T9AWFieldInfo *pAWFieldInfo);
extern void T9FARCALL T9AW_BreakCdbContextInBuffer(T9AWFieldInfo *pAWFieldInfo);
extern void T9FARCALL T9AW_ZeroOutCdbOffsetInfo(T9AWFieldInfo *pAWFieldInfo);

/* define the delimiter that triggers prediction */
#define CDBDELIMITER (T9SYMB) (0x20)

/* The Cdb data area pointer */
#define T9CdbData(cdb) ((T9SYMB T9FARUDBPOINTER *) cdb->sDataArea)

/* Macro to get actual number of bytes in the cdb header area */
#define T9CdbHeaderBytes(cdb)    \
            ((T9UINT)((T9U8 T9FARUDBPOINTER *)T9CdbData(cdb) - (T9U8 T9FARUDBPOINTER *)cdb))

/* Macro to get actual number of bytes in the cdb data area */
#define T9CdbDataAreaSymbs(cdb)    \
            ((T9UINT)((cdb->wDataSize - T9CdbHeaderBytes(cdb))/T9SYMBOLWIDTH))

#if defined(__cplusplus)
}
#endif

#endif /* T9UDB_H */


/* eof */
