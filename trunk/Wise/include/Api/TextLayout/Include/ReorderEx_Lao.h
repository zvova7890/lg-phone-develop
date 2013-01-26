/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	LAO LANGUAGE REORDER FORM CODE TABLE

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

#ifndef		_LGE_REORDEREX_LAO_H_
#define		_LGE_REORDEREX_LAO_H_

#include	"ReorderEx_Common.h"
#include	"..\..\BasicApiLib\Include\Include.h"



#ifndef	ReorderDllExport
#ifndef	BNS_EMULATOR
#define	ReorderDllExport	extern
#else
#define	ReorderDllExport	__declspec(dllexport)
#endif
#endif


#ifdef	BNS_MAIN_VERSION
extern A_CHAR	LaoVowelTbl[12];
extern A_CHAR	LaoVowelLeftTbl[12];
extern A_CHAR	LaoBVowelDownTbl[2];
extern A_CHAR	LaoToneMarkTbl[5];
extern A_CHAR	LaoToneMarkLeftTbl[5];	
extern A_CHAR	LaoToneMarkUpTbl[5];
extern A_CHAR	LaoToneMarkUpLeftTbl[5];
extern A_CHAR	LaoToneMarkUpLeftLeftTbl[5];
#endif


//-------------------------------------------------------------------------------------------------
//	Lao Base Code
#define		LAO_CODE(C)						((0x0E80 <= C) && (0x0EFF >= C))



//=================================================================================================
//	Thai Reordering and Rendering Rules		by hyunho.mo. 2009.12.04
//=================================================================================================

//-------------------------------------------------------------------------------------------------
//	Default Constants.
//-------------------------------------------------------------------------------------------------

#define	LAO_LETTER_NGO						0x0E87
#define	LAO_LETTER_NGO_SMALL				0xFFD1	//	0x0E87 보다 Height가 짧은 User Font.

#define	LAO_VOWEL_AA						0X0EB2

#define	LAO_VOWEL_AM						0X0EB3	//	LAO_VOWEL_AM == LAO_NIGGAHITA + LAO_VOWEL_SIGN_AA)
#define	LAO_VOWEL_AM_NDC					0XFFA1	//	NDC = Non-Dot Circle
#define	LAO_VOWEL_AM_LEFT					0XFFAB	//	LAO_VOWEL_AM의 Basic Font Position보다 왼쪽으로 조금 이동된 User Font.

#define	LAO_SIGN_LO							0x0EBC
#define	LAO_SIGN_LO_NDC						0xFFA9
#define	LAO_SIGN_LO_LEFT					0xFFB3

#define	LAO_NIGGAHITA						0x0ECD
#define	LAO_NIGGAHITA_NDC					0xFFB4
#define	LAO_NIGGAHITA_RIGHT					0xFFB5



//-------------------------------------------------------------------------------------------------
//	Rendering Rules for Comparing
//-------------------------------------------------------------------------------------------------

//	Consonant 인지를 확인 (LAO_DIAGRAPH 포함(= 0x0EDC, 0x0EDD))
#define IS_LAO_CONSONANT(pC)				(((0x0E81 <= *(pC)) && (*(pC) <= 0x0EAE)) || (*(pC) == 0x0EDC) || (*(pC) == 0x0EDD))

//	Ascent 영역까지 꼬리가 올라가는 Consonant 인지를 확인.
#define IS_LAO_ALT_CONSONANT(pC)			((*(pC) == 0x0E9B) || (*(pC) == 0x0E9D) || (*(pC) == 0x0E9F) || (*(pC) == 0x0EA2))

//	Descent 영역까지 꼬리가 내려가는 Consonant 인지를 확인.
#define IS_LAO_BLT_CONSONANT(pC)			((*(pC) == 0x0E8A) || (*(pC) == 0x0E96))

//	Consonant 위에 붙는 Vowel 인지를 확인.
#define IS_LAO_AVOWEL(pC)					((*(pC) == 0x0EB1) || ((0x0EB4 <= *(pC)) && (*(pC) <= 0x0EB7)) || (*(pC) == 0x0EBB))

