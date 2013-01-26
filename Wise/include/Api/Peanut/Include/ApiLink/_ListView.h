/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	PEANUT LIST VIEW CONTROL APILINK

	Copyright(c)     -2007 LG Electronics.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT__PEANUT_LISTVIEW_H_
#define		_BNSOFT__PEANUT_LISTVIEW_H_

#include	"../ListView.h"

typedef H_CTRL				(*T_pfnListView_Create)              (void* pOwner, T_POS X, T_POS Y, T_SIZE W, T_SIZE H);
typedef BOOL				(*T_pfnListView_Destroy)             (H_CTRL hLV);
typedef BOOL				(*T_pfnListView_SetLineGap)          (H_CTRL hLV, int LineGap);
typedef BOOL				(*T_pfnListView_SetInvOffset)        (H_CTRL hLV, int InvOffset);
typedef BOOL				(*T_pfnListView_SetListDeltaX1)      (H_CTRL hLV, int DeltaX1);
typedef BOOL				(*T_pfnListView_SetListDeltaX2)      (H_CTRL hLV, int DeltaX2);
typedef BOOL				(*T_pfnListView_SetDefItemHeight)    (H_CTRL hLV, T_SIZE DefHeight);
typedef BOOL				(*T_pfnListView_SetVItemHeight)	     (H_CTRL hLV, T_SIZE VHeight);
typedef int				(*T_pfnListView_GetLineGap)          (H_CTRL hLV);
typedef int				(*T_pfnListView_GetInvOffset)        (H_CTRL hLV);
typedef int				(*T_pfnListView_GetListDeltaX1)      (H_CTRL hLV);
typedef int				(*T_pfnListView_GetListDeltaX2)      (H_CTRL hLV);
typedef T_NUM				(*T_pfnListView_GetDefItemHeight)    (H_CTRL hLV);
typedef T_NUM				(*T_pfnListView_GetVItemHeight)	      (H_CTRL hLV);
typedef T_NUM				(*T_pfnListView_GetItemNum)          (H_CTRL hLV);
typedef T_INDEX				(*T_pfnListView_GetSelIndex)         (H_CTRL hLV);
typedef TListViewItem*		        (*T_pfnListView_GetSelItem)          (H_CTRL hLV);
typedef T_INDEX				(*T_pfnListView_GetItemIndex)        (H_CTRL hLV, TListViewItem* pListViewItem);
typedef T_SIZE				(*T_pfnListView_GetTotalHeight)      (H_CTRL hLV);
typedef BOOL				(*T_pfnListView_ResetAllItems)       (H_CTRL hLV);
typedef BOOL				(*T_pfnListView_ResetTicker)         (H_CTRL hLV);
typedef BOOL				(*T_pfnListView_Sort)                (H_CTRL hLV, T_pfnSortItem pfnCustomSortFunc);
typedef BOOL				(*T_pfnListView_SetViewMode)         (H_CTRL hLV, E_LISTVMODE ViewMode);
typedef E_LISTVMODE			(*T_pfnListView_GetViewMode)         (H_CTRL hLV);
typedef BOOL				(*T_pfnListView_SetGridItemH)        (H_CTRL hLV, T_SIZE GridItemH);
typedef BOOL				(*T_pfnListView_SetGridItemW)        (H_CTRL hLV, T_SIZE GridItemW);
typedef BOOL				(*T_pfnListView_SetColumnNum)        (H_CTRL hLV, T_NUM  ColumnNum);
typedef BOOL				(*T_pfnListView_SetStr)              (H_CTRL hLV, T_INDEX Index, T_CSTR pcszStr);
typedef BOOL				(*T_pfnListView_SetwData)            (H_CTRL hLV, T_INDEX Index, QUAD wData);
typedef BOOL				(*T_pfnListView_SetlData)            (H_CTRL hLV, T_INDEX Index, QUAD lData);
typedef BOOL				(*T_pfnListView_SetItemHeight)       (H_CTRL hLV, T_INDEX Index, T_SIZE ItemHeight);
typedef TListViewItem*		        (*T_pfnListView_GetItem)             (H_CTRL hLV, T_INDEX Index);
typedef T_CSTR			  	(*T_pfnListView_GetStr)              (H_CTRL hLV, T_INDEX Index);
typedef BOOL				(*T_pfnListView_GetwData)            (H_CTRL hLV, T_INDEX Index, QUAD* pwData);
typedef BOOL				(*T_pfnListView_GetlData)            (H_CTRL hLV, T_INDEX Index, QUAD* plData);
typedef BOOL				(*T_pfnListView_GetStatus)           (H_CTRL hLV, T_INDEX Index, WORD* pStatus);
typedef T_INDEX				(*T_pfnListView_AddItem)             (H_CTRL hLV, T_CSTR pcszStr, QUAD wData, QUAD lData);
typedef BOOL				(*T_pfnListView_InsertItem)          (H_CTRL hLV, T_INDEX Index, T_CSTR pcszStr, QUAD wData, QUAD lData);
typedef BOOL				(*T_pfnListView_DeleteItem)          (H_CTRL hLV, T_INDEX Index);
typedef BOOL				(*T_pfnListView_SelectItem)          (H_CTRL hLV, T_INDEX Index);
typedef BOOL				(*T_pfnListView_AddSeparator)        (H_CTRL hLV, T_INDEX Index);
typedef BOOL				(*T_pfnListView_SetStatus)           (H_CTRL hLV, T_INDEX Index, WORD Status);
typedef BOOL				(*T_pfnListView_EnableItem)          (H_CTRL hLV, T_INDEX Index, BOOL bEnable);
typedef BOOL				(*T_pfnListView_EnsureVisible)       (H_CTRL hLV, T_INDEX Index);
typedef BOOL				(*T_pfnListView_AttachItems)         (H_CTRL hLV, TLnkList* pItemList);
typedef BOOL				(*T_pfnListView_MoveItem)	     (H_CTRL hLV, T_INDEX Index, T_INDEX MoveIndex);
typedef	BOOL				(*T_pfnListView_SetItemCtrl)	     (H_CTRL hLV, T_INDEX Index, T_ID ID, H_CTRL hCtrl);
typedef	H_CTRL				(*T_pfnListView_GetItemCtrl)	     (H_CTRL hLV, T_INDEX Index, T_ID ID);

