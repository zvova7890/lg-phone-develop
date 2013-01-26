/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	LAO LANGUAGE REORDER FORM CODE TABLE

	Copyright(c)     2010 LG Electronics Inc.

	�׷� : TextLayoutLib API
	���� : �⺻���
	��� : �����
	���� : 2.00
	���� : 2010.05.03

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
#define	LAO_LETTER_NGO_SMALL				0xFFD1	//	0x0E87 ���� Height�� ª�� User Font.

#define	LAO_VOWEL_AA						0X0EB2

#define	LAO_VOWEL_AM						0X0EB3	//	LAO_VOWEL_AM == LAO_NIGGAHITA + LAO_VOWEL_SIGN_AA)
#define	LAO_VOWEL_AM_NDC					0XFFA1	//	NDC = Non-Dot Circle
#define	LAO_VOWEL_AM_LEFT					0XFFAB	//	LAO_VOWEL_AM�� Basic Font Position���� �������� ���� �̵��� User Font.

#define	LAO_SIGN_LO							0x0EBC
#define	LAO_SIGN_LO_NDC						0xFFA9
#define	LAO_SIGN_LO_LEFT					0xFFB3

#define	LAO_NIGGAHITA						0x0ECD
#define	LAO_NIGGAHITA_NDC					0xFFB4
#define	LAO_NIGGAHITA_RIGHT					0xFFB5



//-------------------------------------------------------------------------------------------------
//	Rendering Rules for Comparing
//-------------------------------------------------------------------------------------------------

//	Consonant ������ Ȯ�� (LAO_DIAGRAPH ����(= 0x0EDC, 0x0EDD))
#define IS_LAO_CONSONANT(pC)				(((0x0E81 <= *(pC)) && (*(pC) <= 0x0EAE)) || (*(pC) == 0x0EDC) || (*(pC) == 0x0EDD))

//	Ascent �������� ������ �ö󰡴� Consonant ������ Ȯ��.
#define IS_LAO_ALT_CONSONANT(pC)			((*(pC) == 0x0E9B) || (*(pC) == 0x0E9D) || (*(pC) == 0x0E9F) || (*(pC) == 0x0EA2))

//	Descent �������� ������ �������� Consonant ������ Ȯ��.
#define IS_LAO_BLT_CONSONANT(pC)			((*(pC) == 0x0E8A) || (*(pC) == 0x0E96))

//	Consonant ���� �ٴ� Vowel ������ Ȯ��.
#define IS_LAO_AVOWEL(pC)					((*(pC) == 0x0EB1) || ((0x0EB4 <= *(pC)) && (*(pC) <= 0x0EB7)) || (*(pC) == 0x0EBB))

//	Consonant �Ʒ��� �ٴ� Vowel ������ Ȯ��.
#define IS_LAO_BVOWEL(pC)					((*(pC) == 0x0EB8) || (*(pC) == 0x0EB9))

//	Tone Mark ������ Ȯ�� (LAO_CANCELLATION(= 0x0ECC) ����)
#define IS_LAO_TONE_MARK(pC)				((0x0EC8 <= *(pC)) && (*(pC) <= 0x0ECC))

//	LAO LETTER NGO ������ Ȯ��.
#define IS_LAO_LETTER_NGO(pC)				(*(pC) == LAO_LETTER_NGO)

//	LAO NIGGAHITA ������ Ȯ��.
#define	IS_LAO_NIGGAHITA(pC)				(*(pC) == LAO_NIGGAHITA)

//	LAO VOWEL AM ������ Ȯ��.
#define IS_LAO_VOWEL_AM(pC)					(*(pC) == LAO_VOWEL_AM)

//	LAO VOWEL AA ������ Ȯ��.
#define IS_LAO_VOWEL_AA(pC)					(*(pC) == LAO_VOWEL_AA)

//	LAO SIGN LO ������ Ȯ��.
#define IS_LAO_SIGN_LO(pC)					(*(pC) == LAO_SIGN_LO)




//-------------------------------------------------------------------------------------------------
//	Rendering Rules for Changing.
//-------------------------------------------------------------------------------------------------

//	Height�� ª�� LAO LETTER NGO Font�� ��ü ��ȯ.
//	���� : �ٸ� Consonant�ʹ� �޸� LAO LETTER NGO ���� Baseline�� �Ѿ� Descent �������� �������µ�
//	          �̶� Below Vowel�̳� Sign LO ������ Descent ���ϱ��� �������Ƿ� �̸� �����ϱ� ���� ����.
#define CHANGE_LAO_LETTER_NGO(pSrc, pDst)	{																			\
												*(pDst) = LAO_LETTER_NGO_SMALL;											\
											}

