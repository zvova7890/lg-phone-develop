/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	GUJARATI LANGUAGE REORDER FORM CODE TABLE

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

#ifndef		_LGE_REORDEREX_GUJARATI_H_
#define		_LGE_REORDEREX_GUJARATI_H_


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
extern A_CHAR	GUJR_CWN_Tbl[37];
extern A_CHAR	GUJR_IVWN_Tbl[16];
extern A_CHAR	GUJR_HALF_Tbl[37];
extern A_CHAR	GUJR_CWN_HALF_Tbl[37];
extern A_CHAR	GUJR_CWN_YA_Tbl[14];
extern A_CHAR	GUJR_CWN_YA_VA_Tbl[14]; 
extern A_CHAR	GUJR_CWN_VATTU_Tbl[37];
extern A_CHAR	GUJR_VATTU_HALF_Tbl[37];
extern A_CHAR	GUJR_CWN_VATTU_HALF_Tbl[37];
extern A_CHAR	GUJR_LIGATURE_Tbl[37][37];
extern A_CHAR	GUJR_LI_VA_Tbl[37][37]; 
#endif


//-------------------------------------------------------------------------------------------------
//	Gujarati Code Range
#define		GUJR_CODE(C)						((0x0A80 <= C) && (0x0AEF >= C))



//=================================================================================================
//	Gujarati Reordering And Rendering Rule by Sebastian
//=================================================================================================
#define GUJR_CONSONANT(C)					((0x0A95 <= C) && (0x0AB9 >= C))
#define GUJR_SIGN(C)						((0x0A81 <= C) && (C <= 0x0A83))
#define GUJR_INDEPENDENTVOWEL(C)			(((0x0A85 <= C) && (C <= 0x0A94)) || (C == 0x0AE0))
#define GUJR_DEPENDENTVOWEL(C)				((0x0ABE <= C) && (C <= 0x0ACC))
#define GUJR_PREFIX(C)						(C == 0x0ABF)
#define GUJR_VIRAMA(C)						(C == 0x0ACD)
#define GUJR_NUKTA(C)						(C == 0x0ABC)
#define GUJR_RA(C)							(C == 0x0AB0)
#define	GUJR_GENERIC(C)						((0x0AE2 <= C) && (C <= 0x0AE3))
#define GUJR_YA(C)							(C == 0x0AAF)
#define GUJR_KA(C)							(C == 0x0A95)
#define GUJR_FOLLOW_YA(C)					((C == 0x0A95) || (C == 0x0A99) ||(C == 0x0A9B) || (C == 0x0A9D) ||						\
											(C == 0x0A9F) || (C == 0x0AA0) || (C == 0x0AA1) || (C == 0x0AA2))
//=================================================================================================
//	GUJARATI REPH
#define	IS_GUJR_REPH(pC)					(GUJR_RA(*pC) && GUJR_VIRAMA(*(pC+1)) && GUJR_CONSONANT(*(pC+2)))
//-------------------------------------------------------------------------------------------------
//	CONSONANT or INDEPENDENTVOWEL WITH NUKTA
#define	IS_GUJR_CWN(pC)						(GUJR_CONSONANT(*pC) && GUJR_NUKTA(*(pC+1)))
#define	Change_GUJR_CWN(pSrc, pDst)			{																						\
												*pDst		= ZWC;																	\
												*(pDst+1)	= GUJR_CWN_Tbl[*(pSrc) - 0x0A95];										\
											}

#define	IS_GUJR_IVWN(pC)					(GUJR_INDEPENDENTVOWEL(*pC) && GUJR_NUKTA(*(pC+1)))
#define	Change_GUJR_IVWN(pSrc, pDst)		{																						\
												*pDst		= ZWC;																	\
												*(pDst+1)	= (*(pSrc) == 0x0AE0 ? 0xE69F : GUJR_IVWN_Tbl[*(pSrc) - 0x0A85]);		\
											}
