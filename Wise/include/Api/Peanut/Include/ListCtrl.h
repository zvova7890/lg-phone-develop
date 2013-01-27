/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	PEANUT LIST CONTROL

	Copyright(c) 1997-2003 BNSoft Corp.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT_PEANUT_LISTCTRL_H_
#define		_BNSOFT_PEANUT_LISTCTRL_H_

#include	"FrmCtrl.h"
#include	"IconList.h"
#include	"MacroFunc/ListCtrlM.h"

#define		LISTSTY_BORDER			FRMSTY_BORDER		//  0x80000000
#define		LISTSTY_TITLE			FRMSTY_TITLE		//  0x40000000
#define		LISTSTY_LEFTTITLE		FRMSTY_LEFTTITLE	//  0x20000000
#define		LISTSTY_LEFTTOPTITLE		FRMSTY_LEFTTOPTITLE	//  0x00800000
#define		LISTSTY_VSCROLLBAR		FRMSTY_VSCROLLBAR	//  0x10000000
#define		LISTSTY_HSCROLLBAR		FRMSTY_HSCROLLBAR	//  0x08000000
#define		LISTSTY_ALWAYSSHOWSB		FRMSTY_ALWAYSSHOWSB	//  0x04000000
#define		LISTSTY_TITLETICKER		FRMSTY_TITLETICKER	//  0x02000000
#define		LISTSTY_FLICKSCROLL 		FRMSTY_FLICKSCROLL
#define		LISTSTY_CHILDCTRL_NOFLICK	FRMSTY_CHILDCTRL_NOFLICK

#define		LISTSTY_CHECK			0x00008000
#define		LISTSTY_RIGHTCHECK		0x00004000
#define		LISTSTY_ONECHECK		0x00002000
#define		LISTSTY_CIRCULAR		0x00001000
#define		LISTSTY_NUMBERICON		0x00000800
#define		LISTSTY_ICON			0x00000400
#define		LISTSTY_INVERSE			0x00000200
#define		LISTSTY_BOLD			0x00000100
#define		LISTSTY_UNDERLINE		0x00000080
#define		LISTSTY_TICKER			0x00000040
#define		LISTSTY_ALWAYSSELECT	        0x00000020
#define		LISTSTY_ELLIPSIS		0x00000010
#define		LISTSTY_HIGHLIGHT		0x00010000

#define		LISTSTY_ONETOUCH		0x00000008
#define		LISTSTY_TWOTOUCH		0x00000004
#define		LISTSTY_RDOCHECK		0x00000002
#define		LISTSTY_NOMOVESEL		0x00040000
#define		LISTSTY_MENUICON		0x00020000

#define		LISTSTY_SELECTDISABLE		 0x00000001
#define		LISTSTY_SHOWSELECT		(LISTSTY_INVERSE | LISTSTY_BOLD | LISTSTY_UNDERLINE)
#define		LISTSTY_DEF			(FRMSTY_DEF | LISTSTY_CIRCULAR | LISTSTY_INVERSE | LISTSTY_TICKER | LISTSTY_ONETOUCH)

#define		LISTNOTI_ERASEBKGND		NOTIMASK_ERASEBKGND
#define		LISTNOTI_POSTDRAW		NOTIMASK_POSTDRAW
#define		LISTNOTI_PREKEY			NOTIMASK_PREKEY
#define		LISTNOTI_POSTKEY		NOTIMASK_POSTKEY
#define		LISTNOTI_TITLEDRAW		NOTIMASK_TITLEDRAW
#define		LISTNOTI_HASVSCROLL		NOTIMASK_HASVSCROLL
#define		LISTNOTI_SELCHANGED		0x08000000
#define		LISTNOTI_POINTING		0x04000000
#define		LISTNOTI_POINTINGCHECK		0x02000000
#define		LISTNOTI_VISIBLEINDEX		0x00200000
#define		LISTNOTI_POPUPSCROLL		0x00100000
#define		LISTNOTI_SELCTRLINDEX		0x00008000
#define		LISTNOTI_VFONTCHANGED		0x00004000
#define		LISTNOTI_DRAGANDDROP		0x00000100

#define		LISTITEM_HASICON		0x8000
#define		LISTITEM_HASARROW		0x4000
#define		LISTITEM_HASSEPARATOR		0x2000
#define		LISTITEM_NOSENSITIVE		0x1000
#define		LISTITEM_TOUCHDOWN		0x0200

