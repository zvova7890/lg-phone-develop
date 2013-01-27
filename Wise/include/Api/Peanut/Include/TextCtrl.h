/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	PEANUT TEXT CONTROL

	Copyright(c) 1997-2002 BNSoft Corp.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT_PEANUT_TEXTCTRL_H_
#define		_BNSOFT_PEANUT_TEXTCTRL_H_

#include	"BaseCtrl.h"
#include	"MacroFunc/TextCtrlM.h"

#define		TEXTSTY_DEF			(0)

#define		TEXTSTY_BOLD			0x00008000
#define		TEXTSTY_UNDERLINE		0x00004000
#define		TEXTSTY_ITALIC			0x00002000
#define		TEXTSTY_STRIKETHROUGH		0x00001000
#define		TEXTSTY_OUTLINE			0x00000800
#define		TEXTSTY_TXTWORDBREAK		0x00000400
#define		TEXTSTY_TICKER			0x00000200
#define		TEXTSTY_ELLIPSIS		0x00000100
#define		TEXTSTY_NOVFONTCOLOR		0x00080000
#define		TEXTNOTI_POINTING	        0x08000000


typedef enum
{
	TEXTCOL_TEXT				= 0,
	TEXTCOL_NUM
} E_TEXTCOL;

typedef struct
{
	TBaseCtrl		Base;
	T_CSTR			pcszText;
	T_POS			TickerPos;
	int			Align;
} TTextCtrl;



extern H_CTRL		TextCtrl_Create   (void* pOwner, T_POS X, T_POS Y, T_SIZE W, T_SIZE H, T_CSTR pcszText);
extern BOOL		TextCtrl_Destroy  (H_CTRL hTC);

extern BOOL		TextCtrl_SetText  (H_CTRL hTC, T_CSTR pcszText);
extern BOOL		TextCtrl_SetAlign (H_CTRL hTC, int Align);
extern T_CSTR		TextCtrl_GetText  (H_CTRL hTC);
extern int		TextCtrl_GetAlign (H_CTRL hTC);


#endif	//	_BNSOFT_PEANUT_TEXTCTRL_H_
