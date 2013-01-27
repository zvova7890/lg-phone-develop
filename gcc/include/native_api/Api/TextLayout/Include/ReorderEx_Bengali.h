/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	BENGALI LANGUAGE REORDER FORM CODE TABLE

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

#ifndef		_LGE_REORDEREX_BENGALI_H_
#define		_LGE_REORDEREX_BENGALI_H_


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
extern A_CHAR	BengDVSTbl[11];
extern A_CHAR	BengIWNTbl[16];
extern A_CHAR	BengCWNTbl[37];
extern A_CHAR	BengCHALFTbl[37];
extern A_CHAR	BengACHALFTbl[4];
extern A_CHAR	BENGALILIGATURETbl[37][37];
extern A_CHAR	BENGCONJUNCTTbl[36][21];
extern A_CHAR	BENGBELOWCONJUNCTTbl[36][30];
extern A_CHAR	BENGRACONJUNCTTbl[37][37];
extern A_CHAR	BENGTWOPARTTbl[37];
extern A_CHAR	BENGVATTUTbl[37];
extern A_CHAR	BENGULIGATURETbl[35][9];
extern A_CHAR	BENGUULIGATURETbl[35][9];
extern A_CHAR	BENG_U_RA_Tbl[17];
extern A_CHAR	BENG_U_LA_Tbl[11];
extern A_CHAR	BENG_UU_RA_Tbl[17];
extern A_CHAR	BENG_UU_LA_Tbl[11];
#endif


//-------------------------------------------------------------------------------------------------
//	Bengali Code Range
#define		BENG_CODE(C)						((0x0980 <= C) && (0x09FF >= C))


//=================================================================================================
//	Bengali Reordering And Rendering Rule by Sebastian
//=================================================================================================
#define BENG_CONSONANT(C)					((0x0995 <= C) && (0x09B9 >= C))
#define	BENG_ADDCONSONANT(C)				((0x09DC <= C) && (0x09DF >= C))
#define	ASSA_CONSONANT(C)					(C == 0x09F1)
#define BENG_INDEPENDENTVOWEL(C)			((0x0985 <= C) && (C <= 0x0994))
#define BENG_SIGN(C)						((0x0981 <= C) && (C <= 0x0983))
#define BENG_DEPENDENTVOWEL(C)				((0x09BE <= C) && (C <= 0x09C8))
#define BENG_PREFIX(C)						((C == 0x09BF) || (C == 0x09C7) || (C == 0x09C8))
#define	BENG_TWOPART(C)						((C == 0x09CB) || (C == 0x09CC))
#define	BENG_I(C)							(C == 0x09BF)
#define	BENG_E(C)							(C == 0x09C7)
#define	BENG_AI(C)							(C == 0x09C8)
#define BENG_VIRAMA(C)						(C == 0x09CD)
#define BENG_NUKTA(C)						(C == 0x09BC)
#define	BENG_KA(C)							(C == 0x0995)
#define	BENG_HA(C)							(C == 0x09B9)
#define BENG_RA(C)							(C == 0x09B0)
#define BENG_BA(C)							(C == 0x09AC)
#define BENG_YA(C)							(C == 0x09AF)
#define ASSA_RA(C)							(C == 0x09F0)
#define	BENG_GENERIC(C)						((0x09E2 <= C) && (C <= 0x09E3))
#define	BENG_BELOW_VOWEL(C)					((0x09C1 <= C) && (C <= 0x09C4))
#define	BENG_SIGN_U(C)						(C == 0x09C1)
#define	BENG_SIGN_UU(C)						(C == 0x09C2)
#define	BENG_ABOVE_SIGN(C)					(C == 0x0981)
#define	BENG_CONSO(C)						(((0x0995 <= C) && (0x09B9 >= C)) || ((0x09DC <= C) && (0x09DF >= C)) || (C == 0x09F0)	\
											|| (C == 0x09F1))
//-------------------------------------------------------------------------------------------------
//	Bengali Zero Width Characters
#define	Change_BENG_KA_U(pSrc, pDst)		{																						\
												*pDst		= ZWC;																	\
												*(pDst+1)	= 0xE615;																\
											}
#define	Change_BENG_KA_UU(pSrc, pDst)		{																						\
												*pDst		= ZWC;																	\
												*(pDst+1)	= 0xE633;																\
											}
