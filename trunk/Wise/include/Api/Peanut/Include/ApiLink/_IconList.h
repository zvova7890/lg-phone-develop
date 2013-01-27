/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	PEANUT ICON LIST APILINK

	Copyright(c) 1997-2003 BNSoft Corp.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT__PEANUT_ICONLIST_H_
#define		_BNSOFT__PEANUT_ICONLIST_H_

#include	"../IconList.h"

typedef H_CTRL		(*T_pfnIconList_Create)         (void);
typedef BOOL		(*T_pfnIconList_Destroy)        (H_CTRL hIL);
typedef BOOL		(*T_pfnIconList_ResetAllImages) (H_CTRL hIL);
typedef int		(*T_pfnIconList_AddImage)       (H_CTRL hIL, TImage* pImage, TImage* pLargeImage);
typedef BOOL		(*T_pfnIconList_RemoveImage)    (H_CTRL hIL, int nIndex);
typedef TImage*		(*T_pfnIconList_GetImage)       (H_CTRL hIL, int nIndex);
typedef TImage*		(*T_pfnIconList_GetLargeImage)  (H_CTRL hIL, int nIndex);

typedef struct
{
	T_pfnIconList_Create				pfnCreate;
	T_pfnIconList_Destroy				pfnDestroy;
	T_pfnIconList_ResetAllImages		        pfnResetAllImages;
	T_pfnIconList_AddImage				pfnAddImage;
	T_pfnIconList_RemoveImage			pfnRemoveImage;
	T_pfnIconList_GetImage				pfnGetImage;
	T_pfnIconList_GetLargeImage			pfnGetLargeImage;
} TApiGrp_IconList;


#define		IconList_Create()			__ApiLink0(IconList,Create)
#define		IconList_Destroy(p1)			__ApiLink1(IconList,Destroy,p1)
#define		IconList_ResetAllImages(p1)		__ApiLink1(IconList,ResetAllImages,p1)
#define		IconList_AddImage(p1,p2,p3)		__ApiLink3(IconList,AddImage,p1,p2,p3)
#define		IconList_RemoveImage(p1,p2)		__ApiLink2(IconList,RemoveImage,p1,p2)
#define		IconList_GetImage(p1,p2)		__ApiLink2(IconList,GetImage,p1,p2)
#define		IconList_GetLargeImage(p1,p2)		__ApiLink2(IconList,GetLargeImage,p1,p2)


#endif	//	_BNSOFT__PEANUT_ICONLIST_H_
