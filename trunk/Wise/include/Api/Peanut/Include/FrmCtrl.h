/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	PEANUT FRAME CONTROL

	Copyright(c) 1997-2003 BNSoft Corp.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT_PEANUT_FRMCTRL_H_
#define		_BNSOFT_PEANUT_FRMCTRL_H_



#include	"BaseCtrl.h"
#include	"ScrlBar.h"


#include	"MacroFunc\FrmCtrlM.h"


#define		FRMSTY_BORDER				0x80000000		
#define		FRMSTY_TITLE				0x40000000		
#define		FRMSTY_LEFTTITLE			0x20000000		
#define		FRMSTY_VSCROLLBAR			0x10000000		
#define		FRMSTY_HSCROLLBAR			0x08000000		
#define		FRMSTY_ALWAYSSHOWSB			0x04000000		
#define		FRMSTY_TITLETICKER			0x02000000		
#define		FRMSTY_FLICKSCROLL			0x01000000		
#define		FRMSTY_LEFTTOPTITLE			0x00800000		
#define		FRMSTY_FLICKSCROLL_HORIZONTAL           0x00400000			
#define		FRMSTY_SOFTMENU				0x00200000		
#define		FRMSTY_CHILDCTRL_NOFLICK	        0x00100000			
#define		FRMSTY_MOVEOUTPOINT			0x00080000		

#define		FRMSTY_DEF					(FRMSTY_BORDER|FRMSTY_FLICKSCROLL)

#define		FRMNOTI_ERASEBKGND			NOTIMASK_ERASEBKGND	//	0x80000000	
#define		FRMNOTI_POSTDRAW			NOTIMASK_POSTDRAW	//	0x40000000	
#define		FRMNOTI_PREKEY				NOTIMASK_PREKEY		//	0x20000000	
#define		FRMNOTI_POSTKEY				NOTIMASK_POSTKEY	//	0x10000000	
#define		FRMNOTI_TITLEDRAW			NOTIMASK_TITLEDRAW	//	0x01000000
#define		FRMNOTI_HASVSCROLL			NOTIMASK_HASVSCROLL     //	0x00000001	
#define		FRMNOTI_FLICK				0x00080000		//	0x00080000

typedef enum
{
	FRMCOL_BACKGROUND				= 0,
	FRMCOL_FOREGROUND,
	FRMCOL_BORDER_LT,										//	Left/Top Border Color
	FRMCOL_BORDER_RB,										//	Right/Bottom Border Color
	FRMCOL_TITLE_BACKGROUND,
	FRMCOL_TITLE_TEXT,
	FRMCOL_TITLE_UNDERLINE,
	FRMCOL_NUM
} E_FRMCOL;

//-------------------------------------------------------------------------------------------------
// Flicking Scroll
//-------------------------------------------------------------------------------------------------

#define		FRMFLICK_START			0x00000000
#define		FRMFLICK_END			0x00000001
#define		FRMFLICK_HORIZONTAL		0x00000002

typedef enum
{
	FRAME_MOVING_STATE_NONE  = 0,
	FRAME_MOVING_STATE_START,
	FRAME_MOVING_STATE_BYPASS,
	FRAME_MOVING_STATE_DRAG,
	FRAME_MOVING_STATE_FLICK,
	FRAME_MOVING_STATE_FLICK_HORIZONTAL,
	FRAME_MOVING_STATE_START_FROM_FLICK 
} E_FRAME_MOVING_STATE;

typedef struct 
{
	int			nBegin;		
	int			nChange;
	int			nCurTime;	
	int			nDuration;	
	
	QUAD		LastDrawTimeMs;		
	T_HANDLE	hTimer;		// Flick Draw duration Timer
	H_PROCESS	hOwnerProcess;
	T_pfnMsgRun	pfnOwnerMsgRun;

	//david.choi
	int			nPrevScroll;
} TFrameMovingInfo;
typedef struct
{
	T_POS	X;
	T_POS	Y;
	QUAD	Time;
} TFrameLastDrawInfo;

#define MAX_POINTING_LOG	10

typedef struct
{
	int 	FirstIndex;
	int 	LastIndex;
	int 	LastDrawIndex;
	T_POS	X[MAX_POINTING_LOG];
	T_POS	Y[MAX_POINTING_LOG];
	QUAD	Time[MAX_POINTING_LOG];
} TFramePointingLog;

typedef struct 
{
	E_FRAME_MOVING_STATE 	State;			
	BOOL			IsVerticalMovingEnabled; 
	BOOL			IsHorizontalMovingEnabled; 
	TFramePointingLog	PointingLog;
	TFrameLastDrawInfo	LastDrawInfo;
	
	TFrameMovingInfo	Info;
	T_POS			ScrollDiff;
	T_POS			InitPosX;
} TFrameMoving;

typedef enum
{
	SIMCOLOR_NONE = 0,
	SIMCOLOR_GREEN,
	SIMCOLOR_PURPLE,
	SIMCOLOR_YELLOW,
	SIMCOLOR_ORANGE,
	SIMCOLOR_MAX,

	//Not Used In DAKOTA
	SIMCOLOR_BLUE,
	SIMCOLOR_RED
} E_SIMCOLOR;

#define		SIMCOLOR_FIRST		SIMCOLOR_GREEN


typedef enum
{
	SIMICON_NONE = 0,
	SIMICON_SIM,
	SIMICON_HOME,
	SIMICON_HEART,
	SIMICON_OFFICE,
	SIMICON_STAR,
	SIMICON_BOMB,
	SIMICON_MAX,

	//Not Used In DAKOTA
	SIMICON_PEOPLE,
	SIMICON_BAG,
	SIMICON_GIFT
} E_SIMICON;