#define	Change_BENG_HA_UU(pSrc, pDst)		{																						\
												*pDst		= ZWC;																	\
												*(pDst+1)	= 0xE634;																\
											}
//-------------------------------------------------------------------------------------------------
//	INDEPENDENT_WITH_NUKTA_FOR_BENGALI
#define	IS_BENG_IWN(pC)						(BENG_INDEPENDENTVOWEL(*pC) && BENG_NUKTA(*(pC+1)))
#define	Change_BENG_IWN(pSrc, pDst)			{																						\
												*pDst		= ZWC;																	\
												*(pDst+1)	= BengIWNTbl[*(pSrc) - 0x0985];											\
											}
//-------------------------------------------------------------------------------------------------
//	BENGALI_CONSONANT_WITH_NUKTA
#define	IS_BENG_CWN(pC)						(BENG_CONSONANT(*pC) && BENG_NUKTA(*(pC+1)))
#define	Change_BENG_CWN(pSrc, pDst)			{																						\
												*pDst		= ZWC;																	\
												*(pDst+1)	= BengCWNTbl[*(pSrc) - 0x0995];											\
											}
//-------------------------------------------------------------------------------------------------
//	ASSAMESE_CONSONANT_WITH_NUKTA
#define	IS_ASSA_CWN(pC)						(ASSA_CONSONANT(*pC) && BENG_NUKTA(*(pC+1)))
#define	Change_ASSA_CWN(pSrc, pDst)			{																						\
												*pDst		= ZWC;																	\
												*(pDst+1)	= (*(pSrc) == 0x09F0 ? 0xE4BE : 0xE4BF);								\
											}
//-------------------------------------------------------------------------------------------------
//	BENGALI TWO-PART DEPENDENT VOWEL MACRO
#define	IS_BENG_LIGATURE_TWOPART(pC)		((BENG_CONSONANT(*pC) || BENG_ADDCONSONANT(*pC) || ASSA_CONSONANT(*pC)) &&				\
											BENG_VIRAMA(*(pC+1)) && (BENG_CONSONANT(*(pC+2)) || BENG_ADDCONSONANT(*(pC+2)) ||		\
											ASSA_CONSONANT(*(pC+2))))

#define	IS_BENG_CONSONANT_TWOPART(pC)		(BENG_CONSONANT(*pC) && BENG_TWOPART(*(pC+1)))
#define	Change_BENG_CON_TWO(pSrc, pDst)		{																						\
												*pDst		= BENGTWOPARTTbl[*(pSrc) - 0x0995];										\
												*(pDst+1)	= (*(pSrc+1) == 0x09CB ? 0xE485 : 0xE48E);								\
											}
#define	IS_BENG_CON_NUKTA_TWOPART(pC)		(BENG_CONSONANT(*pC) && BENG_NUKTA(*(pC+1)) && BENG_TWOPART(*(pC+2)))
#define	Change_BENG_NUK_TWO(pSrc, pDst)		{																						\
												*pDst		= 0xE48C;																\
												*(pDst+1)	= BengCWNTbl[*(pSrc) - 0x0995];											\
												*(pDst+2)	= (*(pSrc+2) == 0x09CB ? 0xE485 : 0xE48E);								\
											}
//-------------------------------------------------------------------------------------------------
//	BENGALI POST CONSONANT FORM MACRO
#define	IS_BENG_POST(pC)					(BENG_CONSO(*pC) && BENG_VIRAMA(*(pC+1)) && BENG_YA(*(pC+2)))
#define	IS_BENG_ADD_NUKTA_POST(pC)			(BENG_CONSO(*pC) && BENG_VIRAMA(*(pC+2)) && BENG_YA(*(pC+3)))
//-------------------------------------------------------------------------------------------------
//	BENGALI BELOW CONSONANT FORM MACRO
#define	IS_BENG_BELOW(pC)					((BENG_CONSONANT(*pC) || BENG_ADDCONSONANT(*pC) || ASSA_CONSONANT(*pC)) &&				\
											BENG_VIRAMA(*(pC+1)) && BENG_BA(*(pC+2)))
#define	IS_BENG_ADD_NUKTA_BELOW(pC)			((BENG_CONSONANT(*pC) || ASSA_CONSONANT(*pC)) && BENG_NUKTA(*(pC+1)) &&					\
											BENG_VIRAMA(*(pC+2)) && BENG_BA(*(pC+3)))
