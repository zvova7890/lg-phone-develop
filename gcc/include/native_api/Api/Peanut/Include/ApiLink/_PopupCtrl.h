/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	PEANUT POPUP CONTROL APILINK

	Copyright(c) 1997-2003 BNSoft Corp.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT__PEANUT_POPUPCTRL_H_
#define		_BNSOFT__PEANUT_POPUPCTRL_H_

#include	"../PopupCtrl.h"

typedef H_CTRL			(*T_pfnPopupCtrl_Create)        (void* pOwner, QUAD Style, T_POS BaseX, T_POS BaseY);
typedef BOOL			(*T_pfnPopupCtrl_Destroy)       (H_CTRL hPC);
typedef BOOL			(*T_pfnPopupCtrl_SetBase)       (H_CTRL hPC, T_POS BaseX, T_POS BaseY);
typedef BOOL			(*T_pfnPopupCtrl_SetMaxHeight)  (H_CTRL hPC, T_SIZE MaxHeight);
typedef BOOL			(*T_pfnPopupCtrl_SetInitIndex)  (H_CTRL hPC, int InitIndex);
typedef BOOL			(*T_pfnPopupCtrl_SetIcon)       (H_CTRL hPC, int Index, QUAD Icon);
typedef BOOL			(*T_pfnPopupCtrl_SetLeftMargin) (H_CTRL hPC, int LeftMargin);
typedef int			(*T_pfnPopupCtrl_GetSelIndex)   (H_CTRL hPC);
typedef T_CSTR			(*T_pfnPopupCtrl_GetStr)        (H_CTRL hPC, int Index);
typedef T_CSTR			(*T_pfnPopupCtrl_GetSelStr)     (H_CTRL hPC);
typedef QUAD			(*T_pfnPopupCtrl_GetData)       (H_CTRL hPC, int Index);
typedef H_CTRL			(*T_pfnPopupCtrl_GetListHandle) (H_CTRL hPC);
typedef BOOL			(*T_pfnPopupCtrl_AddItem)       (H_CTRL hPC, T_CSTR pcszStr, QUAD Data, QUAD IconID);
typedef BOOL			(*T_pfnPopupCtrl_AddSeparator)  (H_CTRL hPC);
typedef BOOL			(*T_pfnPopupCtrl_AddPopup)      (H_CTRL hPC, T_CSTR pcszStr, QUAD IconID, H_CTRL hSubPC);
typedef BOOL			(*T_pfnPopupCtrl_DoModal)       (H_CTRL hPC);
typedef BOOL			(*T_pfnPopupCtrl_StopModal)     (void);
typedef BOOL			(*T_pfnPopupCtrl_EndModal)      (void);

typedef struct
{
	T_pfnPopupCtrl_Create			pfnCreate;
	T_pfnPopupCtrl_Destroy			pfnDestroy;
	T_pfnPopupCtrl_SetBase			pfnSetBase;
	T_pfnPopupCtrl_SetMaxHeight		pfnSetMaxHeight;
	T_pfnPopupCtrl_SetInitIndex		pfnSetInitIndex;
	T_pfnPopupCtrl_SetIcon			pfnSetIcon;
	T_pfnPopupCtrl_SetLeftMargin		pfnSetLeftMargin;
	T_pfnPopupCtrl_GetSelIndex		pfnGetSelIndex;
	T_pfnPopupCtrl_GetStr			pfnGetStr;
	T_pfnPopupCtrl_GetSelStr		pfnGetSelStr;
	T_pfnPopupCtrl_GetData			pfnGetData;
	T_pfnPopupCtrl_GetListHandle		pfnGetListHandle;
	T_pfnPopupCtrl_AddItem			pfnAddItem;
	T_pfnPopupCtrl_AddSeparator		pfnAddSeparator;
	T_pfnPopupCtrl_AddPopup			pfnAddPopup;
	T_pfnPopupCtrl_DoModal			pfnDoModal;
	T_pfnPopupCtrl_StopModal		pfnStopModal;
	T_pfnPopupCtrl_EndModal			pfnEndModal;
} TApiGrp_PopupCtrl;


#define	PopupCtrl_Create(p1,p2,p3,p4)			__ApiLink4(PopupCtrl,Create,p1,p2,p3,p4)
#define	PopupCtrl_Destroy(p1)				__ApiLink1(PopupCtrl,Destroy,p1)
#define	PopupCtrl_SetBase(p1,p2,p3)			__ApiLink3(PopupCtrl,SetBase,p1,p2,p3)
#define	PopupCtrl_SetMaxHeight(p1,p2)			__ApiLink2(PopupCtrl,SetMaxHeight,p1,p2)
#define	PopupCtrl_SetInitIndex(p1,p2)			__ApiLink2(PopupCtrl,SetInitIndex,p1,p2)
#define	PopupCtrl_SetIcon(p1,p2,p3)			__ApiLink3(PopupCtrl,SetIcon,p1,p2,p3)
#define	PopupCtrl_SetLeftMargin(p1,p2)			__ApiLink2(PopupCtrl,SetLeftMargin,p1,p2)
#define	PopupCtrl_GetSelIndex(p1)			__ApiLink1(PopupCtrl,GetSelIndex,p1)
#define	PopupCtrl_GetStr(p1,p2)				__ApiLink2(PopupCtrl,GetStr,p1,p2)
#define	PopupCtrl_GetSelStr(p1)				__ApiLink1(PopupCtrl,GetSelStr,p1)
#define	PopupCtrl_GetData(p1,p2)			__ApiLink2(PopupCtrl,GetData,p1,p2)
#define	PopupCtrl_GetListHandle(p1)			__ApiLink1(PopupCtrl,GetListHandle,p1)
#define	PopupCtrl_AddItem(p1,p2,p3,p4)			__ApiLink4(PopupCtrl,AddItem,p1,p2,p3,p4)
#define	PopupCtrl_AddSeparator(p1)			__ApiLink1(PopupCtrl,AddSeparator,p1)
#define	PopupCtrl_AddPopup(p1,p2,p3,p4)			__ApiLink4(PopupCtrl,AddPopup,p1,p2,p3,p4)
#define	PopupCtrl_DoModal(p1)				__ApiLink1(PopupCtrl,DoModal,p1)
#define	PopupCtrl_StopModal()				__ApiLink0(PopupCtrl,StopModal)
#define	PopupCtrl_EndModal()				__ApiLink0(PopupCtrl,EndModal)

#endif	//	_BNSOFT__PEANUT_POPUPCTRL_H_
