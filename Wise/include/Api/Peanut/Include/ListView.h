/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	PEANUT LIST VIEW CONTROL

	Copyright(c)   -2007 LG Electronics Inc.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT_PEANUT_LISTVIEW_H_
#define		_BNSOFT_PEANUT_LISTVIEW_H_

#include	"FrmCtrl.h"
#include	"..\..\BasicApiLib\Include\LnkList.h"
//#include	"IconList.h"
#include	"MacroFunc\ListViewM.h"

#define		LISTVIEWSTY_BORDER		FRMSTY_BORDER			//	0x80000000
#define		LISTVIEWSTY_TITLE		FRMSTY_TITLE			//	0x40000000
#define		LISTVIEWSTY_LEFTTITLE		FRMSTY_LEFTTITLE		//	0x20000000
#define		LISTVIEWSTY_LEFTTOPTITLE	FRMSTY_LEFTTOPTITLE		//      0x00800000
#define		LISTVIEWSTY_HSCROLLBAR		FRMSTY_HSCROLLBAR		//	0x10000000
#define		LISTVIEWSTY_VSCROLLBAR		FRMSTY_VSCROLLBAR		//	0x08000000
#define		LISTVIEWSTY_ALWAYSSHOWSB	FRMSTY_ALWAYSSHOWSB		//	0x04000000
#define		LISTVIEWSTY_TITLETICKER		FRMSTY_TITLETICKER		//	0x02000000
#define		LISTVIEWSTY_FLICKSCROLL 	FRMSTY_FLICKSCROLL		//	0x01000000
#define		LISTVIEWSTY_CHILDCTRL_NOFLICK	FRMSTY_CHILDCTRL_NOFLICK
#define		LISTVIEWSTY_CIRCULAR		0x00008000			
#define		LISTVIEWSTY_MULTISELECT		0x00004000		
#define		LISTVIEWSTY_ITEMTICKER		0x00002000		
#define		LISTVIEWSTY_NUMBERICON		0x00001000	
#define		LISTVIEWSTY_TWOTOUCH		0x00000800	
#define		LISTVIEWSTY_VARIABLEITEMHEIGHT	0x00000800
#define		LISTVIEWSTY_UNDERLINE		0x00000400
#define		LISTVIEWSTY_EDITABLESTRING	0x00000200
#define		LISTVIEWSTY_DEF			(FRMSTY_DEF | LISTVIEWSTY_CIRCULAR | LISTVIEWSTY_ITEMTICKER)


#define	LISTVIEWSTY_VFONTCOLOR			0x00000010
#define	LISTVIEWSTY_NOVFONTCOLOR		0x00000010

#define		LISTVIEWNOTI_ERASEBKGND			NOTIMASK_ERASEBKGND   //	0x80000000
#define		LISTVIEWNOTI_POSTDRAW			NOTIMASK_POSTDRAW     //	0x40000000
#define		LISTVIEWNOTI_PREKEY			NOTIMASK_PREKEY	      //	0x20000000
#define		LISTVIEWNOTI_POSTKEY			NOTIMASK_POSTKEY      //	0x10000000
#define		LISTVIEWNOTI_TITLEDRAW			NOTIMASK_TITLEDRAW    //        0x01000000 
#define		LISTVIEWNOTI_HASVSCROLL			NOTIMASK_HASVSCROLL   //	0x00000001
#define		LISTVIEWNOTI_ITEMSELECTED		0x00008000				//
#define		LISTVIEWNOTI_ITEMDRAW			0x00004000				//
#define		LISTVIEWNOTI_ERASEITEMBKGND		0x00002000				//
#define		LISTVIEWNOTI_NUMICONDRAW		0x00001000				//
#define		LISTVIEWNOTI_ITEMDELETE			0x00000800				//
#define		LISTVIEWNOTI_POINTING			0x00000400				//
#define		LISTVIEWNOTI_SELCTRLINDEX		0x00000200				//
#define		LISTVIEWNOTI_DRAGANDDROP		0x00000100				//

#define		LISTVIEWITEM_DISABLE			0x8000					//
#define		LISTVIEWITEM_SELECTED			0x4000					//
#define		LISTVIEWITEM_MULTISELECTED		0x2000					//
#define		LISTVIEWITEM_HASSEPERATOR               0x1000				        //
#define		LISTVIEWITEM_HIDDEN			0x0800				        //
#define		LISTVIEWITEM_CHECKED			0x0400					//
#define		LISTVIEWITEM_HASCTRL			0x0200					//
#define		LISTVIEWITEM_HASNOSELBAR		0x0100					//
#define		LISTVIEWITEM_PRESSED			0x0080					//

