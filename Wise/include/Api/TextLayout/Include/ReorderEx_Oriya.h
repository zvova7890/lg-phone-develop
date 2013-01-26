/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	ORIYA LANGUAGE REORDER FORM CODE TABLE

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

#ifndef		_LGE_REORDEREX_ORIYA_H_
#define		_LGE_REORDEREX_ORIYA_H_


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
extern A_CHAR	OriyaFullLgtTbl[37][37];
extern A_CHAR	OriyaLgtLowPartLeftTbl[37];
extern A_CHAR	OriyaLgtLowPartRightTbl[37];
extern A_CHAR	OriyaCtPostRATbl[41];

extern A_CHAR	OriyaBolowVowelUpTbl[3];
extern A_CHAR	OriyaBolowVowelMidTbl[3];
extern A_CHAR	OriyaBolowVowelDownTbl[3];

extern A_CHAR	OriyaPreVowelCtTbl[41];
extern A_CHAR	OriyaPreVowelFullLgtTbl[37][37];
extern A_CHAR	OriyaPreVowelCtPostRATbl[41];
#endif


//-------------------------------------------------------------------------------------------------
//	Oriya Code Range
#define		ORYA_CODE(C)						((0x0B00 <= C) && (0x0B71 >= C))


//=================================================================================================
//	Oriya Reordering And Rendering Rule by Hyunho.mo
//=================================================================================================

//-------------------------------------------------------------------------------------------------
//	Default Constants.
//-------------------------------------------------------------------------------------------------


//	Letter RA.
#define ORYA_LETTER_RA							0x0B30

#define ORYA_PRE_RA_LEFT						0xF093
#define ORYA_PRE_RA_MID							0xF094
#define ORYA_PRE_RA_RIGHT						0xF095

#define ORYA_POST_RA_RIGHTUP					0xEFD1
#define ORYA_POST_RA_RIGHTDOWN					0xEFD2
//#define ORYA_POST_RA_CENTERUP					0xEFD3
#define ORYA_POST_RA_CENTERDOWN					0xEFD4
#define ORYA_POST_RA_NOTKERNING					0xEFD5


#define ORYA_LETTER_NYA							0x0B1E
#define ORYA_LETTER_JA							0x0B1C

#define ORYA_LETTER_WA							0x0B71
#define	ORYA_LETTER_WA_POST_RA					0xF08C
#define	ORYA_LETTER_WA_PRE_VOWEL				0xF08D
#define	ORYA_LETTER_WA_POST_RA_PRE_VOWEL		0xF08E


#define ORYA_LETTER_YYA							0x0B5F
#define ORYA_LIGATURE_FULL_YA					0xEF30
#define ORYA_LIGATURE_FULL_YA_PRE_VOWEL			0xF036
#define ORYA_LIGATURE_POST_YA					0xEFA5

#define ORYA_VIRAMA								0x0B4D
#define ORYA_VIRAMA_UP							0xEFA8
#define ORYA_VIRAMA_DOWN						0xEFA9

#define ORYA_NUKTA								0x0B3C
#define	ORYA_NUKTA_CENTER						0xEFA6
#define	ORYA_NUKTA_LEFT							0xEFA7


#define ORYA_VOWEL_E							0x0B47

#define ORYA_VOWEL_AA							0x0B3E
#define ORYA_VOWEL_AA_NDC						0xEFD6

#define ORYA_VOWEL_II							0x0B40
#define ORYA_VOWEL_II_NDC						0xEFD7

#define	ORYA_VOWEL_E							0x0B47

//	Two-Part Dependent Vowel.
#define	ORYA_VOWEL_AI							0x0B48
#define	ORYA_VOWEL_O							0x0B4B
#define	ORYA_VOWEL_AU							0x0B4C

#define ORYA_SIGN_AI_NDC						0xF09A
#define ORYA_SIGN_AU_NDC						0xF09B


//	Above Dependent Vowel.
#define ORYA_VOWEL_I							0x0B3F
#define ORYA_VOWEL_I_NDC						0xF099

