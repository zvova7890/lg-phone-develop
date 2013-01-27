/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	THAI LANGUAGE REORDER FORM CODE TABLE

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

#ifndef		_LGE_REORDEREX_THAI_H_
#define		_LGE_REORDEREX_THAI_H_


#include	"ReorderEx_Common.h"
#include	"..\..\BasicApiLib\Include\Include.h"



#ifndef	ReorderDllExport
#ifndef	BNS_EMULATOR
#define	ReorderDllExport		extern
#else
#define	ReorderDllExport		__declspec( dllexport )
#endif
#endif


#ifdef	BNS_MAIN_VERSION
	extern A_CHAR	ThaiVowelTbl[10];
	extern A_CHAR	VowelLeftTbl[7];
	extern A_CHAR	TMOTbl[8];
	extern A_CHAR	TMULTbl[5];
	extern A_CHAR	TMTLTbl[5];
	extern A_CHAR	TMTbl[5];
	extern A_CHAR	TMAMLTbl[4];
	extern A_CHAR	TMAMTbl[4];
#endif


//-------------------------------------------------------------------------------------------------
//	Thai Script code range
#define		THAI_CODE(C)					((0x0E00 <= C) && (0x0E7F >= C))


//=================================================================================================
//	Thai Reordering and Rendering Rule by Sebastian
//=================================================================================================

//	Total Consonant
#define	THAI_CONSONANT(C)					((0x0E01 <= C) && (C <= 0x0E2E))

//	Consonant 아래에 글자가 붙은 Consonant.
#define	THAI_HIDDEN_CONSONANT(C)			((C == 0x0E0D) || (C == 0x0E10))

//	Baseline 이하까지 내려가는 Consonant.
#define	THAI_UNDER_CONSONANT(C)				((C == 0x0E0E) || (C == 0x0E0F) || (C == 0x0E24) || (C == 0x0E26))

//	꼬리가 올라간 Consonant.
#define	THAI_LEFT_CONSONANT(C)				((C == 0x0E1B) || (C == 0x0E1D) || (C == 0x0E1F) || (C == 0x0E2C))

#define	THAI_VOWEL(C)						((0x0E31 <= C) && (C <= 0x0E3A))

#define	THAI_ABOVE_VOWEL(C)					((C == 0x0E31) || ((0x0E34 <= C) && (C <= 0x0E37)))

#define	THAI_SARA_AM(C)						(C == 0x0E33)
#define	THAI_DISP_SARA_AM(C)				((C == 0xF71E) || (C == 0xF71F))

#define	THAI_BELOW_VOWEL(C)					((0x0E38 <= C) && (C <= 0x0E3A))

#define	THAI_TONEMARK(C)					((0x0E48 <= C) && (C <= 0x0E4B))

#define	THAI_MAITAIKHU(C)					(C == 0x0E47)

#define	THAI_SIGN(C)						((0x0E4C <= C) && (C <= 0x0E4E))

//	Sign THANTHAKHAT(==0x0E4C) 포함 
#define	THAI_TONEANDSIGN(C)					((0x0E48 <= C) && (C <= 0x0E4C))



//-------------------------------------------------------------------------------------------------
//	Consonants + Vowels

//	1. Basic form
#define	IS_THAI_VOWEL(pC)					(THAI_CONSONANT(*pC) && THAI_VOWEL(*(pC+1)))
#define	Change_VOWEL(pSrc, pDst)			*(pDst + 1) = ThaiVowelTbl[*(pSrc + 1) - 0x0E31];

//	2. Vowel shift left.
#define	IS_VOWEL_LEFT(pC)					(THAI_LEFT_CONSONANT(*pC) && (THAI_ABOVE_VOWEL(*(pC+1)) || THAI_SARA_AM(*(pC+1))))
#define	Change_VL(pSrc, pDst)				*(pDst + 1) = VowelLeftTbl[*(pSrc + 1) - 0x0E31];

