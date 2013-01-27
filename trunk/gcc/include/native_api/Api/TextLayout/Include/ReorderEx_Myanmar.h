/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	MYANMAR LANGUAGE REORDER FORM CODE TABLE

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

#ifndef		_LGE_REORDEREX_MYANMAR_H_
#define		_LGE_REORDEREX_MYANMAR_H_


#include	"ReorderEx_Common.h"
#include	"..\..\BasicApiLib\Include\Include.h"



#ifndef	ReorderDllExport
#ifndef	BNS_EMULATOR
#define	ReorderDllExport	extern
#else
#define	ReorderDllExport	__declspec( dllexport )
#endif
#endif


#ifdef	BNS_MAIN_VERSION
extern A_CHAR	MyanmarLigatureTbl[4][4];
#endif

//-------------------------------------------------------------------------------------------------
//	Myanmar Point Code
#define		MYANMAR_CODE(C)						((0x1000 <= C) && (0x104F >= C))


//=================================================================================================
//	Myanmar Reordering And Rendering Rule by Sebastian
//=================================================================================================
#define MYANMAR_CONSONANT(C)				(((0x1000 <= C) && (C <= 0x1021)) || (C == 0x103F))
#define MYANMAR_CONSONANT_IV(C)				(((0x1000 <= C) && (C <= 0x1021)) || (C == 0x103F) || (C == 0x1025) || (C == 0x1027) || (C == 0x1029))
#define MYANMAR_MEDIAL(C)					((0x103B <= C) && (C <= 0x103E))
#define MYANMAR_VOWEL(C)					((0x1022 <= C) && (C <= 0x1032))
#define MYANMAR_TONE(C)						((0x1037 <= C) && (C <= 0x1038))
#define MYANMAR_COMBINING_MARK(C)			((0x1036 <= C) && (C <= 0x103A))
//#define MYANMAR_INDEPENDENTVOWEL(C)			((0x1023 <= C) && (C <= 0x102A))
#define MYANMAR_INDEPENDENTVOWEL(C)			((0x1022 <= C) && (C <= 0x102A))

#define MYANMAR_PREFIXMEDIAL(C)				(C == 0x103C)
#define MYANMAR_PREFIXVOWEL(C)				(C == 0x1031)
#define MYANMAR_VIRAMA(C)					(C == 0x1039)
#define MYANMAR_STACK_CONSONANT(C)			((0x1000 <= C) && (C <= 0x1021) && (C != 0x1009) && (C != 0x100B) && (C != 0x101A) && (C != 0x101D) && (C != 0x101F) && (C != 0x1020))
#define	MYANMAR_WIDE_CONSONANT(C)			((C == 0x1000) || (C == 0x1003) || (C == 0x1006) || (C >= 0x100A && C <= 0x1010 ) || (C == 0x1011) || (C == 0x1018) || (C == 0x101A) || (C == 0x101C) || (C == 0x101E) || (C == 0x101F) || (C == 0x1021) || (C == 0x103F))
#define	MYANMAR_NARROW_CONSONANT(C)			((C == 0x1001) || (C == 0x1002) || (C == 0x1004) || (C == 0x1005) || (C == 0x1007) || (C == 0x100E) || (C >= 0x1012 && C <= 0x1017) || (C == 0x1019) || (C == 0x101B) || (C == 0x101D))
#define MYANMAR_LONG_CONSONANT(C)			(((0x1008 <= C) && (C <= 0x100D)) || (C == 0x1020))

//-------------------------------------------------------------------------------------------------
//  1. Consonant Rendering
//	1.1. Consonant NYA Rendering
#define	IS_MYANMAR_C_NYA(pC)					((*(pC) == 0x1009) && ((*(pC+1) == 0x1039) || (*(pC+1) == 0x103A)))
#define	CHANGE_MYANMAR_C_NYA(pSrc, pDst)		{																							\
												*(pDst)		= 0xFF30;																		\
												}
//		Consonant NYA Rendering (Short tail)
#define	IS_MYANMAR_C_NYA_ST(pC)					((*(pC) == 0x1009) && ((*(pC+1) == 0x103B) || (*(pC+1) == 0x103C) || (*(pC+1) == 0x103D)))
#define	CHANGE_MYANMAR_C_NYA_ST(pSrc, pDst)		{																							\
												*(pDst)		= 0xFF31;																		\
												}

