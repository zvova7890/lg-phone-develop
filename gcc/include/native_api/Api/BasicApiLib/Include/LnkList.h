/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	LINKED LIST

	Copyright(c) 1997-2002 BNSoft Corp.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT_LNKLIST_H_
#define		_BNSOFT_LNKLIST_H_

#include	"Include.h"

//	Definitions
#define		LNKOBJ_FREE			0
#define		LNKOBJ_OCCUPIED			1
#define		LNKOBJ_EXTERN			2
#define		LNKOBJ_EXTERNOCCUPIED		(LNKOBJ_EXTERN | LNKOBJ_OCCUPIED)

//	Definition of LnkObj (Single Linked List)
typedef struct _TSLnkObj
{
	QUAD			Flag;
	struct _TSLnkObj*	pNext;
} TSLnkObj;

//	Definition of LnkObj (Double Linked List)
typedef struct _TDLnkObj
{
	QUAD			Flag;
	struct _TDLnkObj*	pNext;
	struct _TDLnkObj*	pPrev;
} TDLnkObj;

typedef		TDLnkObj	TLnkObj;

//	Definition of LnkList
typedef struct
{
	void*				pObjPool;
	T_NUM				DefObjNum;
	T_SIZE				ObjSize;
	BOOL				bDblLnkList;
	TLnkObj*			pHeadObj;
	TLnkObj*			pTailObj;
} TLnkList;


extern BOOL		LnkList_Create       (TLnkList* pLnkList, T_SIZE ObjSize, BOOL bDblLnkList);
extern BOOL		LnkList_Destroy      (TLnkList* pLnkList);

extern BOOL		LnkList_SetObjPool   (TLnkList* pLnkList, void* pObjPool, T_NUM DefObjNum);
extern BOOL		LnkList_InitObjPool  (TLnkList* pLnkList);

extern TLnkObj*		LnkList_AllocObj     (TLnkList* pLnkList);
extern BOOL		LnkList_FreeObj      (TLnkObj* pObj);

extern BOOL		LnkList_AddHead      (TLnkList* pLnkList, TLnkObj* pObj);
extern BOOL		LnkList_AddTail      (TLnkList* pLnkList, TLnkObj* pObj);
extern BOOL		LnkList_InsertBefore (TLnkList* pLnkList, TLnkObj* pObj, TLnkObj* pBase);
extern BOOL		LnkList_InsertAfter  (TLnkList* pLnkList, TLnkObj* pObj, TLnkObj* pBase);
extern TLnkObj*		LnkList_RemoveHead   (TLnkList* pLnkList);
extern TLnkObj*		LnkList_RemoveTail   (TLnkList* pLnkList);
extern BOOL		LnkList_Remove       (TLnkList* pLnkList, TLnkObj* pObj);
extern BOOL		LnkList_RemoveAll    (TLnkList* pLnkList);

extern T_INDEX		LnkList_Find         (TLnkList* pLnkList, TLnkObj* pObj);
extern T_NUM		LnkList_GetNum       (TLnkList* pLnkList);
extern TLnkObj*		LnkList_GetObj       (TLnkList* pLnkList, T_INDEX Index);
extern TLnkObj*		LnkList_GetNext      (TLnkList* pLnkList, TLnkObj* pBase);
extern TLnkObj*		LnkList_GetPrev      (TLnkList* pLnkList, TLnkObj* pBase);


#endif	//	_BNSOFT_LNKLIST_H_
