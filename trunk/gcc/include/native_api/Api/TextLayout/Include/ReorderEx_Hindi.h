/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	HINDI LANGUAGE REORDER FORM CODE TABLE

	Copyright(c)     2010 LG Electronics Inc.

	그룹 : TextLayoutLib API
	구분 : 기본모듈
	등급 : 비공개
	버전 : 2.00
	일자 : 2010.05.03

	Date		Name		Version		Description
	----------	------		----------	-----------------------------------------------------------	
	2010.05.03		.			v2.00	Create.
	
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef		_LGE_REORDEREX_HINDI_H_
#define		_LGE_REORDEREX_HINDI_H_


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
extern A_CHAR	DEVA_LIGATURE_Tbl[37][37];
extern A_CHAR	DEVA_CONJUCT_HALF_Tbl[34][35];
extern A_CHAR	DEVA_HALF_Tbl[37];
extern A_CHAR	DEVA_CWN_Tbl[37];
extern A_CHAR	DEVA_CWN_H_Tbl[37];
extern A_CHAR	DEVA_IWN_Tbl[16];
extern A_CHAR	DEVA_ADHALF_Tbl[8];
extern A_CHAR	DEVA_AC_VATTU_Tbl[8];
extern A_CHAR	AClusterFormTbl[8];
extern A_CHAR	DEVA_RA_SUB_Tbl[28];
extern A_CHAR	DEVA_RA_SUB_NUKTA_Tbl[27];
extern A_CHAR	ClusterFormTbl[37];
extern A_CHAR	CWNVTbl[37];
extern A_CHAR	CWNVHTbl[37];	
extern A_CHAR	BOTSIGNTbl[28][4];
extern A_CHAR	ADDBOTSIGNTbl[2][4];
extern A_CHAR	NUKBOTSIGNTbl[27][4];
extern A_CHAR	DEVA_SSA_BOTTOM_Tbl[2][4];
#endif


//-------------------------------------------------------------------------------------------------
//	Hindi Code Range
#define		DEVA_CODE(C)						((0x0900 <= C) && (0x097F >= C))



//=================================================================================================
//	Hindi Reordering And Rendering Rule by Sebastian
//=================================================================================================
#define	DEVA_C(C)							(DEVA_CONSONANT(C) || DEVA_CONSONANT_WN(C) || DEVA_ADDCONSONANT(C))
#define DEVA_CONSONANT(C)					(((0x0915 <= C) && (C <= 0x0928)) || ((0x092A <= C) && (C <= 0x0930)) || \
											((0x0932 <= C) && (C <= 0x0933)) || ((0x0935 <= C) && (C <= 0x0939)))
#define	DEVA_CONSONANT_WN(C)				((C == 0x0929) || (C == 0x0931) || (C == 0x0934))
#define	DEVA_ADDCONSONANT(C)				((0x0958 <= C) && (C <= 0x095F))
#define DEVA_SIGN(C)						((0x0901 <= C) && (C <= 0x0903))
#define DEVA_INDEPENDENTVOWEL(C)			((0x0905 <= C) && (C <= 0x0914))
#define DEVA_BOTTOMVOWEL(C)					((0x0941 <= C) && (C <= 0x0944))
#define DEVA_PREFIX(C)						(C == 0x093F)
#define DEVA_VIRAMA(C)						(C == 0x094D)
#define DEVA_NUKTA(C)						(C == 0x093C)
#define DEVA_RA(C)							(C == 0x0930)

//=================================================================================================
//	DEVANAGARI REPH
#define	IS_DEVA_REPH(pC)					(DEVA_RA(*pC) && DEVA_VIRAMA(*(pC+1)) && DEVA_C(*(pC+2)))
//=================================================================================================
//	INDEPENDENT VOWEL_WITH_NUKTA
#define	IS_DEVA_IWN(pC)						(DEVA_INDEPENDENTVOWEL(*pC) && DEVA_NUKTA(*(pC+1)))
#define	Change_IWN(pSrc, pDst)				{																						\
												*pDst		= ZWC;																	\
												*(pDst+1)	= DEVA_IWN_Tbl[*(pSrc) - 0x0905];										\
											}