//-------------------------------------------------------------------------------------------------
//	LIGATURE
#if defined(LGSI_INDIAN_LANGUAGE_SUPPORT)
/*Animesh:Indian language rendering rules start*/
#define	IS_GUJR_ZWJ_HALF(pC)				(GUJR_CONSONANT(*pC) && GUJR_VIRAMA(*(pC+1)) && (ZWJ == *(pC+2)) && GUJR_CONSONANT(*(pC+3)))
#define	Change_GUJR_ZWJ_HALF(pSrc, pDst)	{																						\
												*pDst		= ZWC;																	\
												*(pDst+1)	= ZWC;																	\
												*(pDst+2)	= GUJR_HALF_Tbl[*(pSrc) - 0x0A95];										\
											}

/*Animesh:Indian language rendering rules end*/
#endif
#define	IS_GUJR_LIGATURE(pC)				(GUJR_CONSONANT(*pC) && GUJR_VIRAMA(*(pC+1)) && GUJR_CONSONANT(*(pC+2)))
#define	Change_GUJR_HALF(pSrc, pDst)		{																						\
												*pDst		= ZWC;																	\
												*(pDst+1)	= GUJR_HALF_Tbl[*(pSrc) - 0x0A95];										\
											}
#define	Change_GUJR_LIGATURE(pSrc, pDst)	{																						\
												*pDst		= ZWC;																	\
												*(pDst+1)	= ZWC;																	\
												*(pDst+2)	= GUJR_LIGATURE_Tbl[*(pSrc) - 0x0A95][*(pSrc+2) - 0x0A95];				\
											}
#if defined(LGSI_INDIAN_LANGUAGE_SUPPORT)
/*Animesh:Indian language rendering rules start*/
#define	IS_GUJR_CWN_ZWJ_HALF(pC)			(GUJR_CONSONANT(*pC) && GUJR_NUKTA(*(pC+1)) && GUJR_VIRAMA(*(pC+2)) && (ZWJ == *(pC+3)) \
											&& GUJR_CONSONANT(*(pC+4)))
#define	Change_GUJR_CWN_ZWJ_HALF(pSrc, pDst){																						\
												*pDst		= ZWC;																	\
												*(pDst+1)	= ZWC;																	\
												*(pDst+2)	= ZWC;																	\
												*(pDst+3)	= GUJR_CWN_HALF_Tbl[*(pSrc) - 0x0A95];									\
											}
/*Animesh:Indian language rendering rules end*/
#endif

#define	IS_GUJR_CWN_HALF(pC)				(GUJR_CONSONANT(*pC) && GUJR_NUKTA(*(pC+1)) && GUJR_VIRAMA(*(pC+2)) &&					\
											GUJR_CONSONANT(*(pC+3)))
#define	Change_GUJR_CWN_HALF(pSrc, pDst)	{																						\
												*pDst		= ZWC;																	\
												*(pDst+1)	= ZWC;																	\
												*(pDst+2)	= GUJR_CWN_HALF_Tbl[*(pSrc) - 0x0A95];									\
											}

#define	IS_GUJR_CWN_KA(pC)					(GUJR_KA(*pC) && GUJR_NUKTA(*(pC+1)) && GUJR_VIRAMA(*(pC+2)) && GUJR_KA(*(pC+3)))
#define	Change_GUJR_CWN_KA(pSrc, pDst)		{																						\
												*pDst		= ZWC;																	\
												*(pDst+1)	= ZWC;																	\
												*(pDst+2)	= ZWC;																	\
												*(pDst+3)	= 0xE732;																\
											}

#define	IS_GUJR_CWN_YA(pC)					(GUJR_FOLLOW_YA(*pC) && GUJR_NUKTA(*(pC+1)) && GUJR_VIRAMA(*(pC+2)) && GUJR_YA(*(pC+3)))
#define	Change_GUJR_CWN_YA(pSrc, pDst)		{																						\
												*pDst		= ZWC;																	\
												*(pDst+1)	= ZWC;																	\
												*(pDst+2)	= ZWC;																	\
												*(pDst+3)	= GUJR_CWN_YA_Tbl[*(pSrc) - 0x0A95];									\
											}

