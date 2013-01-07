/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	PEANUT DIALOG

	Copyright(c) 1997-2003 BNSoft Corp.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT_PEANUT_DIALOG_H_
#define		_BNSOFT_PEANUT_DIALOG_H_

#include	"FrmCtrl.h"
#include	"MacroFunc\DialogM.h"

//	Dialog Style
#define		DLGSTY_BORDER				FRMSTY_BORDER		//	0x80000000	
#define		DLGSTY_TITLE				FRMSTY_TITLE		//	0x40000000	
#define		DLGSTY_LEFTTITLE			FRMSTY_LEFTTITLE	//	0x20000000	
#define		DLGSTY_LEFTTOPTITLE			FRMSTY_LEFTTOPTITLE	//      0x00800000
#define		DLGSTY_HSCROLLBAR			FRMSTY_HSCROLLBAR	//	0x10000000	
#define		DLGSTY_VSCROLLBAR			FRMSTY_VSCROLLBAR	//	0x08000000	
#define		DLGSTY_ALWAYSSHOWSB			FRMSTY_ALWAYSSHOWSB	//	0x04000000	
#define		DLGSTY_TITLETICKER			FRMSTY_TITLETICKER	//	
#define		DLGSTY_FLICKSCROLL			FRMSTY_FLICKSCROLL	
#define		DLGSTY_FLICKSCROLL_HORIZONTAL	FRMSTY_FLICKSCROLL_HORIZONTAL	


#define		DLGSTY_SOFTMENU				FRMSTY_SOFTMENU	
#define		DLGSTY_CIRCULAR				0x00004000	

#define		DLGSTY_DEF					(DLGSTY_TITLE /*| DLGSTY_SOFTMENU */| DLGSTY_CIRCULAR)


#define		DLGNOTI_ERASEBKGND		NOTIMASK_ERASEBKGND	//	0x80000000
#define		DLGNOTI_POSTDRAW		NOTIMASK_POSTDRAW	//	0x40000000	
#define		DLGNOTI_PREKEY			NOTIMASK_PREKEY		//	0x20000000	
#define		DLGNOTI_POSTKEY			NOTIMASK_POSTKEY	//	0x10000000	
#define		DLGNOTI_HASVSCROLL		NOTIMASK_HASVSCROLL     //	0x00000001
#define		DLGNOTI_FLICK			FRMNOTI_FLICK		//	0x00080000
#define		DLGNOTI_TIMER			0x08000000		//	
#define		DLGNOTI_TIMEOUT			0x04000000		//	
#define		DLGNOTI_FOCUSCHANGED		0x02000000		//	
#define		DLGNOTI_TITLEDRAW		NOTIMASK_TITLEDRAW	//  0x01000000  
#define		DLGNOTI_SOFTMENUPOINTING	0x00020000              //  0x00800000  softmenu point down시에 noti발생
#define		DLGNOTIFLICK_ACTIVECTRLOUT	0x00001000	        //


typedef enum
{
	DLGCOL_BACKGROUND				= FRMCOL_BACKGROUND,
	DLGCOL_FOREGROUND				= FRMCOL_FOREGROUND,
	DLGCOL_BORDER_LT				= FRMCOL_BORDER_LT,
	DLGCOL_BORDER_RB				= FRMCOL_BORDER_RB,
	DLGCOL_TITLE_BACKGROUND				= FRMCOL_TITLE_BACKGROUND,
	DLGCOL_TITLE_TEXT				= FRMCOL_TITLE_TEXT,
	DLGCOL_TITLE_UNDERLINE				= FRMCOL_TITLE_UNDERLINE,
	DLGCOL_NUM
} E_DLGCOL;


typedef struct
{
	H_CTRL				hCtrl;
	T_ID				ID;
} TDlgCtrl;

typedef struct
{
	TSLnkObj			LnkObj;								//	Single Linked List Object
	TDlgCtrl			DlgCtrl;							//	Dialog Ctrl
} TDlgCtrlObj;

#define		DLG_DRAW_ALL			0
#define		DLG_DRAW_FLOATING		2

