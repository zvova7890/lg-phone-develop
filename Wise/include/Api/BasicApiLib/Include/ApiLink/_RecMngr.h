/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	DYNAMIC LINKING LIBRARY

	Copyright(c) 1997-2003 BNSoft Corp.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT__RECMNGR_H_
#define		_BNSOFT__RECMNGR_H_

#include	"..\RecMngr.h"

typedef H_RECTABLE			(*T_pfnRecMngr_CreateTable)      (T_ID ID, T_CSTR pcszTblName, T_POS SortKeyPos, T_SIZE SortKeyLen, T_SIZE ReservedSize, BYTE* pData, T_SIZE DataSize);
typedef H_RECTABLE			(*T_pfnRecMngr_FindTable)        (T_CSTR pcszTblName);
typedef BOOL				(*T_pfnRecMngr_RemoveTable)      (T_CSTR pcszTblName);
typedef BOOL				(*T_pfnRecMngr_IsFreeTableID)    (T_ID ID);
typedef T_ID				(*T_pfnRecMngr_FindFreeTableID)  (T_ID InitID);
typedef T_INDEX				(*T_pfnRecMngr_Insert)           (H_RECTABLE hTable, BYTE* pNewItem, T_SIZE NewItemLen);
typedef T_INDEX				(*T_pfnRecMngr_Update)           (H_RECTABLE hTable, T_INDEX Index, BYTE* pNewItem, T_SIZE NewItemLen);
typedef BOOL				(*T_pfnRecMngr_Delete)           (H_RECTABLE hTable, T_INDEX Index);
typedef BOOL				(*T_pfnRecMngr_DeleteAll)        (H_RECTABLE hTable);
typedef T_CSTR				(*T_pfnRecMngr_GetTableName)     (H_RECTABLE hTable);
typedef T_ID				(*T_pfnRecMngr_GetTableID)       (H_RECTABLE hTable);
typedef T_POS				(*T_pfnRecMngr_GetKeyPos)        (H_RECTABLE hTable);
typedef T_SIZE				(*T_pfnRecMngr_GetKeyLen)        (H_RECTABLE hTable);
typedef T_NUM				(*T_pfnRecMngr_GetItemNum)       (H_RECTABLE hTable);
typedef T_SIZE				(*T_pfnRecMngr_GetUsedSize)      (H_RECTABLE hTable);
typedef T_ADDR				(*T_pfnRecMngr_GetDataAddr)      (H_RECTABLE hTable, T_INDEX Index);
typedef T_SIZE				(*T_pfnRecMngr_GetDataLen)       (H_RECTABLE hTable, T_INDEX Index);
typedef T_ADDR				(*T_pfnRecMngr_GetKeyAddr)       (H_RECTABLE hTable, T_INDEX Index);
typedef T_SIZE				(*T_pfnRecMngr_GetKeyData)       (H_RECTABLE hTable, T_INDEX Index, BYTE* pBuf);
typedef T_SIZE				(*T_pfnRecMngr_GetItemData)      (H_RECTABLE hTable, T_INDEX Index, BYTE* pBuf, T_SIZE BufSize);
typedef T_SIZE				(*T_pfnRecMngr_GetData)          (H_RECTABLE hTable, T_INDEX Index, T_POS Pos, BYTE* pBuf, T_SIZE Len);
typedef T_NUM				(*T_pfnRecMngr_GetRegionNum)     (void);
typedef T_SIZE				(*T_pfnRecMngr_GetRegionSize)    (void);
typedef BOOL				(*T_pfnRecMngr_GetRegionInfo)    (T_INDEX Index, TRecRgnInfo* pRgnInfo);
typedef T_SIZE				(*T_pfnRecMngr_GetTotalSize)     (void);
typedef T_SIZE				(*T_pfnRecMngr_GetTotalUsedSize) (void);
typedef T_SIZE				(*T_pfnRecMngr_GetTotalDelSize)  (void);
typedef T_SIZE				(*T_pfnRecMngr_GetTotalFreeSize) (void);