//=================================================================================================
//	CONSONANT_WITH_NUKTA
#define	IS_DEVA_CWN(pC)						(DEVA_CONSONANT(*pC) && DEVA_NUKTA(*(pC+1)))
#define	Change_DEVA_CWN(pSrc, pDst)			{																						\
												*pDst		= ZWC;																	\
												*(pDst+1)	= DEVA_CWN_Tbl[*(pSrc) - 0x0915];										\
											}
//=================================================================================================
//	DEVANAGARI LIGATURE & HALF FORM MACRO
#define	IS_DEVA_LIGATURE(pC)				((DEVA_CONSONANT(*pC) || DEVA_CONSONANT_WN(*pC)) && DEVA_VIRAMA(*(pC+1)) &&				\
											DEVA_CONSONANT(*(pC+2)))
#define	Change_DEVA_LIGATURE(pSrc, pDst)	{																						\
												*pDst		= ZWC;																	\
												*(pDst+1)	= ZWC;																	\
												*(pDst+2)	= DEVA_LIGATURE_Tbl[*(pSrc) - 0x0915][*(pSrc+2) - 0x0915];				\
											}
#define	IS_DEVA_HALF(pC)					((DEVA_CONSONANT(*pC) || DEVA_CONSONANT_WN(*pC)) && DEVA_VIRAMA(*(pC+1)) &&				\
											DEVA_C(*(pC+2)))
#define	Change_DEVA_HALF(pSrc, pDst)		{																						\
												*pDst		= ZWC;																	\
												*(pDst+1)	= DEVA_HALF_Tbl[*(pSrc) - 0x0915];										\
											}
//=================================================================================================
// DEVANAGARI ADDITIONAL CONSONANTS HALF MACRO
#define	IS_DEVA_ADD_HALF(pC)				(DEVA_ADDCONSONANT(*pC) && DEVA_VIRAMA(*(pC+1)) && DEVA_C(*(pC+2)))
#define	Change_DEVA_ADD_HALF(pSrc, pDst)	{																						\
												*pDst		= ZWC;																	\
												*(pDst+1)	= DEVA_ADHALF_Tbl[*(pSrc) - 0x0958];									\
											}
//=================================================================================================
// DEVANAGARI CONSONANTS SURPRESS VATTU MACRO
#define	IS_DEVA_VATTU(pC)					(DEVA_CONSONANT(*pC) && DEVA_VIRAMA(*(pC+1)) && DEVA_RA(*(pC+2)))
//=================================================================================================
// DEVANAGARI ADDITIONAL CONSONANTS SURPRESS VATTU MACRO
#define	IS_DEVA_ADD_VATTU(pC)				(DEVA_ADDCONSONANT(*pC) && DEVA_VIRAMA(*(pC+1)) && DEVA_RA(*(pC+2)))
#define	Change_DEVA_ADD_VATTU(pSrc, pDst)	{																						\
												*pDst		= ZWC;																	\
												*(pDst+1)	= ZWC;																	\
												*(pDst+2)	= DEVA_AC_VATTU_Tbl[*(pSrc) - 0x0958];									\
											}
//=================================================================================================
//	DEVANAGARI CONSONANT WITH NUKTA VATTU MACRO
#define	IS_DEVA_CWN_VATTU(pC)				(DEVA_CONSONANT(*pC) && DEVA_NUKTA(*(pC+1)) && DEVA_VIRAMA(*(pC+2)) && DEVA_RA(*(pC+3)))
#define	Change_DEVA_CWN_VATTU(pSrc, pDst)	{																						\
												*pDst		= ZWC;																	\
												*(pDst+1)	= ZWC;																	\
												*(pDst+2)	= ZWC;																	\
												*(pDst+3)	= CWNVTbl[*(pSrc) - 0x0915];											\
											}
