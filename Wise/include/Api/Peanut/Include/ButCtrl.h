/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	PEANUT BUTTON CONTROL

	Copyright(c) 1997-2002 BNSoft Corp.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT_PEANUT_BUTCTRL_H_
#define		_BNSOFT_PEANUT_BUTCTRL_H_

#include	"BaseCtrl.h"
#include	"MacroFunc\ButCtrlM.h"


#define		BUTSTY_ALPHAIMG		0x80000000				
#define		BUTSTY_ONOFFDRAG	0x40000000				
#define		BUTSTY_ONOFFDRAGPRESS	0x20000000				
#define		BUTSTY_DRAGPRESS	0x10000000				
#define		BUTSTY_DEF		(0)
#define		BUTSTY_NOVFONTCOLOR	0x02000000


#define		BUTNOTI_ERASEBKGND			NOTIMASK_ERASEBKGND	
#define		BUTNOTI_POSTDRAW			NOTIMASK_POSTDRAW	
#define		BUTNOTI_PREKEY				NOTIMASK_PREKEY		
#define		BUTNOTI_POSTKEY				NOTIMASK_POSTKEY	
#define		BUTNOTI_CLICKED				0x08000000			
#define		BUTNOTI_ONOFF				0x04000000		


typedef enum
{
	BUTCOL_BACKGROUND					= 0,
	BUTCOL_FOREGROUND,
	BUTCOL_BACKGROUND_PRESS,						//	Pressed Background Color
	BUTCOL_FOREGROUND_PRESS,						//	Pressed Foreground Color(Font Color)
	BUTCOL_BORDER_LT,							//	Left/Top Border Color
	BUTCOL_BORDER_RB,							//	Right/Bottom Border Color
	BUTCOL_NUM
} E_BUTCOL;

typedef enum
{
	BUTDRAGSTATE_OFF						= 0,
	BUTDRAGSTATE_ON,
	BUTDRAGSTATE_MOVE,
	BUTDRAGSTATE_MOVE_LEFT, //WISE_PEANUT_DUALSIM_SUPPORT
	BUTDRAGSTATE_MOVE_RIGHT, //WISE_PEANUT_DUALSIM_SUPPORT
	BUTDRAGSTATE_MAX
} E_BUTDRAGSTATE;

typedef enum
{
	BUTCTRL_EVENT_NONE					= 0,
	BUTCTRL_ONOFFBAR_SLIDING,
	BUTCTRL_ONOFFBAR_DOWN,	
} E_ONOFFBAR_EVENT;



typedef struct
{
	TBaseCtrl		Base;
	T_CSTR			pcszText;
	TImage*			pImage;			
	TImage*			pPressedImage;
	TImage*			pOnOffBgImage;
	TImage*			pOnDragImage;	
	TImage*			pOffDragImage;	
	TImage*			pOnDragPressedImage;	
	TImage*			pOffDragPressedImage;
	T_POS			OnOffBarPos;		
	E_ONOFFBAR_EVENT	OnOffBarEvent;
	KEY			SelKey;
	T_CSTR			pcszTip;		
	E_BUTDRAGSTATE		DragState;
	T_POS			DragBarX;
} TButCtrl;



//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//	Create & Destroy Functions
extern H_CTRL			ButCtrl_Create    (void* pOwner, T_POS X, T_POS Y, T_SIZE W, T_SIZE H, T_CSTR pcszText);
extern BOOL			ButCtrl_Destroy   (H_CTRL hBC);

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//	Overriding Functions

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//	ButCtrl Own Functions
extern BOOL			ButCtrl_SetText   (H_CTRL hBC, T_CSTR pcszText);
extern BOOL			ButCtrl_SetImage  (H_CTRL hBC, TImage* pImage);

extern BOOL			ButCtrl_SetPressedImage(H_CTRL hBC, TImage* pImage);
extern BOOL			ButCtrl_SetSelKey (H_CTRL hBC, KEY SelKey);

extern T_CSTR			ButCtrl_GetText   (H_CTRL hBC);
extern TImage*			ButCtrl_GetImage  (H_CTRL hBC);
extern KEY			ButCtrl_GetSelKey (H_CTRL hBC);
extern BOOL			ButCtrl_SetTip	(H_CTRL hBC, T_CSTR psczText);


#endif	//	_BNSOFT_PEANUT_BUTCTRL_H_
