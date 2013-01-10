/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	GRAPHIC IMAGE

	Copyright(c) 1997-2003 BNSoft Corp.

	그룹 : BASIC API
	구분 : 그래픽
	등급 : 공개																						{{BNS_INTERNALCODE()}}
	버전 : 1.08
	일자 : 2003.06.05
	성명 : 박상호
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT_GRIMAGE_H_
#define		_BNSOFT_GRIMAGE_H_

#include	"Include.h"

//-------------------------------------------------------------------------------------------------
typedef enum
{
	IMAGETYPE_BMP						= 0,
	IMAGETYPE_BMPFILE,
	IMAGETYPE_WBMP,
	IMAGETYPE_WBMPFILE,
	IMAGETYPE_GIF,
	IMAGETYPE_GIFFILE,
	IMAGETYPE_JPG,
	IMAGETYPE_JPGFILE,
	IMAGETYPE_PNG,
	IMAGETYPE_PNGFILE,
	IMAGETYPE_SIS,
	IMAGETYPE_SISFILE,
	IMAGETYPE_PRI,											//	PDK Raster Image
	IMAGETYPE_PRIFILE,
	IMAGETYPE_MAX
} E_IMAGETYPE;

//-------------------------------------------------------------------------------------------------
//	TGrImage::Flag의 종류
#define		GRIMG_FLAG_ISFILE			1
#define		GRIMG_FLAG_ALLOCATED_DATA	2

//-------------------------------------------------------------------------------------------------
typedef struct
{
	T_SIZE				Width;
	T_SIZE				Height;
	T_NUM				ColorBit;
	T_NUM				FrameNum;
} TGrImgInfo;

typedef struct
{
	E_IMAGETYPE			enType;
	int					Flag;
	void*				pData;
	void*				pImage;
	T_SIZE				Width;
	T_SIZE				Height;
	T_SIZE				ColorBit;
	T_NUM				FrameNum;
} TGrImage;

//-------------------------------------------------------------------------------------------------
//	GrImage Member Functions
#ifdef		BNS_MAIN_VERSION

	extern TGrImage*		GrImage_Create         (E_IMAGETYPE enImageType, void* pData);
	extern BOOL				GrImage_Destroy        (TGrImage* pGrImg);
	extern BOOL				GrImage_Make           (TGrImage* pGrImg, int FrameIndex);
	extern BOOL				GrImage_MakeEx		   (TGrImage* pGrImg, void* pImage, int FrameIndex, int OutputColorbit);		
	extern BOOL				GrImage_Draw           (TGrImage* pGrImg, T_POS X, T_POS Y);

	extern BOOL				GrImage_GetInfo        (E_IMAGETYPE enImageType, void* pData, TGrImgInfo* pGrImgInfo);

	extern T_SIZE			GrImage_Save           (E_IMAGETYPE enImageType, void* pData, T_POS X, T_POS Y, T_SIZE W, T_SIZE H, T_SIZE BufSize);
	extern T_SIZE			GrImage_GetSaveBufSize (E_IMAGETYPE enImageType, T_POS X, T_POS Y, T_SIZE W, T_SIZE H);

#endif	//	BNS_MAIN_VERSION
//-------------------------------------------------------------------------------------------------

#endif	//	_BNSOFT_GRIMAGE_H_
