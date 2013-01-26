/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	SINHALA LANGUAGE REORDER FORM CODE TABLE

	Copyright(c)     2010 LG Electronics Inc.

	그룹 : TextLayoutLib API
	구분 : 기본모듈
	등급 : 비공개
	버전 : 2.00
	일자 : 2010.05.03

	Date		Name		Version		Description
	----------	------		----------	-----------------------------------------------------------	
	2010.05.03		.			v2.00		Create.
	
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_LGE_REORDEREX_SINHALA_H_
#define		_LGE_REORDEREX_SINHALA_H_


#include	"ReorderEx_Common.h"
#include	"..\..\BasicApiLib\Include\Include.h"



#ifndef	ReorderDllExport
#ifndef	BNS_EMULATOR
#define	ReorderDllExport		extern
#else
#define	ReorderDllExport		__declspec(dllexport)
#endif
#endif


#ifdef	BNS_MAIN_VERSION
extern A_CHAR	SINH_AL_LAKUNA_Tbl[45];
extern A_CHAR	SINH_VOWEL_A_Tbl[5][45];
extern A_CHAR	SINH_TWOPART_Tbl[45];
#endif



//-------------------------------------------------------------------------------------------------
//	Sinhala Code Range
#define		SINH_CODE(C)						((0x0D80 <= C) && (0x0DF4 >= C))



//=================================================================================================
//	Sinhala Reordering And Rendering Rule by Sebastian
//=================================================================================================
#define	SINH_CONSONANT(C)					((0x0D9A <= C) && (C <= 0x0DC6))
#define	SINH_AL_LAKUNA(C)					(C == 0x0DCA)
#define	SINH_VOWEL_A(C)						(((0x0DD2 <= C) && (C <= 0x0DD4)) || (C == 0x0DD6))
#define	SINH_RA(C)							(C == 0x0DBB)
#define	SINH_VOWEL_B(C)						((0x0DD0 <= C) && (C <= 0x0DD1))
#define	SINH_PREFIX_A(C)					((C == 0x0DD9) || (C == 0x0DDB))
#define	SINH_PREFIX_B(C)					(C == 0x0DDA)
#define	SINH_TWOPART(C)						((0x0DDC <= C) && (C <= 0x0DDE))

#define	IS_SINH_AL_LAKUNA(pC)				(SINH_CONSONANT(*pC) && SINH_AL_LAKUNA(*(pC+1)))
#define	Change_SINH_AL_LAKUNA(pSrc, pDst)	{																						\
												*pDst		= ZWC;																	\
												*(pDst+1)	= SINH_AL_LAKUNA_Tbl[*(pSrc) - 0x0D9A];									\
											}
#define	IS_SINH_VOWEL_A(pC)					(SINH_CONSONANT(*pC) && SINH_VOWEL_A(*(pC+1)))
#define	Change_SINH_VOWEL_A(pSrc, pDst)		{																						\
												*pDst		= ZWC;																	\
												*(pDst+1)	= SINH_VOWEL_A_Tbl[*(pSrc+1) - 0x0DD2][*(pSrc) - 0x0D9A];				\
											}
#define	IS_SINH_VOWEL_B(pC)					(SINH_RA(*pC) && SINH_VOWEL_B(*(pC+1)))
#define	Change_SINH_VOWEL_B(pSrc, pDst)		{																						\
												*pDst		= ZWC;																	\
												*(pDst+1)	= *(pSrc+1) == 0x0DD0 ? 0xED1D : 0xED1E;								\
											}
#define	IS_SINH_PREFIX_A(pC)				(SINH_CONSONANT(*pC) && SINH_PREFIX_A(*(pC+1)))
#define	Change_SINH_PREFIX_A(pSrc, pDst)	{																						\
												*pDst		= *(pSrc+1) == 0x0DD9 ? 0x0DE4 : 0x0DE5;								\
												*(pDst+1)	= *pSrc;																\
											}
#define	IS_SINH_PREFIX_B(pC)				(SINH_CONSONANT(*pC) && SINH_PREFIX_B(*(pC+1)))
#define	Change_SINH_PREFIX_B(pSrc, pDst)	{																						\
												*pDst		= 0x0DE4;																\
												*(pDst+1)	= SINH_AL_LAKUNA_Tbl[*(pSrc) - 0x0D9A];									\
											}
#define	IS_SINH_TWOPART(pC)					(SINH_CONSONANT(*pC) && SINH_TWOPART(*(pC+1)))
#define	Change_SINH_TWOPART(pSrc, pDst)		{																						\
												*pDst		= SINH_TWOPART_Tbl[*(pSrc) - 0x0D9A];									\
												*(pDst+1)	= *(pSrc+1) == 0x0DDC ? 0x0DE0 : (*(pSrc+1) == 0x0DDD ? 0x0DE9 : 0x0DE6);\
											}


//-------------------------------------------------------------------------------------------------
//	Member Function.
extern BOOL		ReorderEx_Sinhala			(TReorderExAttr* Attr, T_NUM nBase, T_NUM nLen);
//-------------------------------------------------------------------------------------------------
#endif	//	_LGE_REORDEREX_SINHALA_H_