#define	IS_GUJR_CWN_VATTU(pC)				(GUJR_CONSONANT(*pC) && GUJR_NUKTA(*(pC+1)) && GUJR_VIRAMA(*(pC+2)) && GUJR_RA(*(pC+3)))
#define	Change_GUJR_CWN_VATTU(pSrc, pDst)	{																						\
												*pDst		= ZWC;																	\
												*(pDst+1)	= ZWC;																	\
												*(pDst+2)	= ZWC;																	\
												*(pDst+3)	= GUJR_CWN_VATTU_Tbl[*(pSrc) - 0x0A95];									\
											}

#define	IS_GUJR_VATTU_HALF(pC)				(GUJR_CONSONANT(*pC) && GUJR_VIRAMA(*(pC+1)) && GUJR_RA(*(pC+2)) &&						\
											GUJR_VIRAMA(*(pC+3)) && GUJR_CONSONANT(*(pC+4)))
#define	Change_GUJR_VATTU_HALF(pSrc, pDst)	{																						\
												*pDst		= ZWC;																	\
												*(pDst+1)	= ZWC;																	\
												*(pDst+2)	= ZWC;																	\
												*(pDst+3)	= GUJR_VATTU_HALF_Tbl[*(pSrc) - 0x0A95];								\
											}

#define	IS_GUJR_CWN_VATTU_HALF(pC)			(GUJR_CONSONANT(*pC) && GUJR_NUKTA(*(pC+1)) && GUJR_VIRAMA(*(pC+2)) &&					\
											GUJR_RA(*(pC+3)) &&	GUJR_VIRAMA(*(pC+4)) && GUJR_CONSONANT(*(pC+5)))
#define	Change_GUJR_CWN_VATTU_HALF(pSrc, pDst)	{																					\
												*pDst		= ZWC;																	\
												*(pDst+1)	= ZWC;																	\
												*(pDst+2)	= ZWC;																	\
												*(pDst+3)	= ZWC;																	\
												*(pDst+4)	= GUJR_CWN_VATTU_HALF_Tbl[*(pSrc) - 0x0A95];							\
											}

#define	IS_GUJR_SIGN_R(pC)					((*pC == 0x0AB9) && (*(pC+1) == 0x0AC3))
#define	Change_GUJR_SR(pSrc, pDst)			{																						\
												*pDst		= ZWC;																	\
												*(pDst+1)	= 0x0AD4;																\
											}
#define	IS_GUJR_SIGN_NR(pC)					((*pC == 0x0AB9) && GUJR_NUKTA(*(pC+1)) && (*(pC+2) == 0x0AC3))
#define	Change_GUJR_NSR(pSrc, pDst)			{																						\
												*pDst		= ZWC;																	\
												*(pDst+1)	= ZWC;																	\
												*(pDst+2)	= 0x0AD5;																\
											}

