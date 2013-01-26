/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	PEANUT IMAGE CONTROL

	Copyright(c) 1997-2003 BNSoft Corp.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT_PEANUT_IMGCTRL_H_
#define		_BNSOFT_PEANUT_IMGCTRL_H_

#include	"BaseCtrl.h"
#include	"MacroFunc\ImgCtrlM.h"

#define		IMGSTY_CIRCULAR			0x80000000
#define		IMGSTY_DEF			(IMGSTY_CIRCULAR)

#define		IMGNOTI_ERASEBKGND		NOTIMASK_ERASEBKGND	//	0x80000000
#define		IMGNOTI_POSTDRAW		NOTIMASK_POSTDRAW	//	0x40000000

#define		IMGTYPE_UNKNOWN			0
#define		IMGTYPE_BMP			1
#define		IMGTYPE_JPG			2
#define		IMGTYPE_PNG			3
#define		IMGTYPE_SIS			4
#define		IMGTYPE_PAF			5 //	PDK Animation Format
#define		IMGTYPE_PRI			6 //	PDK Raster Image

#define		IMGBKMODE_OPAQUE			GRSYS_OPAQUE
#define		IMGBKMODE_TRANSPARENT		GRSYS_TRANSPARENT
#define		IMGBKMODE_ALPHABLENDING		GRSYS_ALPHABLENDING

typedef struct
{
	TBaseCtrl			Base;
	T_HANDLE			hImage;
	int				ImageType;
	T_POS				ImageX;
	T_POS				ImageY;
	T_SIZE				ImageWidth;
	T_SIZE				ImageHeight;
	T_NUM				FrameNum;
	T_INDEX				FrameIndex;
	int				BkMode;
	int				AlignMode;
} TImgCtrl;


//	Create & Destroy Functions
extern H_CTRL		ImgCtrl_Create         (void* pOwner, T_POS X, T_POS Y, T_SIZE W, T_SIZE H, T_CSTR pcszFileName);
extern BOOL		ImgCtrl_Destroy        (H_CTRL hIC);

//	Overriding Functions

//	ImgCtrl Own Functions
extern BOOL		ImgCtrl_SetImage       (H_CTRL hIC, T_CSTR pcszFileName);
extern BOOL		ImgCtrl_SetBkMode      (H_CTRL hIC, int Mode);
extern BOOL		ImgCtrl_SetAlign       (H_CTRL hIC, int Align);

extern int		ImgCtrl_GetImageType   (H_CTRL hIC);
extern T_SIZE		ImgCtrl_GetImageWidth  (H_CTRL hIC);
extern T_SIZE		ImgCtrl_GetImageHeight (H_CTRL hIC);
extern T_NUM		ImgCtrl_GetFrameNum    (H_CTRL hIC);
extern T_INDEX		ImgCtrl_GetFrameIndex  (H_CTRL hIC);
extern int		ImgCtrl_GetBkMode      (H_CTRL hIC);
extern int		ImgCtrl_GetAlign       (H_CTRL hIC);

#endif	//	_BNSOFT_PEANUT_IMGCTRL_H_