//	Post Sign.
#define	ORYA_SIGN_ANUSVARA						0x0B02
#define	ORYA_SIGN_ANUSVARA_NDC					0xF08F
#define	ORYA_SIGN_VISARGA						0x0B03
#define	ORYA_SIGN_VISARGA_NDC					0xF090

//	Above Sign.
#define ORYA_SIGN_CANDRABINDU					0x0B01
#define ORYA_SIGN_CANDRABINDU_NDC				0xF091
#define ORYA_SIGN_CANDRABINDU_RIGHT				0xF092



//	Vowel Ligature를 형성하는 Consonant.
#define	ORYA_LETTER_KHA							0x0B16
#define	ORYA_LETTER_THA							0x0B25
#define	ORYA_LETTER_DHA							0x0B27


#define	ORYA_LETTER_KHA_VOWEL_LIGATURE			0xF096
#define	ORYA_LETTER_THA_VOWEL_LIGATURE			0xF097
#define	ORYA_LETTER_DHA_VOWEL_LIGATURE			0xF098


//	Independent Vowels	
#define	ORYA_LETTER_AI							0x0B10
#define	ORYA_LETTER_AU							0x0B14



//-------------------------------------------------------------------------------------------------
//	Rules for Comparing
//-------------------------------------------------------------------------------------------------


#define IS_ORYA_LETTER_RA(pC)					(ORYA_LETTER_RA		== *(pC))

#define IS_ORYA_LETTER_NYA(pC)					(ORYA_LETTER_NYA	== *(pC))
#define IS_ORYA_LETTER_WA(pC)					(ORYA_LETTER_WA		== *(pC))
#define IS_ORYA_LETTER_YYA(pC)					(ORYA_LETTER_YYA	== *(pC))
#define IS_ORYA_LETTER_JA(pC)					(ORYA_LETTER_JA		== *(pC))
#define IS_ORYA_LETTER_KHA(pC)					(ORYA_LETTER_KHA	== *(pC))
#define IS_ORYA_LETTER_DHA(pC)					(ORYA_LETTER_DHA	== *(pC))
#define IS_ORYA_LETTER_THA(pC)					(ORYA_LETTER_THA	== *(pC))


#define IS_ORYA_NUKTA(pC)						(ORYA_NUKTA			== *(pC))
#define IS_ORYA_VIRAMA(pC)						(ORYA_VIRAMA		== *(pC))

#define	IS_ORYA_VOWEL_AA(pC)					(ORYA_VOWEL_AA		== *(pC))

#define	IS_ORYA_VOWEL_I(pC)						(ORYA_VOWEL_I		== *(pC))

#define	IS_ORYA_VOWEL_AI(pC)					(ORYA_VOWEL_AI		== *(pC))
#define	IS_ORYA_VOWEL_O(pC)						(ORYA_VOWEL_O		== *(pC))
#define	IS_ORYA_VOWEL_AU(pC)					(ORYA_VOWEL_AU		== *(pC))

#define IS_ORYA_SIGN_CANDRABINDU(pC)			(ORYA_SIGN_CANDRABINDU == *(pC))



#define IS_ORYA_INDEPENDENT_VOWEL(pC)			(((0x0B05 <= *(pC)) && (*(pC) <= 0x0B14)) || (*(pC) == 0x0B60) || (*(pC) == 0x0B61))
#define IS_ORYA_DEPENDENT_VOWEL(pC)				((0x0B3E <= *(pC)) && (*(pC) <= 0x0B4C))
#define IS_ORYA_PRE_DEPENDENT_VOWEL(pC)			(ORYA_VOWEL_E == *(pC))
#define IS_ORYA_ABOVE_DEPENDENT_VOWEL(pC)		(ORYA_VOWEL_I == *(pC))
#define	IS_ORYA_BELOW_DEPENDENT_VOWEL(pC)		((0x0B41 <= *(pC)) && (*(pC) <= 0x0B43))
#define IS_ORYA_POST_DEPENDENT_VOWEL(pC)		((0x0B3E == *(pC)) || (0x0B40 == *(pC)))
#define	IS_ORYA_TWOPART_DEPENDENT_VOWEL(pC)		(IS_ORYA_VOWEL_AI(pC) || IS_ORYA_VOWEL_O(pC) || IS_ORYA_VOWEL_AU(pC))

