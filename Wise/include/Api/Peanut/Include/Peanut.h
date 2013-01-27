/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	PEANUT LIBRARY

	Copyright(c) 1997-2003 BNSoft Corp.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT_PEANUT_H_
#define		_BNSOFT_PEANUT_H_

#include	"../../BasicApiLib/BasicApiLib.h"
#include	"../../BasicApiLib/Include/LnkList.h"
#include	"PeanutTypeDef.h"

typedef enum
{
	RES_START		= -1,

	RES_GLOBAL,		// 0
	RES_INDICATOR,		// 1
	RES_SOFTMENU,		// 2
	RES_SCRLBAR,		// 3
	RES_ADDWORD,		// 4
	RES_DICTIONARY,		// 5
	RES_SYMBOL,		// 6
	RES_FRMCTRL,		// 7
	RES_LISTCTRL,		// 8
	RES_LISTVIEW,
	RES_SELCTRL,		// 9
	RES_REDITCTRL,		// 10
	RES_TEXTCTRL,		// 11
	RES_BUTCTRL,		// 12
	RES_POPUPMENU,		// 13
	RES_POPUPBOX,		// 14
	RES_POPUPLIST,		// 15
	RES_POPUPYNBOX,		// 16
	RES_POPUPINPUTBOX,	// 17
	RES_POPUPFILEBOX,	// 18
	RES_EDITDIC,		// 19
	RES_WORDLIST,		// 20
	RES_KEYPADCTRL,		// 21
	RES_KEYPOPUPIM,		// 22
	RES_KEYPOPUPEM,		// 23
	RES_KEYHWSCREEN,	// 24
	RES_KEYHWBOX,		// 25
	RES_HWOPTCOL,		// 26
	RES_CHSINPUT,		// 27
	RES_INDIICON,		// 28
	RES_CHKCTRL,

	RES_MAX_END
} E_RESTYPE;


//	Definition of Peanut Global Structure
typedef struct
{
	TSLnkObj			LnkObj;			//	Single Linked List Object
	H_CTRL				hModalDlg;
	H_TIMERCORE			hModalTimer;
	H_CTRL				hModalPopup;
	int				IndShowStyle[2];	//	Indicator Show Style

	// SoftMenu Strings
	T_CSTR				LMenuStr;
	T_CSTR				MMenuStr;
	T_CSTR				RMenuStr;
	int				SM_State[9];		//softmenu
	QUAD				SM_IconID[5];
	H_CTRL				hSMOwner;
} TPeanut;

//	Peanut Extern Variables

extern TPeanut*			g_pPeanut;


extern BOOL		Peanut_SetEnvValue (QUAD Key, QUAD Value);
extern QUAD		Peanut_GetEnvValue (QUAD Key);

extern BOOL		Peanut_SetConfigData	(int ID, E_RESTYPE Type, void* pData);
extern void*		Peanut_GetConfigData	(int ID, E_RESTYPE Type);
extern BOOL		Peanut_SetConfigValue	(int ID, E_RESTYPE Type, int Item, T_PARAM PARAM);
extern QUAD		Peanut_GetConfigValue	(int ID, E_RESTYPE Type, int Item);

extern BOOL		Peanut_GetInterface	(QUAD* pInfo);
extern BOOL		Peanut_SetTip		(TRect* Rect, T_POS X, T_POS Y, T_CSTR pcszStr);

#endif	//	_BNSOFT_PEANUT_H_