typedef struct
{
	T_pfnRecMngr_CreateTable		pfnCreateTable;
	T_pfnRecMngr_FindTable			pfnFindTable;
	T_pfnRecMngr_RemoveTable		pfnRemoveTable;
	T_pfnRecMngr_IsFreeTableID		pfnIsFreeTableID;
	T_pfnRecMngr_FindFreeTableID		pfnFindFreeTableID;
	T_pfnRecMngr_Insert			pfnInsert;
	T_pfnRecMngr_Update			pfnUpdate;
	T_pfnRecMngr_Delete			pfnDelete;
	T_pfnRecMngr_DeleteAll			pfnDeleteAll;
	T_pfnRecMngr_GetTableName		pfnGetTableName;
	T_pfnRecMngr_GetTableID			pfnGetTableID;
	T_pfnRecMngr_GetKeyPos			pfnGetKeyPos;
	T_pfnRecMngr_GetKeyLen			pfnGetKeyLen;
	T_pfnRecMngr_GetItemNum			pfnGetItemNum;
	T_pfnRecMngr_GetUsedSize		pfnGetUsedSize;
	T_pfnRecMngr_GetDataAddr		pfnGetDataAddr;
	T_pfnRecMngr_GetDataLen			pfnGetDataLen;
	T_pfnRecMngr_GetKeyAddr			pfnGetKeyAddr;
	T_pfnRecMngr_GetKeyData			pfnGetKeyData;
	T_pfnRecMngr_GetItemData		pfnGetItemData;
	T_pfnRecMngr_GetData			pfnGetData;
	T_pfnRecMngr_GetRegionNum		pfnGetRegionNum;
	T_pfnRecMngr_GetRegionSize		pfnGetRegionSize;
	T_pfnRecMngr_GetRegionInfo		pfnGetRegionInfo;
	T_pfnRecMngr_GetTotalSize		pfnGetTotalSize;
	T_pfnRecMngr_GetTotalUsedSize		pfnGetTotalUsedSize;
	T_pfnRecMngr_GetTotalDelSize		pfnGetTotalDelSize;
	T_pfnRecMngr_GetTotalFreeSize		pfnGetTotalFreeSize;
} TApiGrp_RecMngr;


#define	RecMngr_CreateTable(p1,p2,p3,p4,p5,p6,p7)	__ApiLink7(RecMngr,CreateTable,p1,p2,p3,p4,p5,p6,p7)
#define	RecMngr_FindTable(p1)				__ApiLink1(RecMngr,FindTable,p1)
#define	RecMngr_RemoveTable(p1)				__ApiLink1(RecMngr,RemoveTable,p1)
#define	RecMngr_IsFreeTableID(p1)			__ApiLink1(RecMngr,IsFreeTableID,p1)
#define	RecMngr_FindFreeTableID(p1)			__ApiLink1(RecMngr,FindFreeTableID,p1)
#define	RecMngr_Insert(p1,p2,p3)			__ApiLink3(RecMngr,Insert,p1,p2,p3)
#define	RecMngr_Update(p1,p2,p3,p4)			__ApiLink4(RecMngr,Update,p1,p2,p3,p4)
#define	RecMngr_Delete(p1,p2)				__ApiLink2(RecMngr,Delete,p1,p2)
#define	RecMngr_DeleteAll(p1)				__ApiLink1(RecMngr,DeleteAll,p1)
#define	RecMngr_GetTableName(p1)			__ApiLink1(RecMngr,GetTableName,p1)
#define	RecMngr_GetTableID(p1)				__ApiLink1(RecMngr,GetTableID,p1)
#define	RecMngr_GetKeyPos(p1)				__ApiLink1(RecMngr,GetKeyPos,p1)
#define	RecMngr_GetKeyLen(p1)				__ApiLink1(RecMngr,GetKeyLen,p1)
#define	RecMngr_GetItemNum(p1)				__ApiLink1(RecMngr,GetItemNum,p1)
#define	RecMngr_GetUsedSize(p1)				__ApiLink1(RecMngr,GetUsedSize,p1)
#define	RecMngr_GetDataAddr(p1,p2)			__ApiLink2(RecMngr,GetDataAddr,p1,p2)
#define	RecMngr_GetDataLen(p1,p2)			__ApiLink2(RecMngr,GetDataLen,p1,p2)
#define	RecMngr_GetKeyAddr(p1,p2)			__ApiLink2(RecMngr,GetKeyAddr,p1,p2)
#define	RecMngr_GetKeyData(p1,p2,p3)			__ApiLink3(RecMngr,GetKeyData,p1,p2,p3)
#define	RecMngr_GetItemData(p1,p2,p3,p4)		__ApiLink4(RecMngr,GetItemData,p1,p2,p3,p4)
#define	RecMngr_GetData(p1,p2,p3,p4,p5)			__ApiLink5(RecMngr,GetData,p1,p2,p3,p4,p5)
#define	RecMngr_GetRegionNum()				__ApiLink0(RecMngr,GetRegionNum)
#define	RecMngr_GetRegionSize()				__ApiLink0(RecMngr,GetRegionSize)
#define	RecMngr_GetRegionInfo(p1,p2)			__ApiLink2(RecMngr,GetRegionInfo,p1,p2)
#define	RecMngr_GetTotalSize()				__ApiLink0(RecMngr,GetTotalSize)
#define	RecMngr_GetTotalUsedSize()			__ApiLink0(RecMngr,GetTotalUsedSize)
#define	RecMngr_GetTotalDelSize()			__ApiLink0(RecMngr,GetTotalDelSize)
#define	RecMngr_GetTotalFreeSize()			__ApiLink0(RecMngr,GetTotalFreeSize)

#endif	//	_BNSOFT__RECMNGR_H_
