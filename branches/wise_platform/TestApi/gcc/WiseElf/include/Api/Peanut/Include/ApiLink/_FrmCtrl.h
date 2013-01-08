/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	PEANUT FRAME CONTROL APILINK

	Copyright(c) 1997-2002 BNSoft Corp.

	그룹 : PEANUT
	구분 : APILINK
	등급 : 공개																						{{BNS_INTERNALCODE()}}
	버전 : 1.00
	일자 : 2002.12.27
	성명 : 이동화
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT__PEANUT_FRMCTRL_H_
#define		_BNSOFT__PEANUT_FRMCTRL_H_

#include	"..\FrmCtrl.h"

//-------------------------------------------------------------------------------------------------
typedef H_CTRL			(*T_pfnFrmCtrl_Create)           (void* pOwner, T_POS X, T_POS Y, T_SIZE W, T_SIZE H);
typedef BOOL			(*T_pfnFrmCtrl_Destroy)          (H_CTRL hFC);
typedef BOOL			(*T_pfnFrmCtrl_ModifyStyle)      (H_CTRL hFC, QUAD RemoveStyle, QUAD AddStyle);
typedef BOOL			(*T_pfnFrmCtrl_SetRange)         (H_CTRL hFC, T_POS X1, T_POS Y1, T_POS X2, T_POS Y2);
typedef BOOL			(*T_pfnFrmCtrl_SetPos)           (H_CTRL hFC, T_POS X, T_POS Y);
typedef BOOL			(*T_pfnFrmCtrl_SetSize)          (H_CTRL hFC, T_SIZE W, T_SIZE H);
typedef BOOL			(*T_pfnFrmCtrl_SetClientRect)    (H_CTRL hFC, T_POS X1, T_POS Y1, T_POS X2, T_POS Y2);
typedef BOOL			(*T_pfnFrmCtrl_SetClientPos)     (H_CTRL hFC, T_POS X, T_POS Y);
typedef BOOL			(*T_pfnFrmCtrl_SetClientSize)    (H_CTRL hFC, T_SIZE W, T_SIZE H);
typedef BOOL			(*T_pfnFrmCtrl_SetDelta)         (H_CTRL hFC, int DeltaX, int DeltaY);
typedef BOOL			(*T_pfnFrmCtrl_SetDelta2)        (H_CTRL hFC, int DeltaX2, int DeltaY2);
typedef BOOL			(*T_pfnFrmCtrl_SetTitle)         (H_CTRL hFC, T_CSTR rcszTitle);
typedef BOOL			(*T_pfnFrmCtrl_SetTitleFont)     (H_CTRL hFC, E_FONT enFont);
typedef BOOL			(*T_pfnFrmCtrl_SetTitleHeight)   (H_CTRL hFC, T_SIZE Height);
typedef BOOL			(*T_pfnFrmCtrl_SetTitleLeftMargin)(H_CTRL hFC, T_SIZE LeftMargin);
typedef BOOL			(*T_pfnFrmCtrl_SetTitleRightMargin)(H_CTRL hFC, T_SIZE RightMargin);
typedef TRect*			(*T_pfnFrmCtrl_GetClientRect)    (H_CTRL hFC);
typedef T_POS			(*T_pfnFrmCtrl_GetClientPosX)    (H_CTRL hFC);
typedef T_POS			(*T_pfnFrmCtrl_GetClientPosY)    (H_CTRL hFC);
typedef T_SIZE			(*T_pfnFrmCtrl_GetClientWidth)   (H_CTRL hFC);
typedef T_SIZE			(*T_pfnFrmCtrl_GetClientHeight)  (H_CTRL hFC);
typedef TRect*			(*T_pfnFrmCtrl_GetWorkArea)      (H_CTRL hFC);
typedef T_POS			(*T_pfnFrmCtrl_GetWorkPosX)      (H_CTRL hFC);
typedef T_POS			(*T_pfnFrmCtrl_GetWorkPosY)      (H_CTRL hFC);
typedef T_SIZE			(*T_pfnFrmCtrl_GetWorkWidth)     (H_CTRL hFC);
typedef T_SIZE			(*T_pfnFrmCtrl_GetWorkHeight)    (H_CTRL hFC);
typedef int				(*T_pfnFrmCtrl_GetDeltaX1)       (H_CTRL hFC);
typedef int				(*T_pfnFrmCtrl_GetDeltaY1)       (H_CTRL hFC);
typedef int				(*T_pfnFrmCtrl_GetDeltaX2)       (H_CTRL hFC);
typedef int				(*T_pfnFrmCtrl_GetDeltaY2)       (H_CTRL hFC);
typedef T_CSTR			(*T_pfnFrmCtrl_GetTitle)         (H_CTRL hFC);
typedef E_FONT			(*T_pfnFrmCtrl_GetTitleFont)     (H_CTRL hFC);
typedef T_SIZE			(*T_pfnFrmCtrl_GetTitleHeight)   (H_CTRL hFC);
typedef T_SIZE			(*T_pfnFrmCtrl_GetTitleLeftMargin)(H_CTRL hFC);
typedef T_SIZE			(*T_pfnFrmCtrl_GetTitleRightMargin)(H_CTRL hFC);
typedef BOOL			(*T_pfnFrmCtrl_AdjustRange)      (H_CTRL hFC);
typedef BOOL			(*T_pfnFrmCtrl_AdjustClientRect) (H_CTRL hFC);
typedef BOOL			(*T_pfnFrmCtrl_AdjustScrollBar)  (H_CTRL hFC);
typedef BOOL			(*T_pfnFrmCtrl_PtInClientRect)   (H_CTRL hFC, int X, int Y);
#if defined (WISE_PEANUT_DUALSIM_SUPPORT)
typedef BOOL			(*T_pfnFrmCtrl_SetTitleIcon)	(H_CTRL hFC, E_SIMICON Sim1Icon, E_SIMICON Sim2Icon);
typedef BOOL			(*T_pfnFrmCtrl_SetTitleColor)	(H_CTRL hFC, E_SIMCOLOR TitleColor);
#endif


