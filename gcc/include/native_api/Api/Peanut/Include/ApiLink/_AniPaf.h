/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	PEANUT ANIPAF APILINK

	Copyright(c) 1997-2003 BNSoft Corp.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_BNSOFT__PEANUT_ANIPAF_H_
#define		_BNSOFT__PEANUT_ANIPAF_H_

#include	"../AniPaf.h"

typedef H_PAF			(*T_pfnAniPaf_Create)            (T_CSTR pcszFileName, QUAD Style, T_POS X, T_POS Y, int Duration);
typedef BOOL			(*T_pfnAniPaf_Destroy)           (H_PAF hAP);
typedef BOOL			(*T_pfnAniPaf_ModifyStyle)       (H_PAF hAP, QUAD RemoveStyle, QUAD AddStyle);
typedef BOOL			(*T_pfnAniPaf_SetPos)            (H_PAF hAP, T_POS X, T_POS Y);
typedef BOOL			(*T_pfnAniPaf_SetDuration)       (H_PAF hAP, int Duration);
typedef T_SIZE			(*T_pfnAniPaf_GetWidth)          (H_PAF hAP);
typedef T_SIZE			(*T_pfnAniPaf_GetHeight)         (H_PAF hAP);
typedef T_NUM			(*T_pfnAniPaf_GetColorNum)       (H_PAF hAP);
typedef T_NUM			(*T_pfnAniPaf_GetFrameNum)       (H_PAF hAP);
typedef int			(*T_pfnAniPaf_GetDuration)       (H_PAF hAP);
typedef T_ID			(*T_pfnAniPaf_GetCurrentFrameID) (H_PAF hAP);
typedef BYTE*			(*T_pfnAniPaf_GetCurrentImage)   (H_PAF hAP);
typedef BOOL			(*T_pfnAniPaf_DrawFirstFrame)    (H_PAF hAP, BOOL bRefresh);
typedef BOOL			(*T_pfnAniPaf_DrawCurrentFrame)  (H_PAF hAP, BOOL bRefresh);
typedef BOOL			(*T_pfnAniPaf_DrawNextFrame)     (H_PAF hAP, BOOL bRefresh);
typedef BOOL			(*T_pfnAniPaf_DrawPrevFrame)     (H_PAF hAP, BOOL bRefresh);

typedef struct
{
	T_pfnAniPaf_Create			pfnCreate;
	T_pfnAniPaf_Destroy			pfnDestroy;
	T_pfnAniPaf_ModifyStyle			pfnModifyStyle;
	T_pfnAniPaf_SetPos			pfnSetPos;
	T_pfnAniPaf_SetDuration			pfnSetDuration;
	T_pfnAniPaf_GetWidth			pfnGetWidth;
	T_pfnAniPaf_GetHeight			pfnGetHeight;
	T_pfnAniPaf_GetColorNum			pfnGetColorNum;
	T_pfnAniPaf_GetFrameNum			pfnGetFrameNum;
	T_pfnAniPaf_GetDuration			pfnGetDuration;
	T_pfnAniPaf_GetCurrentFrameID		pfnGetCurrentFrameID;
	T_pfnAniPaf_GetCurrentImage		pfnGetCurrentImage;
	T_pfnAniPaf_DrawFirstFrame		pfnDrawFirstFrame;
	T_pfnAniPaf_DrawCurrentFrame		pfnDrawCurrentFrame;
	T_pfnAniPaf_DrawNextFrame		pfnDrawNextFrame;
	T_pfnAniPaf_DrawPrevFrame		pfnDrawPrevFrame;
} TApiGrp_AniPaf;


#define		AniPaf_Create(p1,p2,p3,p4,p5)		__ApiLink5(AniPaf,Create,p1,p2,p3,p4,p5)
#define		AniPaf_Destroy(p1)			__ApiLink1(AniPaf,Destroy,p1)
#define		AniPaf_ModifyStyle(p1,p2,p3)		__ApiLink3(AniPaf,ModifyStyle,p1,p2,p3)
#define		AniPaf_SetPos(p1,p2,p3)			__ApiLink3(AniPaf,SetPos,p1,p2,p3)
#define		AniPaf_SetDuration(p1,p2)		__ApiLink2(AniPaf,SetDuration,p1,p2)
#define		AniPaf_GetWidth(p1)			__ApiLink1(AniPaf,GetWidth,p1)
#define		AniPaf_GetHeight(p1)			__ApiLink1(AniPaf,GetHeight,p1)
#define		AniPaf_GetColorNum(p1)			__ApiLink1(AniPaf,GetColorNum,p1)
#define		AniPaf_GetFrameNum(p1)			__ApiLink1(AniPaf,GetFrameNum,p1)
#define		AniPaf_GetDuration(p1)			__ApiLink1(AniPaf,GetDuration,p1)
#define		AniPaf_GetCurrentFrameID(p1)		__ApiLink1(AniPaf,GetCurrentFrameID,p1)
#define		AniPaf_GetCurrentImage(p1)		__ApiLink1(AniPaf,GetCurrentImage,p1)
#define		AniPaf_DrawFirstFrame(p1,p2)		__ApiLink2(AniPaf,DrawFirstFrame,p1,p2)
#define		AniPaf_DrawCurrentFrame(p1,p2)		__ApiLink2(AniPaf,DrawCurrentFrame,p1,p2)
#define		AniPaf_DrawNextFrame(p1,p2)		__ApiLink2(AniPaf,DrawNextFrame,p1,p2)
#define		AniPaf_DrawPrevFrame(p1,p2)		__ApiLink2(AniPaf,DrawPrevFrame,p1,p2)

#endif	//	_BNSOFT__PEANUT_ANIPAF_H_