//	Consonant 아래에 붙는 Vowel 인지를 확인.
#define IS_LAO_BVOWEL(pC)					((*(pC) == 0x0EB8) || (*(pC) == 0x0EB9))

//	Tone Mark 인지를 확인 (LAO_CANCELLATION(= 0x0ECC) 포함)
#define IS_LAO_TONE_MARK(pC)				((0x0EC8 <= *(pC)) && (*(pC) <= 0x0ECC))

//	LAO LETTER NGO 인지를 확인.
#define IS_LAO_LETTER_NGO(pC)				(*(pC) == LAO_LETTER_NGO)

//	LAO NIGGAHITA 인지를 확인.
#define	IS_LAO_NIGGAHITA(pC)				(*(pC) == LAO_NIGGAHITA)

//	LAO VOWEL AM 인지를 확인.
#define IS_LAO_VOWEL_AM(pC)					(*(pC) == LAO_VOWEL_AM)

//	LAO VOWEL AA 인지를 확인.
#define IS_LAO_VOWEL_AA(pC)					(*(pC) == LAO_VOWEL_AA)

//	LAO SIGN LO 인지를 확인.
#define IS_LAO_SIGN_LO(pC)					(*(pC) == LAO_SIGN_LO)




//-------------------------------------------------------------------------------------------------
//	Rendering Rules for Changing.
//-------------------------------------------------------------------------------------------------

//	Height가 짧은 LAO LETTER NGO Font로 대체 변환.
//	이유 : 다른 Consonant와는 달리 LAO LETTER NGO 만이 Baseline을 넘어 Descent 영역까지 내려가는데
//	          이때 Below Vowel이나 Sign LO 붙으면 Descent 이하까지 내려가므로 이를 방지하기 위해 적용.
#define CHANGE_LAO_LETTER_NGO(pSrc, pDst)	{																			\
												*(pDst) = LAO_LETTER_NGO_SMALL;											\
											}

//	(Above Vowel) 의 대체 폰트 변환.
#define CHANGE_LAO_C_AV(pSrc, pDst)			{																			\
												if (IS_LAO_ALT_CONSONANT(pSrc)) {										\
													*(pDst + 1) = LaoVowelLeftTbl[*(pSrc + 1) - 0x0EB1];				\
												} else {																\
													*(pDst + 1) = LaoVowelTbl[*(pSrc + 1) - 0x0EB1];					\
												}																		\
											}
//	(Above Vowel + Tone Mark) 의 대체 폰트 변환.
#define	CHANGE_LAO_C_AV_TM(pSrc, pDst)		{																						\
												if (IS_LAO_ALT_CONSONANT(pSrc)) {													\
													*(pDst + 1) = LaoVowelLeftTbl[*(pSrc + 1) - 0x0EB1];							\
													*(pDst + 2) = LaoToneMarkUpLeftLeftTbl[*(pSrc + 2) - 0x0EC8];					\
												} else {																			\
													*(pDst + 1) = LaoVowelTbl[*(pSrc + 1) - 0x0EB1];								\
																																	\
													if ((*(pSrc + 1) == 0x0EB1) || (*(pSrc + 1) == 0x0EBB)) {						\
														*(pDst + 2) = LaoToneMarkUpTbl[*(pSrc + 2) - 0x0EC8];						\
													} else {																		\
														*(pDst + 2) = LaoToneMarkUpLeftTbl[*(pSrc + 2) - 0x0EC8];					\
													}																				\
												}																					\
											}

//	(Below Vowel) 의 대체 폰트 변환.
#define CHANGE_LAO_C_BV(pSrc, pDst)			{																						\
												if (IS_LAO_BLT_CONSONANT(pSrc)) {													\
													*(pDst + 1) = LaoVowelLeftTbl[*(pSrc + 1) - 0x0EB1];							\
												} else {																			\
													*(pDst + 1) = LaoVowelTbl[*(pSrc + 1) - 0x0EB1];								\
												}																					\
											}