//-------------------------------------------------------------------------------------------------
typedef struct
{
	T_pfnFrmCtrl_Create					pfnCreate;
	T_pfnFrmCtrl_Destroy				pfnDestroy;
	T_pfnFrmCtrl_ModifyStyle			pfnModifyStyle;
	T_pfnFrmCtrl_SetRange				pfnSetRange;
	T_pfnFrmCtrl_SetPos					pfnSetPos;
	T_pfnFrmCtrl_SetSize				pfnSetSize;
	T_pfnFrmCtrl_SetClientRect			pfnSetClientRect;
	T_pfnFrmCtrl_SetClientPos			pfnSetClientPos;
	T_pfnFrmCtrl_SetClientSize			pfnSetClientSize;
	T_pfnFrmCtrl_SetDelta				pfnSetDelta;
	T_pfnFrmCtrl_SetDelta2				pfnSetDelta2;
	T_pfnFrmCtrl_SetTitle				pfnSetTitle;
	T_pfnFrmCtrl_SetTitleFont			pfnSetTitleFont;
	T_pfnFrmCtrl_SetTitleHeight			pfnSetTitleHeight;
	T_pfnFrmCtrl_SetTitleLeftMargin		pfnSetTitleLeftMargin;
	T_pfnFrmCtrl_SetTitleRightMargin	pfnSetTitleRightMargin;
	T_pfnFrmCtrl_GetClientRect			pfnGetClientRect;
	T_pfnFrmCtrl_GetClientPosX			pfnGetClientPosX;
	T_pfnFrmCtrl_GetClientPosY			pfnGetClientPosY;
	T_pfnFrmCtrl_GetClientWidth			pfnGetClientWidth;
	T_pfnFrmCtrl_GetClientHeight		pfnGetClientHeight;
	T_pfnFrmCtrl_GetWorkArea			pfnGetWorkArea;
	T_pfnFrmCtrl_GetWorkPosX			pfnGetWorkPosX;
	T_pfnFrmCtrl_GetWorkPosY			pfnGetWorkPosY;
	T_pfnFrmCtrl_GetWorkWidth			pfnGetWorkWidth;
	T_pfnFrmCtrl_GetWorkHeight			pfnGetWorkHeight;
	T_pfnFrmCtrl_GetDeltaX1				pfnGetDeltaX1;
	T_pfnFrmCtrl_GetDeltaY1				pfnGetDeltaY1;
	T_pfnFrmCtrl_GetDeltaX2				pfnGetDeltaX2;
	T_pfnFrmCtrl_GetDeltaY2				pfnGetDeltaY2;
	T_pfnFrmCtrl_GetTitle				pfnGetTitle;
	T_pfnFrmCtrl_GetTitleFont			pfnGetTitleFont;
	T_pfnFrmCtrl_GetTitleHeight			pfnGetTitleHeight;
	T_pfnFrmCtrl_GetTitleLeftMargin		pfnGetTitleLeftMargin;
	T_pfnFrmCtrl_GetTitleRightMargin	pfnGetTitleRightMargin;
	T_pfnFrmCtrl_AdjustRange			pfnAdjustRange;
	T_pfnFrmCtrl_AdjustClientRect		pfnAdjustClientRect;
	T_pfnFrmCtrl_AdjustScrollBar		pfnAdjustScrollBar;
	T_pfnFrmCtrl_PtInClientRect			pfnPtInClientRect;
	
#if defined (WISE_PEANUT_DUALSIM_SUPPORT)
	T_pfnFrmCtrl_SetTitleIcon			pfnSetTitleIcon;
	T_pfnFrmCtrl_SetTitleColor			pfnSetTitleColor;
#endif
} TApiGrp_FrmCtrl;