#define IS_ORYA_CONSONANT(pC)					((0x0B15 <= *(pC)) && (*(pC) <= 0x0B39))
#define	IS_ORYA_ADD_CONSONANT(pC)				((0x0B5C <= *(pC)) && (*(pC) <= 0x0B5F))
#define	IS_ORYA_SPEC_CONSONANT(pC)				(ORYA_LETTER_WA == *(pC))
#define IS_ORYA_ALL_CONSONANT(pC)				(IS_ORYA_CONSONANT(pC) || IS_ORYA_ADD_CONSONANT(pC) || IS_ORYA_SPEC_CONSONANT(pC))



#define	IS_ORYA_CONSONANT_NUKTA(pC) 			((0x0B5C == *(pC)) || (0x0B5D == *(pC)))
#define	IS_ORYA_FULL_LIGATURE(pC1, pC2)			(((0x0000 != OriyaFullLgtTbl[*(pC1)-0x0B15][*(pC2)-0x0B15]) || (IS_ORYA_LETTER_DHA(pC1) && IS_ORYA_LETTER_YYA(pC2)))	\
												&& IS_ORYA_VIRAMA (pC2-1))

												
#define	IS_ORYA_CONSONANT_POST_RA(pC)			(IS_ORYA_ALL_CONSONANT(pC) && IS_ORYA_VIRAMA(pC+1) && IS_ORYA_LETTER_RA(pC+2))

												
#define IS_ORYA_LAST_LIGATURE(SCnt, SLen, pC)	!(																																		\
													(((SCnt+4) < SLen)		&& IS_ORYA_ALL_CONSONANT(pC+2) && IS_ORYA_VIRAMA(pC+3) && IS_ORYA_ALL_CONSONANT(pC+4))						\
													|| (((SCnt+5) < SLen)	&& IS_ORYA_ALL_CONSONANT(pC+3) && IS_ORYA_VIRAMA(pC+4) && IS_ORYA_ALL_CONSONANT(pC+5))						\
													|| (((SCnt+5) < SLen)	&& IS_ORYA_CONSONANT(pC+2) && IS_ORYA_NUKTA(pC+3) && IS_ORYA_VIRAMA(pC+4) && IS_ORYA_ALL_CONSONANT(pC+5))	\
													|| (((SCnt+6) < SLen)	&& IS_ORYA_CONSONANT(pC+3) && IS_ORYA_NUKTA(pC+4) && IS_ORYA_VIRAMA(pC+5) && IS_ORYA_ALL_CONSONANT(pC+6))	\
												)


#define	IS_CONSONANT_SIGN_TA(pC1, pC2)			((*(pC1) == 0x0B24) && ((*(pC2) == 0x0B15) || (*(pC2) == 0x0B2A)))



#define	GET_ORYA_FULL_LIGATURE(pSrc1, pSrc2)	(OriyaFullLgtTbl[*(pSrc1)-0x0B15][*(pSrc2)-0x0B15])
#define	GET_ORYA_LOWPART_LEFT(pSrc)				(OriyaLgtLowPartLeftTbl[*(pSrc)-0x0B15])
#define	GET_ORYA_LOWPART_RIGHT(pSrc)			(OriyaLgtLowPartRightTbl[*(pSrc)-0x0B15])



//-------------------------------------------------------------------------------------------------
//	Rendering Rules for Changing.
//-------------------------------------------------------------------------------------------------



#define	IS_ORYA_IDV_ABOVE_SIGN(pC)								\
(																\
	((ORYA_LETTER_AI == *(pC)) || (ORYA_LETTER_AU == *(pC)))	\
	&& IS_ORYA_SIGN_CANDRABINDU (pC+1)							\
)
#define	CHANGE_ORYA_IDV_ABOVE_SIGN(pSrc, pDst)	\
{												\
	*(pDst+1)	= ORYA_SIGN_CANDRABINDU_RIGHT;	\
}