//	(Below Vowel + Tone Mark) 의 대체 폰트 변환.
#define	CHANGE_LAO_C_BV_TM(pSrc, pDst)		{																						\
												if (IS_LAO_BLT_CONSONANT(pSrc)) {													\
													*(pDst + 1) = LaoVowelLeftTbl[*(pSrc + 1) - 0x0EB1];							\
												} else {																			\
													*(pDst + 1) = LaoVowelTbl[*(pSrc + 1) - 0x0EB1];								\
												}																					\
												if (IS_LAO_ALT_CONSONANT(pSrc)) {													\
													*(pDst + 2) = LaoToneMarkLeftTbl[*(pSrc + 2) - 0x0EC8];							\
												} else {																			\
													*(pDst + 2) = LaoToneMarkTbl[*(pSrc + 2) - 0x0EC8];								\
												}																					\
											}

//	(Vowel AM) 의 대체 폰트 변환.
#define CHANGE_LAO_C_VAM(pSrc, pDst)		{																						\
												if (IS_LAO_ALT_CONSONANT(pSrc)) {													\
													*(pDst + 1) = LAO_VOWEL_AM_LEFT;												\
												} else {																			\
													*(pDst + 1) = LAO_VOWEL_AM_NDC;													\
												}																					\
											}

//	(Tone Mark) 의 대체 폰트 변환.
#define	CHANGE_LAO_C_TM(pSrc, pDst)			{																						\
												if (IS_LAO_ALT_CONSONANT(pSrc)) {													\
													*(pDst + 1) = LaoToneMarkLeftTbl[*(pSrc + 1) - 0x0EC8]; 						\
												} else {																			\
													*(pDst + 1) = LaoToneMarkTbl[*(pSrc + 1) - 0x0EC8]; 							\
												}																					\
											}

//	(Tone Mark + Vowel AM) 의 대체 폰트 변환.
#define	CHANGE_LAO_C_TM_VAM(pSrc, pDst)		{																						\
												if (IS_LAO_ALT_CONSONANT(pSrc)) {													\
													*(pDst + 1) = LaoToneMarkUpLeftTbl[*(pSrc + 1) - 0x0EC8];						\
													*(pDst + 2) = LAO_VOWEL_AM_LEFT; 												\
												} else {																			\
													*(pDst + 1) = LaoToneMarkUpTbl[*(pSrc + 1) - 0x0EC8];							\
													*(pDst + 2) = LAO_VOWEL_AM_NDC; 												\
												}																					\
											}

//	(NIGGAHITA) 의 대체 폰트 변환.
#define	CHANGE_LAO_C_NIGGAHITA(pSrc, pDst)	{																						\
												*(pDst + 1) = LAO_NIGGAHITA_NDC;													\
											}																						\


//	(NIGGAHITA + Tone Mark) 의 대체 폰트 변환.
#define CHANGE_LAO_C_NIGGAHITA_TM(pSrc, pDst) {																						\
												*(pDst + 1) = LAO_NIGGAHITA_NDC;													\
												*(pDst + 2) = LaoToneMarkUpLeftTbl[*(pSrc + 2) - 0x0EC8];							\
											}

//	(NIGGAHITA + Tone Mark + Vowel AA) 의 대체 폰트 변환.
#define	CHANGE_LAO_C_NIGGAHITA_TM_VAA(pSrc, pDst){																					\
												if (IS_LAO_ALT_CONSONANT(pSrc)) {													\
													*(pDst + 1) = LAO_NIGGAHITA_NDC; 												\
													*(pDst + 2) = LaoToneMarkUpLeftTbl[*(pSrc + 2) - 0x0EC8];						\
												} else {																			\
													*(pDst + 1) = LAO_NIGGAHITA_RIGHT; 												\
													*(pDst + 2) = LaoToneMarkUpTbl[*(pSrc + 2) - 0x0EC8]; 							\
												}																					\
											}

