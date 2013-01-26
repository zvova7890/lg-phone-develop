/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	TALUGU LANGUAGE REORDER FORM CODE TABLE

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

#ifndef		_LGE_REORDEREX_TALUGU_H_
#define		_LGE_REORDEREX_TALUGU_H_


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
extern A_CHAR	TELU_1st_Tbl[37];
extern A_CHAR	TELU_2nd_Tbl[37];
extern A_CHAR	TELU_3rd_Tbl[37];
extern A_CHAR	TELU_4th_Tbl[37];
extern A_CHAR	TELU_VIRAMA_Tbl[37];
extern A_CHAR	TELU_VOWEL_AA_Tbl[37];
extern A_CHAR	TELU_VOWEL_I_Tbl[37];
extern A_CHAR	TELU_VOWEL_II_Tbl[37];
extern A_CHAR	TELU_VOWEL_U_Tbl[37];
extern A_CHAR	TELU_VOWEL_UU_Tbl[37];
extern A_CHAR	TELU_VOWEL_E_Tbl[37];
extern A_CHAR	TELU_VOWEL_EE_Tbl[37];
extern A_CHAR	TELU_VOWEL_O_Tbl[37];
extern A_CHAR	TELU_VOWEL_OO_Tbl[37];
extern A_CHAR	TELU_VOWEL_AU_Tbl[37];
#endif


//-------------------------------------------------------------------------------------------------
//	Telugu Code Range
#define		TELU_CODE(C)						((0x0C00 <= C) && (0x0C6F >= C))



//=================================================================================================
//	Telugu Reordering And Rendering Rule by Sebastian
//=================================================================================================
#define TELU_CONSONANT(C)					((0x0C15 <= C) && (0x0C39 >= C))
#define TELU_SIGN(C)						((0x0C01 <= C) && (C <= 0x0C03))
#define TELU_DEPENDENTVOWEL(C)				((0x0C3E <= C) && (C <= 0x0C4C))
#define	TELU_LENGTHMARK(C)					((0x0C55 <= C) && (C <= 0x0C56))
#define TELU_VIRAMA(C)						(C == 0x0C4D)
#define	TELU_TWOPART(C)						(C == 0x0C48)
#define TELU_CONSONANT(C)					((0x0C15 <= C) && (0x0C39 >= C))
#define	TELU_POSTCONSONANT(C)				((C == 0x0C15) || (C == 0x0C1A) || (C == 0x0C1B) || ((0x0C28 <= C) && (C <= 0x0C2F)) || \
											((0x0C33 <= C) && (C <= 0x0C36)) || (C == 0x0C38))


#define	IS_TELU_1st(pC)						(TELU_CONSONANT(*pC) && TELU_VIRAMA(*(pC+1)) && TELU_CONSONANT(*(pC+2)))
#define	Change_TELU_1st(pSrc, pDst)			{																						\
												*(pDst+1)	= ZWC;																	\
												*(pDst+2)	= TELU_1st_Tbl[*(pSrc+2) - 0x0C15];										\
											}
//venketesh_TD6630_Issue_Fixed
#define TELU_SSA(C) 							(C == 0x0C37)
#define TELU_KA(C)                      		(C == 0x0C15)
#define	IS_TELU_KSHA(pC)						(TELU_KA(*(pC)) && TELU_VIRAMA(*(pC+1)) && TELU_SSA(*(pC+2))) 

#define	Change_TELU_Ksha(pSrc, pDst)			{																					\
													*(pDst)		= ZWC;																\
													*(pDst+1)	= ZWC;																\
													*(pDst+2)	= 0xEAFF;														\
												}
#define	IS_TELU_2nd(pC)						(TELU_CONSONANT(*pC) && TELU_VIRAMA(*(pC+1)) && TELU_CONSONANT(*(pC+2))					\
											&& TELU_VIRAMA(*(pC+3)) && TELU_CONSONANT(*(pC+4)))
#define	Change_TELU_2nd(pSrc, pDst)			{																						\
												*(pDst+1)	= ZWC;																	\
												*(pDst+2)	= TELU_2nd_Tbl[*(pSrc+2) - 0x0C15];										\
												*(pDst+3)	= ZWC;																	\
												*(pDst+4)	= TELU_3rd_Tbl[*(pSrc+4) - 0x0C15];										\
											}
#define	Change_TELU_4th(pSrc, pDst)			*(pDst)	= TELU_4th_Tbl[*(pSrc) - 0x0C15];
#define	Change_TELU_VIRAMA(pSrc, pDst)		*(pDst)	= TELU_VIRAMA_Tbl[*(pSrc) - 0x0C15];

#define	Change_TELU_VOWEL_AA(pSrc, pDst)	*(pDst)	= TELU_VOWEL_AA_Tbl[*(pSrc) - 0x0C15];
#define	Change_TELU_VOWEL_I(pSrc, pDst)		*(pDst)	= TELU_VOWEL_I_Tbl[*(pSrc) - 0x0C15];
#define	Change_TELU_VOWEL_II(pSrc, pDst)	*(pDst)	= TELU_VOWEL_II_Tbl[*(pSrc) - 0x0C15];
#define	Change_TELU_VOWEL_U(pSrc, pDst)		*(pDst)	= TELU_VOWEL_U_Tbl[*(pSrc) - 0x0C15];
#define	Change_TELU_VOWEL_UU(pSrc, pDst)	*(pDst)	= TELU_VOWEL_UU_Tbl[*(pSrc) - 0x0C15];
#define	Change_TELU_VOWEL_E(pSrc, pDst)		*(pDst)	= TELU_VOWEL_E_Tbl[*(pSrc) - 0x0C15];
#define	Change_TELU_VOWEL_EE(pSrc, pDst)	*(pDst)	= TELU_VOWEL_EE_Tbl[*(pSrc) - 0x0C15];
#define	Change_TELU_VOWEL_O(pSrc, pDst)		*(pDst)	= TELU_VOWEL_O_Tbl[*(pSrc) - 0x0C15];
#define	Change_TELU_VOWEL_OO(pSrc, pDst)	*(pDst)	= TELU_VOWEL_OO_Tbl[*(pSrc) - 0x0C15];
#define	Change_TELU_VOWEL_AU(pSrc, pDst)	*(pDst)	= TELU_VOWEL_AU_Tbl[*(pSrc) - 0x0C15];



//-------------------------------------------------------------------------------------------------
//	Member Function.
extern BOOL		ReorderEx_Telugu			(TReorderExAttr* Attr, T_NUM nBase, T_NUM nLen);


#endif	//	_LGE_REORDEREX_TALUGU_H_