//	3. 0E0D와 0E10은 아래에 붙는 Vowel이 오면 그 아래에 붙어있는 글자의 display가 생략된다.
#define	IS_HIDDEN(pC)						(THAI_HIDDEN_CONSONANT(*pC) && THAI_BELOW_VOWEL(*(pC+1)))
#define	Change_Hidden(pSrc, pDst)			{																						\
												*pDst		= (*pSrc == 0x0E0D) ? 0xF70F : 0xF700;									\
												*(pDst + 1) = ThaiVowelTbl[*(pSrc + 1) - 0x0E31];									\
											}

//	4. 0E0E, 0E0F, 0E24, 0E26의 경우 4Level까지 쓰여지므로 그 아래의 영역에 Vowel이 붙는다.
//	(Consonant 자체가 Baseline 이하까지 사용한다)
#define	IS_UNDER(pC)						(THAI_UNDER_CONSONANT(*pC) && THAI_BELOW_VOWEL(*(pC+1)))
#define	Change_Under(pSrc, pDst)			*(pDst + 1) = (*(pSrc + 1) == 0x0E38 ? 0xF718 : (*(pSrc + 1) == 0x0E39 ? 0xF719 : 0xF71A));


//-------------------------------------------------------------------------------------------------
//	Consonant + Tone Mark or Signs
//	1. Basic form
#define	IS_TONEMARK_ORIGINAL(pC)			(THAI_CONSONANT(*pC) && (THAI_MAITAIKHU(*(pC+1)) || THAI_TONEMARK(*(pC+1)) || THAI_SIGN(*(pC+1))))
#define	Change_TM_O(pSrc, pDst)				*(pDst + 1) = TMOTbl[*(pSrc + 1) - 0x0E47];

//	2. Consonants + Tone Mark일 경우에 좌측으로 가는 경우
#define	IS_TONEMARK_UNDERLEFT(pC)			(THAI_LEFT_CONSONANT(*pC) && THAI_TONEMARK(*(pC+1)))
#define	Change_TM_UL(pSrc, pDst)			*(pDst + 1) = TMULTbl[*(pSrc + 1) - 0x0E48];

//	3. Consonants + Sign 일 경우에 좌측으로 가는 경우(0x0E47)
#define	IS_MAITAIKHU(pC)					(THAI_LEFT_CONSONANT(*pC) && THAI_MAITAIKHU(*(pC+1)))
#define	Change_MAITAIKHU(pSrc, pDst)		*(pDst + 1) = 0xF712;




//-------------------------------------------------------------------------------------------------
//	Consonants + Above Vowels + Tone Mark
//	1. Basic form
#define	IS_TONEMARK_TOP(pC)					(THAI_CONSONANT(*pC) && THAI_ABOVE_VOWEL(*(pC+1)) && THAI_TONEANDSIGN(*(pC+2)))
#define	Change_TM_T(pSrc, pDst)				{																						\
												*(pDst + 1) = ThaiVowelTbl[*(pSrc + 1) - 0x0E31];									\
												*(pDst + 2) = TMTbl[*(pSrc + 2) - 0x0E48];											\
											}
//	2. Consonants + Vowels + Tone Mark에서 위/좌측으로 가는 경우
#define	IS_TONEMARK_TOPLEFT(pC)				(THAI_LEFT_CONSONANT(*pC) && THAI_ABOVE_VOWEL(*(pC+1)) && THAI_TONEANDSIGN(*(pC+2)))
#define	Change_TM_TL(pSrc, pDst)			{																						\
												*(pDst + 1) = VowelLeftTbl[*(pSrc + 1) - 0x0E31];									\
												*(pDst + 2) = TMTLTbl[*(pSrc + 2) - 0x0E48];										\
											}
