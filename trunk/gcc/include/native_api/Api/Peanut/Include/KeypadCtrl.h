/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	PEANUT KEYPAD CONTROL

	Copyright(c)     -2007 LG Electronics Inc.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT_PEANUT_KEYPADCTRL_H_
#define		_BNSOFT_PEANUT_KEYPADCTRL_H_

#include	"FrmCtrl.h"
#include	"MacroFunc/KeypadCtrlM.h"

#define		KEYPADSTY_BORDER					FRMSTY_BORDER	// 0x80000000, draw border line
#define		KEYPADSTY_DRAG						0x00008000	// enable focus change when item dragged
#define		KEYPADSTY_ZOOM						0x00004000	// enable zoom when item focused
#define		KEYPADSTY_NEXTSEQUENCE					0x00002000	// enable next input character
#define		KEYPADSTY_DIALPAD					0x00001000	// DIALPAD Style
#define		KEYPADSTY_EMAIL						0x00040000
#define		KEYPADSTY_WEB						0x00020000
#define		KEYPADSTY_DICTIONARY					0x00080000
#define		KEYPADSTY_DEF						(KEYPADSTY_DRAG)

#define		KEYPADMETHOD_KEYPAD					0x80000000	//	virtual keypad(4x3, 4x4, status only, etc)
#define		KEYPADMETHOD_QWERTY					0x40000000	//	virtual QWERTY keyboard
#define		KEYPADMETHOD_HANDWRITING_WORD			        0x20000000	//	handwriting recognition, word level
#define		KEYPADMETHOD_HANDWRITING_CHAR_MONOMODE	                0x10000000	//	handwriting recognition, character level, one mode
#define		KEYPADMETHOD_HANDWRITING_CHAR_MULTIMODE	                0x08000000	//	handwriting recognition, character level, multi mode

#define		KEYPADMETHOD_INIT					KEYPADMETHOD_KEYPAD
#define		KEYPADMETHOD_HANDWRITING_ALL			        (KEYPADMETHOD_HANDWRITING_WORD | KEYPADMETHOD_HANDWRITING_CHAR_MONOMODE | \
									 KEYPADMETHOD_HANDWRITING_CHAR_MULTIMODE)
#define		KEYPADMETHOD_ALL					(KEYPADMETHOD_KEYPAD | KEYPADMETHOD_QWERTY | KEYPADMETHOD_HANDWRITING_ALL)

//	QWERTY layout mode
typedef enum
{
	QWERTYMODE_ERROR					= -1,
	QWERTYMODE_BASIC,					//	basic layout in accordance with character set
	QWERTYMODE_SYMBOL,					//	symbol & number layout
	QWERTYMODE_SPECIFIC,					//	special character layout accordance with character set
	QWERTYMODE_NUMERIC,					//	Number only mode
	QWERTYMODE_ENGLISH,					//	English layout
	QWERTYMODE_EMO,
	QWERTYMODE_URL,
	QWERTYMODE_MAX
} E_QWERTYMODE;



//	SYMBOL layout mode (SHIFT)
typedef enum
{
	SYMBOLMODE_0,
	SYMBOLMODE_1,
	SYMBOLMODE_2,
} E_SYMBOLMODE;


#define		KEYPADNOTI_ERASEBKGND			NOTIMASK_ERASEBKGND			//	0x80000000
#define		KEYPADNOTI_POSTDRAW			NOTIMASK_POSTDRAW			//	0x40000000
#define		KEYPADNOTI_PREKEY			NOTIMASK_PREKEY				//	0x20000000
#define		KEYPADNOTI_POSTKEY			NOTIMASK_POSTKEY			//	0x10000000
#define		KEYPADNOTI_METHODCHANGED		0x00008000				//	when input method is changed
#define		KEYPADNOTI_HOOK				0x00004000				//	when keypad is pointed, no operation in keypad
#define		KEYPADNOTI_OVERLAP			0x00002000				//	when keypad item is overlaped other range
#define		KEYPADNOTI_RANGECHANGED			0x00001000
#define		KEYPADNOTI_OEMNOTIFY			0x00000800
#define		KEYPADNOTI_KEYPRESS			0x00000400
#define		KEYPADNOTI_ARRANGEKEYPAD		0x00000200

