/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	PEANUT RADIO CONTROL

	Copyright(c) 1997-2003 BNSoft Corp.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT_PEANUT_RDOCTRL_H_
#define		_BNSOFT_PEANUT_RDOCTRL_H_

#include	"ChkCtrl.h"
#include	"MacroFunc/RdoCtrlM.h"

#define		RDOSTY_RIGHTICON			CHKSTY_RIGHTICON	//	0x80000000
#define		RDOSTY_ACTIVEBORDER			CHKSTY_ACTIVEBORDER	//	0x40000000
#define		RDOSTY_MULTILINE			CHKSTY_MULTILINE	//	0x10000000
#define		RDOSTY_BOLD				CHKSTY_BOLD		//	0x08000000
#define		RDOSTY_HEAD				0x00800000		//
#define		RDOSTY_ALWAYSSELECT			0x00400000		//

#define		RDOSTY_DEF				(CHKSTY_DEF | RDOSTY_ALWAYSSELECT)

#define		RDONOTI_ERASEBKGND			NOTIMASK_ERASEBKGND	//	0x80000000
#define		RDONOTI_POSTDRAW			NOTIMASK_POSTDRAW	//	0x40000000
#define		RDONOTI_PREKEY				NOTIMASK_PREKEY		//	0x20000000
#define		RDONOTI_POSTKEY				NOTIMASK_POSTKEY	//	0x10000000

typedef enum
{
	RDOSTATUS_OFF					= CHKSTATUS_OFF,
	RDOSTATUS_ON					= CHKSTATUS_ON,
	RDOSTATUS_MAXNUM
} E_RDOSTATUS;

typedef enum
{
	RDOCOL_BACKGROUND				= CHKCOL_BACKGROUND,
	RDOCOL_TEXT					= CHKCOL_TEXT,
	RDOCOL_NUM
} E_RDOCOL;

typedef struct _TRdoCtrl
{
	TChkCtrl		Check;
	struct _TRdoCtrl*	pHead;
	struct _TRdoCtrl*	pNext;
} TRdoCtrl;


//	Create & Destroy Functions
extern H_CTRL			RdoCtrl_Create      (void* pOwner, T_POS X, T_POS Y, T_SIZE W, T_SIZE H, T_CSTR pcszText, H_CTRL hGrpRC);
extern BOOL			RdoCtrl_Destroy     (H_CTRL hRC);

//	Overriding Functions
extern BOOL			RdoCtrl_ModifyStyle (H_CTRL hRC, QUAD RemoveStyle, QUAD AddStyle);
extern BOOL			RdoCtrl_SetStatus   (H_CTRL hRC, E_RDOSTATUS enStatus);
extern BOOL			RdoCtrl_SetCheck    (H_CTRL hRC, BOOL bCheck);

//	RdoCtrl Own Functions
extern H_CTRL			RdoCtrl_GetChecked  (H_CTRL hRC);
extern BOOL			RdoCtrl_UncheckAll  (H_CTRL hRC);


#endif	//	_BNSOFT_PEANUT_RDOCTRL_H_