//-------------------------------------------------------------------------------------------------
#ifndef		BNS_MAIN_VERSION

	#define		FrmCtrl_Create(p1,p2,p3,p4,p5)				__ApiLink5(FrmCtrl,Create,p1,p2,p3,p4,p5)
	#define		FrmCtrl_Destroy(p1)							__ApiLink1(FrmCtrl,Destroy,p1)
	#define		FrmCtrl_ModifyStyle(p1,p2,p3)				__ApiLink3(FrmCtrl,ModifyStyle,p1,p2,p3)
	#define		FrmCtrl_SetRange(p1,p2,p3,p4,p5)			__ApiLink5(FrmCtrl,SetRange,p1,p2,p3,p4,p5)
	#define		FrmCtrl_SetPos(p1,p2,p3)					__ApiLink3(FrmCtrl,SetPos,p1,p2,p3)
	#define		FrmCtrl_SetSize(p1,p2,p3)					__ApiLink3(FrmCtrl,SetSize,p1,p2,p3)
	#define		FrmCtrl_SetClientRect(p1,p2,p3,p4,p5)		__ApiLink5(FrmCtrl,SetClientRect,p1,p2,p3,p4,p5)
	#define		FrmCtrl_SetClientPos(p1,p2,p3)				__ApiLink3(FrmCtrl,SetClientPos,p1,p2,p3)
	#define		FrmCtrl_SetClientSize(p1,p2,p3)				__ApiLink3(FrmCtrl,SetClientSize,p1,p2,p3)
	#define		FrmCtrl_SetDelta(p1,p2,p3)					__ApiLink3(FrmCtrl,SetDelta,p1,p2,p3)
	#define		FrmCtrl_SetDelta2(p1,p2,p3)					__ApiLink3(FrmCtrl,SetDelta2,p1,p2,p3)
	#define		FrmCtrl_SetTitle(p1,p2)						__ApiLink2(FrmCtrl,SetTitle,p1,p2)
	#define		FrmCtrl_SetTitleFont(p1,p2)					__ApiLink2(FrmCtrl,SetTitleFont,p1,p2)
	#define		FrmCtrl_SetTitleHeight(p1,p2)				__ApiLink2(FrmCtrl,SetTitleHeight,p1,p2)
	#define		FrmCtrl_SetTitleLeftMargin(p1,p2)			__ApiLink2(FrmCtrl,SetTitleLeftMargin,p1,p2)
	#define		FrmCtrl_SetTitleRightMargin(p1,p2)			__ApiLink2(FrmCtrl,SetTitleRightMargin,p1,p2)
	#define		FrmCtrl_GetClientRect(p1)					__ApiLink1(FrmCtrl,GetClientRect,p1)
	#define		FrmCtrl_GetClientPosX(p1)					__ApiLink1(FrmCtrl,GetClientPosX,p1)
	#define		FrmCtrl_GetClientPosY(p1)					__ApiLink1(FrmCtrl,GetClientPosY,p1)
	#define		FrmCtrl_GetClientWidth(p1)					__ApiLink1(FrmCtrl,GetClientWidth,p1)
	#define		FrmCtrl_GetClientHeight(p1)					__ApiLink1(FrmCtrl,GetClientHeight,p1)
	#define		FrmCtrl_GetWorkArea(p1)						__ApiLink1(FrmCtrl,GetWorkArea,p1)
	#define		FrmCtrl_GetWorkPosX(p1)						__ApiLink1(FrmCtrl,GetWorkPosX,p1)
	#define		FrmCtrl_GetWorkPosY(p1)						__ApiLink1(FrmCtrl,GetWorkPosY,p1)
	#define		FrmCtrl_GetWorkWidth(p1)					__ApiLink1(FrmCtrl,GetWorkWidth,p1)
	#define		FrmCtrl_GetWorkHeight(p1)					__ApiLink1(FrmCtrl,GetWorkHeight,p1)
	#define		FrmCtrl_GetDeltaX1(p1)						__ApiLink1(FrmCtrl,GetDeltaX1,p1)
	#define		FrmCtrl_GetDeltaY1(p1)						__ApiLink1(FrmCtrl,GetDeltaY1,p1)
	#define		FrmCtrl_GetDeltaX2(p1)						__ApiLink1(FrmCtrl,GetDeltaX2,p1)
	#define		FrmCtrl_GetDeltaY2(p1)						__ApiLink1(FrmCtrl,GetDeltaY2,p1)
	#define		FrmCtrl_GetTitle(p1)						__ApiLink1(FrmCtrl,GetTitle,p1)
	#define		FrmCtrl_GetTitleFont(p1)					__ApiLink1(FrmCtrl,GetTitleFont,p1)
	#define		FrmCtrl_GetTitleHeight(p1)					__ApiLink1(FrmCtrl,GetTitleHeight,p1)
	#define		FrmCtrl_GetTitleLeftMargin(p1)				__ApiLink1(FrmCtrl,GetTitleLeftMargin,p1)
	#define		FrmCtrl_GetTitleRightMargin(p1)				__ApiLink1(FrmCtrl,GetTitleRightMargin,p1)
	#define		FrmCtrl_AdjustRange(p1)						__ApiLink1(FrmCtrl,AdjustRange,p1)
	#define		FrmCtrl_AdjustClientRect(p1)				__ApiLink1(FrmCtrl,AdjustClientRect,p1)
	#define		FrmCtrl_AdjustScrollBar(p1)					__ApiLink1(FrmCtrl,AdjustScrollBar,p1)
	#define		FrmCtrl_PtInClientRect(p1,p2,p3)			__ApiLink3(FrmCtrl,PtInClientRect,p1,p2,p3)
#if defined (WISE_PEANUT_DUALSIM_SUPPORT)
	#define 		FrmCtrl_SetTitleIcon(p1,p2,p3)				__ApiLink3(FrmCtrl,SetTitleIcon,p1,p2,p3)
	#define 		FrmCtrl_SetTitleColor(p1,p2)				__ApiLink2(FrmCtrl,SetTitleColor,p1, p2)
#endif

#endif	//	BNS_MAIN_VERSION
//-------------------------------------------------------------------------------------------------

#endif	//	_BNSOFT__PEANUT_FRMCTRL_H_