//=================================================================================================
//	DEVANAGARI CONSONANT WITH NUKTA HALF FORM MACRO
#define	IS_DEVA_CWN_HALF(pC)				(DEVA_CONSONANT(*pC) && DEVA_NUKTA(*(pC+1)) && DEVA_VIRAMA(*(pC+2)) && DEVA_C(*(pC+3)))
#define	Change_DEVA_CWN_HALF(pSrc, pDst)	{																						\
												*pDst		= ZWC;																	\
												*(pDst+1)	= ZWC;																	\
												*(pDst+2)	= DEVA_CWN_H_Tbl[*(pSrc) - 0x0915];										\
											}
//=================================================================================================
//	CONJUCT SUPRESS VATTU HALF MACRO
#define	IS_DEVA_CONJUCT_VATTU_HALF(pC)		((((*pC == 0x0915) && DEVA_VIRAMA(*(pC+1)) && (*(pC+2) == 0x0937) && DEVA_VIRAMA(*(pC+3)))	\
											|| ((*pC == 0x091C) && DEVA_VIRAMA(*(pC+1)) && (*(pC+2) == 0x091E) && DEVA_VIRAMA(*(pC+3)))	\
											|| ((*pC == 0x0938) && DEVA_VIRAMA(*(pC+1)) && (*(pC+2) == 0x0924) && DEVA_VIRAMA(*(pC+3))))	\
											&& DEVA_RA(*(pC+4)) && DEVA_VIRAMA(*(pC+5)) && DEVA_C(*(pC+6)))
#define	Change_DEVA_CVH(pSrc, pDst)			{																						\
												*pDst		= ZWC;																	\
												*(pDst+1)	= ZWC;																	\
												*(pDst+2)	= ZWC;																	\
												*(pDst+3)	= ZWC;																	\
												*(pDst+4)	= ZWC;																	\
												*(pDst+5)	= (*pSrc == 0x0915 ? 0xE19C : (*pSrc == 0x091C ? 0xE19D : 0xE200));		\
											}
//=================================================================================================
// CONJUCT_SUPRESS_VATTU MACRO
#define	IS_DEVA_CONJUCT_A_VATTU(pC)			((((*pC == 0x0915) && DEVA_VIRAMA(*(pC+1)) && (*(pC+2) == 0x0937)) ||					\
											((*pC == 0x091C) && DEVA_VIRAMA(*(pC+1)) && (*(pC+2) == 0x091E)) ||						\
											((*pC == 0x0938) && DEVA_VIRAMA(*(pC+1)) && (*(pC+2) == 0x0924))) &&					\
											DEVA_VIRAMA(*(pC+3)) && DEVA_RA(*(pC+4)))
#define	Change_DEVA_CONJUCT_A_VT(pSrc, pDst){																						\
												*pDst		= ZWC;																	\
												*(pDst+1)	= ZWC;																	\
												*(pDst+2)	= ZWC;																	\
												*(pDst+3)	= ZWC;																	\
												*(pDst+4)	= (*pSrc == 0x0915 ? 0xE194 : (*pSrc == 0x091C ? 0xE195 : 0xE19F));		\
											}
#define	IS_DEVA_CONJUCT_B_VATTU(pC)			((*pC == 0x0937) && DEVA_VIRAMA(*(pC+1)) && ((*(pC+2) == 0x091F) || (*(pC+2) == 0x0920))\
											&& DEVA_VIRAMA(*(pC+3)) && DEVA_RA(*(pC+4)))
#define	Change_DEVA_CONJUCT_B_VT(pSrc, pDst){																						\
												*pDst		= ZWC;																	\
												*(pDst+1)	= ZWC;																	\
												*(pDst+2)	= ZWC;																	\
												*(pDst+3)	= ZWC;																	\
												*(pDst+4)	= ((*(pSrc+2)) == 0x091F ? 0xE196 : 0xE197);							\
											}