//	1.2.Consonant NNYA Rendering
#define	IS_MYANMAR_C_NNYA(pC)					(((*(pC) == 0x100A) && ((*(pC+1) == 0x1039) || (*(pC+1) == 0x103B) || (*(pC+1) == 0x103D) || (*(pC+1) == 0x103E) || (*(pC+1) == 0x102F) || (*(pC+1) == 0x1030))) || \
												((*(pC) == 0x100A) && (*(pC+1) == 0x102D) && (*(pC+2) == 0x102F)))
#define	CHANGE_MYANMAR_C_NNYA(pSrc, pDst)		{																							\
												*(pDst)		= 0xFF32;																		\
												}

//	1.3. Consonant NA Rendering
#define	IS_MYANMAR_C_NA(pC)						(((*(pC) == 0x1014) && ((MYANMAR_MEDIAL(*(pC+1)) || *(pC+1) == 0x1039) || (*(pC+1) == 0x102F) || (*(pC+1) == 0x1030))) || \
												((*(pC) == 0x1014) && (*(pC+1) == 0x102D) && (*(pC+2) == 0x102F)))
#define	CHANGE_MYANMAR_C_NA(pSrc, pDst)			{																							\
												*(pDst)		= 0xFF33;																		\
												}

//	1.4. Consonant RA Rendering
#define	IS_MYANMAR_C_RA(pC)						((*(pC) == 0x101B) && (*(pC+1) == 0x103E))
#define	CHANGE_MYANMAR_C_RA(pSrc, pDst)			{																							\
												*(pDst)		= 0xFF34;																		\
												}
//		Consonant RA Rendering (Short tail) 
#define	IS_MYANMAR_C_RA_ST(pC)					((*(pC) == 0x101B) && ((*(pC+1) == 0x1039) || (*(pC+1) == 0x102F) || (*(pC+1) == 0x1030) || (*(pC+1) == 0x103B) || (*(pC+1) == 0x103D)))  || \
												((*(pC) == 0x101B) && ( ((*(pC+1) == 0x102D) && (*(pC+2) == 0x102F)) ||	((*(pC+1) == 0x103E) && (*(pC+2) == 0x102F)) ||	((*(pC+1) == 0x103E) && (*(pC+2) == 0x1030))))	||	\
												((*(pC) == 0x101B) && (*(pC+1) == 0x103E) && (*(pC+2) == 0x1020) && (*(pC+3) == 0x102F))
#define	CHANGE_MYANMAR_C_RA_ST(pSrc, pDst)		{																							\
												*(pDst)		= 0xFF35;																		\
												}

//  1.5. Ligature
#define	IS_MYANMAR_LIGATURE(pC)					(*(pC+1) == 0x1039) && ((*(pC) == 0x100B && (*(pC+2) == 0x100B) || *(pC+2) == 0x100C) ||	\
																    (*(pC) == 0x100D && (*(pC+2) == 0x100D) || *(pC+2) == 0x100E) ||		\
																    (*(pC) == 0x100F && (*(pC+2) == 0x100B) || *(pC+2) == 0x100D) ||		\
																	(*(pC) == 0x1020 && *(pC+2) == 0x1020))

#define	CHANGE_MYANMAR_LIGATURE(pSrc, pDst)		{																							\
												*(pDst)		= ZWC;																			\
												*(pDst+1)	= ZWC;																			\
												*(pDst+2)	= (*pSrc == 0x1020) ? MyanmarLigatureTbl[3][3] : MyanmarLigatureTbl[(*(pSrc) - 0x100B) / 2][*(pSrc+2) - 0x100B]; \
												}

//-------------------------------------------------------------------------------------------------
//  2. Stack Consonant Rendering
// 0x1039(VIRAMA) + Consonant (With Dot Circle)
#define	IS_MYANMAR_STACK_C_DC(pC)				(MYANMAR_VIRAMA(*(pC)) && MYANMAR_STACK_CONSONANT(*(pC+1)))
#define	CHANGE_MYANMAR_SUB_FORM_DC(pSrc, pDst)	{																							\
												*(pDst)		= ZWC;																			\
												*(pDst+1)	= (*(pSrc+1) + 0xEF00);															\
												}

// Consonant + 0x1039(VIRAMA) + Consonant
#define	IS_MYANMAR_STACK_C(pC)					(MYANMAR_CONSONANT(*(pC)) && MYANMAR_VIRAMA(*(pC+1)) && MYANMAR_STACK_CONSONANT(*(pC+2)))
#define	CHANGE_MYANMAR_SUB_FORM(pSrc, pDst)		{																							\
												*(pDst+1)	= ZWC;																			\
												*(pDst+2)	= (*(pSrc+2) + 0xEF40);															\
												}