#define	CHANGE_ORYA_VIRAMA(bPreLgt, bPreFullLgt, pSrc, pDst)	\
{															\
	*(pDst)	= ((bPreLgt == FALSE) || (bPreFullLgt == TRUE)) ? ORYA_VIRAMA_UP : ORYA_VIRAMA_DOWN;	\
}



//	Two-Part Dependent Vowel's Rendering & Reordering.
#define CHANGE_ORYA_TWOPART_DV_FULL_LIGATURE(pStSrc, pStDst, pSrc, pDst)	\
{																						\
	CHANGE_ORYA_PRE_DV_FULL_LIGATURE(pStSrc, pStDst, pDst);				\
	CHANGE_ORYA_TWOPART_DV_POST_PART(pStSrc, pStDst, pSrc, pDst);			\
}
#define CHANGE_ORYA_TWOPART_DV_POST_RA(pStSrc, pStDst, pSrc, pDst)			\
{																						\
	CHANGE_ORYA_PRE_DV_POST_RA(pStSrc, pStDst, pDst);						\
	CHANGE_ORYA_TWOPART_DV_POST_PART(pStSrc, pStDst, pSrc, pDst);			\
}
#define CHANGE_ORYA_TWOPART_DV_CT(pStSrc, pStDst, pSrc, pDst)				\
{																						\
	CHANGE_ORYA_PRE_DV_CT(pStSrc, pStDst, pDst);							\
	CHANGE_ORYA_TWOPART_DV_POST_PART(pStSrc, pStDst, pSrc, pDst);			\
}
#define	CHANGE_ORYA_TWOPART_DV_POST_PART(pStSrc, pStDst, pSrc, pDst)		\
{																						\
	if (IS_ORYA_VOWEL_AI(pSrc)) {														\
		memmove(pStDst+2, pStDst+1, sizeof(BISYMB)*(pDst-pStDst-1));					\
		*(pStDst+1)	= ORYA_SIGN_AI_NDC;													\
	} else if (IS_ORYA_VOWEL_O(pSrc)) {													\
		*(pDst)		= ORYA_VOWEL_AA_NDC;												\
	} else if (IS_ORYA_VOWEL_AU(pSrc)) {												\
		*(pDst)		= ORYA_SIGN_AU_NDC;													\
	}																					\
}



//	Pre Dependent Vowel's Rendering & Reordering.
#define CHANGE_ORYA_PRE_DV_FULL_LIGATURE(pStSrc, pStDst, pDst)	\
{																			\
	if (IS_ORYA_LETTER_DHA(pStSrc)) {										\
		*(pStDst)	= ORYA_LIGATURE_FULL_YA_PRE_VOWEL;						\
	} else {																\
		*(pStDst)	= OriyaPreVowelFullLgtTbl[*(pStSrc)-0x0B15][*(pStSrc+2)-0x0B15];	\
	}																		\
	*(pDst)		= ZWC;														\
}
#define CHANGE_ORYA_PRE_DV_POST_RA(pStSrc, pStDst, pDst)	\
{																		\
	if (IS_ORYA_SPEC_CONSONANT(pStSrc))	{								\
		*(pStDst)	=  ORYA_LETTER_WA_POST_RA_PRE_VOWEL;				\
	} else if (IS_ORYA_CONSONANT(pStSrc)) {								\
		*(pStDst)	=  OriyaPreVowelCtPostRATbl[*(pStSrc)-0x0B15];		\
	} else {															\
		*(pStDst)	=  OriyaPreVowelCtPostRATbl[*(pStSrc)-0x0B37];		\
	}																	\
	*(pDst)		= ZWC;													\
}
#define CHANGE_ORYA_PRE_DV_CT(pStSrc, pStDst, pDst)	\
{																	\
	if (IS_ORYA_SPEC_CONSONANT(pStSrc))	{							\
		*(pStDst)	=  ORYA_LETTER_WA_PRE_VOWEL;					\
	} else if (IS_ORYA_CONSONANT(pStSrc)) {							\
		*(pStDst)	=  OriyaPreVowelCtTbl[*(pStSrc)-0x0B15];		\
	} else {														\
		*(pStDst)	=  OriyaPreVowelCtTbl[*(pStSrc)-0x0B37];		\
	}																\
	*(pDst)		= ZWC;												\
}


