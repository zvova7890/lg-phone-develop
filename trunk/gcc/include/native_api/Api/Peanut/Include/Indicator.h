/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	PEANUT INDICATOR MANAGER

	Copyright(c) 1997-2003 BNSoft Corp.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT_PEANUT_INDICATOR_H_
#define		_BNSOFT_PEANUT_INDICATOR_H_

#include	"PeanutInclude.h"
#include	"OemIndicator.h"

#define		INDICATORSTY_HIDE	0
#define		INDICATORSTY_SHOW	1
#define		INDICATORSTY_JAVASHOW	2
#define		INDICATORSTY_HSASHOW	3


extern void			Indicator_Reset          (void);

extern T_POS			Indicator_GetTopY        (void);
extern T_POS			Indicator_GetBottomY     (void);
extern T_POS			Indicator_GetBelowY      (void);

extern void			Indicator_SetShowStyle   (int Style);
extern int			Indicator_GetShowStyle   (void);

extern void			Indicator_SetValue       (int nItem, QUAD Value);
extern QUAD			Indicator_GetValue       (int nItem);
extern void			Indicator_SetBlink       (int nItem, BOOL bBlink);
extern BOOL			Indicator_GetBlink       (int nItem);
extern void			Indicator_SetTime        (int nItem, QUAD Value);
extern QUAD			Indicator_GetTime        (int nItem);
extern void			Indicator_SetValueEx     (int nItem, QUAD Value, QUAD Time);

extern void			Indicator_DrawItem       (int nItem, BOOL bRefresh);
extern void			Indicator_Draw           (BOOL bRefresh);
extern void			Indicator_Timer          (void);
extern BOOL			Indicator_SetTransparent (BOOL bTransparent);
extern BOOL			Indicator_SetUserDefine	 (BOOL bUserSet, TRect* pValidIndiRect, TIndiPosObj *IndiItemObj);
extern TRect*			Indicator_GetRange	 (void);
extern TIndiPosObj*		Indicator_GetIndiPosItem (int nPosIndex);


#endif	//	_BNSOFT_INDICATOR_H_
