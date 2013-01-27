/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	PEANUT TAB CONTROL APILINK

	Copyright(c) 1997-2003 BNSoft Corp.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT__PEANUT_TABCTRL_H_
#define		_BNSOFT__PEANUT_TABCTRL_H_

#include	"../TabCtrl.h"

typedef H_CTRL			(*T_pfnTabCtrl_Create)        (void* pOwner, T_POS X, T_POS Y, T_SIZE W, T_SIZE H);
typedef BOOL			(*T_pfnTabCtrl_Destroy)       (H_CTRL hTC);
typedef H_CTRL			(*T_pfnTabCtrl_CreateDlgTab)  (H_CTRL hTC, T_CSTR rcszTitle);
typedef H_CTRL			(*T_pfnTabCtrl_CreateEditTab) (H_CTRL hTC, T_CSTR rcszTitle, T_NUM MaxChar);
typedef H_CTRL			(*T_pfnTabCtrl_CreateListTab) (H_CTRL hTC, T_CSTR rcszTitle);
typedef H_CTRL			(*T_pfnTabCtrl_CreateTextTab) (H_CTRL hTC, T_CSTR rcszTitle, T_CSTR pcszText);

typedef struct
{
	T_pfnTabCtrl_Create				pfnCreate;
	T_pfnTabCtrl_Destroy				pfnDestroy;
	T_pfnTabCtrl_CreateDlgTab			pfnCreateDlgTab;
	T_pfnTabCtrl_CreateEditTab			pfnCreateEditTab;
	T_pfnTabCtrl_CreateListTab			pfnCreateListTab;
	T_pfnTabCtrl_CreateTextTab			pfnCreateTextTab;
} TApiGrp_TabCtrl;


#define	TabCtrl_Create(p1,p2,p3,p4,p5)			__ApiLink5(TabCtrl,Create,p1,p2,p3,p4,p5)
#define	TabCtrl_Destroy(p1)				__ApiLink1(TabCtrl,Destroy,p1)
#define	TabCtrl_CreateDlgTab(p1,p2)			__ApiLink2(TabCtrl,CreateDlgTab,p1,p2)
#define	TabCtrl_CreateEditTab(p1,p2,p3)			__ApiLink3(TabCtrl,CreateEditTab,p1,p2,p3)
#define	TabCtrl_CreateListTab(p1,p2)			__ApiLink2(TabCtrl,CreateListTab,p1,p2)
#define	TabCtrl_CreateTextTab(p1,p2,p3)			__ApiLink3(TabCtrl,CreateTextTab,p1,p2,p3)


#endif	//	_BNSOFT__PEANUT_TABCTRL_H_