//	(Above Vowel) �� ��ü ��Ʈ ��ȯ.
#define CHANGE_LAO_C_AV(pSrc, pDst)			{																			\
												if (IS_LAO_ALT_CONSONANT(pSrc)) {										\
													*(pDst + 1) = LaoVowelLeftTbl[*(pSrc + 1) - 0x0EB1];				\
												} else {																\
													*(pDst + 1) = LaoVowelTbl[*(pSrc + 1) - 0x0EB1];					\
												}																		\
											}
//	(Above Vowel + Tone Mark) �� ��ü ��Ʈ ��ȯ.
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

//	(Below Vowel) �� ��ü ��Ʈ ��ȯ.
#define CHANGE_LAO_C_BV(pSrc, pDst)			{																						\
												if (IS_LAO_BLT_CONSONANT(pSrc)) {													\
													*(pDst + 1) = LaoVowelLeftTbl[*(pSrc + 1) - 0x0EB1];							\
												} else {																			\
													*(pDst + 1) = LaoVowelTbl[*(pSrc + 1) - 0x0EB1];								\
												}																					\
											}
//	(Below Vowel + Tone Mark) �� ��ü ��Ʈ ��ȯ.
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

//	(Vowel AM) �� ��ü ��Ʈ ��ȯ.
#define CHANGE_LAO_C_VAM(pSrc, pDst)		{																						\
												if (IS_LAO_ALT_CONSONANT(pSrc)) {													\
													*(pDst + 1) = LAO_VOWEL_AM_LEFT;												\
												} else {																			\
													*(pDst + 1) = LAO_VOWEL_AM_NDC;													\
												}																					\
											}

//	(Tone Mark) �� ��ü ��Ʈ ��ȯ.
#define	CHANGE_LAO_C_TM(pSrc, pDst)			{																						\
												if (IS_LAO_ALT_CONSONANT(pSrc)) {													\
													*(pDst + 1) = LaoToneMarkLeftTbl[*(pSrc + 1) - 0x0EC8]; 						\
												} else {																			\
													*(pDst + 1) = LaoToneMarkTbl[*(pSrc + 1) - 0x0EC8]; 							\
												}																					\
											}

//	(Tone Mark + Vowel AM) �� ��ü ��Ʈ ��ȯ.
#define	CHANGE_LAO_C_TM_VAM(pSrc, pDst)		{																						\
												if (IS_LAO_ALT_CONSONANT(pSrc)) {													\
													*(pDst + 1) = LaoToneMarkUpLeftTbl[*(pSrc + 1) - 0x0EC8];						\
													*(pDst + 2) = LAO_VOWEL_AM_LEFT; 												\
												} else {																			\
													*(pDst + 1) = LaoToneMarkUpTbl[*(pSrc + 1) - 0x0EC8];							\
													*(pDst + 2) = LAO_VOWEL_AM_NDC; 												\
												}																					\
											}

//	(NIGGAHITA) �� ��ü ��Ʈ ��ȯ.
#define	CHANGE_LAO_C_NIGGAHITA(pSrc, pDst)	{																						\
												*(pDst + 1) = LAO_NIGGAHITA_NDC;													\
											}																						\


//	(NIGGAHITA + Tone Mark) �� ��ü ��Ʈ ��ȯ.
#define CHANGE_LAO_C_NIGGAHITA_TM(pSrc, pDst) {																						\
												*(pDst + 1) = LAO_NIGGAHITA_NDC;													\
												*(pDst + 2) = LaoToneMarkUpLeftTbl[*(pSrc + 2) - 0x0EC8];							\
											}

//	(NIGGAHITA + Tone Mark + Vowel AA) �� ��ü ��Ʈ ��ȯ.
#define	CHANGE_LAO_C_NIGGAHITA_TM_VAA(pSrc, pDst){																					\
												if (IS_LAO_ALT_CONSONANT(pSrc)) {													\
													*(pDst + 1) = LAO_NIGGAHITA_NDC; 												\
													*(pDst + 2) = LaoToneMarkUpLeftTbl[*(pSrc + 2) - 0x0EC8];						\
												} else {																			\
													*(pDst + 1) = LAO_NIGGAHITA_RIGHT; 												\
													*(pDst + 2) = LaoToneMarkUpTbl[*(pSrc + 2) - 0x0EC8]; 							\
												}																					\
											}

//	(NIGGAHITA + Vowel AA) �� ��ü ��Ʈ ��ȯ.
#define	CHANGE_LAO_C_NIGGAHITA_VAA(pSrc, pDst) {																					\
												if (IS_LAO_ALT_CONSONANT(pSrc)) {													\
													*(pDst + 1) = LAO_NIGGAHITA_NDC;												\
												} else {																			\
													*(pDst + 1) = LAO_NIGGAHITA_RIGHT;												\
												}																					\
											}

