/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	DYNAMIC LINKING LIBRARY

	Copyright(c) 1997-2002 BNSoft Corp.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT__GRIMAGE_H_
#define		_BNSOFT__GRIMAGE_H_

#include	"../GrImage.h"

//-------------------------------------------------------------------------------------------------
typedef TGrImage*		(*T_pfnGrImage_Create)         (E_IMAGETYPE enImageType, void* pData);
typedef BOOL			(*T_pfnGrImage_Destroy)        (TGrImage* pGrImg);
typedef BOOL			(*T_pfnGrImage_Make)           (TGrImage* pGrImg, int FrameIndex);
typedef BOOL			(*T_pfnGrImage_Draw)           (TGrImage* pGrImg, T_POS X, T_POS Y);
typedef BOOL			(*T_pfnGrImage_GetInfo)        (E_IMAGETYPE enImageType, void* pData, TGrImgInfo* pGrImgInfo);
typedef T_SIZE			(*T_pfnGrImage_Save)           (E_IMAGETYPE enImageType, void* pData, T_POS X, T_POS Y, T_SIZE W, T_SIZE H, T_SIZE BufSize);
typedef T_SIZE			(*T_pfnGrImage_GetSaveBufSize) (E_IMAGETYPE enImageType, T_POS X, T_POS Y, T_SIZE W, T_SIZE H);
typedef BOOL			(*T_pfnGrImage_MakeEx)         (TGrImage* pGrImg, void* pImage, int FrameIndex, int OutputColorbit);

//-------------------------------------------------------------------------------------------------
typedef struct
{
	T_pfnGrImage_Create					pfnCreate;
	T_pfnGrImage_Destroy				pfnDestroy;
	T_pfnGrImage_Make					pfnMake;
	T_pfnGrImage_Draw					pfnDraw;
	T_pfnGrImage_GetInfo				pfnGetInfo;
	T_pfnGrImage_Save					pfnSave;
	T_pfnGrImage_GetSaveBufSize			pfnGetSaveBufSize;
	T_pfnGrImage_MakeEx					pfnMakeEx;
} TApiGrp_GrImage;

//-------------------------------------------------------------------------------------------------
#ifndef		BNS_MAIN_VERSION

	#define		GrImage_Create(p1,p2)					__ApiLink2(GrImage,Create,p1,p2)
	#define		GrImage_Destroy(p1)						__ApiLink1(GrImage,Destroy,p1)
	#define		GrImage_Make(p1,p2)						__ApiLink2(GrImage,Make,p1,p2)
	#define		GrImage_Draw(p1,p2,p3)					__ApiLink3(GrImage,Draw,p1,p2,p3)
	#define		GrImage_GetInfo(p1,p2,p3)				__ApiLink3(GrImage,GetInfo,p1,p2,p3)
	#define		GrImage_Save(p1,p2,p3,p4,p5,p6,p7)		__ApiLink7(GrImage,Save,p1,p2,p3,p4,p5,p6,p7)
	#define		GrImage_GetSaveBufSize(p1,p2,p3,p4,p5)	__ApiLink5(GrImage,GetSaveBufSize,p1,p2,p3,p4,p5)
	#define		GrImage_MakeEx(p1,p2,p3,p4)				__ApiLink4(GrImage,MakeEx,p1,p2,p3,p4)

#endif	//	BNS_MAIN_VERSION
//-------------------------------------------------------------------------------------------------

#endif	//	_BNSOFT__GRIMAGE_H_