// Consonant + 0x1039(VIRAMA)
#define	IS_MYANMAR_C_VIRAMA(pC)					(MYANMAR_CONSONANT(*(pC)) && MYANMAR_VIRAMA(*(pC+1)))
#define	CHANGE_MYANMAR_C_VIRAMA(pSrc, pDst)		{																							\
												*(pDst+1)	= 0xFF65;																		\
												}
//-------------------------------------------------------------------------------------------------
//  3. Kinzi Rendering
//		Kinzi(1004 + 103A + 1039) => 0xFF2C (With Dot Circle)
#define	IS_MYANMAR_KINZI_DC(pC)					((*(pC) == 0x1004) && (*(pC+1) == 0x103A) && (*(pC+2) == 0x1039))
#define	CHANGE_MYANMAR_KINZI_DC(pSrc, pDst)		{																							\
												*(pDst)		= ZWC;																			\
												*(pDst+1)	= ZWC;																			\
												*(pDst+2)	= 0xFF2C;																		\
												}

//		Kinzi + Consonant =>  Consonant + 0xFF93
#define	IS_MYANMAR_KINZI(pC)					(IS_MYANMAR_KINZI_DC(pC) && MYANMAR_CONSONANT(*(pC+3)))
#define	CHANGE_MYANMAR_KINZI(pSrc, pDst)		{																							\
												*(pDst)		= ZWC;																			\
												*(pDst+1)	= *(pSrc+3);																	\
												*(pDst+2)	= 0xFF93;																		\
												*(pDst+3)	= ZWC;																			\
												}

//-------------------------------------------------------------------------------------------------
//  4. Medial Rendering
//	4.1. Consonant + Medial
#define	IS_MYANMAR_M(pC)						(MYANMAR_MEDIAL(*(pC)) && (*(pC) != 0x103C))
#define CHANGE_MYANMAR_M(pSrc, pDst)			{																							\
												*(pDst)		= (*(pSrc) + 0xEF40);															\
												}

//	4.2. 2 Character Combined Medial
#define	IS_MYANMAR_2M(pC)						(((*(pC) == 0x103B) && (*(pC+1) == 0x103D)) || ((*(pC) == 0x103B) && (*(pC+1) == 0x103E)) || ((*(pC) == 0x103D) && (*(pC+1) == 0x103E)))
#define	CHANGE_MYANMAR_2M(pSrc, pDst)			{																							\
												*(pDst)		= ZWC;																			\
												*(pDst+1)	= (*(pSrc) == 0x103D) ? 0xFF82 : ((*(pSrc+1) == 0x103D) ? 0xFF80 : 0xFF81 );	\
												}
//		 2 Character Combined Medial (With Dot Circle)
#define	CHANGE_MYANMAR_2M_DC(pSrc, pDst)		{																							\
												*(pDst)		= ZWC;																			\
												*(pDst+1)	= (*(pSrc) == 0x103D) ? 0xFF24 : ((*(pSrc+1) == 0x103D) ? 0xFF22 : 0xFF23 );	\
												}

//	4.3. 3 Character Combined Medial
#define	IS_MYANMAR_3M(pC)						((*(pC) == 0x103B) && (*(pC+1) == 0x103D) && (*(pC+2) == 0x103E))	
#define	CHANGE_MYANMAR_3M(pSrc, pDst)			{																							\
												*(pDst)		= ZWC;																			\
												*(pDst+1)	= ZWC;																			\
												*(pDst+2)	= 0xFF83;																		\
												}
//		 3 Character Combined Medial (With Dot Circle)
#define	CHANGE_MYANMAR_3M_DC(pSrc, pDst)		{																							\
												*(pDst)		= ZWC;																			\
												*(pDst+1)	= ZWC;																			\
												*(pDst+2)	= 0xFF25;																		\
												}

//	4.4. Medial RA Rendering 
//		4.4.1 Medial RA
//			Narrow Consonant + Medial RA
#define	IS_MYANMAR_M_RA(pC)						((*(pC) == 0x103C))
#define	CHANGE_MYANMAR_M_RA_NC(pSrc, pDst)		{																							\
												*(pDst)	= 0xFF84;																			\
												}
