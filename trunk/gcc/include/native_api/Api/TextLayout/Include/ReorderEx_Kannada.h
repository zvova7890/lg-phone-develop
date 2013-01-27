/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	KANNADA LANGUAGE REORDER FORM CODE TABLE

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

#ifndef		_LGE_REORDEREX_KANNADA_H_
#define		_LGE_REORDEREX_KANNADA_H_


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
extern A_CHAR	KNDA_1st_Tbl[37];
extern A_CHAR	KNDA_2nd_Tbl[37];
extern A_CHAR	KNDA_VIRAMA_Tbl[37];
extern A_CHAR	KNDA_VOWEL_AA_Tbl[37];
extern A_CHAR	KNDA_VOWEL_I_Tbl[37];
extern A_CHAR	KNDA_VOWEL_E_Tbl[37];
extern A_CHAR	KNDA_VOWEL_OO_Tbl[37];
extern A_CHAR	KNDA_VOWEL_AU_Tbl[37];
#endif



//-------------------------------------------------------------------------------------------------
//	Kannada Code Range
#define		KNDA_CODE(C)						((0x0C80 <= C) && (0x0CEF >= C))


//=================================================================================================
//	Kannada Reordering And Rendering Rule by Sebastian
//=================================================================================================
#define	KNDA_CONSONANT(C)					(((0x0C95 <= C) && (0x0CB9 >= C)) || (C == 0x0CDE))
#define	KNDA_RA(C)							(C == 0x0CB0)
#define KNDA_VIRAMA(C)						(C == 0x0CCD)
#define	KNDA_SIGN(C)						((0x0C82 <= C) && (C <= 0x0C83))
#define	KNDA_UNDERCONSONANT(C)				((C == 0x0CAA) || (C == 0x0CAB) || (C == 0x0CB5))

#define	IS_KNDA_REPH(pC)					(KNDA_RA(*pC) && KNDA_VIRAMA(*(pC+1)) && KNDA_CONSONANT(*(pC+2)))

//Venketesh_Kannada_CharacterBlinking_Issue__APR2011_[START]
#define KNDA_CONSONANT_KA(C)				(C == 0x0C95)
#define KNDA_CONSONANT_SSA(C)				(C == 0x0CB7)
#define IS_KNDA_KSHA(pC)  					(KNDA_CONSONANT_KA(*(pC)) && KNDA_VIRAMA(*(pC+1)) && KNDA_CONSONANT_SSA(*(pC+2)))
#define	Change_KNDA_KSHA(pSrc, pDst)		{																						\
												*(pDst)		=  ZWC;																	\
												*(pDst+1)	= ZWC;																	\
												*(pDst+2)	= 0xEC36;																\
											}	
//Venketesh_Kannada_CharacterBlinking_Issue__APR2011_[START]

#define	IS_KNDA_1st(pC)						(KNDA_CONSONANT(*pC) && KNDA_VIRAMA(*(pC+1)) && KNDA_CONSONANT(*(pC+2)))
#define	Change_KNDA_1st(pSrc, pDst)			{																						\
												*(pDst+1)	= ZWC;																	\
												*(pDst+2)	= (*(pSrc+2)) == 0x0CDE ? 0xEB33 : KNDA_1st_Tbl[*(pSrc+2) - 0x0C95];	\
											}
#define	IS_KNDA_2nd(pC)						(KNDA_CONSONANT(*pC) && KNDA_VIRAMA(*(pC+1)) && KNDA_CONSONANT(*(pC+2))				\
											&& KNDA_VIRAMA(*(pC+3)) && KNDA_CONSONANT(*(pC+4)))
#define	Change_KNDA_2nd(pSrc, pDst)			{																						\
												*(pDst+1)	= ZWC;																	\
												*(pDst+2)	= (*(pSrc+2)) == 0x0CDE ? 0xEB33 : KNDA_1st_Tbl[*(pSrc+2) - 0x0C95];	\
												*(pDst+3)	= ZWC;																	\
												*(pDst+4)	= (*(pSrc+4)) == 0x0CDE ? 0xEB57 : KNDA_2nd_Tbl[*(pSrc+4) - 0x0C95];	\
											}
#define	Change_KNDA_4th(pSrc, pDst)			*(pDst)	= KNDA_2nd_Tbl[*(pSrc) - 0x0C95];
#define	Change_KNDA_VIRAMA(pSrc, pDst)		*(pDst)	= KNDA_VIRAMA_Tbl[*(pSrc) - 0x0C95];
#define	Change_KNDA_VOWEL_AA(pSrc, pDst)	*(pDst)	= KNDA_VOWEL_AA_Tbl[*(pSrc) - 0x0C95];
#define	Change_KNDA_VOWEL_I(pSrc, pDst)		*(pDst)	= KNDA_VOWEL_I_Tbl[*(pSrc) - 0x0C95];
#define	Change_KNDA_VOWEL_E(pSrc, pDst)		*(pDst)	= KNDA_VOWEL_E_Tbl[*(pSrc) - 0x0C95];
#define	Change_KNDA_VOWEL_OO(pSrc, pDst)	*(pDst)	= KNDA_VOWEL_OO_Tbl[*(pSrc) - 0x0C95];
#define	Change_KNDA_VOWEL_AU(pSrc, pDst)	*(pDst)	= KNDA_VOWEL_AU_Tbl[*(pSrc) - 0x0C95];

#if defined(LGSI_INDIAN_LANGUAGE_SUPPORT)
/*Animesh:Indian language rendering rules start*/
#define	IS_KNDA_CONST_VIRAMA_ZWJ(pC)			(KNDA_CONSONANT(*pC)  && KNDA_VIRAMA(*(pC+1)) && (*(pC+2) == ZWJ))
/*Animesh:Indian language rendering rules end*/
#endif


//-------------------------------------------------------------------------------------------------
//	Member Function.
extern BOOL		ReorderEx_Kannada			(TReorderExAttr* Attr, T_NUM nBase, T_NUM nLen);
//-------------------------------------------------------------------------------------------------
#endif	//	_LGE_REORDEREX_KANNADA_H_