//-------------------------------------------------------------------------------------------------
//	BENGALI VATTU CONSONANT FORM MACRO
#define	IS_BENG_VATTU(pC)					((BENG_CONSONANT(*pC) || BENG_ADDCONSONANT(*pC) || ASSA_CONSONANT(*pC)|| BENG_RA(*pC)||	\
											ASSA_RA(*pC)) && BENG_VIRAMA(*(pC+1)) && (BENG_RA(*(pC+2)) || ASSA_RA(*(pC+2))))
#define	IS_BENG_VAT_CO(pC)					(BENG_CONSONANT(*pC) && BENG_VIRAMA(*(pC+1)) && (BENG_RA(*(pC+2)) || ASSA_RA(*(pC+2))))
#define	IS_BENG_VAT_AD(pC)					(BENG_ADDCONSONANT(*pC) && BENG_VIRAMA(*(pC+1)) && (BENG_RA(*(pC+2)) || ASSA_RA(*(pC+2))))
#define	Change_BENG_ADVAT(pSrc, pDst)		{																						\
												*pDst		= ZWC;																	\
												*(pDst+1)	= ZWC;																	\
												*(pDst+2)	= (*(pSrc) == 0x09DC ? 0xE5DA : (*(pSrc) == 0x09DD ? 0xE5DB : 0xE5DC));	\
											}
#define	IS_BENG_VAT_AS(pC)					((*pC == 0x09F1) && BENG_VIRAMA(*(pC+1)) && (BENG_RA(*(pC+2)) || ASSA_RA(*(pC+2))))
#define	Change_BENG_ASVAT(pSrc, pDst)		{																						\
												*pDst		= ZWC;																	\
												*(pDst+1)	= ZWC;																	\
												*(pDst+2)	= 0xE5DD;																\
											}
#define	IS_BENG_ADD_NUKTA_VATTU(pC)			((BENG_CONSONANT(*pC) || BENG_ADDCONSONANT(*pC) || ASSA_CONSONANT(*pC)|| BENG_RA(*pC)|| \
											ASSA_RA(*pC)) && BENG_VIRAMA(*(pC+2)) && (BENG_RA(*(pC+3)) || ASSA_RA(*(pC+3))))
//-------------------------------------------------------------------------------------------------
//	Bengali Half Form
#if defined(LGSI_INDIAN_LANGUAGE_SUPPORT)
/*Animesh rendering rules start*/		
#define	IS_BENG_ZWJ_HALF(pC)				(BENG_CONSONANT(*pC) && BENG_VIRAMA(*(pC+1)) && (ZWJ == *(pC+2)) &&						\
											(BENG_CONSONANT(*(pC+3)) ||	BENG_ADDCONSONANT(*(pC+3)) || ASSA_CONSONANT(*(pC+3))))
#define	Change_BENG_ZWJ_HALF(pSrc, pDst)	{																						\
												*pDst		= ZWC;																	\
												*(pDst+1)	= ZWC;																	\
												*(pDst+2)	= BengCHALFTbl[*(pSrc) - 0x0995];										\
											}
#define	IS_BENG_ADD_ZWJ_HALF(pC)			(BENG_ADDCONSONANT(*pC) && BENG_VIRAMA(*(pC+1)) && (ZWJ == *(pC+2)) &&					\
											(BENG_CONSONANT(*(pC+3)) ||	BENG_ADDCONSONANT(*(pC+3)) || ASSA_CONSONANT(*(pC+3))))
#define	Change_BENG_ADD_ZWJ_HALF(pSrc, pDst){																						\
												*pDst		= ZWC;																	\
												*(pDst+1)	= ZWC;																	\
												*(pDst+2)	= BengACHALFTbl[*(pSrc) - 0x09DC];										\
											}
#define	IS_ASSA_ZWJ_HALF(pC)				(ASSA_CONSONANT(*pC) && BENG_VIRAMA(*(pC+1)) && (ZWJ == *(pC+2)) &&						\
											(BENG_CONSONANT(*(pC+3)) ||	BENG_ADDCONSONANT(*(pC+3)) || ASSA_CONSONANT(*(pC+3))))