//	KeypadCtrl item status
#define		KEYPADITEM_DOWN				0x80000000
#define		KEYPADITEM_DISABLE			0x40000000
#define		KEYPADITEM_LONG				0x20000000
#define		KEYPADITEM_DRAG				0x10000000
#define		KEYPADITEM_ZOOM				0x08000000
#define		KEYPADITEM_NEXTSEQ			0x04000000
#define		KEYPADITEM_POINTUP			0x02000000

//	KeypadCtrl status object
#define		KSTATUSTYPE_NONE			0x00000000
#define		KSTATUSTYPE_INPUTMETHOD			0x00000001
#define		KSTATUSTYPE_EDITMODE			0x00000002
#define		KSTATUSTYPE_DICTIONARY			0x00000004
#define		KSTATUSTYPE_HANDWRITING			0x00000008
#define		KSTATUSTYPE_VKCLOSE			0x00000010
#define		KSTATUSTYPE_WRITELANGUAGE		0x00000020
#define		KSTATUSTYPE_NAVIGATION			0x00000040
#define		KSTATUSTYPE_BLOCK			0x00000080
#define		KSTATUSTYPE_ALL				(KSTATUSTYPE_INPUTMETHOD | KSTATUSTYPE_EDITMODE | KSTATUSTYPE_DICTIONARY | KSTATUSTYPE_HANDWRITING | KSTATUSTYPE_VKCLOSE | KSTATUSTYPE_WRITELANGUAGE | KSTATUSTYPE_NAVIGATION)

//	KeypadCtrl color definition
typedef enum
{
	KEYPADCOL_BACKGROUND				= FRMCOL_BACKGROUND,
	KEYPADCOL_FOREGROUND				= FRMCOL_FOREGROUND,
	KEYPADCOL_BORDER_LT				= FRMCOL_BORDER_LT,
	KEYPADCOL_BORDER_RB				= FRMCOL_BORDER_RB,
	KEYPADCOL_TITLE_BACKGROUND			= FRMCOL_TITLE_BACKGROUND,
	KEYPADCOL_TITLE_TEXT				= FRMCOL_TITLE_TEXT,
	KEYPADCOL_TITLE_UNDERLINE			= FRMCOL_TITLE_UNDERLINE,
	KEYPADCOL_NORMAL_TEXT,
	KEYPADCOL_NORMAL_BACKGROUND,
	KEYPADCOL_SELECT_TEXT,
	KEYPADCOL_SELECT_BACKGROUND,
	KEYPADCOL_DISABLE_TEXT,
	KEYPADCOL_DISABLE_BACKGROUND,
	KEYPADCOL_NUM
} E_KEYPADCOL;

//	KeypadCtrl item structure
typedef	struct
{
	//	common member
	TRect				Rect;
	QUAD				State;
	QUAD				Data;
	QUAD				IconID;
	//	normal item member
	T_CSTR				pcszStr;
	KEY					Key;
	//	status item member
	QUAD				StatusType;
} TKeypadItem;

//	KeypadCtrl status object structure
typedef	struct
{
	TSLnkObj			LnkObj;		//	Single Linked List Object
	TKeypadItem			Status;
} TStatusObj;

//	QWERTY structure
typedef	struct
{
	BOOL			bCapsLock;
	E_SYMBOLMODE		bShift;
	E_SYMBOLMODE		nsym;
	BOOL			bNavigation;
	E_SYMBOLMODE		nemo;
	E_SYMBOLMODE		burl;
	E_QWERTYMODE		enMode;
	int			SymbolPage;
	BOOL			bMultitapOn;		//by bean	(2008-07-28) -- this is for Qwerty Multitap
	KEY			PrevKey;		//by bean (2008-07-30) -- Previous Input Key
} TQwerty;