//	ListView
typedef enum
{
	LISTVIEWCOL_BACKGROUND				= FRMCOL_BACKGROUND,
	LISTVIEWCOL_FOREGROUND				= FRMCOL_FOREGROUND,
	LISTVIEWCOL_BORDER_LT				= FRMCOL_BORDER_LT,
	LISTVIEWCOL_BORDER_RB				= FRMCOL_BORDER_RB,
	LISTVIEWCOL_TITLE_BACKGROUND			= FRMCOL_TITLE_BACKGROUND,
	LISTVIEWCOL_TITLE_TEXT				= FRMCOL_TITLE_TEXT,
	LISTVIEWCOL_TITLE_UNDERLINE			= FRMCOL_TITLE_UNDERLINE,
	LISTVIEWCOL_NORMAL_TEXT,
	LISTVIEWCOL_DISABLE_TEXT,
	LISTVIEWCOL_SELECT_TEXT,
	LISTVIEWCOL_SELECT_BACKGROUND,
	LISTVIEWCOL_MULTISEL_TEXT,
	LISTVIEWCOL_MULTISEL_BACKGROUND,
	LISTVIEWCOL_SEPARATOR1,
	LISTVIEWCOL_SEPARATOR2,	
	LISTVIEWCOL_NUM
} E_LISTVCOL;


typedef enum
{
	LISTVIEWMODE_LIST						= 0,
	LISTVIEWMODE_GRID,
	LISTVIEWMODE_NUM
} E_LISTVMODE;

#define		LISTVIEW_SCRLALIGN_TOP		1	
#define		MAX_LISTVIEWITEMCTRL_NUM	4

typedef struct
{
	TRect*			pItemRect;
	T_INDEX			Index;			//	Real Index
	T_INDEX			DrawIndex;		//	Draw Index (Hidden Status´Â »­)
	TTextStyle*		pTS;
	E_FONT			Font;
	int			TextAlign;
} TDrawNotiInfo;

typedef struct
{
	TLnkObj			LnkObj;
	T_CSTR			pcszStr;
	H_CTRL			hItemCtrlTbl[MAX_LISTVIEWITEMCTRL_NUM];	
	T_SIZE			Height;
	WORD			Status;
	QUAD			SysData;				
	QUAD			wData;				
	QUAD			lData;	
} TListViewItem;

typedef struct
{
	TFrmCtrl		Frame;
	TLnkList		ItemList;
	T_NUM			MaxItemNum;
	T_NUM			ItemNum;						
	TListViewItem*		pSelItem;
	int			LineGap;
	int			GridLineGap;				
	int			InvOffset;
	T_SIZE			DefHeight;

	T_SIZE			TotalHeight;
	TPoint			Scroll;
	int			ListDeltaX1;				
	int			ListDeltaX2;
	int			VItemHeight;				

	int			TickerPos;
	E_LISTVMODE		ViewMode;

	T_NUM			ColumnNum;
	T_SIZE			GridItemH;	//	Grid Item Height
	T_SIZE			GridItemW;	//	Grid Item Width

	TListViewItem*		DownItem;	// pointing downµÈ indexÀúÀå
	QUAD			FlickScroll;
} TListView;

//-------------------------------------------------------------------------------------------------
//	Call Back Functions
typedef		int		(*T_pfnSortItem) (TListViewItem* pLItem, TListViewItem* pRItem); 


//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//	Create & Destroy Functions
extern H_CTRL			ListView_Create          (void* pOwner, T_POS X, T_POS Y, T_SIZE W, T_SIZE H);
extern BOOL			ListView_Destroy         (H_CTRL hLV);

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//	Overriding Functions

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//	ListView Own Functions
extern BOOL			ListView_SetLineGap          (H_CTRL hLV, int LineGap);
extern BOOL			ListView_SetInvOffset        (H_CTRL hLV, int InvOffset);
extern BOOL			ListView_SetListDeltaX1      (H_CTRL hLV, int DeltaX1);
extern BOOL			ListView_SetListDeltaX2      (H_CTRL hLV, int DeltaX2);
extern BOOL			ListView_SetDefItemHeight    (H_CTRL hLV, T_SIZE DefHeight);
extern BOOL			ListView_SetVItemHeight	     (H_CTRL hLV, T_SIZE VHeight);