typedef struct
{
	T_pfnListView_Create             pfnCreate;             
	T_pfnListView_Destroy            pfnDestroy;            
	T_pfnListView_SetLineGap         pfnSetLineGap;         
	T_pfnListView_SetInvOffset       pfnSetInvOffset;       
	T_pfnListView_SetListDeltaX1     pfnSetListDeltaX1;     
	T_pfnListView_SetListDeltaX2     pfnSetListDeltaX2;     
	T_pfnListView_SetDefItemHeight   pfnSetDefItemHeight;   
	T_pfnListView_SetVItemHeight	 pfnSetVItemHeight;   
	T_pfnListView_GetLineGap         pfnGetLineGap;        
	T_pfnListView_GetInvOffset       pfnGetInvOffset ;      
	T_pfnListView_GetListDeltaX1     pfnGetListDeltaX1;     
	T_pfnListView_GetListDeltaX2     pfnGetListDeltaX2;     
	T_pfnListView_GetDefItemHeight   pfnGetDefItemHeight;   
	T_pfnListView_GetVItemHeight	 pfnGetVItemHeight;   
	T_pfnListView_GetItemNum         pfnGetItemNum;         
	T_pfnListView_GetSelIndex        pfnGetSelIndex;
	T_pfnListView_GetSelItem         pfnGetSelItem;
	T_pfnListView_GetItemIndex	 pfnGetItemIndex;
	T_pfnListView_GetTotalHeight     pfnGetTotalHeight ;    
	T_pfnListView_ResetAllItems      pfnResetAllItems;      
	T_pfnListView_ResetTicker        pfnResetTicker;        
	T_pfnListView_Sort               pfnSort ;              
	T_pfnListView_SetViewMode        pfnSetViewMode ;       
	T_pfnListView_GetViewMode        pfnGetViewMode ;       
	T_pfnListView_SetGridItemH       pfnSetGridItemH;       
	T_pfnListView_SetGridItemW       pfnSetGridItemW;       
	T_pfnListView_SetColumnNum       pfnSetColumnNum  ;     
	T_pfnListView_SetStr             pfnSetStr ;            
	T_pfnListView_SetwData           pfnSetwData ;          
	T_pfnListView_SetlData           pfnSetlData ;          
	T_pfnListView_SetItemHeight      pfnSetItemHeight ;     
	T_pfnListView_GetItem            pfnGetItem  ;          
	T_pfnListView_GetStr             pfnGetStr;             
	T_pfnListView_GetwData           pfnGetwData;           
	T_pfnListView_GetlData           pfnGetlData  ;         
	T_pfnListView_GetStatus          pfnGetStatus  ;        
	T_pfnListView_AddItem            pfnAddItem ;           
	T_pfnListView_InsertItem         pfnInsertItem;         
	T_pfnListView_DeleteItem         pfnDeleteItem ;        
	T_pfnListView_SelectItem         pfnSelectItem ;        
	T_pfnListView_AddSeparator       pfnAddSeparator ;      
	T_pfnListView_SetStatus          pfnSetStatus ;        
	T_pfnListView_EnableItem         pfnEnableItem ;        
	T_pfnListView_EnsureVisible      pfnEnsureVisible;
	T_pfnListView_AttachItems        pfnAttachItems;
	T_pfnListView_MoveItem		 pfnMoveItem;
	T_pfnListView_SetItemCtrl	 pfnSetItemCtrl;
	T_pfnListView_GetItemCtrl	 pfnGetItemCtrl;
} TApiGrp_ListView;