//	Post Dependent Vowel's Rendering.
#define	CHANGE_ORYA_POST_DV(pSrc, pDst)										\
{																				\
	*(pDst)	= (IS_ORYA_VOWEL_AA(pSrc)) ? ORYA_VOWEL_AA_NDC : ORYA_VOWEL_II_NDC;	\
}


//	Below Dependent Vowel's Rendering.
#define	CHANGE_ORYA_BELOW_DV_UP(pSrc, pDst)				\
{														\
	*(pDst) = OriyaBolowVowelUpTbl[*(pSrc)-0x0B41];		\
}
#define	CHANGE_ORYA_BELOW_DV_MID(pSrc, pDst)			\
{														\
	*(pDst) = OriyaBolowVowelMidTbl[*(pSrc)-0x0B41];	\
}
#define	CHANGE_ORYA_BELOW_DV_DOWN(pSrc, pDst)			\
{														\
	*(pDst) = OriyaBolowVowelDownTbl[*(pSrc)-0x0B41];	\
}


//	Above Dependent Vowel's Rendering
#define	CHANGE_ORYA_ABOVE_DV(pStSrc, pStDst, pSrc, pDst)			\
{																	\
	memmove(pStDst+2, pStDst+1, sizeof(BISYMB)*(pDst-pStDst-1));	\
	*(pStDst+1)	= ORYA_VOWEL_I_NDC;									\
}

//	Above Dependent Vowel's Rendering
#define	CHANGE_ORYA_ABOVE_DV_NUKTA(pStSrc, pStDst, pSrc, pDst)		\
{																	\
	memmove(pStDst+3, pStDst+1, sizeof(BISYMB)*(pDst-pStDst-1));	\
	*(pStDst+1)	= ORYA_VOWEL_I_NDC;									\
	*(pStDst+2)	= ORYA_NUKTA_LEFT;									\
}





//	Pre RA Conjunct : RA + VIRAMA + Ct + ...
#define	IS_ORYA_PRE_RA(pStSrc, pC)	\
(									\
	(pStSrc == pC)					\
	&& (IS_ORYA_LETTER_RA(pC) && IS_ORYA_VIRAMA(pC+1) && IS_ORYA_ALL_CONSONANT(pC+2))	\
)


//	Not Post RA :
#define	IS_ORYA_NOT_POST_RA(pC)		\
	(								\
		(IS_ORYA_ALL_CONSONANT(pC) && IS_ORYA_VIRAMA(pC+1) && IS_ORYA_LETTER_RA(pC+2) && IS_ORYA_NUKTA(pC+3))						\
		|| (IS_ORYA_CONSONANT(pC) && IS_ORYA_NUKTA(pC+1) && IS_ORYA_VIRAMA(pC+2) && IS_ORYA_LETTER_RA(pC+3) && IS_ORYA_NUKTA(pC+4))	\
	)
#define	CHANGE_ORYA_NOT_POST_RA(bPreLgt, bPreFullLgt, pSrc, pDst)												\
	{																											\
		if (IS_ORYA_NUKTA(pSrc+3)) {																			\
			*(pDst+1)	= ((bPreLgt == FALSE) || (bPreFullLgt == TRUE)) ? ORYA_VIRAMA_UP : ORYA_VIRAMA_DOWN;	\
			*(pDst+3)	= ORYA_NUKTA_CENTER;																	\
		} else {																								\
			*(pDst+1) 	= (bPreLgt == FALSE) ? ORYA_NUKTA_LEFT : ORYA_NUKTA_CENTER;								\
			*(pDst+2)	= ((bPreLgt == FALSE) || (bPreFullLgt == TRUE)) ? ORYA_VIRAMA_UP : ORYA_VIRAMA_DOWN;	\
			*(pDst+4)	= ORYA_NUKTA_CENTER;																	\
		}																										\
	}



