/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	PEANUT COMBO CONTROL

	Copyright(c) 1997-2003 BNSoft Corp.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT_PEANUT_CMBCTRL_H_
#define		_BNSOFT_PEANUT_CMBCTRL_H_

#include	"BaseCtrl.h"
#include	"MacroFunc/CmbCtrlM.h"

#define		CMBSTY_PULLUP				0x00004000

#define		CMBSTY_DEF				(0)

#define		CMBMASK_ERASEBKGND			NOTIMASK_ERASEBKGND	// 0x80000000
#define		CMBMASK_POSTDRAW			NOTIMASK_POSTDRAW	// 0x40000000

typedef enum
{
	CMBCOL_BACKGROUND				= 0,
	CMBCOL_FOREGROUND,
	CMBCOL_BORDER_LT,						        // Left/Top Border Color
	CMBCOL_BORDER_RB,						        // Right/Bottom Border Color
	CMBCOL_NUM
} E_CMBCOL;

#define	CMBCTRL_DEF_LIST_HEIGHT	(48 * 3+2)

typedef struct
{
	TBaseCtrl			Base;
	H_CTRL				hEdit;
	H_CTRL				hList;
	BOOL				bExpanded;
	T_SIZE				ListHeight;
	T_SIZE				MaxListHeight;
} TCmbCtrl;


//	Create & Destroy Functions
extern H_CTRL		CmbCtrl_Create           (void* pOwner, T_POS X, T_POS Y, T_SIZE W, T_SIZE H);
extern BOOL		CmbCtrl_Destroy          (H_CTRL hCC);

//	Overriding Functions
extern BOOL		CmbCtrl_ModifyStyle      (H_CTRL hCC, QUAD RemoveStyle, QUAD AddStyle);
extern BOOL		CmbCtrl_SetRange         (H_CTRL hCC, T_POS X1, T_POS Y1, T_POS X2, T_POS Y2);
extern BOOL		CmbCtrl_SetPos           (H_CTRL hCC, T_POS X, T_POS Y);
extern BOOL		CmbCtrl_SetSize          (H_CTRL hCC, T_SIZE W, T_SIZE H);

extern BOOL		CmbCtrl_PtInRange        (H_CTRL hCC, T_POS X, T_POS Y);
extern BOOL		CmbCtrl_SetFocus         (H_CTRL hCC);
extern BOOL		CmbCtrl_KillFocus        (H_CTRL hCC);

//	CmbCtrl Own Functions
extern BOOL		CmbCtrl_SetMaxListHeight (H_CTRL hCC, T_SIZE Height);

extern H_CTRL		CmbCtrl_GetEditHandle    (H_CTRL hCC);
extern H_CTRL		CmbCtrl_GetListHandle    (H_CTRL hCC);
extern BOOL		CmbCtrl_IsExpanded       (H_CTRL hCC);
extern T_SIZE		CmbCtrl_GetMaxListHeight (H_CTRL hCC);

extern BOOL		CmbCtrl_ResetAllItems    (H_CTRL hCC);
extern BOOL		CmbCtrl_AddItem          (H_CTRL hCC, T_CSTR pcszStr, QUAD Data, QUAD IconID);
extern BOOL		CmbCtrl_AddSeparator     (H_CTRL hCC);
extern BOOL		CmbCtrl_SelectItem       (H_CTRL hCC, int Index);
extern int		CmbCtrl_SelectNextItem   (H_CTRL hCC);
extern int		CmbCtrl_SelectPrevItem   (H_CTRL hCC);
extern BOOL		CmbCtrl_Expand           (H_CTRL hCC);
extern BOOL		CmbCtrl_Collapse         (H_CTRL hCC);

#endif	//	_BNSOFT_PEANUT_CMBCTRL_H_
