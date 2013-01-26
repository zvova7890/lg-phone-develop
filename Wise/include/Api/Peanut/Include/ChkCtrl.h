/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	PEANUT CHECK CONTROL

	Copyright(c) 1997-2003 BNSoft Corp.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT_PEANUT_CHKCTRL_H_
#define		_BNSOFT_PEANUT_CHKCTRL_H_

#include	"BaseCtrl.h"
#include	"MacroFunc\ChkCtrlM.h"


#define		CHKSTY_RIGHTICON			0x80000000
#define		CHKSTY_ACTIVEBORDER			0x40000000
#define		CHKSTY_TRISTATE				0x20000000
#define		CHKSTY_MULTILINE			0x10000000
#define		CHKSTY_BOLD				0x08000000

#define		CHKSTY_DEF				(CHKSTY_ACTIVEBORDER)

#define		CHKNOTI_ERASEBKGND			NOTIMASK_ERASEBKGND	//	0x80000000
#define		CHKNOTI_POSTDRAW			NOTIMASK_POSTDRAW	//	0x40000000
#define		CHKNOTI_PREKEY				NOTIMASK_PREKEY		//	0x20000000
#define		CHKNOTI_POSTKEY				NOTIMASK_POSTKEY	//	0x10000000

typedef enum
{
	CHKSTATUS_OFF					= 0,
	CHKSTATUS_ON,
	CHKSTATUS_TRI,
	CHKSTATUS_MAXNUM
} E_CHKSTATUS;

typedef enum
{
	CHKCOL_BACKGROUND				= 0,
	CHKCOL_TEXT,
	CHKCOL_NUM
} E_CHKCOL;

typedef struct
{
	TBaseCtrl			Base;
	T_CSTR				pcszText;
	E_CHKSTATUS			enStatus;
	T_SIZE				IconWidth;
	KEY				SelKey;
	int				AlignType;
	int				LineGap;			
} TChkCtrl;


//	Create & Destroy Functions
extern H_CTRL		ChkCtrl_Create       (void* pOwner, T_POS X, T_POS Y, T_SIZE W, T_SIZE H, T_CSTR pcszText);
extern BOOL		ChkCtrl_Destroy      (H_CTRL hCC);


//	ChkCtrl Own Functions

extern BOOL		ChkCtrl_SetText      (H_CTRL hCC, T_CSTR pcszText);
extern BOOL		ChkCtrl_SetStatus    (H_CTRL hCC, E_CHKSTATUS enStatus);
extern BOOL		ChkCtrl_SetCheck     (H_CTRL hCC, BOOL bCheck);
extern BOOL		ChkCtrl_SetIconWidth (H_CTRL hCC, T_SIZE IconWidth);
extern BOOL		ChkCtrl_SetSelKey    (H_CTRL hCC, KEY SelKey);
extern BOOL		ChkCtrl_SetAlignType (H_CTRL hCC, int AlignType);
extern BOOL		ChkCtrl_SetLineGap   (H_CTRL hCC, int LineGap);

extern T_CSTR		ChkCtrl_GetText      (H_CTRL hCC);
extern E_CHKSTATUS	ChkCtrl_GetStatus    (H_CTRL hCC);
extern BOOL	        ChkCtrl_IsChecked    (H_CTRL hCC);
extern T_SIZE		ChkCtrl_GetIconWidth (H_CTRL hCC);
extern KEY		ChkCtrl_GetSelKey    (H_CTRL hCC);
extern int		ChkCtrl_GetAlignType (H_CTRL hCC);
extern int		ChkCtrl_GetLineGap   (H_CTRL hCC);


#endif	//	_BNSOFT_PEANUT_CHKCTRL_H_