//			Wide Consonant + Medial RA
#define	CHANGE_MYANMAR_M_RA_WC(pSrc, pDst)		{																							\
												*(pDst)	= 0xFF85;																			\
												}

//		4.4.2 Medial RA (+ Vowel 0x102D/ 0x102E/ 0x1032)
//			Narrow Consonant + Medial RA (+ Vowel)
#define	IS_MYANMAR_M_RA_V(pC)					((*(pC) == 0x103C) && ((*(pC+1) == 0x102D) || (*(pC+1) == 0x102E) || (*(pC+1) == 0x1032)))
#define	CHANGE_MYANMAR_M_RA_NC_V(pSrc, pDst)	{																							\
												*(pDst)		= 0xFF88;																		\
												}
//			Wide Consonant + Medial RA (+ Vowel)
#define	CHANGE_MYANMAR_M_RA_WC_V(pSrc, pDst)	{																							\
												*(pDst)		= 0xFF89;																		\
												}

//			Medial RA (+ Vowel) (With Dot Circle)
#define	CHANGE_MYANMAR_M_RA_V_DC(pSrc, pDst)	{																							\
												*(pDst)		= 0xFF27;																		\
												}

//		4.4.3 2 Characters Combined Medial RA
//			Narrow Consonant + Medial RA + Medial
#define	IS_MYANMAR_M_RA_2M(pC)					((*(pC) == 0x103C) && ((*(pC+1) == 0x103D) || (*(pC+1) == 0x103E)))
#define	CHANGE_MYANMAR_M_RA_NC_2M(pSrc, pDst)	{																							\
												*(pDst)		= (*(pSrc+1) == 0x103D) ? 0xFF86 : 0xFF9E;										\
												*(pDst+1)	= ZWC;																			\
												}
//			Wide Consonant + Medial RA + Medial
#define	CHANGE_MYANMAR_M_RA_WC_2M(pSrc, pDst)	{																							\
												*(pDst)		= (*(pSrc+1) == 0x103D) ? 0xFF87 : 0xFF9F;										\
												*(pDst+1)	= ZWC;																			\
												}

//			Medial RA + Medial (With Dot Circle)
#define	CHANGE_MYANMAR_M_RA_2M_DC(pSrc, pDst)	{																							\
												*(pDst)		= (*pSrc == 0x103D) ? 0xFF26 : 0xFF2F;											\
												*(pDst+1)	= ZWC;																			\
												}

//		4.4.4 2 Characters Combined Medial RA (+ Vowel 0x102D/ 0x102E/ 0x1032)
//			Narrow Consonant + Medial RA + Medial (+ Vowel)
#define	IS_MYANMAR_M_RA_2MV(pC)					((*(pC) == 0x103C) && (*(pC+1) == 0x103D) && ((*(pC+2) == 0x102D) || (*(pC+2) == 0x102E) || (*(pC+2) == 0x1032)))
#define	CHANGE_MYANMAR_M_RA_NC_2MV(pSrc, pDst)	{																							\
												*(pDst)		= 0xFF8C;																		\
												*(pDst+1)	= ZWC;																			\
												}
//			Wide Consonant + Medial RA + Medial (+ Vowel)
#define	CHANGE_MYANMAR_M_RA_WC_2MV(pSrc, pDst)	{																							\
												*(pDst)		= 0xFF8D;																		\
												*(pDst+1)	= ZWC;																			\
												}
//			Medial RA + Medial (+ Vowel) (with Dot Circle)
#define	CHANGE_MYANMAR_M_RA_2MV_DC(pSrc, pDst)	{																							\
												*(pDst)		= 0xFF29;																		\
												*(pDst+1)	= ZWC;																			\
												}

//		4.4.5 3 Characters Combined Medial RA
//			Narrow Consonant + Medial RA + Medial + Medial
#define	IS_MYANMAR_M_RA_3M(pC)					((*(pC) == 0x103C) && (*(pC+1) == 0x103D) && (*(pC+2) == 0x103E))
#define	CHANGE_MYANMAR_M_RA_NC_3M(pSrc, pDst)	{																							\
												*(pDst)		= 0xFF8A;																		\
												*(pDst+1)	= ZWC;																			\
												*(pDst+2)	= ZWC;																			\
												}
//			Wide Consonant + Medial RA + Medial + Medial
#define	CHANGE_MYANMAR_M_RA_WC_3M(pSrc, pDst)	{																							\
												*(pDst)		= 0xFF8B;																		\
												*(pDst+1)	= ZWC;																			\
												*(pDst+2)	= ZWC;																			\
												}