#define		LISTITEM_HASNOSELBAR		0x0100
#define		LISTITEM_DISABLE		0x0080
#define		LISTITEM_CHECKED		0x0040
#define		LISTITEM_STRIKETHROUGH		0x0020
#define		LISTITEM_HASHEIGHT		0x0010
#define		LISTITEM_NOCHECK		0x0004
#define		LISTITEM_HASCTRL		0x0002
#define		LISTITEM_BOLD			0x0001

typedef enum
{
	LISTCOL_BACKGROUND				= FRMCOL_BACKGROUND,
	LISTCOL_FOREGROUND				= FRMCOL_FOREGROUND,
	LISTCOL_BORDER_LT				= FRMCOL_BORDER_LT,
	LISTCOL_BORDER_RB				= FRMCOL_BORDER_RB,
	LISTCOL_TITLE_BACKGROUND			= FRMCOL_TITLE_BACKGROUND,
	LISTCOL_TITLE_TEXT				= FRMCOL_TITLE_TEXT,
	LISTCOL_TITLE_UNDERLINE				= FRMCOL_TITLE_UNDERLINE,
	LISTCOL_NORMAL_TEXT,
	LISTCOL_DISABLE_TEXT,
	LISTCOL_SELECT_TEXT,
	LISTCOL_SELECT_BACKGROUND,
	LISTCOL_MULTISEL_TEXT,
	LISTCOL_MULTISEL_BACKGROUND,
	LISTCOL_SEPARATOR1,
	LISTCOL_SEPARATOR2,
	LISTCOL_NUM
} E_LISTCOL;

#define		MAX_LISTITEMICON_NUM		4
#define		MAX_LISTITEMCTRL_NUM		3

#define		ICONFLAG_FREE			0x00
#define		ICONFLAG_USED			0x80
#define		ICONFLAG_POSMASK		0x0F
#define		ICONFLAG_NORMAL			0
#define		ICONFLAG_ENDOFLINE		1
#define		ICONFLAG_ENDOFSTR		2
#define		ICONFLAG_CURRENT		3
#define		ICONFLAG_NORMAL_2LINE		4
#define		ICONFLAG_ENDOFLINE_2LINE	5

#define		LISTCTRL_SCRLALIGN_TOP		1

typedef struct
{
	BYTE				Flag;
	BYTE				Padding;
	WORD				IconID;
	int				Distance;
} TListItemIcon;

typedef struct
{
	T_CSTR				pcszHLStr;
	T_COLOR				uColor;
	QUAD				qData;
} TListHighLight;

typedef struct
{
	T_CSTR				pcszStr;
	H_CTRL				hItemCtrlTbl[MAX_LISTITEMCTRL_NUM];
	T_SIZE				Height;
	QUAD				Data;
	WORD				Status;
	TListItemIcon		IconTbl[MAX_LISTITEMICON_NUM];
	TListHighLight		stHighlight;
} TListItem;

typedef struct
{
	TFrmCtrl	    Frame;
	TListItem*	    pItemTbl;
	T_NUM		    MaxItemNum;
	T_NUM		    ItemNum;
	int		    SelIndex;
	TRect		    SelRange;
	int		    LineGap;
	int		    InvOffset;
	int		    TotalHeight;
        int		    LineHeight;
        TPoint		    Scroll;
        TIconList*          pIconList;
        int		    LeftMargin;
        int		    RightMargin;
        T_NUM		    MultiLineNum;
        int		    TickerPos;
        int		    DownIndex;
        QUAD		    FlickScroll;
        BOOL                bTimerDraw;
        TPoint              PrevScroll;
} TListCtrl;



//	Create & Destroy Functions
extern H_CTRL			ListCtrl_Create          (void* pOwner, T_POS X, T_POS Y, T_SIZE W, T_SIZE H);
extern BOOL			ListCtrl_Destroy         (H_CTRL hLC);

//	Overriding Functions

