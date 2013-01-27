/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	PEANUT SELECT CONTROL

	Copyright(c) 1997-2002 BNSoft Corp.

	�׷� : PEANUT
	���� : CONTROL
	��� : ����/�����																				{{BNS_INTERNALCODE()}}
	���� : 1.00
	���� : 2002.12.12
	���� : �̵�ȭ
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT_PEANUT_SELCTRL_H_
#define		_BNSOFT_PEANUT_SELCTRL_H_

#include	"BaseCtrl.h"
#include	"FrmCtrl.h"
#include	"MacroFunc/SelCtrlM.h"

//-------------------------------------------------------------------------------------------------
//	SelCtrl Style�� ���� (TBaseCtrl::Style)
#define		SELSTY_ARROW				0x00000080
#define		SELSTY_DROPDOWN				0x00000040			//2007-03-21, by LYS : Drop Down List Popup(CU920,U990)

#define		SELSTY_TICKER				0x00000020			//	04.04.21 ������ �߰� : ���ڿ��� ���̰� ��� �ڵ����� ��ũ����
#define		SELSTY_ELLIPSIS				0x00000010			//	04.04.21 ������ �߰� : ���ڿ��� �� �� ... �� �����
#define		SELSTY_DEF					(SELSTY_DROPDOWN)	// CU920,U990������ selctrl�� ������� �����Ƿ� SELSTY_DROPDOWN�� default�� ��//2007-03-22, by LYS

//20101021 david.choi@lge.com - Variable Font Color
#if defined (LGE_FEATURE_FONTCOLOR)
//#define	SELSTY_VFONTCOLOR			0x00000200
#define		SELSTY_NOVFONTCOLOR			0x00000200
#endif


//-------------------------------------------------------------------------------------------------
//	NOTIMASK�� ���� (TBaseCtrl::NotiMask)
//#define		SELMASK_ERASEBKGND			NOTIMASK_ERASEBKGND	//	0x80000000	��Ʈ���� ����� �׸��� ��쿡 �߻�
//#define		SELMASK_POSTDRAW			NOTIMASK_POSTDRAW	//	0x40000000  ��Ʈ���� �׸� �� �׷��ȹ��۷� ����ϱ� ���� �߻�
#define		SELNOTI_SELCHANGED			0x08000000			//	�����׸��� �ٲ����
#define		SELNOTI_POINTING			0x04000000			//	SelCtrl������ Pointing�Ǿ���
//-------------------------------------------------------------------------------------------------
//	SelCtrl ���� ����
typedef enum
{
	SELCOL_BACKGROUND					= 0,
	SELCOL_FOREGROUND,
	SELCOL_BORDER_LT,										//	Left/Top Border Color
	SELCOL_BORDER_RB,										//	Right/Bottom Border Color
	SELCOL_NUM
} E_SELCOL;

//-------------------------------------------------------------------------------------------------
//	SelItem ����ü ����
typedef struct
{
	T_CSTR				pcszStr;
	QUAD				Data;
} TSelItem;

//-------------------------------------------------------------------------------------------------
//	SelCtrl ����ü ����
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
	int					TickerPos;	//	04.04.21 ������ �߰�
//DOP�߰�-----------------------------------------------------------------------
	QUAD				DOPData;	// RepeatTimer setting���� ���� ���� ���
//DOP�Ϸ�----------------------------------------------------------------------
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
