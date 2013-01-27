/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	TAMIL LANGUAGE REORDER FORM CODE TABLE

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

#ifndef		_LGE_REORDEREX_TAMIL_H_
#define		_LGE_REORDEREX_TAMIL_H_


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
extern A_CHAR	MEYLIGATURETbl[37];
extern A_CHAR	UKARATbl[33];
extern A_CHAR	UUKAARATbl[33];
extern A_CHAR	TAMLPRETbl[3];
extern A_CHAR	TAMLOOTbl[37];
extern A_CHAR	TAMLAUTbl[37];
#endif


//-------------------------------------------------------------------------------------------------
//	Tamil Code Range
#define		TAML_CODE(C)						((0x0B80 <= C) && (0x0BFF >= C))


//=================================================================================================
//	Tamil Reordering And Rendering Rule by Sebastian
//=================================================================================================
#define TAML_CONSONANT(C)					(((0x0B95 <= C) && (0x0BB5 >= C)) || ((0x0BB7 <= C) && (0x0BB9 >= C)))
#define TAML_CONSONANT_EX(C)				(((0x0B95 <= C) && (0x0B9B >= C)) || ((0x0B9D <= C) && (0x0BB5 >= C)))
#define TAML_SIGN(C)						(((0x0B82 <= C) && (C <= 0x0B83)) || (C == 0x0BD7))
#define TAML_DEPENDENTVOWEL(C)				((0x0BBE <= C) && (C <= 0x0BC8))
#define TAML_PREFIX(C)						((0x0BC6 <= C) && (C <= 0x0BC8))
#define TAML_VIRAMA(C)						(C == 0x0BCD)
#define TAML_RA(C)							(C == 0x0BB0)
#define TAML_SIGN_I(C)						(C == 0x0BBF)
#define TAML_SIGN_II(C)						(C == 0x0BC0)
#define TAML_SIGN_U(C)						(C == 0x0BC1)
#define TAML_SIGN_UU(C)						(C == 0x0BC2)
#define TAML_SIGN_O(C)						(C == 0x0BCA)
#define TAML_SIGN_OO(C)						(C == 0x0BCB)
#define TAML_SIGN_AU(C)						(C == 0x0BCC)

//-------------------------------------------------------------------------------------------------
//	1. Grantha Ligature = sri, ksha and ksh
#define	IS_TAML_SRI(pC)						((*pC == 0x0BB8) && TAML_VIRAMA(*(pC+1)) && TAML_RA(*(pC+2)) && (*(pC+3) == 0x0BC0))
#define	Change_Taml_Sri(pSrc, pDst)			{																						\
												*pDst		= ZWC;																	\
												*(pDst+1)	= ZWC;																	\
												*(pDst+2)	= ZWC;																	\
												*(pDst+3)	= 0xE448;																\
											}

#define	IS_TAML_KSHA(pC)					((*pC == 0x0B95) && TAML_VIRAMA(*(pC+1)) && (*(pC+2) == 0x0BB7))
#define	Change_Taml_Ksha(pSrc, pDst)		{																						\
												*pDst		= ZWC;																	\
												*(pDst+1)	= ZWC;																	\
												*(pDst+2)	= 0xE422;																\
											}
#define	IS_TAML_KSH(pC)						((*pC == 0x0B95) && TAML_VIRAMA(*(pC+1)) && (*(pC+2) == 0x0BB7) && TAML_VIRAMA(*(pC+3)))
#define	Change_Taml_Ksh(pSrc, pDst)			{																						\
												*pDst		= ZWC;																	\
												*(pDst+1)	= ZWC;																	\
												*(pDst+2)	= ZWC;																	\
												*(pDst+3)	= 0xE423;																\
											}
//-------------------------------------------------------------------------------------------------
//	2. Mey Ligature = Consonant + Virama
#define	IS_Mey_Ligature(pC)					(TAML_CONSONANT(*pC) && TAML_VIRAMA(*(pC+1)))
#define	Change_Mey_Ligature(pSrc, pDst)		{																						\
												*pDst		= ZWC;																	\
												*(pDst+1)	= MEYLIGATURETbl[*(pSrc) - 0x0B95];										\
											}
//-------------------------------------------------------------------------------------------------
//	3. Ukara Ligature = Consonant + Tamil vowel sign U(0x0BC1)
#define	IS_UKARA(pC)						(TAML_CONSONANT_EX(*pC) && TAML_SIGN_U(*(pC+1)))
#define	Change_Ukara(pSrc, pDst)			{																						\
												*pDst		= ZWC;																	\
												*(pDst+1)	= UKARATbl[*(pSrc) - 0x0B95];											\
											}
//-------------------------------------------------------------------------------------------------
//	4. Uukaara Ligature = Consonant + Tamil vowel sign UU(0x0BC2)
#define	IS_UUKAARA(pC)						(TAML_CONSONANT_EX(*pC) && TAML_SIGN_UU(*(pC+1)))
#define	Change_Uukaara(pSrc, pDst)			{																						\
												*pDst		= ZWC;																	\
												*(pDst+1)	= UUKAARATbl[*(pSrc) - 0x0B95];											\
											}
//-------------------------------------------------------------------------------------------------
//	5. di and dii
#define	IS_TAML_TTA(pC)						((*pC == 0x0B9F) && (TAML_SIGN_I(*(pC+1)) || TAML_SIGN_II(*(pC+1))))
#define	Change_Taml_TTA(pSrc, pDst)			{																						\
												*pDst		= ZWC;																	\
												*(pDst+1)	= (TAML_SIGN_I(*(pSrc+1)) ? 0xE449 : 0xE44A);							\
											}
