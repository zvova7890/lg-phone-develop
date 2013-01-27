/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	DYNAMIC LINKING LIBRARY

	Copyright(c) 1997-2002 BNSoft Corp.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT__LNKLIST_H_
#define		_BNSOFT__LNKLIST_H_

#include	"../LnkList.h"

typedef BOOL				(*T_pfnLnkList_Create)       (TLnkList* pLnkList, T_SIZE ObjSize, BOOL bDblLnkList);
typedef BOOL				(*T_pfnLnkList_Destroy)      (TLnkList* pLnkList);
typedef BOOL				(*T_pfnLnkList_SetObjPool)   (TLnkList* pLnkList, void* pObjPool, T_NUM DefObjNum);
typedef BOOL				(*T_pfnLnkList_InitObjPool)  (TLnkList* pLnkList);
typedef TLnkObj*			(*T_pfnLnkList_AllocObj)     (TLnkList* pLnkList);
typedef BOOL				(*T_pfnLnkList_FreeObj)      (TLnkObj* pObj);
typedef BOOL				(*T_pfnLnkList_AddHead)      (TLnkList* pLnkList, TLnkObj* pObj);
typedef BOOL				(*T_pfnLnkList_AddTail)      (TLnkList* pLnkList, TLnkObj* pObj);
typedef BOOL				(*T_pfnLnkList_InsertBefore) (TLnkList* pLnkList, TLnkObj* pObj, TLnkObj* pBase);
typedef BOOL				(*T_pfnLnkList_InsertAfter)  (TLnkList* pLnkList, TLnkObj* pObj, TLnkObj* pBase);
typedef TLnkObj*			(*T_pfnLnkList_RemoveHead)   (TLnkList* pLnkList);
typedef TLnkObj*			(*T_pfnLnkList_RemoveTail)   (TLnkList* pLnkList);
typedef BOOL				(*T_pfnLnkList_Remove)       (TLnkList* pLnkList, TLnkObj* pObj);
typedef BOOL		                (*T_pfnLnkList_RemoveAll)    (TLnkList* pLnkList);
typedef T_INDEX		                (*T_pfnLnkList_Find)         (TLnkList* pLnkList, TLnkObj* pObj);
typedef T_NUM			(       *T_pfnLnkList_GetNum)       (TLnkList* pLnkList);
typedef TLnkObj*		        (*T_pfnLnkList_GetObj)       (TLnkList* pLnkList, T_INDEX Index);

typedef struct
{
    T_pfnLnkList_Create                 pfnLnkList_Create;
    T_pfnLnkList_Destroy                pfnLnkList_Destroy;
    T_pfnLnkList_SetObjPool             pfnLnkList_SetObjPool;
    T_pfnLnkList_InitObjPool            pfnLnkList_InitObjPool;
    T_pfnLnkList_AllocObj               pfnLnkList_AllocObj;
    T_pfnLnkList_FreeObj                pfnLnkList_FreeObj;
    T_pfnLnkList_AddHead                pfnLnkList_AddHead;
    T_pfnLnkList_AddTail                pfnLnkList_AddTail;
    T_pfnLnkList_InsertBefore           pfnLnkList_InsertBefore;
    T_pfnLnkList_InsertAfter            pfnLnkList_InsertAfter;
    T_pfnLnkList_RemoveHead             pfnLnkList_RemoveHead;
    T_pfnLnkList_RemoveTail             pfnLnkList_RemoveTail;
    T_pfnLnkList_Remove                 pfnLnkList_Remove;
    T_pfnLnkList_RemoveAll              pfnLnkList_RemoveAll;
    T_pfnLnkList_Find                   pfnLnkList_Find;
    T_pfnLnkList_GetNum			pfnLnkList_GetNum;
   T_pfnLnkList_GetObj			pfnLnkList_GetObj;
} TApiGrp_LnkList;


#define		LnkList_Create(p1,p2,p3)            __ApiLink3(LnkList,LnkList_Create,p1,p2,p3)
#define		LnkList_Destroy(p1)                 __ApiLink1(LnkList,LnkList_Destroy,p1)
#define		LnkList_SetObjPool(p1,p2,p3)        __ApiLink3(LnkList,LnkList_SetObjPool,p1,p2,p3)
#define		LnkList_InitObjPool(p1)             __ApiLink1(LnkList,LnkList_InitObjPool,p1)
#define		LnkList_AllocObj(p1)                __ApiLink1(LnkList,LnkList_AllocObj,p1)
#define		LnkList_FreeObj(p1)                 __ApiLink1(LnkList,LnkList_FreeObj,p1)
#define		LnkList_AddHead(p1,p2)              __ApiLink2(LnkList,LnkList_AddHead,p1,p2)
#define		LnkList_AddTail(p1,p2)              __ApiLink2(LnkList,LnkList_AddTail,p1,p2)
#define		LnkList_InsertBefore(p1,p2,p3)      __ApiLink3(LnkList,LnkList_InsertBefore,p1,p2,p3)
#define		LnkList_InsertAfter(p1,p2,p3)       __ApiLink3(LnkList,LnkList_InsertAfter,p1,p2,p3)
#define		LnkList_RemoveHead(p1)              __ApiLink1(LnkList,LnkList_RemoveHead,p1)
#define		LnkList_RemoveTail(p1)              __ApiLink1(LnkList,LnkList_RemoveTail,p1)
#define		LnkList_Remove(p1,p2)               __ApiLink2(LnkList,LnkList_Remove,p1,p2)
#define		LnkList_RemoveAll(p1)               __ApiLink1(LnkList,LnkList_RemoveAll,p1)
#define		LnkList_Find(p1,p2)                 __ApiLink2(LnkList,LnkList_Find,p1,p2)
#define		LnkList_GetNum(p1)                  __ApiLink1(LnkList,LnkList_GetNum,p1)
#define		LnkList_GetObj(p1,p2)               __ApiLink2(LnkList,LnkList_GetObj,p1,p2)

#endif	//	_BNSOFT__LNKLIST_H_
