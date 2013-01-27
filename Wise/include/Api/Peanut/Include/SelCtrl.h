/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	PEANUT SELECT CONTROL

	Copyright(c) 1997-2002 BNSoft Corp.

	그룹 : PEANUT
	구분 : CONTROL
	등급 : 공개/비공개																				{{BNS_INTERNALCODE()}}
	버전 : 1.00
	일자 : 2002.12.12
	성명 : 이동화
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT_PEANUT_SELCTRL_H_
#define		_BNSOFT_PEANUT_SELCTRL_H_

#include	"BaseCtrl.h"
#include	"FrmCtrl.h"
#include	"MacroFunc/SelCtrlM.h"

//-------------------------------------------------------------------------------------------------
//	SelCtrl Style의 종류 (TBaseCtrl::Style)
#define		SELSTY_ARROW				0x00000080
#define		SELSTY_DROPDOWN				0x00000040			//2007-03-21, by LYS : Drop Down List Popup(CU920,U990)

#define		SELSTY_TICKER				0x00000020			//	04.04.21 전영혜 추가 : 문자열의 길이가 길면 자동으로 스크롤함
#define		SELSTY_ELLIPSIS				0x00000010			//	04.04.21 전영혜 추가 : 문자열이 길 때 ... 을 출력함
#define		SELSTY_DEF					(SELSTY_DROPDOWN)	// CU920,U990에서는 selctrl을 사용하지 않으므로 SELSTY_DROPDOWN을 default로 함//2007-03-22, by LYS

//20101021 david.choi@lge.com - Variable Font Color
#if defined (LGE_FEATURE_FONTCOLOR)
//#define	SELSTY_VFONTCOLOR			0x00000200
#define		SELSTY_NOVFONTCOLOR			0x00000200
#endif


//-------------------------------------------------------------------------------------------------
//	NOTIMASK의 종류 (TBaseCtrl::NotiMask)
//#define		SELMASK_ERASEBKGND			NOTIMASK_ERASEBKGND	//	0x80000000	컨트롤의 배경을 그리는 경우에 발생
//#define		SELMASK_POSTDRAW			NOTIMASK_POSTDRAW	//	0x40000000  컨트롤을 그린 후 그래픽버퍼로 출력하기 전에 발생
#define		SELNOTI_SELCHANGED			0x08000000			//	선택항목이 바뀌었음
#define		SELNOTI_POINTING			0x04000000			//	SelCtrl영역이 Pointing되었음
//-------------------------------------------------------------------------------------------------
//	SelCtrl 색상 정의
typedef enum
{
	SELCOL_BACKGROUND					= 0,
	SELCOL_FOREGROUND,
	SELCOL_BORDER_LT,										//	Left/Top Border Color
	SELCOL_BORDER_RB,										//	Right/Bottom Border Color
	SELCOL_NUM
} E_SELCOL;

//-------------------------------------------------------------------------------------------------
//	SelItem 구조체 정의
typedef struct
{
	T_CSTR				pcszStr;
	QUAD				Data;
} TSelItem;

//-------------------------------------------------------------------------------------------------
//	SelCtrl 구조체 정의
typedef struct
{
	TBaseCtrl			Base;
	TSelItem*			pItemTbl;
	T_NUM				MaxItemNum;
	T_NUM				ItemNum;
	int					SelIndex;
//	T_CSTR				pszTag;
	KEY					PrevKey;
	KEY					NextKey;
//	int					ArrowWidth;
	int					TickerPos;	//	04.04.21 전영혜 추가
//DOP추가-----------------------------------------------------------------------
	QUAD				DOPData;	// RepeatTimer setting여부 구분 위해 사용
//DOP완료----------------------------------------------------------------------
} TSelCtrl;

//-------------------------------------------------------------------------------------------------	{{BNS_INTERNALCODE(+)}}
//	SelCtrl Internal Member Functions
#ifdef		BNS_MAIN_VERSION

	extern BOOL				SelCtrl_CreateBody     (TSelCtrl* pSC, void* pOwner, E_CTRLTYPE enType, QUAD Style, T_POS X, T_POS Y, T_SIZE W, T_SIZE H);
	extern BOOL				SelCtrl_DestroyBody    (TSelCtrl* pSC);

#endif	//	BNS_MAIN_VERSION																	//	{{BNS_INTERNALCODE(-)}}
//-------------------------------------------------------------------------------------------------
//	SelCtrl Member Functions
#ifdef		BNS_MAIN_VERSION

	//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	//	Create & Destroy Functions
	extern H_CTRL			SelCtrl_Create         (void* pOwner, T_POS X, T_POS Y, T_SIZE W, T_SIZE H);
	extern BOOL				SelCtrl_Destroy        (H_CTRL hSC);

	//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	//	Overriding Functions

	//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	//	SelCtrl Own Functions
	extern BOOL				SelCtrl_SetStr         (H_CTRL hSC, int Index, T_CSTR pcszStr);
	extern BOOL				SelCtrl_SetData        (H_CTRL hSC, int Index, QUAD Data);
	extern BOOL				SelCtrl_SetMoveKey     (H_CTRL hSC, KEY PrevKey, KEY NextKey);

	extern TSelItem*		SelCtrl_GetItem        (H_CTRL hSC, int Index);
	extern T_CSTR			SelCtrl_GetStr         (H_CTRL hSC, int Index);
	extern QUAD				SelCtrl_GetData        (H_CTRL hSC, int Index);
	extern int				SelCtrl_GetSelIndex    (H_CTRL hSC);
	extern TSelItem*		SelCtrl_GetSelItem     (H_CTRL hSC);
	extern T_CSTR			SelCtrl_GetSelStr      (H_CTRL hSC);
	extern QUAD				SelCtrl_GetSelData     (H_CTRL hSC);

	extern BOOL				SelCtrl_ResetAllItems  (H_CTRL hSC);
	extern BOOL				SelCtrl_ResetState     (H_CTRL hSC);
	extern BOOL				SelCtrl_AddItem        (H_CTRL hSC, T_CSTR pcszStr, QUAD Data);
	extern BOOL				SelCtrl_SelectItem     (H_CTRL hSC, int Index);
	extern int				SelCtrl_SelectNextItem (H_CTRL hSC);
	extern int				SelCtrl_SelectPrevItem (H_CTRL hSC);
	extern BOOL				SelCtrl_AssignStrSet   (H_CTRL hSC, T_CSTR pStrSet, T_NUM StrNum);
	extern BOOL				SelCtrl_AssignDataSet  (H_CTRL hSC, QUAD* pDataSet, T_NUM DataNum);
	extern BOOL				SelCtrl_ResetTicker    (H_CTRL hSC);

#endif	//	BNS_MAIN_VERSION
//-------------------------------------------------------------------------------------------------

#endif	//	_BNSOFT_PEANUT_SELCTRL_H_
