/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	PEANUT ICON CONTROL APILINK

	Copyright(c) 1997-2002 BNSoft Corp.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT__PEANUT_ICONCTRL_H_
#define		_BNSOFT__PEANUT_ICONCTRL_H_

#include	"../IconCtrl.h"

typedef H_CTRL			(*T_pfnIconCtrl_Create)          (void* pOwner, T_POS X, T_POS Y, TImage* pImage);
typedef BOOL			(*T_pfnIconCtrl_Destroy)         (H_CTRL hIC);
typedef BOOL			(*T_pfnIconCtrl_SetImage)        (H_CTRL hIC, int Index, TImage* pImage);
typedef BOOL			(*T_pfnIconCtrl_AddImage)        (H_CTRL hIC, TImage* pImage);
typedef BOOL			(*T_pfnIconCtrl_SetBkMode)       (H_CTRL hIC, int Mode);
typedef TImage*			(*T_pfnIconCtrl_GetImage)        (H_CTRL hIC, int Index);
typedef T_NUM			(*T_pfnIconCtrl_GetImageNum)     (H_CTRL hIC);
typedef int			(*T_pfnIconCtrl_GetSelIndex)     (H_CTRL hIC);
typedef TImage*			(*T_pfnIconCtrl_GetSelImage)     (H_CTRL hIC);
typedef int			(*T_pfnIconCtrl_GetBkMode)       (H_CTRL hIC);
typedef BOOL			(*T_pfnIconCtrl_SelectImage)     (H_CTRL hIC, int Index);
typedef BOOL			(*T_pfnIconCtrl_SelectNextImage) (H_CTRL hIC);
typedef BOOL			(*T_pfnIconCtrl_SelectPrevImage) (H_CTRL hIC);

typedef struct
{
	T_pfnIconCtrl_Create			pfnCreate;
	T_pfnIconCtrl_Destroy			pfnDestroy;
	T_pfnIconCtrl_SetImage			pfnSetImage;
	T_pfnIconCtrl_AddImage			pfnAddImage;
	T_pfnIconCtrl_SetBkMode			pfnSetBkMode;
	T_pfnIconCtrl_GetImage			pfnGetImage;
	T_pfnIconCtrl_GetImageNum		pfnGetImageNum;
	T_pfnIconCtrl_GetSelIndex		pfnGetSelIndex;
	T_pfnIconCtrl_GetSelImage		pfnGetSelImage;
	T_pfnIconCtrl_GetBkMode			pfnGetBkMode;
	T_pfnIconCtrl_SelectImage		pfnSelectImage;
	T_pfnIconCtrl_SelectNextImage		pfnSelectNextImage;
	T_pfnIconCtrl_SelectPrevImage		pfnSelectPrevImage;
} TApiGrp_IconCtrl;


#define		IconCtrl_Create(p1,p2,p3,p4)		__ApiLink4(IconCtrl,Create,p1,p2,p3,p4)
#define		IconCtrl_Destroy(p1)			__ApiLink1(IconCtrl,Destroy,p1)
#define		IconCtrl_SetImage(p1,p2,p3)		__ApiLink3(IconCtrl,SetImage,p1,p2,p3)
#define		IconCtrl_AddImage(p1,p2)		__ApiLink2(IconCtrl,AddImage,p1,p2)
#define		IconCtrl_SetBkMode(p1,p2)		__ApiLink2(IconCtrl,SetBkMode,p1,p2)
#define		IconCtrl_GetImage(p1,p2)		__ApiLink2(IconCtrl,GetImage,p1,p2)
#define		IconCtrl_GetImageNum(p1)		__ApiLink1(IconCtrl,GetImageNum,p1)
#define		IconCtrl_GetSelIndex(p1)		__ApiLink1(IconCtrl,GetSelIndex,p1)
#define		IconCtrl_GetSelImage(p1)		__ApiLink1(IconCtrl,GetSelImage,p1)
#define		IconCtrl_GetBkMode(p1)			__ApiLink1(IconCtrl,GetBkMode,p1)
#define		IconCtrl_SelectImage(p1,p2)		__ApiLink2(IconCtrl,SelectImage,p1,p2)
#define		IconCtrl_SelectNextImage(p1)		__ApiLink1(IconCtrl,SelectNextImage,p1)
#define		IconCtrl_SelectPrevImage(p1)		__ApiLink1(IconCtrl,SelectPrevImage,p1)

#endif	//	_BNSOFT__PEANUT_ICONCTRL_H_
