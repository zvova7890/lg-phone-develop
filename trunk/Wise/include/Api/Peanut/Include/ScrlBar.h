/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	PEANUT SCROLL BAR

	Copyright(c) 1997-2003 BNSoft Corp.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT_PEANUT_SCRLBAR_H_
#define		_BNSOFT_PEANUT_SCRLBAR_H_

#include	"BaseCtrl.h"

#define		SCRLBAR_HORIZONTAL			0
#define		SCRLBAR_VERTICAL			1

#define		SCRLSTY_HORIZONTAL			0x80000000
#define		SCRLSTY_VERTICAL			0x40000000

typedef enum
{
	SCRLCOL_BACKGROUND			= 0,
	SCRLCOL_FOREGROUND,
	SCRLCOL_BORDER_LT,			//	Left/Top Border Color
	SCRLCOL_BORDER_RB,			//	Right/Bottom Border Color
	SCRLCOL_NUM
} E_SCRLCOL;

//-------------------------------------------------------------------------------------------------
//	ScrlBar 구조체 정의
typedef struct
{
	TBaseCtrl			Base;					
	T_SIZE				Thickness;				
	int				ValueRange;					
	int				HighValue;			
	int				LowValue;			
	int				MovingHighValue;	
	QUAD				SBState;
	BOOL				bFullScroll;
} TScrlBar;


extern H_CTRL		ScrlBar_Create      (void* pOwner, QUAD Style);
extern BOOL		ScrlBar_Destroy     (H_CTRL hSB);

extern BOOL		ScrlBar_SetValue    (H_CTRL hSB, int nRange, int nPos, int nLength);
extern BOOL		ScrlBar_AdjustRange (H_CTRL hSB);


#endif	//	_BNSOFT_PEANUT_SCRLBAR_H_