//	Post RA  : 	Ct + VIRAMA + RA + ...
//				Ct + NUKTA + VIRAMA + RA + ...
//				L + VIRAMA + RA + ...
//				L + NUKTA + VIRAMA + RA + ...
#define IS_ORYA_POST_RA(pC)	\
	(						\
		(IS_ORYA_ALL_CONSONANT(pC) && IS_ORYA_VIRAMA(pC+1) && IS_ORYA_LETTER_RA(pC+2))							\
		|| (IS_ORYA_CONSONANT(pC) && IS_ORYA_NUKTA(pC+1) && IS_ORYA_VIRAMA(pC+2) && IS_ORYA_LETTER_RA(pC+3))	\
	)
#define CHANGE_ORYA_POST_RA(bPreLgt, bPreFullLgt, bPre2PostRA, pSrc, pDst)	\
	{																		\
		if (bPreLgt == FALSE) {												\
			if(IS_ORYA_NUKTA(pSrc+1)) {										\
					*(pDst+1)	= ORYA_NUKTA_CENTER;						\
					*(pDst+2)	= ZWC;										\
					*(pDst+3)	= ORYA_POST_RA_CENTERDOWN;					\
					bPre2PostRA	= TRUE;										\
			} else {														\
				if (IS_ORYA_SPEC_CONSONANT(pSrc)) {							\
					*(pDst)	= ORYA_LETTER_WA_POST_RA;						\
				} else if (IS_ORYA_CONSONANT(pSrc)) {						\
					*(pDst)	= OriyaCtPostRATbl[*(pSrc)-0x0B15];				\
				} else {													\
					*(pDst)	= OriyaCtPostRATbl[*(pSrc)-0x0B37];				\
					bPre2PostRA	= TRUE;										\
				}															\
				*(pDst+1)	= ZWC;											\
				*(pDst+2)	= ZWC;											\
			}																\
		} else {															\
			*(pDst+1)	= ZWC;												\
			if (bPreFullLgt == TRUE) {										\
					*(pDst+2)	= ORYA_POST_RA_RIGHTDOWN;					\
					bPre2PostRA	= TRUE;										\
			} else {														\
				if (bPre2PostRA == FALSE) {									\
					*(pDst+2)	= ORYA_POST_RA_RIGHTDOWN;					\
					bPre2PostRA	= TRUE;										\
				} else {													\
					*(pDst+2)	= ORYA_POST_RA_NOTKERNING;					\
				}															\
			}																\
		}																	\
		bPreFullLgt	= FALSE;												\
	}



//	Not Ligature Rule : C + VIRAMA + [CN | C + NUKTA] + ....
#define IS_ORYA_NOT_LIGATURE_C_VIRAMA(pC)	\
	(										\
		(IS_ORYA_ALL_CONSONANT(pC) && IS_ORYA_VIRAMA(pC+1) && (IS_ORYA_CONSONANT_NUKTA(pC+2) || (IS_ORYA_CONSONANT(pC+2) && IS_ORYA_NUKTA(pC+3))))	\
		|| ((IS_ORYA_ALL_CONSONANT(pC) && !IS_ORYA_LETTER_JA(pC)) && IS_ORYA_VIRAMA(pC+1) && IS_ORYA_LETTER_NYA(pC+2))								\
		|| (IS_ORYA_ALL_CONSONANT(pC) && IS_ORYA_VIRAMA(pC+1) && IS_ORYA_LETTER_WA(pC+2))															\
	)
	
#define CHANGE_ORYA_NOT_LIGATURE_C_VIRAMA(bPreLgt, bPreFullLgt, pSrc, pDst)	\
	{																		\
		*(pDst+1)	= ((bPreLgt == FALSE) || (bPreFullLgt == TRUE)) ? ORYA_VIRAMA_UP : ORYA_VIRAMA_DOWN;	\
																			\
		if (!IS_ORYA_CONSONANT_NUKTA(pSrc+2) && IS_ORYA_NUKTA(pSrc+3)) {	\
			*(pDst+3)	= ORYA_NUKTA_CENTER;								\
		}																	\
	}