#define SIMICON_LOCK SIMICON_BOMB

typedef enum
{
	SIMSELECT_NONE = 0,
	SIMSELECT_SIM1,
	SIMSELECT_SIM2,
	SIMSELECT_MAX

}  E_SELECTSIM;

/// data members of frame control
typedef struct
{
	TBaseCtrl			Base;
	TRect				ClientRect;
	TRect				WorkArea;
	T_CSTR				pcszTitle;
	E_FONT				enTitleFont;
	T_SIZE				TitleHeight;
	T_SIZE				TitleLeftMargin;
	T_SIZE				TitleRightMargin;
	TScrlBar*			pVScrollBar;
	TScrlBar*			pHScrollBar;
	TFrameMoving		FrameMoving;	// For Frame Moving(Flicking Scroll)
	
} TFrmCtrl;

#define		FRMCTRL_DELTA_LEFT		2
#define		FRMCTRL_DELTA_RIGHT		2
#define		FRMCTRL_DELTA_TOP		2
#define		FRMCTRL_DELTA_BOTTOM		2


//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//	Create & Destroy Functions
extern H_CTRL			FrmCtrl_Create           (void* pOwner, T_POS X, T_POS Y, T_SIZE W, T_SIZE H);
extern BOOL			FrmCtrl_Destroy          (H_CTRL hFC);

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//	Overriding Functions
extern BOOL			FrmCtrl_ModifyStyle      (H_CTRL hFC, QUAD RemoveStyle, QUAD AddStyle);
extern BOOL			FrmCtrl_SetRange         (H_CTRL hFC, T_POS X1, T_POS Y1, T_POS X2, T_POS Y2);
extern BOOL			FrmCtrl_SetPos           (H_CTRL hFC, T_POS X, T_POS Y);
extern BOOL			FrmCtrl_SetSize          (H_CTRL hFC, T_SIZE W, T_SIZE H);

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//	FrmCtrl Own Functions
extern BOOL			FrmCtrl_SetClientRect    (H_CTRL hFC, T_POS X1, T_POS Y1, T_POS X2, T_POS Y2);
extern BOOL			FrmCtrl_SetClientPos     (H_CTRL hFC, T_POS X, T_POS Y);
extern BOOL			FrmCtrl_SetClientSize    (H_CTRL hFC, T_SIZE W, T_SIZE H);
extern BOOL			FrmCtrl_SetDelta         (H_CTRL hFC, int DeltaX, int DeltaY);
extern BOOL			FrmCtrl_SetDelta2        (H_CTRL hFC, int DeltaX2, int DeltaY2);
extern BOOL			FrmCtrl_SetTitle         (H_CTRL hFC, T_CSTR rcszTitle);
extern BOOL			FrmCtrl_SetTitleFont     (H_CTRL hFC, E_FONT enFont);
extern BOOL			FrmCtrl_SetTitleHeight   (H_CTRL hFC, T_SIZE Height);
extern BOOL			FrmCtrl_SetTitleLeftMargin(H_CTRL hFC, T_SIZE LeftMargin);
extern BOOL			FrmCtrl_SetTitleRightMargin(H_CTRL hFC, T_SIZE RightMargin);

extern TRect*			FrmCtrl_GetClientRect    (H_CTRL hFC);
extern T_POS			FrmCtrl_GetClientPosX    (H_CTRL hFC);
extern T_POS			FrmCtrl_GetClientPosY    (H_CTRL hFC);
extern T_SIZE			FrmCtrl_GetClientWidth   (H_CTRL hFC);
extern T_SIZE			FrmCtrl_GetClientHeight  (H_CTRL hFC);
extern TRect*			FrmCtrl_GetWorkArea      (H_CTRL hFC);
extern T_POS			FrmCtrl_GetWorkPosX      (H_CTRL hFC);
extern T_POS			FrmCtrl_GetWorkPosY      (H_CTRL hFC);
extern T_SIZE			FrmCtrl_GetWorkWidth     (H_CTRL hFC);
extern T_SIZE			FrmCtrl_GetWorkHeight    (H_CTRL hFC);
extern int			FrmCtrl_GetDeltaX1       (H_CTRL hFC);
extern int			FrmCtrl_GetDeltaY1       (H_CTRL hFC);
extern int			FrmCtrl_GetDeltaX2       (H_CTRL hFC);
extern int			FrmCtrl_GetDeltaY2       (H_CTRL hFC);
extern T_CSTR			FrmCtrl_GetTitle         (H_CTRL hFC);
extern E_FONT			FrmCtrl_GetTitleFont     (H_CTRL hFC);
extern T_SIZE			FrmCtrl_GetTitleHeight   (H_CTRL hFC);
extern T_SIZE			FrmCtrl_GetTitleLeftMargin(H_CTRL hFC);
extern T_SIZE			FrmCtrl_GetTitleRightMargin(H_CTRL hFC);

extern BOOL			FrmCtrl_AdjustRange      (H_CTRL hFC);
extern BOOL			FrmCtrl_AdjustClientRect (H_CTRL hFC);
extern BOOL			FrmCtrl_AdjustScrollBar  (H_CTRL hFC);
extern BOOL			FrmCtrl_PtInClientRect   (H_CTRL hFC, int X, int Y);

        
#endif	//	_BNSOFT_PEANUT_FRMCTRL_H_