//	Symbol structure
typedef	struct
{
	QUAD*				pData;
	LONG				DataLen;
	LONG				Page;
	LONG				MaxPage;
	LONG				NumPerPage;
} TSymbol;


//	Multitab String object structure
#define KEYPADCTRL_MAX_MULTITABSTR_LEN 10
typedef	struct
{
	TSLnkObj			LnkObj;			//	Single Linked List Object
	A_CHAR				szMultitabStr[KEYPADCTRL_MAX_MULTITABSTR_LEN + 1];
} TMultitabStrObj;

//	KeypadCtrl structure
typedef struct
{
	TFrmCtrl			Frame;
	TKeypadItem*		pItemTbl;				//	normal item table
	T_NUM				MaxItemNum;			//	normal item max number
	T_NUM				ItemNum;			//	normal item number
	TLnkList*			pStatusList;			//	status object linked list
	QUAD				Method;				//	input method
	QUAD				EnableMethod;			//	enable input methods
	H_CTRL				hCtrl;				//	handle of other control
	TQwerty				Qwerty;				//	QWERTY
	TImage*				pBkImage;			//	background image
	QUAD				AlphablendLevel;		//	alpha level of control
	TSymbol				Symbol;				//	@maenghs[2008-06-18]
	void*				pOemKeypadCtrl;			//	for oem layer
	TLnkList*			pMultitabStrList;

} TKeypadCtrl;

//	for compatiable previous version
#define		KEYPADNOTI_POINTINGTOKEY		KEYPADNOTI_HOOK
#define		KEYPADNOTI_REDRAW			KEYPADNOTI_OVERLAP

#define		KEYPADMETHOD_NORMAL			KEYPADMETHOD_KEYPAD
#define		KEYPADITEM_INPUTMETHOD			KSTATUSTYPE_INPUTMETHOD
#define		KEYPADITEM_EDITMODE			KSTATUSTYPE_EDITMODE
#define		KEYPADITEM_DICTIONARY			KSTATUSTYPE_DICTIONARY
#define		KEYPADITEM_HANDWRITING			KSTATUSTYPE_HANDWRITING
#define		KEYPADITEM_BLOCK			KSTATUSTYPE_BLCOK
#define		KEYPADITEM_STATUS_ALL			KSTATUSTYPE_ALL
#define		KEYPADMETHOD_HANDWRITING_SCREEN		KEYPADMETHOD_HANDWRITING_WORD
#define		KEYPADMETHOD_HANDWRITING_BOX		KEYPADMETHOD_HANDWRITING_CHAR_MONOMODE



//	create & destroy
extern H_CTRL			KeypadCtrl_Create(void* pOwner, T_POS X, T_POS Y, T_SIZE W, T_SIZE H);
extern BOOL			KeypadCtrl_Destroy(H_CTRL hKC);

//	item create, delete and enable
extern BOOL			KeypadCtrl_ResetAllItems(H_CTRL hKC);
extern BOOL			KeypadCtrl_AddItem      (H_CTRL hKC, T_CSTR pcszStr, TRect Rect, KEY Key, QUAD Data, QUAD IconID);
extern BOOL			KeypadCtrl_DeleteItem   (H_CTRL hKC, int Index);
extern BOOL			KeypadCtrl_EnableItem	(H_CTRL hKC, int Index, BOOL bEnable);
extern T_NUM			KeypadCtrl_GetItemNum	(H_CTRL hKC);

	//	interaction, draw
extern BOOL			KeypadCtrl_SetCtrl		(H_CTRL hKC, H_CTRL hCtrl);
extern BOOL			KeypadCtrl_SetBkImage		(H_CTRL hKC, TImage* pImage);
extern BOOL			KeypadCtrl_SetAlphablendLevel	(H_CTRL hKC, BYTE Level);
extern H_CTRL			KeypadCtrl_GetCtrl				(H_CTRL hKC);
extern TImage*			KeypadCtrl_GetBkImage		(H_CTRL hKC);
extern BYTE			KeypadCtrl_GetAlphablendLevel	(H_CTRL hKC);