#define	IS_GUJR_LI_VA(pC)					((((*pC == 0x0A95) && GUJR_VIRAMA(*(pC+1)) && ((*(pC+2) == 0x0A95) ||					\
											(*(pC+2) == 0x0AAF))) || (((*pC == 0x0A99) || (*pC == 0x0A9B) || (*pC == 0x0A9D)) &&	\
											GUJR_VIRAMA(*(pC+1)) && (*(pC+2) == 0x0AAF)) || ((*pC == 0x0A9C) && GUJR_VIRAMA(*(pC+1))\
											&& (*(pC+2) == 0x0AAE) ) || ((*pC == 0x0A9E) && GUJR_VIRAMA(*(pC+1)) &&					\
											((*(pC+2) == 0x0A9A) || (*(pC+2) == 0x0A9C))) || ((*pC == 0x0A9F) &&					\
											GUJR_VIRAMA(*(pC+1)) && ((*(pC+2) == 0x0A9F) || (*(pC+2) == 0x0AA0) ||					\
											(*(pC+2) == 0x0AAF))) || ((*pC == 0x0AA0) && GUJR_VIRAMA(*(pC+1)) &&					\
											((*(pC+2) == 0x0AA0) || (*(pC+2) == 0x0AAF))) || ((*pC == 0x0AA1) &&					\
											GUJR_VIRAMA(*(pC+1)) && ((*(pC+2) == 0x0AA1) || (*(pC+2) == 0x0AA2)						\
											||(*(pC+2) == 0x0AAF))) || ((*pC == 0x0AA2) && GUJR_VIRAMA(*(pC+1)) &&					\
											((*(pC+2) == 0x0AA2) || (*(pC+2) == 0x0AAF))) || ((*pC == 0x0AA4) &&					\
											GUJR_VIRAMA(*(pC+1)) && (*(pC+2) == 0x0AA4) ) || ((*pC == 0x0AA6) &&					\
											GUJR_VIRAMA(*(pC+1)) && ((*(pC+2) == 0x0A97) || (*(pC+2) == 0x0A98)	||					\
											(*(pC+2) == 0x0AA6) ||(*(pC+2) == 0x0AA7) || (*(pC+2) == 0x0AA8) || (*(pC+2) == 0x0AAC)	\
											|| (*(pC+2) == 0x0AAD) || (*(pC+2) == 0x0AAE) || (*(pC+2) == 0x0AAF) ||					\
											(*(pC+2) == 0x0AB5))) || ((*pC == 0x0AA8) && GUJR_VIRAMA(*(pC+1)) &&					\
											(*(pC+2) == 0x0AA8)) ||	((*pC == 0x0AB6) && GUJR_VIRAMA(*(pC+1)) && ((*(pC+2) == 0x0A9A)\
											|| (*(pC+2) == 0x0AA8) || (*(pC+2) == 0x0AB5))) ||										\
											((*pC == 0x0AB9) && GUJR_VIRAMA(*(pC+1)) && ((*(pC+2) == 0x0AA3) || (*(pC+2) == 0x0AA8)	\
											|| (*(pC+2) == 0x0AAE) || (*(pC+2) == 0x0AAF) || (*(pC+2) == 0x0AB2) ||					\
											(*(pC+2) == 0x0AB5)))) && GUJR_VIRAMA(*(pC+3)) && GUJR_RA(*(pC+4)))
#define	Change_GUJR_LI_VA(pSrc, pDst)		{																						\
												*pDst		= ZWC;																	\
												*(pDst+1)	= ZWC;																	\
												*(pDst+2)	= ZWC;																	\
												*(pDst+3)	= ZWC;																	\
												*(pDst+4)	= GUJR_LI_VA_Tbl[*(pSrc) - 0x0A95][*(pSrc+2) - 0x0A95];					\
											}

#define	IS_GUJR_CWN_KA_VA(pC)				(GUJR_KA(*pC) && GUJR_NUKTA(*(pC+1)) && GUJR_VIRAMA(*(pC+2)) && GUJR_KA(*(pC+3)) &&		\
											GUJR_VIRAMA(*(pC+4)) && GUJR_RA(*(pC+5)))
#define	Change_GUJR_CWN_KA_VA(pSrc, pDst)	{																						\
												*pDst		= ZWC;																	\
												*(pDst+1)	= ZWC;																	\
												*(pDst+2)	= ZWC;																	\
												*(pDst+3)	= ZWC;																	\
												*(pDst+4)	= ZWC;																	\
												*(pDst+5)	= 0xE7C8;																\
											}
#define	IS_GUJR_CWN_YA_VA(pC)				(GUJR_FOLLOW_YA(*pC) && GUJR_NUKTA(*(pC+1)) && GUJR_VIRAMA(*(pC+2)) && GUJR_YA(*(pC+3))	\
											&& GUJR_VIRAMA(*(pC+4)) && GUJR_RA(*(pC+5)))
#define	Change_GUJR_CWN_YA_VA(pSrc, pDst)	{																						\
												*pDst		= ZWC;																	\
												*(pDst+1)	= ZWC;																	\
												*(pDst+2)	= ZWC;																	\
												*(pDst+3)	= ZWC;																	\
												*(pDst+4)	= ZWC;																	\
												*(pDst+5)	= GUJR_CWN_YA_VA_Tbl[*(pSrc) - 0x0A95];									\
											}


//-------------------------------------------------------------------------------------------------
//	Member Function.
extern BOOL		ReorderEx_Gujarati			(TReorderExAttr* Attr, T_NUM nBase, T_NUM nLen);
//-------------------------------------------------------------------------------------------------
#endif	//	_LGE_REORDEREX_GUJARATI_H_