#define	Change_ASSA_ZWJ_HALF(pSrc, pDst)	{																						\
												*pDst		= ZWC;																	\
												*(pDst+1)	= ZWC;																	\
												*(pDst+2)	= (*(pSrc) == 0x09F0 ? 0xE4E1 : 0xE4E2);								\
											}
#define	CHANGE_ASSAMESE_RU(pSrc,pDst){																				\
												*pDst		= ZWC;																	\
												*(pDst+1)	= ZWC;																	\
												*(pDst+2)	= ZWC;																	\
												*(pDst+3)	= ((*(pSrc) == 0x09C1)?0x0E622:0x0E641);						\
											}
#define	Change_ASSA_CON_TWO(pSrc, pDst){																						\
												*pDst		= (*pSrc == 0x09F0 ? 0x0E613 : 0x0E614);										\
												*(pDst+1)	= (*(pSrc+1) == 0x09CB ? 0xE485 : 0xE48E);								\
								    }
/*Animesh rendering rules end*/		
#endif
#define	IS_BENG_HALF(pC)					(BENG_CONSONANT(*pC) && BENG_VIRAMA(*(pC+1)) && (BENG_CONSONANT(*(pC+2)) ||				\
											BENG_ADDCONSONANT(*(pC+2)) || ASSA_CONSONANT(*(pC+2))))
#define	Change_BENG_HALF(pSrc, pDst)		{																						\
												*pDst		= ZWC;																	\
												*(pDst+1)	= BengCHALFTbl[*(pSrc) - 0x0995];										\
											}
#define	IS_BENG_ADD_HALF(pC)				(BENG_ADDCONSONANT(*pC) && BENG_VIRAMA(*(pC+1)) && (BENG_CONSONANT(*(pC+2)) ||			\
											BENG_ADDCONSONANT(*(pC+2)) || ASSA_CONSONANT(*(pC+2))))
#define	Change_BENG_ADD_HALF(pSrc, pDst)	{																						\
												*pDst		= ZWC;																	\
												*(pDst+1)	= BengACHALFTbl[*(pSrc) - 0x09DC];										\
											}
#define	IS_ASSA_HALF(pC)					(ASSA_CONSONANT(*pC) && BENG_VIRAMA(*(pC+1)) && (BENG_CONSONANT(*(pC+2)) ||				\
											BENG_ADDCONSONANT(*(pC+2)) || ASSA_CONSONANT(*(pC+2))))
#define	Change_ASSA_HALF(pSrc, pDst)		{																						\
												*pDst		= ZWC;																	\
												*(pDst+1)	= (*(pSrc) == 0x09F0 ? 0xE4E1 : 0xE4E2);								\
											}
//-------------------------------------------------------------------------------------------------
//	Bengali Ligature
#define	IS_BENG_LIGATURE(pC)				(BENG_CONSONANT(*pC) && BENG_VIRAMA(*(pC+1)) && BENG_CONSONANT(*(pC+2)))
#define	Change_BENG_LIGATURE(pSrc, pDst)	{																						\
												*pDst		= ZWC;																	\
												*(pDst+1)	= ZWC;																	\
												*(pDst+2)	= BENGALILIGATURETbl[*(pSrc) - 0x0995][*(pSrc+2) - 0x0995];				\
											}
#define	Change_BENG_VATTU(pSrc, pDst)		{																						\
												*pDst		= ZWC;																	\
												*(pDst+1)	= ZWC;																	\
												*(pDst+2)	= BENGVATTUTbl[*(pSrc) - 0x0995];										\
											}
#define	Change_BENG_CONHALF(pSrc, pDst)		{																						\
												*pDst		= ZWC;																	\
												*(pDst+1)	= BengCHALFTbl[*(pSrc) - 0x0995];										\
												*(pDst+2)	= *(pSrc+2);															\
											}
#define	IS_BENG_BELOW_LIGATURE(pC)			(BENG_CONSONANT(*pC) && BENG_VIRAMA(*(pC+1)) && BENG_BA(*(pC+2)))
#define	IS_BENG_RA_LIGATURE(pC)				(BENG_CONSONANT(*pC) && BENG_VIRAMA(*(pC+1)) && (BENG_RA(*(pC+2)) || ASSA_RA(*(pC+2))))

