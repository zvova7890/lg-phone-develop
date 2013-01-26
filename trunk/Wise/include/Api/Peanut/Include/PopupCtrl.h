/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	PEANUT POPUP CONTROL

	Copyright(c) 1997-2003 BNSoft Corp.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT_PEANUT_POPUPCTRL_H_
#define		_BNSOFT_PEANUT_POPUPCTRL_H_

#include	"BaseCtrl.h"
#include	"MacroFunc\PopupCtrlM.h"

#define		POPSTY_PARENT			0x80000000
#define		POPSTY_CHILD			0x40000000
#define		POPSTY_TOP			0x00800000
#define		POPSTY_MIDDLE			0x00400000
#define		POPSTY_BOTTOM			0x00200000
#define		POPSTY_LEFT			0x00100000
#define		POPSTY_CENTER			0x00080000
#define		POPSTY_RIGHT			0x00040000
#define		POPSTY_GRAYBACKGROUND		0x00010000
#define		POPSTY_SOFTMENU			0x00008000

#define		POPUPSTY_DEF			(0)


#define		POPNOTI_ERASEBKGND		NOTIMASK_ERASEBKGND
#define		POPNOTI_POSTDRAW		NOTIMASK_POSTDRAW
#define		POPNOTI_PREKEY			NOTIMASK_PREKEY	
#define		POPNOTI_POSTKEY			NOTIMASK_POSTKEY

typedef struct _TPopupCtrl
{
	TBaseCtrl		Base;
	T_POS			BaseX;
	T_POS			BaseY;
	T_SIZE			MaxHeight;
	int			InitIndex;
	BOOL			bSizeChanged;
	H_CTRL			hList;
	BOOL			bPopuped;
	struct _TPopupCtrl*	pSubPC;
} TPopupCtrl;



//	Create & Destroy Functions
extern H_CTRL		PopupCtrl_Create        (void* pOwner, QUAD Style, T_POS BaseX, T_POS BaseY);
extern BOOL		PopupCtrl_Destroy       (H_CTRL hPC);

//	Overriding Functions

//	PopupCtrl Own Functions
extern BOOL		PopupCtrl_SetBase       (H_CTRL hPC, T_POS BaseX, T_POS BaseY);
extern BOOL		PopupCtrl_SetMaxHeight  (H_CTRL hPC, T_SIZE MaxHeight);
extern BOOL		PopupCtrl_SetInitIndex  (H_CTRL hPC, int InitIndex);
extern BOOL		PopupCtrl_SetIcon       (H_CTRL hPC, int Index, QUAD Icon);
extern BOOL		PopupCtrl_SetLeftMargin (H_CTRL hPC, int LeftMargin);

extern int		PopupCtrl_GetSelIndex   (H_CTRL hPC);
extern T_CSTR		PopupCtrl_GetStr        (H_CTRL hPC, int Index);
extern T_CSTR		PopupCtrl_GetSelStr     (H_CTRL hPC);
extern QUAD		PopupCtrl_GetData       (H_CTRL hPC, int Index);
extern H_CTRL		PopupCtrl_GetListHandle (H_CTRL hPC);

extern BOOL		PopupCtrl_AddItem       (H_CTRL hPC, T_CSTR pcszStr, QUAD Data, QUAD IconID);
extern BOOL		PopupCtrl_AddSeparator  (H_CTRL hPC);
extern BOOL		PopupCtrl_AddPopup      (H_CTRL hPC, T_CSTR pcszStr, QUAD IconID, H_CTRL hSubPC);

extern BOOL		PopupCtrl_DoModal       (H_CTRL hPC);
extern BOOL		PopupCtrl_StopModal     (void);
extern BOOL		PopupCtrl_EndModal      (void);


#endif	//	_BNSOFT_PEANUT_POPUPCTRL_H_