//	input method
extern BOOL			KeypadCtrl_SetMethod		(H_CTRL hKC, QUAD Method);
extern BOOL			KeypadCtrl_SetEnableMethod	(H_CTRL hKC, QUAD Methods);
extern QUAD			KeypadCtrl_GetMethod		(H_CTRL hKC);
extern QUAD			KeypadCtrl_GetEnableMethod	(H_CTRL hKC);

//	detail setting of item
extern BOOL			KeypadCtrl_SetItemStr		(H_CTRL hKC, int Index, T_CSTR pcszStr);
extern BOOL			KeypadCtrl_SetItemRange		(H_CTRL hKC, int Index, TRect Rect);
extern BOOL			KeypadCtrl_SetItemKey		(H_CTRL hKC, int Index, KEY Key);
extern BOOL			KeypadCtrl_SetItemData		(H_CTRL hKC, int Index, QUAD Data);
extern BOOL			KeypadCtrl_SetItemIcon		(H_CTRL hKC, int Index, QUAD IconID);
extern T_CSTR			KeypadCtrl_GetItemStr		(H_CTRL hKC, int Index);
extern TRect*			KeypadCtrl_GetItemRange		(H_CTRL hKC, int Index);
extern KEY			KeypadCtrl_GetItemKey		(H_CTRL hKC, int Index);
extern QUAD			KeypadCtrl_GetItemData		(H_CTRL hKC, int Index);
extern QUAD			KeypadCtrl_GetItemIcon		(H_CTRL hKC, int Index);
//	QWERTY
extern BOOL			KeypadCtrl_SetQwertyMode	(H_CTRL hKC, E_QWERTYMODE enMode);
extern E_QWERTYMODE		KeypadCtrl_GetQwertyMode	(H_CTRL hKC);
extern BOOL			KeypadCtrl_EnableQwertyCapsLock	(H_CTRL hKC, BOOL bEnable);
extern BOOL			KeypadCtrl_IsQwertyCapsLock	(H_CTRL hKC);
extern BOOL			KeypadCtrl_SetNextQwertyMode	(H_CTRL hKC);
//	status item
extern BOOL			KeypadCtrl_AddStatusItem	(H_CTRL hKC, TRect Rect, QUAD StatusType, QUAD IconID);
extern BOOL			KeypadCtrl_DeleteStatusItem	(H_CTRL hKC, QUAD StatusType);
extern BOOL			KeypadCtrl_EnableStatusItem	(H_CTRL hKC, QUAD StatusType, BOOL bEnable);
extern BOOL			KeypadCtrl_ReplaceStatusItem	(H_CTRL hKC, QUAD StatusType, QUAD NewStatusType);
extern BOOL			KeypadCtrl_SetStatusItem	(H_CTRL hKC, int Index, QUAD StatusType);

extern BOOL			KeypadCtrl_SetStatusItemRange	(H_CTRL hKC, QUAD StatusType, TRect Rect);
extern BOOL			KeypadCtrl_SetStatusItemIcon	(H_CTRL hKC, QUAD StatusType, QUAD IconID);
extern TRect*			KeypadCtrl_GetStatusItemRange	(H_CTRL hKC, QUAD StatusType);
extern QUAD			KeypadCtrl_GetStatusItemIcon	(H_CTRL hKC, QUAD StatusType);

extern BOOL			KeypadCtrl_DrawStatusItem	(H_CTRL hKC);

//	keypad on/off
extern BOOL			KeypadCtrl_SetKeypadOn		(H_CTRL hKC, BOOL bUseKeypad);
extern BOOL			KeypadCtrl_GetKeypad		(H_CTRL hKC);
extern BOOL			KeypadCtrl_IsKeypadOn		(H_CTRL hKC);


#endif	//	_BNSOFT_PEANUT_KEYPADCTRL_H_