typedef struct
{
	TFrmCtrl			Frame;
	T_SIZE				Width;								//	다이알로그 내용의 전체 폭 (이 범위안에서 스크롤이 이루어진다)
	T_SIZE				Height;								//	다이알로그 내용의 전체 높이
	T_CSTR				pcszLSoftMenu;
	T_CSTR				pcszMSoftMenu;
	T_CSTR				pcszRSoftMenu;
	TPoint				Scroll;
	int					ActiveCtrlIndex;
	BOOL				bButttonPointing;
	T_NUM				CtrlNum;
	T_NUM				TitleCtrlNum;
	KEY					PrevKey;
	KEY					NextKey;
	BOOL				bShowCursor;
	TLnkList			DlgCtrlList;
	TLnkList			TitleCtrlList;
	QUAD				IconIDTbl[5];					// softmenu IconID(image) array
	QUAD				SMType;						// softmenu type - icon(OEM_SOFTSTY_ICON) or general
	H_CTRL				hFloating;					// Active for KeypadCtrl 
	QUAD				nNotiFromEdit;
} TDialog;
															//	{{BNS_INTERNALCODE(-)}}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//	Create & Destroy Functions


extern H_CTRL		Dialog_CreateEx             (void);
extern BOOL		Dialog_DestroyEx            (H_CTRL hDlg);

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//	Overriding Functions
extern BOOL				Dialog_ModifyStyle        (H_CTRL hDlg, QUAD RemoveStyle, QUAD AddStyle);
extern BOOL				Dialog_SetRange           (H_CTRL hDlg, T_POS X1, T_POS Y1, T_POS X2, T_POS Y2);

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//	Dialog Own Functions
extern H_CTRL			Dialog_CreateButCtrl      (H_CTRL hDlg, T_ID ID, T_POS X, T_POS Y, T_SIZE W, T_SIZE H, T_CSTR pcszText);
extern H_CTRL			Dialog_CreateChkCtrl      (H_CTRL hDlg, T_ID ID, T_POS X, T_POS Y, T_SIZE W, T_SIZE H, T_CSTR pcszText);
extern H_CTRL			Dialog_CreateEditCtrl     (H_CTRL hDlg, T_ID ID, T_POS X, T_POS Y, T_SIZE W, T_SIZE H, T_NUM MaxChar);
extern H_CTRL			Dialog_CreateEditCtrlEx   (H_CTRL hDlg, T_ID ID, T_POS X, T_POS Y, T_SIZE W, T_SIZE H, T_NUM MaxChar, QUAD AddStyle);
extern H_CTRL			Dialog_CreateIconCtrl     (H_CTRL hDlg, T_ID ID, T_POS X, T_POS Y, TImage* pImage);
extern H_CTRL			Dialog_CreateImgCtrl      (H_CTRL hDlg, T_ID ID, T_POS X, T_POS Y, T_SIZE W, T_SIZE H, T_CSTR pcszFileName);
extern H_CTRL			Dialog_CreateKeypadCtrl   (H_CTRL hDlg, T_ID ID, T_POS X, T_POS Y, T_SIZE W, T_SIZE H);
extern H_CTRL			Dialog_CreateLineCtrl     (H_CTRL hDlg, T_ID ID, T_POS X1, T_POS Y1, T_POS X2, T_POS Y2);
extern H_CTRL			Dialog_CreateListCtrl     (H_CTRL hDlg, T_ID ID, T_POS X, T_POS Y, T_SIZE W, T_SIZE H);
extern H_CTRL			Dialog_CreateRdoCtrl      (H_CTRL hDlg, T_ID ID, T_POS X, T_POS Y, T_SIZE W, T_SIZE H, T_CSTR pcszText, H_CTRL hGrpRC);
extern H_CTRL			Dialog_CreateREditCtrl    (H_CTRL hDlg, T_ID ID, T_POS X, T_POS Y, T_SIZE W, T_SIZE H, T_NUM MaxChar);
extern H_CTRL			Dialog_CreateREditCtrlEx  (H_CTRL hDlg, T_ID ID, T_POS X, T_POS Y, T_SIZE W, T_SIZE H, T_NUM MaxChar, QUAD AddStyle);
extern H_CTRL			Dialog_CreateSelCtrl      (H_CTRL hDlg, T_ID ID, T_POS X, T_POS Y, T_SIZE W, T_SIZE H);
extern H_CTRL			Dialog_CreateTextCtrl     (H_CTRL hDlg, T_ID ID, T_POS X, T_POS Y, T_SIZE W, T_SIZE H, T_CSTR pcszText);
extern H_CTRL			Dialog_CreateListView     (H_CTRL hDlg, T_ID ID, T_POS X, T_POS Y, T_SIZE W, T_SIZE H);

extern BOOL			Dialog_DestroyCtrl        (H_CTRL hDlg, H_CTRL hCtrl);
extern BOOL			Dialog_DestroyAllCtrls    (H_CTRL hDlg);