//			Medial RA + Medial + Medial (with Dot Circle)
#define	CHANGE_MYANMAR_M_RA_3M_DC(pSrc, pDst)	{																							\
												*(pDst)		= 0xFF28;																		\
												*(pDst+1)	= ZWC;																			\
												*(pDst+2)	= ZWC;																			\
												}

//		4.4.6 3 Characters Combined Medial RA (+ Vowel 0x102D/ 0x102E/ 0x1032)
//			Narrow Consonant + Medial RA + Medial (+ Vowel)
#define	IS_MYANMAR_M_RA_3MV(pC)					((*(pC) == 0x103C) && (*(pC+1) == 0x103D) && (*(pC+2) == 0x103E) && ((*(pC+3) == 0x102D) || (*(pC+3) == 0x102E) || (*(pC+3) == 0x1032)))
#define	CHANGE_MYANMAR_M_RA_NC_3MV(pSrc, pDst)	{																							\
												*(pDst)		= 0xFF90;																		\
												*(pDst+1)	= ZWC;																			\
												*(pDst+2)	= ZWC;																			\
												}
//			Wide Consonant + Medial RA + Medial + Medial (+ Vowel)
#define	CHANGE_MYANMAR_M_RA_WC_3MV(pSrc, pDst)	{																							\
												*(pDst)		= 0xFF91;																		\
												*(pDst+1)	= ZWC;																			\
												*(pDst+2)	= ZWC;																			\
												}
//			Medial RA + Medial + Medial (+ Vowel) (With Dot Circle)
#define	CHANGE_MYANMAR_M_RA_3MV_DC(pSrc, pDst)	{																							\
												*(pDst)		= 0xFF2A;																		\
												*(pDst+1)	= ZWC;																			\
												*(pDst+2)	= ZWC;																			\
												}


//-------------------------------------------------------------------------------------------------
//  5. Vowel Rendering
//	5.1. Vowel
#define	IS_MYANMAR_V(pC)						(MYANMAR_VOWEL(*(pC)))
#define CHANGE_MYANMAR_V(pSrc, pDst)			{																							\
												*(pDst)		= (*(pSrc) + 0xEF40);															\
												}
//	5.2. Vowel + Vowel
#define	IS_MYANMAR_2V(pC)						((*(pC) == 0x102D) && (*(pC+1) == 0x102F))
#define CHANGE_MYANMAR_2V(pSrc, pDst)			{																							\
												*(pDst)		= 0xFF6D;																		\
												*(pDst+1)	= 0xFF6F;																		\
												}
#define CHANGE_MYANMAR_2V_DC(pSrc, pDst)		{																							\
												*(pDst)		= 0x102D;																		\
												*(pDst+1)	= 0xFF6F;																		\
												}

//	5.3. Vowel AA (102B) Rendering
#define	IS_MYANMAR_V_AA(pC)						((*(pC) == 0x102B) && (*(pC+1) == 0x103A))
//		 Consonant (+ Medial) + 102B + 103A => FF92
#define CHANGE_MYANMAR_V_AA(pSrc, pDst)			{																							\
												*(pDst)		= ZWC;																			\
												*(pDst+1)	= 0xFF92;																		\
												}
//		 102B + 103A => FF2B  (with Dot Circle)
#define CHANGE_MYANMAR_V_AA_DC(pSrc, pDst)		{																							\
												*(pDst)		= ZWC;																			\
												*(pDst+1)	= 0xFF2B;																		\
												}

//	5.4. Vowel E (1031) Rendering
//		Vowel E
#define IS_MYANMAR_V_E(pC)						(*(pC) == 0x1031)
#define CHANGE_MYANMAR_V_E(pSrc, pDst)			{																							\
												*(pDst)		= 0xFF71;																		\
												}
#define CHANGE_MYANMAR_V_E_DC(pSrc, pDst)		{																							\
												*(pDst)		= 0x1031;																		\
												}
//		Vowel E + 102B/102C
#define IS_MYANMAR_V_E_2V(pC)					((*(pC) == 0x1031) && ((*(pC+1) == 0x102B) || (*(pC+1) == 0x102C)))
#define CHANGE_MYANMAR_V_E_2V(pSrc, pDst)		{																							\
												*(pDst)		= 0xFF71;																		\
												*(pDst+1)	= *(pSrc+1) + 0xEF40;															\
												}	