//	(NIGGAHITA + Vowel AA) 의 대체 폰트 변환.
#define	CHANGE_LAO_C_NIGGAHITA_VAA(pSrc, pDst) {																					\
												if (IS_LAO_ALT_CONSONANT(pSrc)) {													\
													*(pDst + 1) = LAO_NIGGAHITA_NDC;												\
												} else {																			\
													*(pDst + 1) = LAO_NIGGAHITA_RIGHT;												\
												}																					\
											}

//	(Sign LO) 의 대체 폰트 변환.
#define	CHANGE_LAO_SIGN_LO(pSrc, pDst)		{																						\
												if (IS_LAO_BLT_CONSONANT(pSrc)) {													\
													*(pDst + 1) = LAO_SIGN_LO_LEFT;													\
												} else {																			\
													*(pDst + 1) = LAO_SIGN_LO_NDC;													\
												}																					\
											}

//	(Sign LO + Above Vowel) 의 대체 폰트 변환.
#define CHANGE_LAO_C_SLO_AV(pSrc, pDst)		{																						\
												CHANGE_LAO_SIGN_LO(pSrc, pDst);														\
												if (IS_LAO_ALT_CONSONANT(pSrc)) {													\
													*(pDst + 2) = LaoVowelLeftTbl[*(pSrc + 2) - 0x0EB1];							\
												} else {																			\
													*(pDst + 2) = LaoVowelTbl[*(pSrc + 2) - 0x0EB1];								\
												}																					\
											}

//	(Sign LO + Above Vowel + Tone Mark) 의 대체 폰트 변환.
#define	CHANGE_LAO_C_SLO_AV_TM(pSrc, pDst)	{																						\
												CHANGE_LAO_SIGN_LO(pSrc, pDst);														\
												if (IS_LAO_ALT_CONSONANT(pSrc)) {													\
													*(pDst + 2) = LaoVowelLeftTbl[*(pSrc + 2) - 0x0EB1];							\
													*(pDst + 3) = LaoToneMarkUpLeftLeftTbl[*(pSrc + 3) - 0x0EC8];					\
												} else {																			\
													*(pDst + 2) = LaoVowelTbl[*(pSrc + 2) - 0x0EB1];								\
													if ((*(pSrc + 2) == 0x0EB1) || (*(pSrc + 2) == 0x0EBB)) {						\
														*(pDst + 3) = LaoToneMarkUpTbl[*(pSrc + 3) - 0x0EC8];						\
													} else {																		\
														*(pDst + 3) = LaoToneMarkUpLeftTbl[*(pSrc + 3) - 0x0EC8];					\
													}																				\
												}												 									\
											}

//	(Sign LO + Below Vowel) 의 대체 폰트 변환.
#define CHANGE_LAO_C_SLO_BV(pSrc, pDst)		{																						\
												CHANGE_LAO_SIGN_LO(pSrc, pDst);														\
												*(pDst + 2) = LaoBVowelDownTbl[*(pSrc + 2) - 0x0EB8];								\
											}

//	(Sign LO + Below Vowel + Tone Mark) 의 대체 폰트 변환.
#define	CHANGE_LAO_C_SLO_BV_TM(pSrc, pDst)	{																						\
												CHANGE_LAO_C_SLO_BV(pSrc, pDst);													\
												if (IS_LAO_ALT_CONSONANT(pSrc)) {													\
													*(pDst + 3) = LaoToneMarkLeftTbl[*(pSrc + 3) - 0x0EC8];							\
												} else {																			\
													*(pDst + 3) = LaoToneMarkTbl[*(pSrc + 3) - 0x0EC8];								\
												}																					\
											}

//	(Sign LO + Tone Mark) 의 대체 폰트 변환.
#define	CHANGE_LAO_C_SLO_TM(pSrc, pDst)		{																						\
												CHANGE_LAO_SIGN_LO(pSrc, pDst);														\
												if (IS_LAO_ALT_CONSONANT(pSrc)) {													\
													*(pDst + 2) = LaoToneMarkLeftTbl[*(pSrc + 2) - 0x0EC8]; 						\
												} else {																			\
													*(pDst + 2) = LaoToneMarkTbl[*(pSrc + 2) - 0x0EC8]; 							\
												}																					\
											}

