/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	MALAYALAM LANGUAGE REORDER FORM CODE TABLE

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

#ifndef		_LGE_REORDEREX_MALAYALAM_H_
#define		_LGE_REORDEREX_MALAYALAM_H_


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
extern A_CHAR	MLYM_HALF_Tbl[37];
extern A_CHAR	MLYM_LIGATURE_Tbl[37][37];
extern A_CHAR	MLYM_TWO_E_Tbl[37];
extern A_CHAR	MLYM_TWO_EE_Tbl[37];
#endif


//-------------------------------------------------------------------------------------------------
//	Malayalam Code Range
#define		MLYM_CODE(C)						((0x0D00 <= C) && (0x0D7F >= C))


//=================================================================================================
//	Malayalam Reordering And Rendering Rule by Sebastian
//=================================================================================================
#define	MLYM_CONSONANT(C)					((0x0D15 <= C) && (C <= 0x0D39))
#define	MLYM_INDEPENDENTVOWEL(C)			((0x0D05 <= C) && (C <= 0x0D14))			
#define MLYM_DEPENDENTVOWEL(C)				((0x0D3E <= C) && (C <= 0x0D43))
#define	MLYM_LENGTHMARK(C)					(C == 0x0D57)
#define	MLYM_SIGN(C)						((0x0D02 <= C) && (C <= 0x0D03))
#define	MLYM_VIRAMA(C)						(C == 0x0D4D)
#define	MLYM_PREFIX(C)						((0x0D46 <= C) && (C <= 0x0D48))
#define	MLYM_TWOPART(C)						((0x0D4A <= C) && (C <= 0x0D4C))
#define MLYM_RA(C)							(C == 0x0D30)			//	Vattu
#define MLYM_YA(C)							(C == 0x0D2F)			//	Post Consonant
#define MLYM_VA(C)							(C == 0x0D35)			//	Post Consonant
#define MLYM_LA(C)							(C == 0x0D32)			//	Below Consonant
#define	MLYM_NOT_BELOW_POST_C(C)			((C == 0x0D31) || (C == 0x0D33) || (C == 0x0D34))	//	Below/Post 예외

#if defined(LGSI_INDIAN_LANGUAGE_SUPPORT)
/*Animesh:Indian language rendering rules start*/
#define	MLYM_CHILLU_LETTERS(C)			(C == 0x0D32|| C == 0x0D28 || C == 0x0D30 || C == 0x0D23 || C == 0x0D33 || C == 0x0D15)
#define	MLYM_YAVA(C)						(C == 0x0D2F ||C == 0x0D35)	

#define IS_MLYM_CHILLU(pC)					((MLYM_CHILLU_LETTERS(*pC))&& MLYM_VIRAMA(*(pC+1)) && (ZWJ == *(pC+2)) )
#define	Change_To_CHIILU(pSrc, pDst){									\
												*pDst = ((*pSrc ==0x0D32 ) ? 0x0D7D:((*pSrc == 0x0D28) ? 0x0D7B: ((*pSrc == 0x0D30) ? 0x0D7C: ((*pSrc ==0x0D23) ? 0x0D7A : ((*pSrc ==0x0D33) ? 0x0D7E:0xD7F)))));		\
												*(pDst+1) = ZWC;		\
									}

#define	IS_MLYM_INDA(pC)						(*pC == 0x0D23 && *(pC+1) == 0x0D4D && *(pC+2) == 0x0D1F)
#define	Change_To_INDA(pSrc,pDst){													\
												*pDst	  = 0x0E8CD;				\
												*(pDst+1) = ZWC;				\
												*(pDst+2) = ZWC;				\
								 }

#define	IS_MLYM_INJA(pC)						(*pC == 0x0D1E && *(pC+1) == 0x0D4D && *(pC+2) == 0x0D1A)
#define	Change_To_INJA(pSrc,pDst){												\
												*pDst	  = ZWC;				\
												*(pDst+1) = ZWC;				\
												*(pDst+2) = 0x0E8CE;			\
									}
#define	IS_MLYM_NTA(pC)				((*pC == 0x0D28 && *(pC + 1) == 0x0D4D && *(pC + 2) == 0x0200D && *(pC + 3) == 0x0D31 && *(pC + 4) == 0x0D46))	