//-------------------------------------------------------------------------------------------------
//	Bengali Conjuncts Form
#define	IS_BENG_CONJUNCT(pC)				(((*pC == 0x0995) && BENG_VIRAMA(*(pC+1)) && (*(pC+2) == 0x09B7) && BENG_VIRAMA(*(pC+3))\
											&& ((*(pC+4) == 0x09A3) || (*(pC+4) == 0x09AE))) ||	((*pC == 0x0999) &&					\
											BENG_VIRAMA(*(pC+1)) && (*(pC+2) == 0x0995) && BENG_VIRAMA(*(pC+3)) &&					\
											(*(pC+4) == 0x09B7)) || ((*pC == 0x09AE) && BENG_VIRAMA(*(pC+1)) && (*(pC+2) == 0x09AA) \
											&& BENG_VIRAMA(*(pC+3)) && (*(pC+4) == 0x09B2)) || ((*pC == 0x09B8) &&					\
											BENG_VIRAMA(*(pC+1)) && (*(pC+2) == 0x09AA) && BENG_VIRAMA(*(pC+3)) && (*(pC+4) == 0x09B2)))
#define	Change_BENG_CONJUNCT(pSrc, pDst)	{																						\
												*pDst		= ZWC;																	\
												*(pDst+1)	= ZWC;																	\
												*(pDst+2)	= ZWC;																	\
												*(pDst+3)	= ZWC;																	\
												*(pDst+4)	= BENGCONJUNCTTbl[*(pSrc) - 0x0995][*(pSrc+4) - 0x09A3];				\
											}
#define	IS_BENG_BELOW_CONJUNCT(pC)			((((*pC == 0x0995) && BENG_VIRAMA(*(pC+1)) && ((*(pC+2) == 0x09A4) ||					\
											(*(pC+2) == 0x09B7)) && BENG_VIRAMA(*(pC+3))) || ((*pC == 0x0997) &&					\
											BENG_VIRAMA(*(pC+1)) && (*(pC+2) == 0x09A7) && BENG_VIRAMA(*(pC+3))) ||	((*pC == 0x099A)\
											&& BENG_VIRAMA(*(pC+1)) && (*(pC+2) == 0x099B) && BENG_VIRAMA(*(pC+3))) ||				\
											((*pC == 0x099C) && BENG_VIRAMA(*(pC+1)) && (*(pC+2) == 0x099C) && BENG_VIRAMA(*(pC+3)))\
											|| ((*pC == 0x099E) && BENG_VIRAMA(*(pC+1)) && (*(pC+2) == 0x099A) &&					\
											BENG_VIRAMA(*(pC+3))) || ((*pC == 0x09A4) && BENG_VIRAMA(*(pC+1)) && (*(pC+2) == 0x09A4)\
											&& BENG_VIRAMA(*(pC+3))) ||	((*pC == 0x09A6) && BENG_VIRAMA(*(pC+1)) &&					\
											((*(pC+2) == 0x09A6) || (*(pC+2) == 0x09A7)) &&	BENG_VIRAMA(*(pC+3))) ||				\
											((*pC == 0x09A8) && BENG_VIRAMA(*(pC+1)) && ((*(pC+2) == 0x09A4) || (*(pC+2) == 0x09A6) \
											|| (*(pC+2) == 0x09A7)) && BENG_VIRAMA(*(pC+3))) ||	((*pC == 0x09B8) &&					\
											BENG_VIRAMA(*(pC+1)) && (*(pC+2) == 0x09A4) && BENG_VIRAMA(*(pC+3)))) && BENG_BA(*(pC+4)))
#define	Change_BENG_BELOW_CON(pSrc, pDst)	{																						\
												*pDst		= ZWC;																	\
												*(pDst+1)	= ZWC;																	\
												*(pDst+2)	= ZWC;																	\
												*(pDst+3)	= ZWC;																	\
												*(pDst+4)	= BENGBELOWCONJUNCTTbl[*(pSrc) - 0x0995][*(pSrc+2) - 0x099A];			\
											}
