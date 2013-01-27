/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	PEANUT TAB CONTROL

	Copyright(c) 1997-2003 BNSoft Corp.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT_PEANUT_TABCTRL_H_
#define		_BNSOFT_PEANUT_TABCTRL_H_

#include	"FrmCtrl.h"
#include	"MacroFunc/TabCtrlM.h"

#define		TABSTY_BORDER		FRMSTY_BORDER		//	0x80000000
#define		TABSTY_TITLE		FRMSTY_TITLE		//	0x40000000
#define		TABSTY_LEFTTITLE	FRMSTY_LEFTTITLE	//	0x20000000
#define		TABSTY_LEFTTOPTITLE	FRMSTY_LEFTTOPTITLE	//	0x00800000
#define		TABSTY_HSCROLLBAR	FRMSTY_HSCROLLBAR	//	0x10000000
#define		TABSTY_VSCROLLBAR	FRMSTY_VSCROLLBAR	//	0x08000000
#define		TABSTY_ALWAYSSHOWSB	FRMSTY_ALWAYSSHOWSB	//	0x04000000

#define		TABSTY_SOFTMENU		0x00008000		//
#define		TABSTY_CIRCULAR		0x00001000		//

#define		TABSTY_DEF		(FRMSTY_DEF | TABSTY_TITLE | TABSTY_SOFTMENU | TABSTY_CIRCULAR)

#define		TABNOTI_ERASEBKGND	NOTIMASK_ERASEBKGND	//	0x80000000
#define		TABNOTI_POSTDRAW	NOTIMASK_POSTDRAW	//	0x40000000
#define		TABNOTI_PREKEY		NOTIMASK_PREKEY		//	0x20000000
#define		TABNOTI_POSTKEY		NOTIMASK_POSTKEY	//	0x10000000

typedef enum
{
	TABCOL_BACKGROUND		= FRMCOL_BACKGROUND,
	TABCOL_FOREGROUND		= FRMCOL_FOREGROUND,
	TABCOL_BORDER_LT		= FRMCOL_BORDER_LT,
	TABCOL_BORDER_RB		= FRMCOL_BORDER_RB,
	TABCOL_TITLE_BACKGROUND		= FRMCOL_TITLE_BACKGROUND,
	TABCOL_TITLE_TEXT		= FRMCOL_TITLE_TEXT,
	TABCOL_TITLE_UNDERLINE		= FRMCOL_TITLE_UNDERLINE,
	TABCOL_NUM
} E_TABCOL;

typedef struct
{
	H_CTRL				hPage;
} TTab;

typedef struct
{
	TFrmCtrl			Frame;
	T_NUM				TabNum;
	TTab*				pTabTbl;
	KEY				PrevKey;
	KEY				NextKey;
} TTabCtrl;


//	Create & Destroy Functions
extern H_CTRL	TabCtrl_Create         (void* pOwner, T_POS X, T_POS Y, T_SIZE W, T_SIZE H);
extern BOOL	TabCtrl_Destroy        (H_CTRL hDlg);


//	TabCtrl Own Functions
extern H_CTRL	TabCtrl_CreateDlgTab  (H_CTRL hTC, T_CSTR rcszTitle);
extern H_CTRL	TabCtrl_CreateEditTab (H_CTRL hTC, T_CSTR rcszTitle, T_NUM MaxChar);
extern H_CTRL	TabCtrl_CreateListTab (H_CTRL hTC, T_CSTR rcszTitle);
extern H_CTRL	TabCtrl_CreateTextTab (H_CTRL hTC, T_CSTR rcszTitle, T_CSTR pcszText);


#endif	//	_BNSOFT_PEANUT_TABCTRL_H_
