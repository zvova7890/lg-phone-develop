/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	RECORD MANAGER

	Copyright(c) 1997-2003 BNSoft Corp.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT_RECMNGR_H_
#define		_BNSOFT_RECMNGR_H_

#include	"Include.h"
#include	"LnkList.h"

#define		RECORD_UNIT_SIZE	16

//	Definitions
typedef		T_HANDLE		H_RECTABLE;

typedef struct
{
	QUAD				Revision;			
	T_ADDR				StartAddr;		
	T_SIZE				AvailSize;					
	T_SIZE				UsedSize;	
	T_SIZE				DelSize;	
} TRecRgnInfo;


typedef		void			(*T_pfnRecResetNoti)(void);
typedef		void			(*T_pfnRecNotify)(int Cnt, int TotalCnt);

typedef struct
{
	TSLnkObj	LnkObj;
	T_ADDR		Addr;		
} TRecObject;

typedef struct
{
	TSLnkObj			LnkObj;
	T_ADDR				Addr;				
	T_CSTR				pcszTblName;			
	WORD				ID;					
	WORD				SortKeyPos;				
	WORD				SortKeyLen;				
	WORD				ObjNum;					
	TLnkList			ObjList;			
	TLnkList*			pObjListTbl;			
	T_SIZE				UsedSize;				
	T_SIZE				ReservedSize;	
} TRecTable;
	


extern H_RECTABLE	RecMngr_CreateTable      (T_ID ID, T_CSTR pcszTblName, T_POS SortKeyPos, T_SIZE SortKeyLen, T_SIZE ReservedSize, BYTE* pData, T_SIZE DataSize);
extern H_RECTABLE	RecMngr_FindTable        (T_CSTR pcszTblName);
extern BOOL		RecMngr_RemoveTable      (T_CSTR pcszTblName);
extern BOOL	        RecMngr_IsFreeTableID    (T_ID ID);
extern T_ID	        RecMngr_FindFreeTableID  (T_ID InitID);

extern T_INDEX	        RecMngr_Insert           (H_RECTABLE hTable, BYTE* pNewItem, T_SIZE NewItemLen);
extern T_INDEX	        RecMngr_Update           (H_RECTABLE hTable, T_INDEX Index, BYTE* pNewItem, T_SIZE NewItemLen);
extern BOOL	        RecMngr_Delete           (H_RECTABLE hTable, T_INDEX Index);
extern BOOL	        RecMngr_DeleteAll        (H_RECTABLE hTable);

extern T_CSTR	        RecMngr_GetTableName     (H_RECTABLE hTable);
extern T_ID	        RecMngr_GetTableID       (H_RECTABLE hTable);
extern T_POS	        RecMngr_GetKeyPos        (H_RECTABLE hTable);
extern T_SIZE	        RecMngr_GetKeyLen        (H_RECTABLE hTable);
extern T_NUM	        RecMngr_GetItemNum       (H_RECTABLE hTable);
extern T_SIZE           RecMngr_GetUsedSize      (H_RECTABLE hTable);			

extern T_ADDR	        RecMngr_GetDataAddr      (H_RECTABLE hTable, T_INDEX Index);
extern T_SIZE	        RecMngr_GetDataLen       (H_RECTABLE hTable, T_INDEX Index);
extern T_ADDR	        RecMngr_GetKeyAddr       (H_RECTABLE hTable, T_INDEX Index);
extern T_SIZE	        RecMngr_GetKeyData       (H_RECTABLE hTable, T_INDEX Index, BYTE* pBuf);
extern T_SIZE	        RecMngr_GetItemData      (H_RECTABLE hTable, T_INDEX Index, BYTE* pBuf, T_SIZE BufSize);
extern T_SIZE	        RecMngr_GetData          (H_RECTABLE hTable, T_INDEX Index, T_POS Pos, BYTE* pBuf, T_SIZE Len);

extern T_NUM	        RecMngr_GetRegionNum     (void);
extern T_SIZE	        RecMngr_GetRegionSize    (void);
extern BOOL	        RecMngr_GetRegionInfo    (T_INDEX Index, TRecRgnInfo* pRgnInfo);

extern T_SIZE	        RecMngr_GetTotalSize     (void);
extern T_SIZE	        RecMngr_GetTotalUsedSize (void);
extern T_SIZE	        RecMngr_GetTotalDelSize  (void);
extern T_SIZE	        RecMngr_GetTotalFreeSize (void);


#endif	//	_BNSOFT_RECMNGR_H_