#define	IS_BENG_RA_CONJUNCT(pC)				((((*pC == 0x0995) && BENG_VIRAMA(*(pC+1)) && ((*(pC+2) == 0x099F) ||					\
											(*(pC+2) == 0x09A4) || (*(pC+2) == 0x09B7))) || ((*pC == 0x0999) && BENG_VIRAMA(*(pC+1))\
											&& ((*(pC+2) == 0x0995) || (*(pC+2) == 0x0998))) || ((*pC == 0x099A) &&					\
											BENG_VIRAMA(*(pC+1)) && (*(pC+2) == 0x099B)) ||	((*pC == 0x099F) && BENG_VIRAMA(*(pC+1))\
											&& (*(pC+2) == 0x099F)) || ((*pC == 0x09A3) && BENG_VIRAMA(*(pC+1)) &&					\
											((*(pC+2) == 0x099F) || (*(pC+2) == 0x09A0) || (*(pC+2) == 0x09A1))) || ((*pC == 0x09A6)\
											&& BENG_VIRAMA(*(pC+1)) && ((*(pC+2) == 0x09A6) || (*(pC+2) == 0x09AD))) ||				\
											(((*pC == 0x09A7) || (*pC == 0x09AC)) && BENG_VIRAMA(*(pC+1)) && (*(pC+2) == 0x09AC)) ||\
											((*pC == 0x09A8) && BENG_VIRAMA(*(pC+1)) && ((*(pC+2) == 0x099F) || (*(pC+2) == 0x09A1) \
											|| (*(pC+2) == 0x09A4) || (*(pC+2) == 0x09A6) || (*(pC+2) == 0x09A7))) ||				\
											((*pC == 0x09AA) && BENG_VIRAMA(*(pC+1)) && (*(pC+2) == 0x09A4)) ||	((*pC == 0x09AC) && \
											BENG_VIRAMA(*(pC+1)) && (*(pC+2) == 0x09A6)) ||	((*pC == 0x09AE) && BENG_VIRAMA(*(pC+1))\
											&& ((*(pC+2) == 0x09AA) || (*(pC+2) == 0x09AB) || (*(pC+2) == 0x09AD) ||				\
											(*(pC+2) == 0x09B8))) || ((*pC == 0x09B2) && BENG_VIRAMA(*(pC+1)) &&					\
											((*(pC+2) == 0x099F) || (*(pC+2) == 0x09A1) || (*(pC+2) == 0x09AB))) || ((*pC == 0x09B7)\
											&& BENG_VIRAMA(*(pC+1)) && ((*(pC+2) == 0x0995) || (*(pC+2) == 0x099F) ||				\
											(*(pC+2) == 0x09A0) || (*(pC+2) == 0x09AA) || (*(pC+2) == 0x09AB))) || ((*pC == 0x09B8) \
											&& BENG_VIRAMA(*(pC+1)) && ((*(pC+2) == 0x0995) || (*(pC+2) == 0x099F) ||				\
											(*(pC+2) == 0x09A4) || (*(pC+2) == 0x09AA) || (*(pC+2) == 0x09AB))))					\
											&& BENG_VIRAMA(*(pC+3)) && (BENG_RA(*(pC+4)) || ASSA_RA(*(pC+4))))
#define	Change_BENG_RA_CON(pSrc, pDst)		{																						\
												*pDst		= ZWC;																	\
												*(pDst+1)	= ZWC;																	\
												*(pDst+2)	= ZWC;																	\
												*(pDst+3)	= ZWC;																	\
												*(pDst+4)	= BENGRACONJUNCTTbl[*(pSrc) - 0x0995][*(pSrc+2) - 0x0995];				\
											}
//-------------------------------------------------------------------------------------------------
#define	IS_BENG_U_LIGATURE(pC)				((((*pC == 0x0996) || (*pC == 0x0997) || (*pC == 0x0998) || (*pC == 0x099C) ||			\
											(*pC == 0x09A4) || (*pC == 0x09A5) || (*pC == 0x09A6) || (*pC == 0x09A7) ||				\
											(*pC == 0x09AA) || (*pC == 0x09AC) || (*pC == 0x09AD) || (*pC == 0x09AE) ||				\
											(*pC == 0x09B6) || (*pC == 0x09B8)) && BENG_VIRAMA(*(pC+1)) && (BENG_RA(*(pC+2)) ||		\
											ASSA_RA(*(pC+2)))) || (((*pC == 0x0997) || (*pC == 0x09AA) || (*pC == 0x09AC) ||		\
											(*pC == 0x09B6) || (*pC == 0x09B8)) && BENG_VIRAMA(*(pC+1)) && ((*(pC+2) == 0x09B2) ||	\
											(*(pC+2) == 0x09AA))))