#define		ListView_Create(p1,p2,p3,p4,p5)              __ApiLink5(ListView,Create,p1,p2,p3,p4,p5)
#define		ListView_Destroy(p1)                         __ApiLink1(ListView,Destroy,p1)
#define		ListView_SetLineGap(p1,p2)                   __ApiLink2(ListView,SetLineGap,p1,p2)
#define		ListView_SetInvOffset(p1,p2)                 __ApiLink2(ListView,SetInvOffset,p1,p2)
#define		ListView_SetListDeltaX1(p1,p2)               __ApiLink2(ListView,SetListDeltaX1,p1,p2)
#define		ListView_SetListDeltaX2(p1,p2)               __ApiLink2(ListView,SetListDeltaX2,p1,p2)
#define		ListView_SetDefItemHeight(p1,p2)             __ApiLink2(ListView,SetDefItemHeight,p1,p2)
#define		ListView_SetVItemHeight(p1,p2)	             __ApiLink2(ListView,SetVItemHeight,p1,p2)
#define		ListView_GetLineGap(p1)                      __ApiLink1(ListView,GetLineGap,p1)
#define		ListView_GetInvOffset(p1)                    __ApiLink1(ListView,GetInvOffset,p1)
#define		ListView_GetListDeltaX1(p1)                  __ApiLink1(ListView,GetListDeltaX1,p1)
#define		ListView_GetListDeltaX2(p1)                  __ApiLink1(ListView,GetListDeltaX2,p1)
#define		ListView_GetDefItemHeight(p1)                __ApiLink1(ListView,GetDefItemHeight,p1)
#define		ListView_GetVItemHeight(p1)	             __ApiLink1(ListView,GetVItemHeight,p1)
#define		ListView_GetItemNum(p1)                      __ApiLink1(ListView,GetItemNum,p1)
#define		ListView_GetSelIndex(p1)                     __ApiLink1(ListView,GetSelIndex,p1)
#define		ListView_GetSelItem(p1)                      __ApiLink1(ListView,GetSelItem,p1)
#define		ListView_GetItemIndex(p1,p2)		     __ApiLink2(ListView,GetItemIndex,p1,p2)
#define		ListView_GetTotalHeight(p1)                  __ApiLink1(ListView,GetTotalHeight,p1)
#define		ListView_ResetAllItems(p1)                   __ApiLink1(ListView,ResetAllItems,p1)
#define		ListView_ResetTicker(p1)                     __ApiLink1(ListView,ResetTicker,p1)
#define		ListView_Sort(p1,p2)                         __ApiLink2(ListView,Sort,p1,p2)
#define		ListView_SetViewMode(p1,p2)                  __ApiLink2(ListView,SetViewMode,p1,p2)
#define		ListView_GetViewMode(p1)                     __ApiLink1(ListView,GetViewMode,p1)
#define		ListView_SetGridItemH(p1,p2)                 __ApiLink2(ListView,SetGridItemH,p1,p2)
#define		ListView_SetGridItemW(p1,p2)                 __ApiLink2(ListView,SetGridItemW,p1,p2)
#define		ListView_SetColumnNum(p1,p2)                 __ApiLink2(ListView,SetColumnNum,p1,p2)
#define		ListView_SetStr(p1,p2,p3)                    __ApiLink3(ListView,SetStr,p1,p2,p3)
#define		ListView_SetwData(p1,p2,p3)                  __ApiLink3(ListView,SetwData,p1,p2,p3)
#define		ListView_SetlData(p1,p2,p3)                  __ApiLink3(ListView,SetlData,p1,p2,p3)
#define		ListView_SetItemHeight(p1,p2,p3)             __ApiLink3(ListView,SetItemHeight,p1,p2,p3)
#define		ListView_GetItem(p1,p2)                      __ApiLink2(ListView,GetItem,p1,p2)
#define		ListView_GetStr(p1,p2)                       __ApiLink2(ListView,GetStr,p1,p2)
#define		ListView_GetwData(p1,p2,p3)                  __ApiLink3(ListView,GetwData,p1,p2,p3)
#define		ListView_GetlData(p1,p2,p3)                  __ApiLink3(ListView,GetlData,p1,p2,p3)
#define		ListView_GetStatus(p1,p2,p3)                 __ApiLink3(ListView,GetStatus,p1,p2,p3)
#define		ListView_AddItem(p1,p2,p3,p4)                __ApiLink4(ListView,AddItem,p1,p2,p3,p4)
#define		ListView_InsertItem(p1,p2,p3,p4,p5)          __ApiLink5(ListView,InsertItem,p1,p2,p3,p4,p5)
#define		ListView_DeleteItem(p1,p2)                   __ApiLink2(ListView,DeleteItem,p1,p2)
#define		ListView_SelectItem(p1,p2)                   __ApiLink2(ListView,SelectItem,p1,p2)
#define		ListView_AddSeparator(p1,p2)                 __ApiLink2(ListView,AddSeparator,p1,p2)
#define		ListView_SetStatus(p1,p2,p3)                 __ApiLink3(ListView,SetStatus,p1,p2,p3)
#define		ListView_EnableItem(p1,p2,p3)                __ApiLink3(ListView,EnableItem,p1,p2,p3)
#define		ListView_EnsureVisible(p1,p2)                __ApiLink2(ListView,EnsureVisible,p1,p2)
#define		ListView_AttachItems(p1,p2)                  __ApiLink2(ListView,AttachItems,p1,p2)
#define		ListView_MoveItem(p1,p2,p3)		     __ApiLink3(ListView,MoveItem,p1,p2,p3)
#define		ListView_SetItemCtrl(p1,p2,p3,p4)	     __ApiLink4(ListView,SetItemCtrl,p1,p2,p3,p4)
#define		ListView_GetItemCtrl(p1,p2,p3)		     __ApiLink3(ListView,GetItemCtrl,p1,p2,p3)


#endif	//	_BNSOFT__PEANUT_LISTVIEW_H_