//#define	IS_MLYM_YAVA(pC)					(MLYM_YAVA(*pC)  && MLYM_VIRAMA(*(pC+1)) && MLYM_YAVA(*(pC+2)))
#define	IS_MLYM_YA(pC)					(*pC == 0x0D35  && MLYM_VIRAMA(*(pC+1)) && *(pC+2) ==  0x0D35)
#define	IS_MLYM_VA(pC)					(*pC == 0x0D2F  && MLYM_VIRAMA(*(pC+1)) && *(pC+2) ==  0x0D2F)
#define	IS_MLYM_CONSTVIRAMCOMB(pC)		((MLYM_CONSONANT(*pC) )&& (MLYM_VIRAMA(*(pC+1))) && (MLYM_CONSONANT(*(pC+2))) \
												&& (MLYM_VIRAMA(*(pC+3))) && (MLYM_CONSONANT(*(pC+4)) ||*(pC+4)== 0x200C))
#define	IS_MLYM_ZWJ_HALF(pC)				(MLYM_CONSONANT(*pC) && MLYM_VIRAMA(*(pC+1)) && (ZWJ == *(pC+2)) && MLYM_CONSONANT(*(pC+3)))
#define	Change_MLYM_ZWJ_HALF(pSrc, pDst)	{																						\
												*pDst		= ZWC;																	\
												*(pDst+1)	= ZWC;																	\
												*(pDst+1)	= MLYM_HALF_Tbl[*(pSrc) - 0x0D15];										\
											}												
/*Animesh:Indian language rendering rules end*/
#endif

#define	IS_MLYM_LIGATURE(pC)				(MLYM_CONSONANT(*pC) && MLYM_VIRAMA(*(pC+1)) && MLYM_CONSONANT(*(pC+2)))
#define	Change_MLYM_LIGATURE(pSrc, pDst)	{																						\
												*pDst		= ZWC;																	\
												*(pDst+1)	= ZWC;																	\
												*(pDst+2)	= MLYM_LIGATURE_Tbl[*(pSrc) - 0x0D15][*(pSrc+2) - 0x0D15];				\
											}
#define	Change_MLYM_HALF(pSrc, pDst)		{																						\
												*pDst		= ZWC;																	\
												*(pDst+1)	= MLYM_HALF_Tbl[*(pSrc) - 0x0D15];										\
											}

#define	IS_MLYM_POST(pC)					((MLYM_CONSONANT(*pC) && MLYM_VIRAMA(*(pC+1)) && (MLYM_YA(*(pC+2)) || MLYM_VA(*(pC+2))))\
											&& !MLYM_NOT_BELOW_POST_C(*pC))
#define	Change_MLYM_POST(pSrc, pDst)		{																						\
												*pDst		= ZWC;																	\
												*(pDst+1)	= *(pSrc);																\
												*(pDst+2)	= ((*(pSrc+2)) == 0x0D2F ? 0x0D62 : 0x0D63);							\
											}

#define	IS_MLYM_BELOW(pC)					((MLYM_CONSONANT(*pC) && MLYM_VIRAMA(*(pC+1)) && MLYM_LA(*(pC+2)))						\
											&& !MLYM_NOT_BELOW_POST_C(*pC))
#define	Change_MLYM_BELOW(pSrc, pDst)		{																						\
												*pDst		= ZWC;																	\
												*(pDst+1)	= *(pSrc);																\
												*(pDst+2)	= 0x0D64;																\
											}
#define	IS_MLYM_VATTU(pC)					((MLYM_CONSONANT(*pC) && MLYM_VIRAMA(*(pC+1)) && MLYM_RA(*(pC+2)))						\
											&& !MLYM_NOT_BELOW_POST_C(*pC))
#define	Change_MLYM_VATTU(pSrc, pDst)		{																						\
												*pDst		= ZWC;																	\
												*(pDst+1)	= 0x0D65;																\
												*(pDst+2)	= *(pSrc);																\
											}
#define	Change_MLYM_TWO_E(pSrc, pDst)		*(pDst)		= MLYM_TWO_E_Tbl[*(pSrc) - 0x0D15];
#define	Change_MLYM_TWO_EE(pSrc, pDst)		*(pDst)		= MLYM_TWO_EE_Tbl[*(pSrc) - 0x0D15];




//-------------------------------------------------------------------------------------------------
//	Member Function.
extern BOOL		ReorderEx_Malayalam			(TReorderExAttr* Attr, T_NUM nBase, T_NUM nLen);
//-------------------------------------------------------------------------------------------------
#endif	//	_LGE_REORDEREX_MALAYALAM_H_
