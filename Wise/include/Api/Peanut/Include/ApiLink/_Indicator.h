/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	PEANUT INDICATOR APILINK

	Copyright(c) 1997-2003 BNSoft Corp.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT__PEANUT_INDICATOR_H_
#define		_BNSOFT__PEANUT_INDICATOR_H_

#include	"..\Indicator.h"

typedef void			(*T_pfnIndicator_Reset)           (void);
typedef T_POS			(*T_pfnIndicator_GetTopY)         (void);
typedef T_POS			(*T_pfnIndicator_GetBottomY)      (void);
typedef T_POS			(*T_pfnIndicator_GetBelowY)       (void);
typedef void			(*T_pfnIndicator_SetShowStyle)    (int Style);
typedef int			(*T_pfnIndicator_GetShowStyle)    (void);
typedef void			(*T_pfnIndicator_SetValue)        (int nItem, QUAD Value);
typedef QUAD			(*T_pfnIndicator_GetValue)        (int nItem);
typedef void			(*T_pfnIndicator_SetBlink)        (int nItem, BOOL bBlink);
typedef BOOL			(*T_pfnIndicator_GetBlink)        (int nItem);
typedef void			(*T_pfnIndicator_SetTime)         (int nItem, QUAD Value);
typedef QUAD			(*T_pfnIndicator_GetTime)         (int nItem);
typedef void			(*T_pfnIndicator_SetValueEx)      (int nItem, QUAD Value, QUAD Time);
typedef void			(*T_pfnIndicator_DrawItem)        (int nItem, BOOL bRefresh);
typedef void			(*T_pfnIndicator_Draw)            (BOOL bRefresh);
typedef void			(*T_pfnIndicator_Timer)           (void);
typedef BOOL			(*T_pfnIndicator_SetTransparent)  (BOOL bTransparent);
typedef BOOL			(*T_pfnIndicator_SetUserDefine)	  (BOOL bUserSet, TRect* pValidIndiRect, TIndiPosObj *IndiItemObj);
typedef TRect*			(*T_pfnIndicator_GetRange)	  (void);
typedef TIndiPosObj*	        (*T_pfnIndicator_GetIndiPosItem)  (int nPosIndex);

typedef struct
{
	T_pfnIndicator_Reset			pfnReset;
	T_pfnIndicator_GetTopY			pfnGetTopY;
	T_pfnIndicator_GetBottomY		pfnGetBottomY;
	T_pfnIndicator_GetBelowY		pfnGetBelowY;
	T_pfnIndicator_SetShowStyle		pfnSetShowStyle;
	T_pfnIndicator_GetShowStyle		pfnGetShowStyle;
	T_pfnIndicator_SetValue			pfnSetValue;
	T_pfnIndicator_GetValue			pfnGetValue;
	T_pfnIndicator_SetBlink			pfnSetBlink;
	T_pfnIndicator_GetBlink			pfnGetBlink;
	T_pfnIndicator_SetTime			pfnSetTime;
	T_pfnIndicator_GetTime			pfnGetTime;
	T_pfnIndicator_SetValueEx		pfnSetValueEx;
	T_pfnIndicator_DrawItem			pfnDrawItem;
	T_pfnIndicator_Draw			pfnDraw;
	T_pfnIndicator_Timer			pfnTimer;
	T_pfnIndicator_SetTransparent		pfnSetTransparent;
	T_pfnIndicator_SetUserDefine		pfnSetUserDefine;
	T_pfnIndicator_GetRange			pfnGetRange;
	T_pfnIndicator_GetIndiPosItem		pfnGetIndiPosItem;
} TApiGrp_Indicator;


#define		Indicator_Reset()				__ApiLink0(Indicator,Reset)
#define		Indicator_GetTopY()				__ApiLink0(Indicator,GetTopY)
#define		Indicator_GetBottomY()				__ApiLink0(Indicator,GetBottomY)
#define		Indicator_GetBelowY()				__ApiLink0(Indicator,GetBelowY)
#define		Indicator_SetShowStyle(p1)			__ApiLink1(Indicator,SetShowStyle,p1)
#define		Indicator_GetShowStyle()			__ApiLink0(Indicator,GetShowStyle)
#define		Indicator_SetValue(p1,p2)			__ApiLink2(Indicator,SetValue,p1,p2)
#define		Indicator_GetValue(p1)				__ApiLink1(Indicator,GetValue,p1)
#define		Indicator_SetBlink(p1,p2)			__ApiLink2(Indicator,SetBlink,p1,p2)	
#define		Indicator_GetBlink(p1)				__ApiLink1(Indicator,GetBlink,p1)
#define		Indicator_SetTime(p1,p2)			__ApiLink2(Indicator,SetTime,p1,p2)
#define		Indicator_GetTime(p1)				__ApiLink1(Indicator,GetTime,p1)
#define		Indicator_SetValueEx(p1,p2,p3)			__ApiLink3(Indicator,SetValueEx,p1,p2,p3)
#define		Indicator_DrawItem(p1,p2)			__ApiLink2(Indicator,DrawItem,p1,p2)
#define		Indicator_Draw(p1)				__ApiLink1(Indicator,Draw,p1)
#define		Indicator_Timer()				__ApiLink0(Indicator,Timer)
#define		Indicator_SetTransparent(p1)			__ApiLink1(Indicator,SetTransparent,p1)
#define		Indicator_SetUserDefine(p1,p2,p3)		__ApiLink3(Indicator,SetUserDefine,p1,p2,p3)
#define		Indicator_GetRange()				__ApiLink0(Indicator,GetRange)	
#define		Indicator_GetIndiPosItem(p1)			__ApiLink1(Indicator,GetIndiPosItem,p1)

#endif	//	_BNSOFT__PEANUT_INDICATOR_H_