//=================================================================================================
//	DEVANAGARI BOTTOM DEPENDENT VOWEL MACRO
#define	IS_DEVA_SSA_BOTTOM(pC)				((*pC == 0x0937) && DEVA_VIRAMA(*(pC+1)) && ((*(pC+2) == 0x091F) ||						\
											(*(pC+2) == 0x0920)) && DEVA_VIRAMA(*(pC+3)) && DEVA_RA(*(pC+4)) &&						\
											DEVA_BOTTOMVOWEL(*(pC+5)))
#define	Change_DEVA_SSA_BOTTOM(pSrc, pDst)	{																						\
												*pDst		= ZWC;																	\
												*(pDst+1)	= ZWC;																	\
												*(pDst+2)	= ZWC;																	\
												*(pDst+3)	= ZWC;																	\
												*(pDst+4)	= ZWC;																	\
												*(pDst+5)	= DEVA_SSA_BOTTOM_Tbl[*(pSrc+2) - 0x091F][*(pSrc+5) - 0x0941];			\
											}
#define	IS_DEVA_BOTTOMSIGN(pC)				(((*pC == 0x0919) || (*pC == 0x091B) || (*pC == 0x091F) || (*pC == 0x0920) ||			\
											(*pC == 0x0921) || (*pC == 0x0930) || (*pC == 0x0931) || (*pC == 0x0933) ||				\
											(*pC == 0x0934)) && DEVA_VIRAMA(*(pC+1)) && DEVA_RA(*(pC+2)) &&							\
											DEVA_BOTTOMVOWEL(*(pC+3)))
#define	Change_DEVA_BOTDVS(pSrc, pDst)		{																						\
												*pDst		= ZWC;																	\
												*(pDst+1)	= ZWC;																	\
												*(pDst+2)	= ZWC;																	\
												*(pDst+3)	= BOTSIGNTbl[*(pSrc) - 0x0919][*(pSrc+3) - 0x0941];						\
											}
#define	IS_DEVA_ADDBOTSIGN(pC)				(((*pC == 0x095C) || (*pC == 0x095D)) && DEVA_VIRAMA(*(pC+1)) && DEVA_RA(*(pC+2))		\
											&& DEVA_BOTTOMVOWEL(*(pC+3)))
#define	Change_DEVA_ADDBOTSIGN(pSrc, pDst)	{																						\
												*pDst		= ZWC;																	\
												*(pDst+1)	= ZWC;																	\
												*(pDst+2)	= ZWC;																	\
												*(pDst+3)	= ADDBOTSIGNTbl[*(pSrc) - 0x095C][*(pSrc+3) - 0x0941];					\
											}
#define	IS_DEVA_NUKBOTSIGN(pC)				(((*pC == 0x0919) || (*pC == 0x091B) || (*pC == 0x091F) || (*pC == 0x0920) ||			\
											(*pC == 0x0921) || (*pC == 0x0930) ||(*pC == 0x0933)) && (*(pC+1) == 0x093C) &&			\
											DEVA_VIRAMA(*(pC+2)) && DEVA_RA(*(pC+3)) && DEVA_BOTTOMVOWEL(*(pC+4)))
#define	Change_DEVA_NUKBOTSIGN(pSrc, pDst)	{																						\
												*pDst		= ZWC;																	\
												*(pDst+1)	= ZWC;																	\
												*(pDst+2)	= ZWC;																	\
												*(pDst+3)	= ZWC;																	\
												*(pDst+4)	= NUKBOTSIGNTbl[*(pSrc) - 0x0919][*(pSrc+4) - 0x0941];					\
											}