#define	Change_BENG_U_Li(pSrc, pDst)		{																						\
												*pDst		= ZWC;																	\
												*(pDst+1)	= ZWC;																	\
												*(pDst+2)	= ZWC;																	\
												*(pDst+3)	= BENGULIGATURETbl[*(pSrc) - 0x0996][*(pSrc+2) - 0x09AA];				\
											}
#define	Change_BENG_UU_Li(pSrc, pDst)		{																						\
												*pDst		= ZWC;																	\
												*(pDst+1)	= ZWC;																	\
												*(pDst+2)	= ZWC;																	\
												*(pDst+3)	= BENGUULIGATURETbl[*(pSrc) - 0x0996][*(pSrc+2) - 0x09AA];				\
											}
#define	IS_BENG_U_TA_LIGATURE(pC)			((*pC == 0x09A8) && BENG_VIRAMA(*(pC+1)) && (*(pC+2) == 0x09A4))
#define	Change_BENG_U_TA_Li(pSrc, pDst)		{																						\
												*pDst		= ZWC;																	\
												*(pDst+1)	= ZWC;																	\
												*(pDst+2)	= ZWC;																	\
												*(pDst+3)	= 0xE625;																\
											}
#define	IS_BENG_U_CONJUNCT_RA(pC)			(((((*pC == 0x09AC) || (*pC == 0x09A8)) && BENG_VIRAMA(*(pC+1)) && (*(pC+2) == 0x09A6)) \
											|| (((*pC == 0x09AE) || (*pC == 0x09B8)) && BENG_VIRAMA(*(pC+1)) && (*(pC+2) == 0x09AA)))\
											&& BENG_VIRAMA(*(pC+3)) && (BENG_RA(*(pC+4)) || ASSA_RA(*(pC+4))))
#define	Change_BENG_U_RA(pSrc, pDst)		{																						\
												*pDst		= ZWC;																	\
												*(pDst+1)	= ZWC;																	\
												*(pDst+2)	= ZWC;																	\
												*(pDst+3)	= ZWC;																	\
												*(pDst+4)	= ZWC;																	\
												*(pDst+5)	= BENG_U_RA_Tbl[*(pSrc) - 0x09A8];										\
											}
#define	Change_BENG_UU_RA(pSrc, pDst)		{																						\
												*pDst		= ZWC;																	\
												*(pDst+1)	= ZWC;																	\
												*(pDst+2)	= ZWC;																	\
												*(pDst+3)	= ZWC;																	\
												*(pDst+4)	= ZWC;																	\
												*(pDst+5)	= BENG_UU_RA_Tbl[*(pSrc) - 0x09A8];										\
											}

#define	IS_BENG_U_CONJUNCT_LA(pC)			(((*pC == 0x09AE) || (*pC == 0x09B7) || (*pC == 0x09B8)) && BENG_VIRAMA(*(pC+1)) &&		\
											(*(pC+2) == 0x09AA) && BENG_VIRAMA(*(pC+3)) && (*(pC+4) == 0x09B2))
#define	Change_BENG_U_LA(pSrc, pDst)		{																						\
												*pDst		= ZWC;																	\
												*(pDst+1)	= ZWC;																	\
												*(pDst+2)	= ZWC;																	\
												*(pDst+3)	= ZWC;																	\
												*(pDst+4)	= ZWC;																	\
												*(pDst+5)	= BENG_U_LA_Tbl[*(pSrc) - 0x09AE];										\
											}
#define	Change_BENG_UU_LA(pSrc, pDst)		{																						\
												*pDst		= ZWC;																	\
												*(pDst+1)	= ZWC;																	\
												*(pDst+2)	= ZWC;																	\
												*(pDst+3)	= ZWC;																	\
												*(pDst+4)	= ZWC;																	\
												*(pDst+5)	= BENG_UU_LA_Tbl[*(pSrc) - 0x09AE];										\
											}


//-------------------------------------------------------------------------------------------------
//	Member Function.
extern BOOL		ReorderEx_Bengali			(TReorderExAttr* Attr, T_NUM nBase, T_NUM nLen);
//-------------------------------------------------------------------------------------------------
#endif	//	_LGE_REORDEREX_BENGALI_H_