//	(Sign LO) �� ��ü ��Ʈ ��ȯ.
#define	CHANGE_LAO_SIGN_LO(pSrc, pDst)		{																						\
												if (IS_LAO_BLT_CONSONANT(pSrc)) {													\
													*(pDst + 1) = LAO_SIGN_LO_LEFT;													\
												} else {																			\
													*(pDst + 1) = LAO_SIGN_LO_NDC;													\
												}																					\
											}

//	(Sign LO + Above Vowel) �� ��ü ��Ʈ ��ȯ.
#define CHANGE_LAO_C_SLO_AV(pSrc, pDst)		{																						\
												CHANGE_LAO_SIGN_LO(pSrc, pDst);														\
												if (IS_LAO_ALT_CONSONANT(pSrc)) {													\
													*(pDst + 2) = LaoVowelLeftTbl[*(pSrc + 2) - 0x0EB1];							\
												} else {																			\
													*(pDst + 2) = LaoVowelTbl[*(pSrc + 2) - 0x0EB1];								\
												}																					\
											}

//	(Sign LO + Above Vowel + Tone Mark) �� ��ü ��Ʈ ��ȯ.
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

//	(Sign LO + Below Vowel) �� ��ü ��Ʈ ��ȯ.
#define CHANGE_LAO_C_SLO_BV(pSrc, pDst)		{																						\
												CHANGE_LAO_SIGN_LO(pSrc, pDst);														\
												*(pDst + 2) = LaoBVowelDownTbl[*(pSrc + 2) - 0x0EB8];								\
											}

//	(Sign LO + Below Vowel + Tone Mark) �� ��ü ��Ʈ ��ȯ.
#define	CHANGE_LAO_C_SLO_BV_TM(pSrc, pDst)	{																						\
												CHANGE_LAO_C_SLO_BV(pSrc, pDst);													\
												if (IS_LAO_ALT_CONSONANT(pSrc)) {													\
													*(pDst + 3) = LaoToneMarkLeftTbl[*(pSrc + 3) - 0x0EC8];							\
												} else {																			\
													*(pDst + 3) = LaoToneMarkTbl[*(pSrc + 3) - 0x0EC8];								\
												}																					\
											}

//	(Sign LO + Tone Mark) �� ��ü ��Ʈ ��ȯ.
#define	CHANGE_LAO_C_SLO_TM(pSrc, pDst)		{																						\
												CHANGE_LAO_SIGN_LO(pSrc, pDst);														\
												if (IS_LAO_ALT_CONSONANT(pSrc)) {													\
													*(pDst + 2) = LaoToneMarkLeftTbl[*(pSrc + 2) - 0x0EC8]; 						\
												} else {																			\
													*(pDst + 2) = LaoToneMarkTbl[*(pSrc + 2) - 0x0EC8]; 							\
												}																					\
											}

//	(Sign LO + Tone Mark + Vowel AM) �� ��ü ��Ʈ ��ȯ.
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

//	(Sign LO + NIGGAHITA) �� ��ü ��Ʈ ��ȯ.
#define	CHANGE_LAO_C_SLO_NIGGAHITA(pSrc, pDst)	{																					\
												CHANGE_LAO_SIGN_LO(pSrc, pDst);														\
												*(pDst + 2) = LAO_NIGGAHITA_NDC;													\
											}

//	(Sign LO + NIGGAHITA + Tone Mark) �� ��ü ��Ʈ ��ȯ.
#define CHANGE_LAO_C_SLO_NIGGAHITA_TM(pSrc, pDst) {																					\
												CHANGE_LAO_C_SLO_NIGGAHITA(pSrc, pDst);												\
												*(pDst + 3) = LaoToneMarkUpLeftTbl[*(pSrc + 3) - 0x0EC8];							\
											}

//	(Sign LO + NIGGAHITA + Tone Mark + Vowel AA) �� ��ü ��Ʈ ��ȯ.
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

//	(Sign LO + NIGGAHITA + Vowel AA) �� ��ü ��Ʈ ��ȯ.
#define	CHANGE_LAO_C_SLO_NIGGAHITA_VAA(pSrc, pDst) {																				\
												CHANGE_LAO_SIGN_LO(pSrc, pDst);														\
												if (IS_LAO_ALT_CONSONANT(pSrc)) {													\
													*(pDst + 2) = LAO_NIGGAHITA_NDC;												\
												} else {																			\
													*(pDst + 2) = LAO_NIGGAHITA_RIGHT;												\
												}																					\
											}

//	(Sign LO + Vowel AM) �� ��ü ��Ʈ ��ȯ.
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