//-------------------------------------------------------------------------------------------------
//	Consonants + Below Vowels + Tone Mark
//	1. Basic form
#define	IS_TONEMARK_UNDER(pC)				(THAI_CONSONANT(*pC) && THAI_BELOW_VOWEL(*(pC+1)) && THAI_TONEANDSIGN(*(pC+2)))
#define	Change_TM_U(pSrc, pDst)				{																						\
												*(pDst + 1) = ThaiVowelTbl[*(pSrc + 1) - 0x0E31];									\
												*(pDst + 2) = TMOTbl[*(pSrc + 2) - 0x0E47];											\
											}
//	2. Consonants + Below Vowels + Tone Mark에서 아래/좌측으로 가는 경우
#define	IS_TONEMARK_LEFTUNDER(pC)			(THAI_LEFT_CONSONANT(*pC) && THAI_BELOW_VOWEL(*(pC+1)) && THAI_TONEANDSIGN(*(pC+2)))
#define	Change_TM_LU(pSrc, pDst)			{																						\
												*(pDst + 1) = ThaiVowelTbl[*(pSrc + 1) - 0x0E31];									\
												*(pDst + 2) = TMULTbl[*(pSrc + 2) - 0x0E48];										\
											}
//	3. Consonants + Below Vowels + Tone Mark에서 아래로 가는 경우
#define	IS_TONEMARK_UNDERV(pC)				(THAI_UNDER_CONSONANT(*pC) && THAI_BELOW_VOWEL(*(pC+1)) && THAI_TONEANDSIGN(*(pC+2)))
#define	Change_TM_UV(pSrc, pDst)			{																						\
												*(pDst + 1) = (*(pSrc + 1) == 0xE38 ? 0xF718 : (*(pSrc + 1) == 0xE39 ? 0xF719 : 0xF71A));\
												*(pDst + 2) = TMOTbl[*(pSrc + 2) - 0x0E47];											\
											}
//	4. Hidden Consonants + Below Vowels + Tone Mark에서 아래로 가는 경우
#define	IS_TONEMARK_UNDERH(pC)				(THAI_HIDDEN_CONSONANT(*pC) && THAI_BELOW_VOWEL(*(pC+1)) && THAI_TONEANDSIGN(*(pC+2)))
#define	Change_TM_UH(pSrc, pDst)			{																						\
												*pDst		= *pSrc == 0x0E0D ? 0xF70F : 0xF700;									\
												*(pDst + 1) = ThaiVowelTbl[*(pSrc + 1) - 0x0E31];									\
												*(pDst + 2) = TMOTbl[*(pSrc + 2) - 0x0E47];											\
											}

//-------------------------------------------------------------------------------------------------
//	Consonant + Tone Mark + SARA AM
//	1. Basic form
#define	IS_TONEMARK_AM(pC)					(THAI_CONSONANT(*pC) && THAI_TONEMARK(*(pC+1)) && THAI_SARA_AM(*(pC+2)))
#define	Change_TM_AM(pSrc, pDst)			{																						\
												*(pDst + 1) = TMAMTbl[*(pSrc + 1) - 0x0E48];										\
												*(pDst + 2) = 0xF71E;																\
											}
//	2. Consonant + Tone Mark + SARA AA에서 위/좌측으로 Tone Mark가 찍히는 경우
#define	IS_TONEMARK_AML(pC)					(THAI_LEFT_CONSONANT(*pC) && THAI_TONEMARK(*(pC+1)) && THAI_SARA_AM(*(pC+2)))
#define	Change_TM_AML(pSrc, pDst)			{																						\
												*(pDst + 1) = TMAMLTbl[*(pSrc + 1) - 0x0E48];										\
												*(pDst + 2) = 0xF71F;																\
											}


//-------------------------------------------------------------------------------------------------
//	Member Function.
extern BOOL		ReorderEx_Thai				(TReorderExAttr* Attr, T_NUM nBase, T_NUM nLen);
//-------------------------------------------------------------------------------------------------
#endif	//	_LGE_REORDEREX_THAI_H_