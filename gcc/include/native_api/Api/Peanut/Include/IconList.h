/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	PEANUT ICON LIST

	Copyright(c) 1997-2003 BNSoft Corp.


~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT_PEANUT_ICONLIST_H_
#define		_BNSOFT_PEANUT_ICONLIST_H_

#include	"PeanutInclude.h"
#include	"HndlMngr.h"

typedef enum
{
	ICON_NONE					= 0xFFFF,
	ICON_START					= 0x8000,

	ICON_THEME_TITLE,		
	ICON_THEME_WALLPAPER,
	ICON_THEME_WALLPAPER_VERT,		
	ICON_THEME_SOFTMENU,
	ICON_THEME_INDICATOR,
	ICON_THEME_INDICATOR_VERT,

	ICON_SM_OPTION,
	ICON_SM_OPTION_PRESS,
	ICON_SM_POPOPTION_PRESS,
	ICON_SM_BACK,
	ICON_SM_BACK_PRESS,

	ICON_SM_OPTION_VERT,
	ICON_SM_OPTION_PRESS_VERT,
	ICON_SM_BACK_VERT,
	ICON_SM_BACK_PRESS_VERT,

	ICON_SM_IBACKWARD,			//ICON
	ICON_SM_IBACKWARD_PRESS,
	ICON_SM_IFORWARD,
	ICON_SM_IFORWARD_PRESS,
	ICON_SM_IREFRESH,
	ICON_SM_IREFRESH_PRESS,
	ICON_SM_IFAVORITE,
	ICON_SM_IFAVORITE_PRESS,
	ICON_SM_IDELETE,
	ICON_SM_IDELETE_PRESS,
	ICON_SM_ICOPY,
	ICON_SM_ICOPY_PRESS,
	ICON_SM_IMOVE,
	ICON_SM_IMOVE_PRESS,
	ICON_SM_IPRINT,
	ICON_SM_IPRINT_PRESS,
	ICON_SM_ISAVE,
	ICON_SM_ISAVE_PRESS,
	ICON_SM_IADD,
	ICON_SM_IADD_PRESS,
	ICON_SM_IPLAY,
	ICON_SM_IPLAY_PRESS,
	ICON_SM_ISEND,
	ICON_SM_ISEND_PRESS,

	ICON_RDO_OFF,
	ICON_RDO_ON,

	ICON_CHK_OFF,
	ICON_CHK_ON,
	ICON_CHK_TRI,								
	
	//	scrlbar
	ICON_SCRL_BG_T,		
	ICON_SCRL_BG_M,		
	ICON_SCRL_BG_B,		
	ICON_SCRL_BAR_T,	
	ICON_SCRL_BAR_M,
	ICON_SCRL_BAR_B,
	ICON_SCRL_BAR_CURSOR,

	ICON_LIST_CHK_OFF,
	ICON_LIST_CHK_OFFSEL,
	ICON_LIST_CHK_ON,								
	ICON_LIST_CHK_ONSEL,
	ICON_LIST_RDO_OFF,									
	ICON_LIST_RDO_OFFSEL,
	ICON_LIST_RDO_ON,						
	ICON_LIST_RDO_ONSEL,
	ICON_LIST_MENUICON,
	ICON_LIST_SELBAR_1_L,	
	ICON_LIST_SELBAR_1_C,	
	ICON_LIST_SELBAR_1_R,	
	ICON_LIST_SELBAR_2_L,	
	ICON_LIST_SELBAR_2_C,	
	ICON_LIST_SELBAR_2_R,	
	ICON_LIST_NUM_BG,

	ICON_LIST_ONEBUT,
	ICON_LIST_ONEBUT_PRESS,
	ICON_LIST_ONEBUT_VERT,
	ICON_LIST_ONEBUT_PRESS_VERT,

	ICON_NUMBER_SMALL,
	ICON_NUMBER_MIDDLE,
	ICON_NUMBER_LARGE,
	
	//	Spin Control
	ICON_SPIN_ARROW_L,		
	ICON_SPIN_ARROW_R,
	ICON_SPIN_PRESS_ARROW_L,
	ICON_SPIN_PRESS_ARROW_R,
	ICON_SPIN_ARROW_DOWN_R,
	ICON_SPIN_PRESS_ARROW_DOWN_R,

//	ICON_SPIN_ACTIVE,
//	ICON_SPIN_ACTIVE_L,		
//	ICON_SPIN_ACTIVE_C,		
//	ICON_SPIN_ACTIVE_R,	
//	ICON_SPIN_INACTIVE,
//	ICON_SPIN_INACTIVE_L,	
//	ICON_SPIN_INACTIVE_C,	
//	ICON_SPIN_INACTIVE_R,
	
	//	AddWord Popup Bg
	ICON_ADDWORD_BG,

	//	Dictionary Popup 에서 사용하는 check icon
	ICON_CHECK,

	//	Popup Menu Data
	ICON_POPUP_MENU_1ST_BG_TOP,
	ICON_POPUP_MENU_1ST_BG_MIDDLE,
	ICON_POPUP_MENU_1ST_BG_BOTTOM,
	ICON_POPUP_MENU_2ST_BG_TOP,
	ICON_POPUP_MENU_2ST_BG_MIDDLE,
	ICON_POPUP_MENU_2ST_BG_BOTTOM,
	ICON_POPUP_MENU_2ST_NUM_BG,

	//	Popup Box
	ICON_POPUP_BOX_BG,		//volume과 progress popup bg(213x256)
	ICON_POPUP_BOX_BG_L,
	ICON_POPUP_BOX_BG_M,
	ICON_POPUP_BOX_BG_S,
	ICON_POPUP_BOX_TITLE,		// popuplist,popup file box의 title line image
	ICON_POPUP_BOX_UPARROW,
	ICON_POPUP_BOX_DOWNARROW,
	ICON_POPUP_ONEBUT,
	ICON_POPUP_ONEBUT_PRESS,
	ICON_POPUP_TWOBUT_L,
	ICON_POPUP_TWOBUT_L_PRESS,
	ICON_POPUP_TWOBUT_R,
	ICON_POPUP_TWOBUT_R_PRESS,

	ICON_POPUP_BUTTON1,		// = ICON_POPUP_ONEBUT 
	ICON_POPUP_BUTTON1_PRESS,	// = ICON_POPUP_ONEBUT_PRESS
	ICON_POPUP_BUTTON2,		// = ICON_POPUP_TWOBUT_L = ICON_POPUP_TWOBUT_R
	ICON_POPUP_BUTTON2_PRESS,	// = ICON_POPUP_TWOBUT_L_PRESS = ICON_POPUP_TWOBUT_R_PRESS 동일

	//	Popup File Box
	ICON_POPUP_FBOX_BG,
	ICON_POPUP_FBOX_TITLE,
	ICON_POPUP_FBOX_TITLE_MID,
	ICON_POPUP_FBOX_TITLE_LARGE,
	ICON_POPUP_FBOX_TITLE_SMALL,

	//	Popup Input Box
	ICON_POPUP_INBOX_BG,
	ICON_POPUP_INBOX_TITLE,
	ICON_POPUP_INBOX_TITLE_MID,
	ICON_POPUP_INBOX_TITLE_LARGE,
	ICON_POPUP_INBOX_TITLE_SMALL,
	ICON_POPUP_INBOX_EDIT,
	
	//	Popup YN box
	ICON_POPUP_YNBOX_BG,
	ICON_POPUP_YNBOX_TITLE,

	//	Popup List
	ICON_POPUP_LIST_BG,
	ICON_POPUP_LIST_BG_LARGE,
	ICON_POPUP_LIST_BG_SMALL,
	ICON_POPUP_LIST_BG_MID,
	ICON_POPUP_LIST_TITLE,
	ICON_POPUP_LIST_TITLE_MID,
	ICON_POPUP_LIST_TITLE_LARGE,
	ICON_POPUP_LIST_TITLE_SMALL,

	ICON_POPUP_LIST_SEL_L,
	ICON_POPUP_LIST_SEL_C,
	ICON_POPUP_LIST_SEL_R,
	ICON_POPUP_LIST_ARROW_L,
	ICON_POPUP_LIST_ARROW_L_PRESS,
	ICON_POPUP_LIST_ARROW_R,
	ICON_POPUP_LIST_ARROW_R_PRESS,

	// Input Mode
	ICON_INPUTMODE_ABC,
	ICON_INPUTMODE_Abc,
	ICON_INPUTMODE_abc,
	ICON_INPUTMODE_T9ABC,
	ICON_INPUTMODE_T9Abc,
	ICON_INPUTMODE_T9abc,
	ICON_INPUTMODE_123,

	ICON_INPUTMODE_HEBREW,
	ICON_INPUTMODE_HEBREWT9,

	// CHINESE INPUT EDITOR ICON - 2006.08.23 - JeongJiMyong
	ICON_T9SEL_UP_ARROW,
	ICON_T9SEL_DOWN_ARROW,
	ICON_INPUTMODE_T9BPMF,
	ICON_INPUTMODE_T9PINYIN,
	ICON_INPUTMODE_T9STROKES,
	ICON_INPUTMODE_T9STROKET,
	ICON_INPUTMODE_THAI,
	ICON_INPUTMODE_T9THAI,
	ICON_INPUTMODE_KOREAN,
	ICON_CHSINPUT_DIMBG,
	ICON_CHSINPUT_SELBG,
	ICON_CHSINPUT_SELBLOCK,
	ICON_CHSSTROKE_CURSOR,		
	ICON_CHSSTROKE_HORIZON,		
	ICON_CHSSTROKE_VERTICAL,	
	ICON_CHSSTROKE_FALLINGLEFT,	
	ICON_CHSSTROKE_FALLINGRIGHT,
	ICON_CHSSTROKE_TURNING,		
	ICON_CHSSTROKE_QUESTION,	

	// POPUP HasArrow Icon   by Lee Bo-Rah		2004.11.05
	ICON_LIST_14_POPUP_ARROW,
	ICON_LIST_16_POPUP_ARROW,

	// Symbol 창의 Enter/ Space Image Icon		[2006.11.01, by heyviolet]
	ICON_SYMBOL_ENTER,
	ICON_SYMBOL_SPACE,
	ICON_SYMBOL_DOWNARROW,
	ICON_SYMBOL_UPARROW,
	ICON_SYMBOL_KEYPAD_BG,

	// Landscape UI 지원
	ICON_POPUP_MENU_1ST_BG_TOP_320,
	ICON_POPUP_MENU_1ST_BG_MIDDLE_320,
	ICON_POPUP_MENU_1ST_BG_BOTTOM_320,
	ICON_POPUP_MENU_2ST_BG_TOP_320,
	ICON_POPUP_MENU_2ST_BG_MIDDLE_320,
	ICON_POPUP_MENU_2ST_BG_BOTTOM_320,

	ICON_POPUP_BOX_BG_320,
	ICON_POPUP_BOX_TITLE_320,
	ICON_POPUP_ONEBUT_VERT,
	ICON_POPUP_ONEBUT_PRESS_VERT,
	ICON_POPUP_TWOBUT_L_VERT,
	ICON_POPUP_TWOBUT_L_PRESS_VERT,
	ICON_POPUP_TWOBUT_R_VERT,
	ICON_POPUP_TWOBUT_R_PRESS_VERT,

	ICON_POPUP_BG_ECC,				// = ICON_POPUP_BOX_BG_320 동일
	ICON_POPUP_TITLELINE_ECC,		// popup list의 title line
	ICON_POPUP_BUTTON1_ECC,			// = ICON_POPUP_ONEBUT_VERT
	ICON_POPUP_BUTTON1_PRESS_ECC,	// = ICON_POPUP_ONEBUT_PRESS_VERT
	ICON_POPUP_BUTTON2_ECC,			// = ICON_POPUP_TWOBUT_L_VERT = ICON_POPUP_TWOBUT_R_VERT 동일
	ICON_POPUP_BUTTON2_PRESS_ECC,	// = ICON_POPUP_TWOBUT_L_PRESS_VERT = ICON_POPUP_TWOBUT_R_PRESS_VERT 동일


	ICON_INPUTMETHOD,			//	Input method icon, 2007.04,12 maenghs
	ICON_INPUTMETHOD_PRESS,

	ICON_INPUTMODE_abc_PRESS,	//	Pressed edit mode icon
	ICON_INPUTMODE_Abc_PRESS,
	ICON_INPUTMODE_ABC_PRESS,
	ICON_INPUTMODE_T9ABC_PRESS,
	ICON_INPUTMODE_T9Abc_PRESS,
	ICON_INPUTMODE_T9abc_PRESS,
	ICON_INPUTMODE_123_PRESS,
	ICON_INPUTMODE_T9BPMF_PRESS,
	ICON_INPUTMODE_T9PINYIN_PRESS,
	ICON_INPUTMODE_T9STROKES_PRESS,
	ICON_INPUTMODE_T9STROKET_PRESS,
	ICON_INPUTMODE_CHN_TRAD,
	ICON_INPUTMODE_CHN_SIMP,
	ICON_INPUTMODE_CHN_TRAD_PRESS,
	ICON_INPUTMODE_CHN_SIMP_PRESS,
	ICON_INPUTMODE_THAI_PRESS,
	ICON_INPUTMODE_T9THAI_PRESS,
	ICON_INPUTMODE_KOREAN_PRESS,

	//	KeypadCtrl Icon			//	2007.03.02 maenghs
	ICON_KEYPAD_DEFAULT,
	ICON_KEYPAD_SMALL,
	ICON_KEYPAD_NORMAL,
	ICON_KEYPAD_LARGE,

	//	qwerty button
	ICON_QWERTY_OK,
	ICON_QWERTY_PRESS_OK,
	ICON_QWERTY_OPTION,
	ICON_QWERTY_PRESS_OPTION,
	ICON_QWERTY_BACK,
	ICON_QWERTY_PRESS_BACK,
	ICON_QWERTY_MODE,
	ICON_QWERTY_PRESS_MODE,

	ICON_QWERTY_SOFT,
	ICON_QWERTY_SOFT_PRESS,
	ICON_QWERTY_SAVE,
	ICON_QWERTY_SAVE_PRESS,
	
	//	hand writing
	ICON_HANDWRITING_BOX,

	//	@maenghs[2008-06-09] call keypad image
	ICON_KEYPAD_CALL_BG,
	ICON_KEYPAD_CALL_NO_SPEAKER_BG, //20101222 david.choi@lge.com - Call Keypad BG image withoug speaker
	ICON_KEYPAD_CALL_EMERGENCY_BG,  //20110318 david.choi@lge.com - Call keypad BG image for emergency call
	ICON_KEYPAD_CALL_1,
	ICON_KEYPAD_CALL_2,
	ICON_KEYPAD_CALL_3,
	ICON_KEYPAD_CALL_4,
	ICON_KEYPAD_CALL_5,
	ICON_KEYPAD_CALL_6,
	ICON_KEYPAD_CALL_7,
	ICON_KEYPAD_CALL_8,
	ICON_KEYPAD_CALL_9,
	ICON_KEYPAD_CALL_STAR,
	ICON_KEYPAD_CALL_0,
	ICON_KEYPAD_CALL_SHARP,
	ICON_KEYPAD_CALL_SHARP_NO_SPEAKER, //20101222 david.choi@lge.com - # Key image withoug speaker

	//password keypad image
	ICON_KEYPAD_PW_BG,
	ICON_KEYPAD_PW_1,
	ICON_KEYPAD_PW_2,
	ICON_KEYPAD_PW_3,
	ICON_KEYPAD_PW_4,
	ICON_KEYPAD_PW_5,
	ICON_KEYPAD_PW_6,
	ICON_KEYPAD_PW_7,
	ICON_KEYPAD_PW_8,
	ICON_KEYPAD_PW_9,
	ICON_KEYPAD_PW_STAR,
	ICON_KEYPAD_PW_0,
	ICON_KEYPAD_PW_SHARP,

	//	Chinese T9 Input
	ICON_KEYPAD_STROKE_HORIZON,
	ICON_KEYPAD_STROKE_VERTICAL,
	ICON_KEYPAD_STROKE_FALLINGLEFT,
	ICON_KEYPAD_STROKE_FALLINGRIGHT,
	ICON_KEYPAD_STROKE_TURNING,
	ICON_KEYPAD_STROKE_QUESTION,

	//Navigation Softkey
	ICON_KEYPAD_SOFTKEY_LEFT,	
	ICON_KEYPAD_SOFTKEY_LEFT_PRESS, 
	ICON_KEYPAD_SOFTKEY_UP,
	ICON_KEYPAD_SOFTKEY_UP_PRESS,
	ICON_KEYPAD_SOFTKEY_DOWN,	
	ICON_KEYPAD_SOFTKEY_DOWN_PRESS,		
	ICON_KEYPAD_SOFTKEY_RIGHT,	
	ICON_KEYPAD_SOFTKEY_RIGHT_PRESS, 
	ICON_KEYPAD_SCROLL_UP,
	ICON_KEYPAD_SCROLL_UP_PRESS,
	ICON_KEYPAD_SCROLL_DOWN,	
	ICON_KEYPAD_SCROLL_DOWN_PRESS,		
	
	
	ICON_SLIDING_BUTTON_BG,
	ICON_SLIDING_BUTTON_BAR_ON,
	ICON_SLIDING_BUTTON_BAR_OFF,
	ICON_SLIDING_BUTTON_BAR_SNOOZE,
	ICON_KEYPAD_STAR_SHARP_DIM_BG,

	ICON_END

} E_ICON;