#define CHANGE_MYANMAR_V_E_2V_DC(pSrc, pDst)	{																							\
												*(pDst)		= 0x1031;																		\
												*(pDst+1)	= *(pSrc+1) + 0xEF40;															\
												}	
//		Vowel E + 102B/102C + 103A
#define IS_MYANMAR_V_E_3V(pC)					((*pC == 0x1031) && ((*(pC+1) == 0x102B) || (*(pC+1) == 0x102C)) && (*(pC+2) == 0x103A))
#define CHANGE_MYANMAR_V_E_3V(pSrc, pDst)		{																							\
												*(pDst)		= 0xFF71;																		\
												*(pDst+1)	= (*(pSrc+1) == 0x102B) ? ZWC : 0xFF6C;											\
												*(pDst+2)	= (*(pSrc+1) == 0x102B) ? 0xFF92 : 0xFF7A;										\
												}	
#define CHANGE_MYANMAR_V_E_3V_DC(pSrc, pDst)	{																							\
												*(pDst)		= 0x1031;																		\
												*(pDst+1)	= (*(pSrc+1) == 0x102B) ? ZWC : 0xFF6C;											\
												*(pDst+2)	= (*(pSrc+1) == 0x102B) ? 0xFF92 : 0xFF7A;										\
												}	

//	5.5. Vowel U/UU (102F/1030) Rendering
//		 LongCharacter + V(102D) + 102F/1030 => FF6D FF9A/FF9B
#define	IS_MYANMAR_2V_U(pC)					((*(pC) == 0x102D) && ((*(pC+1) == 0x102F) || (*(pC+1) == 0x1030)))
#define CHANGE_MYANMAR_2V_U(pSrc, pDst)		{																								\
												*(pDst)		= 0xFF6D;																		\
												*(pDst+1)	= (*(pSrc+1) == 0x102F) ? 0xFF9A : 0xFF9B;										\
												}
//		 V(102D) + 102F/1030 => 0x102D FF9A/FF9B (with Dot Circle)
#define CHANGE_MYANMAR_2V_U_DC(pSrc, pDst)		{																							\
												*(pDst)		= 0x102D;																		\
												*(pDst+1)	= (*(pSrc+1) == 0x102F) ? 0xFF9A : 0xFF9B;										\
												}
//		 LongCharacter + 102F/1030 => FF9A/FF9B
#define	IS_MYANMAR_V_U(pC)						((*(pC) == 0x102F) || (*(pC) == 0x1030))
#define CHANGE_MYANMAR_V_U(pSrc, pDst)			{																							\
												*(pDst)		= (*(pSrc) == 0x102F) ? 0xFF9A : 0xFF9B;										\
												}

//	5.6. Medial + Vowel Rendering
//		 Medial 103E + Vowel 102F Rendering
#define IS_MYANMAR_M_V(pC)						((*(pC) == 0x102F) && (*(pC-1) == 0x103E))
#define CHANGE_MYANMAR_M_V(pSrc, pDst)			{																							\
												*(pDst-1)	= ZWC;																			\
												*(pDst)		= 0xFF9C;																		\
												}	
#define CHANGE_MYANMAR_M_V_DC(pSrc, pDst)		{																							\
												*(pDst-1)	= ZWC;																			\
												*(pDst)		= 0xFF2E;																		\
												}	
//		 Medial 103E + Vowel 102D + 102F Rendering
#define IS_MYANMAR_M_2V(pC)						((*(pC) == 0x102D) && (*(pC+1) == 0x102F) && (*(pC-1) == 0x103E))
#define CHANGE_MYANMAR_M_2V(pSrc, pDst)			{																							\
												*(pDst-1)	= ZWC;																			\
												*(pDst)		= ZWC;																			\
												*(pDst+1)	= 0xFF9D;																		\
												}	
#define CHANGE_MYANMAR_M_2V_DC(pSrc, pDst)		{																							\
												*(pDst-1)	= ZWC	;																		\
												*(pDst)		= 0x102D;																		\
												*(pDst+1)	= 0xFF9C;																		\
												}	


//-------------------------------------------------------------------------------------------------
//	Member Function.
extern BOOL		ReorderEx_Myanmar				(TReorderExAttr* Attr, T_NUM nBase, T_NUM nLen);
//-------------------------------------------------------------------------------------------------
#endif	//	_LGE_REORDEREX_MYANMAR_H_