//-------------------------------------------------------------------------------------------------
//	5. TAMIL RA RULE
#define	IS_TAML_RA(pC)						(TAML_RA(*pC) && (TAML_SIGN_I(*(pC+1)) || TAML_SIGN_II(*(pC+1))))
#define	Change_Taml_RA(pSrc, pDst)			{																						\
												*pDst		= ZWC;																	\
												*(pDst+1)	= (TAML_SIGN_I(*(pSrc+1)) ? 0xE44B : 0xE44C);							\
											}
//-------------------------------------------------------------------------------------------------
//	6. TAMIL PREFIX VOWEL
#define	IS_TAML_PREFIX(pC)					(TAML_CONSONANT(*pC) && TAML_PREFIX(*(pC+1)))
#define	Change_Taml_Pre(pSrc, pDst)			{																						\
												*pDst		= TAMLPRETbl[*(pSrc+1) - 0x0BC6];										\
												*(pDst+1)	= *(pSrc);																\
											}
//-------------------------------------------------------------------------------------------------
//	7.	TAMIL TWO-PART DEPENDENT VOWEL
//	7.1	Sign O and OO
#define	IS_TAML_OO(pC)						(TAML_CONSONANT(*pC) && (TAML_SIGN_O(*(pC+1)) || TAML_SIGN_OO(*(pC+1))))
#define	Change_Taml_OO(pSrc, pDst)			{																						\
												*pDst		= (TAML_SIGN_O(*(pSrc+1)) ? 0xE406 : 0xE407);							\
												*(pDst+1)	= TAMLOOTbl[*(pSrc) - 0x0B95];											\
											}
//	7.2	Sign AU
#define	IS_TAML_AU(pC)						(TAML_CONSONANT(*pC) && TAML_SIGN_AU(*(pC+1)))
#define	Change_Taml_AU(pSrc, pDst)			{																						\
												*pDst		= 0xE406;																\
												*(pDst+1)	= TAMLAUTbl[*(pSrc) - 0x0B95];											\
											}
//-------------------------------------------------------------------------------------------------
//	8. Ligature + Two-part dependent vowel
#define	IS_TAML_KSHA_OO(pC)					((*pC == 0x0B95) && TAML_VIRAMA(*(pC+1)) && (*(pC+2) == 0x0BB7) && (TAML_SIGN_O(*(pC+3))\
											|| TAML_SIGN_OO(*(pC+3))))
#define	Change_Taml_Ksha_OO(pSrc, pDst)		{																						\
												*pDst		= (TAML_SIGN_O(*(pSrc+3)) ? 0xE406 : 0xE407);							\
												*(pDst+1)	= ZWC;																	\
												*(pDst+2)	= ZWC;																	\
												*(pDst+3)	= 0xE479;																\
											}
#define	IS_TAML_KSHA_AU(pC)					((*pC == 0x0B95) && TAML_VIRAMA(*(pC+1)) && (*(pC+2) == 0x0BB7) && TAML_SIGN_AU(*(pC+3)))
#define	Change_Taml_Ksha_AU(pSrc, pDst)		{																						\
												*pDst		= 0xE406;																\
												*(pDst+1)	= ZWC;																	\
												*(pDst+2)	= ZWC;																	\
												*(pDst+3)	= 0xE47A;																\
											}

#if defined(LGSI_INDIAN_LANGUAGE_SUPPORT)
/*Animesh:Indian language rendering rules start*/
//-------------------------------------------------------------------------------------------------
//	9. KSHA + + Prefix dependent vowel(A, AA, AII)
#define	IS_TAML_KSHA_PREFIX(pC)					((*pC == 0x0B95) && TAML_VIRAMA(*(pC+1)) && (*(pC+2) == 0x0BB7) && TAML_PREFIX(*(pC+3)))
#define	Change_Taml_Ksha_PREFIX(pSrc, pDst)		{																						\
													*pDst		= TAMLPRETbl[*(pSrc+3) - 0x0BC6];									\
													*(pDst+1)	= ZWC;																	\
													*(pDst+2)	= ZWC;																	\
													*(pDst+3)	= 0xE422;																	\
												}
//-------------------------------------------------------------------------------------------------
//	10. (Pa or Va or Ya or Na) + II	//Animesh
#define	IS_TAML_PiViNiYi(pC)				((*pC == 0x0BAA ||*pC == 0x0BAF ||*pC == 0x0B99 ||*pC == 0x0BB5) && (*(pC+1) == 0x0BBF))
#define	Change_Taml_PiViNiYi(pSrc, pDst)	{ \
												*pDst = ZWC;  \
												*(pDst + 2) = ZWC; \
												*(pDst + 1) = ((*pSrc == 0X0BAA) ? 0X0E47B : ((*pSrc == 0x0BAF) ? 0X0E47C: ((*pSrc == 0x0B99) ? 0X0E47D:0X0E47E)));  \
											}
/*Animesh:Indian language rendering rules end*/
#endif

//-------------------------------------------------------------------------------------------------
//	Member Function.
extern BOOL		ReorderEx_Tamil				(TReorderExAttr* Attr, T_NUM nBase, T_NUM nLen);
//-------------------------------------------------------------------------------------------------
#endif	//	_LGE_REORDEREX_TAMIL_H_