#define	ICON_INPUTMODE_LARGEENG		ICON_INPUTMODE_ABC
#define ICON_INPUTMODE_INITENG		ICON_INPUTMODE_Abc
#define ICON_INPUTMODE_SMALLENG		ICON_INPUTMODE_abc
#define ICON_INPUTMODE_LARGET9		ICON_INPUTMODE_T9ABC
#define ICON_INPUTMODE_INITT9		ICON_INPUTMODE_T9Abc
#define ICON_INPUTMODE_SMALLT9		ICON_INPUTMODE_T9abc
#define ICON_INPUTMODE_NUMBER		ICON_INPUTMODE_123

typedef struct
{
	T_HANDLE			Handle;
	int				MaxIcon;
	TImage**			ImageList;
} TIconList;

//	IconList Macro Member Functions
#define		IconList_GetOemImage(I)		IconList_GetImage (NULL, I)
				

extern T_HANDLE			IconList_Create         (void);
extern BOOL			IconList_Destroy        (T_HANDLE hIL);

extern BOOL			IconList_ResetAllImages (T_HANDLE hIL);
extern int			IconList_AddImage       (T_HANDLE hIL, TImage* pImage, TImage* pLargeImage);
extern BOOL			IconList_RemoveImage    (T_HANDLE hIL, int nIndex);
extern TImage*			IconList_GetImage       (T_HANDLE hIL, int nIndex);
extern TImage*			IconList_GetLargeImage  (T_HANDLE hIL, int nIndex);


#endif	//	_BNSOFT_PEANUT_ICONLIST_H_