extern BOOL			Dialog_AttachCtrl         (H_CTRL hDlg, T_ID ID, H_CTRL hCtrl);
extern BOOL			Dialog_DettachCtrl		  (H_CTRL hDlg, H_CTRL hCtrl);

extern BOOL			Dialog_SetSize            (H_CTRL hDlg, T_SIZE W, T_SIZE H);
extern BOOL			Dialog_SetSoftMenu        (H_CTRL hDlg, T_CSTR rcszLSoftMenu, T_CSTR rcszMSoftMenu, T_CSTR rcszRSoftMenu);
extern BOOL			Dialog_SetScroll          (H_CTRL hDlg, T_POS ScrollX, T_POS ScrollY);
extern BOOL			Dialog_SetMoveKey         (H_CTRL hDlg, KEY PrevKey, KEY NextKey);

extern T_POS			Dialog_GetScrollX         (H_CTRL hDlg);
extern T_POS			Dialog_GetScrollY         (H_CTRL hDlg);
extern TDlgCtrl*		Dialog_GetActiveCtrl      (H_CTRL hDlg);

extern BOOL			Dialog_SetActiveCtrl      (H_CTRL hDlg, T_ID ID);
extern T_ID			Dialog_MoveActiveCtrl     (H_CTRL hDlg, int nOffset);
extern BOOL			Dialog_EnsureVisible      (H_CTRL hDlg, T_ID ID);
extern BOOL			Dialog_ShowCursor         (H_CTRL hDlg, BOOL bShow);
extern BOOL			Dialog_SetLocalOrigin     (H_CTRL hDlg);

extern BOOL			Dialog_DrawSoftMenu       (H_CTRL hDlg, BOOL bRefresh);

extern BOOL			Dialog_DoModal            (H_CTRL hDlg, int LifeTime);
extern BOOL			Dialog_StopModal          (void);
extern BOOL			Dialog_EndModal           (void);
	
extern T_SIZE			Dialog_GetScrollMaxY      (H_CTRL hDlg);

extern H_CTRL			Dialog_CreateTitleButCtrl (H_CTRL hDlg, T_ID ID, T_POS X, T_POS Y, T_SIZE W, T_SIZE H, T_CSTR pcszText);
extern BOOL			Dialog_SetSoftMenuIcon    (H_CTRL hDlg, QUAD IconID1, QUAD IconID2, QUAD IconID3, QUAD IconID4, QUAD IconID5);


extern BOOL			DlgCtrl_ModifyStyle       (H_CTRL hDlg, T_ID ID, QUAD RemoveStyle, QUAD AddStyle);
extern BOOL			DlgCtrl_SetRange          (H_CTRL hDlg, T_ID ID, T_POS X1, T_POS Y1, T_POS X2, T_POS Y2);
extern BOOL			DlgCtrl_SetPos            (H_CTRL hDlg, T_ID ID, T_POS X, T_POS Y);
extern BOOL			DlgCtrl_SetSize           (H_CTRL hDlg, T_ID ID, T_SIZE W, T_SIZE H);
extern BOOL			DlgCtrl_SetFont           (H_CTRL hDlg, T_ID ID, E_FONT enFont);

extern E_CTRLTYPE		DlgCtrl_GetType           (H_CTRL hDlg, T_ID ID);
extern TRect*			DlgCtrl_GetRange          (H_CTRL hDlg, T_ID ID);

extern BOOL			DlgCtrl_Draw              (H_CTRL hDlg, T_ID ID, BOOL bRefresh);

extern BOOL			DlgCtrl_SetVisible        (H_CTRL hDlg, T_ID ID, BOOL bOn);
extern BOOL			DlgCtrl_SetEnable         (H_CTRL hDlg, T_ID ID, BOOL bOn);
extern BOOL			DlgCtrl_SetCanFocus       (H_CTRL hDlg, T_ID ID, BOOL bOn);
extern BOOL			DlgCtrl_IsVisible         (H_CTRL hDlg, T_ID ID);
extern BOOL			DlgCtrl_IsEnable          (H_CTRL hDlg, T_ID ID);
extern BOOL			DlgCtrl_IsCanFocus        (H_CTRL hDlg, T_ID ID);

extern H_CTRL			DlgCtrl_GetHandle         (H_CTRL hDlg, T_ID ID);

#endif	//	_BNSOFT_PEANUT_DIALOG_H_