//	ListCtrl Own Functions
extern BOOL			ListCtrl_SetLineGap      (H_CTRL hLC, int LineGap);
extern BOOL			ListCtrl_SetInvOffset    (H_CTRL hLC, int InvOffset);
extern BOOL			ListCtrl_SetStr          (H_CTRL hLC, int Index, T_CSTR pcszStr);
extern BOOL			ListCtrl_SetData         (H_CTRL hLC, int Index, QUAD Data);
extern BOOL			ListCtrl_SetIcon         (H_CTRL hLC, int Index, QUAD IconID);
extern BOOL			ListCtrl_SetIconEx       (H_CTRL hLC, int Index, int IconIndex, QUAD IconID, int BasePos, int Dist);
extern BOOL			ListCtrl_SetLeftMargin   (H_CTRL hLC, int LeftMargin);
extern BOOL			ListCtrl_SetRightMargin  (H_CTRL hLC, int RightMargin);
extern BOOL			ListCtrl_SetMultiLineNum (H_CTRL hLC, T_NUM MultiLineNum);

extern TListItem*		ListCtrl_GetItem         (H_CTRL hLC, int Index);
extern T_CSTR			ListCtrl_GetStr          (H_CTRL hLC, int Index);
extern QUAD			ListCtrl_GetData         (H_CTRL hLC, int Index);
extern WORD			ListCtrl_GetStatus       (H_CTRL hLC, int Index);
extern WORD			ListCtrl_GetIcon         (H_CTRL hLC, int Index);
extern int			ListCtrl_GetLeftMargin   (H_CTRL hLC);
extern int			ListCtrl_GetRightMargin  (H_CTRL hLC);
extern T_NUM			ListCtrl_GetMultiLineNum (H_CTRL hLC);
extern int			ListCtrl_GetSelIndex     (H_CTRL hLC);
extern TListItem*		ListCtrl_GetSelItem      (H_CTRL hLC);
extern T_CSTR			ListCtrl_GetSelStr       (H_CTRL hLC);
extern QUAD			ListCtrl_GetSelData      (H_CTRL hLC);
extern TRect*			ListCtrl_GetSelRange     (H_CTRL hLC);
extern int			ListCtrl_GetLineGap      (H_CTRL hLC);
extern int			ListCtrl_GetInvOffset    (H_CTRL hLC);
extern int			ListCtrl_GetItemNum      (H_CTRL hLC);

extern BOOL			ListCtrl_AttachIconList  (H_CTRL hLC, T_HANDLE hIconList);
extern BOOL			ListCtrl_ResetAllItems   (H_CTRL hLC);
extern BOOL			ListCtrl_ResetTicker     (H_CTRL hLC);
extern BOOL			ListCtrl_AddItem         (H_CTRL hLC, T_CSTR pcszStr, QUAD Data, QUAD IconID);
extern BOOL			ListCtrl_AddSeparator    (H_CTRL hLC);
extern BOOL			ListCtrl_InsertItem      (H_CTRL hLC, int Index, T_CSTR pcszStr, QUAD Data, QUAD IconID);
extern BOOL			ListCtrl_DeleteItem      (H_CTRL hLC, int Index);
extern BOOL			ListCtrl_SelectItem      (H_CTRL hLC, int Index);
extern int			ListCtrl_SelectNextItem  (H_CTRL hLC);
extern int			ListCtrl_SelectPrevItem  (H_CTRL hLC);
extern BOOL			ListCtrl_SetStatus       (H_CTRL hLC, int Index, WORD RemoveStatus, WORD AddStatus);
extern BOOL			ListCtrl_CheckItem       (H_CTRL hLC, int Index, BOOL bCheck);
extern BOOL			ListCtrl_EnableItem      (H_CTRL hLC, int Index, BOOL bEnable);
extern BOOL			ListCtrl_EnsureVisible   (H_CTRL hLC, int Index);
extern T_SIZE			ListCtrl_CalcFullHeight  (H_CTRL hLC);
extern BOOL			ListCtrl_SetHighlight	 (H_CTRL hLC, int Index, T_CSTR pcszStr, T_COLOR Color, QUAD Data);	//@lima++ [2007-11-30¿ÀÈÄ 12:00:01],
extern BOOL			ListCtrl_GetHighlightInfo(H_CTRL hLC, int Index, TListHighLight* pInfo);
extern BOOL			ListCtrl_SetItemHeight	 (H_CTRL hLC, int Index, T_SIZE Height);
extern T_SIZE			ListCtrl_GetItemHeight	 (H_CTRL hLC, int Index);
extern BOOL			ListCtrl_SetItemCtrl	 (H_CTRL hLC, int Index, T_ID ID, H_CTRL hCtrl);
extern H_CTRL			ListCtrl_GetItemCtrl	 (H_CTRL hLC, int Index, T_ID ID);


#endif	//	_BNSOFT_PEANUT_LISTCTRL_H_