//	(Sign LO + Tone Mark + Vowel AM) 의 대체 폰트 변환.
#define	CHANGE_LAO_C_SLO_TM_VAM(pSrc, pDst)	{																						\
												CHANGE_LAO_SIGN_LO(pSrc, pDst);														\
												if (IS_LAO_ALT_CONSONANT(pSrc)) {													\
													*(pDst + 2) = LaoToneMarkUpLeftTbl[*(pSrc + 2) - 0x0EC8];						\
													*(pDst + 3) = LAO_VOWEL_AM_LEFT;												\
												} else {																			\
													*(pDst + 2) = LaoToneMarkUpTbl[*(pSrc + 2) - 0x0EC8];							\
													*(pDst + 3) = LAO_VOWEL_AM_NDC; 												\
												}																					\
											}

//	(Sign LO + NIGGAHITA) 의 대체 폰트 변환.
#define	CHANGE_LAO_C_SLO_NIGGAHITA(pSrc, pDst)	{																					\
												CHANGE_LAO_SIGN_LO(pSrc, pDst);														\
												*(pDst + 2) = LAO_NIGGAHITA_NDC;													\
											}

//	(Sign LO + NIGGAHITA + Tone Mark) 의 대체 폰트 변환.
#define CHANGE_LAO_C_SLO_NIGGAHITA_TM(pSrc, pDst) {																					\
												CHANGE_LAO_C_SLO_NIGGAHITA(pSrc, pDst);												\
												*(pDst + 3) = LaoToneMarkUpLeftTbl[*(pSrc + 3) - 0x0EC8];							\
											}

//	(Sign LO + NIGGAHITA + Tone Mark + Vowel AA) 의 대체 폰트 변환.
#define	CHANGE_LAO_C_SLO_NIGGAHITA_TM_VAA(pSrc, pDst) {																				\
												CHANGE_LAO_SIGN_LO(pSrc, pDst);														\
												if (IS_LAO_ALT_CONSONANT(pSrc)) {													\
													*(pDst + 2) = LAO_NIGGAHITA_NDC;												\
													*(pDst + 3) = LaoToneMarkUpLeftTbl[*(pSrc + 3) - 0x0EC8];						\
												} else {																			\
													*(pDst + 2) = LAO_NIGGAHITA_RIGHT;												\
													*(pDst + 3) = LaoToneMarkUpTbl[*(pSrc + 3) - 0x0EC8];							\
												}																					\
											}

//	(Sign LO + NIGGAHITA + Vowel AA) 의 대체 폰트 변환.
#define	CHANGE_LAO_C_SLO_NIGGAHITA_VAA(pSrc, pDst) {																				\
												CHANGE_LAO_SIGN_LO(pSrc, pDst);														\
												if (IS_LAO_ALT_CONSONANT(pSrc)) {													\
													*(pDst + 2) = LAO_NIGGAHITA_NDC;												\
												} else {																			\
													*(pDst + 2) = LAO_NIGGAHITA_RIGHT;												\
												}																					\
											}

//	(Sign LO + Vowel AM) 의 대체 폰트 변환.
#define CHANGE_LAO_C_SLO_VAM(pSrc, pDst)	{																						\
												CHANGE_LAO_SIGN_LO(pSrc, pDst);														\
												if (IS_LAO_ALT_CONSONANT(pSrc)) {													\
													*(pDst + 2) = LAO_VOWEL_AM_LEFT;												\
												} else {																			\
													*(pDst + 2) = LAO_VOWEL_AM_NDC;													\
												}																					\
											}



//-------------------------------------------------------------------------------------------------
//	Function
extern BOOL		ReorderEx_Lao				(TReorderExAttr* Attr, T_NUM nBase, T_NUM nLen);
//-------------------------------------------------------------------------------------------------
#endif	//	_LGE_REORDEREX_LAO_H_