//=================================================================================================
//	DEVANAGARI CLUSTER MACRO : CLUSTER is Half form of Supress Vattu.
#define	IS_DEVA_CLUSTER(pC)					(((DEVA_CONSONANT(*pC) || DEVA_CONSONANT_WN(*pC)) && !DEVA_RA(*pC)) && DEVA_VIRAMA(*(pC+1)) && \
											DEVA_RA(*(pC+2)) && DEVA_VIRAMA(*(pC+3)) && DEVA_C(*(pC+4)))
#define	Change_DEVA_CLUSTER(pSrc, pDst)		{																						\
												*pDst		= ZWC;																	\
												*(pDst+1)	= ZWC;																	\
												*(pDst+2)	= ZWC;																	\
												*(pDst+3)	= ClusterFormTbl[*(pSrc) - 0x0915];										\
											}
#define	IS_DEVA_ADD_CLUSTER(pC)				(DEVA_ADDCONSONANT(*pC) && DEVA_VIRAMA(*(pC+1)) && DEVA_RA(*(pC+2)) &&					\
											DEVA_VIRAMA(*(pC+3)) && DEVA_C(*(pC+4)))
#define	Change_DEVA_ADD_CLUSTER(pSrc, pDst)	{																						\
												*pDst		= ZWC;																	\
												*(pDst+1)	= ZWC;																	\
												*(pDst+2)	= ZWC;																	\
												*(pDst+3)	= AClusterFormTbl[*(pSrc) - 0x0958];									\
											}
//=================================================================================================
//	DEVANAGARI CLUSTER WITH NUKTA MACRO
#define	IS_DEVA_CLUSTER_WN(pC)				(DEVA_CONSONANT(*pC) && DEVA_NUKTA(*(pC+1)) && DEVA_VIRAMA(*(pC+2)) && DEVA_RA(*(pC+3))	\
											&& DEVA_VIRAMA(*(pC+4)) && DEVA_C(*(pC+5)))
#define	Change_DEVA_CLUSTER_WN(pSrc, pDst)	{																						\
												*pDst		= ZWC;																	\
												*(pDst+1)	= ZWC;																	\
												*(pDst+2)	= ZWC;																	\
												*(pDst+3)	= ZWC;																	\
												*(pDst+4)	= CWNVHTbl[*(pSrc) - 0x0915];											\
											}
//=================================================================================================
// Conjuct_Half Macro
#define	IS_DEVA_CONJUCT_HALF(pC)			((((*pC == 0x0915) && DEVA_VIRAMA(*(pC+1)) && (*(pC+2) == 0x0937)) ||					\
											((*pC == 0x0916) && DEVA_VIRAMA(*(pC+1)) && (*(pC+2) == 0x0928)) ||						\
											((*pC == 0x091C) &&	DEVA_VIRAMA(*(pC+1)) && (*(pC+2) == 0x091E)) ||						\
											((*pC == 0x0924) && DEVA_VIRAMA(*(pC+1)) && ((*(pC+2) == 0x0924) || (*(pC+2) == 0x0928))) ||\
											((*pC == 0x0926) && DEVA_VIRAMA(*(pC+1)) && (*(pC+2) == 0x092E)) ||						\
											((*pC == 0x092A) && DEVA_VIRAMA(*(pC+1)) && (*(pC+2) == 0x0924)) ||						\
											((*pC == 0x0936) && DEVA_VIRAMA(*(pC+1)) && ((*(pC+2) == 0x091A) || (*(pC+2) == 0x0928) \
											|| (*(pC+2) == 0x0932) || (*(pC+2) == 0x0935))))										\
											&& DEVA_VIRAMA(*(pC+3)) && (DEVA_C(*(pC+4)) && (*(pC+4) != 0x0930)))
#define	Change_DEVA_CONJUCT_HALF(pSrc, pDst){																						\
												*pDst		= ZWC;																	\
												*(pDst+1)	= ZWC;																	\
												*(pDst+2)	= ZWC;																	\
												*(pDst+3)	= DEVA_CONJUCT_HALF_Tbl[*(pSrc) - 0x0915][*(pSrc+2) - 0x0915];			\
											}
