/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	PEANUT IMAGE CONTROL APILINK

	Copyright(c) 1997-2002 BNSoft Corp.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT__PEANUT_IMGCTRL_H_
#define		_BNSOFT__PEANUT_IMGCTRL_H_

#include	"../ImgCtrl.h"

typedef H_CTRL			(*T_pfnImgCtrl_Create)         (void* pOwner, T_POS X, T_POS Y, T_SIZE W, T_SIZE H, T_CSTR pcszFileName);
typedef BOOL			(*T_pfnImgCtrl_Destroy)        (H_CTRL hIC);
typedef BOOL			(*T_pfnImgCtrl_SetImage)       (H_CTRL hIC, T_CSTR pcszFileName);
typedef BOOL			(*T_pfnImgCtrl_SetBkMode)      (H_CTRL hIC, int Mode);
typedef BOOL			(*T_pfnImgCtrl_SetAlign)       (H_CTRL hIC, int Align);
typedef int			(*T_pfnImgCtrl_GetImageType)   (H_CTRL hIC);
typedef T_SIZE			(*T_pfnImgCtrl_GetImageWidth)  (H_CTRL hIC);
typedef T_SIZE			(*T_pfnImgCtrl_GetImageHeight) (H_CTRL hIC);
typedef T_NUM			(*T_pfnImgCtrl_GetFrameNum)    (H_CTRL hIC);
typedef T_INDEX			(*T_pfnImgCtrl_GetFrameIndex)  (H_CTRL hIC);
typedef int			(*T_pfnImgCtrl_GetBkMode)      (H_CTRL hIC);
typedef int			(*T_pfnImgCtrl_GetAlign)       (H_CTRL hIC);

typedef struct
{
	T_pfnImgCtrl_Create					pfnCreate;
	T_pfnImgCtrl_Destroy				pfnDestroy;
	T_pfnImgCtrl_SetImage				pfnSetImage;
	T_pfnImgCtrl_SetBkMode				pfnSetBkMode;
	T_pfnImgCtrl_SetAlign				pfnSetAlign;
	T_pfnImgCtrl_GetImageType			pfnGetImageType;
	T_pfnImgCtrl_GetImageWidth			pfnGetImageWidth;
	T_pfnImgCtrl_GetImageHeight			pfnGetImageHeight;
	T_pfnImgCtrl_GetFrameNum			pfnGetFrameNum;
	T_pfnImgCtrl_GetFrameIndex			pfnGetFrameIndex;
	T_pfnImgCtrl_GetBkMode				pfnGetBkMode;
	T_pfnImgCtrl_GetAlign				pfnGetAlign;
} TApiGrp_ImgCtrl;


#define		ImgCtrl_Create(p1,p2,p3,p4,p5,p6)		__ApiLink6(ImgCtrl,Create,p1,p2,p3,p4,p5,p6)
#define		ImgCtrl_Destroy(p1)				__ApiLink1(ImgCtrl,Destroy,p1)
#define		ImgCtrl_SetImage(p1,p2)				__ApiLink2(ImgCtrl,SetImage,p1,p2)
#define		ImgCtrl_SetBkMode(p1,p2)			__ApiLink2(ImgCtrl,SetBkMode,p1,p2)
#define		ImgCtrl_SetAlign(p1,p2)				__ApiLink2(ImgCtrl,SetAlign,p1,p2)
#define		ImgCtrl_GetImageType(p1)			__ApiLink1(ImgCtrl,GetImageType,p1)
#define		ImgCtrl_GetImageWidth(p1)			__ApiLink1(ImgCtrl,GetImageWidth,p1)
#define		ImgCtrl_GetImageHeight(p1)			__ApiLink1(ImgCtrl,GetImageHeight,p1)
#define		ImgCtrl_GetFrameNum(p1)				__ApiLink1(ImgCtrl,GetFrameNum,p1)
#define		ImgCtrl_GetFrameIndex(p1)			__ApiLink1(ImgCtrl,GetFrameIndex,p1)
#define		ImgCtrl_GetBkMode(p1)				__ApiLink1(ImgCtrl,GetBkMode,p1)
#define		ImgCtrl_GetAlign(p1)				__ApiLink1(ImgCtrl,GetAlign,p1)


#endif	//	_BNSOFT__PEANUT_IMGCTRL_H_