//	Ligature Rule : C + VIRAMA + C + ....
#define IS_ORYA_LIGATURE_C_VIRAMA(pC)	\
	(IS_ORYA_ALL_CONSONANT(pC) && IS_ORYA_VIRAMA(pC+1) && IS_ORYA_ALL_CONSONANT(pC+2))

#define	CHANGE_ORYA_LIGATURE_C_VIRAMA(bPreLgt, bPreFullLgt, pSrc, pDst)		\
	{																		\
		if (bPreLgt == FALSE) {												\
			if (IS_ORYA_CONSONANT_NUKTA(pSrc)) {							\
					*(pDst)		= (*(pSrc) == 0x0B5C) ? 0x0B21 : 0x0B22;	\
					*(pDst+1)	= ORYA_NUKTA_LEFT;							\
					*(pDst+2)	= GET_ORYA_LOWPART_LEFT(pSrc+2);			\
					bPreFullLgt	= FALSE;									\
			} else if (IS_ORYA_LETTER_YYA(pSrc+2)) {						\
				if (IS_ORYA_LETTER_DHA(pSrc)) {								\
					*(pDst)		= ORYA_LIGATURE_FULL_YA;					\
					*(pDst+1)	= ZWC;										\
					*(pDst+2)	= ZWC;										\
					bPreFullLgt	= TRUE;										\
				} else {													\
					*(pDst+1)	= ZWC;										\
					*(pDst+2)	= ORYA_LIGATURE_POST_YA;					\
					bPreFullLgt	= FALSE;									\
				}															\
			} else if (IS_ORYA_FULL_LIGATURE(pSrc, pSrc+2)) {				\
					*(pDst)		= GET_ORYA_FULL_LIGATURE(pSrc, pSrc+2);		\
					*(pDst+1)	= ZWC;										\
					*(pDst+2)	= ZWC;										\
					bPreFullLgt	= TRUE;										\
	 		} else {														\
	 				*(pDst+1)	= ZWC;										\
					*(pDst+2)	= GET_ORYA_LOWPART_LEFT(pSrc+2);			\
					bPreFullLgt	= FALSE;									\
			}																\
		} else {															\
			if (IS_ORYA_LETTER_YYA(pSrc+2)) {								\
					*(pDst+1)	= ZWC;										\
					*(pDst+2)	= ORYA_LIGATURE_POST_YA;					\
					bPreFullLgt	= FALSE;									\
			} else {														\
					*(pDst+1)	= ZWC;										\
					*(pDst+2)	= GET_ORYA_LOWPART_RIGHT(pSrc+2);			\
					bPreFullLgt	= FALSE;									\
			}																\
		}																	\
	}



//	Not Ligature Rule : C + NUKTA + VIRAMA + [CN | C + NUKTA] + ....
#define IS_ORYA_NOT_LIGATURE_CT_NUKTA(pC)	\
	(										\
		(IS_ORYA_CONSONANT(pC) && IS_ORYA_NUKTA(pC+1) && IS_ORYA_VIRAMA(pC+2) && (IS_ORYA_CONSONANT_NUKTA(pC+3) || (IS_ORYA_CONSONANT(pC+3) && IS_ORYA_NUKTA(pC+4))))	\
		|| ((IS_ORYA_CONSONANT(pC) && !IS_ORYA_LETTER_JA(pC)) && IS_ORYA_NUKTA(pC+1) && IS_ORYA_VIRAMA(pC+2) && IS_ORYA_LETTER_NYA(pC+3))								\
		|| (IS_ORYA_CONSONANT(pC) && IS_ORYA_NUKTA(pC+1) && IS_ORYA_VIRAMA(pC+2) && IS_ORYA_LETTER_WA(pC+3))															\
	)
