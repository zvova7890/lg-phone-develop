/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	PEANUT ICON CONTROL

	Copyright(c) 1997-2003 BNSoft Corp.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT_PEANUT_ICONCTRL_H_
#define		_BNSOFT_PEANUT_ICONCTRL_H_

#include	"BaseCtrl.h"
#include	"MacroFunc\IconCtrlM.h"

#define		ICONSTY_CIRCULAR		0x80000000
#define		ICONSTY_DEF			(ICONSTY_CIRCULAR)

#define		ICONNOTI_ERASEBKGND		NOTIMASK_ERASEBKGND	//0x80000000
#define		ICONNOTI_POSTDRAW		NOTIMASK_POSTDRAW	//0x40000000
#define		ICONNOTI_POINTING		0x08000000		//0x08000000
//	IconCtrl BackgroundMode
#define		ICONBKMODE_OPAQUE		GRSYS_OPAQUE
#define		ICONBKMODE_TRANSPARENT		GRSYS_TRANSPARENT

//	IconCtrl 구조체 정의
typedef struct
{
	TBaseCtrl		Base;
	T_NUM			ImageNum;
	int			SelIndex;
	TImage**		ppImage;
	int			BkMode;
} TIconCtrl;


//	Create & Destroy Functions
extern H_CTRL		IconCtrl_Create          (void* pOwner, T_POS X, T_POS Y, TImage* pImage);
extern BOOL		IconCtrl_Destroy         (H_CTRL hIC);

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//	Overriding Functions

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//	IconCtrl Own Functions
extern BOOL		IconCtrl_SetImage        (H_CTRL hIC, int Index, TImage* pImage);
extern BOOL		IconCtrl_AddImage        (H_CTRL hIC, TImage* pImage);
extern BOOL		IconCtrl_SetBkMode       (H_CTRL hIC, int Mode);

extern TImage*		IconCtrl_GetImage        (H_CTRL hIC, int Index);
extern T_NUM		IconCtrl_GetImageNum     (H_CTRL hIC);
extern int		IconCtrl_GetSelIndex     (H_CTRL hIC);
extern TImage*		IconCtrl_GetSelImage     (H_CTRL hIC);
extern int		IconCtrl_GetBkMode       (H_CTRL hIC);

extern BOOL		IconCtrl_SelectImage     (H_CTRL hIC, int Index);
extern BOOL		IconCtrl_SelectNextImage (H_CTRL hIC);
extern BOOL		IconCtrl_SelectPrevImage (H_CTRL hIC);

#endif	//	_BNSOFT_PEANUT_ICONCTRL_H_