extern int			ListView_GetLineGap          (H_CTRL hLV);
extern int			ListView_GetInvOffset        (H_CTRL hLV);
extern int		        ListView_GetListDeltaX1      (H_CTRL hLV);
extern int			ListView_GetListDeltaX2      (H_CTRL hLV);
extern T_NUM			ListView_GetDefItemHeight    (H_CTRL hLV);
extern T_NUM			ListView_GetVItemHeight	     (H_CTRL hLV);
extern T_NUM			ListView_GetItemNum          (H_CTRL hLV);
extern T_INDEX			ListView_GetSelIndex         (H_CTRL hLV);
extern TListViewItem*	        ListView_GetSelItem          (H_CTRL hLV);
extern T_INDEX			ListView_GetItemIndex        (H_CTRL hLV, TListViewItem* pListViewItem);

extern T_SIZE			ListView_GetTotalHeight      (H_CTRL hLV);
extern BOOL			ListView_ResetAllItems       (H_CTRL hLV);
extern BOOL			ListView_ResetTicker         (H_CTRL hLV);
extern BOOL			ListView_Sort                (H_CTRL hLV, T_pfnSortItem pfnCustomSortFunc);

extern BOOL			ListView_SetViewMode         (H_CTRL hLV, E_LISTVMODE ViewMode);
extern E_LISTVMODE		ListView_GetViewMode         (H_CTRL hLV);

extern BOOL			ListView_SetGridItemH        (H_CTRL hLV, T_SIZE GridItemH);
extern BOOL			ListView_SetGridItemW        (H_CTRL hLV, T_SIZE GridItemW);
extern BOOL			ListView_SetColumnNum        (H_CTRL hLV, T_NUM  ColumnNum);

//	ListView Item Related Functions
extern BOOL			ListView_SetStr              (H_CTRL hLV, T_INDEX Index, T_CSTR pcszStr);
extern BOOL			ListView_SetwData            (H_CTRL hLV, T_INDEX Index, QUAD wData);
extern BOOL		        ListView_SetlData            (H_CTRL hLV, T_INDEX Index, QUAD lData);
extern BOOL		        ListView_SetItemHeight       (H_CTRL hLV, T_INDEX Index, T_SIZE ItemHeight);
extern TListViewItem*	        ListView_GetItem             (H_CTRL hLV, T_INDEX Index);
extern T_CSTR			ListView_GetStr              (H_CTRL hLV, T_INDEX Index);
extern BOOL			ListView_GetwData            (H_CTRL hLV, T_INDEX Index, QUAD* pwData);
extern BOOL			ListView_GetlData            (H_CTRL hLV, T_INDEX Index, QUAD* plData);
extern BOOL			ListView_GetStatus           (H_CTRL hLV, T_INDEX Index, WORD* pStatus);

extern T_INDEX			ListView_AddItem             (H_CTRL hLV, T_CSTR pcszStr, QUAD wData, QUAD lData);
extern BOOL			ListView_InsertItem          (H_CTRL hLV, T_INDEX Index, T_CSTR pcszStr, QUAD wData, QUAD lData);
extern BOOL			ListView_DeleteItem          (H_CTRL hLV, T_INDEX Index);
extern BOOL			ListView_SelectItem          (H_CTRL hLV, T_INDEX Index);
extern BOOL			ListView_AddSeparator        (H_CTRL hLV, T_INDEX Index);
extern BOOL			ListView_SetStatus           (H_CTRL hLV, T_INDEX Index, WORD Status);
extern BOOL			ListView_EnableItem          (H_CTRL hLV, T_INDEX Index, BOOL bEnable);
extern BOOL			ListView_EnsureVisible       (H_CTRL hLV, T_INDEX Index);
extern BOOL			ListView_AttachItems         (H_CTRL hLV, TLnkList* pItemList);
extern BOOL			ListView_MoveItem	     (H_CTRL hLV, T_INDEX Index, T_INDEX MoveIndex);
extern BOOL			ListView_SetItemCtrl         (H_CTRL hLV, T_INDEX Index, T_ID ID, H_CTRL hCtrl);
extern H_CTRL			ListView_GetItemCtrl	     (H_CTRL hLV, T_INDEX Index, T_ID ID);

#endif	//	_BNSOFT_PEANUT_LISTVIEW_H_