//=================================================================================================
//	RA SUB WITH VIRAMA FORM MACRO
#define	IS_DEVA_RA_SUB_A(pC)				(((*pC == 0x0919) || (*pC == 0x091B) || ((*pC >= 0x091F) && (*pC <= 0x0922)) ||			\
											(*pC == 0x0931) || (*pC == 0x0933) || (*pC == 0x0934)) &&								\
											DEVA_VIRAMA(*(pC+1)) && DEVA_RA(*(pC+2)) && DEVA_VIRAMA(*(pC+3)))
#define	IS_DEVA_RA_SUB_B(pC)				(DEVA_RA(*pC) && DEVA_VIRAMA(*(pC+1)) && DEVA_RA(*(pC+2)) && DEVA_VIRAMA(*(pC+3)))
#define	Change_DEVA_RA_SUB(pSrc, pDst)		{																						\
												*pDst		= ZWC;																	\
												*(pDst+1)	= ZWC;																	\
												*(pDst+2)	= ZWC;																	\
												*(pDst+3)	= DEVA_RA_SUB_Tbl[*(pSrc) - 0x0919];									\
											}
#define	IS_DEVA_RA_SUB_C(pC)				(((*pC == 0x095C) || (*pC == 0x095D)) && DEVA_VIRAMA(*(pC+1)) && DEVA_RA(*(pC+2)) &&	\
											DEVA_VIRAMA(*(pC+3)))
#define	Change_DEVA_RA_SUB_ADD(pSrc, pDst)	{																						\
												*pDst		= ZWC;																	\
												*(pDst+1)	= ZWC;																	\
												*(pDst+2)	= ZWC;																	\
												*(pDst+3)	= (*(pSrc) == 0x095C ? 0xE158 : 0xE159);								\
											}

#define	IS_DEVA_RA_SUB_NUKTA(pC)			(((*pC == 0x0919) || (*pC == 0x091B) || ((*pC >= 0x091F) &&	(*pC <= 0x0922)) ||			\
											(*pC == 0x0930) || (*pC == 0x0933)) && DEVA_NUKTA(*(pC+1)) && DEVA_VIRAMA(*(pC+2))		\
											&& DEVA_RA(*(pC+3)) && DEVA_VIRAMA(*(pC+4)))
#define	Change_DEVA_RA_SUB_NUKTA(pSrc, pDst){																						\
												*pDst		= ZWC;																	\
												*(pDst+1)	= ZWC;																	\
												*(pDst+2)	= ZWC;																	\
												*(pDst+3)	= ZWC;																	\
												*(pDst+4)	= DEVA_RA_SUB_NUKTA_Tbl[*(pSrc) - 0x0919];								\
											}
#define	IS_DEVA_CJ_VATTU_VM(pC)				((*pC == 0x0937) && DEVA_VIRAMA(*(pC+1)) && ((*(pC+2) == 0x091F) || (*(pC+2) == 0x0920))\
											&& DEVA_VIRAMA(*(pC+3)) && DEVA_RA(*(pC+4)) && DEVA_VIRAMA(*(pC+5)))
#define	Change_DEVA_CJ_VATTU_VM(pSrc, pDst)	{																						\
												*pDst		= ZWC;																	\
												*(pDst+1)	= ZWC;																	\
												*(pDst+2)	= ZWC;																	\
												*(pDst+3)	= ZWC;																	\
												*(pDst+4)	= ZWC;																	\
												*(pDst+5)	= (*(pSrc+2) == 0x091F ? 0xE244 : 0xE245);								\
											}


//-------------------------------------------------------------------------------------------------
//	Member Function.
extern BOOL		ReorderEx_Hindi				(TReorderExAttr* Attr, T_NUM nBase, T_NUM nLen);
//-------------------------------------------------------------------------------------------------
#endif	//	_LGE_REORDEREX_HINDI_H_