#define CHANGE_ORYA_NOT_LIGATURE_CT_NUKTA(bPreLgt, bPreFullLgt, pSrc, pDst)			\
	{																				\
		*(pDst+1) 	= (bPreLgt == FALSE) ? ORYA_NUKTA_LEFT : ORYA_NUKTA_CENTER;		\
		*(pDst+2)	= ((bPreLgt == FALSE) || (bPreFullLgt == TRUE)) ? ORYA_VIRAMA_UP : ORYA_VIRAMA_DOWN;	\
																					\
		if (!IS_ORYA_CONSONANT_NUKTA(pSrc+3) && IS_ORYA_NUKTA(pSrc+4)) {			\
			*(pDst+4)	= ORYA_NUKTA_CENTER;										\
		}																			\
	}



//	Ligature Rule : C + NUKTA + VIRAMA + C + ....
#define IS_ORYA_LIGATURE_CT_NUKTA(pC)	\
	(IS_ORYA_CONSONANT(pC) && IS_ORYA_NUKTA(pC+1) && IS_ORYA_VIRAMA(pC+2) && IS_ORYA_ALL_CONSONANT(pC+3))

#define	CHANGE_ORYA_LIGATURE_CT_NUKTA(bPreLgt, bPreFullLgt, pSrc, pDst)	\
	{																	\
		if (bPreLgt == FALSE) {											\
			if (IS_ORYA_LETTER_YYA(pSrc+3)) {							\
				if (IS_ORYA_LETTER_DHA(pSrc)) {							\
					*(pDst) 	= ORYA_LIGATURE_FULL_YA;				\
					*(pDst+1)	= ZWC;									\
					*(pDst+2)	= ORYA_NUKTA_LEFT;						\
					*(pDst+3)	= ZWC;									\
					bPreFullLgt	= TRUE;									\
				} else {												\
					*(pDst+1)	= ZWC;									\
					*(pDst+2)	= ORYA_NUKTA_CENTER;					\
					*(pDst+3)	= ORYA_LIGATURE_POST_YA;				\
					bPreFullLgt	= FALSE;								\
				}														\
			} else if (IS_CONSONANT_SIGN_TA(pSrc, pSrc+3)) {			\
					*(pDst+1)	= ZWC;									\
					*(pDst+2)	= ORYA_NUKTA_LEFT;						\
					*(pDst+3)	= 0xEFAA;								\
					bPreFullLgt	= FALSE;								\
			} else if (IS_ORYA_FULL_LIGATURE(pSrc, pSrc+3)) {			\
					*(pDst) 	= GET_ORYA_FULL_LIGATURE(pSrc, pSrc+3);	\
					*(pDst+1)	= ZWC;									\
					*(pDst+2)	= ORYA_NUKTA_LEFT;						\
					*(pDst+3)	= ZWC;									\
					bPreFullLgt	= TRUE;									\
			} else {													\
					*(pDst+1)	= ZWC;									\
					*(pDst+2)	= ORYA_NUKTA_LEFT;						\
					*(pDst+3)	= GET_ORYA_LOWPART_LEFT(pSrc+3);		\
					bPreFullLgt	= FALSE;								\
			}															\
		}																\
	}


#define IS_ORYA_VOWEL_LIGATURE(pC)	\
(									\
	(IS_ORYA_LETTER_KHA(pC) || IS_ORYA_LETTER_THA(pC) || IS_ORYA_LETTER_DHA(pC))	\
	&& (IS_ORYA_VOWEL_I(pC+1))		\
)
#define CHANGE_ORYA_VOWEL_LIGATURE(pSrc, pDst)		\
{													\
	if (IS_ORYA_LETTER_KHA(pSrc)) {					\
		*(pDst)	= ORYA_LETTER_KHA_VOWEL_LIGATURE;	\
	} else if (IS_ORYA_LETTER_THA(pSrc)) {			\
		*(pDst)	= ORYA_LETTER_THA_VOWEL_LIGATURE;	\
	} else {										\
		*(pDst)	= ORYA_LETTER_DHA_VOWEL_LIGATURE;	\
	}												\
	*(pDst+1)	= ZWC;								\
}



//-------------------------------------------------------------------------------------------------
//	Member Function.
extern BOOL		ReorderEx_Oriya			(TReorderExAttr* Attr, T_NUM nBase, T_NUM nLen);
//-------------------------------------------------------------------------------------------------
#endif	//	_LGE_REORDEREX_ORIYA_H_
